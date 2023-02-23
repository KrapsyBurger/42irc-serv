#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sockfd = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "An error has occured while creating the socket." << std::endl;
		return (-1);
	}
	std::cout << "socket is : " << sockfd << std::endl;
	
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = PF_LOCAL;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int	connect_result = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (connect_result < 0)
	{
		std::cerr << "Erreur lors de la connexion au socket" << std::endl;
		return (-1);
	}
	std::cout << "Le client est connecte sur le port 8080." << std::endl;
	return (0);
}