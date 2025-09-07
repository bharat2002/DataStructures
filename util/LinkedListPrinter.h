#pragma once
#include <iostream>
#include "../SinglyLinkedList/LinkedList.h"

using namespace std;

template <typename T>
class LinkedListPrinter {
public:
    static void printList(LinkedList<T>& list) {
        Node<T>* current = list.getHead();
        while (current != nullptr) {
            cout << current->getData() << " -> ";
            current = current->getNext();
        }
        cout << "nullptr" << endl;
    }

    static void display(LinkedList<T>& list) {
        cout << "List (size " << list.getSize() << "): ";
        printList(list);
    }

    static void printReverse(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        printReverse(node->next);
        cout << node->data << " -> ";
    }
    
};