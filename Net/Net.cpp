#include "Net.hpp"

Net::Net() {}

Net::~Net() {}

int Net::listen_net(std::string address)
{
    int enable = 1;
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket < 0)
    {
        return SOCKET_ERROR;
    }
    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
    {
        return SETOPT_ERROR;
    }
    if (setsockopt(listen_socket, SOL_SOCKET, SO_NOSIGPIPE, &enable, sizeof(enable)) < 0)
    {
        return SETOPT_ERROR;
    }
    char ipv4[16];
    char port[6];
    if (parse_address(address, ipv4, port) != 0)
    {
        return PARSE_ERROR;
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port));
    serv_addr.sin_addr.s_addr = inet_addr(ipv4);
    if (bind(listen_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
    {
        return BIND_ERROR;
    }
    if (listen(listen_socket, SOMAXCONN) != 0)
    {
        return LISTEN_ERROR;
    }
    return listen_socket;
}

int Net::accept_net(int listen_socket)
{
    return accept(listen_socket, NULL, NULL);
}

int Net::close_net(int socket)
{
    return close(socket);
}

int Net::send_net(int conn, const char *buffer, size_t size)
{
    return send(conn, buffer, (int)size, 0);
}
int Net::recv_net(int conn, char* buffer, size_t size)
{
    return recv(conn, buffer, (int)size, 0);
}

int Net::parse_address(std::string address, char *ipv4, char *port)
{
    size_t i = 0, j = 0;
    int pos = address.find(":");
    if (pos == std::string::npos)
        return 1;
    if (pos >= 16)
        return 2;
    strcpy(ipv4, address.substr(0, pos).c_str());
    std::string port_s = address.substr(pos + 1, address.length());
    if (port_s.length() >= 6)
        return 3;
    strcpy(port, port_s.c_str());
    return 0;
}
