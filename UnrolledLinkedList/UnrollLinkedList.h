#pragma once
#include <iostream>

#define URLD_LST_DEF_SIZE 4

class UnrolledLinkedList {
private:
    struct Node {
        int* arr;
        int count;
        int capacity;
        Node* next;

        Node(int size)
            : arr(new int[size]), count(0), capacity(size), next(nullptr) {}

        ~Node() { delete[] arr; }

        void Rebalance() {
            if (!next)
                next = new Node(capacity);

            int moveStart = count / 2;
            int moveCount = count - moveStart;

            for (int i = 0; i < moveCount; ++i) {
                next->arr[i] = arr[moveStart + i];
            }
            next->count = moveCount;
            count = moveStart;
        }
    };

    Node* head;
    Node* tail;
    int nodeCapacity;
    int totalCount;

public:
    explicit UnrolledLinkedList(int nodeCapacity = URLD_LST_DEF_SIZE) {
        this->nodeCapacity = nodeCapacity > 0 ? nodeCapacity : URLD_LST_DEF_SIZE;
        totalCount = 0;
        head = new Node(this->nodeCapacity);
        tail = head;
    }

    ~UnrolledLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    bool search(int value) const {
        Node* current = head;
        while (current) {
            for (int i = 0; i < current->count; ++i) {
                if (current->arr[i] == value) {
                    return true;
                }
            }
            current = current->next;
        }
        return false;
    }

    void insert(int value) {
        Node* current = tail;
        if (current->count < nodeCapacity) {
            current->arr[current->count++] = value;
        } else {
            current->Rebalance();
            if (current->next) {
                tail = current->next;
            } else {
                tail = new Node(nodeCapacity);
                current->next = tail;
            }
            tail->arr[tail->count++] = value;
        }
        ++totalCount;
    }

    bool remove(int value) {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            for (int i = 0; i < current->count; ++i) {
                if (current->arr[i] == value) {
                    for (int j = i; j < current->count - 1; ++j) {
                        current->arr[j] = current->arr[j + 1];
                    }
                    current->count--;
                    --totalCount;

                    if (current->count < nodeCapacity / 2 && current->next) {
                        Node* nxt = current->next;
                        if (nxt->count > nodeCapacity / 2) {
                            current->arr[current->count++] = nxt->arr[0];
                            for (int j = 0; j < nxt->count - 1; ++j) {
                                nxt->arr[j] = nxt->arr[j + 1];
                            }
                            nxt->count--;
                        } else if (current->count + nxt->count <= nodeCapacity) {
                            for (int j = 0; j < nxt->count; ++j) {
                                current->arr[current->count++] = nxt->arr[j];
                            }
                            current->next = nxt->next;
                            if (nxt == tail)
                                tail = current;
                            delete nxt;
                        }
                    }

                    return true;
                }
            }
            prev = current;
            current = current->next;
        }

        return false; // Not found
    }

    void display() const {
        Node* current = head;
        std::cout << "Unrolled Linked List contents:\n";
        while (current) {
            for (int i = 0; i < current->count; ++i) {
                std::cout << current->arr[i] << " ";
            }
            std::cout << "\n";
            current = current->next;
        }
        std::cout << "(total elements = " << totalCount << ")\n";
    }
};
