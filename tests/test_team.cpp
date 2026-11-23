#include "Team.h"

int main() {
    Team t(1, "Lahore Qalandars", 3);
    cout << boolalpha;

    cout << "Add Fakhar: " << t.addPlayer(Player(10, "Fakhar Zaman", "Batsman")) << endl;
    cout << "Add duplicate ID 10: " << t.addPlayer(Player(10, "Fake", "Bowler")) << endl;
    cout << "Add Shaheen: " << t.addPlayer(Player(20, "Shaheen Afridi", "Bowler")) << endl;
    cout << "Add Haris: " << t.addPlayer(Player(30, "Haris Rauf", "Bowler")) << endl;
    cout << "Add 4th player (full): " << t.addPlayer(Player(40, "Extra", "Batsman")) << endl;

    cout << "\n--- Find ID 20 ---" << endl;
    Player* p = t.findPlayer(20);
    if (p != nullptr) p->displayDetails();

    cout << "\n--- Find ID 99 ---" << endl;
    if (t.findPlayer(99) == nullptr) cout << "Player not found" << endl;

    cout << "\n--- Squad ---" << endl;
    t.displaySquad();
    return 0;
}