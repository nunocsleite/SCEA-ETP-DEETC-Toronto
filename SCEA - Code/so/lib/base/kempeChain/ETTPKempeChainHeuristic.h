#ifndef ETTPKEMPECHAINHEURISTIC_H
#define ETTPKEMPECHAINHEURISTIC_H

#include "eoFunctor.h"
#include "base/kempeChain/ETTPKempeChain.h"
#include <boost/unordered_set.hpp>
#include <utils/eoRNG.h>
#include "base/Common.h"


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
class ETTPKempeChainHeuristic : public eoUF<EOT&, void> {

public:

    /**
     * @brief ETTPKempeChainHeuristic Constructor
     */
    ETTPKempeChainHeuristic() { }

    /**
     * @brief build Create a Kempe chain for a random move
     * @param _sol
     */
    virtual void build(EOT& _sol);

    /**
     * @brief operator () Apply Kempe chain move to solution _sol
     * @param _chrom
     */
    virtual void operator()(EOT& _sol);

    /**
     * @brief getKempeChain Return Kempe chain object
     * @return
     */
    ETTPKempeChain<EOT> &getKempeChain() const;

protected:

    void kempeChainOperator(EOT& _sol, unordered_set<int>& ti_period,
                            unordered_set<int>& tj_period, int exami);


    /**
     * @brief kempeChain The kempe chain relating the current solution to the neighbour solution
     */
    ETTPKempeChain<EOT> kempeChain;
};



/**
 * @brief build Create a Kempe chain for a random move
 * @param _sol
 */
template <typename EOT>
void ETTPKempeChainHeuristic<EOT>::build(EOT &_sol)
{
    int exami; // Selected exam to move
    int ti, tj; // Source and destination time slots, respectively
    boost::unordered_set<int> *tiPeriod; // Time slot exams container
    boost::unordered_set<int> *tjPeriod;
    // Select randomly two time slots, ti and tj.
    do {
        ti = rng.random(_sol.getNumPeriods());
        do {
            tj = rng.random(_sol.getNumPeriods());
        }
        while (ti == tj);
    }
    while (_sol.getPeriods()[ti].size() == 0); // Repeat until we found a non-empty time slot
    //
    // Select randomly an exam ei from timeslot ti and move it
    // to timeslot tj. If the solution becomes infeasible,
    // because exam ei has students in common with exams ej, ek, ...,
    // that are assigned to time slot tj, one have to move exams
    // ej, ek, ..., to time slot ti. This process is repeated until all the
    // exams that have students in common are assigned to different time slots.
    //
#ifdef DEBUG_ETTP_KEMPE_CHAIN_HEURISTIC
    cout << "ti = " << ti << ", tj = " << tj << ", _chrom.getNumPeriods() = " << _chrom.getNumPeriods() << endl;
#endif
    // Get solution periods
    vector<unordered_set<int> >& solPeriods = _sol.getPeriods();
    // Get source and destination time slots
    tiPeriod = &solPeriods[ti];
    tjPeriod = &solPeriods[tj];
    // Generate random index
    int idx = rng.random(tiPeriod->size());
#ifdef DEBUG_ETTP_KEMPE_CHAIN_HEURISTIC
    cout << "idx = " << idx << ", ti_period.size() = " << ti_period.size() << endl;
#endif
    /// TODO - NOT EFFICIENT
    ///
    // Get exam id
    unordered_set<int>::const_iterator it_i;
    it_i = tiPeriod->begin();

    for (int i = 0; i < idx; ++i, ++it_i)
        ;

    exami = *it_i;

    // Initialise Kempe chain object
    kempeChain.setSolution(_sol);
    kempeChain.setEi(exami);
    kempeChain.setTi(ti);
    kempeChain.setTj(tj);
    kempeChain.setTiPeriod(tiPeriod);
    kempeChain.setTjPeriod(tjPeriod);

//    // Kempe chain operator
//    kempeChainOperator(_sol, *ti_period, *tj_period, exami);

#ifdef DEBUG_ETTP_KEMPE_CHAIN_HEURISTIC
    cout << "After kempeChainOperator(_chrom, ti_period, tj_period, exami);" << endl;
#endif

}








