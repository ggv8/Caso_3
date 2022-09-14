# pragma once
# include "List.hpp"

template<class T>
class Stack
{
    private:
        List<T>* stackList;
    
    public:
        Stack() {
            stackList = new List<T>;
        }

        bool isEmpty() {
            return stackList->isEmpty();
        }

        T* top() {
            return stackList->getFirst();
        }

        void push(T* pData) {
            stackList->insert(pData, 0);
        }

        T* pop() {
            return stackList->remove(0);
        }
};