//
// Created by rchowda on 11/17/2016.
//

#include <ctime>
#include "User.h"

User::User(const std::string &userName, const std::string &password, const std::string &lastLogin) : userName(userName), password(password), lastLogin(lastLogin){
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

User::User() {
    userName = "dummy";
    password = "dummy";
    lastLogin = "never";

}

const std::string &User::getUserName() const {
    return userName;
}

void User::setUserName(const std::string &userName) {
    User::userName = userName;
}

const std::string &User::getPassword() const {
    return password;
}

void User::setPassword(const std::string &password) {
    User::password = password;
}

const std::string &User::getLastLogin() const {
    return lastLogin;
}

void User::setLastLogin(const std::string &lastLogin) {
    User::lastLogin = lastLogin;
}

const User *User::getParent() const {
    return this;
}
