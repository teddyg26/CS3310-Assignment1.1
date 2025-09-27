#include <iostream>
#include <string>
#include <cassert>

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
        return;
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
    size_t size;

public:
    // Constructor
    LinkedList(): head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() { clear(); }

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
        return;
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
        return;
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
        return;
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
        return;
    }
};


// This is about the point where the file length
// is making me hate myself
//
// Oh well! not like separating into different files
// will lend to performance gains


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
    ~Stack() { clear(); }

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
            this->getTop()->setPrev(x);
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
    Node* peek() const { return this->top; }

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

/*
 *  Implementation of Queue for char nodes
 *
 *  Following previous implementations here,
 *  this queue  will be empty and must be
 *  added to after construction.
 */
class Queue {
private:
    Node* front;
    Node* rear;
    size_t len;

public:
    // Constructor
    Queue(): front(nullptr), rear(nullptr), len(0) {}
    ~Queue() { clear(); };

    // Getters
    Node* getFront() { return this->front; }
    Node* getRear() { return this->rear; }
    size_t getLen() { return this->len; }

    // Setters
    void setFront(Node* newFront) { this->front = newFront; }
    void setRear(Node* newRear) { this->rear = newRear; }
    void setLen(size_t newLen) { this->len = newLen; }

    // Returns Boolean of whether queue is currently empty
    bool isEmpty() {
        return this->getLen() == 0;
    }

    // Adds item to rear of queue
    void enqueue(Node* x) {
		if(isEmpty()) this->front = this->rear = x;
		else {
			this->getRear()->setNext(x);
			x->setPrev(this->getRear());
			this->setRear(x);
		}
		this->len++;
        return;
    }

    // Removes item from front of queue and returns it
    // Returns a nullptr if the queue is empty
    Node* dequeue() {
        if(isEmpty()) return nullptr;

		// Store a temp node to hold the value of the front.
		// Delete the front of the queue, then set the new front
		// and return the temp node.
		Node* returnNode = this->getFront();
		this->setFront(returnNode->getNext());
		if(this->getFront()) this->getFront()->setPrev(nullptr);
		else this->setRear(nullptr); // In this else, the Queue is empty
		this->len--;
        return returnNode;
    }

    // Check the end of the queue without removing
	// Functionally the same as getRear()
    Node* poll() { return this->rear; }

    void print() {
		Node* cur = this->getFront();
		while(cur != nullptr) {
			cur->print();
			cur = cur->getNext();
		}
        return;
    }

    // Clear the queue of all nodes
    void clear() {
		while(isEmpty() == false) {
			this->dequeue();
		}
        return;
    }
};

// As with other classes, needs to have a stack
// added with the setStack method after construction
class StackParenthesesChecker {
private:
	Stack* stack;
public:
	// Constructor
	StackParenthesesChecker(): stack(nullptr) {}

	// Getter
	Stack* getStack() const {
		return this->stack;
	}

	// Setter
	void setStack(Stack* newStack) {
		this->stack = newStack;
		return;
	}

	bool isBalanced(std::string s) {
		// Since every open bracket will have a
		// matching closing bracket, the input
		// string _must_ be even in length to
		// meet the criteria of being balanced.
		if(s.length() % 2 != 0) return false;

		// Load stack with characters in string
		for(int i = 0; i < s.length(); i++) {
			Node* node = new Node(s[i]);
			this->getStack()->push(node);
		}

		// Check the string for the solution using a queue.
		// This will be done by dequeue-ing one item at a time.
		// If the item is a '(', increment the counter by one.
		// If the item is a ')', decrement the counter by one.
		// If at any time the counter is positive, the input is unbalanced.
		// This is because stacks are FILO, so ')' are counted first.
		// If the counter is non-zero at the end, the input is unbalanced.
		int count = 0;
		Node* cur;
		size_t numIterations = this->getStack()->getDepth();
		for(int i = 0; i < numIterations; i++) {
			cur = this->getStack()->pop();
			if(cur->getData() == '(') count++;
			if(cur->getData() == ')') count--;
			if(count > 0) return false;
		}

		return count == 0;
	}
};

// As with other classes, needs to have a queue
// added with the setQueue method after construction
class QueueParenthesesChecker {
private:
	Queue* queue;
public:
	// Constructor
	QueueParenthesesChecker(): queue(nullptr) {}

	// Getter
	Queue* getQueue() const {
		return this->queue;
	}

	// Setter
	void setQueue(Queue* newQueue) {
		this->queue = newQueue;
		return;
	}

	bool isBalanced(std::string s) {
		// Since every open bracket will have a
		// matching closing bracket, the input
		// string _must_ be even in length to
		// meet the criteria of being balanced.
		if(s.length() % 2 != 0) return false;

		// Load queue with characters in string
		for(int i = 0; i < s.length(); i++) {
			Node* node = new Node(s[i]);
			this->getQueue()->enqueue(node);
		}

		// Check the string for the solution using a queue.
		// This will be done by dequeue-ing one item at a time.
		// If the item is a '(', increment the counter by one.
		// If the item is a ')', decrement the counter by one.
		// If at any time the counter is negative, the input is unbalanced.
		// This is the inverse of a stack since Queues are FIFO and stacks are FILO.
		// If the counter is non-zero at the end, the input is unbalanced.
		int count = 0;
		Node* cur;
		size_t numIterations = this->getQueue()->getLen();
		for(int i = 0; i < numIterations; i++) {
			cur = this->getQueue()->dequeue();
			if(cur->getData() == '(') count++;
			if(cur->getData() == ')') count--;
			if(count < 0) return false;
		}

		return count == 0;
	}
};

