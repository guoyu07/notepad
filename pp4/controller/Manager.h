//
// Created by rchowda on 11/19/2016.
//

#ifndef PP4_MANAGER_H
#define PP4_MANAGER_H


#include "../model/Dao.h"

class Manager {
    Dao dao;
public:
    bool authenticate(std::string userName, std::string password);
    bool authenticate(std::string jsonStr);

    void createNote(std::string userName, std::string title, std::string body);
    bool createNote(std::string jsonStr);


    bool updateNote(std::string userName, int noteId, std::string title, std::string body);
    bool updateNote(std::string jsonStr);

    bool deleteNote(std::string userName, int noteId);
    bool deleteNote(std::string jsonStr);

    std::string getNotesList(std::string jsonStr);
};


#endif //PP4_MANAGER_H
