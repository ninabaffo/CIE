// Name: Nina Baffo
// Date: 12/02/22
// FileName: MyList.cpp
// Description: Here is where all the methods crated in the Node.h file are told what to do.

#include "Node.h"
#include "MyList.h"
#include <iostream>
using namespace std;

// Description: explicit constructor which sets the node value to the inputted integer and sets the previous and next nodes to nullptr.
// Input: None
// Output: int value
Node::Node(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
};

// Description:
// Input:
// Output:
Node::Node() {
    value = 0;
    left = nullptr;
    right = nullptr;
}

// Description: getValue() returns the integer stored in the node
// Input: None
// Output: int value
int Node::getValue() const {return value;}

// Description: setValue(int _value) sets the value of the node to the inputted value
// Input: int _value
// Output: None
void Node::setValue(int _value) {value = _value;}

// Description: *getNext() returns the value of the next node in the list
// Input: None
// Output: Node next
Node *Node::getRight() const {return right;}

// Description: setNext(Node * ptr) sets the next node in the list to the address of *ptr
// Input: Node * ptr
// Output: None
void Node::setRight(Node * nextPtr) {right = nextPtr;}

// Description: getPrevious() returns the value of the previous node in the list
// Input: None
// Output: previous node
Node *Node::getLeft() const {return left;}

// Description: setPrevious(Node * prev) sets the previous node in the list to the address of * prev
// Input: Node * prev
// Output: None
void Node::setLeft(Node * prevPtr) {left = prevPtr;}

// Description: print() prints the value stored in the node
// Input: None
// Output: None
void Node::print() {
    cout << value << endl;
}
