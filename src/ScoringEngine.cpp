
#include "../include/ScoringEngine.h"

// Updates match score.
void ScoringEngine::updateMatchScore() {
    if (teamAInnings) {
        match.setInningsA(totalRuns, totalWickets, ballsBowled);
    }
    else {
        match.setInningsB(totalRuns, totalWickets, ballsBowled);
    }
}

// Constructor.
ScoringEngine::ScoringEngine(Match& m, Player& p, bool teamA)
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

// Checks whether innings is over.
bool ScoringEngine::isInningsOver() const {
    return totalWickets >= Match::ALL_OUT ||
           ballsBowled >= Match::MAX_OVERS *
                          Match::BALLS_PER_OVER;
}

// Records runs and wickets.
void ScoringEngine::recordBall(int runs, int wickets) {

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

    // Save previous state.
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

    player.updateRuns(runs);
    player.updateWickets(wickets);

    updateMatchScore();

    cout << "Ball recorded successfully!" << endl;
}

// Undoes last ball.
void ScoringEngine::undoLastBall() {

    if (undoStack.isEmpty()) {
        cout << "No ball available to undo!" << endl;
        return;
    }

    BallEvent event = undoStack.pop();

    // Restore player statistics.
    player.updateRuns(-event.getRunsScored());
    player.updateWickets(-event.getWickets());

    // Restore previous match score.
    totalRuns = event.getTotalRuns();
    totalWickets = event.getTotalWickets();
    ballsBowled = event.getOvers();

    updateMatchScore();

    cout << "Last ball undone successfully!" << endl;
}

// Displays current score.
void ScoringEngine::displayScore() const {

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
void ScoringEngine::displayUndoHistory() const {
    undoStack.display();
}

// Finishes the match.
void ScoringEngine::finishMatch() {

    if (teamAInnings || !isInningsOver()) {
        cout << "Second innings is not completed!" << endl;
        return;
    }

    match.finishMatch();

    cout << "Match completed successfully!" << endl;
}
