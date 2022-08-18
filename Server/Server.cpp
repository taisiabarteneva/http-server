# include "Server.hpp"

Server::Server(std::string & address, std::vector<Location> locations) 
{
	memset(activeSet, 0, sizeof(activeSet));
	_address = address;
	_locations = locations;
	enable_mode = 1;
	connectSocket = -1;
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
	initSocketSet();
}

/* 
	# define POLLIN			0x001		// There is data to read.
	# define POLLPRI		0x002		// There is urgent data to read.
	# define POLLOUT		0x004		// Writing now will not block.
*/

void Server::run(void)
{
	int res;
    int status;
    int i;
	bool end;

	do
	{
		/* 
            it waits for one of a set of file descriptors to become ready to perform I/O
            1 - the set of file descriptors to be monitored 
            2 - specify the number of items in the fds array
            3 - specifies the number of milliseconds that poll() should block waiting for a file descriptor to become
                ready
                specifying a negative value in timeout means an infinite timeout
            функция блокируется до тех пор, пока во входящем сокете не появятся данные для чтения; изначально проверяем только слушающий сокет
        */
		res = poll(activeSet, numSet, -1);
		if (res <= 0)
        {
            std::cerr << "[Error] : poll() system call failed\n";
            exit(EXIT_FAILURE);
        } 
		else if (res > 0)
		{
			for (i = 0; i < numSet; i++)
			{
				/* 
					find the active POLL IN event and determine 
					whether it's a listening or connected socket 
				*/
				if (activeSet[i].fd == listenSocket)
				{
					/*
						accept all incoming connections that are quequed up on the listening socket, 
							if there are any
					*/
					do
					{
						connectSocket = accept(listenSocket, NULL, NULL);
						if (connectSocket < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								std::cerr << "[Error] : accept() system call failed\n";
								end = true;
							}
							break ;
						}
						if (numSet < SOMAXCONN)
						{
							/* add new connection to pollfd struct */
							activeSet[numSet].fd = connectSocket;
							activeSet[numSet].events = POLLIN;
							numSet++;
						} 
						else 
						{
							std::cerr << "[Error] : queue is full\n";
							close(connectSocket);
						}
					} 	while (connectSocket != -1);
				}
				else if (activeSet[i].revents & POLLIN) 		/* the connection was already established  */
				{
					// std::cout << "Poll In \n";
					status = readFromClient(activeSet[i].fd, buf, sizeof(buf) + 1);
					if (status < 0)
					{
						closeConnection(i);
					} 
					else 
					{
						activeSet[i].events = POLLOUT;
					}
				}
				else if (activeSet[i].revents & POLLOUT)
                {
					// std::cout << "Poll Out \n";
					// std::cout << "NumSet : " << numSet << std::endl;
                    sendToClient(activeSet[i].fd, buf, BUF_LEN);
                    activeSet[i].revents = POLLIN;
                }
				else if (activeSet[i].revents != POLLIN && activeSet[i].revents != POLLOUT)
				{
					std::cerr << "[Error] : socket error\n";
					closeConnection(i);
				}
			}
		}
	} while (end == false);
	cleanAllSockets();
}

/* ------------------------------------------- private methods */
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
	addr.sin_len = sizeof(addr);
    addr.sin_port = htons(atoi(port));
	/* inet_aton() converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary form */
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
        fprintf(stderr, "[Error] : listen() call failed\n");
        exit(EXIT_FAILURE);
    }
}

void Server::initSocketSet()
{
	activeSet[0].fd = listenSocket;
	activeSet[0].events = POLLIN;
	activeSet[0].revents = 0;
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
    http.processMessage(buffer);
    return 1; // ToDo
}

int Server::sendToClient(int conn, const char *buffer, size_t size)
{
    std::string response = http.getResponseHeader();
    response = "HTTP/1.1 200 OK\nContent-Length: 5\nContent-Type: text/html\r\n\r\nhello";
    // std::cout << "THIS IS A RESPONSE : \n\n" << response << std::endl;
    // get bytes and send it back to the client
    // std::cout << "THIS IS BODY::\n\n" << http.getResponseBody().c_str() << std::endl;
    send(conn, response.c_str(), strlen(response.c_str()), 0);
    // http.recieveDataFromFile();
    // while (!http.isEndOfFile())
    // {
    //     send(conn, http.getResponseBody().c_str(), strlen(http.getResponseBody().c_str()), 0);
    //     http.recieveDataFromFile();
    // }
    return 0; // ToDo
}

void Server::closeConnection(int i)
{
	close(activeSet[i].fd);
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
