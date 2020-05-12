//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Abhishek Panhale on 18/02/19.
//  Copyright © 2019 Abhishek Panhale. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp
#pragma once
#include <stdio.h>
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 bulls = 0;
    int32 cows = 0;
};

enum class EGuessStatus
{
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_String,
    Not_Lowercase,
    Invalid_Status
};


class  FBullCowGame
{
public:
    FBullCowGame();
    
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    bool isGameWon() const;
    EGuessStatus checkGuessValidity(FString);
    
    void reset();
    
    //counts bulls and cows, and increases try # assuming valid guess
    FBullCowCount submitValidGuess(FString);
    
private:
    int32 myCurrentTry;
    FString myHiddenWord;
    bool bGameIsWon;
    
    bool isIsogram(FString) const;
    bool isLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
