#ifndef EASYMODE_H
#define EASYMODE_H

#include "Mode.h"
#include "Grid.h"
#include "WordValidator.h"
#include "ScoreTracker.h"
#include "Player.h"
#include <vector>
#include <string>

class EasyMode : public Mode {
public:
    EasyMode();
    void play() override;
void loadedWords();
    
private:
    void loadWords();
    void startLevel(int levelNumber);
    std::vector<std::string> words;
    Player player;
};

#endif // EASYMODE_H