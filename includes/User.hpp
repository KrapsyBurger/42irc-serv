/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:18:45 by rpol              #+#    #+#             */
/*   Updated: 2023/03/01 21:52:56 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <string>

class User {
	
	public:

		//canon
		User( const User & to_copy );
		User & operator=( const User & toTheRight );
		~User( void );

		User( std::string str, int clientSocket );

		void printInfo();

		std::string getNick( void );
		std::string getName( void );
		std::string getHost( void );
		int			getFd( void );
		void		setNick( std::string nick );
		
	private:

		//canon
		User( void );



		void 	_setInfo( std::string buf, int clientSocket  );
		


		std::string _nick;
		
		std::string _name;

		std::string _host;
		
		int _fd;

		int _mode;
};

#endif