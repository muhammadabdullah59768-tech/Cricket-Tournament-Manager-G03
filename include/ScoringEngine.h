
#ifndef SCORINGENGINE_H
#define SCORINGENGINE_H

#include <iostream>
#include "UndoStack.h"
#include "Player.h"
#include "Match.h"
using namespace std;

class ScoringEngine {
private:
    Match& match;
    Player& player;
    UndoStack undoStack;

    bool teamAInnings;

    int totalRuns;
    int totalWickets;
    int ballsBowled;

    void updateMatchScore();

public:
    ScoringEngine(Match& m, Player& p, bool teamA = true);

    bool isInningsOver() const;

    void recordBall(int runs, int wickets = 0);

    void undoLastBall();

    void displayScore() const;

    void displayUndoHistory() const;

    void finishMatch();
};

#endif
