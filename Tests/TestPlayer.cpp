#include "../LinkedList.h"
#include "../Tile.h"
#include "../Player.h"

#include <iostream>
#include <string>

void basic_functions(TileBag* tb);
void player_hand(TileBag* tb);

int main(void){
    LinkedList* list = new LinkedList();
    TileBag* tb = new TileBag(list);

    player_hand(tb);

    //basic_functions(tb);
}

void basic_functions(TileBag* tb){
    Player* pl = new Player();
    Tile* tl = new Tile('A', 10);

    pl->setName("name1");
    std::cout << pl->getName() << std::endl;
    pl->setScore(10000);
    std::cout << pl->getScore() << std::endl;

    std::cout << "==========================" << std::endl;

    pl->setHand(tb);
    pl->printHand();

    std::cout << "==========================" << std::endl;
    
    if (pl->isTileInHand(tl->getLetter()) == true){
        std::cout << pl->getTileInHand(tl->getLetter())->getValue() << std::endl;
        //need to remove from hand
        //need to add new tile from bag
    }

}

void player_hand(TileBag* tb){
    Player* pl1 = new Player();
    pl1->setName("test");
    Letter letter;
    pl1->setHand(tb);
    pl1->printHand();
    std::cin >> letter;
    pl1->removeTileInHand(letter);
    pl1->printHand();
}
