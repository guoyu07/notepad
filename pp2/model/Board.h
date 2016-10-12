//
// Created by rchowda on 9/6/16.
//

#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H


#include <string>
#include <array>
#include "Player.h"

class Board {
//TODO reverse access to private before submission
public:
    std::array<Player,9> cursor;
    Player player1;
    Player player2;

    Board();
    Board(const Player&, const Player&);
    const std::array<Player, 9> getCursor() const;
    void setCursor(const std::array<Player, 9> &cursor);
    void setPlayer(std::string&, std::string&, int);
    int markSymbol(const Player&, int);
    std::string printBoard();
    char whoWon();
    void start();
    void reset();
    bool compare(const Player, const Player);
};


#endif //TICTACTOE_BOARD_H
