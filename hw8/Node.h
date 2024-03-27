// Name: Nina Baffo
// Date: 12/02/22
// FileName: Node.h
// Description: Here is where the methods implemented in the Node class are created.

#ifndef HW8_NODE_H
#define HW8_NODE_H

class Node {
public:
    explicit Node(int val);
    Node();

    int getValue() const;
    void setValue(int _value);

    Node *getRight() const;
    void setRight(Node * nextPtr);

    Node *getLeft() const;
    void setLeft(Node * prevPtr);

    void print();

private:
    int value;
    Node * right;
    Node * left;
};

#endif //HW8_NODE_H

