#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::string;

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

/**
 * @brief Tile represent a letter with a specified score value
 *
 */
class Tile
{
public:
   Letter letter; // letter of the Tile
   Value value;   // score value of the Tile

   /**
    * @brief Construct a new Tile object
    *
    * @param letter
    * @param value
    */
   Tile(Letter letter, Value value);

   /**
    * @brief Construct a new Tile object
    *
    */
   Tile();

   /**
    * @brief Get the Letter object
    *
    * @return Letter
    */
   Letter getLetter();

   /**
    * @brief Get the Value object
    *
    * @return Value
    */
   Value getValue();

private:
};

#endif // ASSIGN2_TILE_H
