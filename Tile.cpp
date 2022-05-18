#include "Tile.h"

/**
 * @brief Construct a new Tile:: Tile object
 *
 * @param letter
 * @param value
 */
Tile::Tile(Letter letter, Value value)
{
    this->letter = letter;
    this->value = value;
}

/**
 * @brief Construct a new Tile:: Tile object
 *
 */
Tile::Tile() {}

/**
 * @brief get the letter of the Tile
 *
 * @return Letter
 */
Letter Tile::getLetter()
{
    return this->letter;
}

/**
 * @brief get the score value of the Tile
 *
 * @return Value
 */
Value Tile::getValue()
{
    return this->value;
}