#ifndef NODE_H
#define NODE_H

template <class T>
class Node{

    public:
        Node(T value);
        T getValue();
        void setNext(Node* next);
        Node<T>* getNext();

    private:
        T currNode;
        Node* nextNode;

};

#endif