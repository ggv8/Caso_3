# include <iostream>
# include "structs/Queue.hpp"
# include "structs/QueueStacks.hpp"
# include "Postfix/PostfixParser.hpp"
# include "Airport/Airport.hpp"

# define TOTAL_TRACKS 8
# define TOTAL_FLIGHTS 18
# define START_HOUR 7
# define END_HOUR 22

using namespace std;

int main() {
    //-------------//
    // Ejercicio 1 //
    //-------------//
    cout << "Ejercicio #1: Parser de infijo a postfijo" << endl;
    string infixArray[] {
        "57 + 1 + 80 * 25",
        "(3 + 4) * 8",
        "(10 * 5) + 17",
        "(10 - (4+5) * 8)",
        "(17 + 50) + 41 + 8"
    };

    PostfixParser parser;
    for (int index = 0; index < 5; index++) {   // Demo
        parser.parseInfix(infixArray[index]);
        cout << "\t Postfix \"" << parser.getNotation();
        cout << "\" ==> " << parser.evaluate() << endl;
    }
    
    string infixInput;
    cout << "\nNotacion Infija: ";
    cin >> infixInput;

    parser.parseInfix(infixInput);
    cout << "\t Postfix \"" << parser.getNotation();
    cout << "\" ==> " << parser.evaluate() << endl;
    
    //-------------//
    // Ejercicio 2 //
    //-------------//
    cout << "\nEjercicio #2: Queue TDA via Stacks" << endl;
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

    //-------------//
    // Ejercicio 3 //
    //-------------//
    cout << "\nEjercicio #3: Despegues en aeropuerto" << endl;
    Airport airport = {TOTAL_TRACKS, TOTAL_FLIGHTS};
    airport.fillFlights(START_HOUR, END_HOUR);
    airport.assignTracks();
    airport.takeOff();

    return 0;
}