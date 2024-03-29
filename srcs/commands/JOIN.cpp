#include "irc.hpp"

void	join_cmd(std::istringstream *iss, std::string word, User *user, Server &srv) {
	if (*iss >> word) {
		std::list<Channel*>::iterator it = srv.find_channel( word );
		if (it == srv.getChannelsEnd() ){	
			srv.add_to_Channels(new Channel(word, user));
			std::cerr << "User " << user->getNick() << " created channel " << word << std::endl;
		} else {
			Channel * tmp = *it;
			if (tmp->isBanned(user) && !user->isServerOperator)
				return;
			if (tmp->isInviteOnly && !tmp->isInvited(user)) {
				std::string msg = ERR_NEEDINVITE(user, tmp);
				send(user->getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
				return;
			}
			tmp->join( user );
			std::string current_topic = (*it)->get_topic();
			if (!current_topic.empty()) {
				std::string msg = RPL_TOPIC(user, word, current_topic);
				send(user->getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
			}
			std::cerr << "User " << user->getNick() << " was added to channel " << tmp->getName() << std::endl;
		}
	} else {
		std::string msg = ERR_NEEDMOREPARAMS(user, "JOIN");
		send(user->getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
	}
}