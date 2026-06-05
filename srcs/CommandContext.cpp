#include "CommandContext.hpp"

CommandContext::CommandContext(Server &s, Client &c, ClientManager &cm, Message &m)://, ChannelManager& chm
    server(s),
    client(c),
    clients(cm),
    //channels(chm),
    msg(m) {}