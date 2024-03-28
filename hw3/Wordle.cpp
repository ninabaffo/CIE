// Name: Nina Baffo
// Date: Sep 18th, 2022
// FileName: Wordle.cpp
// Description: Here is where all the methods crated in the Wordle.h file are told what to do.
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Wordle.h"

using namespace std;

// Description: This function instantiates the Wordle class and sets the input string from main to the 
//              private variable or to the default string "".
// Inputs:      None
// Output:      The private string wordListFilename is set to filein and availableLetter set to true
Wordle::Wordle(){
    wordListFilename = "wordList.txt";           // defualt filename
    availableLetter[25] = true;                // initialize this array to all true.
}
// Description: This function sets the file name to the name that is inputted in main
// Inputs:      String filein
// Output:      There is no output but the private string wordListFilename is set to filein.
void Wordle::setFilename(string filein){wordListFilename = filein;}

// Description: Opens the file specified by the user in setFileName, counts the number of words in 
//              the file and sets the size for the vector string wordList.            
// Inputs:      None
// Output:      vector<string> secretWord is returned with a size of the number of words in worList.txt.
vector <string> Wordle::loadWordList(){
    ifstream fin(wordListFilename);
    if (fin.fail()){                                // If file fails to open:
        cout << "Error: could not open " << wordListFilename << endl;
    }

    int numWords = 0;
    string listTemp;
    while (!fin.eof()) {                            // read the list & count the number of words into numWords
        getline(fin, listTemp, '\n');
        numWords++;
    }

    wordList.resize(numWords);                      // use vector resize method to allocate the required number of strings.
    fin.clear();                                    // use fin.clear(); to clear the end of file flag,
    fin.seekg(0, fin.beg);                          // return the file reading to the start of the file

    string wordlistTemp;
    for (int i = 0; i <= numWords; i++){            // read in and store each word in wordList.
        getline(fin, wordlistTemp, '\n');
        wordList[i] = wordlistTemp;
    }
    return wordList;
}

// Description: This function sets a random word to be the secret Wordle word.
// Inputs:      None.
// Output:      No output but the secretWord is set to a random word from the wordList.
void Wordle::setRandomSecretWord(){
    secretWord = wordList[rand() % wordList.size() -1];
}

// Description: This function retrieves the random secret word.
// Inputs:      None.
// Output:      Secret word is obtained.
string Wordle::getRandomSecretWord() {return secretWord;}

// Description: Called in main to see what number guess the user is on
// Inputs:      None
// Output:      Returns an int guessNum with the number guess the user is on
int Wordle::getGuessNum() const {return guessNum;}


// Description: Takes the userGuess for the secretWord. It will notify user if guess is not in word list or guess 
//              is not 5 characters. It will also tell the user feedback for their upcoming guesses.
// Inputs:      String userGuess is the users guess for secretWord.
// Output:      True is outputted if the userGuess == secretWord and false is outputted if otherwise.
bool Wordle::makeGuess(string userGuess) {
    fill(feedback.begin(), feedback.end(), ".");           // restart feedback string with all "."
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    //check if userGuess is in wordlist.txt.
    if (find(wordList.begin(), wordList.end(), userGuess) == wordList.end()) {
        cout << "Error: " + userGuess + " is not in the wordlist. Please make another guess. " << endl;
        return false;
    }
    else { // check if the userGuess is a valid 5-character word & has more guesses
        if (userGuess.size() == 5 && guessNum < 6) { 
            guess.push_back(userGuess); // word added to the guess vector
            guessNum += 1;

            // if it is a valid word, check if the user guessed correctly 
            if (userGuess == secretWord){
                return true;
            }
            string secretWordTemp = secretWord; // copy of the secret word
            vector <string> feedbackTemp;
            // Compare the guess character-by-character with copy of the secret word.
            for (int i = 0; i<=4; i++){
                if (userGuess[i] == secretWordTemp[i]) {
                    feedback[i] = "!";
                    secretWordTemp[i] = '-';
                }
            }
            string tempString2[] = {};
            for (int j = 0; j <= 4; j++) {
                tempString2[j] += feedback[j];
            }
            for (int j = 0; j <= 4; j++) {
                if (tempString2[j] != "!") {
                    for (int m = 0; m <= 26; m++){
                        if (userGuess[m] == secretWordTemp[m]) {
                            secretWordTemp[m] = '-';
                            feedback[m]= '+';
                        }
                    }
                    availableLetter[alphabet.find(userGuess[j])] = "1";
                }
            }
        }
        // if size not correct &/or too many guesses
        cout << "Game over. The correct secret word is " + secretWord << endl;
        return false;
    }
    return false;
}

// Description: This function is used in main to print the users guesses and feedback about them.
// Inputs:      None.
// Output:      vector<string> guess with the words the user has already guesses
//              vector<string> feedback about the guesses are printed.
void Wordle::print() {
    string tempString2;
    for (int j = 0; j <= 4; j++) {
        tempString2 += feedback[j];
    }
    tempString.push_back(tempString2);
    for (int i = 0; i < guessNum; i++){
        cout << i+1 << ": " << guess[i] << " " << tempString[i] << endl;
    }
}

// Description: This function is used in main to print the available letters to guess
// Inputs:      None.
// Output:      a string with the available letters
void Wordle::printAvailableLetters() {
    string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s",
                         "t", "u", "v", "w", "x", "y", "z"};
    string tempString2;

    for (int i = 0; i <= 25; i++) {
        if (availableLetter[i] != 1) {
                tempString2 += alphabet[i];
            }
        }
    cout << "Available letters to guess: " << tempString2 << endl;
}