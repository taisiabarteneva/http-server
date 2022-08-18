#ifndef CGI_HPP
#define CGI_HPP

#include "../Http/Request.hpp"

class Cgi {
public:
	Cgi();
	Cgi(const Cgi& cgi_copy);
	~Cgi();

private:
	Request                 request;


};

#endif
