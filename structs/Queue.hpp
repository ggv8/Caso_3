# pragma once
# include "List.hpp"

template<class T>
class Queue
{
    private:
        List<T>* queueList;
    
    public:
        Queue() {
            queueList = new List<T>;
        }

        bool isEmpty() {
            return queueList->isEmpty();
        }

        T* getFront() {
            return queueList->getFirst();
        }

        void enqueue(T* pData) {
            queueList->add(pData);
        }

        T* dequeue() {
            return queueList->remove(0);
        }

    
};