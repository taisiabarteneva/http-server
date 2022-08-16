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

void    Http::openFile(std::string file)
{
    reader.clear();
    reader.open(file, std::ios::in | std::ios::binary | std::ios::ate);
    if (reader.fail())
    {
        std::cerr << "Open file failure" << std::endl;
        return ; 
    }
    response->setFileSize(reader.tellg()); //TODO:: а что с большим файлом?
    reader.seekg(0);
    response->setFileType(file.substr(file.find(".") + 1));
    reader.clear();
}

void Http::recieveDataFromFile()
{
    reader.read(fileBuffer, BUFFER_SIZE);
    if (reader.bad())
    {
        std::cerr << "File reading fail" << std::endl; // TODO:??
    }
    bytes = reader.gcount();
}

void    Http::responseError(std::string code, std::string path)
{
    response->setCode(code);
    response->setStatus(response->statusCodes[atoi(code.c_str())]);
    response->setHeader("Connection", "keep-alive");
    openFile(path);
    if (reader.fail())
    {
        openFile(response->getErrorPage(code));
    }
}

void    Http::responseGet(std::string root)
{
    fileName = root + request->getURI(); //TODO: filename from GET
    openFile(fileName);
    if (reader.fail())
    {
        std::cerr << "Bad file" << std::endl;
        responseError("404", "");
    }
    else
    {
        response->setCode("200");
        response->setStatus(response->statusCodes[200]);
    }

    response->setHeader("Content-Type", response->getMIME()); // TODO: подготовить файл
    response->setHeader("Content-Length", response->getFileSize());
    response->setHeader("Connection", "close");
    response->setHeader("Accept-Ranges", "bytes");
    response->setBody(fileBuffer);
}

void    Http::responsePost(std::string root)
{

}

void    Http::responseDelete(std::string root)
{

}

void    Http::prepareResponse(std::string root)
{
    //TODO: проверка файла
    if (request->getMethod() == request->stringToMethod("GET"))
    {
        std::cout << "GETGETGET" << std::endl;
        responseGet(root);
    }
    else if (request->getMethod() == request->stringToMethod("POST"))
        responsePost(root);
    else if (request->getMethod() == request->stringToMethod("DELETE"))
        responseDelete(root);
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
