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
    char fileBuffer[BUFFER_SIZE];
    std::streamsize bytes;
    //config file;
public: //TODO: debug. delete
    char* recieveFile(std::string fileName);

public:
    Http(std::string request);
    ~Http();
    std::string getResponse() const;
    std::string getRequest() const;
    // Http createResponce();
    std::streamsize getBytes() const;
    bool isEndOfFile();

    
};


#endif
