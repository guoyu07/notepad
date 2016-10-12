#include <iostream>
#include <sstream>
#include <fstream>

#include "controller/TTTController.h"

int main() {
    std::cout << "content-type: text/html\n\n";

    //receive json into string
    std::stringstream inBuff;

   inBuff << std::cin.rdbuf();

    std::string inJsonRequest = inBuff.str();

//    std::ofstream file("jsonOut");
//    file << inJsonRequest;
//    file.close();
//
//    std::cout << inJsonRequest ; return 0;

//    std::cin >> inJsonRequest;

    TTTController tttController;
    //check string for identifiers
    std::string identifier;
    tttController.partParseJson(inJsonRequest,identifier);

    switch (identifier[0]) {
        case 'G':
            std::cout << tttController.getAllSavedPlayers(); break;
        //'G' -> @return getAllSavedPlayers
        case 'P': {
            //'P' -> has
            /*
             * Player1: Name, Marker
             * Player2: Name, Marker
             * Cursor: All positions; 1- as P1 marker, 2- as P2 marker, 0- as not yet marked
             *
             * @return: getGameDisplay(true); determineWinner
             * */
            std::string player_name, player_marker, cursor;

            //parse and create new players
            tttController.partParseJson(inJsonRequest, player_name);
            tttController.partParseJson(inJsonRequest, player_marker);
            tttController.createPlayer(player_name, player_marker, 1);
            tttController.partParseJson(inJsonRequest, player_name);
            tttController.partParseJson(inJsonRequest, player_marker);
            tttController.createPlayer(player_name, player_marker, 2);


            tttController.startNewGame();

            //parse cursor into array
            tttController.partParseJson(inJsonRequest, cursor);
            // setSelection accordingly
            for (int i = 0; i < 9; i++) {
                if (cursor[i] == '1') tttController.setSelection(i, 1);
                else if (cursor[i] == '2') tttController.setSelection(i, 2);
            }
            cursor = tttController.getGameDisplay(true);
            cursor.pop_back();
            std::cout << cursor << ",\"winner\":" << tttController.determineWinner() << "}";
            break;
        }
        default:
        std::cout << "{\"error\":147}";
    }
}