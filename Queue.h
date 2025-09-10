// C++ program for insertion and
// deletion in Circular Queue
#include <iostream>
using namespace std;

class CircularQueue {
private:
    int *arr;        
    int front, size; 
    int capacity;    

public:
    CircularQueue(int c) {
        arr = new int[c];
        capacity = c;
        front = size = 0; 
    }

    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(int x) {
        if (size == capacity) {
            cout << "Queue is full" << endl;
            return;
        }
        int rear = (front + size) % capacity;
        arr[rear] = x;
        size++;
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    int getFront() const {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return -1; 
        }
        return arr[front];
    }

    int getRear() const {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return -1; 
        }
        int rear = (front + size - 1) % capacity;
        return arr[rear];
    }
    int getSize() const {
        return size;
    }
    int getCapacity() const {
        return capacity;
    }


};