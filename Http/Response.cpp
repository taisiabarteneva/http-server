#include "Response.hpp"

void Response::initStatusCodes()
{
    statusCodes[100] = "Continue";
    statusCodes[101] = "Switching Protocol";
    statusCodes[102] = "Processing";
    statusCodes[103] = "Early Hints";
    statusCodes[200] = "OK";
    statusCodes[201] = "Created";
    statusCodes[202] = "Accepted";
    statusCodes[203] = "Non-Authoritative Information";
    statusCodes[204] = "No Content";
    statusCodes[205] = "Reset Content";
    statusCodes[206] = "Partial Content";
    statusCodes[300] = "Multiple Choice";
    statusCodes[301] = "Moved Permanently";
    statusCodes[302] = "Found";
    statusCodes[303] = "See Other";
    statusCodes[304] = "Not Modified";
    statusCodes[305] = "Use Proxy";
    statusCodes[306] = "Switch Proxy";
    statusCodes[307] = "Temporary Redirect";
    statusCodes[308] = "Permanent Redirect";
    statusCodes[400] = "Bad Request";
    statusCodes[401] = "Unauthorized";
    statusCodes[402] = "Payment Required";
    statusCodes[403] = "Forbidden";
    statusCodes[404] = "Not Found";
    statusCodes[405] = "Method Not Allowed";
    statusCodes[406] = "Not Acceptable";
    statusCodes[407] = "Proxy Authentication Required";
    statusCodes[408] = "Request Timeout";
    statusCodes[409] = "Conflict";
    statusCodes[410] = "Gone";
    statusCodes[411] = "Length Required";
    statusCodes[412] = "Precondition Failed";
    statusCodes[413] = "Request Entity Too Large";
    statusCodes[414] = "Request-URI Too Long";
    statusCodes[415] = "Unsupported Media Type";
    statusCodes[416] = "Requested Range Not Satisfiable";
    statusCodes[417] = "Expectation Failed";
    statusCodes[500] = "Internal Server Error";
    statusCodes[501] = "Not Implemented";
    statusCodes[502] = "Bad Gateway";
    statusCodes[503] = "Service Unavailable";
    statusCodes[504] = "Gateway Timeout";
    statusCodes[505] = "HTTP Version Not Supported";
}

