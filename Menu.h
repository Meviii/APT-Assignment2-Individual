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
    Menu();
    ~Menu();
    
    void runMenu();
    void printMenu();
    void runChoice();
    void printCredits();

    void playerSelection(int i);
    void playerCheck();
    void newGame();

    vector<string> argTokenizer(string input);
    int argCounter(string input);

    bool getIsTwoPlayer();
    void setIsTwoPlayer(bool val);

    void loadGame(string inputFile);

    void readPlayerFile();
private:
    //void readPlayerFile();
    // void sortPlayerScoreMap();
    bool isPlayerNameUnique(string name);
    bool compareValues(std::pair<string, int>& a, std::pair<string, int>& b);
    vector < std::pair<string, int> > nameScoreVector;
    bool isTwoPlayer = true;
    bool wordMatcherToggle = false;
    int choice;
    vector<Player *> players;
};

#endif // MENU_H