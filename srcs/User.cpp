/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:22:40 by rpol              #+#    #+#             */
/*   Updated: 2023/03/01 16:54:37 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User( void ) {

	return;
}

User::User( std::string str, int clientSocket ) {
	
	_setInfo( str, clientSocket );
	return;
}

User::User(const User & to_copy) {
	
	*this = to_copy;
	return;
}

User &User::operator=(const User & toTheRight)
{
	if ( this == &toTheRight )
		return ( *this );
		
	this->_fd = toTheRight._fd;
	this->_nick = toTheRight._nick;
	this->_mode = toTheRight._mode;
	return ( *this );
}

User::~User( void ) {

	return;
}

void User::printInfo( void ) {

	std::cout << _nick << std::endl << getName() << std::endl;	
}

std::string User::getNick( void ) {

	return ( this->_nick );
}

int User::getFd( void ) {

	return ( this->_fd );
}

std::string User::getName( void ) {

	return ( this->_nick + "!" + this->_nick + "@" + this->_host );
}

void User::setNick( std::string nick ) {
	
	this->_nick = nick;
}

std::string User::getHost( void ) {

	return ( this->_host );
}

void User::_setInfo( std::string str, int clientSocket ) {
	
	size_t nick_pos = str.find("NICK ");
	this->_fd = clientSocket;
	this->_host = "localhost";
    
	if ( nick_pos != std::string::npos ) {
        
		size_t nick_end_pos = str.find("\n", nick_pos + 5);
        
		if ( nick_end_pos != std::string::npos ) {
			
            std::string nick = str.substr(nick_pos + 5, nick_end_pos - nick_pos - 6);
            _nick = nick;
        }
    }
}
