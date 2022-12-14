# pragma once

template<class T>
struct Node
{
    public:
        T* data;
        Node* prev;
        Node* next;

        Node(T* pData)
        : data(pData), prev(NULL), next(NULL)
        {}
};
