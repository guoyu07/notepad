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
    std::string users_db = "users_db.txt", notes = "note_db.txt";
    bool isLocked;
    std::ofstream outFile;
    std::ifstream inFile;


public:

    int getNewUserId();
    bool canTrust(std::string userName, std::string password);

    rapidjson::Document getUserDetails(std::string userName);

    User getUser(std::string userName);

    void createUser (std::string userName, std::string password,std::string lastLogin, std::string createdByAdminUserName, bool isRegular);

    void updateUser(rapidjson::Document updatedUser);

    void deleteUser(rapidjson::Document deleteUser);

    bool doesUserExists(std::string userName);

    rapidjson::Document getNotesList(std::string userName);

    rapidjson::Document getNotesList(int userId);

    rapidjson::Document getNote(int NoteId);

    void createNote(rapidjson::Document note);

    void updateNote(rapidjson::Document note);

    void deleteNote(rapidjson::Document note);

    
};


#endif //PP4_DAO_H
