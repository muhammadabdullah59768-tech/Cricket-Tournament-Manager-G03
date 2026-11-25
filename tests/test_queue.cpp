#include <iostream>
#include "TeamQueue.h"
using namespace std;

int main() {
    TeamQueue q(4);
    cout << boolalpha;
    int id;

    cout << "Empty at start: " << q.isEmpty() << endl;
    cout << "Dequeue on empty: " << q.dequeue(id) << endl;
    cout << "Peek on empty: " << q.peek(id) << endl;

    cout << "\n--- Enqueue 1, 2, 3, 4 ---" << endl;
    cout << "Enqueue 1: " << q.enqueue(1) << endl;
    cout << "Enqueue 2: " << q.enqueue(2) << endl;
    cout << "Enqueue 3: " << q.enqueue(3) << endl;
    cout << "Enqueue 4: " << q.enqueue(4) << endl;
    cout << "Enqueue 5 (full): " << q.enqueue(5) << endl;
    cout << "Is full: " << q.isFull() << endl;
    q.display();

    cout << "\n--- Dequeue two ---" << endl;
    q.dequeue(id); cout << "Removed: " << id << endl;
    q.dequeue(id); cout << "Removed: " << id << endl;
    q.display();

    cout << "\n--- Wrap-around: enqueue 5 and 6 ---" << endl;
    cout << "Enqueue 5: " << q.enqueue(5) << endl;
    cout << "Enqueue 6: " << q.enqueue(6) << endl;
    q.display();

    cout << "\n--- Peek and getAt ---" << endl;
    if (q.peek(id)) cout << "Front: " << id << endl;
    if (q.getAt(3, id)) cout << "Position 3: " << id << endl;
    cout << "Position 4 (invalid): " << q.getAt(4, id) << endl;

    cout << "\n--- Rotate twice ---" << endl;
    q.rotate(); q.display();
    q.rotate(); q.display();

    cout << "\n--- Clear ---" << endl;
    q.clear();
    cout << "Size after clear: " << q.size() << endl;
    q.display();
    return 0;
}
