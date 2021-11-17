#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "sodium.h"
using namespace std;

int main()
{
    unsigned char* line = new unsigned char[450];
    ifstream myFile("C:/Users/D-ani/source/repos/ConsoleApplication1/txt.txt");
    //fstream myFile("txt.txt");
    if (myFile.is_open())
    {
        myFile.getline((char*)line, 450, '\0');
        myFile.close();
    }
    cout << line;
     
    if (sodium_init() < 0) {
        return -1;
    }

    // len de un char*
    int plainText_len = strlen((char*)line);

    unsigned char* cipherText = new unsigned char[plainText_len];
    unsigned char* decipherText = new unsigned char[plainText_len];

    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];

    // generador de claves
    crypto_secretbox_keygen(key);
    randombytes_buf(nonce, sizeof nonce);

    int errorCode = crypto_stream_chacha20_xor(cipherText, line, plainText_len, nonce, key);
    for (int i = 0; i < plainText_len; i++) {
        std::cout << std::setfill
        ('0') << std::setw(2) << std::hex << int(cipherText[i]);
    }
    std::cout << std::endl;
    return 0;
}