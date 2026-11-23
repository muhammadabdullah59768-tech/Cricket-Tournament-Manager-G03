#include "Match.h"

int main() {
    Match m(1, 1, 2);
    m.setInningsA(180, 6, 120);    // 20.0 overs
    m.setInningsB(150, 10, 117);   // all out in 19.3 overs
    m.finishMatch();
    m.displayScorecard();
    cout << "Balls for NRR, Team A: " << m.ballsForNRR_A() << endl;
    cout << "Balls for NRR, Team B: " << m.ballsForNRR_B() << endl;
    cout << "Overs text for 117 balls: " << m.oversText(117) << endl;

    Match t(2, 3, 4);
    t.setInningsA(150, 8, 120);
    t.setInningsB(150, 7, 120);
    t.finishMatch();
    t.displayScorecard();

    Match n(3, 1, 3);
    n.displayScorecard();
    return 0;
}