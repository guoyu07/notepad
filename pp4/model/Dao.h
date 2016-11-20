//
// Created by rchowda on 11/18/16.
//

#ifndef PP4_DAO_H
#define PP4_DAO_H


#include <string>
#include <fstream>
#include "../lib/rapidjson/document.h"
#include "Users/User/User.h"

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

public:
    int getNewNoteId();

    bool canTrust(std::string userName, std::string password);

    rapidjson::Document getUserDetails(std::string userName);

    User* getUser(std::string userName);

    bool createUser (std::string userName, std::string password,std::string lastLogin, std::string createdByAdminUserName, bool isRegular);

    void updateUser(rapidjson::Document &updatedUser);

    void deleteUser(rapidjson::Document &deleteUser);

    bool doesUserExists(std::string userName);

    std::string getNotesList(std::string userName);

    rapidjson::Document getNotesList(int userId);

    rapidjson::Document getNote(int noteId);

    void createNote(rapidjson::Document &note);

    bool updateNote(rapidjson::Document &note, bool shouldDelete);

    void deleteNote(rapidjson::Document &note);

};


#endif //PP4_DAO_H
