#include <iostream>

#include "controller/TTTController.h"

int main() {

    std::string name1, name2, symbol1, symbol2;
    std::cout << "Enter Player1 Name: "; std::cin >> name1;
    std::cout << "Enter Player1 Symbol: "; std::cin >> symbol1;
    std::cout << std::endl;

    std::cout << "Enter Player2 Name: "; std::cin >> name2;
    std::cout << "Enter Player2 Symbol: "; std::cin >> symbol2;
    std::cout << std::endl;

//    Board  board(Player(name1,symbol1),Player(name2,symbol2));
//    board.start();

    TTTController controller;
    controller.createPlayer(name1,symbol1,1);
    controller.createPlayer(name2,symbol2,2);

    controller.startNewGame();
    int choice;
    int turn =1;
    std::cout << "Choose you move ..." << std::endl;
    while(!controller.determineWinner()){
        std::cout << controller.getGameDisplay();
        if(turn%2){
            std::cout << controller.getPlayerName(1) << "'s turn:" ;
            std::cin >> choice;
            if(controller.setSelection(choice-1,1)) turn++;
        }else{
            std::cout << controller.getPlayerName(2) << "'s turn:" ;
            std::cin >> choice;
            if(controller.setSelection(choice-1,2)) turn++;
        }

    }

    switch (controller.determineWinner()){
        case 1: std::cout << controller.getPlayerName(1) << " has won!" << std::endl; break;
        case 2: std::cout << controller.getPlayerName(2) << " has won!" << std::endl;break;
        case 3: std::cout << "Game is tie!"<< std::endl;break;
        default: std::cout << "Can't determine who won ask the one who created me!"<< std::endl;

    }

}