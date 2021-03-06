//
// Created by rchowda on 11/18/16.
//

#ifndef PP4_DAO_H
#define PP4_DAO_H


#include <string>
#include <fstream>
#include "../lib/rapidjson/document.h"
#include "Users/User/User.h"
#include "Notes/Note.h"

class Dao {
    std::string users_db = "users_db.txt", notes_db = "note_db.txt";
    bool isLocked;
    std::ofstream outFile;
    std::ifstream inFile;

    //Json keys
//    const char
//    *noteId       = "noteId",
//    *noteTitle    = "noteTitle",
//    *noteBody     = "noteBody",
//    *userName     = "userName",
//    *password     = "password",
//    *lastLogin    = "lastLogin",
//    *lastModified = "lastModified";
    rapidjson::Value& setString(rapidjson::Value& value, std::string string, rapidjson::Document::AllocatorType& allocator);
public:
    int getNewNoteId();

    bool canTrust(std::string userName, std::string password);

    rapidjson::Document getUserDetails(std::string userName);

    User* getUser(std::string userName);

    bool createUser (std::string userName, std::string password, std::string createdByAdminUserName, bool isRegular,std::string lastLogin);

    bool updateUser(User* user, bool shouldDelete);

    bool deleteUser(User* user);

    bool doesUserExists(std::string userName);

    std::string getNotesList(std::string userName);

    rapidjson::Document getNotesList(int userId);

    Note* getNote(int noteId);

    int createNote(Note* note);

    bool updateNote(rapidjson::Document &note, bool shouldDelete);
    bool updateNote(Note* note, bool shouldDelete);

    void deleteNote(rapidjson::Document &note);

};


#endif //PP4_DAO_H
