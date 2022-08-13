#include "Response.hpp"

void Response::initStatusCodes()
{
    statusCodes[100] = "Continue";
    statusCodes[101] = "Switching Protocol";
    statusCodes[102] = "Processing";
    statusCodes[103] = "Early Hints";
    statusCodes[200] = "OK";
    statusCodes[201] = "Created";
    statusCodes[202] = "Accepted";
    statusCodes[203] = "Non-Authoritative Information";
    statusCodes[204] = "No Content";
    statusCodes[205] = "Reset Content";
    statusCodes[206] = "Partial Content";
    statusCodes[300] = "Multiple Choice";
    statusCodes[301] = "Moved Permanently";
    statusCodes[302] = "Found";
    statusCodes[303] = "See Other";
    statusCodes[304] = "Not Modified";
    statusCodes[305] = "Use Proxy";
    statusCodes[306] = "Switch Proxy";
    statusCodes[307] = "Temporary Redirect";
    statusCodes[308] = "Permanent Redirect";
    statusCodes[400] = "Bad Request";
    statusCodes[401] = "Unauthorized";
    statusCodes[402] = "Payment Required";
    statusCodes[403] = "Forbidden";
    statusCodes[404] = "Not Found";
    statusCodes[405] = "Method Not Allowed";
    statusCodes[406] = "Not Acceptable";
    statusCodes[407] = "Proxy Authentication Required";
    statusCodes[408] = "Request Timeout";
    statusCodes[409] = "Conflict";
    statusCodes[410] = "Gone";
    statusCodes[411] = "Length Required";
    statusCodes[412] = "Precondition Failed";
    statusCodes[413] = "Request Entity Too Large";
    statusCodes[414] = "Request-URI Too Long";
    statusCodes[415] = "Unsupported Media Type";
    statusCodes[416] = "Requested Range Not Satisfiable";
    statusCodes[417] = "Expectation Failed";
    statusCodes[500] = "Internal Server Error";
    statusCodes[501] = "Not Implemented";
    statusCodes[502] = "Bad Gateway";
    statusCodes[503] = "Service Unavailable";
    statusCodes[504] = "Gateway Timeout";
    statusCodes[505] = "HTTP Version Not Supported";
}

Response::Response()
{
    startLine[VERSION] = RESPONSE_VERSION;
    initStatusCodes();
}

Response::~Response()
{
}


std::string Response::getHeaderStrings()
{
    std::string ret;
    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
    {
        ret += it->first + ": " + it->second + "\r\n";
    }
    return ret;
}

std::string Response::responseToString()
{
    std::string ret;
    ret += startLine[VERSION] + " ";
    ret += startLine[CODE] + " ";
    ret += startLine[STATUS] + "\r\n";
    ret += getHeaderStrings() + "\r\n";
    ret += body;// TODO: body отдельно отправляется
    return ret;
}

std::string Response::responseHeaderToString()
{
    std::string ret;
    ret += startLine[VERSION] + " ";
    ret += startLine[CODE] + " ";
    ret += startLine[STATUS] + "\r\n";
    ret += getHeaderStrings() + "\r\n";
    return ret;
}

char* Response::getBody() const
{
    return this->body;
}

void    Response::setVersion(std::string& version)
{
    this->startLine[VERSION] = version;
}
void    Response::setCode(std::string code)
{
    this->startLine[CODE] = code;
}
void    Response::setStatus(std::string &status)
{
    this->startLine[STATUS] = status;
}
void    Response::setHeader(std::string key, std::string value)
{
    this->headers.insert(std::make_pair(key, value));
}
void    Response::setBody(char* body)
{
    this->body = body;
}

void    Response::setFileSize(int size) //TODO:: а что с большим файлом?
{
    // TODO:: если файл большой, готовим заголовок Transfer-Encoding: chunked
    stream << size;
    fileSize = stream.str();
    stream.str("");
    stream.clear();
}

void    Response::setFileType(std::string type)
{
    this->fileType = type;
}

std::string Response::getFileSize() const
{
    return fileSize;
}

std::string Response::getFileType() const
{
    // TODO: прогнать типы и определить
    std::string fullFileType = "image/" + fileType;
    return fullFileType;
}

