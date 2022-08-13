#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# define RESPONSE_VERSION "HTTP/1.1"

# include <sstream>
# include "Request.hpp"

enum StartLine {
    VERSION,
    CODE,
    STATUS
};

class Response
{
private:
    int responseCode; //TODO: а нужен?
    std::map<StartLine, std::string> startLine;
    std::map<std::string, std::string> headers;
    char* body;
    std::string fileSize;
    std::string fileType;
    std::ostringstream stream;

    std::string getHeaderStrings();
    void codeStringToInt();
    void initStatusCodes();
    

public:
    std::map<int, std::string> statusCodes;

    Response();
    ~Response();
    std::string responseToString();
    std::string responseHeaderToString();
    std::string responseBodyToString();
    void setVersion(std::string& version);
    void setCode(std::string code);
    void setStatus(std::string &status);
    void setHeader(std::string key, std::string value);
    void setBody(char* body);
    void setFileSize(int size);
    void setFileType(std::string type);
    char* getBody() const;
    std::string getFileSize() const;
    std::string getFileType() const;
};

#endif