#include "FixtureGenerator.h"

bool checkAllPairs(const FixtureGenerator& g, const int* ids, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int times = 0;
            for (int k = 0; k < g.getCount(); k++) {
                const Fixture* f = g.getFixture(k);
                if (f->involves(ids[i]) && f->involves(ids[j])) times++;
            }
            if (times != 1) return false;
        }
    }
    return true;
}

int main() {
    FixtureGenerator g;
    cout << boolalpha;

    cout << "--- 4 teams ---" << endl;
    int four[] = {1, 2, 3, 4};
    int made = g.generate(four, 4);
    g.display();
    cout << "Expected 6, got " << made << ": " << (made == 6) << endl;
    cout << "Every pair plays exactly once: " << checkAllPairs(g, four, 4) << endl;
    for (int i = 0; i < 4; i++)
        cout << "Team " << four[i] << " plays " << g.countForTeam(four[i]) << " matches" << endl;

    cout << "\n--- 5 teams (odd, one team rests each round) ---" << endl;
    int five[] = {10, 20, 30, 40, 50};
    made = g.generate(five, 5);
    g.display();
    cout << "Expected 10, got " << made << ": " << (made == 10) << endl;
    cout << "Every pair plays exactly once: " << checkAllPairs(g, five, 5) << endl;

    cout << "\n--- 8 teams ---" << endl;
    int eight[] = {1, 2, 3, 4, 5, 6, 7, 8};
    made = g.generate(eight, 8);
    cout << "Expected 28, got " << made << ": " << (made == 28) << endl;
    cout << "Every pair plays exactly once: " << checkAllPairs(g, eight, 8) << endl;

    cout << "\n--- Invalid input ---" << endl;
    int one[] = {1};
    int dup[] = {1, 2, 2};
    cout << "1 team gives: " << g.generate(one, 1) << endl;
    cout << "Duplicate IDs give: " << g.generate(dup, 3) << endl;
    return 0;
}
