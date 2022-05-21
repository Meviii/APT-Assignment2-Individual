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
    menu->readPlayerFile();
    return 0;
}