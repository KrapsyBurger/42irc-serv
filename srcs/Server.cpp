/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:09:26 by rpol              #+#    #+#             */
/*   Updated: 2023/03/02 16:51:59 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Server.hpp"
#include "Server.hpp"

//canon
Server::Server( void ) {

	return;
}

Server::Server( const Server & to_copy ) {
	
	*this = to_copy;
	return;
}

Server &Server::operator=( const Server & toTheRight ) {
	
	if ( this == &toTheRight )
		return ( *this );
	
	this->_password = toTheRight._password;
	this->_hostName = toTheRight._hostName;
	this->_socket = toTheRight._socket;
	this->users = toTheRight.users;
	
	return ( *this );
}

Server::~Server( void ) {

	return;
}

std::string Server::getPassword( void ) const {
	
	return ( this->_password );
}

std::string Server::getHostName( void ) const {
	
	return ( this->_hostName );
}

Server::Server( std::string const hostName, std::string const password, int fd ) {
	
	this->_password = password;
	this->_hostName = hostName;
	this->_socket = fd;
	return;
}


