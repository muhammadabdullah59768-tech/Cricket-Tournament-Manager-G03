
#include <iostream>
using namespace std;

int main() {

    cout << "Name: Javeria Latif" << endl;
    cout << "Roll No: 2501323" << endl;
    cout << "Class: BSCS III B" << endl;

    int stack[5];
    int top = -1;

    // Push elements
    stack[++top] = 10;
    stack[++top] = 20;
    stack[++top] = 30;

    cout << "\n--- Stack Demo ---" << endl;

    cout << "Pushed: 10, 20, 30" << endl;

    // Display stack
    cout << "Stack elements: ";
    for (int i = top; i >= 0; i--) {
        cout << stack[i] << " ";
    }

    // Peek operation
    cout << "\nTop element: " << stack[top] << endl;

    // Pop operation
    cout << "Popped element: " << stack[top] << endl;
    top--;

    // Display after pop
    cout << "After pop: ";
    for (int i = top; i >= 0; i--) {
        cout << stack[i] << " ";
    }

    cout << endl;

    return 0;
}
