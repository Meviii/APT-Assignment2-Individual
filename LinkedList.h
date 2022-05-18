
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

using std::cout;
using std::endl;

class LinkedList
{
public:
   LinkedList();
   ~LinkedList();

   void addBack(Tile *node);
   void addFront(Tile *node);
   Node *getHead();
   int getSize();
   Node *getNode(int i);
   bool checkEmpty();
   void removeNode(int i);
   void removeBack();
   void printList();
   Tile *getNodeAsTile(int i);

private:
   Node *head;
   Node *tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
