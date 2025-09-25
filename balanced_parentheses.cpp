#include <iostream>
#include <string>

/*
 *  Class for nodes in a linked list that contain singular chars.
 */
class Node {
private:
    char data;
    Node* prev;
    Node* next;

public:
    // Constructors
    Node(char nodeData): data(nodeData), prev(nullptr), next(nullptr) {}
    Node(char nodeData, Node *nodePrev)
        : data(nodeData), prev(nodePrev), next(nullptr) {}
    Node(char nodeData, Node *nodePrev, Node *nodeNext)
        : data(nodeData), prev(nodePrev), next(nodeNext) {}

    // Setters
    char getData() const { return data; }
    Node* getPrev() const { return prev; }
    Node* getNext() const { return next; }

    // Getters
    void setData(char newChar) { data = newChar; }
    void setPrev(Node* newPrev) { prev = newPrev; }
    void setNext(Node* newNext) { next = newNext; }

    // Debugging print function
    void print() const {
        std::cout << "Node(" << data << ")";
        if (prev) std::cout << " prev: " << prev->data;
        if (next) std::cout << " next: " << next->data;
        std::cout << std::endl;
    }
};

// class LinkedList {

// }

// class Stack {

// }

// class Queue {

// }

// class StackParenthesesChecker {

// }

// class QueueParenthesesChecker {

// }

int main() {
    Node first = Node('a');
    first.print();
    Node second = Node('b', &first);
    second.print();
    Node third = Node('c', &second);
    third.print();
    second.setNext(&third);
    second.print();

    return 0;
}