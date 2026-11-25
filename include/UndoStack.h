
#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <iostream>
#include "BallEvent.h"
using namespace std;

class UndoStack {
private:
    static const int MAX_SIZE = 100;
    BallEvent events[MAX_SIZE];
    int top;

public:
    UndoStack();

    bool isEmpty() const;
    bool isFull() const;

    void push(BallEvent event);
    BallEvent pop();
    BallEvent peek() const;

    void display() const;
    int size() const;
};

#endif
