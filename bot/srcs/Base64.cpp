#include "Base64.hpp"

static const std::string BASE64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static int base64CharIndex(char c)
{
    if (c >= 'A' && c <= 'Z') return (c - 'A');
    if (c >= 'a' && c <= 'z') return (c - 'a' + 26);
    if (c >= '0' && c <= '9') return (c - '0' + 52);
    if (c == '+') return (62);
    if (c == '/') return (63);
    return (-1);
}

std::string base64Encode(const std::string& input)
{
    std::string result;
    size_t      i = 0;
    unsigned char buf3[3];
    unsigned char buf4[4];

    for (size_t pos = 0; pos < input.size(); )
    {
        i = 0;
        while (i < 3 && pos < input.size())
        {
            buf3[i] = static_cast<unsigned char>(input[pos]);
            ++i;
            ++pos;
        }

        buf4[0] = (buf3[0] & 0xFC) >> 2;// 0xFC => 1111 1100
        buf4[1] = ((buf3[0] & 0x03) << 4) | ((buf3[1] & 0xF0) >> 4);// 0x03 => 0000 0101; 0xF0 => 1111 0000
        buf4[2] = ((buf3[1] & 0x0F) << 2) | ((buf3[2] & 0xC0) >> 6);// 0x0F => 0000 1111; 0xC0 => 1100 0000
        buf4[3] = buf3[2] & 0x3F;// 0x3F => 0011 1111;

        for (size_t j = 0; j < i + 1; ++j)
            result += BASE64_CHARS[buf4[j]];

        for (size_t j = i; j < 3; ++j)
            result += '=';
    }
    return (result);
}

std::string base64Decode(const std::string& input)
{
    std::string   result;
    unsigned char buf4[4];
    unsigned char buf3[3];
    size_t        i = 0;

    for (size_t pos = 0; pos < input.size(); )
    {
        i = 0;
        while (i < 4 && pos < input.size())
        {
            char c = input[pos++];
            if (c == '=')
                break;
            int idx = base64CharIndex(c);
            if (idx == -1)
                continue;
            buf4[i++] = static_cast<unsigned char>(idx);
        }
        if (i == 0)
            break;

        buf3[0] = (buf4[0] << 2) | ((buf4[1] & 0x30) >> 4); //0x30 => 0011 0000
        buf3[1] = ((buf4[1] & 0x0F) << 4) | ((buf4[2] & 0x3C) >> 2);//0x0F => 0000 1111; 0x3C => 0011 1100
        buf3[2] = ((buf4[2] & 0x03) << 6) | buf4[3];//0x03 0000 0011

        for (size_t j = 0; j < i - 1; ++j)
            result += static_cast<char>(buf3[j]);
    }
    return (result);
}