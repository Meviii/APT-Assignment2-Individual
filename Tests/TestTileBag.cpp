#include "../LinkedList.h"
#include "../Tile.h"
#include "../TileBag.h"

#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <time.h>

void testSetAsList(LinkedList* tile_list);
LinkedList* testGetList();
int testGetSize();
Tile* testGetTile(int i);
Tile* testGetFront();
void testAddBack(Tile* tile);
void testRemove(int i);
void testRemoveFront();
void testRemoveBack();
void testShuffle();
void testReadFile();

class TestTileBag {

    private:
    LinkedList* tile_list;

    
    public:


    TestTileBag(){
    this->tile_list = nullptr;
    }

    TestTileBag(LinkedList* tile_list){
        this->tile_list = tile_list;
        this->testReadFile();
        testShuffle();
    }

    ~TestTileBag(){
        tile_list->~LinkedList();
    }

    void testSetAsList(LinkedList* tile_list){
        this->tile_list = tile_list;
    }

    LinkedList* testGetList(){
        return tile_list;
    }

    int testGetSize(){
        return tile_list->getSize();
    }

    Tile* testGetTile(int i){
        return tile_list->getNodeAsTile(i);
    }

    Tile* testGetFront(){
        return tile_list->getNodeAsTile(0);
    }

    void testAddBack(Tile* tile){
        tile_list->addBack(tile);
    }

    void testRemove(int i){
        tile_list->removeNode(i);
    }

    void testRemoveFront(){
        tile_list->removeNode(0);
    }

    void testRemoveBack(){
        tile_list->removeBack();
    }

    void testShuffle(){
        
        LinkedList* tmpList = new LinkedList();        
        Tile* curr_tile;

        int size = (tile_list->getSize());
        srand(time(0));


        for (int j = 0; j <= size; j++){
            int i = rand() % size;

            // takes a random tile from total tilelist at int i and adds to temporary list
            curr_tile = new Tile(this->tile_list->getNodeAsTile(i)->getLetter(), this->tile_list->getNodeAsTile(i)->getValue());
            tmpList->addBack(curr_tile);

            
            
        } 
        this->tile_list = tmpList;

    }

    void testReadFile(){
        std::ifstream file;
        std::string line;
        std::istringstream iss_line(line);
        std::string letter;
        std::string value;
        file.open("Tests/TestScrabbleTiles.txt");
        if (!file.is_open()){
            std::cout << "Can't read file" << std::endl;
        }else{
            while (std::getline(file, line)) {
                letter = line.substr(0,1);
                value = line.substr(1,-1);
                int num = std::stoi(value);
                char c = letter[0];
                Tile* tmp = new Tile((Letter) c,(Value) num);
                this->testAddBack(tmp);
                tmp = nullptr;
            }
        }
    }


};

int main(void){

    LinkedList* list = new LinkedList();
    TestTileBag* tileBag = new TestTileBag(list);

    tileBag->testGetList()->printList();

    std::cout << "Size of list is: " << tileBag->testGetSize() << std::endl;

    std::cout << "Tile at back is " << tileBag->testGetTile(tileBag->testGetSize() - 1)->letter << tileBag->testGetTile(tileBag->testGetSize() -1)->value << std::endl;


    std::cout << "Removing 5 tiles from tilebag back" << std::endl;


    for (int i = 0; i < 5; i++){
        tileBag->testRemoveBack();
    }

    std::cout << "Tile at back is " << tileBag->testGetTile(tileBag->testGetSize() - 1)->letter << tileBag->testGetTile(tileBag->testGetSize() -1)->value << std::endl;


    std::cout << "Size of list is: " << tileBag->testGetSize() << std::endl;

    std::cout << "Tile at front is " << tileBag->testGetFront()->letter << tileBag->testGetFront()->value << std::endl;

    
    std::cout << "Removing 5 tiles from tilebag front" << std::endl;


    for (int i = 0; i < 5; i++){
        tileBag->testRemoveFront();
    }

    std::cout << "Size of list is: " << tileBag->testGetSize() << std::endl;

    std::cout << "Tile at front is " << tileBag->testGetFront()->letter << tileBag->testGetFront()->value << std::endl;



    
    
}

