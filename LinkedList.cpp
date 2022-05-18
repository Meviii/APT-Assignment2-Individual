
#include "LinkedList.h"

#include <iostream>

LinkedList::LinkedList()
{
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::~LinkedList()
{
   while (head != nullptr)
   {
      Node *cur = head->next;
      delete head;
      head = cur;
   }
   size = 0;
}

int LinkedList::getSize()
{
   return size;
}

Node *LinkedList::getHead()
{
   return head;
}

void LinkedList::addBack(Tile *node)
{
   Node *newNode = new Node(node, nullptr);

   // If list is empty, head is assigned to the given node
   if (head == nullptr)
   {
      head = newNode;
   }
   // Else node is assigned to end of linked list by iterating through next pointers until nullptr is found
   else
   {
      Node *tmp = head;

      while (tmp->next != nullptr)
      {
         tmp = tmp->next;
      }
      tmp->next = newNode;
   }
   size++;
}

void LinkedList::addFront(Tile *node)
{

   // Create new node already pointing to current head node as next
   Node *newNode = new Node(node, head);

   if (head == nullptr)
   {
      head = newNode;
   }
   else
   {
      head = newNode;
   }
   size++;
}

void LinkedList::removeBack()
{
   this->removeNode(size);
}

Node *LinkedList::getNode(int i)
{
   int counter = 0;
   Node *node = head;
   // Iterates through nodes until at given index of node
   if (i >= 0 && i <= size)
   {
      while (counter != i && node != nullptr)
      {
         node = node->next;
         counter++;
      }
   }
   else
   {
      Node *t = nullptr;
      std::cout << "Node not in range" << std::endl;
      return t;
   }

   return node;
}

// Same functionality of getNode but takes found node's variables to create a new tile to return
Tile *LinkedList::getNodeAsTile(int i)
{
   int counter = 0;
   Node *cur = head;
   Tile *ret = nullptr;

   if (i >= 0 && i <= size)
   {
      while (counter != i && cur != nullptr)
      {
         cur = cur->next;
         counter++;
      }
   }
   else
   {
      std::cout << "Node not in range" << std::endl;
      return ret;
   }
   ret = new Tile(cur->tile->getLetter(), cur->tile->getValue());
   return ret;
}

bool LinkedList::checkEmpty()
{
   return head == nullptr;
}

void LinkedList::removeNode(int i)
{

   if (i == 0)
   {
      // Checks if list is empty
      if (head == nullptr)
      {
         return;
         // Else will assign next node as head and delete current head
      }
      else
      {
         Node *tmp = head;
         head = head->next;
         size--;
         delete tmp;
         return;
      }
      // If node is between 0 and list size (not head or tail)
   }
   else if (i > 0 && i < size)
   {
      Node *n = getNode(i - 1);
      Node *n1 = getNode(i + 1);
      n->next = n1;
      size++;
      // Else if wanted node deleted is tail
   }
   else if (i == size)
   {
      this->tail = nullptr;
   }
   else
   {
      std::cout << "not in range" << std::endl;
      return;
   }
   size--;
}

void LinkedList::printList()
{
   std::cout << "Linked List with tile size: " << size << std::endl;
   struct Node *tmp = head;
   while (tmp != NULL)
   {
      std::cout << "Letter: " << tmp->tile->getLetter() << ", Value: " << tmp->tile->getValue() << std::endl;
      tmp = tmp->next;
   }
}