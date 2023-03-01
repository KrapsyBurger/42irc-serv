

#include "../includes/irc.hpp"
#include "../includes/User.hpp"


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

std::string RPL_WELCOME( User & user ) {
	
	return ( ":" + user.getName() + " 001 " + user.getNick() + " :Welcome to the Internet Relay Network " + user.getName() + "\n" );
} 

std::string RPL_YOURHOST( User & user ) { 
	
	return ( ":" + user.getName() + " 002 " + user.getNick() + " :Your host is " + user.getHost() + ", running version 42\n" );
}

std::string RPL_CREATED( User & user ) { 
	
	return ( ":" + user.getName() + " 003 " + user.getNick() + " :This server was created at saint Gliglin\n" );
}

std::string RPL_MYINFO( User & user ) {
	
	return ( ":" + user.getName() + " 002 " + user.getNick() + " :" + user.getHost() + " 42 iwso ntio\n" );
}

std::string NICK( User & user, std::string nick ) {
	
	return ( ":" + user.getName() + " NICK " + nick + "\n");
}

std::string PONG( User & user ) {
	
	return ( ":" + user.getName() + " PONG " + user.getHost() + "\n");
}

void stream( std::string str, User & user ) {

	std::istringstream iss(str);
    std::string word;
	if ( iss >> word ) {
		
		if ( word == "NICK") {

			if ( iss >> word ) {

				if ( user.getNick() != word ) {

					std::string str = NICK( user, word );
					user.setNick( word );
					send( user.getFd(), str.c_str(), str.length(), MSG_NOSIGNAL );
				}
			}
		}
		else if ( word == "PING") {

			if ( iss >> word ) {
				std::string str = PONG( user );
				send( user.getFd(), str.c_str(), str.length(), MSG_NOSIGNAL );
				std::cerr << str << std::endl;
				str = "PING localhost\n";
				send( user.getFd(), str.c_str(), str.length(), MSG_NOSIGNAL );
			}
		}
	}
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

	bool firstConnection = true;
	
	User *user;

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
		std::string str = std::string( buf, 0, bytesRecv );
		std::cout << "Received : " << str << std::endl;


		if ( firstConnection ) {

			user = new User( str, clientSocket );

			user->printInfo();
        	send( user->getFd(), RPL_WELCOME( *user ).c_str(), RPL_WELCOME( *user ).length(), 0);
			send( user->getFd(), RPL_YOURHOST( *user ).c_str(), RPL_YOURHOST( *user ).length(), 0);
			send( user->getFd(), RPL_CREATED( *user ).c_str(), RPL_CREATED( *user ).length(), 0);
			send( user->getFd(), RPL_MYINFO( *user ).c_str(), RPL_MYINFO( *user ).length(), 0);
			firstConnection = false;
		} else {
			
			stream( str, *user );
		}

    	
	}

	close( clientSocket );
	
	return ( EXIT_SUCCESS );
}