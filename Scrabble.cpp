#include "LinkedList.h"
#include "Menu.h"
#include "Player.h"

#include <iostream>
#include <fstream>

#define EXIT_SUCCESS 0

int main(int argc, char *args[])
{

      Menu *menu = new Menu();
      menu->runMenu();

   return EXIT_SUCCESS;
}