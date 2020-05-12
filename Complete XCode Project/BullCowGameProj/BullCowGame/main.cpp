//
//  main.cpp
//  BullCowGame
//
//  Created by Abhishek Panhale on 28/01/19.
//  Copyright © 2019 Abhishek Panhale. All rights reserved.
//

#pragma once
#include <iostream>
#include "FBullCowGame.hpp"

//To make syntax Unreal friendly
using FText = std::string;
using int32 = int;


//Function protoypes as outside a class
void printIntro();
FText getValidGuess();
void playGame();
bool askToPlayAgain();
void printGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// entry point for our game
int32 main() {
    do
    {
        printIntro();
        playGame();
    }while(askToPlayAgain());
    return 0;
}
// exit the game

//Introduce the game
void printIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "                  }   {         ___" << std::endl;
    std::cout << "                  (o o)        (o o)" << std::endl;
    std::cout << "   / - - - - - - - \\ /          \\ / - - - - - - -\\" << std::endl;
    std::cout << "  /  |  BULL      | O            O |      COW  |  \\ " << std::endl;
    std::cout << " *   | - , - - -  |                | - - -vvv- |   *" << std::endl;
    std::cout << "     |            |                |           |" << std::endl;
    std::cout << "     ^            ^                ^           ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

//Plays a single game till completion
void playGame()
{
    BCGame.reset();
    //loop asking for guesses while the game is NOT won
    //and there are still tries remaining
    while(!BCGame.isGameWon() && BCGame.getCurrentTry() <= BCGame.getMaxTries())
    {
        FText guess = getValidGuess();
        
        //submit a valid guess and reveive count of bulls/cows
        FBullCowCount BullCowCount = BCGame.submitValidGuess(guess);
        //print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.bulls << " Cows = " << BullCowCount.cows << "\n\n";
    }
    
    printGameSummary();
}

//loop continuously until the user gives a valid guess
FText getValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText fGuess = "";
    do
    {
        std::cout << "Try " << BCGame.getCurrentTry() << " of " << BCGame.getMaxTries() << ". Enter your guess: ";
        getline(std::cin, fGuess);
        Status =  BCGame.checkGuessValidity(fGuess);
        switch (Status)
        {
            case EGuessStatus::Not_Isogram:
                std::cout << "ERROR: Please enter a word without repeating letters.\n\n";
                break;
            case EGuessStatus::Wrong_Length:
                std::cout << "ERROR: Please enter a " << BCGame.getHiddenWordLength() << " letter word!\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "ERROR: Please enter lowercase letters.\n\n";
                break;
            case EGuessStatus::Not_String:
                std::cout << "ERROR: Please enter only alphabetical letters.\n\n";
                break;
            default:
                break;
        }
    }while(Status != EGuessStatus::OK);
    return fGuess;
}

//Ask to play again
bool askToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/n)\n";
    FText response = "";
    getline(std::cin, response);
    std::cout << std::endl;
    return (response[0] == 'Y') || (response[0] == 'y');
}

//Print game summary
void printGameSummary()
{
    if(BCGame.isGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n\n";
    }
    else
    {
        std::cout << "YOU LOSE - Better luck next time!\n\n";
    }
}
