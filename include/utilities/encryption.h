#pragma once

#include <string>

using namespace std;

// Singleton Class which Handles basic XOR Enryption
class Encrypt
{
public:
    // Returns an instance of Encrypt Class which belongs to the class itself
    static Encrypt& getInstance(){
        static Encrypt instance;
        return instance;
    }
    // Encrypt or Decrypy a text using a key with the XOR operator
    void encryptDecrypt(string &text, char key)
    {
        for (char &c : text)
        {
            c ^= key;
        }
    }
private:
    Encrypt() {};
};
