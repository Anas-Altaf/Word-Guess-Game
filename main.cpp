#include "Game.h"
#include <iostream>
#include <time.h>

int main()
{
    // In main.cpp or before grid creation
    srand(static_cast<unsigned>(time(0)));
    Game game;
    game.displayMenu();
    return 0;
}