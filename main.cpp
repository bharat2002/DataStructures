#include <iostream>
#include "SkipLinkedList/SkipLinkedList.h"
int main() {
    SkipLinkedList list(6); // maxLevel = 6, probability = 0.5


    for(int i = 0; i < 20 ;i++) {
        list.insert(rand()%99);
        list.display();
    }
    

    list.search(40) ? std::cout << "Found 50\n" : std::cout << "50 Not Found\n";
    list.search(99) ? std::cout << "Found 75\n" : std::cout << "75 Not Found\n";
   
    return 0;
}