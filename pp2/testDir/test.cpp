//
// Created by rchowda on 10/11/16.
//

#include <iostream>
#include <cstring>

using namespace std;

void partParseJson(std::string& json, std::string& key, unsigned long& cursor){
    unsigned long endCursor =0;
    cursor = json.find(":");

    if(json.find(":\"")!= string::npos){
        cursor+=2;
        key = json.substr(cursor,json.find("\"",cursor)-cursor);
        endCursor = json.find("\"",cursor)+2;
    }
    else if(json.find(",")!= string::npos){
        cursor+=1;
        key = json.substr(cursor,json.find(",",cursor)-cursor);
        endCursor = json.find(",",cursor)+2;
    }
    else {
        cursor+=1;
        key = json.substr(cursor,json.find("}",cursor)-cursor);
        endCursor = json.find("}",cursor)+1;
    }

    json = json.substr(endCursor);

}

int main(){

    string jsonUP = "{\"name\":\"Raghuvaran\",\"marker\":\"x\",\"playerNum\":\"Hi There\"}";

    string jsonStr;

    jsonStr = jsonUP;

    cout << jsonUP;

    cout << endl;

    char* json;

    json = new char[jsonUP.length()+1];

    strcpy(json,jsonUP.c_str());

    string name, marker, playerNum;//, switcher =0;

    unsigned long cursor = 0;

    partParseJson(jsonStr,name,cursor);
    partParseJson(jsonStr,marker,cursor);
    partParseJson(jsonStr,playerNum,cursor);

//    int cursor = jsonStr.find(":");
//
//    cursor+=2;
//
//    name = jsonStr.substr(cursor,jsonStr.find("\"",cursor)-cursor);
//
//    jsonStr = jsonStr.substr(cursor);
//
//    cursor = jsonStr.find(":");
//
//    cursor+=2;
//
//    marker = jsonStr.substr(cursor,jsonStr.find("\"",cursor)-cursor);
//
//    jsonStr = jsonStr.substr(cursor);
//
//    cursor = jsonStr.find(":");
//
//    cursor+=1;
//
//    playerNum = std::stoi(jsonStr.substr(cursor,jsonStr.find("}",cursor)-cursor));
//







    cout << endl;
//    for(int i = 0; i < jsonUP.length(); i++){
//        if(json[i] == ':'){
//            ++switcher;
//            i++;
////            if(json[i+1]=='"') i+=1;
////            if(json[i+1]!='"') i+=1;
//        }
//        switch (switcher){
//            case 1:
//                name.push_back(json[i]); if(json[i] == '"') switcher =0; break;
//            case 2:
//                marker.push_back(json[i]); if(json[i] == '"') switcher =0; break;
//            case 3:
//                cout << i;
//                playerNum = std::atoi(&json[i]); switcher = 0;break;
//
//
//        }
////        if(switcher!= 0 && json[i] == '"') switcher =0;
//    }


    cout << name << endl;cout << marker << endl;cout << playerNum<< endl;


}