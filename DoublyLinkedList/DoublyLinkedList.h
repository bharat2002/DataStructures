#include "DoublyLInkedListNode.h"
#include "../Interfaces/InsertionInterface.h"
#include "../Interfaces/DeletionInterface.h"

template <typename T>
class DoublyLinkedList: InsertionInterface<T>, DeletionInterface<T> {
private:
    DoublyLinkedListNode<T>* head;
    DoublyLinkedListNode<T>* tail;
    int size;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoublyLinkedList() {
        DoublyLinkedListNode<T>* current = head;
        DoublyLinkedListNode<T>* nextNode;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    //Getters
    DoublyLinkedListNode<T>* getHead() {
        return head;
    } 
    DoublyLinkedListNode<T>* getTail() {
        return tail;
    }
    int getSize() {
        return size;
    }

    void addFirst(T val)
    {
        DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(val);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void addLast(T val)
    {
        DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(val);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void addAt(int index, T val)
    {
        if(index < 0 || index > size) {
            cout << "Index out of bounds" << endl;
            return;
        }

        if(index == 0) {
            addFirst(val);
            return;
        }

        if(index == size) {
            addLast(val);
            return;
        }

        DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(val);
        DoublyLinkedListNode<T>* current = head;
        int currentPos = 1;
        while(currentPos < index) {
            current = current->next;
            currentPos++;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;        
        size++;

    }

    void deleteFirst() {
        if(size == 0) {
            cout << "List is empty" << endl;
            return;
        }

        DoublyLinkedListNode<T>* temp = head;
        head = head->next;
        if(head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        size--;

        if(size == 0) {
            tail = nullptr;
        }
    }

    void deleteLast() {
        if(size == 0) {
            cout << "List is empty" << endl;
            return;
        }

        DoublyLinkedListNode<T>* temp = tail;
        tail = tail->prev;
        if(tail != nullptr) {
            tail->next = nullptr;
        }
        delete temp;
        size--;

        if(size == 0) {
            head = nullptr;
        }
    }

    void display() {
        DoublyLinkedListNode<T>* current = head;
        while (current != nullptr) {
            current->display();
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};