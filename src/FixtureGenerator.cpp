#include "FixtureGenerator.h"

FixtureGenerator::FixtureGenerator() {
    fixtures = nullptr;
    count = 0;
    capacity = 0;
}

FixtureGenerator::~FixtureGenerator() {
    delete[] fixtures;
}

void FixtureGenerator::clear() {
    delete[] fixtures;
    fixtures = nullptr;
    count = 0;
    capacity = 0;
}

void FixtureGenerator::addFixture(int a, int b) {
    if (count >= capacity) return;
    int id = count + 1;
    fixtures[count] = Fixture(id, a, b, "Day " + to_string(id));
    count++;
}

int FixtureGenerator::generate(const int* teamIDs, int teamCount) {
    clear();
    if (teamIDs == nullptr || teamCount < 2) return 0;

    for (int i = 0; i < teamCount; i++) {
        if (teamIDs[i] == BYE) return 0;
        for (int j = i + 1; j < teamCount; j++) {
            if (teamIDs[i] == teamIDs[j]) return 0;
        }
    }

    capacity = teamCount * (teamCount - 1) / 2;
    fixtures = new Fixture[capacity];

    int n = teamCount;
    if (n % 2 != 0) n++;

    int fixedTeam = teamIDs[0];
    TeamQueue rotating(n - 1);
    for (int i = 1; i < teamCount; i++) rotating.enqueue(teamIDs[i]);
    if (n != teamCount) rotating.enqueue(BYE);

    int rounds = n - 1;
    int half = n / 2;

    for (int r = 0; r < rounds; r++) {
        int first;
        rotating.getAt(0, first);
        if (first != BYE) addFixture(fixedTeam, first);

        for (int i = 1; i < half; i++) {
            int a, b;
            rotating.getAt(i, a);
            rotating.getAt(n - 1 - i, b);
            if (a != BYE && b != BYE) addFixture(a, b);
        }
        rotating.rotate();
    }
    return count;
}

const Fixture* FixtureGenerator::getFixture(int index) const {
    if (index < 0 || index >= count) return nullptr;
    return &fixtures[index];
}

int FixtureGenerator::countForTeam(int teamID) const {
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (fixtures[i].involves(teamID)) total++;
    }
    return total;
}

void FixtureGenerator::display() const {
    if (count == 0) {
        cout << "No fixtures generated." << endl;
        return;
    }
    cout << "Total fixtures: " << count << endl;
    for (int i = 0; i < count; i++) fixtures[i].display();
}
