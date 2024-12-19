#include "ScreenController.h"
#include <iostream>

void ScreenController::showMainMenu() {
    std::cout << "-------MAIN MENU-------" << std::endl;
    std::cout << "1. Play with Other Player" << std::endl;
    std::cout << "2. Play with BOT" << std::endl;
    std::cout << "3. Replay" << std::endl;
    std::cout << "4. Player's Information" << std::endl;
    std::cout << "5. Guide" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

void ScreenController::showPlayWithBotMenu() {
    std::cout << "-------Play with BOT-------" << std::endl;
    std::cout << "1. Easy Mode" << std::endl;
    std::cout << "2. Normal Mode" << std::endl;
    std::cout << "3. Hard Mode" << std::endl;
    std::cout << "4. Back to MAIN MENU" << std::endl;
}
