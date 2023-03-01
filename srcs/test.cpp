#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>


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

	std::cout << "Le serveur est connecte sur le port " << argv[1] << "." << std::endl;


	pollfd	poll_struct;
	std::vector<pollfd> poll_vec;
	std::vector<pollfd>::iterator poll_it;
	std::vector<pollfd>::iterator poll_endit;
	char recv_buff[1024];
	int byte_received;
	int	clientsockfd;
	clientsockfd = accept(sockfd, NULL, NULL);
	poll_struct.fd = clientsockfd;
	poll_struct.events = POLLIN;
	poll_struct.revents = 0;
	poll_vec.push_back(poll_struct);
	poll_it = poll_vec.begin();
	poll_endit = poll_vec.end();
	while (true)
	{
		while (poll_it != poll_endit)
		{
			if (poll(poll_vec.data(), poll_vec.size(), -1) > 0)
			{
				if (poll_it->revents == POLLIN)
				{
					byte_received = recv(clientsockfd, recv_buff, sizeof(recv_buff), 0);
					recv_buff[byte_received] = '\0';
					if (byte_received > 0)
						std::cout << "Received : [" << std::string(recv_buff, 0, byte_received) << "]" << std::endl;
					poll_vec.push_back(poll_struct);
				}
			}
			std::cout << "coucou" << std::endl;
			poll_it++;
		}
		poll_it = poll_vec.begin();
	}
	close(sockfd);
	return (0);
}
