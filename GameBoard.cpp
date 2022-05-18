#include "GameBoard.h"

#include <iostream>

/*
 * Construct a new Game Board:: Game Board object
 * Assigns empty tiles to each co-ordinate on the GameBoard
 */
GameBoard::GameBoard()
{
    gameRow.assign(BOARD_MAX, nullptr);
    board.assign(BOARD_MAX, gameRow);

}

std::vector<std::vector<Tile *>> GameBoard::getBoard()
{
    return this->board;
}

void GameBoard::addTile(int row, int col, Tile *tile)
{
    this->board[row][col] = tile;
}

int GameBoard::getSize()
{
    return board.size();
}

/*
 * Prints current state of GameBoard object to output
 */
void GameBoard::printBoard()
{
    char alpha[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};

    std::cout << "    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  " << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    for (int row = 0; row < getSize(); row++)
    {
        std::cout << alpha[row] << " ";
        for (int col = 0; col < getSize(); col++)
        {
            if (board[row][col] == nullptr)
            {
                std::cout << "|   ";
            }
            else
            {
                std::cout << "| " << board[row][col]->getLetter() << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
}

/*
 * Checks for validity of a Tile
 * Returns true if Tile is within GameBoard bounds
 * and if the Tile is open
 */
bool GameBoard::isTileValid(int row, int col)
{
    return row < BOARD_MAX && col < BOARD_MAX && board[row][col] == NULL && row >= 0 && col >= 0;
    
}

/*
 * Checks for adjacency of tile
 * Returns true if Tile is within GameBoard bounds
 * and if the Tile is open
 */
bool GameBoard::isTileAdj(int row, int col) 
{   
    if ((row-1) < BOARD_MAX && (row-1) >= 0) {
        if (row+1 < BOARD_MAX && (row+1) >= 0){
            if (col-1 < BOARD_MAX && (col-1) >= 0){
                if (col+1 < BOARD_MAX && (col+1) >= 0){
                    if (board[(row-1)][col] != NULL || board[(row+1)][col] != NULL || board[row][(col-1)] != NULL || board[row][(col+1)] != NULL)
                    {
                        return true;
                    }    
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    return false;
}