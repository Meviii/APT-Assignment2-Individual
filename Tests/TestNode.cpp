#include "../Tile.h"
#include "../Node.h"

#include <iostream>
#include <string>




 
class TestNode {

    

    
    public:

    TestNode* next;
    Tile* tile;

    
    
    TestNode(Tile* tile, TestNode* next)
    {
    this->tile = tile;
    this->next = next;
    }

    TestNode(TestNode& other)
    {
    this->tile = other.tile;
    }


};

int main(void){

    Tile* tl1 = new Tile('A',1);

    std::cout << "Assigning node with Tile (A1)" << std::endl;
    TestNode* tl1_node = new TestNode(tl1, nullptr);

    std::cout << "Test Node 1: " << tl1_node->tile->getLetter() << tl1_node->tile->getValue() << std::endl;

    std::cout << "Creating new node with original node as parameter" << std::endl;

    TestNode* nd1_node = new TestNode(*tl1_node);

    std::cout << "Test Node 2: " << nd1_node->tile->getLetter() << nd1_node->tile->getValue() << std::endl;




    
}