/**
 * @brief operator() Move current solution _sol to this neighbour using
 * information maintained in the KempeChain structure
 */
template <typename EOT>
void ETTPKempeChainHeuristic<EOT>::operator()(EOT & _sol) {

//    std::cout << std::endl << "############# RGRAPH #############" << std::endl << std::endl;

//    Rgraph rgraph(graph);
//    Rgraph::adjacency_iterator rbegin, rend;
//    for (boost::tie(rbegin, rend) = boost::adjacent_vertices(v2, rgraph); rbegin != rend; ++rbegin)
//    {
//        std::cout << *rbegin << std::endl;
//    }
//    std::cout << std::endl;



    /// ITERATIVE ?


    // Kempe chain operator
    kempeChainOperator(_sol, *kempeChain.getTiPeriod(), *kempeChain.getTjPeriod(), kempeChain.getEi());

//    cout << "After kempeChainOperator(_chrom, ti_period, tj_period, exami);" << endl;


    /// Update Exam proximity costs where ?
}




template <typename EOT>
void ETTPKempeChainHeuristic<EOT>::kempeChainOperator(EOT& _sol, unordered_set<int>& ti_period,
                                                 unordered_set<int>& tj_period, int exami) {

/*

//    cout << "kempe chain operator" << endl;
//    cout << "ei = " << exami << endl;

    /// TODO > SEE OTHER WAYS: WORKING WITH THE GRAPH, FIND & MOVE,...

    // Verify exam ei feasibility with exams in slot tj and move exams
    // if necessary
    int n;
    vector<int> conflictingExams_tj;
    for (unordered_set<int>::const_iterator it_j = tj_period.begin(); it_j != tj_period.end(); ++it_j) {
        int examj = *it_j;
        n = _sol.getConflictMatrix()->getVal(exami, examj);
        if (n > 0) {
            // Exam examj have conflicts with exam ei
            conflictingExams_tj.push_back(examj);
        }
    }

//    cout << "#exams in slot ti = " << ti_period.size() << endl;
//    cout << "#exams in slot tj = " << tj_period.size() << endl;

//    cout << "Exams's list in slot ti = " << endl;
//    copy(ti_period.begin(), ti_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Exams's list in slot tj = " << endl;
//    copy(tj_period.begin(), tj_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Conflicting exams in slot tj = " << endl;
//    copy(conflictingExams_tj.begin(), conflictingExams_tj.end(), ostream_iterator<int>(cout, "\n"));

    vector<int> conflictingExams_ti;
    for (vector<int>::const_iterator it_conflict = conflictingExams_tj.begin(); it_conflict != conflictingExams_tj.end(); ++it_conflict) {
        for (unordered_set<int>::const_iterator it_i = ti_period.begin(); it_i != ti_period.end(); ++it_i) {
            int exam_conflict = *it_conflict;
            if (*it_i != exami) {
                n = _sol.getConflictMatrix()->getVal(exam_conflict, *it_i);
                if (n > 0) {
                    // Verify if it's inserted already
                    if (find_if(conflictingExams_ti.begin(), conflictingExams_ti.end(),
                                bind2nd(equal_to<int>(), *it_i)) == conflictingExams_ti.end()) {
                        // Exam exam_conflict have conflicts with exam in slot ti
                        conflictingExams_ti.push_back(*it_i);
                    }
                }
            }
        }
    }
    // Consider also exam exami in slot ti
    conflictingExams_ti.push_back(exami);

//    cout << "Conflicting exams in slot ti = " << endl;
//    copy(conflictingExams_ti.begin(), conflictingExams_ti.end(), ostream_iterator<int>(cout, "\n"));


    // Move conflicting exams from slot ti
//    for (vector<int>::const_iterator it_conflict = conflictingExams_ti.begin(); it_conflict != conflictingExams_ti.end(); ++it_conflict) {
        // Remove from slot ti
//        cout << "*it_conflict = " << *it_conflict << " found: " << (ti_period.find(*it_conflict) != ti_period.end()) <<  endl;
//        ti_period.erase(ti_period.find(*it_conflict));

        // Insert in slot tj
//        tj_period.insert(*it_conflict);
//    }

    // Remove from slot ti
    ti_period.erase(exami);
    // Insert just exami in slot tj and then repeat the process for the remainder conflicting exams
    tj_period.insert(exami);
    // Remove exami from conflicting exams
    conflictingExams_ti.erase(find_if(conflictingExams_ti.begin(), conflictingExams_ti.end(), bind2nd(equal_to<int>(), exami)));

    // Move conflicting exams from slot tj
    for (vector<int>::const_iterator it_conflict = conflictingExams_tj.begin(); it_conflict != conflictingExams_tj.end(); ++it_conflict) {
        // Remove from slot tj
        tj_period.erase(tj_period.find(*it_conflict));
        // Insert in slot ti
        ti_period.insert(*it_conflict);
    }

//    cout << "After Kempe chain movement" << endl;
//    cout << "#exams in slot ti = " << ti_period.size() << endl;
//    cout << "#exams in slot tj = " << tj_period.size() << endl;

//    cout << "Exams's list in slot ti = " << endl;
//    copy(ti_period.begin(), ti_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Exams's list in slot tj = " << endl;
//    copy(tj_period.begin(), tj_period.end(), ostream_iterator<int>(cout, "\n"));

    for (vector<int>::const_iterator it_conflict = conflictingExams_ti.begin(); it_conflict != conflictingExams_ti.end(); ++it_conflict) {
        kempeChainOperator(_sol, ti_period, tj_period, *it_conflict);
    }
*/
}


