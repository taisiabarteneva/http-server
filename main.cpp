#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define LOCALHOST "127.0.0.1"

#include "Http/Http.hpp"
#include "ConfigFile/config_file.hpp"

int main(int argc, char** argv)
{
	struct sockaddr_in serv_addr = {0};
	char buffer[30000];
	int socket_fd, err, accept_fd;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(80);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		std::cerr << "Socket failure" << std::endl;
		exit(1);
	}
	err = bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (err < 0)
	{
		std::cerr << "Binding failure" << errno <<  std::endl;
		exit(1);
	}
	err = listen(socket_fd, 10);
	if (err < 0)
	{
		std::cerr << "Listening failure" << std::endl;
		exit(1);
	}
	int fd = open("resources/22.png", O_RDWR);
    char bufer[160038];
    err = read(fd, bufer, 160038);
	while (1)
	{
		std::cout << "ATTENTION!!! WAITING FOR CONNECTION!!!" << std::endl; // здесь цикл
		int addrlen = sizeof(serv_addr);
		accept_fd = accept(socket_fd, (struct sockaddr *)&serv_addr, (socklen_t *)&addrlen);
		if (accept_fd < 0)
		{
			std::cerr << "Accepting failure" << std::endl;
			exit(1);
		}
		recv(accept_fd, buffer, 30000, 0);
		// Http http(buffer); //TODO: в разработке
		std::cout << buffer << std::endl; //вывод полученного сообщения от сервера
		const char *message = "HTTP/1.1 200 OK\r\nContent-Length: 160038\r\nContent-Type: image/png\r\nConnection: Closed\r\n\r\n";
		send(accept_fd, message, strlen(message), 0);
		send(accept_fd, bufer, 160038, 0);
		close(accept_fd);
		std::cout << "CONNECTION REFUSED!!!" << std::endl;
	}

	close(socket_fd);
	/* TEST
	char ip[INET_ADDRSTRLEN];
	std::cout << inet_ntop(AF_INET, &(serv_addr.sin_addr), ip, INET_ADDRSTRLEN) << std::endl;
	std::cout << ntohs(serv_addr.sin_port) << std::endl;
	*/ 
	

	/* FORBIDDEN
	// int status;
	// struct addrinfo hints;
	// struct addrinfo *servinfo;

	// memset(&hints, 0, sizeof hints);
	// hints.ai_family = AF_UNSPEC;
	// hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE;
	// if ((status = getaddrinfo(NULL, "80", &hints, &servinfo)))
	// {
	// 	fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	// 	exit(1);
	// }
	// freeaddrinfo(servinfo);
	*/

	// int bind1 = bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	// if (bind1 < 0)
	// {
	// 	std::cerr << "binding problems" << std::endl;
	// }
	// std::cout << inet_ntoa(serv_addr.sin_addr) << std::endl;
	// std::cout << htons(serv_addr.sin_port) << std::endl;

	// listen(fd, 5);
	// int addrlen = sizeof(serv_addr);
	// int new_socket = accept(fd, (struct sockaddr *)&serv_addr, (socklen_t *)&addrlen);
	// if (new_socket < 0)
	// {
	// 	std::cerr << "accept troubles" << std::endl;
	// 	perror("");
	// }

	// std::cout << server->h_name << std::endl;
	// serv_addr.sin_family = AF_INET;
	// bcopy((char *) server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	// serv_addr.sin_port = htons(80);
	// int err = connect(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	// if (err < 0)
	// {
	// 	std::cerr<< "Connection failure" << std::endl;
	// }
	// printf("Enter the message: ");
	// fgets(buffer, 255, stdin);
	// int n = write(fd, buffer, strlen(buffer));
	// if ( n < 0)
	// {
	// 	std::cerr << "Bad write" << std::endl;
	// }
	// bzero(buffer, 256);

	// n = read(fd, buffer, 255);
	// if (n < 0)
	// {
	// 	std::cerr << "Bad read" << std::endl;
	// }
	// close(fd);

//    ConfigFile cfg;
//    cfg.openConfigFile(argv[1]);

}