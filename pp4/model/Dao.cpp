//
// Created by rchowda on 11/18/16.
//

#include <iostream>
#include "Dao.h"
#include "../lib/rapidjson/writer.h"
#include "Users/regularUser.h"
#include "Users/adminUser.h"

//done - can be improved
bool Dao::canTrust(std::string userName, std::string password) {
    if(!inFile.is_open()) { inFile.open(users_db);}
    if(inFile.good()){
        std::string tmp_str;
        char* tmp_char;
        rapidjson::Document json;

        if(!inFile.eof()){ std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

        while (!inFile.eof()) {
            if(json["userName"].GetString() == userName && json["password"].GetString() == password){
                inFile.close();
                //TODO update lastLogin
                return true;
            }//TODO else update invalid login counter

            std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);
        }
        }
    inFile.close();
    return false;
}

rapidjson::Document Dao::getUserDetails(std::string userName) {
    return rapidjson::Document();
}

User* Dao::getUser(std::string userName) {
    if(doesUserExists(userName)){
        if(!inFile.is_open()) { inFile.open(users_db);}
        if(inFile.good()){
            std::string tmp_str;
            char* tmp_char;
            rapidjson::Document json;

            if(!inFile.eof()){ std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

            while (!inFile.eof()){
                if(json["userName"].GetString() == userName){
                    inFile.close();
                    User* user;
                    if(json["parent"].GetString() == userName){
                        user = new adminUser(json["userName"].GetString(),json["password"].GetString(),json["lastLogin"].GetString());
                    }else{
                        user = new regularUser(json["userName"].GetString(),json["password"].GetString(),json["lastLogin"].GetString(),getUser(json["parent"].GetString()));
                    }
                    return user;
                }
                std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char);
            }
        }
        inFile.close();
    }

    return new User();
}

bool Dao::createUser(std::string userName, std::string password,std::string lastLogin, std::string createdByAdminUserName, bool isRegular) {
    if(doesUserExists(userName)) return false;
    User* newUser;
    if(isRegular){
       newUser = new regularUser(userName,password,lastLogin,getUser(createdByAdminUserName));
    }else {
       newUser = new adminUser(userName,password,lastLogin);
    }

    rapidjson::Document json; json.SetObject(); rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
    rapidjson::Value tmp_val;
    tmp_val.SetString(&newUser->getUserName()[0],newUser->getUserName().length(),allocator);
    json.AddMember("userName",tmp_val,allocator);
    tmp_val.SetString(&newUser->getPassword()[0],newUser->getPassword().length(),allocator);
    json.AddMember("password",tmp_val,allocator);
    tmp_val.SetString(&getUser(createdByAdminUserName)->getUserName()[0],getUser(createdByAdminUserName)->getUserName().length(), allocator);
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

//haven't tested!
rapidjson::Document Dao::getNotesList(std::string userName) {
    if(!inFile.is_open()) { inFile.open(users_db);}
    if(inFile.good()) {
        std::string tmp_str;
        char *tmp_char;

        rapidjson::Document json, outJson,; outJson.SetObject(); rapidjson::Document::AllocatorType& allocator = outJson.GetAllocator();
        rapidjson::Value index, tmp_val, note; note.SetObject();

        int count = 0;

        if (!inFile.eof()) { std::getline(inFile, tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

        while (!inFile.eof()) {
            if(json["owner"].GetString() == userName){
                note.SetObject(); note.RemoveAllMembers();
                index.SetString(std::to_string(count).c_str(),std::to_string(count++).length(),allocator);

                note.AddMember("noteId",json["noteId"],allocator);
                note.AddMember("noteTitle",json["noteTitle"],allocator);
                note.AddMember("noteBody",json["noteBody"],allocator);
                //note.AddMember("noteLastModified",json["lastModified"],allocator);

                outJson.AddMember(index, note, allocator);

            }
        }

        return outJson;
    }
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

//    dao.createUser("Raghu","asdfasdf","neeva","Raghuvaran",true);
    std::cout << dao.canTrust("Raghuvaran","hell") << std::endl;
    std::cout << dao.canTrust("Raghuvaran","helo") << std::endl;
    std::cout << dao.canTrust("Raghuvaran","hello") << std::endl;
    std::cout << dao.canTrust("Raghuvaran","hello3") << std::endl;
    std::cout << dao.canTrust("Raghuvaran","hellosdf") << std::endl;




}