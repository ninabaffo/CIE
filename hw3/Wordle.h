// Name: Nina Baffo
// Date: Sep 18th, 2022
// FileName: Wordle.h
// Description: Here is where the methods implemented in the Wordle class are created.

#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#ifndef HW3_WORDLE_H
#define HW3_WORDLE_H

class Wordle {
public:
    Wordle();                               // Call constructor
    string getFilename() const;             // Getter method for filename
    void setFilename(string filein);        // Setter method for filename
    vector<string> loadWordList();          // Implementing loadWordList() method to get list of words from file.
    void setRandomSecretWord();             // Setter method for random secret word
    string getRandomSecretWord();           // Getter method for random secret word
    int getGuessNum () const;               // Getter method for guessNum
    bool makeGuess(string userGuess);       // makeGuess method which returns true if guess matches secret word or false if otherwise.
    void print();
    void printAvailableLetters();           // this method prints the letters that have not been guessed yet

private:
    string wordListFilename;                // Holds the filename of a file that contains a list of all valid words.
    vector<string> wordList;                // Empty vector of strings
    string secretWord;                      // This string holds the secret word to guess.
    int guessNum;                           // number of guesses
    vector<string> guess;                   // list of previous guesses
    vector<string> feedback;                // list of feedback strings
    vector<string> tempString;              // list of feedback strings appended
    bool availableLetter[26];               // array that holds "available letters"
};

#endif //HW3_WORDLE_H
