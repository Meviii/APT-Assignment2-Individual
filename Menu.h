#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include "GameBoard.h"
#include "LinkedList.h"
#include "Tile.h"
#include "TileBag.h"
#include "Node.h"
#include "GameEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <ctype.h>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;
using std::ws;

/**
 * @brief Menu class, which display the main menu for the overall system
 *
 */
class Menu
{
public:
    /**
     * @brief Construct a new Menu object
     *
     */
    Menu();

    /**
     * @brief Destroy the Menu object, for deleting the dynamic object of the Player
     *
     */
    ~Menu();

    /**
     * @brief display the main menu and get user input from the stdin
     *
     */
    void runMenu();

    /**
     * @brief print the detailed option choices for the player
     *
     */
    void printMenu();

    /**
     * @brief Main logic for the menu object
     *
     */
    void runChoice();

    /**
     * @brief print the detailed credits info
     *
     */
    void printCredits();

    void playerSelection(int i);
    void playerCheck();

    /**
     * @brief launching a new game
     *
     */
    void newGame();

    vector<string> argTokenizer(string input);
    int argCounter(string input);

    /**
     * @brief check weather there are two players in the game
     *
     * @return true
     * @return false
     */
    bool isTwoPlayer();

    /**
     * @brief load the game detailed info from the input filename
     *
     * @param inputFile
     */
    void loadGame(string inputFile);

private:
    bool wordMatcherToggle = false;
    int choice;
    vector<Player *> players;
};

#endif // MENU_H