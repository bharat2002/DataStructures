#include <iostream>
#include "SkipLinkedList/SkipLinkedList.h"
int main() {
    SkipLinkedList list(6); // maxLevel = 6, probability = 0.5


    for(int i = 0; i < 20 ;i++) {
        list.insert(rand()%99);
        list.display();
    }
    
    list.insert(50);
    list.insert(75);
    if(list.search(50)) {
        std::cout << "50 found in the list.\n";
    } else {
        std::cout << "50 not found in the list.\n";
    }
    list.display();
    list.remove(92);
    list.display();
    list.remove(34);
    list.display();
    return 0;
}