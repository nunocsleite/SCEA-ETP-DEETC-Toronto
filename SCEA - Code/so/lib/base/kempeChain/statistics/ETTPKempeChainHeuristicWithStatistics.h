#ifndef ETTPKEMPECHAINHEURISTICWITHSTATISTICS_H
#define ETTPKEMPECHAINHEURISTICWITHSTATISTICS_H

#include "eoFunctor.h"
#include "base/chromosome/eoChromosome.h"

#include "base/kempeChain/ETTPKempeChainHeuristic.h"
#include <boost/unordered_set.hpp>
#include <utils/eoRNG.h>


using namespace std;
using namespace boost;


struct MovedExam {
    int exam;
    int sourcePeriod;
    int destPeriod;
};



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
class ETTPKempeChainHeuristicWithStatistics : public ETTPKempeChainHeuristic<EOT> {

public:

    // Ctors
    ETTPKempeChainHeuristicWithStatistics() : ETTPKempeChainHeuristic() { }

    // Overriden method
    virtual void operator()(EOT& _chrom) override;

    MovedExam const& getMoveExamInfo() { return movedExam; }

private:
    MovedExam movedExam;

};




///
/// Overriden method
///
template <typename EOT>
void ETTPKempeChainHeuristicWithStatistics<EOT>::operator()(EOT & _chrom) override {
    int exami;
    int ti, tj;

    unordered_set<int>* ti_period;
    unordered_set<int>* tj_period;

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

    // Kempe chain operator of super class
    kempeChainOperator(_chrom, *ti_period, *tj_period, exami);

//    cout << "After kempeChainOperator(_chrom, ti_period, tj_period, exami);" << endl;

    ///////////////////////////////////////////////////////
    // Statistics
    //
    // Update information about moved exam
    //
    movedExam.exam = exami;
    movedExam.sourcePeriod = ti;
    movedExam.destPeriod = tj;
    ///////////////////////////////////////////////////////

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




#endif // ETTPKEMPECHAINHEURISTICWITHSTATISTICS_H
