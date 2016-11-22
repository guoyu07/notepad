//
// Created by rchowda on 11/18/2016.
//

#include "regularUser.h"

std::string regularUser::getUserType() {
    return regularUser::type;
}

regularUser::regularUser(const std::string &userName, const std::string &password,const std::string &lastLogin, User* parent) : User(userName, password, lastLogin),
                                                                                           parent(parent) {}

regularUser::regularUser(const std::string &userName, const std::string &password, const std::string &lastLogin) : User(
        userName, password, lastLogin) {

}

int regularUser::getMaxFailuresAllowed() const {
    return maxFailuresAllowed;
}

void regularUser::setMaxFailuresAllowed(int maxFailuresAllowed) {
    regularUser::maxFailuresAllowed = maxFailuresAllowed;
}

void regularUser::loginFailed() {
    regularUser::failedLogins++;
}

bool regularUser::isLocked() {
    return regularUser::maxFailuresAllowed <= regularUser::failedLogins;
}

void regularUser::clearFailedLogins() {
    regularUser::failedLogins = 0;
}

const User *regularUser::getParent() const {
    return parent;
}

void regularUser::setParent(User *parent) {
    delete regularUser::parent;
    regularUser::parent = parent;
}
