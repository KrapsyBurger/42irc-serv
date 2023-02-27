#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cctype>


bool	is_string_digit( char *str ) {

	while ( *str ) {

		if ( !isdigit( *str ) )
			return ( EXIT_FAILURE );
		str++;
	}
	return ( EXIT_SUCCESS );
}

bool	arguments_check( int argc, char *str ) {

	if ( argc != 3 ) {

		std::cerr << "Error : must put 2 arguments." << std::endl;
		return ( EXIT_FAILURE );
	}
	if ( is_string_digit( str ) ) {

		std::cerr << "Error : first argument have to be only digits." << std::endl;
		return ( EXIT_FAILURE );
	}
	return ( EXIT_SUCCESS );
}

int main(int argc, char **argv)
{

	if ( arguments_check(argc, argv[1]) )
		return ( EXIT_FAILURE );

	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening < 0) {

		std::cerr << "An error has occured while creating the socket." << std::endl;
		return ( EXIT_FAILURE );
	}
	std::cout << "socket is : " << listening << std::endl;
	
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons( atoi( argv[1] ) );
	inet_pton( AF_INET, "0.0.0.0", &hint.sin_addr );

	
	if ( bind( listening, AF_INET, &hint, sizeof(hint) ) < 0) {

		std::cerr << "Error : cannot bind to IP/Port." << std::endl;
		return ( EXIT_FAILURE );
	}


	int listen_result = listen(listening, 5);
	if (listen_result < 0) {

		std::cerr << "Error : cannot listen on this port." << std::endl;
		return ( EXIT_FAILURE );
	}

	std::cout << "The client is connected to port : " << argv[1] << "." << std::endl;
	return (0);
}