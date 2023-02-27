#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cctype>


bool is_string_digit(char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
			return false;
		str++;
	}
	return true;
}

bool arguments_check(int argc, char *str)
{
	if (argc != 3)
	{
		std::cerr << "Error : must put 2 arguments." << std::endl;
		return false;
	}
	if (!is_string_digit(str))
	{
		std::cerr << "Error : first argument have to be only digits." << std::endl;
		return false;
	}
	return true;
}

int main(int argc, char **argv)
{

	if (!arguments_check(argc, argv[1]))
		return (-1);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "An error has occured while creating the socket." << std::endl;
		return (-1);
	}
	std::cout << "socket is : " << sockfd << std::endl;
	
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int	bind_result = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (bind_result < 0)
	{
		std::cerr << "Error : cannot bind to the socket. Port is already used." << std::endl;
		return (-1);
	}


	int listen_result = listen(sockfd, 5);
	if (listen_result < 0)
	{
		std::cerr << "Error : cannot listen on this port." << std::endl;
		return (-1);
	}

	std::cout << "Le client est connecte sur le port " << argv[1] << "." << std::endl;

	while(1)
	{}

	std::string quit_cmd = "/quit\n";
	int send_result = send(sockfd, quit_cmd.c_str(), quit_cmd.length(), 0);
	if (send_result < 0)
	{
		std::cerr << "Unable to send the message to the socket." << std::endl;
		return (-1);
	}
	
	std::cout << "A message has been sent to " << argv[1] << "." << std::endl;

	close(sockfd);
	return (0);
}