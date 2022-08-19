# include "Server.hpp"

Server::Server(std::string & address, std::vector<Location> locations) 
{
	memset(activeSet, 0, sizeof(activeSet));
	_address = address;
	_locations = locations;
	enable_mode = 1;
	// connectSocket = 0;
}

Server::Server(const Server & rhs)
{
	*this = rhs;
}

const Server & Server::operator=(const Server & rhs)
{
	if (this != &rhs) 
	{
		_address = rhs._address;
		listenSocket = rhs.listenSocket;
		connectSocket = rhs.connectSocket;
		enable_mode = rhs.enable_mode;
		strcpy(ipv4, rhs.ipv4); strcpy(port, rhs.port);
		addr = rhs.addr;
		numSet = rhs.numSet;
		strcpy(buf, rhs.buf);
		_locations = rhs._locations;
	}

	return *this;
}

Server::~Server() {}

/* -------------------------------------------------- getters */
std::vector<Location> Server::getLocations() 
{
	return _locations;
}

std::string Server::getAddress() 
{
	return _address;
}

int	Server::getListenSocket()
{
	return listenSocket;
}

/* ------------------------------------------ member functions */
void Server::setupServer(void)
{
	createListenSocket();
	fillServerStruct();
	bindListenSock();
	createQueue();
	initPollFdStruct();
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

void Server::run(void)
{
	int i, status;
	bool end = false;

	while (true)
	{
		std::cout << "Poll\n";
		status = poll(activeSet, numSet, INFINITE);
		if (status < 0)
		{
			std::cerr << "[Error] : poll() system call failed\n";
            exit(EXIT_FAILURE);
		}
		// numset additional variable 
		std::cout << "Poll\n";
		for (i = 0; i < numSet; i++)
		{
			if (activeSet[i].revents != POLLIN && activeSet[i].revents != POLLOUT \
					&& activeSet[i].revents != 0)
			{
				fprintf(stdout, "socket [%d] revents : %d\n", activeSet[i].fd, activeSet[i].revents);
				std::cerr << "[Error] : unexpected socket status, closing the connection...\n";
				this->closeConnection(activeSet[i], i);
				continue ;
			}
			else if (activeSet[i].fd == this->listenSocket)
			{
				this->acceptNewConnection();
			}
			else
			{
				this->handleExistingConnection(activeSet[i]);
			}
		}
	}
	cleanAllSockets();
}

// /* ------------------------------------------- private methods */
Server::Server()
{}

void Server::createListenSocket(void)
{
	std::cout << "> creating listening socket...\n";
 	this->listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket < 0)
    {
        std::cerr << "[Error] : socket() system call failed\n";
        exit(EXIT_FAILURE);
    }
	/* 
		allow socket descriptor to be reuseable 
	*/
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, \
                    (const void *)&enable_mode, sizeof(enable_mode)) < 0)
    {
        std::cerr << "[Error] : setsockopt() system call failed\n";
		close(listenSocket);
        exit(EXIT_FAILURE);
    }
	/* 	
		set socket to be non-blocking. all of the sockets for
  		the incoming connections will also be nonblocking since
  		they will inherit that state from the listening socket	
	*/
	if (fcntl(listenSocket, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "[Error] : fcntl() system call failed\n";
		close(listenSocket);
		exit(EXIT_FAILURE);
	}
}

int Server::fillServerStruct(void)
{
    if (parseAddress() != 0)
        return 1;
	memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
	addr.sin_len = sizeof(addr);
	bzero(&(addr.sin_zero), 8);
	/* 
		inet_aton() converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary form 
	*/
	if (inet_aton(ipv4, &addr.sin_addr) == 0)
	{
		std::cerr << "[Error] : invalid address\n";
		return 1;
	}
    return 0;
}

