#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Request.hpp"

class Response
{
private:
    int responseCode;
    std::string version;
    std::string code;
    std::string status;
    std::map <std::string, std::string> headers;
    std::string body;

    std::string getHeaderStrings();
    

public:
    const static int OK = 200;
    const static int CREATED = 201;
    const static int ACCEPTED = 202;
    const static int NO_CONTENT = 203;
    const static int BAD_REQUEST = 400;
    const static int FORBIDDEN = 403;
    const static int NOT_FOUND = 404;
    const static int REQUEST_TIMEOUT = 408;
    const static int INTERNAL_SERVER_ERROR = 500;
    const static int BAD_GATEWAY = 502;
    const static int SERVICE_UNAVAILABLE = 503;// TODO: дополнить/исправить

    Response(Request request);
    ~Response();
    std::string responseToString();

};

#endif