#ifndef BoardController_H
#define BoardController_H

#include <vector>
#include <iostream>

const int SIZE = 10; // Kich thuoc ban co
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

class BoardController {
private:
    std::vector<std::vector<char>> board;

    bool checkDirection(int x, int y, int dx, int dy, char player);

public:
    BoardController();
    void displayBoard();
    bool makeMove(int x, int y, char player);
    bool checkWin(char player);
    bool isFull();
    std::vector<std::pair<int, int>> getEmptyPositions();
    void undoMove(int x, int y);
};

#endif // BOARDCONTROLLER_H
