#include <iostream>
#include <string>
using namespace std;

class CircularQueue {
private:
    int* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    CircularQueue(int cap) {
        if (cap < 1) cap = 1;
        capacity = cap;
        data = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~CircularQueue() { delete[] data; }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    int size() const { return count; }

    bool enqueue(int teamID) {
        if (isFull()) return false;
        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = teamID;
        count++;
        return true;
    }

    bool dequeue(int& teamID) {
        if (isEmpty()) return false;
        teamID = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return true;
    }

    bool peek(int& teamID) const {
        if (isEmpty()) return false;
        teamID = data[frontIndex];
        return true;
    }

    bool getAt(int pos, int& teamID) const {
        if (pos < 0 || pos >= count) return false;
        teamID = data[(frontIndex + pos) % capacity];
        return true;
    }

    bool rotate() {
        int id;
        if (!dequeue(id)) return false;
        return enqueue(id);
    }

    void display() const {
        if (isEmpty()) {
            cout << "  Queue: [empty]\n";
            return;
        }
        cout << "  Queue (front -> rear): ";
        for (int i = 0; i < count; i++) {
            cout << "T" << data[(frontIndex + i) % capacity];
            if (i < count - 1) cout << " -> ";
        }
        cout << "   [size " << count << "/" << capacity
             << ", front idx " << frontIndex << ", rear idx " << rearIndex << "]\n";
    }
};

void line(const string& title) {
    cout << "\n--- " << title << " ---\n";
}

int main() {
    cout << "===== Circular Queue Demo (Team IDs) =====\n";

    CircularQueue q(4);

    line("1. Empty queue");
    q.display();
    int id;
    cout << "  Dequeue on empty: " << (q.dequeue(id) ? "ok" : "rejected (empty)") << "\n";

    line("2. Enqueue teams 101, 102, 103, 104");
    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);
    q.enqueue(104);
    q.display();
    cout << "  Enqueue 105 when full: " << (q.enqueue(105) ? "ok" : "rejected (full)") << "\n";

    line("3. Dequeue two teams");
    q.dequeue(id); cout << "  Removed T" << id << "\n";
    q.dequeue(id); cout << "  Removed T" << id << "\n";
    q.display();

    line("4. Wrap-around: enqueue 105 and 106");
    q.enqueue(105);
    q.enqueue(106);
    q.display();
    cout << "  Rear index went back to the start of the array, no space wasted.\n";

    line("5. Peek");
    if (q.peek(id)) cout << "  Front team is T" << id << "\n";

    line("6. Rotate (front team goes to rear)");
    for (int r = 1; r <= 2; r++) {
        q.rotate();
        cout << "  After rotate " << r << ":\n";
        q.display();
    }

    line("7. Round-robin preview with 4 teams (circle method)");
    CircularQueue others(3);
    others.enqueue(2);
    others.enqueue(3);
    others.enqueue(4);
    int fixed = 1, fixtures = 0;
    for (int round = 1; round <= 3; round++) {
        int a, b, c;
        others.getAt(0, a);
        others.getAt(1, b);
        others.getAt(2, c);
        cout << "  Round " << round << ": T" << fixed << " vs T" << a
             << ",  T" << b << " vs T" << c << "\n";
        fixtures += 2;
        others.rotate();
    }
    cout << "  Total fixtures: " << fixtures << " (4 teams -> 4*3/2 = 6)\n";

    line("8. Empty the queue");
    while (q.dequeue(id)) cout << "  Removed T" << id << "\n";
    q.display();

    cout << "\n===== Demo finished =====\n";
    return 0;
}
