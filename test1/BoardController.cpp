#include "BoardController.h"

BoardController::BoardController() {
    board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
}

void BoardController::displayBoard() {
    std::cout << "   ";
    for (int i = 0; i < SIZE; i++)
        std::cout<<" " << i << "  ";
    std::cout << std::endl;

    for (int i = 0; i < SIZE; i++) {
        std::cout << i << " | ";
        for (int j = 0; j < SIZE; j++) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl;
        std::cout << "  " << std::string(SIZE * 4, '-') << std::endl;
    }
}

bool BoardController::makeMove(int x, int y, char player) {
    if (board[x][y] == EMPTY) {
        board[x][y] = player;
        return true;
    }
    return false;
}

bool BoardController::checkWin(char player) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == player) {
                if (checkDirection(i, j, 1, 0, player) ||
                    checkDirection(i, j, 0, 1, player) ||
                    checkDirection(i, j, 1, 1, player) ||
                    checkDirection(i, j, 1, -1, player))
                    return true;
            }
        }
    }
    return false;
}

bool BoardController::checkDirection(int x, int y, int dx, int dy, char player) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        int newX = x + i * dx;
        int newY = y + i * dy;
        if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE || board[newX][newY] != player)
            return false;
        count++;
    }
    return count == 5;
}

bool BoardController::isFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

std::vector<std::pair<int, int>> BoardController::getEmptyPositions() {
    std::vector<std::pair<int, int>> emptyPositions;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                emptyPositions.push_back({ i, j });
            }
        }
    }
    return emptyPositions;
}

void BoardController::undoMove(int x, int y) {
    board[x][y] = EMPTY;
}
