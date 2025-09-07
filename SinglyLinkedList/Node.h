
template <typename T>
class Node  {
protected:
    T data;
    Node* next;

public:
    Node(T val) {
        data = val;
        next = nullptr;
    }

    ~Node() {
        // Destructor to free memory if needed
    }

    void display() {
        cout << data << " -> ";
    }

    void setData(T val) {
        data = val;
    }

    T getData() {
        return data;
    }

    void setNext(Node* nextNode) {
        next = nextNode;
    }

    Node* getNext() {
        return next;
    }
};
