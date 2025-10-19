#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <cstring>  // for memset
#include <cstdlib>  // for rand()

#define SKIP_LST_MAX_LEVEL 6
#define PROBABILITY 0.5

class SkipLinkedList {
private:
    struct Node {
        int value;
        std::vector<Node*> forward;
        Node(int val, int level) : value(val), forward(level, nullptr) {}
    };

    Node* head;
    int maxLevel;
    int currentLevel;

    int randomLevel() {
        int level = 1;
        while ((static_cast<float>(rand()) / RAND_MAX) < PROBABILITY && level < maxLevel)
            level++;
        return level;
    }

public:
    SkipLinkedList(int maxLevel = SKIP_LST_MAX_LEVEL)
        : maxLevel(maxLevel), currentLevel(1)
    {
        head = new Node(INT_MIN, maxLevel);
    }

    ~SkipLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(int value) {
        Node* update[SKIP_LST_MAX_LEVEL];
        memset(update, 0, sizeof(Node*) * SKIP_LST_MAX_LEVEL);

        Node* current = head;
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value)
                current = current->forward[i];
            update[i] = current;
        }

        int nodeLevel = randomLevel();
        if (nodeLevel > currentLevel) {
            for (int i = currentLevel; i < nodeLevel; i++)
                update[i] = head;
            currentLevel = nodeLevel;
        }

        Node* newNode = new Node(value, nodeLevel);
        for (int i = 0; i < nodeLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool search(int value) {
        Node* current = head;
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value)
                current = current->forward[i];
        }
        current = current->forward[0];

        if (current && current->value == value)            
        {
            std::cout << "Found: " << value << "\n";
            return true;
        }
        else    
        {
            std::cout << "Not Found: " << value << "\n";
            return false;
        }
    }


    void display() {
        if (head->forward[0] == nullptr) {
            std::cout << "List is empty.\n";
            return;
        }

        std::cout << "\n--- Skip List ---\n";
        for (int i = currentLevel - 1; i >= 0; i--) {
            Node* node = head->forward[i];
            std::cout << "Level " << i + 1 << ": ";
            while (node) {
                std::cout << node->value << " ";
                node = node->forward[i];
            }
            std::cout << "\n";
        }
        std::cout << "-----------------\n";
    }
};
