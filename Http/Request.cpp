#include "Request.hpp"

void Request::recieveHeaders(std::string& message)
{
    size_t endOfLine;
    std::string header;
    std::string tmp_key;
    std::string tmp_value;
    std::pair<std::string, std::string> vec_header;
    std::string::size_type pos;
    while (message.compare("\r\n")) //TODO: здесь может упасть если нет тела
    {
        endOfLine = message.find("\r\n");
        header = message.substr(0, endOfLine);
        pos = header.find(": ");
        if (pos == std::string::npos) //TODO: костыль
            break ;
        tmp_key = header.substr(0, pos);
        tmp_value = header.substr(pos + 2, header.size());
        vec_header = std::make_pair(tmp_key, tmp_value);
        headers.insert(vec_header);
        message.erase(0, endOfLine + 2);
    }
    message.erase(0, 2);
    body = message;
}

std::string Request::recieveStartLine(std::string& message, char delimiter)
{
    std::string word = message.substr(0, message.find(delimiter));
    message.erase(0, word.length() + 1);
    return word;
}

void Request::initRequest(std::string message)
{
    method = stringToMethod(recieveStartLine(message, ' '));
    target = recieveStartLine(message, ' ');
    version = recieveStartLine(message, '\n') + "\n";
    recieveHeaders(message);
}

Request::Request()
{
}

Request::~Request()
{
}

std::string Request::getStartLineString()
{
    return (methodToString(method) + " " + target + " " + version);
}

std::string Request::toString()
{
    std::string ret = getStartLineString();
    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
    {
        ret += it->first + ": " + it->second + "\r\n";
    }
    ret += body;
    return ret;
}

Request::Method Request::getMethod() const
{
	return this->method;
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

std::string Request::getBody() const
{
    return this->body;
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

// const std::string Request::HTTP_VERSION = "HTTP/1.1"; //TODO: убрать 
