#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <iostream>
#include "BallEvent.h"
using namespace std;

// Stores previous ball states for undo operation.
class UndoStack {
private:
    static const int MAX_SIZE = 100;
    BallEvent events[MAX_SIZE];
    int top;

public:
    UndoStack() {
        top = -1;
    }

    // Checks whether the stack is empty.
    bool isEmpty() const {
        return top == -1;
    }

    // Checks whether the stack is full.
    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    // Saves a ball event in the stack.
    void push(BallEvent event) {
        if (isFull()) {
            cout << "Undo Stack is full!" << endl;
            return;
        }

        top++;
        events[top] = event;
    }

    // Removes and returns the last saved ball event.
    BallEvent pop() {
        if (isEmpty()) {
            cout << "Undo Stack is empty!" << endl;
            return BallEvent();
        }

        BallEvent event = events[top];
        top--;
        return event;
    }

    // Returns the top event without removing it.
    BallEvent peek() const {
        if (isEmpty()) {
            return BallEvent();
        }

        return events[top];
    }

    // Displays all saved events.
    void display() const {
        if (isEmpty()) {
            cout << "No previous events available." << endl;
            return;
        }

        cout << "\n--- Undo Stack Events ---" << endl;

        for (int i = top; i >= 0; i--) {
            events[i].displayDetails();
        }
    }

    // Returns the number of saved events.
    int size() const {
        return top + 1;
    }
};

#endif