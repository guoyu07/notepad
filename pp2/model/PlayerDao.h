//
// Created by rchowda on 10/8/2016.
//

#ifndef PP2_PLAYERDAO_H
#define PP2_PLAYERDAO_H


#include <list>
#include <fstream>
#include "Player.h"

class PlayerDao {
    std::string fileName = "filePlayers.txt";
    std::ofstream outFile;
    std::ifstream inFile;
public:
    bool createNewPlayer(Player &);    //Create
    Player getPlayer(std::string name); //Read
    std::list<Player> getAllPlayers();
    //Update
    //Delete
    bool isPresent(const std::string& name);
};


#endif //PP2_PLAYERDAO_H
