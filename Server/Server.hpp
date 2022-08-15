#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Parser//location.hpp"

using namespace std;


class Server {
public:
    Server(string& ip_port, vector<Location> all_locations);
    ~Server();

	vector<Location>    getLocations();
	string              getIpPort();

private:
	vector<Location>    locations;
	string              ip_port;
};


#endif