void Server::bindListenSock(void)
{
    std::cout << "> binding ...\n";

    /* bind()
       assigns the address specified by addr to the socket referred to
       by the file descriptor sockfd.  addrlen specifies the size 
    */
    if (bind(listenSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "[Error] : bind() system call failed\n";
		close(listenSocket);
	    exit(EXIT_FAILURE);
    }
}

void Server::createQueue(void)
{
    std::cout << "> listening ...\n";

    /*  listen() 
        marks the socket referred to by sockfd as a passive
        socket, that is, as a socket that will be used to accept incoming
        connection requests using accept(2)
    */
    if (listen(listenSocket, SOMAXCONN) != 0)
    {
        std::cerr<< "[Error] : listen() call failed\n";
		close(listenSocket);
        exit(EXIT_FAILURE);
    }
}

void Server::initPollFdStruct()
{
	memset(activeSet, 0, sizeof(activeSet));
	/*
		add the listening socket to the array  
	*/
	activeSet[0].fd = listenSocket;
	activeSet[0].events = POLLIN;
	numSet = 1;
}

int Server::parseAddress()
{
    size_t i = 0, j = 0;

    int pos = _address.find(":");
    if (pos == std::string::npos)
        return 1;
    if (pos >= 16)
        return 2;
    strcpy(this->ipv4, _address.substr(0, pos).c_str());
    std::string port_s = _address.substr(pos + 1, _address.length());
    if (port_s.length() >= 6)
        return 3;
    strcpy(this->port, port_s.c_str());
    return 0;
}

int Server::readFromClient(int conn, char* buffer, size_t size)
{
    bzero((void *)buf, sizeof(buf));
    recv(conn, buffer, (int)size, 0);
    return 0; // ToDo
}

int Server::sendToClient(int conn, const char *buffer, size_t size)
{
	std::string response;

    response = "HTTP/1.1 200 OK\nContent-Length: 5\nContent-Type: text/html\r\n\r\nhello";
    send(conn, response.c_str(), strlen(response.c_str()), 0);
    return 0; // ToDo
}

void Server::acceptNewConnection(void)
{
	std::cout << "listening socket is readable\n";
	while (true)
	{
				std::cout << "Accept\n";
		this->connectSocket = accept(listenSocket, NULL, NULL);
				std::cout << "Accept\n";
		if (connectSocket < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "[Error] : accept() system call failed\n";
				exit(EXIT_FAILURE);
			}
			break ;
		}
		// std::cout << "new incoming connection -- " << connectSocket << std::endl;
		activeSet[numSet].fd = connectSocket;
		activeSet[numSet].events = POLLIN;
		activeSet[numSet].revents = 0; // 
		numSet++;
	}
}

void Server::handleExistingConnection(struct pollfd connection)
{
	int status;

	/* обнаружили событие, обнулим revents, чтобы можно было переиспользовать структуру */
	if (connection.revents & POLLIN)
	{
				std::cout << "Receive\n";
		status = this->readFromClient(connection.fd, buf, sizeof(buf));
				std::cout << "Receive\n";
		if (status == 0)
		{
			connection.revents = POLLOUT;
		}
	}
	else if (connection.revents & POLLOUT)
	{
				std::cout << "Send\n";
		status = this->sendToClient(connection.fd, buf, sizeof(buf));
				std::cout << "Send\n";
		if (status == 0)
		{
			connection.revents = POLLIN;
		}
	}
	// connection.revents = 0;
}

void Server::closeConnection(struct pollfd connection, int i)
{
	close(connection.fd);
	activeSet[i].fd = -1;
	for (int i = 0; i < numSet; i++)
	{
		if (activeSet[i].fd == -1)
		{
			for (int j = 0; j < numSet - 1; j++)
				activeSet[i].fd = activeSet[j + 1].fd;
			i--;
			numSet--;
		}
	}
}

void Server::cleanAllSockets(void)
{
	for (int i = 0; i < numSet; i++)
	{
		if (activeSet[i].fd >= 0)
			close(activeSet[i].fd);
	}
}
