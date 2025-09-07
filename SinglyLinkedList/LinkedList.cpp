// #include <iostream>
// #include "LinkedList.h"

// template <typename T>
// LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}
        
// template <typename T>
// void LinkedList<T>::addFirst(T val) {
//     Node<T>* newNode = new Node<T>(val);
//     if (size == 0) {
//         head = newNode;
//         tail = newNode;
//     } else {
//         newNode->next = head;
//         head = newNode;
//     }
//     size++;
// }

// template <typename T>
// void LinkedList<T>::display() {
//     Node<T>* current = head;
//     while (current != nullptr) {
//         current->display();
//         current = current->next;
//     }
//     std::cout << "nullptr" << std::endl;
// }

// template <typename T>
// LinkedList<T>::~LinkedList()
// {
//     Node<T>* current = head;
//     Node<T>* nextNode;
//     while (current != nullptr) {
//         nextNode = current->next;
//         delete current;
//         current = nextNode;
//     }
// }