Bot::~Bot()
{}

Bot::Bot(): _user("default"), _nick("default")
{}

Bot::Bot(std::string &user, std::string &nick):
_user(user), _nick(nick)
{}

Bot::Bot(const Bot& toCopy)
{}

Bot::connexion(std::string &password)
{
    std::string realname = this->_nick + "_bot";
    std::string connexion_pass = "PASS " + this->_password + "\r\n";
    std::string connexion_user = "USER " + this->_user + "0 * :" + realname;
    std::string connexion_nick = "NICK " + this->nick;
    send(this->_fd, connexion_pass.c_str(), connexion_pass.size(), 0);
    send(this->_fd, connexion_user.c_str(), connexion_user.size(), 0);
    send(this->_fd, connexion_nick.c_str(), connexion_nick.size(), 0);
}