template <typename EOT>
ETTPKempeChain<EOT> &ETTPKempeChainHeuristic<EOT>::getKempeChain() const
{
    return kempeChain;
}


#endif // ETTPKEMPECHAINHEURISTIC_H


/*

template <typename EOT>
void ETTPKempeChainHeuristic<EOT>::operator()(EOT & _sol) {

    int exami;
    int ti, tj;

    boost::unordered_set<int>* ti_period;
    boost::unordered_set<int>* tj_period;

    /// Original implementation
    // Select randomly two timeslots, ti and tj.
    do {
        ti = rng.random(_sol.getNumPeriods());
        do {
            tj = rng.random(_sol.getNumPeriods());
        }
        while (ti == tj);
    }
    while (_sol.getPeriods()[ti].size() == 0);

    // Select randomly an exam ei from timeslot ti and move it
    // to timeslot tj. If the solution becomes infeasible,
    // because exam ei has students in common with exams ej, ek, ...,
    // that are assigned to time slot tj, one have to move exams
    // ej, ek, ..., to time slot ti. This process is repeated until all the
    // exams that have students in common are assigned to dif-
    // ferent time slots.


//    cout << "ti = " << ti << ", tj = " << tj << ", _chrom.getNumPeriods() = " << _chrom.getNumPeriods() << endl;

    vector<unordered_set<int> >& periods = _sol.getPeriods();

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


    // Kempe chain operator
    kempeChainOperator(_sol, *ti_period, *tj_period, exami);

//    cout << "After kempeChainOperator(_chrom, ti_period, tj_period, exami);" << endl;


    _sol.computeProximityCosts();

//    _chrom.validate();

//    cout << "Validate Ok" << endl;

//    cout << "#exams in slot ti = " << ti_period.size() << endl;
//    cout << "#exams in slot tj = " << tj_period.size() << endl;

//    cout << "Exams's list in slot ti = " << endl;
//    copy(ti_period.begin(), ti_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Exams's list in slot tj = " << endl;
//    copy(tj_period.begin(), tj_period.end(), ostream_iterator<int>(cout, "\n"));

}
*/


