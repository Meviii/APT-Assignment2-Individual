#include "TileBag.h"


// Tilebag acts as a container for a linked list with added specific functionality when used in the game such as reading the file in
// and shuffling at construction
TileBag::TileBag(){
    this->tile_list = nullptr;
}

TileBag::TileBag(LinkedList* tile_list){
    this->tile_list = tile_list;
    this->readFile();
    shuffle();
}

TileBag::~TileBag(){
    tile_list->~LinkedList();
}

void TileBag::setAsList(LinkedList* tile_list){
    this->tile_list = tile_list;
}

LinkedList* TileBag::getList(){
    return tile_list;
}

int TileBag::getSize(){
    return tile_list->getSize();
}

Tile* TileBag::getTile(int i){
    return tile_list->getNodeAsTile(i);
}

Tile* TileBag::getFront(){
    return tile_list->getNodeAsTile(0);
}

void TileBag::addBack(Tile* tile){
    tile_list->addBack(tile);
}

void TileBag::remove(int i){
    tile_list->removeNode(i);
}

void TileBag::removeFront(){
    tile_list->removeNode(0);
}

void TileBag::removeBack(){
    tile_list->removeBack();
}

void TileBag::shuffle(){

    // create new empty list
    LinkedList* tmpList = new LinkedList();
    

    // create new tile for shuffle function
    Tile* curr_tile;

    int size = (tile_list->getSize());

    // create random seed using time
    srand(time(0));

     
    for (int j = 0; j <= size; j++){
        int i = rand() % size;

        // takes a random tile from total tilelist at int i and adds to temporary list
        curr_tile = new Tile(this->tile_list->getNodeAsTile(i)->getLetter(), this->tile_list->getNodeAsTile(i)->getValue());
        tmpList->addBack(curr_tile);

        
        
    } 
    this->tile_list = tmpList;

}


// Reads in given file line by line and assigns the character and value in each line to a tile to then add to the TileBag linked list
void TileBag::readFile(){
    std::ifstream file;
    std::string line;
    std::istringstream iss_line(line);
    std::string letter;
    std::string value;
    file.open("ScrabbleTiles.txt");
    if (!file.is_open()){
        std::cout << "Error while trying to open file" << std::endl;
    }else{
        while (std::getline(file, line)) {
            letter = line.substr(0,1);
            value = line.substr(1,-1);
            int num = std::stoi(value);
            char c = letter[0];
            Tile* tmp = new Tile((Letter) c,(Value) num);
            this->addBack(tmp);
            tmp = nullptr;
        }
    }
}