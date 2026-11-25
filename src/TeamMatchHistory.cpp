#include "TeamMatchHistory.h"

TeamMatchHistory::TeamMatchHistory(int id) {
    teamID = id;
    head = nullptr;
    tail = nullptr;
    count = 0;
}

TeamMatchHistory::~TeamMatchHistory() {
    clear();
}

void TeamMatchHistory::clear() {
    MatchNode* current = head;
    while (current != nullptr) {
        MatchNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

bool TeamMatchHistory::addMatch(const Match& m) {
    if (m.getTeamAID() != teamID && m.getTeamBID() != teamID) return false;
    if (findMatch(m.getMatchID()) != nullptr) return false;

    MatchNode* node = new MatchNode(m);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    count++;
    return true;
}

bool TeamMatchHistory::removeMatch(int matchID) {
    MatchNode* prev = nullptr;
    MatchNode* current = head;

    while (current != nullptr && current->data.getMatchID() != matchID) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) return false;

    if (prev == nullptr) head = current->next;
    else prev->next = current->next;

    if (current == tail) tail = prev;

    delete current;
    count--;
    return true;
}

const Match* TeamMatchHistory::findMatch(int matchID) const {
    MatchNode* current = head;
    while (current != nullptr) {
        if (current->data.getMatchID() == matchID) return &current->data;
        current = current->next;
    }
    return nullptr;
}

int TeamMatchHistory::getWins() const {
    int total = 0;
    for (MatchNode* c = head; c != nullptr; c = c->next) {
        if (c->data.isCompleted() && c->data.getWinnerID() == teamID) total++;
    }
    return total;
}

int TeamMatchHistory::getLosses() const {
    int total = 0;
    for (MatchNode* c = head; c != nullptr; c = c->next) {
        int w = c->data.getWinnerID();
        if (c->data.isCompleted() && w != teamID && w != 0) total++;
    }
    return total;
}

int TeamMatchHistory::getTies() const {
    int total = 0;
    for (MatchNode* c = head; c != nullptr; c = c->next) {
        if (c->data.isCompleted() && c->data.getWinnerID() == 0) total++;
    }
    return total;
}

int TeamMatchHistory::getTotalRuns() const {
    int total = 0;
    for (MatchNode* c = head; c != nullptr; c = c->next) {
        if (!c->data.isCompleted()) continue;
        if (c->data.getTeamAID() == teamID) total += c->data.getRunsA();
        else total += c->data.getRunsB();
    }
    return total;
}

void TeamMatchHistory::display() const {
    cout << "Match history of Team " << teamID << " (" << count << " matches)" << endl;
    if (head == nullptr) {
        cout << "No matches yet." << endl;
        return;
    }
    for (MatchNode* c = head; c != nullptr; c = c->next) {
        c->data.displayScorecard();
    }
    cout << "W: " << getWins() << " | L: " << getLosses()
         << " | T: " << getTies() << " | Runs: " << getTotalRuns() << endl;
}
