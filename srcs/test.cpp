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
	std::string RPL_WELCOME = ":nfascia!nfascia@localhost 001 nfascia :Welcome to the Internet Relay Network nfascia!nfascia@localhost\n";
	std::string RPL_YOURHOST = ":nfascia!nfascia@localhost 002 nfascia :Your host is <server_name>, running version <666>\n";
	std::string RPL_CREATED = ":nfascia!nfascia@localhost 003 nfascia :This server was created <date>\n";
	std::string RPL_MYINFO = ":nfascia!nfascia@localhost 004 nfascia :<server_name> <version> <user_modes> <chan_modes>\n";

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

	std::cout << "Le serveur est connecte sur le port " << argv[1] << "." << std::endl;


	char recv_buff[1024];
	int byte_received;
	int	clientsockfd;
	int i = 0;
	clientsockfd = accept(sockfd, NULL, NULL);
	while (true)
	{
		byte_received = recv(clientsockfd, recv_buff, sizeof(recv_buff), 0);
		recv_buff[byte_received] = '\0';

		if (byte_received > 0)
			std::cout << "Received : " << std::string(recv_buff, 0, byte_received) << std::endl;

		if (i == 0)
		{
			std::string nick_welcome = ":NICK :nfascia\n";
			send(clientsockfd, nick_welcome.c_str(), nick_welcome.length(), 0);
			send(clientsockfd, RPL_WELCOME.c_str(), RPL_WELCOME.length(), 0);
			send(clientsockfd, RPL_YOURHOST.c_str(), RPL_YOURHOST.length(), 0);
			send(clientsockfd, RPL_CREATED.c_str(), RPL_CREATED.length(), 0);
			send(clientsockfd, RPL_MYINFO.c_str(), RPL_MYINFO.length(), 0);
			i++;
		}
	}
	close(sockfd);
	return (0);
}
