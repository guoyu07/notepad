//
// Created by rchowda on 11/18/2016.
//

#ifndef PP4_ADMINUSER_H
#define PP4_ADMINUSER_H


#include "User/User.h"

class adminUser : public User {
protected:
    std::string type = "admin";
public:
    adminUser(int userId, const std::string &userName);

    virtual std::string getUserType() override;

};


#endif //PP4_ADMINUSER_H
