#include "Http.hpp"

std::map<int , std::pair<Request*, Response*> > Http::connections;

int Http::send_msg(int conn, const char *buffer, size_t size)
{
    return send(conn, buffer, (int)size, MSG_NOSIGNAL);
}
int Http::recv_msg(int conn, char* buffer, size_t size)
{
    return recv(conn, buffer, (int)size, 0);
}

int Http::makeRequest(int fd, Request *request)
{
    request->setBytesRead(recv_msg(fd, request->getBuffer(), BUFFER_SIZE));
    if (request->getBytesRead() == -1)
        return (-1);
    request->processRequest();
    return (0);
}

int Http::acceptRequest(int fd, Server * serv)
{
    if (connections.find(fd) == connections.end())
        connections[fd] = std::make_pair(new Request, new Response);
    if (makeRequest(fd, connections[fd].first) == -1)
        return (-1);
    bool ret = connections[fd].first->isRead();
    return ret ? 1 : 0;

}

int Http::getResponse(int fd, Server * serv)
{
    bool done;
    Response* resp = connections[fd].second;
    if (resp->isFirstResponse())
    {
        std::string head = resp->prepareResponse(serv->getLocations(), connections[fd].first);
        if (send_msg(fd, head.c_str(), head.length()) == -1)
            return -1;
    }
    else
    {
        char* buffer = resp->getBody();
        int size = resp->getBodySize();
        if (send_msg(fd, buffer, size) == -1)
            return -1;
    }
    done = resp->isRead();
    if (done)
    {
        resp->resetData();
        connections[fd].first->resetData();
        connections.erase(fd);
    }
    return done ? 1 : 0;
}

Http::Http()
{
}

Http::~Http()
{
}
