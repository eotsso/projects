#include <iostream>
#include <string>
#include <fstream> 
#include <vector> 
#include <algorithm>
#include <queue>
using namespace std;


//Trying to find the key length 
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
void VE_Decrypt(int coincidenceVal) {
 //Take the encryptedText and take every 5th letter, and determine the frequency which each alphabet occurs. 
    int encryptedFrequency[26] = {0}; 
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

    //Loops through encrypted text one at a time, and finds the position by comparing char with the position its located in the string
    //This for-loop increments every 5 spaces because the coincidence found earlier was 5 (I'm assuming key length = 5)  
    for (int i = 0; i < encryptedText.size(); i+=5) { 
        char ch = encryptedText.at(i); 
        int pos = ALPHABET.find(ch);
    //Increments the position A = 0, ..., Z = 25 if character is found. 
        if (pos != string::npos) {
            encryptedFrequency[pos]++;
        }
    }

    //Determine the relative frequencies for every 5th character including the 0th character.
    //I was thinking in this case, we could just divide the total text size by 5. 
    int totalLetters = 0; 
    for (int i = 0; i < 26; i++) {
       totalLetters += encryptedFrequency[i];  
    }
    cout << "LINE 68 Total Letters: " << totalLetters << endl; 

    //Stores the decimal values of alphabet freqencies found in the encrypted text (for every 5th element) 
    double encryptedFreqencyList[26];
    for (int i = 0; i < 26; i++) {
        encryptedFreqencyList[i] = (double)encryptedFrequency[i] / totalLetters; 
    }

    for (double x : encryptedFreqencyList) {
        cout << "LINE 77 EncryptedFrequencylist after dividing: " << x << " " << endl;
    }

    //Data retrieved from https://cs.wellesley.edu/~fturbak/codman/letterfreq.html
    //Double data types don't give exact representation of decimal values--so this might be a problem. 
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
    
   
    //Find the largest value value in each row, and the largest value in that row is the correct shift key. 
    double finalArrayCalculation[26];
    for (int j = 0; j < 26; j++) {
        double sum = 0;  
        for (int i = 0; i < 26; i++) {
            sum += calculatedArray[j][i];
        }
        finalArrayCalculation[j] = sum;
    }
    
    for (double x : finalArrayCalculation) {
        std::cout << "LINE 116: finalArrayCalculations: " << x << " " << endl;
    }

    //Finds the row that is the correct shift key
    int posOfHighestFrequencyShift = 0; 
    double max = finalArrayCalculation[0];
    for (int i = 1; i < 26; i++) {
        if (finalArrayCalculation[i] > max) {
            max = finalArrayCalculation[i];
            posOfHighestFrequencyShift = i; 
        }
    }
    
    cout <<"LINE 131: The shift key is: ...! " << posOfHighestFrequencyShift << endl;
    char shiftKey = posOfHighestFrequencyShift + 65;
    cout << "The char associated is: " << shiftKey << endl;
}
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

    //From this function, I determined the key length = 5, probably. 
    //coincidence(encryptedText); 

    //Take the encryptedText and take every 5th letter, and determine the frequency which each alphabet occurs. 
    int encryptedFrequency[26] = {0}; 
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

    //Loops through encrypted text one at a time, and finds the position by comparing char with the position its located in the string
    //This for-loop increments every 5 spaces because the coincidence found earlier was 5 (I'm assuming key length = 5)  
    for (int i = 0; i < encryptedText.size(); i+=5) { 
        char ch = encryptedText.at(i); 
        int pos = ALPHABET.find(ch);
    //Increments the position A = 0, ..., Z = 25 if character is found. 
        if (pos != string::npos) {
            encryptedFrequency[pos]++;
        }
    }

    //Determine the relative frequencies for every 5th character including the 0th character.
    //I was thinking in this case, we could just divide the total text size by 5. 
    int totalLetters = 0; 
    for (int i = 0; i < 26; i++) {
       totalLetters += encryptedFrequency[i];  
    }
    cout << "LINE 68 Total Letters: " << totalLetters << endl; 

    //Stores the decimal values of alphabet freqencies found in the encrypted text (for every 5th element) 
    double encryptedFreqencyList[26];
    for (int i = 0; i < 26; i++) {
        encryptedFreqencyList[i] = (double)encryptedFrequency[i] / totalLetters; 
    }

    for (double x : encryptedFreqencyList) {
        cout << "LINE 77 EncryptedFrequencylist after dividing: " << x << " " << endl;
    }

    //Data retrieved from https://cs.wellesley.edu/~fturbak/codman/letterfreq.html
    //Double data types don't give exact representation of decimal values--so this might be a problem. 
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
    
   
    //Find the largest value value in each row, and the largest value in that row is the correct shift key. 
    double finalArrayCalculation[26];
    for (int j = 0; j < 26; j++) {
        double sum = 0;  
        for (int i = 0; i < 26; i++) {
            sum += calculatedArray[j][i];
        }
        finalArrayCalculation[j] = sum;
    }
    
    for (double x : finalArrayCalculation) {
        std::cout << "LINE 116: finalArrayCalculations: " << x << " " << endl;
    }

    //Finds the row that is the correct shift key
    int posOfHighestFrequencyShift = 0; 
    double max = finalArrayCalculation[0];
    for (int i = 1; i < 26; i++) {
        if (finalArrayCalculation[i] > max) {
            max = finalArrayCalculation[i];
            posOfHighestFrequencyShift = i; 
        }
    }
    
    cout <<"LINE 131: The shift key is: ...! " << posOfHighestFrequencyShift << endl;
    char shiftKey = posOfHighestFrequencyShift + 65;
    cout << "The char associated is: " << shiftKey << endl;

    //string plainText = VE_Decrypt(encryptedText, 11, 7);

    //cout << plainText << '\n'; 

    return 0;

}
