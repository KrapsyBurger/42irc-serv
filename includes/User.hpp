/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:18:45 by rpol              #+#    #+#             */
/*   Updated: 2023/03/09 02:01:04 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <string>
#include <sstream>

class User {
	
	public:

		//canon
		User( const User & to_copy );
		User & operator=( const User & toTheRight );
		~User( void );

		User( int clientSocket );

		void printInfo();


		std::string getName( void ) const;
		std::string getHost( void ) const;
		int			getFd( void ) const;
		
		void		setNick( std::string nick );
		std::string getNick( void ) const;		
		
		std::string	getBuff( void ) const;
		void		setBuff( std::string buff );
		void		appendBuff( std::string buff );

		void		initUser( std::string password ); 
		
		bool		isUserSet;
		
	private:

		//canon
		User( void );

		
		std::string _nick;
		
		std::string _name;

		std::string _host;

		std::string _buff;

		bool _isPasswordChecked;
		
		int _fd;

		

		int _mode;
};

#endif