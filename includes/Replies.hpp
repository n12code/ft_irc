/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 09:21:46 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/16 08:41:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# include "Status.hpp"
# include <string>
# include <vector>
# include <map>

class Replies
{
    private:
        typedef std::string (*ReplyBuilder)(const std::vector<std::string>& args);
        static  std::map<Status, ReplyBuilder> _replies;
        
        static std::string  dispatch(Status status, const std::vector<std::string>& args);
        static std::string  _server;
    public:
        static void init();
        static std::string create(Status status, 
                                  const std::string& arg1, 
                                  const std::string& arg2 = "", 
                                  const std::string& arg3 = "", 
                                  const std::string& arg4 = "", 
                                  const std::string& arg5 = "", 
                                  const std::string& arg6 = "", 
                                  const std::string& arg7 = "",
                                  const std::string& arg8 = "",
                                  const std::string& arg9 = "");
                                  
        //errors
        static  std::string errNoSuchNick(const std::vector<std::string>& args);
        static  std::string errNoSuchChannel(const std::vector<std::string>& args);
        static  std::string errUserNotInChannel(const std::vector<std::string> &args);
        static  std::string errNotOnChannel(const std::vector<std::string>& args);
        static  std::string errChannelIsFull(const std::vector<std::string> &args);
        static  std::string errInviteOnlyChan(const std::vector<std::string> &args);
        static  std::string errBadChannelKey(const std::vector<std::string> &args);
        static  std::string errChaNoPrivsNeeded(const std::vector<std::string> &args);

        //replies
        static  std::string rplWelcome(const std::vector<std::string> &args);
        static  std::string rplEndOfWho(const std::vector<std::string> &args);
        static  std::string rplTopic(const std::vector<std::string> &args);
        static  std::string rplWhoReply(const std::vector<std::string> &args);
        static  std::string rplNamReply(const std::vector<std::string> &args);
        static  std::string rplEndOfNames(const std::vector<std::string> &args);
};

#endif