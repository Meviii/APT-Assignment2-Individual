#include "../Tile.h"

#include <iostream>
#include <string>

/**
 * @brief test the functionality of the Tile class
 *
 * @return int
 */
int main(void)
{
    // 26 amount of Tile pointer array, which used for testing
    Tile *tiles[26];
    for (int i = 0; i < 26; i++)
    {
        // allocating new Tile object with specified value for each element of the tiles
        tiles[i] = new Tile('A' + i, i);
    }

    for (int i = 0; i < 26; i++)
    {
        // print the promption information
        cout << "Tile Letter: " << tiles[i]->getLetter() << " Tiles Value" << tiles[i]->getValue();

        // if the result matched the expected result, print passed
        if ((tiles[i]->getLetter() == 'A' + i) && (tiles[i]->getValue() == i))
        {
            cout << ", test " << i << " Passed." << endl;
        }
        else
        {
            cout << ", test " << i << " Failed." << endl;
        }
    }

    // delete the dynamic memory allocated
    for (int i = 0; i < 26; i++)
    {
        delete tiles[i];
        tiles[i] = nullptr;
    }

    return 0;
}
