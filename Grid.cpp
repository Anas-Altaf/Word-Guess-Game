#include "Grid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <wincon.h>
#include <windows.h>
#include <conio.h>
#include <chrono>

Grid::Grid(int gridSize) : size(gridSize)
{
    allocateGrid(size);
}

Grid::~Grid()
{
    deallocateGrid();
}

void Grid::allocateGrid(int gridSize)
{
    grid = new char *[gridSize];
    for (int i = 0; i < gridSize; ++i)
    {
        grid[i] = new char[gridSize];
    }
}

void Grid::deallocateGrid()
{
    for (int i = 0; i < size; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

void Grid::populateGrid(const std::vector<std::string> &words)
{
    srand(static_cast<unsigned>(time(0)));
    fillRandomLetters();

    for (const auto &word : words)
    {
        bool placed = false;
        int attempts = 0;
        while (!placed && attempts < 100)
        { // Limit attempts to avoid infinite loops
            placed = placeWord(word);
            attempts++;
        }
        if (placed)
        {
            placedWords.push_back(word);
        }
    }
}

void Grid::fillRandomLetters()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            grid[i][j] = 'A' + rand() % 26;
        }
    }
}

bool Grid::placeWord(const std::string &word)
{
    int direction = rand() % 3; // 0: Horizontal, 1: Vertical, 2: Diagonal
    int row = rand() % size;
    int col = rand() % size;

    switch (direction)
    {
    case 0: // Horizontal
        if (canPlaceHorizontally(row, col, word))
        {
            placeHorizontally(row, col, word);
            return true;
        }
        break;
    case 1: // Vertical
        if (canPlaceVertically(row, col, word))
        {
            placeVertically(row, col, word);
            return true;
        }
        break;
    case 2: // Diagonal
        if (canPlaceDiagonally(row, col, word))
        {
            placeDiagonally(row, col, word);
            return true;
        }
        break;
    }
    return false;
}

bool Grid::canPlaceHorizontally(int row, int col, const std::string &word)
{
    int wordLength = word.length();
    if (col + wordLength > size)
        return false;

    for (int i = 0; i < wordLength; ++i)
    {
        if (grid[row][col + i] != word[i] && grid[row][col + i] != ' ' && grid[row][col + i] != 'A' + rand() % 26)
        {
            return false;
        }
    }
    return true;
}

bool Grid::canPlaceVertically(int row, int col, const std::string &word)
{
    int wordLength = word.length();
    if (row + wordLength > size)
        return false;

    for (int i = 0; i < wordLength; ++i)
    {
        if (grid[row + i][col] != word[i] && grid[row + i][col] != ' ' && grid[row + i][col] != 'A' + rand() % 26)
        {
            return false;
        }
    }
    return true;
}

bool Grid::canPlaceDiagonally(int row, int col, const std::string &word)
{
    int wordLength = word.length();
    if (row + wordLength > size || col + wordLength > size)
        return false;

    for (int i = 0; i < wordLength; ++i)
    {
        if (grid[row + i][col + i] != word[i] && grid[row + i][col + i] != ' ' && grid[row + i][col + i] != 'A' + rand() % 26)
        {
            return false;
        }
    }
    return true;
}

void Grid::placeHorizontally(int row, int col, const std::string &word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        grid[row][col + i] = word[i];
    }
}

void Grid::placeVertically(int row, int col, const std::string &word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        grid[row + i][col] = word[i];
    }
}

void Grid::placeDiagonally(int row, int col, const std::string &word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        grid[row + i][col + i] = word[i];
    }
}


void Grid::displayGrid()
{
    setColor(CYAN);
    std::cout << "\n   ╔";
    for (int i = 0; i < size; i++)
    {
        std::cout << "═══";
    }
    std::cout << "╗\n";

    // Column numbers
    std::cout << "   ║ ";
    setColor(YELLOW);
    for (int i = 0; i < size; i++)
    {
        std::cout << i << "  ";
    }
    setColor(CYAN);
    std::cout << "║\n";

    // Separator line
    std::cout << "   ╠";
    for (int i = 0; i < size; i++)
    {
        std::cout << "═══";
    }
    std::cout << "╣\n";

    // Grid content
    for (int i = 0; i < size; i++)
    {
        setColor(YELLOW);
        std::cout << " " << i << " ";
        setColor(CYAN);
        std::cout << "║ ";

        for (int j = 0; j < size; j++)
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
    for (int i = 0; i < size; i++)
    {
        std::cout << "═══";
    }
    std::cout << "╝\n\n";

    setColor(RESET);
}

int Grid::getSize() const
{
    return size;
}

char Grid::getCharAt(int row, int col) const
{
    if (row >= 0 && row < size && col >= 0 && col < size)
    {
        return grid[row][col];
    }
    return '\0';
}

bool Grid::checkWord(const std::string &word)
{
    // Since word placement is random, we can check if the word is among the placed words
    for (const auto &placedWord : placedWords)
    {
        if (word == placedWord)
        {
            return true;
        }
    }
    return false;
}
void Grid::markWord(const std::string &word)
{
    // Iterate over the grid to find and mark the word
    int size = getSize();
    int wordLength = word.length();

    // Check horizontally
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col <= size - wordLength; ++col)
        {
            int i;
            for (i = 0; i < wordLength; ++i)
            {
                if (grid[row][col + i] != word[i])
                {
                    break;
                }
            }
            if (i == wordLength)
            {
                // Mark the word
                for (i = 0; i < wordLength; ++i)
                {
                    grid[row][col + i] = '*'; // Mark with an asterisk
                }
                return;
            }
        }
    }

    // Check vertically
    for (int col = 0; col < size; ++col)
    {
        for (int row = 0; row <= size - wordLength; ++row)
        {
            int i;
            for (i = 0; i < wordLength; ++i)
            {
                if (grid[row + i][col] != word[i])
                {
                    break;
                }
            }
            if (i == wordLength)
            {
                // Mark the word
                for (i = 0; i < wordLength; ++i)
                {
                    grid[row + i][col] = '*'; // Mark with an asterisk
                }
                return;
            }
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int row = 0; row <= size - wordLength; ++row)
    {
        for (int col = 0; col <= size - wordLength; ++col)
        {
            int i;
            for (i = 0; i < wordLength; ++i)
            {
                if (grid[row + i][col + i] != word[i])
                {
                    break;
                }
            }
            if (i == wordLength)
            {
                // Mark the word
                for (i = 0; i < wordLength; ++i)
                {
                    grid[row + i][col + i] = '*'; // Mark with an asterisk
                }
                return;
            }
        }
    }

    // Check diagonally (bottom-left to top-right)
    for (int row = wordLength - 1; row < size; ++row)
    {
        for (int col = 0; col <= size - wordLength; ++col)
        {
            int i;
            for (i = 0; i < wordLength; ++i)
            {
                if (grid[row - i][col + i] != word[i])
                {
                    break;
                }
            }
            if (i == wordLength)
            {
                // Mark the word
                for (i = 0; i < wordLength; ++i)
                {
                    grid[row - i][col + i] = '*'; // Mark with an asterisk
                }
                return;
            }
        }
    }
}