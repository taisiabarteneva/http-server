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
# define PARSE_ERROR    -1

class Core
{
    private:
        std::vector<Server>    servers;
    
    public:
        Core(char* config);
        Core(const Core & rhs);
        const Core & operator=(const Core & rhs);
        ~Core();
};

#endif
