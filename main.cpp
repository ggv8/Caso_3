# include <iostream>
# include "structs/Queue.hpp"
# include "structs/QueueStacks.hpp"
# include "Postfix/PostfixParser.hpp"

using namespace std;

int main() {
    /* cout << "Ejercicio #2: Queue TDA via Stacks" << endl;
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
    } */

    PostfixParser parser;
    string inf1 = "57 + 1 + 80 * 25";
    string inf2 = "(3 + 4) * 8";
    string inf3 = "(3 * 4) + 8";
    string inf4 = "(4 - (3+4) * 8)";
    string inf5 = "(17 + 50) + 41 + 8";
    parser.parseInfix(inf1);
    cout << "\t Postfix: '" << parser.getNotation();
    cout << "' = " << parser.evaluate() << endl;

    parser.parseInfix(inf2);
    cout << "\t Postfix: '" << parser.getNotation();
    cout << "' = " << parser.evaluate() << endl;

    parser.parseInfix(inf3);
    cout << "\t Postfix: '" << parser.getNotation();
    cout << "' = " << parser.evaluate() << endl;

    parser.parseInfix(inf4);
    cout << "\t Postfix: '" << parser.getNotation();
    cout << "' = " << parser.evaluate() << endl;

    parser.parseInfix(inf5);
    cout << "\t Postfix: '" << parser.getNotation();
    cout << "' = " << parser.evaluate() << endl;

    return 0;
}