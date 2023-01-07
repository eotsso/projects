#include <iostream>
#include <string>
#include <fstream> 
#include <streambuf>
using namespace std;

//Affine cypher decryption without knowing the initial 'a' or 'b' values in f(c) = ax + b

/*
So we need to determine both the alpha and beta value without knowing the initial encryption formula. 
One way to do this is to use a plaintext attack. It was explictedly stated that these
files were obtained from PROJECT GUTENBERG and the text was modified to be all upper-case and devoid of space characters. 

A quick peek at the universal format for ebooks in gutenberg.org begins with "THEPROJECTGUTENBERGEBOOK". 
Therefore, we will map the encrypted text to the plaintext to figure out the 'a' and 'b' parameters for an 
affine cipher decryption. 

Basically, I solved for 'a' and 'b' using linear combination. Then I used 'a' to find the inverse of 'a', which gave me 
my parameters to decrypt the message. 

*/
 
string Affine_Decrypt(string txt, int aInverse, int b) {

    string temp = "";

    for (int i = 0; i < txt.size(); i++) {
        char ch = txt.at(i);

        ch = ch - 'A'; 
        ch = ((aInverse * (ch - b)) % 26);

        // makeshift modulo operation because trouble with negative modulo operations
        while (ch < 0) { ch += 26; }

        ch = ch + 'A';
        
        temp += ch;  
   
    }

    return temp; 

}

int main()
{
    // create file variables
    ifstream file;
    file.open("3d2680ae_ae.txt");

    if (!file.is_open()) {
        cout << "Error opening input file \n" ;
        return 1;
    }

    //file iterator that points to the beginning, and char iterator that points to end()
    string encryptedText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    file.close(); 

    //Calls Affine_Decrypt, parameters can be determined either via brute force or plaintext attack
    //NOTE: parameter 'a' is the modulo 26 inverse of the original encryption key for 'a'
    string plainText = Affine_Decrypt(encryptedText, 11, 7);

    cout << plainText << '\n'; 

    return 0;

}
