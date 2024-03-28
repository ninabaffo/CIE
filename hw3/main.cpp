// Name: Nina Baffo
// Date: Sep 18th, 2022
// FileName: hw3.cpp
// Description: Writing/using C++ classes, splitting up programs into multiple files, problem solving, and creating the game Wordle.

#include "Wordle.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std; 

// The main program has the responsibility of creating objects and responding to user input.
int main() {
    Wordle wordle;
    wordle.setFilename("wordList.txt");
    wordle.loadWordList();

    // instructions for WORDLE game
    cout << "Guess the WORDLE in 6 tries. " << endl;
    cout << "Each guess must be a 5-letter word. Hit the enter button to submit."<< endl;
    cout << "After each guess, you will get feedback to how close your guess was to the word."<< endl;
    cout << "! is the correct letter in the correct spot."<< endl;
    cout << "+ is the correct letter in the wrong spot."<< endl;
    cout << ". is a letter that does not appear in the word.\n" << endl;

    Wordle myObject;                            // Instantiate a Wordle object.
    myObject.loadWordList();                    // Load the valid word list into the object.
    myObject.setRandomSecretWord();             // Set a random word for the game 
    int guessNumber = 0;                        // initialize guess num to 0 before the start of the game

    while ( guessNumber <= 5) {
        string usersGuess;
        cout << "Enter guess: " << endl;
        cin >> usersGuess;
        myObject.makeGuess(usersGuess);

        myObject.print();                       // after each guess, the program should print the list of guesses & associated feedback.
        myObject.printAvailableLetters();       // also print letters still available to guess

        if (usersGuess == myObject.getRandomSecretWord()) {
            cout << "Congratulations, you won!" << endl;
            guessNumber = 6;
        } 
        if (usersGuess != myObject.getRandomSecretWord()) {
            if (guessNumber == 5) {
                cout << "Sorry, you lost. The secret word is: " << myObject.getRandomSecretWord() << endl;
            }
        }
        guessNumber += 1;
    }
    return 0;
}

