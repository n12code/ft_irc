#ifndef FILETRANSFER_HPP
#define FILETRANSFER_HPP

#include <string>

struct FileTransfer
{
    std::string sender;
    std::string filename;
    size_t      expectedSize;
    std::string expectedcrc32;
    std::string accumulatedBase64;
};

#endif