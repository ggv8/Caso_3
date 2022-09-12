# include <iostream>
# include "structs/Queue.hpp"
# include "structs/QueueStacks.hpp"

using namespace std;

int main() {
    cout << "Ejercicio #2: Queue TDA via Stacks" << endl;
    Queue<int> regularQueue;
    QueueStacks<int> stackQueue;

    int numValues[5] = {7, 89, 20, 49, 127};
    for (int index = 0; index < 5; index++) {
        regularQueue.enqueue( &numValues[index] );
        stackQueue.enqueue( &numValues[index] );
    }

    cout << "front() method comparison: " << endl;
    cout << "\tRegular Queue returned " << *regularQueue.getFront() << endl;
    cout << "\tStack Queue returned " << *stackQueue.getFront() << endl;

    cout << "dequeue() method comparison: " << endl;
    while (! regularQueue.isEmpty()) {
        cout << "\tRegular dequeue (" << *regularQueue.dequeue() << ") vs ";
        cout << "Stack dequeue (" << *stackQueue.dequeue() << ") \n";
    }

    return 0;
}