#include "PointsTable.h"

int main() {
    PointsTable table(4);
    cout << boolalpha;

    table.addTeam(1, "Lahore Qalandars");
    table.addTeam(2, "Karachi Kings");
    table.addTeam(3, "Islamabad United");
    table.addTeam(4, "Peshawar Zalmi");
    cout << "Add duplicate team 1: " << table.addTeam(1, "Fake") << endl;
    cout << "Add 5th team (full): " << table.addTeam(5, "Extra") << endl;

    // Match 1: Team 1 wins. Team 2 is all out (counts as 20 overs for NRR).
    Match m1(1, 1, 2);
    m1.setInningsA(180, 6, 120);
    m1.setInningsB(150, 10, 117);
    m1.finishMatch();

    // Match 2: Team 4 chases the target in 18.0 overs.
    Match m2(2, 3, 4);
    m2.setInningsA(160, 5, 120);
    m2.setInningsB(161, 4, 108);
    m2.finishMatch();

    // Match 3: a tie, so both teams get 1 point.
    Match m3(3, 1, 3);
    m3.setInningsA(170, 8, 120);
    m3.setInningsB(170, 7, 120);
    m3.finishMatch();

    // Match 4: Team 4 wins again (17.1 overs).
    Match m4(4, 2, 4);
    m4.setInningsA(140, 10, 100);
    m4.setInningsB(141, 3, 103);
    m4.finishMatch();

    Match notPlayed(5, 1, 4);   // never finished

    cout << "Record match 1: " << table.recordMatch(m1) << endl;
    cout << "Record match 2: " << table.recordMatch(m2) << endl;
    cout << "Record match 3: " << table.recordMatch(m3) << endl;
    cout << "Record match 4: " << table.recordMatch(m4) << endl;
    cout << "Record unfinished match: " << table.recordMatch(notPlayed) << endl;

    cout << "\n--- Before sorting (order added) ---" << endl;
    table.display();

    table.sortTable();
    cout << "\n--- After quicksort (points, then NRR) ---" << endl;
    table.display();
    return 0;
}