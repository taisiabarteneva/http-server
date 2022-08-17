#ifndef REQUEST_HPP
# define REQUEST_HPP
# define ERROR_PAGE_PATH "resources/errors/"

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

    std::string recieveStartLine(std::string& message, char delimiter);
    void recieveHeaders(std::string& message);
    std::string getStartLineString();
public:
    Request(std::string message);
    ~Request();
    Method getMethod() const;
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