#ifndef NODE_H
#define NODE_H

template <class T>
class Node{

    public:
        
        T currNode;
        Node* nextNode;

        Node(T value){
        currNode = value;
        nextNode = nullptr;
        }

        
        T getValue(){
         return(currNode);
        }

        void setNode(T next){
            currNode = next;
        }

        
        void setNext(Node* next){
            nextNode = next;
        }

        
        Node<T>* getNext(){
            return(nextNode);
        }

    
       

};

#endif