void Response::initMIMETypes()
{
    mimeTypes["html"] = "text/html; charset=utf-8";
    mimeTypes["htm"] = "text/html; charset=utf-8";
    mimeTypes["shtml"] = "text/html; charset=utf-8";
    mimeTypes["css"] = "text/css";
    mimeTypes["xml"] = "text/xml";
    mimeTypes["gif"] = "image/gif";
    mimeTypes["jpeg"] = "image/jpeg";
    mimeTypes["jpg"] = "image/jpeg";
    mimeTypes["js"] = "application/javascript";
    mimeTypes["atom"] = "application/atom+xml";
    mimeTypes["rss"] = "application/rss+xml";

    mimeTypes["mml"] = "text/mathml";
    mimeTypes["txt"] = "text/plain; charset=utf-8";
    mimeTypes["jad"] = "text/vnd.sun.j2me.app-descriptor";
    mimeTypes["wml"] = "text/vnd.wap.wml";
    mimeTypes["htc"] = "text/x-component";

    mimeTypes["avif"] = "image/avif";
    mimeTypes["png"] = "image/png";
    mimeTypes["svg"] = "image/svg+xml";
    mimeTypes["svgz"] = "image/svg+xml";
    mimeTypes["tif"] = "image/tiff";
    mimeTypes["tiff"] = "image/tiff";
    mimeTypes["wbmp"] = "image/vnd.wap.wbmp";
    mimeTypes["webp"] = "image/webp";
    mimeTypes["ico"] = "image/x-icon";
    mimeTypes["jng"] = "image/x-jng";
    mimeTypes["bmp"] = "image/x-ms-bmp";

    mimeTypes["woff"] = "font/woff";
    mimeTypes["woff2"] = "font/woff2";

    mimeTypes["jar"] = "application/java-archive";
    mimeTypes["war"] = "application/java-archive";
    mimeTypes["ear"] = "application/java-archive";
    mimeTypes["json"] = "application/json";
    mimeTypes["hqx"] = "application/mac-binhex40";
    mimeTypes["doc"] = "application/msword";
    mimeTypes["pdf"] = "application/pdf";
    mimeTypes["ps"] = "application/postscript";
    mimeTypes["eps"] = "application/postscript";
    mimeTypes["ai"] = "application/postscript";
    mimeTypes["rtf"] = "application/rtf";
    mimeTypes["m3u8"] = "application/vnd.apple.mpegurl";
    mimeTypes["kml"] = "application/vnd.google-earth.kml+xml";
    mimeTypes["kmz"] = "application/vnd.google-earth.kmz";
    mimeTypes["xls"] = "application/vnd.ms-excel";
    mimeTypes["eot"] = "application/vnd.ms-fontobject";
    mimeTypes["ppt"] = "application/vnd.ms-powerpoint";
    mimeTypes["odg"] = "application/vnd.oasis.opendocument.graphics";
    mimeTypes["odp"] = "application/vnd.oasis.opendocument.presentation";
    mimeTypes["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    mimeTypes["odt"] = "application/vnd.oasis.opendocument.text";
    mimeTypes["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypes["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypes["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes["wmlc"] = "application/vnd.wap.wmlc";
    mimeTypes["wasm"] = "application/wasm";
    mimeTypes["7z"] = "application/x-7z-compressed";
    mimeTypes["cco"] = "application/x-cocoa";
    mimeTypes["jardiff"] = "application/x-java-archive-diff";
    mimeTypes["jnlp"] = "application/x-java-jnlp-file";
    mimeTypes["run"] = "application/x-makeself";
    mimeTypes["pl"] = "application/x-perl";
    mimeTypes["pm"] = "application/x-perl";
    mimeTypes["prc"] = "application/x-pilot";
    mimeTypes["pdb"] = "application/x-pilot";
    mimeTypes["rar"] = "application/x-rar-compressed";
    mimeTypes["rpm"] = "application/x-redhat-package-manager";
    mimeTypes["sea"] = "application/x-sea";
    mimeTypes["swf"] = "application/x-shockwave-flash";
    mimeTypes["sit"] = "application/x-stuffit";
    mimeTypes["tcl"] = "application/x-tcl";
    mimeTypes["tk"] = "application/x-tcl";
    mimeTypes["der"] = "application/x-x509-ca-cert";
    mimeTypes["pem"] = "application/x-x509-ca-cert";
    mimeTypes["crt"] = "application/x-x509-ca-cert";
    mimeTypes["xpi"] = "application/x-xpinstall";
    mimeTypes["xhtml"] = "application/xhtml+xml";
    mimeTypes["xspf"] = "application/xspf+xml";
    mimeTypes["zip"] = "application/zip";

    mimeTypes["bin"] = "application/octet-stream";
    mimeTypes["exe"] = "application/octet-stream";
    mimeTypes["dll"] = "application/octet-stream";
    mimeTypes["deb"] = "application/octet-stream";
    mimeTypes["dmg"] = "application/octet-stream";
    mimeTypes["iso"] = "application/octet-stream";
    mimeTypes["img"] = "application/octet-stream";
    mimeTypes["msi"] = "application/octet-stream";
    mimeTypes["msp"] = "application/octet-stream";
    mimeTypes["msm"] = "application/octet-stream";

    mimeTypes["mid"] = "audio/midi";
    mimeTypes["midi"] = "audio/midi";
    mimeTypes["kar"] = "audio/midi";
    mimeTypes["mp3"] = "audio/mpeg";
    mimeTypes["ogg"] = "audio/ogg";
    mimeTypes["m4a"] = "audio/x-m4a";
    mimeTypes["ra"] = "audio/x-realaudio";

    mimeTypes["3gpp"] = "video/3gpp";
    mimeTypes["3gp"] = "video/3gpp";
    mimeTypes["ts"] = "video/mp2t";
    mimeTypes["mp4"] = "video/mp4";
    mimeTypes["mpeg"] = "video/mpeg";
    mimeTypes["mpg"] = "video/mpeg";
    mimeTypes["mov"] = "video/quicktime";
    mimeTypes["webm"] = "video/webm";
    mimeTypes["flv"] = "video/x-flv";
    mimeTypes["m4v"] = "video/x-m4v";
    mimeTypes["mng"] = "video/x-mng";
    mimeTypes["asx"] = "video/x-ms-asf";
    mimeTypes["asf"] = "video/x-ms-asf";
    mimeTypes["wmv"] = "video/x-ms-wmv";
    mimeTypes["avi"] = "video/x-msvideo";
}

void Response::initResponsePages()
{
    errors["403"] = "resources/errors/403.html";
    errors["404"] = "resources/errors/404.html";
    errors["405"] = "resources/errors/405.html";
    errors["413"] = "resources/errors/413.html";
    errors["500"] = "resources/errors/500.html";
}

Response::Response()
{
    firstResponse = false;
    startLine[VERSION] = RESPONSE_VERSION;
    initStatusCodes();
    initMIMETypes();
    initResponsePages();
    bytes = 0;
    bytesRead = 0;
}

Response::~Response()
{
    if (reader.is_open())
        reader.close();
}

std::string Response::prepareResponse(std::vector<Location> locations, Request* request)
{
    this->request = request;
    Location *location = getLocation(locations);
    if (BUFFER_SIZE < 2000)
        responseError("500", getErrorPage("500"));
    else
    {
        if (!location->getRedirection().empty())
            responseRedirect(location);
        else if (request->getMethod() == "GET")
            responseGet(location);
        else if (request->getMethod() == "POST")
            responsePost(location);
        else if (request->getMethod() == "DELETE")
            responseDelete(location);
        else
        {
            responseError("405", getErrorPage("405"));
            setHeader("Content-Type", getMIME());
            setHeader("Content-Length", getFileSize());
            setHeader("Connection", "close");
        }
    }
    return (getHeaders());
}

Location    *Response::getLocation(std::vector<Location> &locations)
{
    int pos;
    int start;
    std::string currentLocationPath;
    std::string path = request->getURI();
    Location* ret;
    std::string comp1;
    std::string comp2;
    int compability;
    int maxCompability = 0;

    if (path.back() != '/')
        path += '/';
    for (std::vector<Location>::iterator it = locations.begin(); it != locations.end(); it++)
    {
        currentLocationPath = it->getPath();
        if (currentLocationPath.back() != '/')
            currentLocationPath += '/';
        start = currentLocationPath.find('/');
        start++;
        pos = 0;
        compability = 0;
        while (pos != std::string::npos)
        {
            pos = currentLocationPath.find('/', start);
            if (pos == std::string::npos)
            {
                if (maxCompability == 0 && !currentLocationPath.compare("/"))
                    ret = &(*it);
                break;
            }
            comp1 = currentLocationPath.substr(start, pos - start);
            comp2 = path.substr(start, pos - start);
            if (comp1.compare(comp2) == 0)
                compability++;
            else
            {
                compability = 0;
                break;
            }
            start = pos + 1;
        }
        if (maxCompability < compability)
        {
            maxCompability  = compability;
            ret = &(*it);
        }
    }
    // ret->printLocationInfo();
    fileName = getFileName(ret);
    checkOtherPreferences(ret);
    return ret;
}

std::string Response::getFileName(Location *location)
{
    std::string filePath;
    std::string fileURI;

    fileURI = request->getURI();
    if (location == NULL)
        return "resources/index.html";
    filePath = location->getRoot();
    if (filePath.empty())
        filePath = "resources/";
    else if (filePath.back() != '/')
        filePath += '/';
    fileURI.erase(0, location->getPath().length());
    if (fileURI.empty())
    {
        fileURI = location->getIndex();
        if (fileURI.back() == '/')
            fileURI = fileURI.substr(0, fileURI.size() - 1);
        if (fileURI.empty())
            fileURI = "index.html";
    }
    return (filePath + fileURI);

}

void    Response::checkOtherPreferences(Location *location)
{
    if (location != NULL)
    location->getAllowMethods();
    if (location->getAutoindex().compare("on"))
        autoIndexOn = true;
    else
        autoIndexOn = false;
    // std::cout << "AUTOINDEX: " << location->getAutoindex() << std::endl;
    // for (std::string i : location->getErrors())
    // {
    //     i = location->getRoot() + i;
    //     std::cout << i << std::endl;
    // }
    // location->printLocationInfo();
    // map<string, string> i = location->getErrors(); // segfault
    // // std::cout << "SIZE: " << i.size() << std::endl;
    //     std::cout << "ERRORS GOT" << std::endl;
    // if (i.size() != 0)
    // {
    // std::map<std::string, std::string>::iterator it = location->getErrors().begin();
    //     std::cout << "ERRORS GOT" << std::endl;
    // std::map<std::string, std::string>::iterator it1 = location->getErrors().end();
    //     std::cout << "ERRORS GOT" << std::endl;
    //     errors.insert(location->getErrors().begin(), location->getErrors().end());
    // }
    // else
    //     std::cout << "Kek" << std::endl;
}

void    Response::responseRedirect(Location *location)
{
    setCode("307");
    std::cout << location->getRedirection() << std::endl;; 
    setHeader("Location", location->getRedirection());
}

void    Response::responseGet(Location* location)
{
    vector<string> methods = location->getAllowMethods();
    if (std::find(methods.begin(), methods.end(), "GET") == methods.end())
        responseError("405", getErrorPage("405"));
    else
    {
        openFile(fileName);
        if (reader.fail())
        {
            // if (autoIndexOn)
            //     checkFolder(); //TODO: autoindex
            if (!access(fileName.c_str(), F_OK))
            {
                std::cerr << "Permission denied" << std::endl;
                responseError("403", getErrorPage("403"));
            }
            else
            {
                std::cerr << "File not found" << std::endl;
                responseError("404", getErrorPage("404"));
            }
        }
        else
        {
            setCode("200");
            setStatus(statusCodes[200]);
        }
    }
    setHeader("Content-Type", getMIME()); // TODO: подготовить файл
    setHeader("Content-Length", getFileSize());
    // setHeader("Transfer-Encoding", "chunked");//TODO
    setHeader("Connection", "keep-alive"); //TODO: ???
    setHeader("Accept-Ranges", "bytes");
}

void    Response::responsePost(Location * location)
{
    vector<string> methods = location->getAllowMethods();
    if (std::find(methods.begin(), methods.end(), "POST") == methods.end())
        responseError("405", getErrorPage("405"));
    else
    {

        std::string postContentType;
        //TODO: запихнуть в отдельный метод поиска в response; или нет
        postContentType = request->getHeaderValue("Content-Type");
        std::cout << "-----------------THIS IS CONTENT TYPE-----------" << std::endl;
        if (!postContentType.compare("application/x-www-form-urlencoded"))// TODO: проверить скрипт или нет
        {
            CGI cgi(request, location); // TODO: перенести в runCGI
            cgi.start(); // TODO: перенести в runCGI
            std::cout << postContentType << std::endl << std::endl;
            openFile("resources/cgi.serv");
            if (reader.fail())
            {
                if (!access(fileName.c_str(), F_OK))
                {
                    std::cerr << "Permission denied" << std::endl;
                    responseError("403", getErrorPage("403"));
                }
                else
                {
                    std::cerr << "File not found" << std::endl;
                    responseError("404", getErrorPage("404"));
                }
            }
            else
            {
                setCode("200");
                setStatus(statusCodes[200]);
            }
            //if checkCGI()
            //  runCGI(); //TODO: здесь CGI
            //else 
            // {
            // responseGet(location);
            //     return;
            // }
            // std::cout << request->toString() << std::endl; //debug 
            // std::cout << postContentType << std::endl << std::endl;
        }
        else if (postContentType.substr(0, 19) == "multipart/form-data")
        {
            std::cout << postContentType << std::endl << std::endl;
            openFile("resources/success.html");
            if (reader.fail())
            {
                if (!access(fileName.c_str(), F_OK))
                {
                    std::cerr << "Permission denied" << std::endl;
                    responseError("403", getErrorPage("403"));
                }
                else
                {
                    std::cerr << "File not found" << std::endl;
                    responseError("404", getErrorPage("404"));
                }
            }
            else
            {
                setCode("200");
                setStatus(statusCodes[200]);
            }
        }
        setHeader("Content-Type", getMIME());
        setHeader("Content-Length", getFileSize());
        setHeader("Connection", "close");
    }
}

void    Response::responseDelete(Location * location)
{
    vector<string> methods = location->getAllowMethods();
    if (std::find(methods.begin(), methods.end(), "DELETE") == methods.end())
        responseError("405", getErrorPage("405"));
     else
    {
        openFile(fileName);
        if (reader.fail())
        {
            if (!access(fileName.c_str(), F_OK))
            {
                std::cerr << "Permission denied" << std::endl;
                responseError("403", getErrorPage("403"));
            }
            else
            {
                std::cerr << "File not found" << std::endl;
                responseError("404", getErrorPage("404"));
            }
        }
        else
        {
            std::remove(fileName.data());
            setCode("204");
            setStatus(statusCodes[204]);
        }
    }
}

void    Response::responseError(std::string code, std::string path)
{
    setCode(code);
    setStatus(statusCodes[atoi(code.c_str())]);
    setHeader("Connection", "keep-alive"); //TODO: ???
    openFile(path);
    if (reader.fail())
    {
        openFile(getErrorPage(code));
    }
}

void Response::recieveDataFromFile()
{
    reader.read(body, BUFFER_SIZE);
    if (reader.bad())
    {
        std::cerr << "File reading fail" << std::endl; // TODO:??
    }
    bytes = reader.gcount();
}


void    Response::openFile(std::string file)
{
    reader.clear();
    reader.open(file, std::ios::in | std::ios::binary | std::ios::ate);
    if (reader.fail())
    {
        std::cout << "Filename is : " << file << std::endl;
        std::cerr << "Open file failure" << std::endl;
        return ; 
    }
    setFileSize(reader.tellg()); //TODO:: а что с большим файлом?
    reader.seekg(0);
    setFileType(file.substr(file.find(".") + 1));
    reader.clear();
}

bool Response::isFirstResponse()
{
    if (!firstResponse)
    {
        firstResponse = true;
        return true;
    }
    return false;
}

std::string Response::getHeaders()
{
    std::string ret;
    ret += startLine[VERSION] + " ";
    ret += startLine[CODE] + " ";
    ret += startLine[STATUS] + "\r\n";
    ret += getHeaderStrings() + "\r\n";
    
    return ret;
}

char* Response::getBody()
{
    recieveDataFromFile();
    return this->body;
}

int Response::getBodySize()
{
    return this->bytes;
}

bool Response::isRead()
{
    if (reader.eof())
        return true;
    return false;
}

void    Response::resetData()
{
    reader.close();
    bytes = 0;
    bytesRead = 0;
    request = NULL;
    firstResponse = false;
}

std::string Response::getHeaderStrings()
{
    std::string ret;
    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
    {
        ret += it->first + ": " + it->second + "\r\n";
    }
    return ret;
}

void    Response::setVersion(std::string& version)
{
    this->startLine[VERSION] = version;
}
void    Response::setCode(std::string code)
{
    this->startLine[CODE] = code;
}
void    Response::setStatus(std::string &status)
{
    this->startLine[STATUS] = status;
}
void    Response::setHeader(std::string key, std::string value)
{
    this->headers.insert(std::make_pair(key, value));
}

void    Response::setFileSize(int size) //TODO:: а что с большим файлом?
{
    // TODO:: если файл большой, готовим заголовок Transfer-Encoding: chunked
    stream << size;
    fileSize = stream.str();
    stream.str("");
    stream.clear();
}

void    Response::setFileType(std::string type)
{
    this->fileType = type;
}

std::string Response::getErrorPage(std::string code)
{
    return errors[code];
}

std::string Response::getFileSize() const
{
    return fileSize;
}

std::string Response::getHeaderValue(std::string key)
{
    return (headers.find(key)->second);
}

std::string Response::getMIME() const
{
    std::string key = fileType;
    std::string mime;
    for (std::map<std::string, std::string>::const_iterator it = mimeTypes.begin(); it != mimeTypes.end(); it++)
    {
        if (fileType == it->first)
        {
            mime = it->second;
        }
    }
    return mime;
}
