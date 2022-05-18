
#include "../Tile.h"
#include "../Node.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

 

int testGetSize();
Node* testGetHead();
void testAddBack(Tile* node);
void testAddFront(Tile* node);
void testRemoveBack();
Node* testGetNode();
bool testCheckEmpty();
void testRemoveNode(int i);
Tile* testGetNodeAsTile(int i);
void testPrintList();


class TestLinkedList{
    

        

    private:
        int size;
        Node* head;
        Node* tail;

    public:


    TestLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
   


    ~TestLinkedList() {
        while (head != nullptr){
            Node* cur = head->next;
            delete head;
            head = cur;
        }
        size = 0;
        }

    int testGetSize(){
        return size;
    }

    Node* testGetHead(){
        return head;
    }

    void testAddBack(Tile* node){
        Node* newNode = new Node(node, nullptr);

        if (head == nullptr){
            head = newNode;
        }else{
            Node* tmp = head;

            while(tmp->next != nullptr){
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }
        size++;
        }

    void testAddFront(Tile* node){
        Node* newNode = new Node(node, head);

        if (head == nullptr){
            head = newNode;
        }else{
            
            head = newNode;
        }
        size++;
    }

    void testRemoveBack(){
        this->testRemoveNode(size);
    }

    Node* testGetNode(int i){
        int counter = 0;
        Node* node = head;
        if (i >= 0 && i <= size){
            while (counter != i && node != nullptr){
                node = node->next;
                counter++;
            }
        }else{
            Node* t = nullptr;
            std::cout << "Node not in range" << std::endl;
            return t;
        }

        return node;
    }

    Tile* testGetNodeAsTile(int i){
        int counter = 0;
        Node* cur = head;
        Tile* ret = nullptr;

        if (i >= 0 && i <= size){
            while (counter != i && cur != nullptr){
                cur = cur->next;
                counter++;
            }
        }else{
            std::cout << "Node not in range" << std::endl;
            return ret;
        }
        ret = new Tile(cur->tile->getLetter(), cur->tile->getValue());
        return ret;
    }


    bool testCheckEmpty(){
        return head == nullptr;
    }

    void testRemoveNode(int i){

        if (i == 0){
            if (head == nullptr){
                return;
            }else{
                Node* tmp = head;
                head = head->next;
                size--;
                delete tmp;
                return;
            }
        }else if (i > 0 && i < size){
            Node* n = testGetNode(i-1);
            Node* n1 = testGetNode(i+1);
            n->next = n1;
            size++;
        }else if (i == size){
            this->tail = nullptr;
        }else{
            std::cout << "not in range" << std::endl;
            return;
        }
        size--;
    }

    void testPrintList(){
        std::cout << "Linked List with tile size: " << size << std::endl;
        struct Node* tmp = head;
        while (tmp != NULL){
            std::cout << "Letter: " << tmp->tile->getLetter() << ", Value: " << tmp->tile->getValue() << std::endl;
            tmp = tmp->next;
        }
    }

    void testReadFile(){
        std::ifstream file;
        std::string line;
        std::istringstream iss_line(line);
        std::string letter;
        std::string value;
        file.open("Tests/LinkedListTestInput.txt");
        if (!file.is_open()){
            std::cout << "Can't open file" << std::endl;
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
    TestLinkedList* testList = new TestLinkedList();
    testList->testReadFile();

    std::cout << "Printing test list: " << std::endl;

    testList->testPrintList();
    std::cout << std::endl;

    std::cout << "Test linked list size is: " << testList->testGetSize() << std::endl;

    std::cout << "Testing if linked list is empty, answer should be 0: " << testList->testCheckEmpty() << std::endl;

    std::cout << "Head node is: " << testList->testGetHead()->tile->letter << testList->testGetHead()->tile->value << std::endl;

    Tile* tmp = new Tile('F',4);

    std::cout << "Adding new F 4 node to front" << std::endl;
    testList->testAddFront(tmp);

    std::cout << "Head node is: " << testList->testGetHead()->tile->letter << testList->testGetHead()->tile->value << std::endl;


    std::cout << "Getting node at int 5" << std::endl;
     std::cout << "Node is: " << testList->testGetNode(5)->tile->letter << testList->testGetNode(5)->tile->value << std::endl;


    std::cout << "Removing node at int 5" << std::endl;
    testList->testRemoveNode(5);

    std::cout << "Getting node at int 5" << std::endl;
    std::cout << "Node is: " << testList->testGetNode(5)->tile->letter << testList->testGetNode(5)->tile->value << std::endl;




    
    

}
