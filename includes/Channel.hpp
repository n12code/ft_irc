/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:57:18 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/09 11:03:14 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <set>
# include <string>

class Channel
{
    private:
        std::size_t     _maxCap;
        std::string     _name;
        std::string     _topic;
        std::string     _password;
        std::set<char>  _modes;
        std::set<int>   _chanops;
        std::set<int>   _users;
        std::set<int>   _invited;
    public:
        Channel();
        Channel(const std::string& name, const int creatorFd);
        ~Channel();

        bool    hasMode(const char mode);
        bool    isInvited(const int fd);
        bool    isBanned(const int fd);
        bool    isChanop(const int fd);
        
        const std::string   getPassword() const;
        const std::string   getName() const;
        std::size_t   getMaxCap() const;
        const std::set<int> getUsers() const;

        
        void    setPassword(const std::string& password);
        //utility
        void    addMode(const char mode);
        void    removeMode(const char mode);
        void    addInvited(const int fd);
        void    removeInvited(const int fd);
        void    addChanop(const int fd);
        void    removeChanop(const int fd);
        void    addUser(const int fd);
        void    removeUser(const int fd);
};

#endif