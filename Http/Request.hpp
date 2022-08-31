#ifndef     REQUEST_HPP
# define    REQUEST_HPP

# define ERROR_PAGE_PATH "resources/errors/"
# include "Defines.hpp"

# include <map>
# include <cstring>
# include <string>
# include <sys/socket.h>


class Request
{
private:
    enum Method
    {
        GET,
        POST,
        DELETE,
        FAIL
    };
    Method      method;
    std::string target;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string message;
    char buffer[BUFFER_SIZE];
    int bytesRead;
    int startLineSize;
    size_t totalBytesRead;
    bool startLineRead;
    bool headerRead;
    bool bodyRead;
    bool bodyPresent;

    void processStartLine();
    void processHeader();
    void processBody();
    std::string recieveStartLine(std::string& message, char delimiter);
    void recieveHeaders(std::string& message);
    std::string getStartLineString();
    
public:
    void processRequest();
    void setBytesRead(int bytes);
    int getBytesRead() const; //TODO: debug purpose
    char *getBuffer();
    bool isRead();
    bool isBodyPresent();
    void resetData();

    Request();
    ~Request();
    std::string getMethod();
    std::string getURI() const;
    std::string getVersion() const;
    std::map<std::string, std::string> getHeaders() const;
    std::string getHeaderValue(std::string key);
    std::string getBody() const;
    std::string toString();
    std::string methodToString(Method method);
    Method stringToMethod(std::string method);
};

#endif