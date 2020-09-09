#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Node.h"

template <typename T>
class LinkedList
{
    public:
        LinkedList(){
            
            tail = nullptr;
            length = 0;
        }

        ~LinkedList(){
            Node<T>* temp = head;
            

            while(temp->getNext() != nullptr){
                Node<T>* current = temp->getNext();
                delete temp;
                temp = current;
            }
        }

        //Retrieve a node at the required position
        Node<T>* getNode(int index){
            if(length == 0 || index > length || index < 0){
                 return(nullptr);
            }

            Node<T>* current = head;
            for(int i = 1; i < index; i++){
                current = current->getNext();
            }

            return current;
        }


        //Retrieve the length of the list at point required
        int getLength(){
            return(length);
        }

        //Add to Head
        void addHead(T value){

            Node<T>* newNode = new Node<T>(value);
            newNode->currNode = value;
            newNode->nextNode = head;
            head = newNode;
            //return value;
            
            //Node<T>* temp = new Node<T>(value);
            
            
           /*if (head == NULL){
                head = new Node<T>(value);
            }
             
            else
            {
                Node<T>* temp = new Node<T>(value);
                temp->setNode(value); 
                head->setNext(temp);
                head = temp;
            }*/


                /*if(isEmpty())
                {
                    head = temp;
                }
                
                else {
                    temp->setNext(head);
                    head = temp;
                }

            length++;*/
        }

        //Add to Tail
      
        void addTail(T value){

                Node<T>* newNode = new Node<T>(value);
                newNode->setNode(value);
                newNode->setNext(NULL);

                Node<T>* cur = head;
                while(cur) {
                    if(cur->getNext() == NULL) {
                        cur->setNext(newNode);
                        return;
                    }
                    cur = cur->getNext();
	}


            /*if (head == NULL){
                head = new Node<T>(value);
            }
             
            else
            {
                Node<T>* temp = new Node<T>(value);
                temp->setNode(value); 
                head->setNext(temp);
                head = temp;
            }
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

            length++;*/
        }

        //Remove from front of queue
        
        bool removeFront()
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
     
        bool isEmpty(){
        return(length == 0);
}

    private:
        Node<T>* head;
        Node<T>* tail;
        int length;
};
#endif