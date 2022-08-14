#include "Http.hpp"

Http::Http(std::string message)
{
    request = new Request(message);
    response = new Response();
    bytes = BUFFER_SIZE;
    prepareResponse("resources/");
}

Http::~Http()
{
    delete response;
    delete request;
}

void Http::recieveDataFromFile()
{
    if (!reader.is_open())
    {
        reader.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
        response->setFileSize(reader.tellg()); //TODO:: а что с большим файлом?
        reader.seekg(0);
        response->setFileType(fileName.substr(fileName.find(".") + 1));
        reader.clear();
    }
    reader.read(fileBuffer, BUFFER_SIZE);
    bytes = reader.gcount();
}

void    Http::prepareResponse(std::string root)
{
    //TODO: проверка файла
    response->setCode("200");
    response->setStatus(response->statusCodes[200]);
    fileName = root + "22.png"; //TODO: filename from GET
    recieveDataFromFile();
    response->setHeader("Content-Type", response->getFileType());
    response->setHeader("Content-Length", response->getFileSize());
    response->setBody(fileBuffer);
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

std::string Http::getResponse() const
{
    return (response->responseToString());
}

std::string Http::getResponseHeader() const
{
    return (response->responseHeaderToString());
}

std::string Http::getResponseBody() const
{
    return (response->getBody());
}

std::string Http::getRequest() const
{
    return (request->toString());
}

std::streamsize Http::getBytes() const
{
    return (bytes);
}
