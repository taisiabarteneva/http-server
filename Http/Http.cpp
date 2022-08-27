#include "Http.hpp"

std::map<int , std::pair<Request*, Response*> > Http::connections;

int Http::send_msg(int conn, const char *buffer, size_t size)
{
    return send(conn, buffer, (int)size, 0);
}
int Http::recv_msg(int conn, char* buffer, size_t size)
{
    return recv(conn, buffer, (int)size, 0);
}

void Http::makeRequest(int fd, Request *request)
{
    request->setBytesRead(recv_msg(fd, request->getBuffer(), BUFFER_SIZE));
    request->processRequest();
    if (request->isBodyPresent())
    {
        // записать на сервак. Учитывай что в этот момент часть тела скорее всего будет считана. Размер bytesRead, буффер buffer.
    }
    //где то здесь идёт запись в файл в том случае, если нужный хедер присутствует и тело есть
}

bool Http::acceptRequest(int fd)
{
    if (connections.find(fd) == connections.end())
        connections[fd] = std::make_pair(new Request, new Response);
    makeRequest(fd, connections[fd].first);
    return connections[fd].first->isRead();
}

bool Http::getResponse(int fd) // принять конфиг
{
    bool done;
    Response* resp = connections[fd].second;
    if (resp->isFirstResponse())
    {
        std::string head = resp->prepareResponse("resources", connections[fd].first);
        send_msg(fd, head.c_str(), head.length());
    }
    else
    {
        char* buffer = resp->getBody();
        int size = resp->getBodySize();
        send_msg(fd, buffer, size);
    }
    done = resp->isRead();
    if (done)
    {
        resp->resetData();
        connections[fd].first->resetData();
        // connections[fd].first->~Request();
        connections.erase(fd);
    }
    return done;
}

Http::Http()
{
}

Http::~Http()
{
}
