#include "Http.hpp"

std::string Http::getResponse() const
{
    return (response->responseToString());
}

std::string Http::getRequest() const
{
    return (request->toString());
}

std::streamsize Http::getBytes() const
{
    return (bytes);
}

bool Http::isEndOfFile()
{
    if (bytes < BUFFER_SIZE)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

char* Http::recieveFile(std::string fileName)
{
    if (!reader.is_open())
    {
        reader.open(fileName, std::ios::in);
    }
    reader.read(fileBuffer, BUFFER_SIZE);
    bytes = reader.gcount();
    return (fileBuffer);
}


Http::Http(std::string message)
{
    request = new Request(message);
    response = new Response();
    bytes = BUFFER_SIZE;
    
}

Http::~Http()
{
    delete response;
    delete request;
}