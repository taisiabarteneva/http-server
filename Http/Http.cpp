#include "Http.hpp"

Http::Http(std::string message)
{
    request = new Request(message);
    response = new Response(*request);
    
}

Http::~Http()
{
    delete response;
    delete request;
}