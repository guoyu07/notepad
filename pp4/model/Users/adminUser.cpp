//
// Created by rchowda on 11/18/2016.
//

#include "adminUser.h"

adminUser::adminUser(int userId, const std::string &userName, const std::string &lastLogin) : User(userId, userName, lastLogin) {}

std::string adminUser::getUserType() {
    return adminUser::type;
}

int adminUser::getMaxChildUsers() const {
    return maxChildUsers;
}

void adminUser::setMaxChildUsers(int maxChildUsers) {
    adminUser::maxChildUsers = maxChildUsers;
}

bool adminUser::childBorn() {
    adminUser::currentChildUsers++;
    return maxChildUsers <= currentChildUsers;
}

bool adminUser::childDied() {
    adminUser::currentChildUsers--;
    return currentChildUsers >= 0;
}
