#ifndef MATCH_H
#define MATCH_H

#include <iostream>
#include <string>
using namespace std;

// Stores the result of one match.
// We store BALLS (not decimal overs) because 19.3 overs means
// 19 overs and 3 balls = 117 balls, not 19.3 as a number.
class Match {
public:
    static constexpr int MAX_OVERS = 20;
    static constexpr int BALLS_PER_OVER = 6;
    static constexpr int ALL_OUT = 10;   // wickets that end an innings

private:
    int matchID;
    int teamAID, teamBID;
    int runsA, wicketsA, ballsA;   // Team A innings
    int runsB, wicketsB, ballsB;   // Team B innings
    int winnerID;                  // team ID, 0 = tie, -1 = not played yet
    bool completed;

public:
    Match() {
        matchID = 0; teamAID = 0; teamBID = 0;
        runsA = 0; wicketsA = 0; ballsA = 0;
        runsB = 0; wicketsB = 0; ballsB = 0;
        winnerID = -1;
        completed = false;
    }

    Match(int id, int a, int b) {
        matchID = id; teamAID = a; teamBID = b;
        runsA = 0; wicketsA = 0; ballsA = 0;
        runsB = 0; wicketsB = 0; ballsB = 0;
        winnerID = -1;
        completed = false;
    }

    int getMatchID() const { return matchID; }
    int getTeamAID() const { return teamAID; }
    int getTeamBID() const { return teamBID; }
    int getRunsA() const { return runsA; }
    int getRunsB() const { return runsB; }
    int getWicketsA() const { return wicketsA; }
    int getWicketsB() const { return wicketsB; }
    int getBallsA() const { return ballsA; }
    int getBallsB() const { return ballsB; }
    int getWinnerID() const { return winnerID; }
    bool isCompleted() const { return completed; }

    void setInningsA(int runs, int wickets, int balls) {
        runsA = runs; wicketsA = wickets; ballsA = balls;
    }

    void setInningsB(int runs, int wickets, int balls) {
        runsB = runs; wicketsB = wickets; ballsB = balls;
    }

    // Decides the winner and marks the match as completed.
    void finishMatch() {
        if (runsA > runsB) winnerID = teamAID;
        else if (runsB > runsA) winnerID = teamBID;
        else winnerID = 0;   // tie
        completed = true;
    }

    // For NRR, an all-out innings counts as the full quota of overs.
    int ballsForNRR_A() const {
        if (wicketsA >= ALL_OUT) return MAX_OVERS * BALLS_PER_OVER;
        return ballsA;
    }

    int ballsForNRR_B() const {
        if (wicketsB >= ALL_OUT) return MAX_OVERS * BALLS_PER_OVER;
        return ballsB;
    }

    // 117 balls -> "19.3"
    string oversText(int balls) const {
        return to_string(balls / BALLS_PER_OVER) + "." +
               to_string(balls % BALLS_PER_OVER);
    }

    void displayScorecard() const {
        cout << "Match " << matchID << ": Team " << teamAID;
        if (!completed) {
            cout << " vs Team " << teamBID << " | Not played yet" << endl;
            return;
        }
        cout << " " << runsA << "/" << wicketsA << " (" << oversText(ballsA) << " ov)"
             << " vs Team " << teamBID << " " << runsB << "/" << wicketsB
             << " (" << oversText(ballsB) << " ov) | Winner: ";
        if (winnerID == 0) cout << "Tie" << endl;
        else cout << "Team " << winnerID << endl;
    }
};

#endif