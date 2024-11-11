#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

class Grid {
public:
    Grid(int size);
    ~Grid();
    void allocateGrid(int size);
    void deallocateGrid();
    void populateGrid(const std::vector<std::string>& words);
    void displayGrid();
    bool checkWord(const std::string& word);
    void markWord(const std::string& word);
    int getSize() const;
    char getCharAt(int row, int col) const;

private:
    int size;
    char** grid;
    std::vector<std::string> placedWords;

    void fillRandomLetters();
    bool placeWord(const std::string& word);
    bool canPlaceHorizontally(int row, int col, const std::string& word);
    bool canPlaceVertically(int row, int col, const std::string& word);
    bool canPlaceDiagonally(int row, int col, const std::string& word);
    void placeHorizontally(int row, int col, const std::string& word);
    void placeVertically(int row, int col, const std::string& word);
    void placeDiagonally(int row, int col, const std::string& word);
    void setColor(int color);
    static const int RESET = 7;
    static const int RED = 12;
    static const int GREEN = 10;
    static const int BLUE = 9;
    static const int YELLOW = 14;
    static const int MAGENTA = 13;
    static const int CYAN = 11;
    static const int WHITE = 15;

};

#endif // GRID_H