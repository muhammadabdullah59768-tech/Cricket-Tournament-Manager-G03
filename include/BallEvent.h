#ifndef BALLEVENT_H
#define BALLEVENT_H

#include <iostream>
using namespace std;

// Stores the state saved before each ball.
class BallEvent {
private:
    int ballNumber;
    int runsScored;
    int wickets;
    int totalRuns;
    int totalWickets;
    int overs;

public:
    BallEvent()
        : ballNumber(0), runsScored(0), wickets(0),
          totalRuns(0), totalWickets(0), overs(0) {}

    BallEvent(int ball, int runs, int w,
              int totalR, int totalW, int over)
        : ballNumber(ball), runsScored(runs), wickets(w),
          totalRuns(totalR), totalWickets(totalW), overs(over) {}

    int getBallNumber() const { return ballNumber; }
    int getRunsScored() const { return runsScored; }
    int getWickets() const { return wickets; }
    int getTotalRuns() const { return totalRuns; }
    int getTotalWickets() const { return totalWickets; }
    int getOvers() const { return overs; }

    void displayDetails() const {
        cout << "Ball Number: " << ballNumber
             << " | Runs Scored: " << runsScored
             << " | Wickets: " << wickets
             << " | Total Runs: " << totalRuns
             << " | Total Wickets: " << totalWickets
             << " | Overs: " << overs << endl;
    }
};

#endif