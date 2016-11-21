//
// Created by rchowda on 11/17/2016.
//

#ifndef PP4_USER_H
#define PP4_USER_H


#include <iostream>

class User {
protected:
    std::string userName, password, lastLogin;

public:
    User();
    User(const std::string &userName, const std::string &password, const std::string &lastLogin);
    virtual std::string getUserType();

    const std::string &getUserName() const;

    void setUserName(const std::string &userName);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getLastLogin() const;

    void setLastLogin(const std::string &lastLogin);

    virtual void loginFailed();

    virtual void clearFailedLogins();

    virtual bool isLocked();

    virtual int getMaxFailuresAllowed() const;

    virtual void setMaxFailuresAllowed(int);

    virtual int getMaxChildUsers() const;

    virtual void setMaxChildUsers(int);

    virtual bool childBorn();

    virtual bool childDied();

    virtual const User *getParent() const;
};


#endif //PP4_USER_H
