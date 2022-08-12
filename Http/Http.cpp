#include "Http.hpp"

std::string Http::getResponse() const
{
    return (response->responseToString());
}

std::string Http::getRequest() const
{
    return (request->toString());
}


Http::Http(std::string message)
{
    request = new Request(message);
    response = new Response();
    
}

Http::~Http()
{
    delete response;
    delete request;
}