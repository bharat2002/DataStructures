#include <iostream>
#include "SinglyLinkedList/LinkedList.h"
#include "util/LinkedListPrinter.h"
using namespace std;    
int main() {
    LinkedList<int> list;
    list.addFirst(10);

    // delete iterator;
    // LinkedListPrinter<int>::printList(list);
    // LinkedListPrinter<int>::printList(list);
    list.addFirst(20);
    // LinkedListPrinter<int>::printList(list);
    list.addFirst(30);
    // LinkedListPrinter<int>::printList(list);
    list.addFirst(40);
    auto iterator = list.createIterator();
     while(iterator->hasNext()) {
        cout << iterator->next() << " ";
    }
    cout << endl;
    delete iterator;
    // LinkedListPrinter<int>::printList(list);
    list.addFirst(50);
    // LinkedListPrinter<int>::printList(list);
    list.addAt(2, 25);
    // LinkedListPrinter<int>::printList(list);
    list.addLast(5);
    iterator = list.createIterator();
     while(iterator->hasNext()) {
        cout << iterator->next() << " ";
    }
    cout << endl;
    delete iterator;
    // LinkedListPrinter<int>::printList(list);
    list.addLast(1);
    // LinkedListPrinter<int>::printList(list);
    list.deleteFirst();
    // LinkedListPrinter<int>::printList(list);
    list.deleteLast();
    // LinkedListPrinter<int>::printList(list);

    return 0;
}