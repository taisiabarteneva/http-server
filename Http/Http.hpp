#ifndef HTTP_HPP
# define HTTP_HPP

# include <map>
# include <string>
# include <iostream>
# include "Response.hpp"
# include "Request.hpp"

class Http
{
private:
    Request* request;
    Response* response;

public:
    Http(std::string request);
    ~Http();
    std::string toString(Http http);
    // Http createResponce();
};


#endif
