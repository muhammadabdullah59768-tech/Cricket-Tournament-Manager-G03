#include "TeamMatchHistory.h"

int main() {
    TeamMatchHistory h(1);
    cout << boolalpha;

    Match m1(1, 1, 2);
    m1.setInningsA(180, 6, 120);
    m1.setInningsB(150, 10, 117);
    m1.finishMatch();

    Match m2(2, 3, 1);
    m2.setInningsA(170, 5, 120);
    m2.setInningsB(160, 9, 120);
    m2.finishMatch();

    Match m3(3, 1, 4);
    m3.setInningsA(140, 8, 120);
    m3.setInningsB(140, 7, 120);
    m3.finishMatch();

    Match other(4, 2, 3);
    other.setInningsA(100, 10, 90);
    other.setInningsB(101, 2, 60);
    other.finishMatch();

    cout << "Add match 1: " << h.addMatch(m1) << endl;
    cout << "Add match 2: " << h.addMatch(m2) << endl;
    cout << "Add match 3: " << h.addMatch(m3) << endl;
    cout << "Add match 1 again (duplicate): " << h.addMatch(m1) << endl;
    cout << "Add match 4 (Team 1 not playing): " << h.addMatch(other) << endl;

    cout << "\n--- History ---" << endl;
    h.display();

    cout << "\n--- Find match 2 ---" << endl;
    const Match* f = h.findMatch(2);
    if (f != nullptr) f->displayScorecard();
    cout << "Find match 99: " << (h.findMatch(99) != nullptr) << endl;

    cout << "\n--- Remove middle (2), head (1), missing (99) ---" << endl;
    cout << "Remove 2: " << h.removeMatch(2) << endl;
    cout << "Remove 1: " << h.removeMatch(1) << endl;
    cout << "Remove 99: " << h.removeMatch(99) << endl;
    h.display();

    cout << "\n--- Remove last, then add again (tail check) ---" << endl;
    cout << "Remove 3: " << h.removeMatch(3) << endl;
    cout << "Empty: " << h.isEmpty() << endl;
    cout << "Add match 1: " << h.addMatch(m1) << endl;
    h.display();
    return 0;
}
