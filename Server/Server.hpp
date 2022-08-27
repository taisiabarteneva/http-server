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

/*
	struct sockaddr_in 
	{
		short          sin_family;
		u_short        sin_port;
		struct in_addr sin_addr;
		char           sin_zero[8]; // for align
	} 
*/

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
		void 	setupServer(void);

	private:
		Server();
		void 	createListenSocket(void);
		int 	fillServerStruct(void);
		int 	parseAddress(void);
		void 	bindListenSock(void);
		void 	createQueue(void);

		std::vector<Location> 	_locations;
		std::string             _address;
		int 					listenSocket;
		int						enable_mode;
		char					ipv4[16];
		char					port[4];
		struct sockaddr_in  	addr;
};


#endif
