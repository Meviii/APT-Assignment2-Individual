#include "../LinkedList.h"
#include "../Tile.h"
#include "../Menu.h"

#include <iostream>
#include <string>

/**
 * @brief test the functionality for the Menu class
 *
 * @return int
 */

int main(void)
{
    cout << "==================================" << endl;
    cout << "Display the System header info" << endl;
    // display info during the constructor of the Menu function
    Menu menu;

    cout << "==================================" << endl;
    // displty the main menu of the overall program
    cout << "Display the menu" << endl;
    menu.printMenu();
    cout << "printMenu() function passed" << endl;

    cout << "==================================" << endl;
    cout << "Display the Credits" << endl;
    menu.printCredits();
    cout << "printCredits() function passed" << endl;

    cout << "==================================" << endl;
    cout << "Check if Two Players" << endl;
    if (menu.getIsTwoPlayer())
    {
        cout << "isTwoPlayer() function passed" << endl;
    }
    else
    {
        cout << "isTwoPlayer() function failed" << endl;
    }

    return 0;
}
