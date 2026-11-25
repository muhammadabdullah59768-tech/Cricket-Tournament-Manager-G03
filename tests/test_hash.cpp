#include "PlayerHashTable.h"

int main() {
    PlayerHashTable table(7);
    cout << boolalpha;

    cout << "Insert Babar: " << table.insert(Player(1, "Babar Azam", "Batsman")) << endl;
    cout << "Insert Shaheen: " << table.insert(Player(2, "Shaheen Afridi", "Bowler")) << endl;
    cout << "Insert Rizwan: " << table.insert(Player(3, "Mohammad Rizwan", "Wicketkeeper")) << endl;
    cout << "Insert Shadab: " << table.insert(Player(4, "Shadab Khan", "All-rounder")) << endl;
    cout << "Insert Fakhar: " << table.insert(Player(5, "Fakhar Zaman", "Batsman")) << endl;
    cout << "Insert Naseem: " << table.insert(Player(6, "Naseem Shah", "Bowler")) << endl;
    cout << "Insert Haris: " << table.insert(Player(7, "Haris Rauf", "Bowler")) << endl;
    cout << "Insert Imad: " << table.insert(Player(8, "Imad Wasim", "All-rounder")) << endl;
    cout << "Insert duplicate ID 3: " << table.insert(Player(3, "Someone Else", "Batsman")) << endl;
    cout << "Insert same name, new ID 9: " << table.insert(Player(9, "Babar Azam", "Batsman")) << endl;

    cout << "\n--- Table (chaining) ---" << endl;
    table.display();
    cout << "Load factor: " << table.loadFactor() << endl;
    cout << "Longest chain: " << table.longestChain() << endl;

    cout << "\n--- Search (case does not matter) ---" << endl;
    Player* p = table.search("shaheen afridi");
    if (p != nullptr) p->displayDetails();
    p = table.search("MOHAMMAD RIZWAN");
    if (p != nullptr) p->displayDetails();
    cout << "Search 'Wasim Akram': " << (table.search("Wasim Akram") != nullptr) << endl;

    cout << "\n--- Search all with the same name ---" << endl;
    Player* results[5];
    int found = table.searchAll("Babar Azam", results, 5);
    cout << "Found " << found << " players named Babar Azam" << endl;
    for (int i = 0; i < found; i++) results[i]->displayDetails();

    cout << "\n--- Remove ---" << endl;
    cout << "Remove Shadab Khan: " << table.remove("Shadab Khan") << endl;
    cout << "Remove Shadab Khan again: " << table.remove("Shadab Khan") << endl;
    cout << "Search Shadab Khan: " << (table.search("Shadab Khan") != nullptr) << endl;
    cout << "Players left: " << table.size() << endl;
    table.display();
    return 0;
}
