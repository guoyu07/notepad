//
// Created by rchowda on 10/11/16.
//

#include <iostream>
#include <cstring>

using namespace std;

int main(){

    string jsonUP = "{\"name\":\"Raghuvaran\",\"marker\":\"x\",\"playerNum\":1}";

    string jsonStr;

    jsonStr = jsonUP;

    cout << jsonUP;

    cout << endl;

    char* json;

    json = new char[jsonUP.length()+1];

    strcpy(json,jsonUP.c_str());

    string name, marker; int playerNum, switcher =0;

    int cursor = jsonStr.find(":");

    cursor+=2;

    name = jsonStr.substr(cursor,jsonStr.find("\"",cursor)-cursor);

    jsonStr = jsonStr.substr(cursor);

    cursor = jsonStr.find(":");

    cursor+=2;

    marker = jsonStr.substr(cursor,jsonStr.find("\"",cursor)-cursor);

    jsonStr = jsonStr.substr(cursor);
    
    cursor = jsonStr.find(":");

    cursor+=1;

    cout << jsonStr.substr(cursor,jsonStr.find("}",cursor)-cursor);








    cout << endl;
    for(int i = 0; i < jsonUP.length(); i++){
        if(json[i] == ':'){
            ++switcher;
            i++;
//            if(json[i+1]=='"') i+=1;
//            if(json[i+1]!='"') i+=1;
        }
        switch (switcher){
            case 1:
                name.push_back(json[i]); if(json[i] == '"') switcher =0; break;
            case 2:
                marker.push_back(json[i]); if(json[i] == '"') switcher =0; break;
            case 3:
                cout << i;
                playerNum = std::atoi(&json[i]); switcher = 0;break;


        }
//        if(switcher!= 0 && json[i] == '"') switcher =0;
    }


 //   cout << name << endl;cout << marker << endl;cout << playerNum<< endl;


}