#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <map>
# include <string>


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
    const static std::string HTTP_VERSION; //TODO: убрать
    Method method;
    std::string target;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string methodToString(Method method);
    Method stringToMethod(std::string method);
    std::string recieveStartLine(std::string& message, char delimiter);
    void recieveHeaders(std::string& message);
public:
    Request(std::string message);
    ~Request();
    Method const getMethod() const;
    std::string const getURI() const;
    std::string const getVersion() const;
    std::map<std::string, std::string> const getHeaders() const;
    std::string const getBody() const;

    

};

#endif