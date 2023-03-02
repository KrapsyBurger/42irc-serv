/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:22:40 by rpol              #+#    #+#             */
/*   Updated: 2023/03/02 17:18:59 by rpol             ###   ########.fr       */
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
	this->_name = toTheRight._name;
	this->_mode = toTheRight._mode;
	this->_host = toTheRight._host;
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

	return ( this->_nick + "!" + this->_name + "@" + this->_host );
}

void User::setNick( std::string nick ) {
	
	this->_nick = nick;
}

std::string User::getHost( void ) {

	return ( this->_host );
}

void User::_setInfo( std::string str, int clientSocket ) {
	
	this->_fd = clientSocket;
	std::istringstream iss( str );
    std::string word;
	while ( iss >> word ) {
		
		if ( word == "USER" ) {
			
			if ( iss >> word )
				this->_nick = word;
			if ( iss >> word )
				this->_name = word;
			if ( iss >> word ) {
				
				this->_host = word;
				return;
			}
		}
	}
}
