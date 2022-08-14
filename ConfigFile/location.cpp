#include "location.hpp"

Location::Location(map<string, string>& loc) {

    map<string, string>::iterator it_loc = loc.begin();
    while (it_loc != loc.end()) {
        if (it_loc->first == "listen")
            ip_port = it_loc->second;
        else if (it_loc->first == "server_name")
            server_name = it_loc->second;
        else if (it_loc->first == "client_max_body_size") {
            if (it_loc->second[it_loc->second.size() - 1] == 'K')
                client_max_body_size = atol(
                        it_loc->second.substr(0,it_loc->second.size() - 1).c_str()) * 1000;
            else if (it_loc->second[it_loc->second.size() - 1] == 'M')
                client_max_body_size = atol(
                        it_loc->second.substr(0,it_loc->second.size() - 1).c_str()) * 1000000;
            else if (it_loc->second[it_loc->second.size() - 1] == 'G')
                client_max_body_size = atol(
                        it_loc->second.substr(0,it_loc->second.size() - 1).c_str()) * 1000000000;
            else {
                cout << "30" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (it_loc->first == "root")
            root = it_loc->second;
        else if (it_loc->first == "path")
            path = it_loc->second;
        else if (it_loc->first == "autoindex")
            autoindex = it_loc->second;
        else if (it_loc->first == "index")
            index = it_loc->second;
        else if (it_loc->first == "cgi_path")
            cgi_path = it_loc->second;
        else if (it_loc->first == "cgi_extension")
            cgi_extension = it_loc->second;
        else if (it_loc->first == "allow_methods")
            allow_methods = getTokens(it_loc->second, '/');
        else
            errors[it_loc->first] = it_loc->second;
        ++it_loc;
    }
}

Location::Location(const Location& location) {
    *this = location;
}

Location::~Location() {}

Location& Location::operator=(const Location& location) {
    if (this != &location) {
        ip_port = location.ip_port;
        path = location.path;
        server_name = location.server_name;
        client_max_body_size = location.client_max_body_size;
        root = location.root;
        cgi_path = location.cgi_path;
        cgi_extension = location.cgi_extension;
        autoindex = location.autoindex;
        index = location.index;
        allow_methods = location.allow_methods;
        errors = location.errors;
//        this_location = location.this_location;
//        authentication = location.authentication;
    }
    return (*this);
}

vector<string> Location::getTokens(string &str, char sep) {
    vector<string>	words;
    size_t          i = 0;
    size_t          j;

    while (str[i]) {
        while (str[i] && str[i] == sep)
            ++i;
        j = i;
        while (str[i] && str[i] != sep)
            ++i;
        string word = str.substr(j, i - j);
        words.push_back(word);
    }
    return (words);
}

string Location::getIpPort() const {
    return ip_port;
}

string Location::getServerName() const {
    return server_name;
}

size_t Location::getClientMaxBodySize() const {
    return client_max_body_size;
}

string Location::getRoot() const {
    return root;
}

string Location::getPath() const {
    return path;
}

string Location::getCgiPath() const {
    return cgi_path;
}

string Location::getCgiExtension() const {
    return cgi_extension;
}

string Location::getIndex() const {
    return index;
}

string Location::getAutoindex() const {
    return autoindex;
}

vector<string>  Location::getAllowMethods() const {
    return allow_methods;
}

map<string, string> Location::getErrors() const {
    return errors;
}
