//
// Created by rchowda on 11/18/16.
//

#include <iostream>
#include <ctime>
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
                User* user = new User(userName,password,getTimeStamp());
                updateUser(user,false);
                delete user;
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

//creates new instance //caller should delete after use
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

    if(!outFile.is_open()){outFile.open(users_db,std::ios_base::app);}
    outFile << buffer.GetString() << std::endl;
    outFile.close();

    return true;

}

//haven't tested - may work
bool Dao::updateUser(User* user, bool shouldDelete) {
    std::string tempFile = "tmp_users_db.txt";
    bool didSkip = false;

    outFile.open(tempFile, std::ios_base::out);
    if(!inFile.is_open()) { inFile.open(users_db, std::ios_base::in);}
    if(inFile.good()) {
        std::string tmp_str, userName = user->getUserName();
        char *tmp_char;

        rapidjson::Document json, outJson; outJson.SetObject(); rapidjson::Document::AllocatorType& allocator = outJson.GetAllocator();
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        while (std::getline(inFile,tmp_str)) {
            tmp_char = &tmp_str[0]; json.Parse(tmp_char);
            if(json["userName"].GetString() == userName){
                if(shouldDelete){ didSkip = true; continue;}  // Deletes

                rapidjson::Value &lastLogin = json["lastLogin"]; lastLogin.SetString(user->getLastLogin().c_str(),user->getLastLogin().length());
                //Add any update if required

                json.Accept(writer);
                outFile << buffer.GetString() << std::endl;
                while (std::getline(inFile, tmp_str)) outFile << tmp_str << std::endl;

                inFile.close();
                outFile.close();
                std::rename(tempFile.c_str(), users_db.c_str());
                // assert(!success);
                return true;
            }
            outFile << tmp_str << std::endl;
        }

    }
    inFile.close();
    outFile.close();
    if(shouldDelete)
        std::rename(tempFile.c_str(), users_db.c_str());
    else
        std::remove(tempFile.c_str());
    return didSkip;

}

