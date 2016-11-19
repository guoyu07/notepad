//
// Created by rchowda on 11/18/16.
//

#include <iostream>
#include "Dao.h"
#include "../lib/rapidjson/writer.h"
#include "Users/User/User.h"
#include "Users/regularUser.h"
#include "Users/adminUser.h"

bool Dao::canTrust(std::string userName, std::string password) {

    return false;
}

rapidjson::Document Dao::getUserDetails(std::string userName) {
    return rapidjson::Document();
}

std::string Dao::getUser(std::string userName) {
    if(doesUserExists(userName)){
        if(!inFile.is_open()) { inFile.open(users_db);}
        if(inFile.good()){
            std::string tmp_str;
            char* tmp_char;
            rapidjson::Document json;

            if(!inFile.eof()){ std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

            while (!inFile.eof()){
                if(json["userName"].GetString() == userName){
                    inFile.close();
                    return true;
                }
                std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char);
            }
        }
        inFile.close();
    }

    return User();
}

bool Dao::createUser(std::string userName, std::string password,std::string lastLogin, std::string createdByAdminUserName, bool isRegular) {
    if(doesUserExists(userName)) return false;
    User* newUser;
    if(isRegular){
       newUser = new regularUser(getNewUserId(),userName,password,lastLogin,getUser(createdByAdminUserName));
    }else {
       newUser = new adminUser(getNewUserId(),userName,password,lastLogin);
    }

    rapidjson::Document json; json.SetObject(); rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
    rapidjson::Value tmp_val;
    tmp_val.SetInt(newUser->getUserId());
    json.AddMember("userId",tmp_val, allocator);
    tmp_val.SetString(&newUser->getUserName()[0],newUser->getUserName().length(),allocator);
    json.AddMember("userName",tmp_val,allocator);
    tmp_val.SetString(&newUser->getPassword()[0],newUser->getPassword().length(),allocator);
    json.AddMember("password",tmp_val,allocator);
    tmp_val.SetInt(getUser(createdByAdminUserName).getUserId());
    json.AddMember("parent",tmp_val,allocator);
    tmp_val.SetString(&lastLogin[0], lastLogin.length(), allocator);
    json.AddMember("lastLogin",tmp_val,allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    json.Accept(writer);
    std::cout << buffer.GetString() << '\n';
    if(!outFile.is_open()){outFile.open(users_db,std::ios_base::app); printf("Opened file \n");}
    outFile << buffer.GetString() << std::endl;
    outFile.close();

    return true;

}

void Dao::updateUser(rapidjson::Document updatedUser) {

}

void Dao::deleteUser(rapidjson::Document deleteUser) {

}
//done
bool Dao::doesUserExists(std::string userName) {

    if(!inFile.is_open()) { inFile.open(users_db);}
    if(inFile.good()){
        std::string tmp_str;
        char* tmp_char;
        rapidjson::Document json;

        if(!inFile.eof()){ std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

        while (!inFile.eof()){
            if(json["userName"].GetString() == userName){
                inFile.close();
                return true;
            }
            std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char);
        }
    }
    inFile.close();
    return false;
}

rapidjson::Document Dao::getNotesList(std::string userName) {
    return rapidjson::Document();
}

rapidjson::Document Dao::getNotesList(int userId) {
    return rapidjson::Document();
}

rapidjson::Document Dao::getNote(int NoteId) {
    return rapidjson::Document();
}

void Dao::createNote(rapidjson::Document note) {

}

void Dao::updateNote(rapidjson::Document note) {

}

void Dao::deleteNote(rapidjson::Document note) {

}
//done - maybe
int Dao::getNewUserId(){
    int id =-1;

    if(!inFile.is_open()) { inFile.open(users_db);}
    if(inFile.good()){
        std::string tmp_str;
        char* tmp_char;
        rapidjson::Document json;


        while (!inFile.eof()){
            std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char);
        }

        if(json.IsObject() && json.HasMember("userId") && json["userId"].IsInt()){
            id = json["userId"].GetInt();
        }
    }
    inFile.close();
    return ++id;
}

int main(){
    Dao dao;
    std::cout << dao.getNewUserId() << std::endl;
    dao.createUser("Raghu","asdfasdf","neeva","Raghuvaran",true);
    std::cout << dao.getUser("Raghuvaran").getUserId() << std::endl;
    std::cout << dao.getNewUserId() << std::endl;
}