#ifndef TEAMMATCHHISTORY_H
#define TEAMMATCHHISTORY_H

#include "Match.h"

class MatchNode {
public:
    Match data;
    MatchNode* next;

    MatchNode(const Match& m) : data(m), next(nullptr) {}
};

class TeamMatchHistory {
private:
    int teamID;
    MatchNode* head;
    MatchNode* tail;
    int count;

public:
    TeamMatchHistory(int id = 0);
    ~TeamMatchHistory();

    TeamMatchHistory(const TeamMatchHistory& other) = delete;
    TeamMatchHistory& operator=(const TeamMatchHistory& other) = delete;

    void setTeamID(int id) { teamID = id; }
    int getTeamID() const { return teamID; }
    int size() const { return count; }
    bool isEmpty() const { return head == nullptr; }

    bool addMatch(const Match& m);
    bool removeMatch(int matchID);
    const Match* findMatch(int matchID) const;

    int getWins() const;
    int getLosses() const;
    int getTies() const;
    int getTotalRuns() const;

    void clear();
    void display() const;
};

#endif
