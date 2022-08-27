#ifndef CORE_HPP
# define CORE_HPP

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
# include "../Server/Server.hpp"

# define BUF_LEN        1024
# define INFINITE 		-1

/*
	struct pollfd 
	{
		int 	fd;				// the following descriptor being polled 
		short 	events;			// input parameter, specifying the events the app is interested in for the fd
		short 	revents;		// output parameter, filled by a kernel with the events that actually occured
	}; 
	nfds_t — an unsigned integer type (long) used for the number of file descriptors
*/

class Core
{
    private:
        std::vector<Server>     servers;
        struct pollfd           activeSet[SOMAXCONN];
        int                     numSet;
        char                    buf[BUF_LEN];
        std::vector<int>        vSocks;
        Http                    HTTP;
    
    public:
        Core(char* config);
        Core(const Core & rhs);
        const Core & operator=(const Core & rhs);
        ~Core();
        
        void setUpWebServers(void);
        void runWebServers(void);
        void printInfo(void);
    
    private:
        void acceptNewConnection(int listenSocket);
        void handleExistingConnection(struct pollfd & connection, int i);
        void closeConnection(struct pollfd connection, int i);
        void cleanAllSockets(void);
};

#endif
