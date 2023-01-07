#include <iostream>
#include <string>
#include <fstream> 
#include <streambuf>
using namespace std;


string shift_Decrypt(string txt, int k) {

    string temp = "";

    for (int i = 0; i < txt.size(); i++) {
        char ch = txt.at(i);
        ch = ((ch - 'A') - k + 26) % 26 + 'A';
        temp += ch; 
    }

    return temp; 

}

int main()
{
    // create file variables
    ifstream file;
    file.open("56143c5d_cc.txt");

    if (!file.is_open()) {
        cout << "Error opening input file \n" ;
        return 1;
    }

    //stores file into string using file iterator that points to the beginning, and char iterator that points to end()
    string encryptedText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
   
    file.close(); 

    string plainText = shift_Decrypt(encryptedText, 14);

    cout << plainText << '\n'; 

    return 0;
}
