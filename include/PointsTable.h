#ifndef POINTSTABLE_H
#define POINTSTABLE_H

#include <iostream>
#include <string>
#include "Match.h"
using namespace std;

// One row of the points table (one team).
// Overs are stored as BALLS, because 19.3 overs = 117 balls (not 19.3).
class TeamStanding {
public:
    int teamID;
    string name;
    int played, won, lost, tied;
    int points;
    int runsScored, ballsFaced;       // our batting
    int runsConceded, ballsBowled;    // our bowling
    double nrr;                       // Net Run Rate

    TeamStanding() {
        teamID = 0; name = "";
        played = 0; won = 0; lost = 0; tied = 0;
        points = 0;
        runsScored = 0; ballsFaced = 0;
        runsConceded = 0; ballsBowled = 0;
        nrr = 0.0;
    }
};

class PointsTable {
private:
    static const int WIN_POINTS = 2;
    static const int TIE_POINTS = 1;

    TeamStanding* rows;   // dynamic array
    int count;            // teams added so far
    int capacity;         // maximum teams

    int findIndex(int teamID);
    void recalculateNRR(TeamStanding& t);
    bool isBetter(const TeamStanding& a, const TeamStanding& b);
    void swapRows(int i, int j);
    int partition(int low, int high);
    void quickSort(int low, int high);

public:
    PointsTable(int cap);
    ~PointsTable();

    // Copying would make two tables share one array, so we forbid it.
    PointsTable(const PointsTable& other) = delete;
    PointsTable& operator=(const PointsTable& other) = delete;

    bool addTeam(int teamID, string name);   // false if full or duplicate
    bool recordMatch(const Match& m);        // false if not finished or unknown team
    void sortTable();                        // our own quicksort
    void display();
    int getCount() const { return count; }
    const TeamStanding* getRow(int index) const;   // nullptr if out of range
};

#endif