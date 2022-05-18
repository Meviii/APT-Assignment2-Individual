#include "../GameBoard.h"
#include "../LinkedList.h"
#include "../TileBag.h"
#include "../Player.h"
#include "../Tile.h"

#include <iostream>
#include <vector>
#include <array>

std::vector<std::vector<Tile*>> testGetBoard();
void testAddTile(int row, int col, Tile* tile);
int testGetSize();
void testPrintBoard();
bool testIsTileValid(int row, int col);


class TestGameBoard {

    private:
        std::vector<Tile*> gameRow;
        std::vector<std::vector<Tile*>> board;

    public:
    
        std::map<char, int> boardRow = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6},
                                        {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13},
                                        {'O', 14}};
    
    
        TestGameBoard(){
            gameRow.assign(BOARD_MAX, nullptr);
            board.assign(BOARD_MAX, gameRow);

            for (int row = 0; row < (this->testGetSize()); row++){
                for (int col = 0; col < (this->testGetSize()); col++){
                    Tile* tmp = new Tile(' ',0);
                    board[row][col] = tmp;
                }
            }
        }

        std::vector<std::vector<Tile*>> testGetBoard(){
            return this->board;
        }

        void testAddTile(int row, int col, Tile* tile){
            this->board[row][col] = tile;
        }

        int testGetSize(){
            return board.size();
        }


        void testPrintBoard(){
            char alpha[15] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
            
            std::cout << "    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  " << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;

            for (int row = 0; row < testGetSize(); row++){
                std::cout << alpha[row] << " ";
                for (int col = 0; col < testGetSize(); col++){
                    if (board[row][col] == nullptr){
                        std::cout << "| ";
                    }else{
                        std::cout << "| " << board[row][col]->getLetter() << " ";
                    }
                }
                std::cout << "|" << std::endl;
            }
        }

        bool testIsTileValid(int row, int col){
            return row < BOARD_MAX && col < BOARD_MAX && (board[row][col] == NULL || board[row][col]->getLetter() == ' ');
        }

        
};

int main(void){
    TestGameBoard* gb = new TestGameBoard();

    //Test 1: Print Empty board
    std::cout << "Printing empty board:" << std::endl;
    gb->testPrintBoard();

    gb->testGetBoard();

    //Test 2: Print board dimensions
    std::cout << "Printing size of board dimension. Expected size = 15:" << std::endl;
    std::cout << "Board is " << gb->testGetSize() << " x " << gb->testGetSize() << std::endl << std::endl;

    //Test 3: Test validity of an open Tile space 
    std::cout << "Testing validity of open tile at Pos (D,3) to place a tile (boolean):" << std::endl;
    if(gb->testIsTileValid(3,3) != 0){
        std::cout << "(D,3) is a valid space to place a tile." << std::endl;
    } else {
        std::cout << "(D,3) is not a valid space to place a tile." << std::endl;
    }
    std::cout << "The return value is: " << gb->testIsTileValid(3,3) << std::endl << std::endl;

    //Test 4: Place a Tile and print the board
    std::cout << "Placing tile 'A' at Pos (D,3) and printing the game board state:" << std::endl;
    Tile* testTile = new Tile('A',1);
    gb->testAddTile(3, 3, testTile);
    gb->testPrintBoard();
    std::cout << std::endl << std::endl;

    //Test 5: Test validity of an occupied Tile space
    std::cout << "Testing validity of now occupied tile at Pos (D,3) to place a tile (boolean):" << std::endl;
     if(gb->testIsTileValid(3,3) != 0){
        std::cout << "(D,3) is a valid space to place a tile." << std::endl;
    } else {
        std::cout << "(D,3) is not a valid space to place a tile." << std::endl;
    }
    std::cout << "The return value is: " << gb->testIsTileValid(3,3) << std::endl;

    return EXIT_SUCCESS;
}