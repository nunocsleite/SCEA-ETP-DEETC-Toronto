#ifndef TESTSETDESCRIPTION_H
#define TESTSETDESCRIPTION_H

#include <string>

using namespace std;


/// TODO: REFACTORING
/// - Remove numPeriods fiels and ctor #1. For Toronto, also use TimetableProblemData
///


class TestSetDescription {
    string name;
    string description;
    int numPeriods;  /// USED IN TORONTO BENCHMARKS
public:
    TestSetDescription(string name, string description, int numPeriods) :   /// USED IN TORONTO BENCHMARKS
        name(name), description(description), numPeriods(numPeriods) { }

    TestSetDescription(string _name, string _description) :
        name(_name), description(_description) { }

    string getName() const { return name; }
    string getDescription() const { return description; }

    int getPeriods() const { return numPeriods; }      /// USED IN TORONTO BENCHMARKS

    friend ostream& operator<<(ostream& os, const TestSetDescription& t);
};


#endif // TESTSETDESCRIPTION_H
