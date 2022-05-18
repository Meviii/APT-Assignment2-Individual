#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <vector>
#include <array>

#include "LinkedList.h"
#include "TileBag.h"
#include "Player.h"

using std::vector;

#define BOARD_MAX  15
#define BOARD_MIN  0

class GameBoard
{
public:
    GameBoard();
    std::vector<std::vector<Tile *>> getBoard();
    void printBoard();
    void addTile(int row, int col, Tile *tile);
    int getSize();
    bool isTileValid(int row, int col);
    bool isTileAdj(int row, int col);
private:
    std::vector<Tile *> gameRow;
    std::vector<std::vector<Tile *>> board;
};

#endif // GAMEBOARD_H