# include "Server.hpp"

Server::Server(std::string & address, std::vector<Location> locations) 
{
	_address = address;
	_locations = locations;
	enable_mode = 1;
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
		enable_mode = rhs.enable_mode;
		strcpy(ipv4, rhs.ipv4); strcpy(port, rhs.port);
		addr = rhs.addr;
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
    if (setsockopt(listenSocket, SOL_SOCKET, SO_NOSIGPIPE, \
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