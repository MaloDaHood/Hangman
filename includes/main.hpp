/**
 * @file main.hpp
 * @author Malo Massieu Rocabois
 * @brief Header file for my hangman game
 * @version 0.1
 * @date 2022-01-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

std::string askForSecretWord();
char makeGuess();
bool isGuessInWord(char const &guess, std::string const &word);
void compareGuessToWord(char const &guess, std::string const &word, std::string &guessedWord);
void addMissedGuess(char const &guess, std::vector<char> &misses);
void display(std::string const &guessedWord, char const &guess, std::vector<char> misses, size_t const &guessesLeft);
bool isGameOver(std::string const &guessedWord, size_t const &guessesLeft);
bool playAgain();
void clearBuffer();