#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

// Stores the data of one cricket player.
class Player {
private:
    int playerID;
    string name;
    string role;
    int runs;
    int wickets;

public:
    Player() : playerID(0), name(""), role(""), runs(0), wickets(0) {}

    Player(int id, string n, string r)
        : playerID(id), name(n), role(r), runs(0), wickets(0) {}

    int getID() const { return playerID; }
    string getName() const { return name; }
    string getRole() const { return role; }
    int getRuns() const { return runs; }
    int getWickets() const { return wickets; }

    void updateRuns(int r) { runs += r; }
    void updateWickets(int w) { wickets += w; }

    void displayDetails() const {
        cout << "ID: " << playerID << " | Name: " << name
             << " | Role: " << role << " | Runs: " << runs
             << " | Wickets: " << wickets << endl;
    }
};

#endif