#ifndef GAME_H
#define GAME_H

#include "Mode.h"
#include <vector>
#include <string>

class Game
{
public:
    Game();
    void displayTitle();
    void showGameDetails();
    void displayGrid();
    void showGameStatus();
    void displayMenu();
    void startGame();
    void showInstructions();
    void showHighScores();
    void aboutUs();
    void exitGame();
    ~Game();

private:
    void clearScreen();
    void pause();
    void processGuess();
    void showGameOver();
    void setColor(int color);

    static const int GRID_SIZE = 10;
    std::vector<std::string> hiddenWords;
    char **grid;
    int chances;
    int remainingWords;
    int currentScore;
};

#endif // GAME_H