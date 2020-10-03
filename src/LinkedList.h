#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<class T>

struct Node {
    //Current Node
    T data;

    //Next Node
    Node<T> *next;
};

template<class T>
class LinkedList {

private:
    //Head of List
    Node<T> *head;

    //Length of List
    int length;

public:
    
    /*
    * Default Constructor
    */
    LinkedList() {
        head = nullptr;
        length = 0;
    }

    /*
    * Deconstructor
    */
    ~LinkedList() {
        Node<T> *temp = head;
        while (temp->next != nullptr) {
            Node<T> *current = temp->next;
            delete temp;
            temp = current;
        }
    }

    /*
    * Add Node to the Tail end of the List
    */
    void addBack(T data) {
        auto *node = new Node<T>;
        node->data = data;
        node->next = nullptr;
        
        if (!head) {
            head = node;
        } 
        else {
            auto *tail = head;
            while (tail->next) tail = tail->next;
            tail->next = node;
        }
        length++;
    }

    /*
    * Add Node to the Head of the List
    */
    void addFront(T data) {
        auto *newNode = new Node<T>();
        newNode->data = data;
        newNode->next = head;
       
        head = newNode;
        length++;
    }

    /**
    * Checks whether the list is empty
    * @return 0 if true
    */
    bool isEmpty() {
        return length == 0;
    }

    /*
    * Fetch node at required position
    */
    T get(int index) {
        T result;

        if (index == 0) {
            result = head->data;
        } 

        else {
            auto *curr = head;
            for (int i = 0; i < index; ++i) {
                curr = curr->next;
            }

            result = curr->data;
        }
        return result;
    }

    /*
    * Remove Node from the Head of the List
    */
    void popFront() {
        if (head) {

            if (head->next) {
                Node<T> *temp = head->next;
                delete head;
                head = temp;
            } 

            else {
                delete head;
                head = nullptr;
            }

            length--;
        } 
        
        else {
            throw std::runtime_error("Called popFront() when the list is empty");
        }

    }

    /*
    * Remove Node currently in question
    */
    void deleteNode(Node<T> *node) {
        if (head == node) {
            if (head->next == nullptr) {
                head == nullptr;
            } else {
                head->data = head->next->data;
                node = head->next;

                head->next = head->next->next;

                delete node;
            }

            length--;

        } 
        else {
            Node<T> *prev = head;
            while (prev->next != nullptr && prev->next != node) {
                prev = prev->next;
            }

            if (prev->next == nullptr) {
                std::cout << "This value does not exist in the list" << std::endl;
            }

            prev->next = prev->next->next;

            delete node;
            length--;
        }
    }


    /**
    * Return length of the current list
    * @return : int length
    */
    int getLength() {
        return length;
    }
};
#endif