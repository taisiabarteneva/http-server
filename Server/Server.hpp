#ifndef 	SERVER_HPP
# define 	SERVER_HPP

# include <stdio.h>
# include <iostream>
# include <string.h>
# include <string>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <cctype>
# include <cstdio>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/poll.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include "../Parser/Location.hpp"
# include "../Http/Http.hpp"

# define BUF_LEN        1024
# define PARSE_ERROR    -1

class Server 
{
	public:
		Server(std::string & address, std::vector<Location> locations);
		Server(const Server & rhs);
		const Server & operator=(const Server & rhs);
		~Server();

		/* ------------------------------------------------ getters */
		std::vector<Location>    	getLocations();
		std::string              	getAddress();
		int							getListenSocket();

		/* --------------------------------------- member functions */
		void setupServer(void);
		void run(void);

	private:
		Server();
		void createListenSocket(void);
		int fillServerStruct(void);
		int parseAddress(void);
		void bindListenSock(void);
		void createQueue(void);
		void initSocketSet(void);
		void handlePollIn(int fd);
		int readFromClient(int conn, char* buffer, size_t size);
		int sendToClient(int conn, const char *buffer, size_t size);
		void closeConnection(int i);
		void cleanAllSockets(void);


		std::vector<Location> 	_locations;
		std::string             _address;
		int 					listenSocket;
		int						connectSocket;
		int						enable_mode;
		char					ipv4[16];
		char					port[4];
		struct sockaddr_in  	addr;
		struct pollfd       	activeSet[SOMAXCONN];
		int   		            numSet;
		char                	buf[BUF_LEN];
		Http					http;

};


#endif
