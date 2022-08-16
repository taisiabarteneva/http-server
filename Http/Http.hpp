#ifndef HTTP_HPP
# define HTTP_HPP
# define BUFFER_SIZE 2000

# include <map>
# include <string>
# include <iostream>
# include <fstream>
# include "Response.hpp"
# include "Request.hpp"

class Http
{
private:
    Request* request;
    Response* response;
    std::ifstream reader;
    std::streamsize bytes;
    std::string fileName;
    //config file;
public: //TODO: debug. delete
    void recieveDataFromFile();
    void prepareResponse(std::string root);
    void openFile(std::string file);
    void responseGet(std::string root);
    void responsePost(std::string root);
    void responseDelete(std::string root);
    void responseError(std::string code, std::string path);

public:
    char fileBuffer[BUFFER_SIZE];
    Http(std::string request);
    ~Http();
    std::string getResponse() const;
    std::string getRequest() const;
    std::string getResponseHeader() const;
    std::string getResponseBody() const;
    // Http createResponce();
    std::streamsize getBytes() const;
    bool isEndOfFile();
};


#endif
