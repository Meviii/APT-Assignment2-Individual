#include "Player.h"

Player::Player()
{
    hand = new LinkedList();
}

Player::Player(string name, LinkedList *tile_hand)
{
    this->name = name;
    this->score = 0;
    this->hand = tile_hand;
    this->passCounter = 0;
}

int Player::getPassCounter()
{
    return passCounter;
}

void Player::setPassCounter(int pass_counter)
{
    this->passCounter = pass_counter;
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
}

string Player::getName()
{
    return name;
}

void Player::setName(string name)
{
    this->name = name;
}

void Player::setHand(TileBag *tb)
{
    for (int i = 0; i < PLAYER_HAND_AMOUNT; i++)
    {
        this->hand->addBack(tb->getFront());
        tb->removeFront();
    }
    return;
}

LinkedList *Player::getHand()
{
    return hand;
}

void Player::addToHand(Tile *tile)
{
    this->hand->addBack(tile);
}

int Player::getHandSize()
{
    return hand->getSize();
}

void Player::printHand()
{
    cout << "Your hand is: " << endl;

    Node *h = hand->getHead();
    for (int i = 0; i < PLAYER_HAND_AMOUNT; i++)
    {
        if (i == (PLAYER_HAND_AMOUNT - 1))
        {
            cout << h->tile->getLetter() << "-" << h->tile->getValue();
        }
        else
        {
            cout << h->tile->getLetter() << "-" << h->tile->getValue() << ", ";
        }
        h = h->next;
    }
    cout << endl;
}

void Player::printRawHand()
{
    Node *h = hand->getHead();
    for (int i = 0; i < PLAYER_HAND_AMOUNT; i++)
    {
        if (i == (PLAYER_HAND_AMOUNT - 1))
        {
            cout << h->tile->getLetter() << "-" << h->tile->getValue();
        }
        else
        {
            cout << h->tile->getLetter() << "-" << h->tile->getValue() << ", ";
        }
        h = h->next;
    }
}

Tile *Player::getTileInHand(Letter letter)
{
    Node *h = this->hand->getHead();
    Tile *toRet;
    while (h != nullptr)
    {
        if (h->tile->getLetter() == letter)
        {
            toRet = new Tile(h->tile->getLetter(), h->tile->getValue());
            return toRet;
        }
        else
        {
            h = h->next;
        }
    }
    return 0;
}

bool Player::isTileInHand(Letter letter)
{
    Node *h = this->hand->getHead();

    while (h != nullptr)
    {
        if (h->tile->getLetter() == letter)
        {
            return true;
        }
        else
        {
            h = h->next;
        }
    }
    return false;
}

void Player::removeTileInHand(Letter letter)
{

    Node *h = this->hand->getHead();
    int count = 0;
    while (h != nullptr)
    {
        if (h->tile->getLetter() == letter)
        {
            hand->removeNode(count);
            return;
        }
        else
        {
            count += 1;
            h = h->next;
        }
    }
    return;
}

bool Player::canDrawTile(TileBag *tb)
{
    if (tb->getSize() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::drawTile(TileBag *tb)
{
    hand->addBack(tb->getFront());
    tb->removeFront();
}