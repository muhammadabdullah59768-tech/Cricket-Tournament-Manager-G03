#include <iostream>
#include "TeamQueue.h"
using namespace std;

TeamQueue::TeamQueue(int cap) {
    if (cap < 1) cap = 1;
    capacity = cap;
    data = new int[capacity];
    frontIndex = 0;
    rearIndex = -1;
    count = 0;
}

TeamQueue::~TeamQueue() {
    delete[] data;
}

bool TeamQueue::isEmpty() const {
    return count == 0;
}

bool TeamQueue::isFull() const {
    return count == capacity;
}

int TeamQueue::size() const {
    return count;
}

int TeamQueue::getCapacity() const {
    return capacity;
}

bool TeamQueue::enqueue(int teamID) {
    if (isFull()) return false;
    rearIndex = (rearIndex + 1) % capacity;
    data[rearIndex] = teamID;
    count++;
    return true;
}

bool TeamQueue::dequeue(int& teamID) {
    if (isEmpty()) return false;
    teamID = data[frontIndex];
    frontIndex = (frontIndex + 1) % capacity;
    count--;
    return true;
}

bool TeamQueue::peek(int& teamID) const {
    if (isEmpty()) return false;
    teamID = data[frontIndex];
    return true;
}

bool TeamQueue::getAt(int pos, int& teamID) const {
    if (pos < 0 || pos >= count) return false;
    teamID = data[(frontIndex + pos) % capacity];
    return true;
}

bool TeamQueue::rotate() {
    int id;
    if (!dequeue(id)) return false;
    return enqueue(id);
}

void TeamQueue::clear() {
    frontIndex = 0;
    rearIndex = -1;
    count = 0;
}

void TeamQueue::display() const {
    if (isEmpty()) {
        cout << "Queue: [empty]" << endl;
        return;
    }
    cout << "Queue (front -> rear): ";
    for (int i = 0; i < count; i++) {
        cout << data[(frontIndex + i) % capacity];
        if (i < count - 1) cout << " -> ";
    }
    cout << "  [" << count << "/" << capacity << "]" << endl;
}
