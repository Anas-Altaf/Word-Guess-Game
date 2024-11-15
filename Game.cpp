// Game.cpp
#include "Game.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h> // For system("CLS"), Sleep()
#include <fstream>   // Added for std::ifstream
#include "EasyMode.h"
#include <conio.h>
// Color definitions
#define RESET 7
#define RED 12
#define GREEN 10
#define BLUE 9
#define YELLOW 14
#define MAGENTA 13
#define CYAN 11
#define WHITE 15

// Add this helper function in Game class
void Game::setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
Game::Game() : chances(5), remainingWords(3), currentScore(0)
{
    // Set console to UTF-8
    system("chcp 65001");
    // Initialize hiddenWords with some default words
    hiddenWords = {"CAT", "DOG", "RAT"}; // Example words

    // Allocate the grid
    grid = new char *[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++)
    {
        grid[i] = new char[GRID_SIZE];
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = '.'; // Initialize with dots
        }
    }
}
Game::~Game()
{
    // Deallocate the grid
    for (int i = 0; i < GRID_SIZE; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
}
void Game::showHighScores()
{
    std::cout << "\n=== HIGH SCORES ===\n";
    std::ifstream scoreFile("highscores.txt");
    if (scoreFile.is_open())
    {
        std::string line;
        while (getline(scoreFile, line))
        {
            std::cout << line << "\n";
        }
        scoreFile.close();
    }
    else
    {
        std::cout << "No high scores yet!\n";
    }
    std::cout << "=================\n";
}
void Game::displayTitle()
{
    //clearScreen();
    setColor(CYAN);
    std::cout << "\n╔═══════════════════════════════════╗\n";
    setColor(YELLOW);
    std::cout << "║      WORD SEARCH PUZZLE GAME      ║\n";
    setColor(CYAN);
    std::cout << "╚═══════════════════════════════════╝\n\n";
    setColor(RESET);
}
void Game::showGameDetails()
{
    std::cout << "\n=== WORD SEARCH GAME - INSTRUCTIONS ===\n";
    std::cout << "1. Find hidden words in the grid\n";
    std::cout << "2. Words can be:\n";
    std::cout << "   - Horizontal (left to right)\n";
    std::cout << "   - Vertical (top to bottom)\n";
    std::cout << "   - Diagonal (top left to bottom right)\n";

    std::cout << "\nHidden Words Lengths:\n";
    for (const auto &word : hiddenWords)
    {
        std::cout << "- " << word.length() << " letters\n";
    }
    std::cout << "\n===============================\n\n";
}

void Game::displayGrid()
{
    setColor(CYAN);
    std::cout << "\n   ╔";
    for (int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << "═══";
    }
    std::cout << "╗\n";

    // Column numbers
    std::cout << "   ║ ";
    setColor(YELLOW);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << i << "  ";
    }
    setColor(CYAN);
    std::cout << "║\n";

    // Separator line
    std::cout << "   ╠";
    for (int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << "═══";
    }
    std::cout << "╣\n";

    // Grid content
    for (int i = 0; i < GRID_SIZE; i++)
    {
        setColor(YELLOW);
        std::cout << " " << i << " ";
        setColor(CYAN);
        std::cout << "║ ";

        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == '*')
            {
                setColor(GREEN); // Found words in green
            }
            else
            {
                setColor(WHITE); // Regular letters in white
            }
            std::cout << grid[i][j] << "  ";
        }

        setColor(CYAN);
        std::cout << "║\n";
    }

    // Bottom border
    std::cout << "   ╚";
    for (int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << "═══";
    }
    std::cout << "╝\n\n";

    setColor(RESET); // Reset color
}
void Game::showGameStatus()
{
    setColor(CYAN);
    std::cout << "╔════════════════════════════════╗\n";
    std::cout << "║         GAME STATUS           ║\n";
    std::cout << "╠════════════════════════════════╣\n";

    setColor(WHITE);
    std::cout << "║ Remaining Chances: ";
    setColor(YELLOW);
    std::cout << chances;
    setColor(CYAN);
    std::cout << "         ║\n";

    setColor(WHITE);
    std::cout << "║ Words Remaining: ";
    setColor(YELLOW);
    std::cout << remainingWords;
    setColor(CYAN);
    std::cout << "           ║\n";

    setColor(WHITE);
    std::cout << "║ Score: ";
    setColor(GREEN);
    std::cout << currentScore;
    setColor(CYAN);
    std::cout << "                    ║\n";
    std::cout << "╚════════════════════════════════╝\n\n";

    setColor(RESET);
}

void Game::displayMenu()
{
    int choice;
    do
    {
        displayTitle();
        std::cout << "1. Start Game\n";
        std::cout << "2. Instructions\n";
        std::cout << "3. Highest Scores\n";
        std::cout << "4. About Us\n";
        std::cout << "5. Exit\n";
        std::cout << "\nSelect an option (1-5): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            startGame();
            break;
        case 2:
            showInstructions();
            break;
        case 3:
            showHighScores();
            break;
        case 4:
            aboutUs();
            break;
        case 5:
            exitGame();
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            pause();
            break;
        }
    } while (choice != 5);
}

void Game::startGame()
{
    system("CLS");
    showGameDetails();
    EasyMode easyMode;
    easyMode.play();

    while (chances > 0 && remainingWords > 0)
    {
        displayGrid();
        showGameStatus();
        processGuess();
    }

    showGameOver();
}
void Game::processGuess()
{
    std::string guess;
    std::cout << "Enter your guess: ";
    std::cin >> guess;

    // Check if guess is valid and matches a hidden word
    bool found = false;
    for (auto it = hiddenWords.begin(); it != hiddenWords.end(); ++it)
    {
        if (*it == guess)
        {
            std::cout << "Correct! You found a word!\n";
            currentScore += 10;
            hiddenWords.erase(it);
            remainingWords--;
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "Incorrect guess!\n";
        chances--;
    }

    Sleep(1500);
    //clearScreen();
}

void Game::showGameOver()
{
    //clearScreen();
    std::cout << "=== GAME OVER ===\n";
    std::cout << "Final Score: " << currentScore << "\n";
    if (remainingWords == 0)
    {
        std::cout << "Congratulations! You found all the words!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
    pause();
}
void Game::showInstructions()
{
    //clearScreen();
    std::cout << "Instructions:\n";
    std::cout << "- Find and guess the required number of words per level.\n";
    std::cout << "- Words can be found horizontally, vertically, or diagonally.\n";
    std::cout << "- You have 5 chances to complete all three levels.\n";
    pause();
}

void Game::aboutUs()
{
    //clearScreen();
    std::cout << "About Us:\n";
    std::cout << "This game is developed by [Your Team Names].\n";
    pause();
}

void Game::exitGame()
{
    //clearScreen();
    std::cout << "Thank you for playing!\n";
    Sleep(2000);
    exit(0);
}

void Game::clearScreen()
{
    system("CLS");
}

void Game::pause()
{
    std::cout << "\nPress any key to continue...";
    _getch();
}