/*

template <typename EOT>
void ETTPKempeChainHeuristic<EOT>::kempeChainOperator(EOT& _sol, unordered_set<int>& ti_period,
                                                 unordered_set<int>& tj_period, int exami) {

//    cout << "kempe chain operator" << endl;
//    cout << "ei = " << exami << endl;

    /// TODO > SEE OTHER WAYS: WORKING WITH THE GRAPH, FIND & MOVE,...

    // Verify exam ei feasibility with exams in slot tj and move exams
    // if necessary
    int n;
    vector<int> conflictingExams_tj;
    for (unordered_set<int>::const_iterator it_j = tj_period.begin(); it_j != tj_period.end(); ++it_j) {
        int examj = *it_j;
        n = _sol.getConflictMatrix()->getVal(exami, examj);
        if (n > 0) {
            // Exam examj have conflicts with exam ei
            conflictingExams_tj.push_back(examj);
        }
    }

//    cout << "#exams in slot ti = " << ti_period.size() << endl;
//    cout << "#exams in slot tj = " << tj_period.size() << endl;

//    cout << "Exams's list in slot ti = " << endl;
//    copy(ti_period.begin(), ti_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Exams's list in slot tj = " << endl;
//    copy(tj_period.begin(), tj_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Conflicting exams in slot tj = " << endl;
//    copy(conflictingExams_tj.begin(), conflictingExams_tj.end(), ostream_iterator<int>(cout, "\n"));

    vector<int> conflictingExams_ti;
    for (vector<int>::const_iterator it_conflict = conflictingExams_tj.begin(); it_conflict != conflictingExams_tj.end(); ++it_conflict) {
        for (unordered_set<int>::const_iterator it_i = ti_period.begin(); it_i != ti_period.end(); ++it_i) {
            int exam_conflict = *it_conflict;
            if (*it_i != exami) {
                n = _sol.getConflictMatrix()->getVal(exam_conflict, *it_i);
                if (n > 0) {
                    // Verify if it's inserted already
                    if (find_if(conflictingExams_ti.begin(), conflictingExams_ti.end(),
                                bind2nd(equal_to<int>(), *it_i)) == conflictingExams_ti.end()) {
                        // Exam exam_conflict have conflicts with exam in slot ti
                        conflictingExams_ti.push_back(*it_i);
                    }
                }
            }
        }
    }
    // Consider also exam exami in slot ti
    conflictingExams_ti.push_back(exami);

//    cout << "Conflicting exams in slot ti = " << endl;
//    copy(conflictingExams_ti.begin(), conflictingExams_ti.end(), ostream_iterator<int>(cout, "\n"));


    // Move conflicting exams from slot ti
//    for (vector<int>::const_iterator it_conflict = conflictingExams_ti.begin(); it_conflict != conflictingExams_ti.end(); ++it_conflict) {
        // Remove from slot ti
//        cout << "*it_conflict = " << *it_conflict << " found: " << (ti_period.find(*it_conflict) != ti_period.end()) <<  endl;
//        ti_period.erase(ti_period.find(*it_conflict));

        // Insert in slot tj
//        tj_period.insert(*it_conflict);
//    }

    // Remove from slot ti
    ti_period.erase(exami);
    // Insert just exami in slot tj and then repeat the process for the remainder conflicting exams
    tj_period.insert(exami);
    // Remove exami from conflicting exams
    conflictingExams_ti.erase(find_if(conflictingExams_ti.begin(), conflictingExams_ti.end(), bind2nd(equal_to<int>(), exami)));

    // Move conflicting exams from slot tj
    for (vector<int>::const_iterator it_conflict = conflictingExams_tj.begin(); it_conflict != conflictingExams_tj.end(); ++it_conflict) {
        // Remove from slot tj
        tj_period.erase(tj_period.find(*it_conflict));
        // Insert in slot ti
        ti_period.insert(*it_conflict);
    }

//    cout << "After Kempe chain movement" << endl;
//    cout << "#exams in slot ti = " << ti_period.size() << endl;
//    cout << "#exams in slot tj = " << tj_period.size() << endl;

//    cout << "Exams's list in slot ti = " << endl;
//    copy(ti_period.begin(), ti_period.end(), ostream_iterator<int>(cout, "\n"));

//    cout << "Exams's list in slot tj = " << endl;
//    copy(tj_period.begin(), tj_period.end(), ostream_iterator<int>(cout, "\n"));

    for (vector<int>::const_iterator it_conflict = conflictingExams_ti.begin(); it_conflict != conflictingExams_ti.end(); ++it_conflict) {
        kempeChainOperator(_sol, ti_period, tj_period, *it_conflict);
    }
}

*/




















