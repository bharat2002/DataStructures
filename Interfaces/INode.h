#include <iostream>
#pragma once
using namespace std;

template <typename T>
class INode {
public:
    virtual T getData() = 0;
    virtual void setData(T val) = 0;
    virtual INode<T>* getNext() = 0;
    virtual void setNext(INode<T>* nextNode) = 0;
    virtual ~INode() {}
};  