#include<iostream>

class LinkedList {

	//the Node for the list
    struct Node {
		char currNode;
		Node *nextNode;
	};

	// Constructor
	LinkedList() {
		head = NULL;
		tail = NULL;
	}

	// Deconstructor
	~LinkedList() {
		Node *nextNode = head;

		while (nextNode) {
			Node *deleteMe = nextNode;
			nextNode = nextNode->nextNode;
			delete deleteMe; //please
		}
	}

	// Adds the element to the front of the list
	bool addHeadNode(char currNode) {
		Node *newNode = new Node();
		newNode->currNode = currNode;
		newNode->nextNode = NULL;

		if (tail == NULL) {
			tail = newNode;
		}

		newNode->nextNode = head;
		head = newNode;

		return true;
	}

    //Adds the element to the end of the list
	bool addNode(char currNode) {
		if (tail == NULL) {
			addHeadNode(currNode);
		}

		Node * newNode = new Node();
		newNode->currNode = currNode;
		newNode->nextNode = NULL;

		tail->nextNode = newNode;
		tail = tail->nextNode;

		return true;
	}

    //Removes element
    void remove(char key) {
		char item = NULL;
		Node * temp = head;

		while (temp) {
			if (temp->currNode == key) {
				item = temp->currNode;
				temp = temp->nextNode;
			}
			temp = temp->nextNode;
		}
	}

	//Returns the value of the first item and deletes it
	int removeHead() {
        
        // If the list is empty
		if (head == NULL){
			return 0;
        }

		Node *newNode = head;
		int item = newNode->currNode;

		head = head->nextNode;
		delete newNode;
		return item;
	}

    //Checks whether value is in the list
	bool contains(char key) {
		Node * temp = head;

		while (temp->nextNode) {
			if (temp->nextNode->currNode == key) {
				return true;
			}
			temp = temp->nextNode;
		}
		return tail->currNode == key;
	}

    private:
        Node * head;
        Node * tail;

};
