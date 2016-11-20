//
// Created by rchowda on 11/19/2016.
//

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

        return dao.canTrust(json["userName"].GetString(),json["password"].GetString());
    }

    return false;
}

void Manager::createNote(std::string userName, std::string title, std::string body) {
    rapidjson::Document json; json.SetObject(); auto& allocator = json.GetAllocator();

    rapidjson::Value tmp_val;
    tmp_val.SetString(userName.c_str(),userName.length(),allocator);
    json.AddMember("owner",tmp_val,allocator);
    tmp_val.SetString(title.c_str(),title.length(),allocator);
    json.AddMember("noteTitle",tmp_val,allocator);
    tmp_val.SetString(body.c_str(),body.length(),allocator);
    json.AddMember("noteBody",tmp_val,allocator);

    dao.createNote(json);
}

bool Manager::createNote(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    std::cout << json["owner"].GetString() << json["noteTitle"].GetString() << json["noteBody"].GetString() << std::endl;
    if(!json.HasParseError() &&
            json.HasMember("owner") &&
            json.HasMember("noteTitle") &&
            json.HasMember("noteBody") &&
            json["owner"].IsString() &&
            dao.doesUserExists(json["owner"].GetString()) &&
//            json["noteTitle"].IsString() &&
            json["noteTitle"].GetString() != "" &&
//            json["noteBody"].IsString() &&
            json["noteBody"].GetString() != "") {
        dao.createNote(json);
        return true;
    }
    return false;
}

bool Manager::updateNote(std::string userName, int noteId, std::string title, std::string body) {
    rapidjson::Document json; json.SetObject(); auto& allocator = json.GetAllocator();

    rapidjson::Value tmp_val;
    tmp_val.SetString(userName.c_str(),userName.length(),allocator);
    json.AddMember("owner",tmp_val,allocator);
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
       json.HasMember("owner") &&
       json.HasMember("noteId") &&
       json.HasMember("noteTitle") &&
       json.HasMember("noteBody") &&
       json["owner"].IsString() &&
       json["noteId"].IsInt() &&
       json["noteId"].GetInt() >= 0 &&
       dao.doesUserExists(json["owner"].GetString()) &&
       json["noteTitle"].IsString() &&
       json["noteTitle"].GetString() != "" &&
       json["noteBody"].IsString() &&
       json["noteBody"].GetString() != "") {

        return dao.updateNote(json,false);
    }
    return false;
}

bool Manager::deleteNote(std::string userName, int noteId) {
    rapidjson::Document json; json.SetObject(); auto& allocator = json.GetAllocator();

    rapidjson::Value tmp_val;
    tmp_val.SetString(userName.c_str(),userName.length(),allocator);
    json.AddMember("owner",tmp_val,allocator);
    tmp_val.SetInt(noteId);
    json.AddMember("noteId",tmp_val,allocator);

    return dao.updateNote(json, true);
}

bool Manager::deleteNote(std::string jsonStr) {
    rapidjson::Document json; json.Parse(jsonStr.c_str());

    if(!json.HasParseError() &&
       json.HasMember("owner") &&
       json.HasMember("noteId") &&
       json["owner"].IsString() &&
       json["noteId"].IsInt() &&
       json["noteId"].GetInt() >= 0 &&
       dao.doesUserExists(json["owner"].GetString())) {

        return dao.updateNote(json,true);
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
