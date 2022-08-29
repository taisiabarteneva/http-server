#include "Core.hpp"
#include "../Parser/ConfigFile.hpp"

Core::Core(char *config)
:   numSet(0)
{
    ConfigFile  cfg;
	memset(activeSet, 0, sizeof(activeSet));

    cfg.openConfigFile(config);
    servers = cfg.getAllServers();
}

Core::Core(const Core & rhs) 
{
    *this = rhs;
}

const Core & Core::operator=(const Core & rhs)
{
    if (this != &rhs) {}

    return *this;
}

Core::~Core() {}

void Core::setUpWebServers(void)
{
    std::cout << "Num of servers : " << servers.size() << std::endl;
    for (int i = 0; i < servers.size(); i++)
    {
        std::cout << "Setting up server at " << servers[i].getAddress() << std::endl;
        servers[i].setupServer();
        activeSet[i].fd = servers[i].getListenSocket();
        activeSet[i].events = POLLIN;
        numSet++;
        vSocks.push_back(servers[i].getListenSocket());
        std::cout << "activeSet[i] : " << activeSet[i].fd << std::endl;
    }
}

/* 
	The poll() API is more efficient than the select() API and therefore poll() is always recommended over select() 
	- https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/poll.htm

	# define POLLIN			0x001		// data other than high-priority data may be read without blocking
	# define POLLPRI		0x002		// high priority data may be read without blocking
	# define POLLOUT		0x004		// normal data may be written without blocking
	# define POLLERR     	0x008		// an error has occurred (revents only)
    # define POLLHUP     	0x010		// device has been disconnected (revents only)
   	# define POLLNVAL    	0x020		// invalid fd member (revents only).

	int   poll(struct pollfd fds[], nfds_t nfds, int timeout);
	  	1 - the set of file descriptors to be monitored 
		2 - specify the number of items in the fds array
		3 - if the value of timeout is -1, poll() will block until a requested event occurs or until the call is interrupted
*/

void Core::runWebServers(void)
{
    int i, status;
    std::vector<int>::iterator it;
	std::map<int, Server *> toHttp;

	while (true)
	{		
		/* 	
			on success, poll() returns a non-negative value which is the
			number of elements in the pollfds whose revents fields have been
			set to a nonzero value, indincating an event or an error
		*/
		status = poll(activeSet, numSet, INFINITE);
		if (status < 0)
		{
			std::cerr << "[Error] : poll() system call failed\n";
            exit(EXIT_FAILURE);
		}
		std::cout << "numset : " << numSet << std::endl;
		for (i = 0; i < numSet; i++)
		{
			// std::cout << "numset : " << numSet << std::endl;
            it = std::find(vSocks.begin(), vSocks.end(), activeSet[i].fd);
			/* for debugging purposes */
			/* if (activeSet[i].revents != 0) 
            {
                printf("fd = %d; revents: %s%s\n", activeSet[i].fd,
                        (activeSet[i].revents & POLLIN)  ? "POLLIN "  : "",
                        (activeSet[i].revents & POLLOUT) ? "POLLOUT " : "");
			} */
			if (activeSet[i].revents == 0)
				continue ;
            else if (it != vSocks.end()) // else if (activeSet[i].fd == listenSocket)
			{
				for (std::vector<Server>::iterator serversIt = servers.begin(); serversIt != servers.end(); serversIt++)
				{
					if (serversIt->getListenSocket() == *it)
						acceptNewConnection(serversIt, toHttp);
				}
			}
			else if ((activeSet[i].revents & POLLIN || activeSet[i].revents & POLLOUT))
			{
				std::cout << "FD being processed : " << activeSet[i].fd << " i " << i << "\n";
				handleExistingConnection(activeSet[i], i, toHttp[activeSet[i].fd]);
			}
			else
			{
				std::cerr << "FD : " << activeSet[i].fd << ", revents : " << activeSet[i].revents << std::endl;
				std::cerr << "[Error] : internal error has occurred. Disconnecting...\n";
				closeConnection(activeSet[i], i);
			}
		}
	}

	cleanAllSockets();
}

void Core::acceptNewConnection(std::vector<Server>::iterator serv, \
	 std::map<int, Server *> & toHttp)
{
	int 	connectSocket = 1;

	while (connectSocket > 0)
	{
		connectSocket = accept(serv->getListenSocket(), NULL, NULL);
		if (connectSocket < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "[Error] : accept() system call failed\n";
				exit(EXIT_FAILURE);
			}
			/* connection already exist */
			break ;
		}
		toHttp[connectSocket] = &(*serv);
		activeSet[numSet].fd = connectSocket;
		/* revents field is 0 by default */
		activeSet[numSet].events = POLLIN;
		numSet++;
	}
}

void Core::handleExistingConnection(struct pollfd & connection, int i, Server* serv)
{
	std::string response;

	if (connection.revents & POLLIN)
	{
		std::cout << "Here\n";
		if (http.acceptRequest(connection.fd, serv))
            connection.events = POLLOUT;
	}
	else if (connection.revents & POLLOUT)
	{
		std::cout << "Here\n";

		if (http.getResponse(connection.fd, serv))
		{
			closeConnection(connection, i);
			// connection.events = 0;
		}
	}
	/* 
		reset revents field to reuse the structure 
	*/
	connection.revents = 0;
}

void Core::closeConnection(struct pollfd connection, int i)
{
	close(connection.fd);
	activeSet[i].fd = -1;
	for (int i = 0; i < numSet; i++)
	{
		if (activeSet[i].fd == -1)
		{
			for (int j = 0; j < numSet - 1; j++)
			{
				activeSet[i].fd = activeSet[j + 1].fd;
				activeSet[i].events = activeSet[j + 1].events;
				activeSet[i].revents = activeSet[j + 1].revents;
			}
			i--;
		}
	}
	numSet--;
}

void Core::cleanAllSockets(void)
{
	for (int i = 0; i < numSet; i++)
	{
		if (activeSet[i].fd >= 0)
			close(activeSet[i].fd);
	}
	numSet = 0;
}

void Core::printInfo(void)
{
    vector<Server>::iterator it = servers.begin();
    while (it != servers.end())
    {
        cout << "Server's address: " << it->getAddress() << endl;
        vector<Location> locations = it->getLocations();
        cout << "Locations' size: " << locations.size() << endl;
        vector<Location>::iterator iter = locations.begin();
        while (iter != locations.end()) 
        {
            iter->printLocationInfo();
            cout << endl;
            ++iter;
        }
        ++it;
    }
}