//
// Created by rchowda on 10/8/2016.
//

#include <fstream>
#include <iostream>
#include "PlayerDao.h"

bool PlayerDao::createNewPlayer(Player &player) {
    if(isPresent(player.getName())) return false;
    if(!outFile.is_open()){outFile.open(fileName,std::ios_base::app);}
    outFile << player.getName() << std::endl;
    outFile << player.getSymbol() << std::endl;
    outFile.close();
    return true;
}

Player PlayerDao::getPlayer(std::string name) {
    if(!inFile.is_open()){inFile.open(fileName);}
    std::string tmp_str;
    if(!inFile.eof()) inFile >> tmp_str;
    while(!inFile.eof()) {
        if (tmp_str == name) {
            inFile >> tmp_str;
            return Player(name, tmp_str);
        }
        inFile >> tmp_str;
    }
    inFile.close();
    return Player();
}

std::list<Player> PlayerDao::getAllPlayers() {
    std::list<Player> playersList;
    if(!inFile.is_open()){inFile.open(fileName);}
    std::string tmp_name_str, tmp_sym_str;
    if(!inFile.eof()) {
        inFile >> tmp_name_str;
        inFile >> tmp_sym_str;
    }
    while(!inFile.eof()){
        playersList.push_back(Player(tmp_name_str,tmp_sym_str));
        inFile >> tmp_name_str;
        inFile >> tmp_sym_str;
    }
    inFile.close();
    return playersList;
}

bool PlayerDao::isPresent(const std::string& name) {
    if(!inFile.is_open()){inFile.open(fileName);}
    if(inFile.good()){
        std::string tmp_str;
        if(!inFile.eof()) inFile >> tmp_str;
        while(!inFile.eof()){
            if(tmp_str == name){
                inFile.close();
                return true;
            }
            inFile >> tmp_str;inFile >> tmp_str;    //To skip symbol
        }
        return false;

    }else{
        std::cout << "Unable to find" + fileName + "\n";
        return false;

    }
}

//int main(){
//    PlayerDao playerDao;
//    Player one("Raghuvaran",'p');
//
//    std::cout << playerDao.createNewPlayer(one) << std::endl;
//}