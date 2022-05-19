#include "../GameEngine.h"
#include "../Menu.h"
#include "../LinkedList.h"
#include "../Tile.h"

#include <map>
#include <iterator>
#include <fstream>
#include <iostream>

int main(void){
    Menu* menu = new Menu();
    
    menu->loadGame("savegame.sav");

    // string place_tile_input = "place A at A1";
    // ge->placeTile(place_tile_input);
    // gb->printBoard();
    return 0;
}