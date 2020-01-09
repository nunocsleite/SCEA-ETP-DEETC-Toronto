#ifndef ETTPKEMPECHAINHEURISTICTWOEPOCH_H
#define ETTPKEMPECHAINHEURISTICTWOEPOCH_H


#include "eoFunctor.h"
#include "base/chromosome/eoChromosome.h"

#include "base/kempeChain/ETTPKempeChainHeuristic.h"
#include <boost/unordered_set.hpp>
#include <utils/eoRNG.h>


using namespace std;
using namespace boost;


//////////////////////////////////////////////////////////
//
// (rf. Demeester paper)
// Concerning the uncapacitated Toronto examination time-
// tabling problem, we apply the Kempe chain based heuris-
// tics. These low-level heuristics perturb feasible solutions
// to the uncapacitated examination timetabling problem,
// without making them infeasible. Suppose a partial solu-
// tion that corresponds to the left hand side of Fig. 1. If
// we want to move exam e1 to time slot tj, the solution
// becomes infeasible, since exam e1 has students in com-
// mon with exams e6, e7, and e8 that are assigned to time
// slot tj. To overcome this, exams e6, e7, and e8 should be
// moved to time slot ti. This process is repeated until all the
// exams that have students in common are assigned to dif-
// ferent time slots. The result is depicted at the right hand
// side of Fig. 1. The Kempe Chain heuristic Uncap1 can be
// seen as moving an exam to another time slot whilst main-
// taining feasibility by repairing any infeasibilities that may
// have been introduced.
//
template <typename EOT>
class ETTPKempeChainHeuristicTwoEpoch : public ETTPKempeChainHeuristic<EOT> {

public:

    // Ctors

    ///
    /// ADDED IN ORDER TO SUPPORT H2 CONSTRAINT IN TWO-EPOCH PROBLEM
    ///
    ///
    ETTPKempeChainHeuristicTwoEpoch(vector<int> const* _firstEpochPeriodsUpperBound) :
        firstEpochPeriodsUpperBound(_firstEpochPeriodsUpperBound) { }


    //
    // Overriden method
    //
    virtual void operator()(EOT& _chrom) override;


private:

    bool feasibleKempeChain(EOT& _chrom, int _ti, int _tj, int _exami);

    //
    // Fields
    //
    vector<int> const* firstEpochPeriodsUpperBound;
};





template <typename EOT>
void ETTPKempeChainHeuristicTwoEpoch<EOT>::operator()(EOT & _chrom) override {

    int exami;
    int ti, tj;

    unordered_set<int>* ti_period;
    unordered_set<int>* tj_period;

    /// Original implementation
    // Select randomly two timeslots, ti and tj.
    do {
        ti = rng.random(_chrom.getNumPeriods());
        do {
            tj = rng.random(_chrom.getNumPeriods());
        }
        while (ti == tj);
    }
    while (_chrom.getPeriods()[ti].size() == 0);

    // Select randomly an exam ei from timeslot ti and move it
    // to timeslot tj. If the solution becomes infeasible,
    // because exam ei has students in common with exams ej, ek, ...,
    // that are assigned to time slot tj, one have to move exams
    // ej, ek, ..., to time slot ti. This process is repeated until all the
    // exams that have students in common are assigned to dif-
    // ferent time slots.


//    cout << "ti = " << ti << ", tj = " << tj << ", _chrom.getNumPeriods() = " << _chrom.getNumPeriods() << endl;

    vector<unordered_set<int> >& periods = _chrom.getPeriods();

    ti_period = &periods[ti];
    tj_period = &periods[tj];


    // Generate random index
    int idx = rng.random(ti_period->size());

//    cout << "idx = " << idx << ", ti_period.size() = " << ti_period.size() << endl;

    /// TODO - NOT EFFICIENT
    // Get exam id
    unordered_set<int>::const_iterator it_i;
    it_i = ti_period->begin();

    for (int i = 0; i < idx; ++i, ++it_i)
        ;

    exami = *it_i;


    ///
    /// ADDED
    ///
    ///

    /// OPTIMIZE CODE

    // Verify feasibility of Kempe chain regarding H2 constraint (Minimum exam distance)
    if (feasibleKempeChain(_chrom, ti, tj, exami)) {
        // Kempe chain operator
        kempeChainOperator(_chrom, *ti_period, *tj_period, exami);
    }

//    cout << "After kempeChainOperator(_chrom, ti_period, tj_period, exami);" << endl;


    _chrom.computeProximityCosts();

//    _chrom.validate();

//    cout << "Validate Ok" << endl;

//    cout << "#exams in slot ti = " << ti_period.size() << endl;
//    cout << "#exams in slot tj = " << tj_period.size() << endl;

//    cout << "Exams's list in slot ti = " << endl;
//    copy(ti_period.begin(), ti_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Exams's list in slot tj = " << endl;
//    copy(tj_period.begin(), tj_period.end(), ostream_iterator<int>(cout, "\n"));

}




template <typename EOT>
bool ETTPKempeChainHeuristicTwoEpoch<EOT>::feasibleKempeChain(EOT& _chrom, int _ti, int _tj, int _exami) {

    //    cout << "feasibleKempeChain" << endl;

    /// OPTIMIZE CODE

    // Get a chromosome copy
    EOT chromCopy = _chrom;
    // Get periods
    vector<unordered_set<int> >& periods = chromCopy.getPeriods();
    auto & ti_period = periods[_ti];
    auto & tj_period = periods[_tj];

    // Apply Kempe chain operator
    kempeChainOperator(chromCopy, ti_period, tj_period, _exami);

    // Then, verify if kempe chain, when exam move occurs, respect H2 constraint (Minimum exam distance)
    //
    bool feasible = true;
    // Verify periods ti and tj feasibility
    for (unordered_set<int>::const_iterator it_i = ti_period.begin(); it_i != ti_period.end(); ++it_i) {
        int exami = *it_i;
        if (_ti > (*firstEpochPeriodsUpperBound)[exami]) { // Exams are indexed at 1
            feasible = false;
            return feasible;
        }
    }

    if (feasible) {
        for (unordered_set<int>::const_iterator it_j = tj_period.begin(); it_j != tj_period.end(); ++it_j) {
            int examj = *it_j;
            if (_tj > (*firstEpochPeriodsUpperBound)[examj]) { // Exams are indexed at 1
                feasible = false;
                return feasible;
            }
        }
    }
    return feasible;
}



#endif // ETTPKEMPECHAINHEURISTICTWOEPOCH_H
