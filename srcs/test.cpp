#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
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

	
	if ( bind( listening, reinterpret_cast< sockaddr * >( &hint ), sizeof( hint ) ) < 0 ) {

		std::cerr << "Error : cannot bind to IP/Port." << std::endl;
		return ( EXIT_FAILURE );
	}


	
	if ( listen( listening, SOMAXCONN ) < 0 ) {

		std::cerr << "Error : cannot listen to the IP/Port." << std::endl;
		return ( EXIT_FAILURE );
	}

	sockaddr_in client;
	socklen_t clientSize = sizeof( client );
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];

	int clientSocket = accept( listening,
								 reinterpret_cast< sockaddr * >( &client ),
								  &clientSize );

	if ( clientSocket < 0 ) {

		std::cerr << "Error : problem with client connecting." << std::endl;
		return ( EXIT_FAILURE );
	}
	close( listening );

	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo( reinterpret_cast< sockaddr * >( &client ),
								  sizeof ( client ),
								  host,
								  NI_MAXHOST,
								  svc,
								  NI_MAXSERV,
								  0);
	if ( result ) {

		std::cout << host << " connected on " << svc << std::endl;
	} else {

		inet_ntop( AF_INET, &client.sin_addr, host, NI_MAXHOST );
		std::cout << host << " connected on " << ntohs( client.sin_port ) << std::endl;
	}

	char buf[4096];

	while ( true ) {

		memset( buf, 0, 4096 );
		int bytesRecv = recv( clientSocket, buf, 4096, 0);
		if ( bytesRecv < 0 ) {

			std::cerr << "Error : connection issue." << std::endl;
			break;
		}

		if ( !bytesRecv ) {

			std::cout << "The client disconected." << std::endl;
			break;
		}

		std::cout << "Received : " << std::string( buf, 0, bytesRecv ) << std::endl;

		send( clientSocket, buf, bytesRecv + 1, 0);
	}

	close( clientSocket );
	
	return ( EXIT_SUCCESS );
}