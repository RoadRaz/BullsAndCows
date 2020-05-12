//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Abhishek Panhale on 18/02/19.
//  Copyright © 2019 Abhishek Panhale. All rights reserved.
//
#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
    reset();
}

int32 FBullCowGame::getCurrentTry() const{ return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const{ return (int32)myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::getMaxTries() const
{
    TMap<int32, int32> wordToLength{ {3,5},{5,12},{6,15},{7,18} };
    return wordToLength[(int32)myHiddenWord.length()];
}

void FBullCowGame::reset()
{
    const FString HIDDEN_WORD = "planet";
    //TMap<int32, FString> lengthToWord { {3,"air"},{5,"pixel"},{6,"planet"},{7,"backlog"} };
    
    myCurrentTry = 1;
    myHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString EGuess)
{
    if(!isIsogram(EGuess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if(EGuess.length() != getHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else if(!isLowercase(EGuess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else
    {
        return EGuessStatus::OK;
    }
    
    
}

//receives a valid guess, increments turn and returns counts
FBullCowCount FBullCowGame::submitValidGuess(FString fGuess)
{
    myCurrentTry++;
    FBullCowCount BullCowCount;
    
    int32 WordLength = (int32)myHiddenWord.length(); //assuming same length as guess
    
    //loop through all letters in the hidden word
    for(int MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        //compare letter with the guess
        for(int GChar = 0; GChar < WordLength; GChar++)
        {
            if(fGuess[GChar] == myHiddenWord[MHWChar])
            {
                //increment bulls if they are in the correct position
                if (MHWChar == GChar)
                {
                    BullCowCount.bulls++;
                }
                //increment cows if they are not in correct position
                else
                {
                    BullCowCount.cows++;
                }
            }
        }
    }
    if(BullCowCount.bulls == getHiddenWordLength())
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::isIsogram(FString fGuess) const
{
    // treat 0 and 1 letter words as isogram
    if(fGuess.length() <= 1){ return true; }
    
    //setup our map
    TMap<char, bool> LetterSeen;
    
    for (auto Letter : fGuess) // for all letters in fGuess
    {
        Letter = tolower(Letter); // handle mixed case
        //if the letter is in the map
        if(LetterSeen[Letter] == true)
            {
                // we do not have isogram
                return false;
            }
        else
            {
                LetterSeen[Letter] = true;
            }
    }
    return  true;
}

bool FBullCowGame::isLowercase(FString fGuess) const
{
    for(auto Letter : fGuess)
    {
        if(!islower(Letter))
            return false;            
    }
    return true;
}

