#ifndef Game_H
#define Game_H

#include "BoardController.h"
#include "ScreenController.h"

class Game {
private:
    BoardController boardController;
    ScreenController screenController;
    char currentPlayer;

    std::pair<int, int> getBestMove();
    int minimax(bool isMaximizing);

public:
    Game();
    void start();
    void playWithPlayer();
    void playWithBot();
    void playGame();
    void handleBotMenuChoice();
};

#endif // GAME_H
