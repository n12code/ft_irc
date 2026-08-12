#ifndef SENDFILECOMMAND_HPP
#define SENDFILECOMMAND_HPP

#include <string>
#include <vector>

class Bot;

std::string cmdSendFile(Bot& bot, const std::vector<std::string>& args);

#endif