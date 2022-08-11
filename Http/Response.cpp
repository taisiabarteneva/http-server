#include "Response.hpp"

Response::Response(Request request)
{
    version = request.getVersion();

}

Response::~Response()
{
}

std::string Response::getHeaderStrings()
{
    std::string ret;
    std::pair<std::string, std::string> j;
    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
    {
        std::string j = it->first;
    }
    // while (!headers.empty())
    // {
    //     ret += headers.front().first + ": " + headers.front().second;
    //     headers.pop_back();
    // }
    return ret;
}

std::string Response::responseToString()
{
    std::string ret;
    ret += version + " ";
    ret += code + " ";
    ret += status + "\n";
    ret += getHeaderStrings();
    ret += body;// TODO: body отдельно отправляется
    return ret;
}
