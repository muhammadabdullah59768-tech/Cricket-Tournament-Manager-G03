#include "AVLPlayerTree.h"

int main() {
    AVLPlayerTree tree;

    tree.insert(Player(10, "Babar Azam", "Batsman"));
    tree.insert(Player(20, "Shaheen Afridi", "Bowler"));
    tree.insert(Player(30, "Mohammad Rizwan", "Wicketkeeper"));
    tree.insert(Player(40, "Shadab Khan", "All-rounder"));
    tree.insert(Player(50, "Fakhar Zaman", "Batsman"));
    tree.insert(Player(25, "Haris Rauf", "Bowler"));

    cout << "--- Players in sorted ID order ---" << endl;
    tree.displayInOrder();
    cout << "\nTree height: " << tree.getTreeHeight() << endl;

    cout << "\n--- Search ID 30 ---" << endl;
    Player* p = tree.searchByID(30);
    if (p != nullptr) p->displayDetails();
    else cout << "Player not found" << endl;

    cout << "\n--- Search ID 99 ---" << endl;
    p = tree.searchByID(99);
    if (p != nullptr) p->displayDetails();
    else cout << "Player not found" << endl;

    cout << "\n--- Duplicate ID test ---" << endl;
    if (!tree.insert(Player(30, "Fake Player", "Batsman")))
        cout << "Duplicate ID rejected" << endl;

    // 1000 sorted IDs would make a normal BST 1000 levels tall.
    AVLPlayerTree big;
    for (int i = 1; i <= 1000; i++)
        big.insert(Player(i, "Player", "Batsman"));
    cout << "\nHeight after 1000 sorted inserts: " << big.getTreeHeight() << endl;

    return 0;
}