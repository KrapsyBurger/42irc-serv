#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "An error has occured while creating the socket." << std::endl;
		return (-1);
	}
	std::cout << "socket is : " << sockfd << std::endl;
	
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int	bind_result = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (bind_result < 0)
	{
		std::cerr << "Error : cannot bind to the socket." << std::endl;
		return (-1);
	}


	int listen_result = listen(sockfd, 5);
	if (listen_result < 0)
	{
		std::cerr << "Error : cannot listen on this port." << std::endl;
		return (-1);
	}

	std::cout << "Le client est connecte sur le port 8080." << std::endl;
	return (0);
}