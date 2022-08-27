# define LOCALHOST "127.0.0.1"

// # include "Core/Core.hpp"
# include "Http/Http.hpp"
# include "Parser/ConfigFile.hpp"
# include "Net/Net.hpp"
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage:\n\t./run {config__file}.cfg\n";
		exit(EXIT_FAILURE); 
	}
	Core 	core(argv[1]);

	// core.printInfo();
	std::cout << "Debugd\n" << std::endl;
	core.setUpWebServers();
	core.runWebServers();

	// char buffer[30000];
	// int socket_fd, accept_fd;
	// Net net;
	// Http http;
	// std::map<int, Http*> connection;

	// socket_fd = net.listen_net("0.0.0.0:8088");
	// if (socket_fd < 0)
	// {
	// 	std::cerr << "Jopa" << std::endl;
	// 	exit(101);
	// }
	// while (1)
	// {
	// 	std::cout << "ATTENTION!!! WAITING FOR CONNECTION!!!" << std::endl;
	// 	accept_fd = net.accept_net(socket_fd);
	// 	std::cout << "ACCEPTED FD: " << accept_fd << std::endl;
	// 	if (accept_fd < 0)
	// 	{
	// 		std::cerr << "Accepting failure" << std::endl;
	// 		exit(1);
	// 	}
	// 	bool test = false;
	// 	while (!test) //ТУДУ: НИКАКИХ ВАЙЛ! СЮДА ЗАХОД ПОСЛЕ POLL
	// 		test = http.acceptRequest(accept_fd);
	// 	test = false;
	// 	while (!test)
	// 	{
	// 		test = http.getResponse(accept_fd);
	// 	}
	// 	std::cout << "CONNECTION REFUSED!!!" << std::endl;
	// }

	// close(socket_fd);
	/* REQUEST TEMPLATE */
	// std::string buff = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nsec-ch-ua:  Not A;Brand;v=99, Chromium;v=100, Google Chrome;v=100\r\nsec-ch-ua-mobile: ?0sec-ch-ua-platform: macOS\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7\r\n";
	/*		*/

	/* RESPONSE TEMPLATE */
	// const char *message = "HTTP/1.1 200 OK\r\nContent-Length: 160038\r\nContent-Type: image/png\r\nConnection: Closed\r\n\r\n";
	/*		*/
	
	
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

	// vector<Server> servers = cfg.getAllServers();
	// vector<Server>::iterator it = servers.begin();
	// while (it != servers.end()) {
	// 	cout << "server's ip_port: " << it->getIpPort() << endl << endl;
	// 	vector<Location> locations = it->getLocations();
	// 	cout << "locations.size: " << locations.size() << endl;
	// 	vector<Location>::iterator ite = locations.begin();
	// 	while (ite != locations.end()) {
	// 		ite->printLocationInfo();
	// 		cout << endl;
	// 		++ite;
	// 	}
	// 	++it;
	// }

}