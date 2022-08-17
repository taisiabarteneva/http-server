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
}

Response::Response()
{
    startLine[VERSION] = RESPONSE_VERSION;
    initStatusCodes();
    initMIMETypes();
    initResponsePages();
}

Response::~Response()
{
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

std::string Response::responseToString()
{
    std::string ret;
    ret += startLine[VERSION] + " ";
    ret += startLine[CODE] + " ";
    ret += startLine[STATUS] + "\r\n";
    ret += getHeaderStrings() + "\r\n";
    ret += body;
    return ret;
}

std::string Response::responseHeaderToString()
{
    std::string ret;
    ret += startLine[VERSION] + " ";
    ret += startLine[CODE] + " ";
    ret += startLine[STATUS] + "\r\n";
    ret += getHeaderStrings() + "\r\n";
    return ret;
}

char* Response::getBody() const
{
    return this->body;
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
void    Response::setBody(char* body)
{
    this->body = body;
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

