#include "LinkedList.h"

//Constructor
template <typename T>
LinkedList<T>::LinkedList(){
  head = nullptr;
  length = 0;
}

//Deconstructor
template <typename T>
LinkedList<T>::~LinkedList(){
  Node<T>* temp = head;

  while(temp->getNext() != nullptr){
    Node<T>* current = temp->getNext();
    delete temp;
    temp = current;
  }

}

//Get a Node
template <typename T>
Node<T>* LinkedList<T>::getNode(int index){
  if(length == 0 || index > length || index < 1){
    return(nullptr);
  }

  Node<T>* current = head;

    for(int i = 1; i < index; i++){
      current = current->getNext();
    }

  return(current);
}

//Retrieve length of Node
template <typename T>
int LinkedList<T>::getLength(){
  return(length);
}

//Add to Head
template <typename T>
void LinkedList<T>::addHead(T value){
	Node<T>* temp = new Node<T>(value);
		
		if(isEmpty()){
			head = temp;
		}
		
		else {
			temp->setNext(head);
			head = temp;
		}
	length++;
}

//Add to Tail
template <typename T>
void LinkedList<T>::addTail(T value){
  if(isEmpty()){
    return;
  }

  else {
    Node<T>* temp = new Node<T>(value);
    Node<T>* nHead = head;

    while(nHead->getNext() != nullptr){
      nHead = nHead->getNext();
    }
      nHead->setNext(temp);
  }

  length++;
}

//Remove from front of queue
template <typename T>
bool LinkedList<T>::removeFront()
{
  if(isEmpty()){
    return(false);
  }
  
  else if(length == 1){
    delete head;
    head = nullptr;
    length = 0;
  }
  
  else{
    Node<T>* temp = head;
    temp = temp->getNext();
    delete head;
    head = temp;
    length--;
  }
  
  return(true);
}

//Check if there are any nodes in the list
template <typename T>
bool LinkedList<T>::isEmpty(){
  return(length == 0);
}