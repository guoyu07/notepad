//
// Created by rchowda on 9/6/16.
//

#include "Player.h"

Player::Player(): name("No name"), symbol('*'), id(-1){}

Player::Player(char symbol): name("null"), symbol(symbol), id(-rand()%10000){};

Player::Player(const std::string &name, char symbol) : name(name), symbol(symbol), id(rand()%10000){}

Player::Player(const std::string &name, const std::string symbol) : name(name), symbol(symbol[0]), id(rand()%10000){}

const std::string &Player::getName() const {
    return name;
}

void Player::setName(std::string name) {
    Player::name = name;
}

const char Player::getSymbol() const {
    return symbol;
}

void Player::setSymbol(char symbol) {
    Player::symbol = symbol;
}

int Player::getId() const {
    return id;
}

void Player::setId(int id) {
    Player::id = id;
}
