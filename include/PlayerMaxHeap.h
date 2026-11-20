
#ifndef PLAYERMAXHEAP_H
#define PLAYERMAXHEAP_H

#include <iostream>
#include "PlayerStat.h"
using namespace std;

// Stores players in a Max Heap.
class PlayerMaxHeap {
private:
    static const int MAX_SIZE = 100;
    PlayerStat heap[MAX_SIZE];
    int size;

    // Checks which player has higher priority.
    bool isGreater(PlayerStat a, PlayerStat b) const {
        if (a.getRuns() != b.getRuns()) {
            return a.getRuns() > b.getRuns();
        }

        return a.getWickets() > b.getWickets();
    }

    // Moves a player upward.
    void heapifyUp(int index) {
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

    // Moves a player downward.
    void heapifyDown(int index) {
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

public:
    PlayerMaxHeap() {
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == MAX_SIZE;
    }

    // Inserts a player into the heap.
    void insert(PlayerStat player) {
        if (isFull()) {
            cout << "Heap is full!" << endl;
            return;
        }

        heap[size] = player;
        heapifyUp(size);
        size++;
    }

    // Returns the player with maximum priority.
    PlayerStat peek() const {
        if (isEmpty()) {
            cout << "Heap is empty!" << endl;
            return PlayerStat();
        }

        return heap[0];
    }

    // Removes and returns the top player.
    PlayerStat removeMax() {
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

    // Displays all players in heap order.
    void display() const {
        if (isEmpty()) {
            cout << "No players available!" << endl;
            return;
        }

        cout << "\n--- Player Leaderboard ---" << endl;

        for (int i = 0; i < size; i++) {
            heap[i].displayDetails();
        }
    }

    int getSize() const {
        return size;
    }
};

#endif
