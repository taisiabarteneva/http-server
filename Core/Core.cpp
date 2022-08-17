#include "Core.hpp"
#include "../Parser/config_file.hpp"

// Core::Core(std::string & ip_port, vector<Location> locations) 
// {
//     this->address = ip_port;
//     this->locations = locations;
//     this->enable_mode = 1;
//     memset(&addr, 0, sizeof(addr));
// }

Core::Core(char *config)
{
    ConfigFile cfg;
    cfg.openConfigFile(argv[1]);
    servers = cfg.getAllServers();

    vector<Server>::iterator it = servers.begin();
    while (it != servers.end()) {
        cout << "server's ip_port: " << it->getIpPort() << endl << endl;
        vector<Location> locations = it->getLocations();
        cout << "locations.size: " << locations.size() << endl;
        vector<Location>::iterator ite = locations.begin();
        while (ite != locations.end()) {
            ite->printLocationInfo();
            cout << endl;
            ++ite;
        }
        ++it;
    }

}

Core::Core(const Core & rhs) 
{
    *this = rhs;
}

const Core & Core::operator=(const Core & rhs)
{
    if (this != &rhs)
    {
        //    
    }
    return *this;
}

Core::~Core() {}

void Core::createListenSock(void)
{
    this->listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(listen_sock, F_SETFL, O_NONBLOCK); // 
    if (listen_sock < 0)
    {
        fprintf(stderr, "[Error] : socket() system call failed\n");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, \
                    (const void *)&enable_mode, sizeof(enable_mode)) < 0)
    {
        fprintf(stderr, "[Error] : setsockopt() system call failed\n");
        exit(EXIT_FAILURE);
    }
}

int Core::fillServerStruct(std::string address)
{
    if (parse_address(address, this->ipv4, this->port) != 0)
        return PARSE_ERROR;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = htonl(atoi(ipv4));
    return 0;
}

