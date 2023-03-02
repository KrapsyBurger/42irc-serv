/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:08:36 by rpol              #+#    #+#             */
/*   Updated: 2023/03/02 16:27:11 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"
#include <list>

class User;

class Server {

	public :

		//canon
		Server( const Server & to_copy );
		Server & operator=( const Server & toTheRight );
		~Server( void );

		Server( std::string const password, std::string const hostName, int socket);
		
		std::string getPassword( void ) const;
		
		std::string getHostName( void ) const;
		
		std::list< User * > users;
	
	private :

		//canon
		Server( void );

		std::string		_password;
		
		std::string		_hostName;

		int				_socket;
};

#endif