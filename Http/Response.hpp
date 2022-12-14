#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# define RESPONSE_VERSION "HTTP/1.1"
# include "Defines.hpp"
# define HEADERS_SIZE 16384

# include <sstream>
# include <cstring>
# include <iostream>
# include <unistd.h>
# include <fstream>
# include <vector>
#include <algorithm>
# include <dirent.h>
# include <sys/stat.h>
# include "../Server/Server.hpp"
# include "../Cgi/Cgi.hpp"
# include "Request.hpp"

enum StartLine {
    VERSION,
    CODE,
    STATUS
};

class Response
{
private:
    std::ifstream reader;
    std::streamsize bytes;
    Request* request;
    bool firstResponse;
    size_t bytesRead;
    char body[BUFFER_SIZE];
    std::map<StartLine, std::string> startLine;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> mimeTypes;
    std::map<std::string, std::string> errors;
    std::string fileSize;
    std::string fileType;
    std::ostringstream stream;
    bool autoIndexOn;
    std::string fileName;
    bool autoFilePresent;


    void        responseGet(Location* location);
    void        responsePost(Location *location);
    void        responseDelete(Location *location);
    void        responseError(std::string code, std::string path);
    void        responseRedirect(Location *location);
    void        openFile(std::string file);
    void        recieveDataFromFile();
    std::string getHeaders(); //Debug and other
    void        initStatusCodes();
    void        initMIMETypes();
    void        initResponsePages();
    void        getFolders(Location* location);

    Location    *getLocation(std::vector<Location> &locations);
    std::string getFileName(Location *location);
    void        checkOtherPreferences(Location *location);

    void setVersion(std::string& version);
    void setCode(std::string code);
    void setStatus(std::string &status);
    void setHeader(std::string key, std::string value);
    void setFileSize(int size);
    void setFileType(std::string type);
    std::string getHeaderValue(std::string key);
    std::string getErrorPage(std::string code);
    std::string getFileSize() const;
    std::string getMIME() const;

public:
    std::map<int, std::string> statusCodes;
    Response();
    ~Response();
    std::string prepareResponse(std::vector<Location>, Request* request);
    void        resetData();

    bool        isFirstResponse();
    bool        isRead();
    char        *getBody();
    int         getBodySize();
    int         getResponseSize();
    size_t      getBytesRead();
    std::string getHeaderStrings();
};

#endif