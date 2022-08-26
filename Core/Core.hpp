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

class Core
{
    private:
        std::vector<Server>     servers;
        struct pollfd           activeSet[SOMAXCONN];
        int                     numSet;
        char                    buf[BUF_LEN];
        std::vector<int>        vSocks;
    
    public:
        Core(char* config);
        Core(const Core & rhs);
        const Core & operator=(const Core & rhs);
        ~Core();
        
        void setUpWebServers(void);
        void runWebServers(void);
        void printInfo(void);
    
    private:
        int readFromClient(int conn, char* buffer, size_t size);
        int sendToClient(int conn, const char *buffer, size_t size);
        void acceptNewConnection(int listenSocket);
        void handleExistingConnection(struct pollfd & connection);
        void closeConnection(struct pollfd connection, int i);
        void cleanAllSockets(void);
};

#endif
