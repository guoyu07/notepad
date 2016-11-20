//
// Created by rchowda on 11/18/2016.
//

#ifndef PP4_NOTES_H
#define PP4_NOTES_H


#include <string>
#include "../Users/User/User.h"

class Notes {
protected:
    int noteId;
    std::string title, body, lastModified;
    User *userName;
public:
    Notes(int noteId, const std::string &title, const std::string &body, User *userName);
};


#endif //PP4_NOTES_H
