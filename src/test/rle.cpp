#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
using namespace std;

// Helper function to extract UTF-8 character from string at position
string getUTF8Char(const string &str, size_t &pos)
{
    if (pos >= str.size())
        return "";

    unsigned char byte = str[pos];
    string result;
    int charLen = 1;

    // Determine character length based on first byte
    if ((byte & 0x80) == 0)
        charLen = 1; // ASCII
    else if ((byte & 0xE0) == 0xC0)
        charLen = 2;
    else if ((byte & 0xF0) == 0xE0)
        charLen = 3;
    else if ((byte & 0xF8) == 0xF0)
        charLen = 4;

    // Extract the character
    for (int i = 0; i < charLen && pos < str.size(); i++, pos++)
    {
        result += str[pos];
    }

    return result;
}

// Count the number of actual UTF-8 characters (not bytes)
size_t countUTF8Chars(const string &str)
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

string rleEncode(const string &input)
{
    if (input.empty())
        return "";

    string encoded = "";
    size_t i = 0;
    string currentChar = getUTF8Char(input, i);
    int count = 1;

    while (i < input.size())
    {
        string nextChar = getUTF8Char(input, i);
        if (nextChar == currentChar)
        {
            count++;
        }
        else
        {
            encoded += to_string(count) + currentChar;
            currentChar = nextChar;
            count = 1;
        }
    }

    // Add the last run
    encoded += to_string(count) + currentChar;

    return encoded;
}

int main()
{
// Set locale to UTF-8 for proper character handling
#ifdef _WIN32
    setlocale(LC_ALL, ".UTF8");
#else
    setlocale(LC_ALL, "en_US.UTF-8");
#endif

    string input;

    cout << "Ingrese la cadena a codificar: ";
    getline(cin, input); // Read entire line including spaces

    string encoded = rleEncode(input);

    cout << "\nCadena original: " << input << "\n";
    cout << "Cadena codificada: " << encoded << "\n";

    // Count actual UTF-8 characters, not just bytes
    size_t originalChars = countUTF8Chars(input);
    size_t originalBytes = input.size();
    size_t encodedBytes = encoded.size();

    cout << "\nTamaño original: " << originalChars << " caracteres (" << originalBytes << " bytes)\n";
    cout << "Tamaño codificado: " << encodedBytes << " bytes\n";

    if (encodedBytes < originalBytes)
    {
        cout << "Resultado: Compresión positiva" << "\n";
    }
    else if (encodedBytes > originalBytes)
    {
        cout << "Resultado: Compresión negativa" << "\n";
    }
    else
    {
        cout << "Resultado: No hubo compresión" << "\n";
    }

    return 0;
}