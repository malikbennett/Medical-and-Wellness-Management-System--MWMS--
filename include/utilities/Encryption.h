#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Singleton Class which Handles basic XOR Enryption
class Encrypt
{
public:
    // Returns an instance of Encrypt Class which belongs to the class itself
    static Encrypt &getInstance()
    {
        static Encrypt instance;
        return instance;
    }
    // Read the key from a file
    void readKeyFromFile(const string &filePath, string &key)
    {
        try
        {
            ifstream keyFile(filePath);
            if (!keyFile)
            {
                throw runtime_error("Key failed to open");
            }
            getline(keyFile, key);
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    // Returns Encrypted input using XOR Encryption | Returns In HEX Format
    string xorEncryptDecrypt(const string &input, const string &key)
    {
        if (key.empty()) {
            throw invalid_argument("Encryption key cannot be empty.");
        }
        string output = input;
        for (size_t i = 0; i < input.size(); ++i)
        {
            output[i] ^= key[i % key.size()]; // Loop through the key
        }
        return toHex(output);
    }
    // Converts input to HEX format | Returns HEX Format
    string toHex(const string &input)
    {
        ostringstream oss;
        for (unsigned char c : input)
        {
            oss << hex << setw(2) << setfill('0') << (int)c;
        }
        return oss.str();
    }

private:
    Encrypt() {};
};
