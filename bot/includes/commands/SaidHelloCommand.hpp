#ifndef SAIDHELLOCOMMAND_HPP
#define SAIDHELLOCOMMAND_HPP

#include <string>
#include <vector>

class Bot;

std::string cmdSaidHello(Bot& bot, const std::vector<std::string>& args);

#endif