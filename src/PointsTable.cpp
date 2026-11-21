#include "PointsTable.h"

// Adds spaces on the right so table columns line up.
static string pad(string s, int width) {
    while ((int)s.length() < width) s += " ";
    return s;
}

PointsTable::PointsTable(int cap) {
    capacity = cap;
    rows = new TeamStanding[capacity];   // allocate memory
    count = 0;
}

// Destructor: gives the memory back.
PointsTable::~PointsTable() {
    delete[] rows;
}

int PointsTable::findIndex(int teamID) {
    for (int i = 0; i < count; i++) {
        if (rows[i].teamID == teamID) return i;
    }
    return -1;
}

bool PointsTable::addTeam(int teamID, string name) {
    if (count >= capacity) return false;          // table is full
    if (findIndex(teamID) != -1) return false;    // duplicate team ID
    rows[count].teamID = teamID;
    rows[count].name = name;
    count++;
    return true;
}

// NRR = (runs scored / overs faced) - (runs conceded / overs bowled)
// Overs = balls / 6. The 6.0 makes the division a decimal division.
void PointsTable::recalculateNRR(TeamStanding& t) {
    if (t.ballsFaced == 0 || t.ballsBowled == 0) {
        t.nrr = 0.0;   // avoid dividing by zero
        return;
    }
    double oversFaced = t.ballsFaced / 6.0;
    double oversBowled = t.ballsBowled / 6.0;
    t.nrr = (t.runsScored / oversFaced) - (t.runsConceded / oversBowled);
}

bool PointsTable::recordMatch(const Match& m) {
    if (!m.isCompleted()) return false;

    int a = findIndex(m.getTeamAID());
    int b = findIndex(m.getTeamBID());
    if (a == -1 || b == -1) return false;

    // Team A: batted in innings A, bowled in innings B.
    // ballsForNRR already treats an all-out innings as the full 20 overs.
    rows[a].played++;
    rows[a].runsScored += m.getRunsA();
    rows[a].ballsFaced += m.ballsForNRR_A();
    rows[a].runsConceded += m.getRunsB();
    rows[a].ballsBowled += m.ballsForNRR_B();

    // Team B: the opposite.
    rows[b].played++;
    rows[b].runsScored += m.getRunsB();
    rows[b].ballsFaced += m.ballsForNRR_B();
    rows[b].runsConceded += m.getRunsA();
    rows[b].ballsBowled += m.ballsForNRR_A();

    int winner = m.getWinnerID();
    if (winner == 0) {                        // tie
        rows[a].tied++;
        rows[b].tied++;
        rows[a].points += TIE_POINTS;
        rows[b].points += TIE_POINTS;
    } else if (winner == rows[a].teamID) {    // team A won
        rows[a].won++;
        rows[b].lost++;
        rows[a].points += WIN_POINTS;
    } else {                                  // team B won
        rows[b].won++;
        rows[a].lost++;
        rows[b].points += WIN_POINTS;
    }

    recalculateNRR(rows[a]);
    recalculateNRR(rows[b]);
    return true;
}

// "a is better than b" = more points, or equal points and higher NRR.
bool PointsTable::isBetter(const TeamStanding& a, const TeamStanding& b) {
    if (a.points != b.points) return a.points > b.points;
    return a.nrr > b.nrr;
}

void PointsTable::swapRows(int i, int j) {
    TeamStanding temp = rows[i];
    rows[i] = rows[j];
    rows[j] = temp;
}

// Quicksort step: the last row is the pivot. Every row better than the
// pivot is moved to the left side. Then the pivot goes in its final place.
int PointsTable::partition(int low, int high) {
    TeamStanding pivot = rows[high];
    int i = low - 1;   // end of the "better than pivot" part
    for (int j = low; j < high; j++) {
        if (isBetter(rows[j], pivot)) {
            i++;
            swapRows(i, j);
        }
    }
    swapRows(i + 1, high);
    return i + 1;
}

void PointsTable::quickSort(int low, int high) {
    if (low >= high) return;
    int p = partition(low, high);
    quickSort(low, p - 1);
    quickSort(p + 1, high);
}

void PointsTable::sortTable() {
    quickSort(0, count - 1);
}

const TeamStanding* PointsTable::getRow(int index) const {
    if (index < 0 || index >= count) return nullptr;
    return &rows[index];
}

void PointsTable::display() {
    cout << pad("Pos", 5) << pad("Team", 20) << pad("P", 4) << pad("W", 4)
         << pad("L", 4) << pad("T", 4) << pad("Pts", 5)
         << pad("Runs", 7) << pad("Ov.Faced", 10)
         << pad("Conc.", 7) << pad("Ov.Bowled", 11) << "NRR" << endl;

    cout.setf(ios::fixed);
    cout.precision(3);   // NRR with 3 decimals

    for (int i = 0; i < count; i++) {
        TeamStanding& t = rows[i];
        string oversF = to_string(t.ballsFaced / 6) + "." + to_string(t.ballsFaced % 6);
        string oversB = to_string(t.ballsBowled / 6) + "." + to_string(t.ballsBowled % 6);

        cout << pad(to_string(i + 1), 5) << pad(t.name, 20)
             << pad(to_string(t.played), 4) << pad(to_string(t.won), 4)
             << pad(to_string(t.lost), 4) << pad(to_string(t.tied), 4)
             << pad(to_string(t.points), 5)
             << pad(to_string(t.runsScored), 7) << pad(oversF, 10)
             << pad(to_string(t.runsConceded), 7) << pad(oversB, 11);
        cout << t.nrr << endl;
    }
}