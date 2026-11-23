
#ifndef SCORINGENGINE_H
#define SCORINGENGINE_H

#include <iostream>
#include "UndoStack.h"
#include "Player.h"
#include "Match.h"
using namespace std;

// Handles ball-by-ball scoring and undo operation.
class ScoringEngine {
private:
    Match& match;
    Player& player;
    UndoStack undoStack;

    bool teamAInnings;

    int totalRuns;
    int totalWickets;
    int ballsBowled;

    // Updates the match score.
    void updateMatchScore() {
        if (teamAInnings) {
            match.setInningsA(totalRuns, totalWickets, ballsBowled);
        }
        else {
            match.setInningsB(totalRuns, totalWickets, ballsBowled);
        }
    }

public:
    // Constructor.
    ScoringEngine(Match& m, Player& p, bool teamA = true)
        : match(m), player(p), teamAInnings(teamA) {

        if (teamAInnings) {
            totalRuns = match.getRunsA();
            totalWickets = match.getWicketsA();
            ballsBowled = match.getBallsA();
        }
        else {
            totalRuns = match.getRunsB();
            totalWickets = match.getWicketsB();
            ballsBowled = match.getBallsB();
        }
    }

    // Checks whether the innings is over.
    bool isInningsOver() const {
        return totalWickets >= Match::ALL_OUT ||
               ballsBowled >= Match::MAX_OVERS *
                              Match::BALLS_PER_OVER;
    }

    // Records runs and wickets after each ball.
    void recordBall(int runs, int wickets = 0) {

        if (isInningsOver()) {
            cout << "Innings is over!" << endl;
            return;
        }

        if (runs < 0 || runs > 6 ||
            wickets < 0 || wickets > 1) {
            cout << "Invalid ball data!" << endl;
            return;
        }

        if (totalWickets + wickets > Match::ALL_OUT) {
            cout << "Invalid wicket count!" << endl;
            return;
        }

        if (undoStack.isFull()) {
            cout << "Undo Stack is full!" << endl;
            return;
        }

        // Save previous state before updating the score.
        BallEvent event(
            ballsBowled + 1,
            runs,
            wickets,
            totalRuns,
            totalWickets,
            ballsBowled
        );

        undoStack.push(event);

        // Update score.
        totalRuns += runs;
        totalWickets += wickets;
        ballsBowled++;

        // Update player statistics.
        player.updateRuns(runs);
        player.updateWickets(wickets);

        updateMatchScore();

        cout << "Ball recorded successfully!" << endl;
    }

    // Undoes the last ball.
    void undoLastBall() {

        if (undoStack.isEmpty()) {
            cout << "No ball available to undo!" << endl;
            return;
        }

        BallEvent event = undoStack.pop();

        // Reverse player statistics.
        player.updateRuns(-event.getRunsScored());
        player.updateWickets(-event.getWickets());

        // Restore previous match state.
        totalRuns = event.getTotalRuns();
        totalWickets = event.getTotalWickets();

        // The overs field stores previous balls bowled.
        ballsBowled = event.getOvers();

        updateMatchScore();

        cout << "Last ball undone successfully!" << endl;
    }

    // Displays current score.
    void displayScore() const {

        cout << "\n--- Current Score ---" << endl;
        cout << "Runs: " << totalRuns << endl;
        cout << "Wickets: " << totalWickets << endl;

        cout << "Overs: "
             << ballsBowled / Match::BALLS_PER_OVER
             << "."
             << ballsBowled % Match::BALLS_PER_OVER
             << endl;
    }

    // Displays undo history.
    void displayUndoHistory() const {
        undoStack.display();
    }

    // Finishes the match after the second innings.
    void finishMatch() {

        if (teamAInnings || !isInningsOver()) {
            cout << "Second innings is not completed!" << endl;
            return;
        }

        match.finishMatch();
        cout << "Match completed successfully!" << endl;
    }
};

#endif
