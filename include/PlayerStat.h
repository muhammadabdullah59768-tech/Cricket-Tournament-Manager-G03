
#ifndef PLAYERSTAT_H
#define PLAYERSTAT_H

#include <iostream>
#include <string>
using namespace std;

// Stores player information for the leaderboard.
class PlayerStat {
private:
    int playerID;
    string name;
    int runs;
    int wickets;

public:
    PlayerStat()
        : playerID(0), name(""), runs(0), wickets(0) {}

    PlayerStat(int id, string n, int r, int w)
        : playerID(id), name(n), runs(r), wickets(w) {}

    int getID() const {
        return playerID;
    }

    string getName() const {
        return name;
    }

    int getRuns() const {
        return runs;
    }

    int getWickets() const {
        return wickets;
    }

    void displayDetails() const {
        cout << "ID: " << playerID
             << " | Name: " << name
             << " | Runs: " << runs
             << " | Wickets: " << wickets << endl;
    }
};

#endif
