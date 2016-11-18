//
// Created by rchowda on 11/18/2016.
//

#ifndef PP4_REGULARUSER_H
#define PP4_REGULARUSER_H


#include "User/User.h"

class regularUser : public User {
protected:
    std::string type = "regular";
    User createdBy;
public:
    regularUser(int userId, const std::string &userName, const User &createdBy);

    virtual std::string getUserType() override;
};


#endif //PP4_REGULARUSER_H
