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
# include "../Http/Http.hpp"
# include "../Parser/location.hpp"
# include "../Server/Server.hpp"

# define BUF_LEN        1024
# define PARSE_ERROR    -1

class Core
{
    private:
        vector<Server>      servers;
        int                 listen_sock;    //  слушающий сокет
        int                 connect_sock;   //  двусторонний сокет
        int                 enable_mode;
        char                buf[BUF_LEN];
        char                ipv4[16];
        char                port[4];
        socklen_t           size;
        struct sockaddr_in  addr;
        struct sockaddr_in  client;
        struct pollfd       active_set[SOMAXCONN]; // ??
        bool                autoindex;
        int                 num_set;
        Http                http;

        int parse_address(std::string address, char *ipv4, char *port);
    
    public:
        Core(char** argv);
        Core(const Core & rhs);
        const Core & operator=(const Core & rhs);
        ~Core();

        void createListenSock(void);
        int fillServerStruct(std::string address);
        void bindListenSock(void);
        void createQueue(void);
        void initSocketSet(void);
        void stateManager(void); 

        int readFromClient(int conn, char* buffer, size_t size);
        int sendToClient(int conn, const char *buffer, size_t size);
};

#endif
