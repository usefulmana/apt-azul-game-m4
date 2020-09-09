#include "Node.h"

template <class T>
Node<T>::Node(T value){
  currNode = value;
  nextNode = nullptr;
}

template <class T>
T Node<T>::getValue(){
  return(currNode);
}

template <class T>
void Node<T>::setNext(Node* next){
  nextNode = next;
}

template <class T>
Node<T>* Node<T>::getNext(){
  return(nextNode);
}