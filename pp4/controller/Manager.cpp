//
// Created by rchowda on 11/19/2016.
//

#include <ctime>
#include "Manager.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/writer.h"

bool Manager::authenticate(std::string userName, std::string password) {
    return dao.canTrust(userName,password);
}

bool Manager::authenticate(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(json.HasMember("userName") &&
       json.HasMember("password") &&
       json["userName"].IsString() &&
       json["userName"].GetString() != "" &&
       json["password"].IsString() &&
       json["password"].GetString() != ""){

        if(dao.canTrust(json["userName"].GetString(),json["password"].GetString())) {
            User* user = new User(json["userName"].GetString(),json["password"].GetString(),getTimeStamp());
            dao.updateUser(user,false);
            delete user;
            return true;
        }
    }

    return false;
}

std::string Manager::getRecentLogin(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(json.HasMember("userName") &&
            json["userName"].IsString() &&
            json["userName"].GetString() != ""){
        User* user = dao.getUser(json["userName"].GetString());
        std::string lastLogin = user->getLastLogin();
        delete user;
        return lastLogin;
    }


}

bool Manager::createUser(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(json.HasMember("userName") &&
       json.HasMember("password") &&
       json["userName"].IsString() &&
       json["userName"].GetString() != "" &&
       json["password"].IsString() &&
       json["password"].GetString() != ""){

        return dao.createUser(json["userName"].GetString(),json["password"].GetString(),"webAdmin",true,getTimeStamp());
    }

    return false;
}

void Manager::createNote(std::string userName, std::string title, std::string body) {
    rapidjson::Document json; json.SetObject(); auto& allocator = json.GetAllocator();

    rapidjson::Value tmp_val;
    tmp_val.SetString(userName.c_str(),userName.length(),allocator);
    json.AddMember("userName",tmp_val,allocator);
    tmp_val.SetString(title.c_str(),title.length(),allocator);
    json.AddMember("noteTitle",tmp_val,allocator);
    tmp_val.SetString(body.c_str(),body.length(),allocator);
    json.AddMember("noteBody",tmp_val,allocator);

    //dao.createNote(json);
}

bool Manager::createNote(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

//    std::cout << json["userName"].GetString() << json["noteTitle"].GetString() << json["noteBody"].GetString() << std::endl;
    if(!json.HasParseError() &&
            json.HasMember("userName") &&
            json.HasMember("noteTitle") &&
            json.HasMember("noteBody") &&
            json["userName"].IsString() &&
            dao.doesUserExists(json["userName"].GetString()) &&
//            json["noteTitle"].IsString() &&
            json["noteTitle"].GetString() != "" &&
//            json["noteBody"].IsString() &&
            json["noteBody"].GetString() != "") {

        User* user = dao.getUser(json["userName"].GetString());
        Note* note = new Note(-1, json["noteTitle"].GetString(), json["noteBody"].GetString(), getTimeStamp(), user);
        if(dao.createNote(note)){
            delete user,note;
            return true;
        }
        delete user,note;
    }
    return false;
}

bool Manager::updateNote(std::string userName, int noteId, std::string title, std::string body) {
    rapidjson::Document json; json.SetObject(); auto& allocator = json.GetAllocator();

    rapidjson::Value tmp_val;
    tmp_val.SetString(userName.c_str(),userName.length(),allocator);
    json.AddMember("userName",tmp_val,allocator);
    tmp_val.SetInt(noteId);
    json.AddMember("noteId",tmp_val,allocator);
    tmp_val.SetString(title.c_str(),title.length(),allocator);
    json.AddMember("noteTitle",tmp_val,allocator);
    tmp_val.SetString(body.c_str(),body.length(),allocator);
    json.AddMember("noteBody",tmp_val,allocator);

    return dao.updateNote(json, false);
}

bool Manager::updateNote(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(!json.HasParseError() &&
       json.HasMember("userName") &&
       json.HasMember("noteId") &&
       json.HasMember("noteTitle") &&
       json.HasMember("noteBody") &&
       json["userName"].IsString() &&
       json["noteId"].IsInt() &&
       json["noteId"].GetInt() >= 0 &&
       dao.doesUserExists(json["userName"].GetString()) &&
       json["noteTitle"].IsString() &&
       json["noteTitle"].GetString() != "" &&
       json["noteBody"].IsString() &&
       json["noteBody"].GetString() != "") {


            Note* note = dao.getNote(json["noteId"].GetInt());
            note->setTitle(json["noteTitle"].GetString());
            note->setBody(json["noteBody"].GetString());
            note->setLastModified(getTimeStamp());
            if(dao.updateNote(note,false)){
                delete note;
                return true;
            }
            delete note;

    }
    return false;
}

bool Manager::deleteNote(std::string userName, int noteId) {
    rapidjson::Document json; json.SetObject(); auto& allocator = json.GetAllocator();

    rapidjson::Value tmp_val;
    tmp_val.SetString(userName.c_str(),userName.length(),allocator);
    json.AddMember("userName",tmp_val,allocator);
    tmp_val.SetInt(noteId);
    json.AddMember("noteId",tmp_val,allocator);

    return dao.updateNote(json, true);
}

bool Manager::deleteNote(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(!json.HasParseError() &&
       json.HasMember("userName") &&
       json.HasMember("noteId") &&
       json["userName"].IsString() &&
       json["noteId"].IsInt() &&
       json["noteId"].GetInt() >= 0 &&
       dao.doesUserExists(json["userName"].GetString())) {

        Note* note = dao.getNote(json["noteId"].GetInt());

        if(dao.updateNote(note, true)){
            delete note->getUserName();
            delete note;
            return true;
        }
        delete note;
    }
    return false;
}

std::string Manager::getNotesList(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(!json.HasParseError() &&
            json.HasMember("userName") &&
            json["userName"].IsString() &&
            json["userName"].GetString() != "" &&
            dao.doesUserExists(json["userName"].GetString())){
        return dao.getNotesList(json["userName"].GetString());
    }

    return NULL;
}

std::string Manager::getTimeStamp() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    std::time (&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}