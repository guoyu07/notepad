//
// Created by rchowda on 11/18/2016.
//

#ifndef PP4_ADMINUSER_H
#define PP4_ADMINUSER_H


#include "User/User.h"

class adminUser : public User {
protected:
    std::string type = "admin";
    int maxChildUsers, currentChildUsers;
public:
    adminUser(int userId, const std::string &userName, const std::string &lastLogin);

    virtual std::string getUserType() override;

    virtual int getMaxChildUsers() const;

    virtual void setMaxChildUsers(int maxChildUsers);

    virtual bool childBorn() override;

    virtual bool childDied() override;


};


#endif //PP4_ADMINUSER_H
