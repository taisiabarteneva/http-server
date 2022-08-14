#ifndef NET_HPP
# define NET_HPP

#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <vector>

class Net
{
private:
    enum error_t {
        SOCKET_ERROR = -1,
        SETOPT_ERROR = -2,
        PARSE_ERROR = -3,
        BIND_ERROR = -4,
        LISTEN_ERROR = -5,
    };
    std::vector<int> listeners;

    int parse_address(std::string address, char *ipv4, char *port);

public:
    Net();
    ~Net();

    int listen_net(std::string address);
    int accept_net(int listener);
    int close_net(int conn);

    int send_net(int conn, const char* buffer, size_t size);
    int recv_net(int conn, char* buffer, size_t size);



};



#endif