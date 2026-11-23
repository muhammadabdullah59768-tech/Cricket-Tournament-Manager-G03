#ifndef TEAM_H
#define TEAM_H

#include "Player.h"

// A team with a squad stored in a dynamic array.
class Team {
private:
    int teamID;
    string teamName;
    Player* squad;     // dynamic array of players
    int playerCount;   // players added so far
    int capacity;      // maximum players

public:
    Team();
    Team(int id, string name, int cap = 20);
    ~Team();

    // Copying would make two teams share one array (dangerous), so we forbid it.
    Team(const Team& other) = delete;
    Team& operator=(const Team& other) = delete;

    int getID() const { return teamID; }
    string getName() const { return teamName; }
    int getPlayerCount() const { return playerCount; }

    bool addPlayer(Player p);     // false if full or the ID already exists
    Player* findPlayer(int id);   // nullptr if not found
    void displaySquad() const;
};

#endif