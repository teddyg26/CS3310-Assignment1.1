#include <iostream>
#include <string>

/*
 *  Class for nodes in a linked list that contain singular chars
 *  and pointers to other nodes.
 */
class Node {
private:
    char data;
    Node* prev;
    Node* next;

public:
    // Constructor
    Node(char nodeData): data(nodeData), prev(nullptr), next(nullptr) {}

    // Getters
    char getData() const { return this->data; }
    Node* getPrev() const { return this->prev; }
    Node* getNext() const { return this->next; }

    // Setters
    void setData(char newChar) { this->data = newChar; }
    void setPrev(Node* newPrev) { this->prev = newPrev; }
    void setNext(Node* newNext) { this->next = newNext; }



    // Debugging print function (prints node data neatly)
    void print() const {
        std::cout << "Node(" << this->data << ")";
        if (prev) std::cout << " prev: " << this->prev->data;
        if (next) std::cout << " next: " << this->next->data;
        std::cout << std::endl;
    }
};

/*
 *  Implementation of LinkedList for char nodes.
 *
 *  Must create an empty LinkedList and then
 *  add any nodes to it.
 */
class LinkedList {
private:
    Node* head;
    Node* tail;
    // int capacity;
    size_t size;

public:
    // Constructor
    LinkedList(): head(nullptr), tail(nullptr), size(0) {}

    // Getters
    Node* getHead() const { return this->head; }
    Node* getTail() const { return this->tail; }
    size_t getSize() const { return this->size; }

    // Setters
    void setHead(Node* newHead) { this->head = newHead; }
    void setTail(Node* newTail) { this->tail = newTail; }
    void setSize(size_t newSize) { this->size = newSize; }

    // Get node at index i
    Node* gotoNode(size_t i) const {
        if(this->size < i) throw std::out_of_range("Index out of range for gotoNode");

        // Start from the closest end and work forwards/back
        if(i < this->size / 2) {
            Node* cur = this->head;
            for(size_t j = 0; j < i; j++) cur = cur->getNext();
            return cur;
        } else {
            Node* cur = this->tail;
            for(size_t j = this->size - 1; j > i; j--) cur = cur->getPrev();
            return cur;
        }
    }

    // Append to the end of the linked list
    void append(Node* node) {
        Node* toAdd = node;
        if(this->size == 0) head = tail = toAdd;
        else {
            this->tail->setNext(toAdd);
            toAdd->setPrev(this->tail);
            this->setTail(toAdd);
        }
        this->size++;
    }

    // Push to the front of the linked list
    void push(Node* node) {
        Node* toAdd = node;
        if(this->size == 0) head = tail = toAdd;
        else {
            this->head->setPrev(toAdd);
            toAdd->setNext(this->head);
            this->setHead(toAdd);
        }
        this->size++;
    }

    // Add node x at index i
    void add(size_t i, Node* x) {
        if(i > this->size) std::out_of_range("Index out of range for add");

        // Front of list
        if(i == 0) {
            this->push(x);
            return;
        }

        // End of list
        if(i == this->size) {
            this->append(x);
            return;
        }

        // Get the node currently at the index
        Node* after = gotoNode(i);
        Node* before = after->getPrev();

        // The ol' switcheroo
        before->setNext(x);
        x->setPrev(before);
        x->setNext(after);
        after->setPrev(x);
        this->size++;
        return;
    }

    // Remove item at index i and return it.
    // Returns a nullptr if there is no item.
    Node* remove(size_t i) {
        if(i >= this->size) throw std::out_of_range("Index out of range for remove.");
        
        Node* toRemove = gotoNode(i);
        if(toRemove == nullptr) return nullptr; // No item, return nullptr

        char val = toRemove->getData();
        Node* toRemovePrev = toRemove->getPrev();
        Node* toRemoveNext = toRemove->getNext();

        // Swap pointers as needed for deletion. Set head if needed
        if(toRemovePrev) toRemovePrev->setNext(toRemoveNext);
        else this->setHead(toRemoveNext);

        // Same but set tail if needed
        if(toRemoveNext) toRemoveNext->setPrev(toRemovePrev);
        else this->setTail(toRemovePrev);

        delete(toRemove);
        this->size--;
        return new Node(val);
    }

    /*
     *  Iterate through the list and print each node.
     */
    void print() {
        Node* printp = this->head;
        while(printp != nullptr) {
            printp->print();
            printp = printp->getNext();
        }
    }
};

// class Stack {

// };

// class Queue {

// };

// class StackParenthesesChecker {

// };

// class QueueParenthesesChecker {

// };

int main() {
    Node* first = new Node('a');
    Node* second = new Node('b');
    Node* third = new Node('c');

    LinkedList myList = LinkedList();
    myList.add(0, first);
    myList.add(1, second);
    myList.add(2, third);
    myList.print();
    myList.remove(1);
    myList.print();

    return 0;
}