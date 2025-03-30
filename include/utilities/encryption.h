#pragma once

#include <string>

using namespace std;

class Encrypt
{
public:
    static Encrypt& getInstance(){
        static Encrypt instance;
        return instance;
    }
    string encryptDecrypt(const string &text, char key)
    {
        string result = text;
        for (char &c : result)
        {
            c ^= key; // XOR each character with the key
        }
        return result;
    }
private:
    Encrypt() {};
};
