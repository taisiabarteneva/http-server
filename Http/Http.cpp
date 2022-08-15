#include "Http.hpp"

Http::Http(std::string message/*, std::string(or struct) source*/)
{
    request = new Request(message);
    response = new Response();
    bytes = BUFFER_SIZE;
    prepareResponse("resources"); /* source*/
}

Http::~Http()
{
    if (reader.is_open())
        reader.close();
    delete response;
    delete request;
}

void    Http::openFile()
{
    reader.clear();
    reader.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!reader.good())
    {
        std::cerr << "Bad file" << std::endl; //TODO: debug
    }
    response->setFileSize(reader.tellg()); //TODO:: а что с большим файлом?
    reader.seekg(0);
    response->setFileType(fileName.substr(fileName.find(".") + 1));
    reader.clear();
}

void Http::recieveDataFromFile()
{
    reader.read(fileBuffer, BUFFER_SIZE);
    if (reader.fail() || reader.bad())
    {
        std::cerr << "File reading fail" << std::endl; // TODO:??
    }
    bytes = reader.gcount();
}

void    Http::prepareResponse(std::string root)
{
    //TODO: проверка файла
    response->setCode("200");
    response->setStatus(response->statusCodes[200]);
    fileName = root + request->getURI(); //TODO: filename from GET
    std::cout << fileName << std::endl;
    openFile(); //if body present
    response->setHeader("Content-Type", response->getMIME()); // TODO: подготовить файл
    std::cout << getResponseHeader() << std::endl;
    response->setHeader("Content-Length", response->getFileSize());
    response->setBody(fileBuffer);
}

bool Http::isEndOfFile()
{
    if (reader.eof())
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