void Core::bindListenSock(void)
{
    fprintf(stdout, "> binding ...\n");

    /* bind()
       assigns the address specified by addr to the socket referred to
       by the file descriptor sockfd.  addrlen specifies the size 
    */
    if (bind(listen_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        fprintf(stderr, "[Error] : bind() system call failed\n");
        exit(EXIT_FAILURE);
    }
}

void Core::createQueue(void)
{
    fprintf(stdout, "> listening ...\n");

    /*  listen() 
        marks the socket referred to by sockfd as a passive
        socket, that is, as a socket that will be used to accept incoming
        connection requests using accept(2)
    */
    if (listen(this->listen_sock, SOMAXCONN) != 0)
    {
        fprintf(stderr, "[Error] : listen() call failed\n");
        exit(EXIT_FAILURE);
    }
}

// парсер отправит вектор структур, по нему создаем слушающие сокеты в цикле 

void Core::initSocketSet(void)
{
    this->active_set[0].fd = listen_sock;
    this->active_set[0].events = POLLIN; //  POLLIN - there is data to read
    this->active_set[0].revents = 0;    // returned event 
    this->num_set = 1;
}

void Core::stateManager(void)
{
    int res;
    int err;
    int i; 

    while (true)
    {
        /* 
            it waits for one of a set of file descriptors to become ready to perform I/O
            1 - the set of file descriptors to be monitored 
            2 - specify the number of items in the fds array
            3 - specifies the number of milliseconds that poll() should block waiting for a file descriptor to become
                ready
                specifying a negative value in timeout means an infinite timeout
            функция блокируется до тех пор, пока во входящем сокете не появятся данные для чтения; изначально проверяем только слушающий сокет
        */
        res = poll(active_set, num_set, -1);
        if (res < 0)
        {
            fprintf(stderr, "[Error] : poll() system call failed\n");
            exit(EXIT_FAILURE);
        }
        if (res > 0)
        {
            for (i = 0; i < num_set; i++)
            {
                if (active_set[i].revents & POLLIN) // возвращенное состояние имеет выставленный бит, соответствующий событию POLL IN
                {
                    // fprintf(stdout, "got POLL IN in fd [%d]\n", active_set[i].fd); // 
                    active_set[i].revents &= - POLLIN; // для повторного использвания структуры обнуляем событие;

                    if (i == 0) /* this is the listening socket -> accept new connection */
                    { 
                        size = sizeof(client);
                        memset(&client, 0, sizeof(client));
                        // connect_sock = accept(active_set[i].fd, (struct sockaddr *)&client, (socklen_t *)&size);
                        connect_sock = accept(active_set[i].fd, NULL, NULL);
                        fprintf(stdout, "new client with fd [%d]\n", connect_sock);
                        fcntl(connect_sock, F_SETFL, O_NONBLOCK); // 
                        /* next step: add a new connected socket to the set */
                        if (num_set < SOMAXCONN)
                        {
                            active_set[num_set].fd = connect_sock;
                            active_set[num_set].events = POLLIN;
                            active_set[num_set].revents = 0;
                            num_set += 1;
                        } else 
                        {
                            fprintf(stderr, "[Error] : cannot create new socket\n");
                            close(connect_sock);
                        }
                    } else /* the connection was already established  */
                    {
                        err = readFromClient(active_set[i].fd, buf, BUF_LEN);
                        std::cout << "Message from Client : " << buf << std::endl;
                        active_set[i].events = POLLOUT;
                        if (err < 0)
                        {
                            close(active_set[i].fd);
                            if (i < num_set - 1)
                            {
                                // ToDo: in a loop 
                                active_set[i] = active_set[num_set - 1];
                                num_set--;
                                i--;
                            }
                        } else if (err == 0) // пустой запрос, закрыть соединение 
                        {
                            // ToDo: close connection, remove in a loop
                            close(active_set[i].fd);
                            active_set[i].fd = -1;
                            for (int i = 0; i < num_set; i++)
                            {
                                if (active_set[i].fd == -1)
                                {
                                    for (int j = 0; j < num_set - 1; j++)
                                        active_set[i].fd = active_set[j + 1].fd;
                                    i--;
                                    num_set--;
                                }
                            }
                        }
                    }
                } else if (active_set[i].revents & POLLOUT)
                {
                    sendToClient(active_set[i].fd, buf, BUF_LEN);
                    active_set[i].events = POLLIN;
                }
            }
        }
    }
}

int Core::readFromClient(int conn, char* buffer, size_t size)
{
    bzero((void *)buf, sizeof(buf));
    recv(conn, buffer, (int)size, 0);
    
    http.processMessage(buffer);
    return 0; // ToDo
}

int Core::sendToClient(int conn, const char *buffer, size_t size)
{
    std::string response = http.getResponseHeader();
    // response = "HTTP/1.1 200 OK\nContent-Length: 5\nContent-Type: text/html\r\n\r\nhello";
    std::cout << "THIS IS A RESPONSE : \n\n" << response << std::endl;
    // get bytes and send it back to the client
    std::cout << "THIS IS BODY::\n\n" << http.getResponseBody().c_str() << std::endl;
    send(conn, response.c_str(), strlen(response.c_str()), 0);
    http.recieveDataFromFile();
    while (!http.isEndOfFile())
    {
        // std::cout << "PIZDEC" << std::endl;
        send(conn, http.getResponseBody().c_str(), strlen(http.getResponseBody().c_str()), 0);
        http.recieveDataFromFile();

    }
    // return send(conn, http.getResponseBody().c_str(), strlen(http.getResponseBody().c_str()), 0);
    return 0;
}

/* ------------------------ private methods ------------------------ */
int Core::parse_address(std::string address, char *ipv4, char *port)
{
    size_t i = 0, j = 0;

    int pos = address.find(":");
    if (pos == std::string::npos)
        return 1;
    if (pos >= 16)
        return 2;
    strcpy(ipv4, address.substr(0, pos).c_str());
    std::string port_s = address.substr(pos + 1, address.length());
    if (port_s.length() >= 6)
        return 3;
    strcpy(port, port_s.c_str());
    return 0;
}
