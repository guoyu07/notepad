//
// Created by rchowda on 11/18/2016.
//

#ifndef PP4_NOTES_H
#define PP4_NOTES_H


#include <string>
#include "../Users/User/User.h"

class Note {
protected:
    int noteId;
    std::string title, body, lastModified;
    User *userName;
public:
    Note();

    Note(int noteId, const std::string &title, const std::string &body, const std::string &lastModified, User *owner);

    int getNoteId() const;

    void setNoteId(int noteId);

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    const std::string &getBody() const;

    void setBody(const std::string &body);

    const std::string &getLastModified() const;

    void setLastModified(const std::string &lastModified);

    User *getUserName() const;

    void setUserName(User *userName);
};


#endif //PP4_NOTES_H
