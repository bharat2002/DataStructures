#include <iostream>
#include <vector>
#include <limits>

class StackInterface {
public:
    virtual void push(int value) = 0;
    virtual int pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual void display() = 0;
    virtual ~StackInterface() {}
};

class VectorStack : public StackInterface {
private:
    std::vector<int> elements;
public:

    void push(int value)
    {
        elements.push_back(value);
    }
    int pop()
    {
        if(elements.empty()) {
            std::cerr << "Stack Underflow\n";
            return -1; 
        }
        int value = elements.back();
        elements.pop_back();
        return value;
    }
    bool isEmpty() const
    {
        return elements.empty();
    }
    void display()
    {
        std::cout << "Stack elements: ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    void clear()
    {
        elements.clear();
    }

    size_t size()
    {
        return elements.size();
    }

    int peek()
    {
        if(elements.empty()) {
            std::cerr << "Stack is empty\n";
            return -1; 
        }
        return elements.back();
    }
};

class ArrayStack : public StackInterface{
private:
    int* arr;
    int top;
    int capacity;
public:
    ArrayStack(int size = 100) : capacity(size), top(-1)
    {
        arr = new int[capacity];
    }

    ~ArrayStack()
    {
        delete[] arr;
    }

    void push(int value)
    {
        if (top == capacity - 1) {
            std::cerr << "Stack Overflow\n";
            return;
        }
        arr[++top] = value;
    }

    int pop()
    {
        if (top == -1) {
            std::cerr << "Stack Underflow\n";
            return -1; 
        }
        return arr[top--];
    }

    void display()
    {
        std::cout << "Stack elements: ";
        for (int i = top; i >= 0; --i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }

    void clear()
    {
        top = -1;
    }

    bool isEmpty() const
    {
        return top == -1;
    }

    int size() const
    {
        return top + 1;
    }

    int peek() const
    {
        if (top == -1) {
            std::cerr << "Stack is empty\n";
            return -1; 
        }
        return arr[top];
    }

    void resize(int newSize)
    {
        if (newSize <= capacity) {
            std::cerr << "New size must be greater than current size\n";
            return;
        }
        int* newArr = new int[newSize];
        for (int i = 0; i <= top; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newSize;
    }
};

class LinkedListStack: public StackInterface
{
    private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

     Node* top;
    public:
    LinkedListStack() : top(nullptr) {}
    ~LinkedListStack()
    {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(int value)
    {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int pop()
    {
        if(isEmpty()) {
            std::cerr << "Stack Underflow\n";
            return -1; 
        }
        Node* temp = top;
        int poppedValue = top->data;
        top = top->next;
        delete temp;
        return poppedValue;
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void display()
    {
        std::cout << "Stack elements: ";
        Node* current = top;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};
