#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "GameBoard.h"
#include "LinkedList.h"
#include "Tile.h"
#include "TileBag.h"
#include "Node.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::map;
using std::ofstream;
using std::stoi;
using std::string;
using std::stringstream;
using std::to_string;
using std::transform;
using std::vector;
using std::ws;

class GameEngine
{
public:
    GameEngine();
    GameEngine(TileBag *tb, vector<Player *> players, GameBoard *gb);
    void gamePlay();
    int valueByLetter(Letter letter);
    vector<string> argTokenizer(string input);
    void placeTile(string input);
    void changePlayer();
    void replaceTile(string input);
    bool checkGameOver();
    void printWinner();
    void saveGame(string inputFile);
    void setWordMatcherToggle(bool val);
    bool getWordMatcherToggle();

    int curr_player_turn = 0;
    map<char, int> boardRow = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}};

private:
    void readWordList();
    string verticalBotToTopSearch(int col);
    string verticalTopToBotSearch(int col);
    string horizontalRightToLeftSearch(int row);
    string horizontalLeftToRightSearch(int row);
    vector<string> checkWord(vector<string> wordsToCheck);
    vector<string> isWord(int row, int col);

    bool wordMatcherToggle = true;
    std::vector<std::string> checkedWords;
    std::vector<std::string> wordList;
    bool isGameOver;
    TileBag *tb;
    vector<Player *> players;
    GameBoard *gb;
    Player *curr_player;
    map<Letter, int> letterValue = {{'A', 1}, {'B', 3}, {'C', 3}, {'D', 2}, {'E', 1}, {'F', 4}, {'G', 2}, {'H', 4}, {'I', 1}, {'J', 8}, {'K', 5}, {'L', 1}, {'M', 3}, {'N', 1}, {'O', 1}, {'P', 3}, {'Q', 10}, {'R', 1}, {'S', 1}, {'T', 1}, {'U', 1}, {'V', 4}, {'W', 4}, {'X', 8}, {'Y', 4}, {'Z', 10}};

};

#endif // MENU_H