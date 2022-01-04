/**
 * @file main.cpp
 * @author Malo Massieu Rocabois
 * @brief Source code for my hangman game
 * @version 0.1
 * @date 2022-01-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.hpp"

/**
 * @brief Entry point of the program, used to initialize all important variables and to connect all the other functions together.
 * 
 * @param argc Amount of command line arguments
 * @param argv Content of command line arguments, [0] == program name, [1] == secret word
 * @return int 
 */
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << '[' << argv[0] << "] - Error : Missing argument." << std::endl;
        return EXIT_FAILURE;
    }

    // The terminal is cleared so the player can't see the secret word
    system("clear");

    // The word the player has to find
    std::string const word {argv[1]};

    // Current state of what the player has found
    std::string guessedWord(word.length(), '_');

    // Wrong letters input by the player
    std::vector<char> misses;

    // Amount of guesses the player has left
    size_t guessesLeft {word.length() * 2};

    // Player's guess
    char guess;

    // Main game loop : Everything is repeated until the game is over
    do
    {
        guess = makeGuess();

        // If the player makes a good guess it is compared to the word to replace the '_' in the guessed word
        if(isGuessInWord(guess, word))
            compareGuessToWord(guess, word, guessedWord);

        // If the player is wrong, his guess is added to he miss list and his number of guesses left decreases
        else
        {
            addMissedGuess(guess, misses);
            guessesLeft--;
        }

        // The terminal is cleared just for looks
        system("clear");

        display(guessedWord, guess, misses, guessesLeft);

    } while(!isGameOver(guessedWord, guessesLeft));

    return EXIT_SUCCESS;
}

/**
 * @brief Displays everything the player needs to know between each of his guesses
 * 
 * @param guessedWord Current state of what the player has found
 * @param guess Player's last guess
 * @param misses Wrong letters input by the player
 * @param guessesLeft Amount of guesses the player has left
 */
void display(std::string const &guessedWord, char const &guess, std::vector<char> misses, size_t const &guessesLeft)
{
    std::cout << "Word : " << guessedWord << std::endl;
    std::cout << "Guess : " << (char)std::toupper(guess) << std::endl;
    std::cout << "Misses : ";
    for(char const &miss : misses)
    {
        std::cout << (char)std::toupper(miss) << ',';
    }
    std::cout << "\nNumber of guesses left : " << guessesLeft << std::endl;
}

/**
 * @brief Asks the player to make a guess
 * 
 * @return char
 */
char makeGuess()
{
    char guess;
    while(true)
    {
        std::cout << "Your guess : ";
        std::cin >> guess;
        if(std::cin.fail() || !std::isalpha(guess))
        {
            inputError();
            continue;
        }
        break;
    }
    return std::toupper(guess);
}

/**
 * @brief Checks if the player's guess is in the secret word
 * 
 * @param guess The player's last guess
 * @param word The secret word the player has to find
 * @return true If the player's guess in within the word
 * @return false Otherwise
 */
bool isGuessInWord(char const &guess, std::string const &word)
{
    return std::any_of(
        word.begin(), word.end(), 
        [guess](char const &letter) -> bool{
            return std::toupper(letter) == guess;
        }
    );
}

/**
 * @brief Replaces the '_' with the player's guess on the right spots compared to the secret word
 * 
 * @param guess The player's last guess
 * @param word The secret word the player has to find
 * @param guessedWord Current state of what the player has found
 */
void compareGuessToWord(char const &guess, std::string const &word, std::string &guessedWord)
{
    for(size_t i {0}; i < word.length(); i++)
    {
        if(guess == std::toupper(word[i]))
            guessedWord[i] = guess;
    }
}

/**
 * @brief Adds the player's guess in the list of wrong letters only if it was not already there
 * 
 * @param guess The player's last guess
 * @param misses Wrong letters input by the player
 */
void addMissedGuess(char const &guess, std::vector<char> &misses)
{
    if(misses.empty())
    {
        misses.push_back(guess);
        return;
    }
    else
        if(std::any_of(misses.begin(), misses.end(), [guess](char const &miss) -> bool{return guess == miss;}))
            return;
    misses.push_back(guess);
}

/**
 * @brief Checks if the guessed word is complete or if there are any guesses left
 * 
 * @param guessedWord Current state of what the player has found
 * @param guessesLeft Number of guesses left for the player to make
 * @return true If the game is over
 * @return false Otherwise
 */
bool isGameOver(std::string const &guessedWord, size_t const &guessesLeft)
{
    return !std::any_of(guessedWord.begin(), guessedWord.end(),[](char const &letter) -> bool{return letter == '_';})
            ||
            guessesLeft == 0;
}

/**
 * @brief Warns the player about an input error and clears the buffer 
 * 
 */
void inputError()
{
    std::cout << "You have to input only a letter." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}