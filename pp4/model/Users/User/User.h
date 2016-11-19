//
// Created by rchowda on 11/17/2016.
//

#ifndef PP4_USER_H
#define PP4_USER_H


#include <iostream>

class User {
protected:
    int userId;
    std::string userName, password, lastLogin;

    std::string getTimeStamp();
public:
    User();
    User(int userId, const std::string &userName, const std::string &password, const std::string &lastLogin);
    virtual std::string getUserType();

    int getUserId() const;

    void setUserId(int userId);

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
};


#endif //PP4_USER_H
