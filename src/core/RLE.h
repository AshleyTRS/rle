#ifndef RLE_H
#define RLE_H

#include <string>

namespace RLE
{
    std::string encode(const std::string &input);
    std::string decode(const std::string &input);
    size_t countUTF8Chars(const std::string &str);
}

#endif