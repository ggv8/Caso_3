# pragma once
# include "Stack.hpp"

template<class T>
class QueueStacks
{
    private:
        Stack<T>* mainStack;

    public:
        QueueStacks() {
            mainStack = new Stack<T>;
        }

        bool isEmpty() {
            return mainStack->isEmpty();
        }
        
        T* getFront() {
            return mainStack->top();
        }

        void enqueue(T* pData) {
            Stack<T>* reverseStack = new Stack<T>;
            while (! mainStack->isEmpty()) {
                T* elem = mainStack->pop();
                reverseStack->push( elem );
            }
            mainStack->push(pData);

            while (! reverseStack->isEmpty()) {
                T* elem = reverseStack->pop();
                mainStack->push( elem );
            }
            delete reverseStack;
        }

        T* dequeue() {
            return mainStack->pop();
        }
};