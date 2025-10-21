#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
class QueueInterface {
public:
    virtual void enqueue(int value) = 0;
    virtual int dequeue() = 0;
    virtual bool isEmpty() const = 0;
    virtual void display() = 0;
    virtual ~QueueInterface() {}
    virtual size_t size() const = 0;
    virtual int front() const = 0;
    virtual int rear() const = 0;
};


class ArrayQueue : public QueueInterface {
private:
    int* arr;
    int capacity;
    int frontIndex;
    int sizeCount;
public:
    ArrayQueue(int size = 100) : capacity(size), frontIndex(0), sizeCount(0)
    {
        arr = new int[capacity];
    }

    ~ArrayQueue()
    {
        delete[] arr;
    }
    void enqueue(int value) override
    {
        if(sizeCount == capacity) {
            std::cerr << "Queue Overflow\n";
            return;
        }
        int rearIndex = (frontIndex + sizeCount) % capacity;
        arr[rearIndex] = value;
        sizeCount++;  
    }

    int dequeue() override
    {
        if(isEmpty()) {
            std::cerr << "Queue Underflow\n";
            return -1;
        }
        int dequeuedValue = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        sizeCount--;
        return dequeuedValue;
    }


    bool isEmpty() const override
    {
        return sizeCount == 0;
    }

    int front() const override
    {
        if(isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return arr[frontIndex];
    }

    int rear() const override
    {
        if(isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        int rearIndex = (frontIndex + sizeCount - 1) % capacity;
        return arr[rearIndex];
    }


    void display() override
    {
        std::cout << "Queue elements: ";
        for (int i = 0; i < sizeCount; ++i) {
            int index = (frontIndex + i) % capacity;
            std::cout << arr[index] << " ";
        }
        std::cout << "\n";
    }
    
    size_t size() const override
    {
        return sizeCount;
    }
};


class LinkedListQueue : public QueueInterface {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* frontNode;
    Node* rearNode;
    size_t sizeCount;
public:
    LinkedListQueue() : frontNode(nullptr), rearNode(nullptr), sizeCount(0) {}
    ~LinkedListQueue()
    {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(int value) override
    {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        sizeCount++;
    }

    int dequeue() override
    {
        if(isEmpty()) {
            std::cerr << "Queue Underflow\n";
            return -1;
        }
        Node* temp = frontNode;
        int dequeuedValue = frontNode->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        sizeCount--;
        return dequeuedValue;
    }

    bool isEmpty() const override
    {
        return sizeCount == 0;
    }

    void display() override
    {
        std::cout << "Queue elements: ";
        Node* current = frontNode;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
    int front() const override
    {
        if(isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    int rear() const override
    {
        if(isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return rearNode->data;
    }

    size_t size() const override
    {   
        return sizeCount;
    }
};

class ThreadSafeQueue : public QueueInterface {
private:
    std::deque<int> data;
    mutable std::mutex mtx;

public:
    void enqueue(int value) override {
        std::lock_guard<std::mutex> lock(mtx);
        data.push_back(value);
    }

    int dequeue() override {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) {
            throw std::underflow_error("Queue underflow");
        }
        int value = data.front();
        data.pop_front();
        return value;
    }

    bool isEmpty() const override {
        std::lock_guard<std::mutex> lock(mtx);
        return data.empty();
    }

    void display() override {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Queue elements: ";
        for (int val : data)
            std::cout << val << " ";
        std::cout << "\n";
    }

    int front() const override {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty())
            throw std::runtime_error("Queue is empty");
        return data.front();
    }

    int rear() const override {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty())
            throw std::runtime_error("Queue is empty");
        return data.back();
    }

    size_t size() const override {
        std::lock_guard<std::mutex> lock(mtx);
        return data.size();
    }
};
