#include "Node.h"

template<typename T>
class DoublyLinkedListNode extends Node<T> {
public:
    DoublyLinkedListNode<T>* next;
    DoublyLinkedListNode<T>* prev;
    DoublyLinkedListNode(T val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }

    DoublyLinkedListNode(T val, DoublyLinkedListNode<T>* prevNode, DoublyLinkedListNode<T>* nextNode) {
        data = val;
        next = nextNode;
        prev = prevNode;
    }

    ~DoublyLinkedListNode() {
        // Destructor to free memory if needed
    }
    void display() {
        cout << data << " <-> ";
    }
};