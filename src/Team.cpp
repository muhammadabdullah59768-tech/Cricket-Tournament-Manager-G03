#include "Team.h"

Team::Team() {
    teamID = 0;
    teamName = "";
    squad = nullptr;
    playerCount = 0;
    capacity = 0;
}

Team::Team(int id, string name, int cap) {
    teamID = id;
    teamName = name;
    capacity = cap;
    playerCount = 0;
    squad = new Player[capacity];   // allocate memory
}

// Destructor: gives the memory back.
Team::~Team() {
    delete[] squad;
}

Player* Team::findPlayer(int id) {
    for (int i = 0; i < playerCount; i++) {
        if (squad[i].getID() == id) return &squad[i];
    }
    return nullptr;
}

bool Team::addPlayer(Player p) {
    if (playerCount >= capacity) return false;          // squad is full
    if (findPlayer(p.getID()) != nullptr) return false; // duplicate ID
    squad[playerCount] = p;
    playerCount++;
    return true;
}

void Team::displaySquad() const {
    cout << "Team " << teamID << ": " << teamName
         << " (" << playerCount << " players)" << endl;
    for (int i = 0; i < playerCount; i++)
        squad[i].displayDetails();
}