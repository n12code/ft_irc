#include "CommandContext.hpp"

CommandContext::CommandContext(Server &s, Client &c, ClientManager &cm, ChannelManager &chm, Message &m):
    server(s),
    client(c),
    clients(cm),
    channels(chm),
    msg(m) {}