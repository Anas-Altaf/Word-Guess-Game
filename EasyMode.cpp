#include "EasyMode.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "Utility.h"

EasyMode::EasyMode() : player("Player", 0, 5)
{
    loadWords();
}

void EasyMode::loadWords()
{
    std::ifstream file("easy_words.txt");
    if (file.is_open())
    {
        std::string word;
        while (file >> word)
        {
            word = toUpperCase(word);
            words.push_back(word);
        }
        file.close();
    }
    else
    {
        std::cout << "Error: Unable to open easy_words.txt\n";
    }
    //To See the Loaded Words
    loadedWords();
}

void EasyMode::play()
{
    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    player.setName(name);

    for (int level = 1; level <= 3 && player.getRemainingChances() > 0; ++level)
    {
        startLevel(level);
    }

    std::cout << "\nGame Over!\n";
    std::cout << "Your Score: " << player.getScore() << "\n";

    ScoreTracker scoreTracker;
    scoreTracker.saveHighScore(player);
    scoreTracker.displayHighScores();

    std::cout << "\nPress any key to return to main menu...";
    _getch();
}

void EasyMode::loadedWords()
{
    // After loading words
    std::cout << "Loaded words:\n";
    for (const auto &w : words)
    {
        std::cout << w << std::endl;
    }
}

void EasyMode::startLevel(int levelNumber)
{
    system("CLS");
    std::cout << "Easy Mode - Level " << levelNumber << "\n";

    int gridSize = (levelNumber == 1) ? 10 : (levelNumber == 2) ? 15
                                                                : 20;
    int wordsToGuess = (levelNumber == 1) ? 3 : (levelNumber == 2) ? 5
                                                                   : 7;

    Grid grid(gridSize);
    grid.populateGrid(words);
    WordValidator validator(words, grid);

    int guessedWords = 0;

    while (guessedWords < wordsToGuess && player.getRemainingChances() > 0)
    {
        grid.displayGrid();
        std::cout << "\nRemaining Chances: " << player.getRemainingChances() << "\n";
        std::cout << "Words Remaining to Guess: " << (wordsToGuess - guessedWords) << "\n";
        std::cout << "Enter word (2-4 letters): ";

        std::string guess;
        std::cin >> guess;
        guess = toUpperCase(guess);

        if (validator.isValidWord(guess))
        {
            if (validator.isInGrid(guess))
            {
                if (!grid.checkWord(guess))
                {
                    std::cout << "Correct! Word found.\n";
                    player.updateScore(10);
                    guessedWords++;
                    grid.markWord(guess);
                }
                else
                {
                    std::cout << "Word already found.\n";
                }
            }
            else
            {
                std::cout << "Word not in grid.\n";
                player.decreaseChance();
            }
        }
        else
        {
            std::cout << "Invalid word.\n";
            player.decreaseChance();
        }

        Sleep(1500);
        system("CLS");
    }

    if (player.getRemainingChances() == 0)
    {
        std::cout << "No remaining chances. Game Over.\n";
    }
    else
    {
        std::cout << "Level " << levelNumber << " complete!\n";
        Sleep(1500);
    }
}