/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:09:26 by rpol              #+#    #+#             */
/*   Updated: 2023/03/13 18:10:39 by nfascia          ###   ########.fr       */
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
	if (this == &toTheRight)
		return (*this);
	this->_password = toTheRight._password;
	this->_hostName = toTheRight._hostName;
	this->_socket = toTheRight._socket;
	this->users = toTheRight.users;
	return (*this);
}

Server::~Server( void ) {
	delete[] this->_poll_fds;
	return;
}

Server::Server( std::string const hostName, std::string const password, int fd ) {
	this->_password = password;
	this->_hostName = hostName;
	this->_socket = fd;
	this->_poll_fds = new pollfd[1024];
	this->_poll_fds[0].fd = fd;
	this->_poll_fds[0].events = POLLIN;
	this->_clientNbr = 0;
	return;
}

User * Server::user( int userIndex ) {
	int index = 1;

	std::list< User * >::iterator it = this->users.begin();
	std::list< User * >::iterator ite = this->users.end();
	while (index != userIndex) {
		
		index++;
		it++;
		if (it == ite)
			std::cerr << "Error : User in Server ite problem" << std::endl;
	}
	return (*it);
}


// getter
std::string Server::getPassword( void ) const {
	return (this->_password);
}

std::string Server::getHostName( void ) const {
	return (this->_hostName);
}

pollfd		*Server::getAllPollfds( void ) const {
	return (this->_poll_fds);
}

int			Server::getClientNbr( void ) const {
	return (this->_clientNbr);
}

pollfd		Server::getPollfd( int index ) const {
	return (this->_poll_fds[index]);
}

//setter
void		Server::clientNbrIncr( void ) {
	this->_clientNbr += 1;
}

void		Server::setPollfd( int index, int fd_value, int events_value, int revents_value) {
	this->_poll_fds[index].fd = fd_value;
	this->_poll_fds[index].events = events_value;
	this->_poll_fds[index].revents = revents_value;
}