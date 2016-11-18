//
// Created by rchowda on 11/17/2016.
//

#ifndef PP4_USER_H
#define PP4_USER_H


#include <iostream>

class User {
protected:
    int userId;
    std::string userName, lastLogin;

    std::string getTimeStamp();
public:
    User(int userId, const std::string &userName);
};


#endif //PP4_USER_H
