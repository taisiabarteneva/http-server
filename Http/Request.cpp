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
    // std::cout << getBuffer() << std::endl; //TODO: debug
}

void Request::processHeader()
{
    size_t len = message.find("\r\n\r\n");
    size_t bytesLeft;
    if (len == std::string::npos)
        return ;
    message = message.substr(0, len + 4);
    headerRead = true;
    if (bytesRead < BUFFER_SIZE)
        bodyRead = true;
    recieveHeaders(message);
    len += 4;
    bytesLeft = totalBytesRead - startLineSize - len; // записать сколько считали (осталось передать)
    if (bytesLeft != 0)
        bodyPresent = true;
}

void Request::processBody()
{
    if (bytesRead < BUFFER_SIZE)
        bodyRead = true;
}

void    Request::processPost()
{
    std::string content = getHeaderValue("Content-Type");
    if (content.substr(0, content.find(';')) == "multipart/form-data")
    {
        multiBoundary = content.substr(content.find(' ') + 1, content.length());
        multiBoundary.erase(0, multiBoundary.find_first_not_of('-', multiBoundary.find('=') + 1));
        // std::cout << "BOUNDARY: " << multiBoundary << std::endl;
        for (int i = 0; i < bytesRead; i++)
        {
            std::cout << buffer[i];
            if (buffer[i] == '-')
                multiCheckBoundary(i);
        }
        // std::cout << buffer << std::endl;
    }
}

bool    Request::multiCheckString(std::string& str)
{
    if (str.substr(str.find_first_not_of('-'), str.find("\r\n") - str.find_first_not_of('-')) == multiBoundary)
    {
        if (multiFlag == false)
        {
            multiFlag = true;
            return false;
        }
        // if (multiWriter.is_open())
        //     multiWriter.close();// TODO: segfault
        std::cout << "WEBKIT" << std::endl;;
        return true;
    }
    return false;
}

void    Request::writeInFile(int pos, std::string fileName)
{
    if (!multiWriter.is_open())
    {
        multiWriter.open("resources/files/multiTest", std::ofstream::out | std::ofstream::binary | std::ofstream::app);
    }
    multiWriter.write(&buffer[pos], BUFFER_SIZE - pos);
}

void    Request::multiCheckBoundary(int &pos)
{
    // std::cout << pos << std::endl;
    while (buffer[pos] == '-')
        pos++;
    if (!multiBuffer.empty())
    {
        std::string buf = &buffer[multiBoundary.length() - multiBuffer.length()];
        buf = multiBuffer + buf;
        if (multiCheckString(buf))
        {
            int position = buf.find("\r\n\r\n") + 4;
            if (position == std::string::npos)
                return ;
            // std::string fileName = buf.substr(buf.find("filename=") + 10, buf.find("\""));
            std::string fileName = "Hello";
            // std::cout << "FILE NAME: " << fileName << std::endl;
            //спарсить заголовок;
            pos += position;
            writeInFile(pos, fileName);
        }
    }
    else if (pos + multiBoundary.length() <= BUFFER_SIZE)
    {
        std::string buf = &buffer[pos];
        // std::cout << buf << std::endl;
        if (multiCheckString(buf))
        {
            int position = buf.find("\r\n\r\n") + 4;
            if (position == std::string::npos)
                return ;
            int tmpPos = buf.find("filename=");
            buf.erase(tmpPos);
            std::string fileName;
            if (tmpPos != std::string::npos)
                fileName = "Hello";
                // fileName = buf.substr(tmpPos + 10, buf.find("\"") - tmpPos + 10);
            else
                fileName = "tmp";
            std::cout << "FILE NAME: " << fileName << std::endl;
            //спарсить заголовок;
            pos += position;
            writeInFile(pos, fileName);//TODO write in file
        }

    }
    else
    {
        multiBuffer = std::string(&buffer[pos], BUFFER_SIZE - bytesRead);
    }
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
    if (method == POST && bodyPresent)
        processPost();
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
    multiFlag = false;
    multiReading = false;
    location = NULL;
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
    ret += buffer;
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

void Request::setLocation(Location* location)
{
    this->location = location;
}

Location *Request::getLocation()
{
    return location;
}
