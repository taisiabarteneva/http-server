#ifndef     REQUEST_HPP
# define    REQUEST_HPP

# define ERROR_PAGE_PATH "resources/errors/"
# include "Defines.hpp"

# include <map>
# include <cstring>
# include <string>
# include <sys/socket.h>
# include <fstream>
# include "../Parser/Location.hpp"


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
    int headersSize;
    size_t totalBytesRead;
    bool startLineRead;
    bool headerRead;
    bool bodyRead;
    bool bodyPresent;
    Location *location;

    /* POST multipart/form-data */
    std::string multiBuffer;
    // int multiBufferSize;
    bool multiFlag;
    std::string multiBoundary;
    bool multiReading;
    std::string multiFileName;
    int multiBodyPosition;
    bool multiHeaderRead;
    std::string multiHeaderBuf;
    ofstream multiWriter;
    bool multiNewFile;
    bool multiNewBuf;
    bool multiNewRead;

    void processStartLine();
    void processHeader();
    void processBody();
    std::string recieveStartLine(std::string& message, char delimiter);
    void recieveHeaders(std::string& message);
    std::string getStartLineString();
    void    processPost();


    void    multiCheckBoundary(int &pos);
    bool    multiCheckString(std::string& str);
    void    writeInFile(int begin, int end, std::string fileName);
    void    multiGetHeaders(std::string buf, int pos);
    
public:
    void processRequest();
    void setBytesRead(int bytes);
    int getBytesRead() const; //TODO: debug purpose
    char *getBuffer();
    bool isRead();
    bool isBodyPresent();
    void resetData();
    Location *getLocation();
    void    setLocation(Location *location);

    Request();
    ~Request();
    Request(Request &e);
    std::string getMethod();
    std::string getURI() const;
    std::string getVersion() const;
    std::map<std::string, std::string> getHeaders() const;
    std::string getHeaderValue(std::string key);
    std::string getBody() const;
    std::string toString();
    std::string methodToString(Method method);
    Method stringToMethod(std::string method);

    // zaglushka++
};
// std::ofstream &operator=(std::ofstream &e);

#endif