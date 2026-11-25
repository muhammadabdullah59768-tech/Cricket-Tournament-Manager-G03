
#include <iostream>
#include "../include/UndoStack.h"
using namespace std;

int main() {

    cout << "Name: Javeria Latif" << endl;
    cout << "Roll No: 2501323" << endl;
    cout << "Class: BSCS III B" << endl;

    UndoStack stack;

    cout << "\n--- Stack Testing ---" << endl;

    // Push three events
    BallEvent e1(1, 4, 0, 0, 0, 0);
    BallEvent e2(2, 6, 0, 4, 0, 1);
    BallEvent e3(3, 0, 1, 10, 0, 2);

    stack.push(e1);
    stack.push(e2);
    stack.push(e3);

    cout << "\nStack size: " << stack.size() << endl;

    // Check peek
    cout << "\nTop event:" << endl;
    stack.peek().displayDetails();

    // Display all events
    stack.display();

    // Pop one event
    cout << "\nPopped event:" << endl;
    stack.pop().displayDetails();

    cout << "\nStack size after pop: " << stack.size() << endl;

    // Check empty
    cout << "\nIs stack empty? ";
    cout << (stack.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
