#ifndef PLAYERHASHTABLE_H
#define PLAYERHASHTABLE_H

#include "Player.h"

class HashNode {
public:
    Player data;
    HashNode* next;

    HashNode(const Player& p) : data(p), next(nullptr) {}
};

class PlayerHashTable {
private:
    HashNode** table;
    int tableSize;
    int count;

    string toLower(const string& s) const;
    int hashFunction(const string& name) const;
    bool containsID(int playerID) const;

public:
    PlayerHashTable(int size = 101);
    ~PlayerHashTable();

    PlayerHashTable(const PlayerHashTable& other) = delete;
    PlayerHashTable& operator=(const PlayerHashTable& other) = delete;

    bool insert(const Player& p);
    Player* search(const string& name);
    int searchAll(const string& name, Player** results, int maxResults);
    bool remove(const string& name);

    int size() const { return count; }
    int getTableSize() const { return tableSize; }
    double loadFactor() const;
    int longestChain() const;
    void display() const;
};

#endif
