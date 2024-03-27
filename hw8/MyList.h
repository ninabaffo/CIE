// Name: Nina Baffo
// Date: 12/02/22
// FileName: MyList.h
// Description: Here is where the methods implemented in the MyList class are created.

#ifndef HW8_MYLIST_H
#define HW8_MYLIST_H

#include "Node.h"

class MyList : public Node{
public:
    MyList();
    ~MyList();

    void printAscending();
    void printDescending();
    void insert(int valToInsert);
    void remove(int valToDelete);
    void clear();

private:
    Node * currentPtr;
};

#endif //HW8_MYLIST_H
