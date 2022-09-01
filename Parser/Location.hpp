#ifndef LOCATION_HPP
#define LOCATION_HPP

# include <string>
# include <vector>
# include <map>
# include <iostream>

#include "ConfigUtils.hpp"

using namespace std;

class Location {
public:
    Location(map<string, string>& loc);
    ~Location();
    Location(const Location& location);
    Location& operator=(const Location& location);

    vector<string>      getTokens(string &str, char sep);
    string              getIpPort() const;
    string              getServerName() const;
    size_t              getClientMaxBodySize() const;
    string              getRoot() const;
    string              getPath() const;
    string              getIndex() const;
    string              getAutoindex() const;
    vector<string>      getAllowMethods() const;
    map<string, string> getErrors() const;
	string              getCgiDir() const;
	void                printLocationInfo();

private:
    string              ip_port;
    string              server_name;
    size_t              client_max_body_size;
    string              root;
    string              path;
    string              cgi_dir;
    string              autoindex;
    string              index;
    vector<string>      allow_methods;
    map<string, string> errors;

//    map<string, string> this_location;
//    string    authentication;
};

#endif
