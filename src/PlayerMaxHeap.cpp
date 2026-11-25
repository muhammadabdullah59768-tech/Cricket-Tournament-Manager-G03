
#include "../include/PlayerMaxHeap.h"

// Constructor.
PlayerMaxHeap::PlayerMaxHeap() {
    size = 0;
}

// Compares two players.
bool PlayerMaxHeap::isGreater(PlayerStat a, PlayerStat b) const {

    if (a.getRuns() != b.getRuns()) {
        return a.getRuns() > b.getRuns();
    }

    return a.getWickets() > b.getWickets();
}

// Moves player upward.
void PlayerMaxHeap::heapifyUp(int index) {

    while (index > 0) {

        int parent = (index - 1) / 2;

        if (isGreater(heap[index], heap[parent])) {

            PlayerStat temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            index = parent;
        }
        else {
            break;
        }
    }
}

// Moves player downward.
void PlayerMaxHeap::heapifyDown(int index) {

    while (true) {

        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size &&
            isGreater(heap[left], heap[largest])) {
            largest = left;
        }

        if (right < size &&
            isGreater(heap[right], heap[largest])) {
            largest = right;
        }

        if (largest != index) {

            PlayerStat temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;

            index = largest;
        }
        else {
            break;
        }
    }
}

// Checks whether heap is empty.
bool PlayerMaxHeap::isEmpty() const {
    return size == 0;
}

// Checks whether heap is full.
bool PlayerMaxHeap::isFull() const {
    return size == MAX_SIZE;
}

// Inserts player into heap.
void PlayerMaxHeap::insert(PlayerStat player) {

    if (isFull()) {
        cout << "Heap is full!" << endl;
        return;
    }

    heap[size] = player;

    heapifyUp(size);

    size++;
}

// Returns maximum player.
PlayerStat PlayerMaxHeap::peek() const {

    if (isEmpty()) {
        cout << "Heap is empty!" << endl;
        return PlayerStat();
    }

    return heap[0];
}

// Removes maximum player.
PlayerStat PlayerMaxHeap::extractMax() {

    if (isEmpty()) {
        cout << "Heap is empty!" << endl;
        return PlayerStat();
    }

    PlayerStat maxPlayer = heap[0];

    heap[0] = heap[size - 1];

    size--;

    if (size > 0) {
        heapifyDown(0);
    }

    return maxPlayer;
}

// Earlier function name compatibility.
PlayerStat PlayerMaxHeap::removeMax() {
    return extractMax();
}

// Displays heap.
void PlayerMaxHeap::display() const {

    if (isEmpty()) {
        cout << "No players available!" << endl;
        return;
    }

    cout << "\n--- Player Leaderboard ---" << endl;

    for (int i = 0; i < size; i++) {
        heap[i].displayDetails();
    }
}

// Returns heap size.
int PlayerMaxHeap::getSize() const {
    return size;
}
