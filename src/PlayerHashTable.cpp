#include "PlayerHashTable.h"

PlayerHashTable::PlayerHashTable(int size) {
    if (size < 1) size = 1;
    tableSize = size;
    count = 0;
    table = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; i++) table[i] = nullptr;
}

PlayerHashTable::~PlayerHashTable() {
    for (int i = 0; i < tableSize; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    delete[] table;
}

string PlayerHashTable::toLower(const string& s) const {
    string result = s;
    for (int i = 0; i < (int)result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') result[i] = result[i] - 'A' + 'a';
    }
    return result;
}

int PlayerHashTable::hashFunction(const string& name) const {
    string key = toLower(name);
    unsigned long long hash = 0;
    for (int i = 0; i < (int)key.length(); i++) {
        hash = (hash * 31 + (unsigned char)key[i]) % tableSize;
    }
    return (int)hash;
}

bool PlayerHashTable::containsID(int playerID) const {
    for (int i = 0; i < tableSize; i++) {
        for (HashNode* c = table[i]; c != nullptr; c = c->next) {
            if (c->data.getID() == playerID) return true;
        }
    }
    return false;
}

bool PlayerHashTable::insert(const Player& p) {
    if (containsID(p.getID())) return false;

    int index = hashFunction(p.getName());
    HashNode* node = new HashNode(p);
    node->next = table[index];
    table[index] = node;
    count++;
    return true;
}

Player* PlayerHashTable::search(const string& name) {
    int index = hashFunction(name);
    string key = toLower(name);
    for (HashNode* c = table[index]; c != nullptr; c = c->next) {
        if (toLower(c->data.getName()) == key) return &c->data;
    }
    return nullptr;
}

int PlayerHashTable::searchAll(const string& name, Player** results, int maxResults) {
    int found = 0;
    int index = hashFunction(name);
    string key = toLower(name);
    for (HashNode* c = table[index]; c != nullptr && found < maxResults; c = c->next) {
        if (toLower(c->data.getName()) == key) {
            results[found] = &c->data;
            found++;
        }
    }
    return found;
}

bool PlayerHashTable::remove(const string& name) {
    int index = hashFunction(name);
    string key = toLower(name);
    HashNode* prev = nullptr;
    HashNode* current = table[index];

    while (current != nullptr) {
        if (toLower(current->data.getName()) == key) {
            if (prev == nullptr) table[index] = current->next;
            else prev->next = current->next;
            delete current;
            count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

double PlayerHashTable::loadFactor() const {
    return (double)count / tableSize;
}

int PlayerHashTable::longestChain() const {
    int longest = 0;
    for (int i = 0; i < tableSize; i++) {
        int length = 0;
        for (HashNode* c = table[i]; c != nullptr; c = c->next) length++;
        if (length > longest) longest = length;
    }
    return longest;
}

void PlayerHashTable::display() const {
    cout << "Hash table: " << count << " players, " << tableSize << " buckets" << endl;
    for (int i = 0; i < tableSize; i++) {
        if (table[i] == nullptr) continue;
        cout << "[" << i << "] ";
        for (HashNode* c = table[i]; c != nullptr; c = c->next) {
            cout << c->data.getName() << " (" << c->data.getID() << ")";
            if (c->next != nullptr) cout << " -> ";
        }
        cout << endl;
    }
}
