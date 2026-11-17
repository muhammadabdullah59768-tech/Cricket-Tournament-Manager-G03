#ifndef TEAMQUEUE_H
#define TEAMQUEUE_H

class TeamQueue {
private:
    int* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    explicit TeamQueue(int cap = 10);
    ~TeamQueue();

    TeamQueue(const TeamQueue&) = delete;
    TeamQueue& operator=(const TeamQueue&) = delete;

    bool enqueue(int teamID);
    bool dequeue(int& teamID);
    bool peek(int& teamID) const;
    bool getAt(int pos, int& teamID) const;
    bool rotate();

    bool isEmpty() const;
    bool isFull() const;
    int  size() const;
    int  getCapacity() const;
    void clear();
    void display() const;
};

#endif
