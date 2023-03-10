#include <iostream>
#include <string>
#include <fstream> 
#include <vector> 
#include <algorithm>
#include <queue>
using namespace std;

/*
  First, if the key length is unknown. You can run the encrypted text through the 'coincidence()' function to determine the key
  manually. 

  Then, you can use the key length to determine the key used in the Vigenere cipher using 'getVE_key()' 
  - This is done using freqency analysis.

  Finally, the text, key, and keylength (coincidence), are passed into 'VE_Decrypt()' to decode the text. 

   Usually key length is determined because manual decryption will take too long. So alterantively, this problem can just brute-force
   the key length (coincidence) parameter, and the result can be manually inspected. 
*/

void coincidence(string); 
string getVE_key(string, int);
string VE_Decrypt(string, string, int);

int main()
{
    // create file variables
    ifstream file;
    file.open("e12e9445_ve.txt");
    if (!file.is_open()) {
        cout << "Error opening input file \n" ;
        return 1;
    }

    //file iterator that points to the beginning, and char iterator that points to end()
    string encryptedText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close(); 

    //USE coincidence() FIRST TO DETERMINE KEY LENGTH. UNCOMMENT IT OUT WHEN NEEDED. 
    //coincidence(encryptedText); 

    //PASS THE ENCRYPTED TEXT AND KEY LENGTH INTO VE_Decrypt
    string VE_key = getVE_key(encryptedText, 5);
    cout << "The key used for this Vigenere Cipher is: " << VE_key << endl;
    
    string plainText = VE_Decrypt(encryptedText, VE_key, 5);
    cout << "The decrypted text for this Vigenere Cipher is:\n" << plainText; 

    return 0;
}


//Use this function to find keylength manually.  
void coincidence(string txt) {
    for (int j = 0; j < txt.length(); j++) {
        int counter = 0;
        for (int i = 0; i < txt.length() - i; i++) {
            char ch1 = txt.at(1 + i + j);
            char ch2 = txt.at(0 + i);

            if (ch1 == ch2) {
                counter++; 
            }
        }
       cout << "Coincidences: " << counter << endl;  
    }
}

//Take in the encrypted text, and a known key length, and outputs the decrypted message using freqency analysis 
string getVE_key(string encryptedText, int coincidenceVal) {
    
    //Variable is used to store and return the output VE_Key 
    string VE_key = ""; 
    
    int counterVal = 0; 
    while (counterVal != coincidenceVal) { 

        //Take the encryptedText and take every 5th letter, and determine the frequency which each alphabet occurs. 
        int encryptedFrequency[26] = {0}; 
        string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

        //Loops through encrypted text one at a time, and finds the position by comparing char with the position located in the string
        //This for-loop increments every 5 spaces because the coincidence (key length) found earlier was 5 (I'm assuming key length = 5)  
        for (int i = counterVal; i < encryptedText.size(); i+=coincidenceVal) { 
            char ch = encryptedText.at(i); 
            int pos = ALPHABET.find(ch);
        //Increments the position A = 0, ..., Z = 25 if character is found. 
            if (pos != string::npos) {
                encryptedFrequency[pos]++;
            }
        }

        //Determine the relative frequencies for every 5th character including the 0th character.
        //FIXME:: I was thinking in this case, we could just divide the total text size by 5. 
        int totalLetters = 0; 
        for (int i = 0; i < 26; i++) {
        totalLetters += encryptedFrequency[i];  
        }

        //Stores the decimal values of alphabet freqencies found in the encrypted text (for every 5th element) 
        double encryptedFreqencyList[26];
        for (int i = 0; i < 26; i++) {
            encryptedFreqencyList[i] = (double)encryptedFrequency[i] / totalLetters; 
        }

        //Data retrieved from https://cs.wellesley.edu/~fturbak/codman/letterfreq.html
        vector<double> englishAlphabetFrequency = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 
        0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 
        0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

        //calculatedArray stores the encryptedFrequencyList * englishAlphabetFrequency. This is to find the part of the key. After the highest value is determined 
        //2D array is required to store all the multipled freqencies with the shifts 
        int ROW = 26;
        int COL = 26;
        double calculatedArray[ROW][COL]; 

        for (int j = 0; j < 26; j++) {
            for (int i = 0; i < 26; i++) {
                calculatedArray[j][i] = encryptedFreqencyList[i] * englishAlphabetFrequency.at(i); 
            }
            //need to shift the frequencies. due to implementation, im shifting going to bring the last element to the front and delete the last element 
            double temp = englishAlphabetFrequency.back();              
            englishAlphabetFrequency.insert(englishAlphabetFrequency.begin(), temp); //inserts at front
            englishAlphabetFrequency.pop_back(); 
        }
        
    
        //Find the largest value value in each row for the 2D array. Then stores each value into a 1D array. 
        double finalArrayCalculation[26];
        for (int j = 0; j < 26; j++) {
            double sum = 0;  
            for (int i = 0; i < 26; i++) {
                sum += calculatedArray[j][i];
            }
            finalArrayCalculation[j] = sum;
        }
        

        //Finds the row that is the correct shift key (the highest value in the array corresponds to the correct # of shifts)
        int posOfHighestFrequencyShift = 0; 
        double max = finalArrayCalculation[0];
        for (int i = 1; i < 26; i++) {
            if (finalArrayCalculation[i] > max) {
                max = finalArrayCalculation[i];
                posOfHighestFrequencyShift = i; 
            }
        }

        
        char shiftKey = posOfHighestFrequencyShift + 65;
        VE_key += shiftKey;    
        
        counterVal++; 

    }

    return VE_key;
}

string VE_Decrypt(string txt, string key, int keyLength) {

    string temp = "";

    int i = 0; 
    while (i < txt.size() - 4) {
        //Inner loops through the key size amount. The key will loop 0 to 4, while the i iterates at the same time with j. 
        int j = 0; 
        while (j < keyLength) {
            char ch = txt.at(i);      //iterates through entire string
            char k = key.at(j);       //repeats through the key for a VE_cipher 
            ch = ((ch - k + 26)) % 26; 
            while (ch < 0) { ch += 26; }
            ch = ch + 'A';
            temp += ch; 
            j++;
            i++; 
        }
    }
    return temp; 

}
