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

    // Iterate through the list and print each node.
    void print() {
        Node* printp = this->head;
        while(printp != nullptr) {
            printp->print();
            printp = printp->getNext();
        }
    }

    // Delete all elements in the list.
    void clear() {
        Node* next;

        if(this->size == 0) return;
        do {
            next = this->head->getNext();
            delete(this->head);
            this->setHead(next);
        } while(next != nullptr);
    }
};

/*
 *  Implementation of Stack for char nodes.
 *
 *  Must create an empty Stack and then add
 *  any nodes to it.
 */
class Stack {
private:
    Node* top;
    size_t depth;

public:
    // Constructor
    Stack(): top(nullptr), depth(0) {}

    // Getters
    Node* getTop() const { return this->top; }
    size_t getDepth() const { return this->depth; }

    // Setters
    void setTop(Node* newTop) { this->top = newTop; }
    void setDepth(Node* newDepth) { this->top = newDepth; }

    // Push a new node to the top of the stack
    void push(Node* x) {
        if(isEmpty()) top = x; // Empty stack handling
        else {
            // Set input as new top
            x->setNext(top);
            top->setPrev(x);
            this->setTop(x);
        }
        depth++;
        return;
    }

    /*
     *  Delete the top of the stack and return a copy.
     *  If there is no top, return a nullptr.
     */
    Node* pop() {
        if(isEmpty()) return nullptr; // Stack is empty

        Node* popped = this->getTop();
        this->setTop(this->getTop()->getNext());
        // Set the new top's previous
        if(this->getTop() != nullptr) this->getTop()->setPrev(nullptr);
        this->depth--;
        return popped;
    }

    // Functionally the same as getTop
    Node* peek() const { return this->getTop(); }

    bool isEmpty() {
        return this->depth == 0;
    }

    // Not sure why this is in the documentation,
    // a stack with a linked list is inherently dynamically
    // allocated, and therefore won't be full until
    // there is no room in memory.
    // bool isFull() {

    // }

    void print() {
        Node* cur = this->getTop();
        while(cur != nullptr) {
            cur->print();
            cur = cur->getNext();
        }
        return;
    }

    // Clear the stack of all nodes.
    void clear() {
        while(isEmpty() == false) {
            // pop until empty
            this->pop();
        }
        return;
    }
};

// class Queue {

// };

// class StackParenthesesChecker {

// };

// class QueueParenthesesChecker {

// };

int main() {
    // Array of Nodes for unit testing
    Node* nodeArray[] {     new Node('1'), new Node('2'), new Node('3'),
                            new Node('4'), new Node('5'), new Node('6'), };

    // The unit tests below no doubt are not
    // "proper" for true unit testing. I have
    // no doubt asserts would be preferable,
    // but given the scope of this assignment
    // I kind of can't be bothered. Oh, well!

    // List testing
    // LinkedList myList = LinkedList();
    // for(int i = 0; i < (sizeof(nodeArray) / sizeof(nodeArray[0])); i++) {
    //     myList.add(i, nodeArray[i]);
    // }
    // myList.print();
    // myList.remove(3);
    // myList.print();

    // Stack testing
    // Stack myStack = Stack();
    // for(int i = 0; i < (sizeof(nodeArray) / sizeof(nodeArray[0])); i++) {
    //     myStack.push(nodeArray[i]);
    // }
    // myStack.print();
    // myStack.clear();
    // myStack.print();

    return 0;
}