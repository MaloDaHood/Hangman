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

#include "../includes/main.hpp"

/**
 * @brief Entry point of the program, used to initialize all important variables and to connect all the other functions together.
 * 
 * @return int 
 */
int main(void)
{
    do
    {
        // The word the player has to find
        std::string const word {askForSecretWord()};

        // The terminal is cleared so the player can't see the secret word
        system("clear");

        // Current state of what the player has found
        std::string guessedWord(word.length(), '_');

        // Wrong letters input by the player
        std::vector<char> misses;

        // Amount of guesses the player has left
        size_t guessesLeft {word.length() * 2};

        // Main game loop : Everything is repeated until the game is over
        do
        {
            // Player's guess
            char guess = makeGuess();

            // If the player makes a good guess it is compared to the word to replace the '_' in the guessed word
            if(isGuessInWord(guess, word))
                compareGuessToWord(guess, word, guessedWord);

            // If the player is wrong, his guess is added to the miss list and his number of guesses left decreases
            else
            {
                addMissedGuess(guess, misses);
                guessesLeft--;
            }

            // The terminal is cleared just for looks
            system("clear");

            // All the current info are displayed
            display(guessedWord, guess, misses, guessesLeft);

        } while(!isGameOver(guessedWord, guessesLeft));

    } while(playAgain());

    return EXIT_SUCCESS;
}

/**
 * @brief Asks the game master for the secret word
 * 
 * @return std::string The uppercase secret word
 */
std::string askForSecretWord()
{
    std::string word;
    
    while(true)
    {
        std::cout << "Enter your secret word : ";
        std::cin >> word;
        if(word.length() <= 1
            ||
            std::any_of(word.begin(), word.end(), [](char const &letter) ->bool {
                return !std::isalpha(letter);
            })
        )
        {
            std::cout << "You have to input a word only with letters." << std::endl;
            clearBuffer();
            continue;
        }
        break;
    }
    std::for_each(word.begin(), word.end(), [](char &letter){letter = std::toupper(letter);});
    return word;
}

/**
 * @brief Asks the player to make a guess
 * 
 * @return char The uppercase player's guess
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
            std::cout << "You have to input only a letter." << std::endl;
            clearBuffer();
            continue;
        }
        clearBuffer();
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
            return letter == guess;
        }
    );
}

/**
 * @brief Replaces the '_' with the player's guess on the right spots compared to the secret word
 * 
 * @param guess The player's last guess
 * @param word The secret word the player has to find
 * @param guessedWord Current state of what the player has found, modifies it by reference
 */
void compareGuessToWord(char const &guess, std::string const &word, std::string &guessedWord)
{
    for(size_t i {0}; i < word.length(); i++)
    {
        if(guess == word[i])
            guessedWord[i] = guess;
    }
}

/**
 * @brief Adds the player's guess in the list of wrong letters only if it was not already there
 * 
 * @param guess The player's last guess
 * @param misses Wrong letters input by the player, modifies it by reference
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
 * @brief Asks the player if he wants to play again
 * 
 * @return true If the player wants to play again
 * @return false Otherwise
 */
bool playAgain()
{
    while(true)
    {
        unsigned short int choice;
        std::cout << "Do you want to play again ?\n1. YES\n2. NO" << std::endl;
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                return true;
            case 2:
                return false;
            default:
                std::cout << "You have to input either 1 or 2." << std::endl;
                clearBuffer();
        }
    }
}

/**
 * @brief Clears the input buffer 
 * 
 */
void clearBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}