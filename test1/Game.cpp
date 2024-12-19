#include "Game.h"
#include <iostream>
#include <limits>
#include <algorithm>

Game::Game() : currentPlayer(PLAYER1) {}

void Game::start() {
    int choice;
    while (true) {
        screenController.showMainMenu();
        std::cout << "Press number to choice: ";
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            playWithPlayer();
            break;
        case 2:
            screenController.showPlayWithBotMenu(); // Hien thi menu choi voi BOT
            handleBotMenuChoice();
            break;
        case 6:
            return;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
}

void Game::handleBotMenuChoice() {
    int botChoice;
    std::cout << "Press number to choose bot mode: ";
    while (!(std::cin >> botChoice)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    switch (botChoice) {
    case 1:
    case 2:
    case 3:
        playWithBot();
        break;
    case 4:
        start(); // Quay lai menu chinh
        break;
    default:
        std::cout << "Invalid choice, please try again." << std::endl;
        handleBotMenuChoice();
    }
}

void Game::playWithPlayer() {
    playGame();
}

void Game::playWithBot() {
    boardController = BoardController(); // Reset ban co
    while (true) {
        boardController.displayBoard();
        if (currentPlayer == PLAYER1) {
            int x, y;
            std::cout << "Player 1 (X), nhap vi tri (hang cot): ";
            while (true) {
                std::cin >> x >> y;
                if (std::cin.fail() || x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                    std::cout << "Invalid move,try again (hang cot): ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    break;
                }
            }
            if (boardController.makeMove(x, y, currentPlayer)) {
                if (boardController.checkWin(currentPlayer)) {
                    boardController.displayBoard();
                    std::cout << "Player 1 (X) win!" << std::endl;
                    break;
                }
                currentPlayer = PLAYER2;
            }
            else {
                std::cout << "invalid move,try again." << std::endl;
            }
        }
        else {
            
            auto bestMove = getBestMove();
            boardController.makeMove(bestMove.first, bestMove.second, PLAYER2);
            if (boardController.checkWin(PLAYER2)) {
                boardController.displayBoard();
                std::cout << "Player 2 (O) [BOT] Win!" << std::endl;
                break;
            }
            currentPlayer = PLAYER1;
        }

        if (boardController.isFull()) {
            boardController.displayBoard();
            std::cout << "draw!" << std::endl;
            break;
        }
    }
}

std::pair<int, int> Game::getBestMove() {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };
    for (auto& move : boardController.getEmptyPositions()) {
        boardController.makeMove(move.first, move.second, PLAYER2);
        int score = minimax(false);
        boardController.undoMove(move.first, move.second);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

int Game::minimax(bool isMaximizing) {
    if (boardController.checkWin(PLAYER2)) return 1;
    if (boardController.checkWin(PLAYER1)) return -1;
    if (boardController.isFull()) return 0;

    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    for (auto& move : boardController.getEmptyPositions()) {
        boardController.makeMove(move.first, move.second, isMaximizing ? PLAYER2 : PLAYER1);
        int score = minimax(!isMaximizing);
        boardController.undoMove(move.first, move.second);
        if (isMaximizing) {
            bestScore = std::max(score, bestScore);
        }
        else {
            bestScore = std::min(score, bestScore);
        }
    }
    return bestScore;
}

void Game::playGame() {
    boardController = BoardController();
    while (true) {
        boardController.displayBoard();
        int x, y;
        std::cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") << ", nhap vi tri (hang cot): ";
        while (true) {
            std::cin >> x >> y;
            if (std::cin.fail() || x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                std::cout << "Invalid move,try again (hang cot): ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        if (boardController.makeMove(x, y, currentPlayer)) {
            if (boardController.checkWin(currentPlayer)) {
                boardController.displayBoard();
                std::cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") << " win!" << std::endl;
                break;
            }
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }
        else {
            std::cout << "Invalid move,try again:." << std::endl;
        }
    }
}
