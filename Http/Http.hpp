#ifndef HTTP_HPP
# define HTTP_HPP

# include "Defines.hpp"
# define HEADERS_SIZE 16384
# define REQUEST_SIZE 16384

# include <map>
# include <string>
# include <iostream>
# include <fstream>
# include <unistd.h>
# include "Response.hpp"
# include "Request.hpp"
# include "../Server/Server.hpp"
// class Server;

class Http
{
    private:
        static std::map<int , std::pair<Request*, Response*> > connections;
        int recv_msg(int conn, char* buffer, size_t size);
        int send_msg(int conn, const char *buffer, size_t size);
        int makeRequest(int fd, Request *request);
        //config file;??

    public:
        Http();
        ~Http();

        int acceptRequest(int fd, Server * serv);
        int getResponse(int fd, Server * serv);
};


#endif