// Iterate through a given string to validate if it is
// a good input for the problem.
bool checkInputStr(std::string str) {
	for(int i = 0; i < str.length(); i++) {
		if(str[i] != '(' && str[i] != ')') return false;
	}
	return true;
}

int main() {
    // TODO: Implement user input that takes an arbitrary
    // line of parentheses ['('], [')'] and processes them to
    // see if they are balanced or not (each open bracket
	// has a matching closed bracket).
	//
	// EX: "((())())()" ✔︎		"))()" ✘	"(()))" ✘

	// Initialize checkers
	StackParenthesesChecker checkerStack = StackParenthesesChecker();
	QueueParenthesesChecker checkerQueue = QueueParenthesesChecker();
	Stack* myStack = new Stack();
	Queue* myQueue = new Queue();
	checkerStack.setStack(myStack);
	checkerQueue.setQueue(myQueue);

	// Asserts to ensure program is functioning
	assert(checkerStack.isBalanced("((())())()"));
	assert(checkerQueue.isBalanced("((())())()"));

	assert(!checkerStack.isBalanced("))()"));
	assert(!checkerQueue.isBalanced("))()"));

	assert(!checkerStack.isBalanced("(()))"));
	assert(!checkerQueue.isBalanced("(()))"));

	

	// USER INPUT SECTION
	std::string userStr;

	// Take first user input, then all future inputs
	// are taken from within the while loop. The user
	// enters 'q' or 'Q' when they want to stop the program.
	std::cout << "Input string of parentheses (or 'q' to quit): ";
	std::getline(std::cin, userStr);
	while(std::tolower(userStr[0]) != 'q') {
		// Start by checking user's input for validity
		if(!checkInputStr(userStr)) {
			std::cout << "Invalid input." << std::endl;
			std::cout << "Input string of parentheses (or 'q' to quit): ";
			std::getline(std::cin, userStr);
			continue;
		}

		// Check user input with both stack & queue, then
		// output if it cleared either.
		bool stackClear = checkerStack.isBalanced(userStr);
		bool queueClear = checkerQueue.isBalanced(userStr);

		if(stackClear) std::cout << "Input is balanced with stack." << std::endl;
		else std::cout << "Input is not balanced with stack." << std::endl;

		if(queueClear) std::cout << "Input is balanced with queue." << std::endl;
		else std::cout << "Input is not balanced with queue." << std::endl;

		// Clear checker's and take new user input.
		checkerStack.getStack()->clear();
		checkerQueue.getQueue()->clear();
		std::cout << "Input string of parentheses (or 'q' to quit): ";
		std::getline(std::cin, userStr);
	}



	/*
	*========================================================
	*		UNIT TESTING
	*========================================================
	*/

    // The unit tests below no doubt are not
    // "proper" for true unit testing. I have
    // no doubt asserts would be preferable,
    // but given the scope of this assignment
    // I kind of can't be bothered. Oh, well!


	// // Array of Nodes for unit testing
    // Node* nodeArray[] {     new Node('1'), new Node('2'), new Node('3'),
    //                         new Node('4'), new Node('5'), new Node('6'), };

    // // List testing
    // LinkedList myList = LinkedList();
    // for(int i = 0; i < (sizeof(nodeArray) / sizeof(nodeArray[0])); i++) {
    //     myList.add(i, nodeArray[i]);
    // }
    // myList.print();
    // myList.remove(3);
    // myList.print();

    // // Stack testing
    // Stack myStack = Stack();
    // for(int i = 0; i < (sizeof(nodeArray) / sizeof(nodeArray[0])); i++) {
    //     myStack.push(nodeArray[i]);
    // }
    // myStack.print();
    // myStack.clear();
    // myStack.print();

	// // Queue testing
	// Queue myQueue = Queue();
	// for(int i = 0; i < (sizeof(nodeArray) / sizeof(nodeArray[0])); i++) {
    //     myQueue.enqueue(nodeArray[i]);
    // }
	// myQueue.print();
	// Node* removed = myQueue.dequeue();
	// removed->print();
	// removed = myQueue.dequeue();
	// removed->print();

    return 0;
}

/*
 *  NOTE: ChatGPT and Google Gemini were used as tools along with posts on
 *  StackOverflow to both get the C++ compiler running on my MacBook
 *  (M1 MacBook Air) and to quickly gain an understanding of syntax
 *  conventions in the C++ language (as well as some convenient 
 *  features for using OOP). It was not, however, used to copy paste code
 *  as many students have been doing. I hope this will be understandable
 *  to you (Dr. Rhodes), given this IS my first time coding in C++.
 * 
 *  -teddyg
 */