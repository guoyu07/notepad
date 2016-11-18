//
// Created by rchowda on 11/18/2016.
//

#include "adminUser.h"

adminUser::adminUser(int userId, const std::string &userName) : User(userId, userName) {}

std::string adminUser::getUserType() {
    return adminUser::type;
}
