
#ifndef PLAYERMAXHEAP_H
#define PLAYERMAXHEAP_H

#include <iostream>
#include "PlayerStat.h"
using namespace std;

class PlayerMaxHeap {
private:
    static const int MAX_SIZE = 100;
    PlayerStat heap[MAX_SIZE];
    int size;

    bool isGreater(PlayerStat a, PlayerStat b) const;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PlayerMaxHeap();

    bool isEmpty() const;
    bool isFull() const;

    void insert(PlayerStat player);

    PlayerStat peek() const;

    PlayerStat extractMax();

    // Compatibility with the earlier header.
    PlayerStat removeMax();

    void display() const;

    int getSize() const;
};

#endif
