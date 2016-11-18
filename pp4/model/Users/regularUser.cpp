//
// Created by rchowda on 11/18/2016.
//

#include "regularUser.h"

std::string regularUser::getUserType() {
    return regularUser::type;
}

regularUser::regularUser(int userId, const std::string &userName,const std::string &lastLogin, const User &createdBy) : User(userId, userName, lastLogin),
                                                                                           createdBy(createdBy) {}

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


