#include "Request.hpp"

std::string Request::recieveStartLine(std::string& message, char delimiter)
{
    std::string word = message.substr(0, message.find(delimiter));
    startLineSize += word.length() + 1;
    message.erase(0, word.length() + 1);
    return word;
}

void Request::processStartLine()
{
    if (message.find("\r\n") != std::string::npos)
    {
        method = stringToMethod(recieveStartLine(message, ' '));
        target = recieveStartLine(message, ' ');
        version = recieveStartLine(message, '\n') + "\n";
        startLineRead = true;
    }
}

void Request::recieveHeaders(std::string& message)
{
    size_t endOfLine;
    std::string header;
    std::string tmp_key;
    std::string tmp_value;
    std::pair<std::string, std::string> vec_header;
    std::string::size_type pos;
    while (message.compare("\r\n"))
    {
        endOfLine = message.find("\r\n");
        header = message.substr(0, endOfLine);
        pos = header.find(": ");
        if (pos == std::string::npos)
            break ;
        tmp_key = header.substr(0, pos);
        tmp_value = header.substr(pos + 2, header.size());
        vec_header = std::make_pair(tmp_key, tmp_value);
        headers.insert(vec_header);
        message.erase(0, endOfLine + 2);
    }
}

void Request::processHeader()
{
    size_t len = message.find("\r\n\r\n");
    if (len == std::string::npos)
        return ;
    message = message.substr(0, len + 4);
    headerRead = true;
    if (bytesRead < BUFFER_SIZE)
        bodyRead = true;
    recieveHeaders(message);
    len += 4;
    bytesRead = totalBytesRead - startLineSize - len; // записать сколько считали (осталось передать)
    if (bytesRead != 0)
        bodyPresent = true;
}

void Request::processBody()
{
    if (bytesRead < BUFFER_SIZE)
        bodyRead = true;
    //здесь также обработка заголовка в POST
}

void Request::processRequest()
{
    totalBytesRead += bytesRead;
    message.append(buffer, bytesRead);
    if (!startLineRead)
        processStartLine();
    if (!headerRead && startLineRead)
        processHeader();
    if (bodyPresent && !bodyRead && startLineRead && headerRead)
        processBody();
}

Request::Request()
{
    bytesRead = 0;
    totalBytesRead = 0;
    startLineSize = 0;
    startLineRead = false;
    headerRead = false;
    bodyRead = false;
    bodyPresent = false;
}

Request::~Request()
{
}

std::string Request::methodToString(Method method)
{
    switch (method)
    {
        case GET:
            return "GET";
            break;
        case POST:
            return "POST";
            break;
        case DELETE:
            return "DELETE";
            break;
        default:
            return "FAIL";
            break;
    }
    return NULL;
}

Request::Method Request::stringToMethod(std::string method)
{
    if (method == Request::methodToString(GET))
    {
        return GET;
    }
    else if (method == Request::methodToString(POST))
    {
        return POST;
    }
    else if (method == Request::methodToString(DELETE))
    {
        return DELETE;
    }
    return FAIL;
}

std::string Request::toString() //TODO:: DEBUG
{
    std::string ret = getStartLineString();
    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
    {
        ret += it->first + ": " + it->second + "\r\n";
    }
    return ret;
}

std::string Request::getStartLineString()
{
    return (methodToString(method) + " " + target + " " + version);
}

std::string Request::getMethod()
{
	return methodToString(this->method);
}

std::string Request::getURI() const
{
    return this->target;
}

std::string Request::getVersion() const
{
    return this->version;
}

std::map<std::string, std::string> Request::getHeaders() const
{
    return this->headers;
}

std::string Request::getHeaderValue(std::string key)
{
    return (headers.find(key)->second);
}

char *Request::getBuffer()
{
    return this->buffer;
}

void Request::setBytesRead(int bytes)
{
    this->bytesRead = bytes;
}

int Request::getBytesRead() const
{
    return this->bytesRead;
}

bool Request::isRead()
{
    return (headerRead && startLineRead && (!this->bodyPresent || (this->bodyRead && this->bodyPresent))); //TODO: проверить
}

bool Request::isBodyPresent()
{
    return this->bodyPresent;
}

void Request::resetData()
{
    bytesRead = 0;
    totalBytesRead = 0;
    startLineSize = 0;
    startLineRead = false;
    headerRead = false;
    bodyRead = false;
    bodyPresent = false;
}
