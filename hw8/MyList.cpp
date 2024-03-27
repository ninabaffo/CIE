// Name: Nina Baffo
// Date: 12/02/22
// FileName: MyList.cpp
// Description: Here is where all the methods crated in the MyList.h file are told what to do.

#include "MyList.h"
#include "Node.h"
#include <iostream>
using namespace std;

// Description: default constructor that that initializes the list to an empty list.
// Input: None
// Output: None
MyList::MyList() {
    currentPtr = nullptr;
}

// Description: The destructor deletes all the nodes in the list and prints the values of each node that is deleted.
// Input: None
// Output: None
MyList::~MyList() {
    clear();
}

// Description: This method should print the integers stored in the list in ascending order.
// Input: None
// Output: the list is printed
void MyList::printAscending() {
    if (currentPtr == nullptr) {
        cout << "The list is empty." << endl;
        return;
        }
    else {
        while (currentPtr->getLeft() != nullptr) {
            currentPtr = currentPtr->getLeft();
        }
        while (currentPtr != nullptr) {
            cout << currentPtr->getValue() << " ";
            currentPtr = currentPtr->getRight();
        }
    }
    cout << endl;
}

// Description: This method should print the integers stored in the list in descending order.
// Input: None
// Output: list in descending order
void MyList::printDescending() {
    if (currentPtr == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }
    else {
        while (currentPtr->getRight() != nullptr) {
            currentPtr = currentPtr->getRight();
        }
        while (currentPtr != nullptr) {
            cout << currentPtr->getValue() << " ";
            currentPtr = currentPtr->getLeft();
        }
    }
}

// Description: If the value that is being inserted in the list is less than the current Node, the value will be placed
//              to the left of the current node. If it is more than the current, it will be placed to the right of the current node.
// Input: int valToInsert
// Output: None
void MyList::insert(int valToInsert) {
    Node *newPtr = new Node;
    newPtr->setValue(valToInsert);

    if (currentPtr == nullptr) {
        currentPtr = newPtr;
    }

    if (valToInsert > currentPtr->getValue()) {
        while (currentPtr->getRight() != nullptr && currentPtr->getValue() < currentPtr->getRight()->getValue()) {
                currentPtr = currentPtr->getRight();
            }
            currentPtr->setRight(newPtr);
            newPtr->setLeft(currentPtr);
        }
    else {
        while (currentPtr->getLeft() != nullptr && currentPtr->getValue() > currentPtr->getLeft()->getValue()) {
                currentPtr = currentPtr->getLeft();
            }
            currentPtr->setLeft(newPtr);
            newPtr->setRight(currentPtr);
        }
}

// Description: This method removes a single node from the list that matches the input value if it exists.
// Input: int valToDelete
// Output: None
void MyList::remove(int valToDelete) {
    if (currentPtr == nullptr){
        cout << "The list is empty, there is nothing to delete." << endl;
    }
    else {
        if (currentPtr->getValue() == valToDelete) {
            delete currentPtr;
            cout << "The Node was deleted." << endl;
        }
        else {
            while (currentPtr->getLeft() != nullptr) {
                currentPtr = currentPtr->getLeft();
            }
            if (valToDelete == currentPtr->getValue()){
                delete currentPtr;
                cout << "The Node was deleted" << endl;
            }
            else {
                cout << valToDelete << " Was not found in the list." << endl;
            }
        }
    }
}

// Description: this method should remove all elements from the list and print the value of each node that is deleted.
// Input: None
// Output: None
void MyList::clear() {
    while (currentPtr->getLeft() != nullptr) {
        currentPtr = currentPtr->getLeft();
    }
    while (currentPtr->getRight() != nullptr) {
        cout << currentPtr->getValue() << " ";
        currentPtr = currentPtr->getRight();
        delete currentPtr->getLeft();
    }
    if (currentPtr->getRight() == nullptr) {
        cout << currentPtr->getValue() << " ";
        delete currentPtr;
    }
}
