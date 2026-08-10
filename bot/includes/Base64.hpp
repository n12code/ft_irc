#ifndef BASE64_HPP
# define BASE64_HPP

# include <string>

static const std::string BASE64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64Encode(const std::string& input);
std::string base64Decode(const std::string& input);

#endif