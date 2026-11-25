#ifndef FIXTURE_H
#define FIXTURE_H

#include <iostream>
#include <string>
using namespace std;

class Fixture {
private:
    int fixtureID;
    int teamAID;
    int teamBID;
    string date;

public:
    Fixture() : fixtureID(0), teamAID(0), teamBID(0), date("") {}

    Fixture(int id, int a, int b, string d)
        : fixtureID(id), teamAID(a), teamBID(b), date(d) {}

    int getFixtureID() const { return fixtureID; }
    int getTeamAID() const { return teamAID; }
    int getTeamBID() const { return teamBID; }
    string getDate() const { return date; }

    void setDate(string d) { date = d; }

    bool involves(int teamID) const {
        return teamAID == teamID || teamBID == teamID;
    }

    void display() const {
        cout << "Fixture " << fixtureID << ": Team " << teamAID
             << " vs Team " << teamBID << " | " << date << endl;
    }
};

#endif
