#include "Server.hpp"

Server::Server(string& ip_port, vector<Location> all_locations) {
	this->ip_port = ip_port;
	locations = all_locations;
}

Server::~Server() {}

vector<Location> Server::getLocations() {
	return locations;
}

string  Server::getIpPort() {
	return ip_port;
}