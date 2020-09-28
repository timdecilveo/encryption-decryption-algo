/*
Name: Tim Decilveo
SSID: 1841381
Assignment #: 2
Submission Date: 10/3/2020
Email Address: decilveo_timothy_jos@student.smc.edu

Description:
    - A program to encrypt and decrypt a message using a shift cipher
    - The plaintext message must contain lowercase or uppercase alpha, digits 0-9,  and '@' or '$'
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <typeinfo>

using namespace std;

const int CBL = 64; //Code Book Length constant

void encrypt(string& plaintext, int k);
void decrypt(string& ciphertext, int k);
void copy_string(string& s, char* text);

char codebook [] = {'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G',
                    'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N',
                    'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U',
                    'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z',
                    '0', '1', '2','3','4','5','6','7','8','9', '@', '$'};
string ad_converted {codebook}; // convert the char array to a string

int main(int argc, char* argv[]){
    cout << " ------- Begin Command Line Arguments ------- " << endl;

    int k = -1; // k shift
    int msg_index = 0; // msg_index of plaintext or ciphertext in argv
    string msg; // string to hold the plaintext or ciphertext
    bool do_encrypt = false; // True for encrypt or False for decrypt
    bool do_decrypt = false; // True for decrypt or False for encrypt


    for(int i = 1; i < argc; i++){
        //tests for the -p value in the command line argument
        if(strcmp(argv[i], "-p") == 0){
            msg = argv[++i];
        }
        //tests for the -C value in the command line argument
        if(strcmp(argv[i], "-C") == 0){
            msg = argv[++i];
        }
        //tests for the -k value in the command line argument
        if(strcmp(argv[i], "-k") == 0){
            k = atoi(argv[++i]);
        }
        //tests for the -E value in the command line argument
        if (strcmp(argv[i], "-E") == 0) {
            do_encrypt = true;
        }
        //tests for the -D value in the command line argument
        if (strcmp(argv[i], "-D") == 0) {
            do_decrypt = true;
        }
    }

    // Todo A2: copy argv into msg using copy_string function
    // not quite sure why this is needed at all; seems like a wasted function


    // QUESTION: how do i make the argv == '-p' or '-C'
    // Todo A2: call encrypt or decrypt functions
    if(do_encrypt && !msg.empty() && (k != -1)){
        encrypt(msg, k);
    }
    else if(do_decrypt && !msg.empty() && (k != -1)){
        decrypt(msg, k);
    }

    cout << endl;
    return 0;
}

/*
Todo A2: copy argv into msg using copy_string function
not quite sure why this is needed at all; seems like a wasted function
*/
void copy_string(string& s, char* text){
    cout << endl;
}

void encrypt(string& plaintext, int k){
    /************************ ENCRYPTION ************************
    To encrypt a plaintext string use the following formula to compute an
    index i into the codebook array:

        Ci = E(p) = (p + k) mod 36;
    
    where mod is the modulus operator %,
    C is the ciphertext,
    E is the encryption function,
    p is the index of the plaintext character,
    k is the key shift,
    36 is the length of the codebook array.
    ************************ ENCRYPTION ************************/

    string ciphertext {};

    for (char c: plaintext){
        size_t position = ad_converted.find(c); // this looks for the position of the character in the ad_converted string
        int plaintext_manipulator = (position + k) % CBL; // manipulates plaintext to ciphertext

        if(position != string::npos){ // this means we found the character
            char new_char {ad_converted.at(plaintext_manipulator)}; //need a new character from the ad_converted string
            ciphertext += new_char;
        }
        else{
            ciphertext += c;
        }
    }

    cout << "The plaintext was: " << plaintext << endl;
    cout << "The ciphertext is: " << ciphertext << endl;
    cout << "Enter any key to exit" << endl;
}


void decrypt(string& ciphertext, int k){
    /************************ DECRYPTION ************************
    To decrypt a ciphertext string use the following formula to compute
    an index i into the codebook array:

        pi = D(C) = (C - k) mod 36;                     (C - k) >= 0
        pi = D(C) = (((C - k) mod 36) + 36) mod 36;     (C - k) < 0

    where mod is the modulus operator %
    C is the index of the ciphertext character
    D is the decryption function
    p is the plaintext
    k is the key shift
    36 is the length of the codebook marray.
    ************************ DECRYPTION ************************/

    string plaintext {};

    for (char c: ciphertext){
        size_t position = ad_converted.find(c); // this looks for the position of the character in the ad_converted string
        int ciphertext_manipulator = (position - k) % CBL; // manipulates ciphertext to plaintext
        int ciphertext_manipulator_greater_than_0 = (position - k) % CBL; // manipulates ciphertext to plaintext if position - k > 0
        int ciphertext_manipulator_less_than_0 = (((position - k) % CBL) + CBL) % CBL; // manipulates ciphertext to plaintext if position - k < 0

        if(position != string::npos){ // this means you found the character
            char new_char {ad_converted.at(ciphertext_manipulator)}; //need a new character from the ad_converted string
            plaintext += new_char;
        }
        else{
            plaintext += c;
        }
    }
   
    cout << "The ciphertext was: " << ciphertext << endl;
    cout << "The plaintext is: " << plaintext << endl;
    cout << "Enter any key to exit" << endl;
}