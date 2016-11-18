//
// Created by rchowda on 11/18/2016.
//

#include "regularUser.h"

std::string regularUser::getUserType() {
    return regularUser::type;
}

regularUser::regularUser(int userId, const std::string &userName, const User &createdBy) : User(userId, userName),
                                                                                           createdBy(createdBy) {}
