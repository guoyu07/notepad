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
    User(int userId, const std::string &userName, const std::string &lastLogin);
    virtual std::string getUserType();

    virtual void loginFailed();

    virtual void clearFailedLogins();

    virtual bool isLocked();

    virtual int getMaxFailuresAllowed() const;

    virtual void setMaxFailuresAllowed(int);

    virtual int getMaxChildUsers() const;

    virtual void setMaxChildUsers(int);

    virtual bool childBorn();

    virtual bool childDied();
};


#endif //PP4_USER_H
