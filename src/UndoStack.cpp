
#include "../include/UndoStack.h"

// Constructor
UndoStack::UndoStack() {
    top = -1;
}

// Checks whether stack is empty.
bool UndoStack::isEmpty() const {
    return top == -1;
}

// Checks whether stack is full.
bool UndoStack::isFull() const {
    return top == MAX_SIZE - 1;
}

// Adds a ball event.
void UndoStack::push(BallEvent event) {
    if (isFull()) {
        cout << "Undo Stack is full!" << endl;
        return;
    }

    top++;
    events[top] = event;
}

// Removes and returns the last event.
BallEvent UndoStack::pop() {
    if (isEmpty()) {
        cout << "Undo Stack is empty!" << endl;
        return BallEvent();
    }

    BallEvent event = events[top];
    top--;

    return event;
}

// Returns top event without removing it.
BallEvent UndoStack::peek() const {
    if (isEmpty()) {
        return BallEvent();
    }

    return events[top];
}

// Displays all saved events.
void UndoStack::display() const {
    if (isEmpty()) {
        cout << "No previous events available." << endl;
        return;
    }

    cout << "\n--- Undo Stack Events ---" << endl;

    for (int i = top; i >= 0; i--) {
        events[i].displayDetails();
    }
}

// Returns number of events.
int UndoStack::size() const {
    return top + 1;
}
