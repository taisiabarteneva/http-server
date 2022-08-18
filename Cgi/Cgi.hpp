#ifndef CGI_HPP
#define CGI_HPP

#include <dir.h>
#include <vector>

#include "../Http/Request.hpp"

class Cgi {
public:
	Cgi();
	Cgi(const Cgi& cgi_copy);
	~Cgi();

    void    prepareCgiEnv();
    void    prepareCgiArgs();

private:
	Request request;
    string  abs_path;
    char**  env;
    char**  args;


};

#endif
