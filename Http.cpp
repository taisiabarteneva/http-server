#include "Http.hpp"

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void Http::recieveStartLine(std::string& request) // TODO: exception/error
{
    std::string::size_type pos = request.find('\r');
    if (pos != std::string::npos && request[pos + 1] == '\n')
        startLine = request.substr(0, pos);
    request.erase(0, pos + 1);
}

void Http::recieveHeaders(std::string& request)
{
    int i = 0;
    std::string header;
    std::string tmp_key;
    std::string tmp_value;
    std::pair<std::string, std::string> map_header;
    std::string::size_type pos;
    // std::string tmp[] = requestsplit('\n');
    // while (hasEnding(request, "\r\n")) {
        header = request.substr(0, request.find("\r\n"));
        pos = header.find(": ");
        tmp_key = header.substr(0, pos);
        tmp_value = header.substr(pos + 2, header.size());
        std::cout << tmp_key << std::endl;
        std::cout << tmp_value << std::endl;
        map_header = std::make_pair(tmp_key, tmp_value);
        headers.insert(map_header);
        request.erase(0, pos + 2);
        // std::cout << request.substr(10);
    // }
}

Http::Http(std::string request)
{
    // std::cout << "Start line:" << std::endl << recieveStartLine(request) << std::endl << std::endl;
    recieveStartLine(request);
    recieveHeaders(request);
    
    // std::cout << request << std::endl;
    
}

Http::~Http()
{
}