# pragma once

template<class T>
struct Node
{
    T* data;
    Node* prev;
    Node* next;

    Node(T* pData)
    : data(pData), prev(NULL), next(NULL)
    {}
};
