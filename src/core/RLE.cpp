#include "RLE.h"
#include <string>

using namespace std;

static string getUTF8Char(const string &str, size_t &pos)
{
    if (pos >= str.size())
        return "";

    unsigned char byte = str[pos];
    string result;
    int charLen = 1;

    if ((byte & 0x80) == 0)
        charLen = 1;
    else if ((byte & 0xE0) == 0xC0)
        charLen = 2;
    else if ((byte & 0xF0) == 0xE0)
        charLen = 3;
    else if ((byte & 0xF8) == 0xF0)
        charLen = 4;

    for (int i = 0; i < charLen && pos < str.size(); i++, pos++)
        result += str[pos];

    return result;
}

size_t RLE::countUTF8Chars(const string &str)
{
    size_t count = 0;
    size_t i = 0;
    while (i < str.size())
    {
        getUTF8Char(str, i);
        count++;
    }
    return count;
}

string RLE::encode(const string &input)
{
    if (input.empty())
        return "";

    string encoded = "";
    size_t i = 0;
    string currentChar = getUTF8Char(input, i);
    long long count = 1;

    while (i < input.size())
    {
        string nextChar = getUTF8Char(input, i);
        if (nextChar == currentChar)
            count++;
        else
        {
            encoded += to_string(count) + currentChar;
            currentChar = nextChar;
            count = 1;
        }
    }

    encoded += to_string(count) + currentChar;
    return encoded;
}

string RLE::decode(const string &input)
{
    string decoded = "";
    size_t i = 0;
    const size_t maxSize = 100000000; // 100 MB limit

    while (i < input.size())
    {
        // Read number
        string num = "";
        while (i < input.size() && isdigit(input[i]))
        {
            num += input[i++];
        }

        // Skip if no number was found
        if (num.empty())
        {
            getUTF8Char(input, i);
            continue;
        }

        long long count = stoll(num);

        // Read UTF-8 char
        string ch = getUTF8Char(input, i);

        // Check if adding this would exceed memory limit
        if (decoded.size() + (size_t)(ch.length() * count) > maxSize)
        {
            break; // Stop decoding if output would be too large
        }

        // Efficiently repeat the character in smaller chunks
        if (count > 0)
        {
            const long long chunkSize = 10000;
            while (count > chunkSize)
            {
                string chunk;
                chunk.reserve(ch.length() * chunkSize);
                for (long long j = 0; j < chunkSize; j++)
                    chunk += ch;
                decoded += chunk;
                count -= chunkSize;
            }
            // Append remaining
            for (long long j = 0; j < count; j++)
                decoded += ch;
        }
    }

    return decoded;
}