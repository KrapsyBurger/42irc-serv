/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:53:07 by nfascia           #+#    #+#             */
/*   Updated: 2023/03/23 17:41:23 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	pass_cmd(std::istringstream *iss, std::string *word, User *user, Server &srv)
{
	if ( *iss >> *word ) {
		if ( *word == srv.getPassword() ) {
				user->isPasswordChecked = true;
				user->isPasswordChecked = true;
				std::cerr << "A user got password right" << std::endl;
			} else {
				if ( user->isIrssi )
					user->isAlive = false;
				std::string msg = ERR_PASSWDMISMATCH(user);
				send(user->getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
			}
	} else {
		std::string msg = ERR_NEEDMOREPARAMS(user, "PASS");
		send(user->getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
	}
}