//
// Created by rchowda on 9/6/16.
//

#include <iostream>
#include "Board.h"

Board::Board() : cursor{Player('1'),Player('2'),Player('3'),Player('4'),Player('5'),Player('6'),Player('7'),Player('8'),Player('9')} {
    player1 = Player("dummy",'d');
    player2 = Player("dummy",'d');
}
//int main(){
//    Board b = Board(Player("Raghu",'x'),Player("Sathy",'o'));
//    //if(b.compare(b.player1,b.player1))    std::cout << b.player1.getId() << " | " << b.player2.getId() << std::endl;
//}
Board::Board(const Player &p1, const Player &p2) : cursor{Player('1'),Player('2'),Player('3'),Player('4'),Player('5'),Player('6'),Player('7'),Player('8'),Player('9')}  {
    player1 = p1;
    player2 = p2;
}

void Board::setPlayer(std::string& name, std::string &marker, int playerNum) {
    switch (playerNum){
        case 1: player1.setName(name); player1.setSymbol(marker[0]);
            break;
        case 2: player2.setName(name); player2.setSymbol(marker[0]);
            break;
        default: std::cout << "Invalid Player number" << std::endl;
    }
}


int Board::markSymbol(const Player &player, int pos) {


    if(pos > 0 && pos < 10){


        if( compare(cursor[pos-1],player1)|| compare(cursor[pos-1],player2)){

            std::cout << "\033[1;31mCaution:\033[0;m Invalid position! Please try again";// << std::endl;
            return 1;
        }

        cursor[pos - 1] = player;
        return 0;

    }else{
        std::cout << "\033[1;31mCaution:\033[0;m Position not in range";// << std::endl;
        return 1;
    }

}


std::string Board::printBoard(){
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


char Board::whoWon() {
/*Return
     * symbol of player - player won
     * 'D' - Draw
     * 'R' - Still running no one won
     * 'E' - Error*/


    //Check column match
    for(int i=0, j=3, k=6; i<3; i++, j++, k++){
        if(compare(cursor[i],cursor[j]) && compare(cursor[j],cursor[k])){
            return cursor[i].getSymbol();
        }
    }

    //check row match
    for(int i=0, j=1, k=2; i<3; i+=3, j+=3, k+=3){
        if(compare(cursor[i],cursor[j]) && compare(cursor[j],cursor[k])){
            return cursor[i].getSymbol();
        }
    }
    //check diagonal match
    if((compare(cursor[0], cursor[4]) && compare(cursor[4], cursor[8])) || (compare(cursor[2], cursor[4]) && compare(cursor[4], cursor[6]))){
        return cursor[4].getSymbol();
    }

    //Is it a draw? or still running?
    for(int i=0; i < 9; i++){
        if(cursor[i].getId() <0)  {return 'R';}
    }


    //Game is draw
    return 'D';

    //None of the above cases worked?
}

void Board::start() {
    printBoard();
    int turn = 1;
    int pos = -1;

    while (whoWon() == 'R'){

        if(turn % 2){
            std::cout << player1.getName() << "'s turn:" << std::endl;
            std::cin >> pos;
            if(!markSymbol(player1,pos)){
                turn++;
            }
        }else{
            std::cout << player2.getName() << "'s turn:" << std::endl;
            std::cin >> pos;
            if(!markSymbol(player2,pos)){
                turn++;
            }
        }
        printBoard();
    }


        if(whoWon() == 'D') {
            std::cout << "The game is draw!" << std::endl;
        }else{
            if(player1.getSymbol() == whoWon()){
                std::cout << player1.getName() << " has won the game!" << std::endl;
            } else{
                std::cout << player2.getName() << " has won the game!" << std::endl;
            }
        }


}



bool Board::compare(const Player p1, const Player p2){
    return p1.getId() == p2.getId();
}