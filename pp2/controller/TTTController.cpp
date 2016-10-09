//
// Created by rchowda on 9/7/2016.
//

#include <iostream>
#include <cstring>
#include <limits>
#include "TTTController.h"
#include "../model/Player.h"

TTTController::TTTController() {}
TTTController::~TTTController() {}

void TTTController::createPlayer(std::string& name, std::string& marker, int playerNum=1)  {
            switch (playerNum){
                case 1: player1 = Player(name, marker); break;
                case 2: player2 = Player(name, marker); break;

            }
          // board.setPlayer(name, marker,playerNum);
}

//void TTTController::startGame(){
//    board = Board(player1,player2);
//    std::cout << board.printBoard() << std::endl;
//    int turn = 1;
//    int pos = -1;
//
//    while (board.whoWon() == 'R'){
//
//        if(turn % 2){
//            std::cout << player1.getName() << "'s turn:";
//            std::cin >> pos;
//	    std::cout << std::endl;
//            if(!board.markSymbol(player1,pos)){
//                turn++;
//            }
//        }else{
//            std::cout << player2.getName() << "'s turn:";
//            std::cin >> pos;
//	    std::cout << std::endl;
//            if(!board.markSymbol(player2,pos)){
//                turn++;
//            }
//        }
//	if (std::cin.eof()==1) {
//		std::cin.clear();
//		//std::cin.ignore();
//		continue;
//	}
//	if(pos==0){
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//        }
//	for(int m = 0; m <2; m++){std::cout << "                                                " << std::endl;}
//        std::cout << "\033[12A";
//	for(int m = 0; m <10; m++){std::cout << "                                                " << std::endl;}
//        std::cout << "\033[10A";
//        std::cout << board.printBoard() << std::endl;
//    }
//
//
//    if(board.whoWon() == 'D') {
//        std::cout << "The game is draw!" << std::endl;
//    }else{
//        if(player1.getSymbol() == board.whoWon()){
//            std::cout << player1.getName() << " has won the game!" << std::endl;
//        } else{
//            std::cout << player2.getName() << " has won the game!" << std::endl;
//        }
//    }
//}

bool TTTController::setSelection(int row, int col, int currentPlayer) {
    switch (currentPlayer){
        case 1: board.markSymbol(player1,(3*row+col+1));
            return true;
        case 2: board.markSymbol(player2,(3*row+col+1));
            return true;
        default: std::cout << "Invalid Player number" << std::endl;return false;
    }
}

int TTTController::determineWinner() {

    std::array<Player,9> cursor;
    cursor = board.getCursor();
    std::cout << cursor[0].getSymbol() << std::endl;std::cout << cursor[8].getSymbol() << std::endl;
    //Check column match
    for(int i=0, j=3, k=6; i<3; i++, j++, k++){
        if(compare(cursor[i],cursor[j]) && compare(cursor[j],cursor[k])){
            //std::cout << "i:" << i;
            return compare(cursor[i],player1)?1:2;
        }
    }

    //check row match
    for(int i=0, j=1, k=2; i<9; i+=3, j+=3, k+=3){
        if(compare(cursor[i],cursor[j]) && compare(cursor[j],cursor[k])){
            return compare(cursor[i],player1)?1:2;
        }
    }
    //check diagonal match
    if((compare(cursor[0], cursor[4]) && compare(cursor[4], cursor[8])) || (compare(cursor[2], cursor[4]) && compare(cursor[4], cursor[6]))){
        return compare(cursor[4],player1)?1:2;
    }

    //Is it a draw? or still running?
    for(int i=0; i < 9; i++){
        if(cursor[i].getId() <0)  {return 0;}
    }


    //Game is draw
    return 3;

    //None of the above cases worked?


}


std::string TTTController::getGameDisplay() {
    std::array<Player,9> cursor = board.getCursor();
    std::string out = "";
    std::string hor = "-----";
    std::string lver = "|  ";
    std::string rver = "  |";
    std::string ver = "  |  ";

    // out += "\033[8A";   //Clear 8 lines up
    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    out +=  lver ; out +=  cursor[0].getSymbol() ; out +=  ver ; out +=  cursor[1].getSymbol() ; out +=  ver ; out +=  cursor[2].getSymbol() ; out +=  rver ; out +=  "\n";

    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    out +=  lver ; out +=  cursor[3].getSymbol() ; out +=  ver ; out +=  cursor[4].getSymbol() ; out +=  ver ; out +=  cursor[5].getSymbol() ; out +=  rver ; out +=  "\n";

    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    out +=  lver ; out +=  cursor[6].getSymbol() ; out +=  ver ; out +=  cursor[7].getSymbol() ; out +=  ver ; out +=  cursor[8].getSymbol() ; out +=  rver ; out +=  "\n";
    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    return out;
}

bool TTTController::compare(const Player& p1, const Player& p2){
    return p1.getId() == p2.getId();
}

//int main(){
//    TTTController ttt;
//    ttt.player1 = Player("RV",'x');
//    ttt.player2 = Player("SV",'o');
//    ttt.board = Board(ttt.player1,ttt.player2);
//    ttt.board.cursor[0] = ttt.player1;ttt.board.cursor[1] = ttt.player1;ttt.board.cursor[8] = ttt.player1;
//    ttt.board.cursor[3] = ttt.player2;ttt.board.cursor[2] = ttt.player2;ttt.board.cursor[7] = ttt.player2;
//    ttt.board.cursor[4] = ttt.player2;ttt.board.cursor[5] = ttt.player1;ttt.board.cursor[6] = ttt.player2;
//    std::cout << ttt.getGameDisplay() << std::endl;
//    std::cout << ttt.determineWinner() << std::endl;
//}