#ifndef FIXTUREGENERATOR_H
#define FIXTUREGENERATOR_H

#include <iostream>
#include <string>
#include "TeamQueue.h"
#include "Fixture.h"
using namespace std;

class FixtureGenerator {
private:
    static const int BYE = 0;

    Fixture* fixtures;
    int count;
    int capacity;

    void addFixture(int a, int b);

public:
    FixtureGenerator();
    ~FixtureGenerator();

    FixtureGenerator(const FixtureGenerator& other) = delete;
    FixtureGenerator& operator=(const FixtureGenerator& other) = delete;

    int generate(const int* teamIDs, int teamCount);
    int getCount() const { return count; }
    const Fixture* getFixture(int index) const;
    int countForTeam(int teamID) const;
    void clear();
    void display() const;
};

#endif
