#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Node.h"

template <typename T>
class LinkedList
{
    public:
        LinkedList();
        ~LinkedList();

        //Retrieve a node at the required position
        Node<T>* getNode(int index);
        //Retrieve the length of the list at point required
        int getLength();

        //Add Node to the front of the list
        void addHead(T value);
        //Add Node to the end of the list
        void addTail(T value);

        //Remove Node from the front of the list
        bool removeFront();
        
        //Check whether there are any nodes within the list
        bool isEmpty();


    private:
        Node<T>* head;
        int length;
};
#endif