//done
bool Dao::deleteUser(User* user) {
    return updateUser(user, true);
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

//done - can be improved
std::string Dao::getNotesList(std::string userName) {
    if(!inFile.is_open()) { inFile.open(notes_db);}
    if(inFile.good()) {
        std::string tmp_str;
        char *tmp_char;

        rapidjson::Document json, outJson; outJson.SetObject(); rapidjson::Document::AllocatorType& allocator = outJson.GetAllocator();
        rapidjson::Value index, tmp_val, note; note.SetObject();
        rapidjson::Value notesArray(rapidjson::kArrayType);

        int count = 0;

//        if (!inFile.eof()) { std::getline(inFile, tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

        while (std::getline(inFile,tmp_str)) {
            tmp_char = &tmp_str[0]; json.Parse(tmp_char);
            if(json["userName"].GetString() == userName){
                note.SetObject(); note.RemoveAllMembers();
                index.SetString(std::to_string(count).c_str(),std::to_string(count++).length(),allocator);

                note.AddMember("noteId",json["noteId"],allocator);
                note.AddMember("noteTitle",json["noteTitle"],allocator);
                note.AddMember("noteBody",json["noteBody"],allocator);
                //note.AddMember("noteLastModified",json["lastModified"],allocator);

                notesArray.PushBack(note,allocator);


            }
        }
        outJson.AddMember("notes",notesArray,allocator);
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        outJson.Accept(writer);

        return buffer.GetString();
    }
    return NULL;
}

rapidjson::Document Dao::getNotesList(int userId) {
    return rapidjson::Document();
}

//haven't tested
Note* Dao::getNote(int noteId) {
    if(noteId >= 0){
        if(!inFile.is_open()) { inFile.open(users_db);}
        if(inFile.good()){
            std::string tmp_str;
            char* tmp_char;
            rapidjson::Document json;

            while (std::getline(inFile,tmp_str)){
                tmp_char = &tmp_str[0]; json.Parse(tmp_char);
                if(json["noteId"].GetInt() == noteId){
                    inFile.close();
                    Note* note = new
                    Note(noteId, json["noteTitle"].GetString(), json["noteBody"].GetString(), json["lastModified"].GetString(), getUser(json["userName"].GetString()));
                    return note;
                }
            }
        }
        inFile.close();
    }
    return new Note();
}

void Dao::createNote(rapidjson::Document &note) {
    rapidjson::Document json; json.SetObject(); rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
    rapidjson::Value tmp_val;

    if(note.HasMember("noteTitle") && note.HasMember("noteBody") && note.HasMember("userName") &&
            note["noteTitle"].IsString() && note["noteBody"].IsString() && note["userName"].IsString() &&
            note["noteTitle"].GetString() != "" && note["noteBody"].GetString() != "" && note["userName"].GetString() != ""){
        tmp_val.SetInt(getNewNoteId()); json.AddMember("noteId",tmp_val,allocator);
        tmp_val = note["noteTitle"];    json.AddMember("noteTitle",tmp_val,allocator);
        tmp_val = note["noteBody"];     json.AddMember("noteBody",tmp_val,allocator);
        tmp_val = note["userName"];        json.AddMember("userName",tmp_val,allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        json.Accept(writer);

        if(!outFile.is_open()){outFile.open(notes_db,std::ios_base::app);}
        outFile << buffer.GetString() << std::endl;
        outFile.close();
    }

}

bool Dao::updateNote(rapidjson::Document &note, bool shouldDelete) {
    std::string tempFile = "tmp_notes_db.txt";
    bool didSkip = false;

    outFile.open(tempFile, std::ios_base::out);
    if(!inFile.is_open()) { inFile.open(notes_db, std::ios_base::in);}
    if(inFile.good()) {
        std::string tmp_str, userName = note["userName"].GetString();
        char *tmp_char;


        rapidjson::Document json, outJson; outJson.SetObject(); rapidjson::Document::AllocatorType& allocator = outJson.GetAllocator();
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

//        if (!inFile.eof()) { std::getline(inFile, tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char); }

        while (std::getline(inFile,tmp_str)) {
            tmp_char = &tmp_str[0]; json.Parse(tmp_char);
            if(json["noteId"].GetInt() == note["noteId"].GetInt() &&
                    json["userName"].GetString() == userName) {

                if(shouldDelete){ didSkip = true; continue;}  // Deletes
                rapidjson::Value &title = json["noteTitle"];
                title = note["noteTitle"];
                rapidjson::Value &body = json["noteBody"];
                body = note["noteBody"];


                json.Accept(writer);
                outFile << buffer.GetString() << std::endl;
                while (std::getline(inFile, tmp_str)) outFile << tmp_str << std::endl;

                inFile.close();
                outFile.close();
                std::rename(tempFile.c_str(), notes_db.c_str());
                // assert(!success);
                return true;
            }
            outFile << tmp_str << std::endl;

        }
    }
    inFile.close();
    outFile.close();
    if(shouldDelete)
        std::rename(tempFile.c_str(), notes_db.c_str());
    else
        std::remove(tempFile.c_str());
    return didSkip;

}

bool Dao::updateNote(Note *note, bool shouldDelete) {
    std::string tempFile = "tmp_notes_db.txt";
    bool didSkip = false;

    outFile.open(tempFile, std::ios_base::out);
    if(!inFile.is_open()) { inFile.open(notes_db, std::ios_base::in);}
    if(inFile.good()) {
        std::string tmp_str;
        char *tmp_char;

        rapidjson::Document json, outJson;
        outJson.SetObject();
        rapidjson::Document::AllocatorType &allocator = outJson.GetAllocator();
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        while (std::getline(inFile, tmp_str)) {
            tmp_char = &tmp_str[0]; json.Parse(tmp_char);

            if(json["noteId"].GetInt() == note->getNoteId() &&
                    json["userName"].GetString() == note->getUserName()->getUserName()){

                if(shouldDelete) {didSkip = true; continue;}
                rapidjson::Value &title = json["noteTitle"]; title.SetString(note->getTitle().c_str(),note->getTitle().length());
                rapidjson::Value &body  = json["noteBody"];  body.SetString(note->getBody().c_str(), note->getBody().length());
                rapidjson::Value &lastM = json["lastModified"]; lastM.SetString(note->getLastModified().c_str(), note->getLastModified().length());

                json.Accept(writer);
                outFile << buffer.GetString() << std::endl;
                while (std::getline(inFile, tmp_str)) outFile << tmp_str << std::endl;

                inFile.close();
                outFile.close();
                std::rename(tempFile.c_str(), notes_db.c_str());
                // assert(!success);
                return true;
            }
            outFile << tmp_str << std::endl;
        }
    }
    inFile.close();
    outFile.close();
    if(shouldDelete)
        std::rename(tempFile.c_str(), notes_db.c_str());
    else
        std::remove(tempFile.c_str());
    return didSkip;
}

void Dao::deleteNote(rapidjson::Document &note) {
    updateNote(note,true);

}
//done - maybe
int Dao::getNewNoteId(){
    int id =-1;

    if(!inFile.is_open()) { inFile.open(notes_db);}
    if(inFile.good()){
        std::string tmp_str;
        char* tmp_char;
        rapidjson::Document json;


        while (!inFile.eof()){
            std::getline(inFile,tmp_str);tmp_char = &tmp_str[0]; json.Parse(tmp_char);
        }

        if(json.IsObject() && json.HasMember("noteId") && json["noteId"].IsInt()){
            id = json["noteId"].GetInt();
        }
    }
    inFile.close();
    return ++id;
}

std::string Dao::getTimeStamp() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    std::time (&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}
//int main(){
//    Dao dao;
//
////    dao.createUser("Raghu","asdfasdf","neeva","Raghuvaran",true);
//    std::cout << dao.canTrust("Raghuvaran","hell") << std::endl;
//    std::cout << dao.canTrust("Raghuvaran","helo") << std::endl;
//    std::cout << dao.canTrust("Raghuvaran","hello") << std::endl;
//    std::cout << dao.canTrust("Raghuvaran","hello3") << std::endl;
//    std::cout << dao.canTrust("Raghuvaran","hellosdf") << std::endl;
//
//    rapidjson::Document note; note.SetObject(); auto& allocator = note.GetAllocator();
//    std::string
//        title = "Hi how are you doing?",
//        body  = "He picks up the line by numbytes in fseek, but the data line may vary and numbytes not be accurate, how can I fix this?",
//        userName = "Raghuvaran";
//
//    rapidjson::Value tmp_val;
//    tmp_val.SetInt(-1);
//    note.AddMember("noteId",tmp_val,allocator);
//    tmp_val.SetString(&title[0],title.length(),allocator);
//    note.AddMember("noteTitle",tmp_val,allocator);
//    tmp_val.SetString(&body[0],body.length(),allocator);
//    note.AddMember("noteBody",tmp_val,allocator);
//    tmp_val.SetString(&userName[0],userName.length(),allocator);
//    note.AddMember("userName",tmp_val,allocator);
//
//
//    std::cout << dao.getNotesList("Raghuv") <<std::endl;
//
//
//
//}