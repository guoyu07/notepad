//
// Created by rchowda on 11/17/2016.
//

#include <ctime>
#include "User.h"

User::User(int userId, const std::string &userName, const std::string &lastLogin) : userId(userId), userName(userName), lastLogin(lastLogin){
}

std::string User::getUserType() {
    return std::string("No type");
}

void User::loginFailed() {

}

bool User::isLocked() {
    return false;
}

int User::getMaxFailuresAllowed() const {
    return 99999;
}

void User::setMaxFailuresAllowed(int maxFailuresAllowed) {

}

std::string User::getTimeStamp() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    std::time (&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}

void User::clearFailedLogins() {

}

int User::getMaxChildUsers() const {
    return 0;
}

void User::setMaxChildUsers(int) {

}

bool User::childBorn() {
    return false;
}

bool User::childDied() {
    return false;
}
