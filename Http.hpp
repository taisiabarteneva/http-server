#ifndef HTTP_HPP
# define HTTP_HPP

#include <map>
#include <string>
#include <iostream>

class Http
{
private:
    std::string startLine;
    std::map<std::string, std::string> headers;
    std::string body;

    void recieveStartLine(std::string& request);
    void recieveHeaders(std::string& request);

public:
    Http(std::string request);
    ~Http();
    std::string toString(Http http);
    // Http createResponce();
};


#endif
