#include "Cgi.hpp"

using namespace std;
// спецификация указывает какая инфа нужна скрипту от сервера и какая нужна серверу от скрипта

Cgi::Cgi(Request& req) {
	request = req;
}

Cgi::Cgi(const Cgi &cgi_copy) {
	*this = cgi_copy;
}

Cgi::~Cgi() {};
