#include <iostream>
#pragma once
using namespace std;
#include "Node.h"
#include "../Interfaces/InsertionInterface.h"
#include "../Interfaces/DeletionInterface.h"
#include "../Interfaces/PrintableList.h"
template <typename T>
class LinkedList: InsertionInterface<T>, DeletionInterface<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~LinkedList() {
        Node<T>* current = head;
        Node<T>* nextNode;
        while (current != nullptr) {
            nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
    }

    //Getters
    Node<T>* getHead() {
        return head;
    } 
    Node<T>* getTail() {
        return tail;
    }
    int getSize() {
        return size;
    }

    void addFirst(T val)
    {
        Node<T>* newNode = new Node<T>(val);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->setNext(head);
            head = newNode;
        }
        size++;
    }

    void addLast(T val)
    {
        Node<T>* newNode = new Node<T>(val);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->setNext(newNode);
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

        Node<T>* newNode = new Node<T>(val);
        Node<T>* current = head;
        int currentPos = 1;
        while(currentPos < index) {
            current->setNext(current->getNext());
            currentPos++;
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);        
        size++;

    }

    void deleteFirst() {
        if(size == 0) {
            cout << "List is empty" << endl;
            return;
        }

        Node<T>* temp = head;
        head = head->getNext();
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

        if(size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
            return;
        }

        Node<T>* current = head;
        while(current->getNext() != tail) {
            current = current->getNext();
        }

        delete tail;
        tail = current;
        tail->setNext(nullptr);
        size--;
    }

    void deleteAt(int index) {
        if(index < 0 || index >= size) {
            cout << "Index out of bounds" << endl;
            return;
        }

        if(index == 0) {
            deleteFirst();
            return;
        }

        if(index == size - 1) {
            deleteLast();
            return;
        }

        Node<T>* current = head;
        int currentPos = 1;
        while(currentPos < index) {
            current = current->getNext();
            currentPos++;
        }

        Node<T>* temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
        size--;
    }


};