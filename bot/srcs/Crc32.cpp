#include "Crc32.hpp"
#include <sstream>
#include <iomanip>

static void initCrc32Table(unsigned int (&crc32Table)[256], bool& tableInitialized)
{
    for (unsigned int i = 0; i < 256; ++i)
    {
        unsigned int c = i;
        for (int j = 0; j < 8; ++j)
        {
            if (c & 1)
                c = 0xEDB88320 ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc32Table[i] = c;
    }
    tableInitialized = true;
}

static unsigned int crc32(const std::string& data, unsigned int (&crc32Table)[256])
{
    static bool         tableInitialized = false;
    if (!tableInitialized)
        initCrc32Table(crc32Table, tableInitialized);

    unsigned int crc = 0xFFFFFFFF;
    for (size_t i = 0; i < data.size(); ++i)
    {
        unsigned char byte = static_cast<unsigned char>(data[i]);
        crc = crc32Table[(crc ^ byte) & 0xFF] ^ (crc >> 8);
    }
    return (crc ^ 0xFFFFFFFF);
}

std::string computeCrc32(const std::string& input)
{
    static unsigned int crc32Table[256];
    unsigned int checksum = crc32(input, crc32Table);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << checksum;
    return (oss.str());
}