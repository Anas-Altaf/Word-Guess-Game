

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++# Word Search Puzzle Game

A console-based word search puzzle game implemented in C++.

### Project Structure

```
src/
├── main.cpp          - Entry point
├── Game.h/cpp        - Main game controller
├── Mode.h            - Base class for game modes
├── EasyMode.h/cpp    - Easy mode implementation
├── Grid.h/cpp        - Grid management
├── Player.h/cpp      - Player state management
├── WordValidator.h/cpp- Word validation logic
├── ScoreTracker.h/cpp- High score management
└── easy_words.txt    - Word database for easy mode
```

### Features


- Multiple difficulty levels
- Colorful console interface
- Word search in horizontal, vertical and diagonal directions
- Score tracking
- High score system
- Grid sizes: 10x10, 15x15, 20x20

### Requirements

- Windows OS
- C++11 compatible compiler
- Visual Studio Code (recommended)

### Building the Game

```batch
# Navigate to source directory
cd src

# Compile all source files
g++ -std=c++11 -o WordSearchGame main.cpp Game.cpp EasyMode.cpp Grid.cpp Word.cpp WordValidator.cpp ScoreTracker.cpp Player.cpp
```

### Running the Game

```batch
# Run the compiled executable
WordSearchGame.exe
```

### Gameplay Instructions

1. Select game mode (Easy)
2. Enter your name
3. Find words in the grid:
   - Words can be horizontal, vertical, or diagonal
   - Word lengths: 2-4 letters (Easy mode)
   - You have 5 chances to complete all levels

### Controls

- Enter numbers 1-5 to navigate menus
- Type words and press Enter to make guesses
- Press any key to continue at prompts

### Files Required

- `easy_words.txt` - Contains word database
- `easy_highscores.txt` - Stores high scores (created automatically)

### Color Legend

- 🟦 Cyan: Borders and frames
- 🟨 Yellow: Coordinates and statistics
- ⬜ White: Regular letters
- 🟩 Green: Found words
- Red: Error messages

### Note

Make sure all source files and word database are in the same directory before compiling.