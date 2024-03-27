// Name: Nina Baffo
// Date: 12/02/22
// FileName: hw8
// Description: Implement a doubly linked list class of integers.
//              Write two new classes, Node and MyList. implemented in their own files, i.e.,
//              Node.cpp, Node.h, MyList.cpp and MyList.h.
#include <iostream>
#include "Node.h"
#include "MyList.h"

using namespace std;

int main() {
    // testing explicit constructor for Node class
    Node testNode1(5);
    cout << "Node: Should print: 0x0, 5, 0x0. Actually prints: " <<
    testNode1.getLeft() << ", " <<  testNode1.getValue() << ", " << testNode1.getRight() << endl;

    Node testNode2(3);
    int val = 6;
    // testing methods setValue and getValue from the Node class
    testNode2.setValue(val);
    cout << "setValue: Should print: " << val << ", Actually prints: " << testNode2.getValue() << endl;

    // testing methods setRight and getRight from the Node class
    Node * nextNode;
    testNode2.setRight(nextNode);
    cout << "setRight: Should print: " << nextNode << ", Actually prints: " << testNode2.getRight() << endl;

    // testing methods setLeft and getLeft from the Node class
    Node * previousNode;
    testNode2.setLeft(previousNode);
    cout << "setLeft: Should print: " << previousNode << ", Actually prints: " << testNode2.getLeft() << endl;

    // testing print() method of the node class
    cout << "print: Should print: " << testNode2.getValue() << ", Actually prints: ";
    testNode2.print();
    cout << endl;

    // testing that printAscending() works
    MyList myList1; // creating an empty list & calling default constructor
    cout << "printAscending() empty list: Should print 'The list is empty.' Actually prints: ";
    myList1.printAscending();
    myList1.insert(5);
    myList1.insert(10);
    myList1.insert(3);
    myList1.insert(13);
    myList1.insert(15);
    cout << "printAscending(): Should print '3 5 10 13 15'. Actually prints: ";
    myList1.printAscending();
    cout << endl;

    // testing that printDescending() works
    MyList myList2;
    cout << "printDescending() empty list: Should print 'The list is empty.' Actually prints: ";
    myList2.printDescending();
    myList2.insert(5);
    myList2.insert(10);
    myList2.insert(3);
    myList2.insert(13);
    myList2.insert(15);
    cout << "printDescending(): Should print '15 13 10 5 3'. Actually prints: ";
    myList2.printDescending();
    cout << '\n' << endl;

    // testing to make sure remove(valToDelete) method works
    MyList myList3;
    myList3.insert(10);
    myList3.insert(5);
    myList3.insert(15);
    myList3.insert(3);
    cout << "remove: Should print 'The Node was deleted.' Actually prints: ";
    myList3.remove(3);
    cout << "remove: Should print '6 Was not found in the list.' Actually prints: ";
    myList3.remove(6);
    cout << endl;

    // testing if clear() method works (tested twice with myList4 and myList 5)
    MyList myList4;
    myList4.insert(5);
    myList4.insert(10);
    myList4.insert(3);
    myList4.insert(13);
    myList4.insert(15);
    cout << "clear(): Should print '3 5 10 13 15'. Actually prints: ";
    myList4.clear();
    cout << endl;

    MyList myList5;
    myList5.insert(20);
    myList5.insert(75);
    myList5.insert(13);
    myList5.insert(90);
    myList5.insert(10);
    cout << "clear(): Should print '10 13 20 75 90'. Actually prints: ";
    myList5.clear();
    cout << '\n' << endl;

    MyList myList6;
    myList6.insert(25);
    myList6.insert(80);
    myList6.insert(10);
    myList6.insert(15);
    myList6.insert(33);
    cout << "Destructor: Should print '10 15 25 33 80'. Actually prints: ";
    myList6.~MyList();

    return 0;
}
