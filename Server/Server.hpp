#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ConfigFile/location.hpp"

using namespace std;


class Server {
public:
    Server(string& ip_port, vector<Location> locations);
    ~Server();
};


#endif
