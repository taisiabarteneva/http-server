#include "location.hpp"

Location::Location(map<string, string>& loc) {
    map<string, string>::iterator it_loc = loc.begin();
    while (it_loc != loc.end()) {
        if (it_loc->first == "listen")
            ip_port = it_loc->second;
        else if (it_loc->first == "server_name")
            server_name = it_loc->second;
        else if (it_loc->first == "client_max_body_size") {
			char c = it_loc->second[it_loc->second.length() - 1];
			if (c != 'K' && c != 'M' && c != 'G') {
				cout << "30" << endl;
				exit(EXIT_FAILURE);
			}
			size_t client_size = atol(it_loc->second.substr(0,it_loc->second.size() - 1).c_str());
	        switch (c) {
				case 'K':
					client_max_body_size = client_size * 1000;
			        break;
				case 'M':
					client_max_body_size = client_size * 1000000;
					break;
				case 'G':
					client_max_body_size = client_size * 1000000000;
					break;
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

//	printLocationInfo();
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

void Location::printLocationInfo() {

	cout << "ip_port: " << ip_port << endl;
	cout << "server_name: " << server_name << endl;
	cout << "client_max_body_size: " << client_max_body_size << endl;
	cout << "root: " << root << endl;
	cout << "path: " << path << endl;
	cout << "cgi_path: " << cgi_path << endl;
	cout << "cgi_extension: " << cgi_extension << endl;
	cout << "autoindex: " << autoindex << endl;
	cout << "index: " << index << endl;

	vector<string>::iterator it = allow_methods.begin();
	cout << "allow_methods: ";
	while (it != allow_methods.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	map<string, string>::iterator ite = errors.begin();
    map<string, string>::iterator rite = errors.end();
    if (rite != ite)
            rite--;
	cout << "errors: ";
	while (ite != rite) {
		cout << ite->first << " " << ite->second << ", ";
		++ite;
	}
    if (ite != errors.end())
        cout << ite->first << " " << ite->second;

	cout << endl << "done!" << endl << endl;
}