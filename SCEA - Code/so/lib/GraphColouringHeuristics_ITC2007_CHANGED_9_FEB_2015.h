#ifndef GRAPH_COLOURING_HEURISTIC
#define GRAPH_COLOURING_HEURISTIC

#include "ITC2007TestSet.h"
#include "Common.h"
#include <boost/random.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "VertexPriorityQueue.h"
#include "boost/unordered_set.hpp"
#include "ChromosomeCapacitated.hpp"
#include <utility>
#include <ctime>
#include <boost/dynamic_bitset.hpp>


using namespace std;
using namespace boost;


#define _DEBUG




//===
//
// ITC2007 Hard constraints
//
// The STRICT-HARD constraints
//
// All solutions must, without exception, satisfy the following constraints:
// COMPLETE-ALLOCATION : All exams must actually take place. Scheduling problems are
//   never a good reason to not run an exam!
// NO-PERIOD-SPLITTING : Exams cannot be split between periods.
// NO-ROOM-SPLITTING : Exams cannot be split between rooms.
// Observe that these correspond to requiring that all exams are assigned to precisely one
// period and one room.
//
// The RELAXABLE-HARD constraints
//
// NO-CONFLICTS: Conflicting exams cannot be assigned to the same period. (As usual,
//   two exams are said to conflict whenever they have some student taking them both.)
// ROOM-OCCUPANCY: For every room and period no more seats are used than are available
//   for that room.
// PERIOD-UTILISATION: No exam assigned to a period uses more time than available for
//   that period.
// PERIOD-RELATED: All of a set of time-ordering requirements between pairs of exams
//   are obeyed. Specifically, for any pair (e1, e2) of exams, one can specify any of:
//   - ‘AFTER’: e1 must take place strictly after e2,
//   - ‘EXAM_COINCIDENCE’: e1 must take place at the same time as e2,
//   - ‘EXCLUSION’: e1 must not take place at the same time as e2.
// ROOM-RELATED: Room requirements are obeyed. Specifically, for any exam one can
//   disallow the usual sharing of rooms and specify
//   - ‘EXCLUSIVE’: Exam e must take place in a room on its own.
//
//===


/*

template <typename EOT>
class GCHeuristicsITC2007 {

public:
    static bool saturationDegree(ITC2007TestSet const& _itc2007TestSet, EOT& _chrom);


private:


/// TODO: TRANSFER THESE METHODS OR PART TO EXAM CLASS
///

    static bool selectRandomPeriodAndRoom(int _ei, int& _tj, int& _rk, EOT& _chrom,
                                              const vector<bool> &_examsAvailablePeriodsList,
                                              int _numAvailablePeriods);

    static int generateRandomPeriod(const vector<bool> &_availablePeriodsList, int _numAvailablePeriods);

    static void initRandomGenerator();

    static void initExamInfoStructs(ITC2007TestSet const& _itc2007TestSet,
                                    VertexPriorityQueue & _pq,
                                    vector<pair<int, vector<bool> > > & _examsAvailablePeriodsList,
                                    int _numExams, int _numRooms, int _numPeriods);

    static void scheduleExamIntoRandomPeriod(VertexPriorityQueue & _pq,
                                      vector<pair<int, vector<bool> > > & _examsAvailablePeriodsList,
                                      EOT& _chrom, vector<int> &_unscheduledExams);

//    static void scheduleExam(int _ei, int _tj, int _rk, EOT &_chrom);

    static void forceExamSchedulingIntoRandomPeriodRoom(int _ei, int &_tj, int &_rk, EOT &_chrom,
                                                        vector<int> & _unscheduledExams);

    ///
    /// Fields
    ///
    // Random generator used to generate periods
    static random::mt19937 rng;
};



// Random generator used to generate periods
template <typename EOT>
random::mt19937 GCHeuristicsITC2007<EOT>::rng;




//==========================================================//
//                                                          //
// Private methods                                          //
//                                                          //
//==========================================================//


/// bool ?

template <typename EOT>
bool GCHeuristicsITC2007<EOT>::selectRandomPeriodAndRoom(int _ei, int &_tj, int &_rk, EOT &_chrom,
                                                        const vector<bool> & _availablePeriodsList,
                                                        int _numAvailablePeriods)
{
//    bool feasiblePeriodFound = false;

//    if (!feasiblePeriodFound) {

//        cout << "[I THINK THAT THIS SHOULDN'T HAPPEN] No feasible period found, infeasible room? Stopping..." << endl;
//        cin.get();

////            / Force the schedule of 'ei' into a this period into a random room
////            / and unschedule all conflicting exams.
////            /

//    }


//    do {
        // Select a random available (feasible) period 'tj' for scheduling exam 'ei'.
        // Note that we have a vector of bool values, so we have
        // to select a random index within the set of 'true' positions (feasible periods).
        _tj = generateRandomPeriod(_availablePeriodsList, _numAvailablePeriods);
        // Get a feasible room
        _chrom.getFeasibleRoom(_ei, _tj, _rk);


        // If the selected period is not feasible, try another random period.
        // If no feasible period can be found return false.

        // Decrement number of available periods
//        --_numAvailablePeriods;
//    }
//    while (_numAvailablePeriods > 0 && !feasiblePeriodFound);

//    return feasiblePeriodFound;


///
/// TODO
///
        return true;
}




template <typename EOT>
int GCHeuristicsITC2007<EOT>::generateRandomPeriod(const vector<bool> & _availablePeriodsList,
                                                   int _numAvailablePeriods)
{
    // Period distribution. The class template uniform_int_distribution models a random_distribution.
    boost::random::uniform_int_distribution<> periodsDist(0, _numAvailablePeriods-1);
    int index = periodsDist(rng);

    /// O(T) complexity.
    ///

    int tj = -1;
    // Find period that corresponds to the random period distribution index
    for (int p = 0, selectedPeriod = 0; p < _availablePeriodsList.size(); ++p) {
        if (_availablePeriodsList[p] == true) {
            // Found a feasible period. Check if it's the selected period
            if (selectedPeriod == index) {
                tj = p;
                break;
            }
            ++selectedPeriod;
        }
    }

//    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;
//    cout << endl << "Available period vector" << endl;
//    copy(valueTrue.begin(), valueTrue.end(), ostream_iterator<size_t>(cout, " "));
//    cout << endl;
//    cout << "period distribution random index = " << index << ", tj = " << tj << endl;
//    cin.get();
    return tj;
}




template <typename EOT>
void GCHeuristicsITC2007<EOT>::initRandomGenerator() {
    // Generate new seed for random_shuffle
    srand(time(0));
    // Create new seed for random generator
    rng.seed(std::time(0));
}



template <typename EOT>
void GCHeuristicsITC2007<EOT>::initExamInfoStructs(ITC2007TestSet const& _itc2007TestSet,
                                                   VertexPriorityQueue & _pq,
                                                   vector<pair<int, vector<bool> > > & _examsAvailablePeriodsList,
                                                   int _numExams, int _numRooms, int _numPeriods) {

cout << "initExamInfoStructs method" << endl;


    //
    // Fill priority queue with all exams sorted by their period availability.
    //
    vector<bool> allPeriods(_numPeriods);
    for (int p = 0; p < _numPeriods; ++p)
        allPeriods[p] = true; // allPeriods[p] == true means that period 'p' is feasible


//cout << "_examsAvailablePeriodsList.size() = " << _examsAvailablePeriodsList.size() << endl;

    // Exams indexes start at 0 (as specified by the ITC 2007 rules)
    for (int exami = 0; exami < _numExams; ++exami) {
        // Initially, all periods for all exams are feasible
        _examsAvailablePeriodsList[exami] = pair<int, vector<bool> >(_numPeriods, allPeriods);
    }

//cout << "Now, obtain hard constraints" << endl;

    //
    // Update period availability according to the hard constraints. In this phase only the "AFTER" hard constraint
    // is observed, because it limits the exams's period availability.
    //
    // Define a Union-Find structure for maintaining exams dependencies relating to the "AFTER" hard constraint
    vector<int> unionFind(_numExams);
    for (int exami = 0; exami < _numExams; ++exami)
        unionFind[exami] = exami; // All exams have no parent

    // Obtain "AFTER" hard constraints and fill the union-find structure
    vector<boost::shared_ptr<Constraint> > const& hardConstraints = _itc2007TestSet.getHardConstraints();
    for (auto & sharedPtr : hardConstraints) {
        AfterConstraint* ptrConstr = dynamic_cast<AfterConstraint*>(sharedPtr.get());
        if (ptrConstr != nullptr) {

//cout << "Found AfterConstraint: e1 = " << ptrConstr->getE1() << ", e2 = " << ptrConstr->getE2() << endl;

            unionFind[ptrConstr->getE2()] = ptrConstr->getE1();
        }
    }
    int count;
    int ei;
    // Now, determine the period availability using the union-find
    for (int exami = 0; exami < _numExams; ++exami) {
        count = 0; // Number of infeasible periods
        ei = exami;
        while (ei != unionFind[ei]) {
            ei = unionFind[ei];
            ++count; // Traverse union-find tree
        }
        // Subtract number of infeasible periods
        // E.g. If e2 -> e1 -> e3 then e2 have T-2 available periods, e1 have T-1 available periods,
        // and e3 have T available periods.
        _examsAvailablePeriodsList[exami].first -= count;
        while (count > 0) {
            _examsAvailablePeriodsList[exami].second[_numPeriods-count] = false; // Mark period as unavailable
            --count;
        }
    }

// DEBUG
//    // Exams indexes start at 0 (as specified by the ITC 2007 rules)
//    for (int exami = 0; exami < _numExams; ++exami) {
//        cout << "Exam " << exami << ", # available periods " << _examsAvailablePeriodsList[exami].first << endl;
//        for (auto const& b : _examsAvailablePeriodsList[exami].second)
//            cout << b << " ";
//        cout << endl;
//    }
//    cout << endl;
///

    // Shuffle exams indexes
    // Exam's vector. Exams indexes start at 0 (as specified by the ITC 2007 rules)
    vector<int> exams;
    for (int ei = 0; ei < _numExams; ++ei)
        exams.push_back(ei);
    random_shuffle(exams.begin(), exams.end());

    // Insert exams and respective priority (number of feasible available periods) in the priority queue
    for (int exami = 0; exami < _numExams; ++exami) {
        _pq.push(exams[exami], _examsAvailablePeriodsList[exams[exami]].first);
    }
}



//template <typename EOT>
//void GCHeuristicsITC2007<EOT>::scheduleExam(int _ei, int _tj, int _rk, EOT &_chrom) {
//    //
//    // Schedule exam 'ei' in time slot 'tj' and room 'rk'
//    //
//    Exam& scheduledExam = *_chrom.getExamVector()[ei];
//    scheduledExam.setPeriod(tj);
//    scheduledExam.setRoom(rk);
//    // Get room vector
//    auto const& roomVector = _chrom.getRoomVector();
//    // Get number of currently occupied seats for room _rk
//    int numOccupiedSeats = roomVector[rk]->getNumOccupiedSeats();
//    // Get number of students for exam _ei
//    int thisExamNumStudents = scheduledExam.getNumStudents();
//    roomVector[rk]->setNumOccupiedSeats(numOccupiedSeats + thisExamNumStudents);
//    // Insert exam in random feasible room-period
//    auto& timetable = _chrom.getTimetable();
//    timetable(rk, tj).insert(ei);
//}



//
// Output parameters:
// _tj: time slot
// _rk: room
// _unscheduledExams: list of unscheduled exams
//
template <typename EOT>
void GCHeuristicsITC2007<EOT>::forceExamSchedulingIntoRandomPeriodRoom(int _ei, int &_tj, int &_rk, EOT &_chrom,
                                                                       vector<int> & _unscheduledExams) {


cout << "forceExamSchedulingIntoRandomPeriodRoom method" << endl;


//        // period distribution
//        boost::random::uniform_int_distribution<> periodsDist(0, _numAvailablePeriods-1);
//        int index = periodsDist(rng);

//        /// O(T) complexity.
//        ///

//        int tj = -1;
//        // Find period that corresponds to the random period distribution index
//        for (int p = 0, selectedPeriod = 0; p < _availablePeriodsList.size(); ++p) {
//            if (_availablePeriodsList[p] == true) {
//                // Found a feasible period. Check if it's the selected period
//                if (selectedPeriod == index) {
//                    tj = p;
//                    break;
//                }
//                ++selectedPeriod;
//            }
//        }

}




template <typename EOT>
void GCHeuristicsITC2007<EOT>::scheduleExamIntoRandomPeriod(VertexPriorityQueue & _pq,
                                                   vector<pair<int, vector<bool> > > & _examsAvailablePeriodsList,
                                                   EOT& _chrom,
                                                   vector<int> & _unscheduledExams) {
    ///
    /// 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and, if there exists at least
    ///    one available period, schedule it into a random available period 'tj' and room 'rk'. If the available period
    ///    list for exam 'ei' is empty, schedule 'ei' into a random period and unschedule all conflicting exams.
    ///
    VertexPriorityQueue::heap_data data = _pq.top();
    int ei = data.vertex;
    int numAvailablePeriods = data.priority;
    _pq.pop();

    int tj; // Period where exam 'ei' is to be scheduled
    int rk; // Room where exam 'ei' is to be scheduled

    if (numAvailablePeriods > 0) {
        selectRandomPeriodAndRoom(ei, tj, rk, _chrom, _examsAvailablePeriodsList[ei].second,
                                  numAvailablePeriods);

        //
        // Schedule exam 'ei' in time slot 'tj' and room 'rk'
        //
        scheduleExam(ei, tj, rk, _chrom);
    }
    else {
        /// If the available period list for exam 'ei' is empty, schedule 'ei' into a
        /// random period and room and unschedule all conflicting exams.
        ///
        forceExamSchedulingIntoRandomPeriodRoom(ei, tj, rk, _chrom, _unscheduledExams);

    }
}


//==========================================================//
//                                                          //
// Public methods                                           //
//                                                          //
//==========================================================//

template <typename EOT>
bool GCHeuristicsITC2007<EOT>::saturationDegree(ITC2007TestSet const& _itc2007TestSet, EOT& _chrom) {
    //===
    // SD (Saturation Degree) graph colouring heuristic for ITC2007:
    //
    // 1. Create a priority queue with all exams sorted by their period availability.
    //    A period is marked as available for a given exam if all the hard constraints are respected:
    //    - NO-CONFLICTS
    //    - ROOM-OCCUPANCY
    //    - PERIOD-UTILISATION
    //    - PERIOD-RELATED
    //    - ROOM-RELATED
    //
    //    That is:
    //    (1) if there aren't conflicts with exams scheduled in that period,
    //    (2) if there exists at least one room with sufficient seats,
    //    (3) the exam does not exceed the time available for that period, and
    //    (4) all period and room related constraints are satisfied.
    //
    // 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and, if there exists at least
    //    one available period, schedule it into a random available period 'tj' and room 'rk'. If the available period
    //    list for exam 'ei' is empty, schedule 'ei' into a random period and unschedule all conflicting exams.
    //    2.1. Update period availability for all unscheduled exams according to the hard constraints.
    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
    //
    //
    //// APPLY SOME SORT OF TABU LIST OR CONFLICT-BASED STATISTICS?
    ///
    // 3. Goto step 2.
    //===

    cout << endl << "GCHeuristics::SaturationDegreeITC2007 method" << endl;

    // Local variables
    // Initialise random generator
    initRandomGenerator();
//    // N is the number of vertices
//    const int numExams = _chrom.getNumExams();
//    // Number of rooms
//    const int numRooms = _chrom.getNumRooms();
//    // Number of periods
//    const int numPeriods = _chrom.getNumPeriods();
//    // Chromosome's room x periods timetable
//    boost::shared_ptr<ChromosomeCapacitated::TimetableMatrix> timetable(
//                new ChromosomeCapacitated::TimetableMatrix(numRooms, numPeriods));
//    // Set chromosome's timetable
//    _chrom.setTimetable(timetable);

    // Instantiate chromosome's timetable
    _chrom.createTimetable();



    /// SD (Saturation Degree) graph colouring heuristic for ITC2007:
    ///
    /// 1. Create a priority queue with all exams sorted by their period availability.
    ///    A period is marked as available for a given exam if all the hard constraints are respected:
    ///    - NO-CONFLICTS
    ///    - ROOM-OCCUPANCY
    ///    - PERIOD-UTILISATION
    ///    - PERIOD-RELATED
    ///    - ROOM-RELATED
    ///
    ///    That is:
    ///    (1) if there aren't conflicts with exams scheduled in that period,
    ///    (2) if there exists at least one room with sufficient seats,
    ///    (3) the exam does not exceed the time available for that period, and
    ///    (4) all period and room related constraints are satisfied.
    ///

    const int numExams = _chrom.getNumExams();
    // Create vertex priority queue
    VertexPriorityQueue pq(numExams);
    // Feasible available period's list.
    // Periods indexes start at 0 (as specified by the ITC 2007 rules).
    // Each entry in the 'examsAvailablePeriodsList' vector comprise a pair containing
    // the total number of feasible available periods and the corresponding periods vector
    // where each element indicates if that period is feasible (true value) or infeasible (false value).
/*    vector<pair<int, vector<bool> > > examsAvailablePeriodsList(numExams);
    // Initialize exam info (priority queue and exams available period list) structures
    initExamInfoStructs(_itc2007TestSet, pq, examsAvailablePeriodsList, numExams, numExams, numPeriods);

///
/// TODO
///

    // Boolean vector containing information about scheduled exams
//    vector<bool> scheduledExams(numExams); // Initially all false

    vector<int> unscheduledExams; // Output parameter

    // While exams's priority queue is not empty
    while (!pq.empty()) {
        ///
        /// 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and, if there exists at least
        ///    one available period, schedule it into a random available period 'tj' and room 'rk'. If the available period
        ///    list for exam 'ei' is empty, schedule 'ei' into a random period and unschedule all conflicting exams.
        ///
        unscheduledExams.clear();
        scheduleExamIntoRandomPeriod(pq, examsAvailablePeriodsList, _chrom, unscheduledExams);

        ///
        ///    2.1. Update period availability for all unscheduled exams according to the hard constraints.
        ///         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
        ///
        //// APPLY SOME SORT OF TABU LIST OR CONFLICT-BASED STATISTICS?
        ///
        ///


/// TODO

//        // Get adjacent vertices
//        auto const& examGraph = _chrom.getExamGraph();
//        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, examGraph);
//        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
//        boost::tie(ai, a_end) = adjacent_vertices(ei, examGraph);
//        for (; ai != a_end; ++ai) {
//            // Get adjacent exam
//            int ej = get(index_map, *ai);
//            // If adjacent exam's tj period was not marked as unavailable yet
//            if (examsAvailablePeriodsList[ej].second[tj] == 0) {
//                // Decrement number of feasible available periods for exam 'ej'
//                --examsAvailablePeriodsList[ej].first;
//            }
//            // Mark as unavailable period tj of adjacent exam ej.
//            // We decrement a reference counter that represent the number of exams
//            // that declare conflict with this one.
//            examsAvailablePeriodsList[ej].second[tj]--;
//            // If exam was not scheduled
//            if (!scheduled_exams[ej])  {
//                // Update priority queue
//                pq.update(ej, examsAvailablePeriodsList[ej].first);
//            }
//        }
//        // After marking adjacent exams tj period, mark as scheduled exam 'ei'
//        scheduled_exams[ei] = true;
        ///
        /// 3. Goto step 2.
        ///
    }
*

    // Solution is feasible
    return true;
}

*/


/// OLD CODE /////////////



//template <typename EOT>
//bool GCHeuristicsITC2007<EOT>::SaturationDegree(TimetableProblemData const& _timetableProblemData, EOT& _chrom) {
//    //===
//    //
//    // ITC2007 Hard constraints
//    //
//    // The STRICT-HARD constraints
//    //
//    // All solutions must, without exception, satisfy the following constraints:
//    // COMPLETE-ALLOCATION : All exams must actually take place. Scheduling problems are
//    //   never a good reason to not run an exam!
//    // NO-PERIOD-SPLITTING : Exams cannot be split between periods.
//    // NO-ROOM-SPLITTING : Exams cannot be split between rooms.
//    // Observe that these correspond to requiring that all exams are assigned to precisely one
//    // period and one room.
//    //
//    // The RELAXABLE-HARD constraints
//    //
//    // NO-CONFLICTS: Conflicting exams cannot be assigned to the same period. (As usual,
//    //   two exams are said to conflict whenever they have some student taking them both.)
//    // ROOM-OCCUPANCY: For every room and period no more seats are used than are available
//    //   for that room.
//    // PERIOD-UTILISATION: No exam assigned to a period uses more time than available for
//    //   that period.
//    // PERIOD-RELATED: All of a set of time-ordering requirements between pairs of exams
//    //   are obeyed. Specifically, for any pair (e1, e2) of exams, one can specify any of:
//    //   - ‘AFTER’: e1 must take place strictly after e2,
//    //   - ‘EXAM_COINCIDENCE’: e1 must take place at the same time as e2,
//    //   - ‘EXCLUSION’: e1 must not take place at the same time as e2.
//    // ROOM-RELATED: Room requirements are obeyed. Specifically, for any exam one can
//    //   disallow the usual sharing of rooms and specify
//    //   - ‘EXCLUSIVE’: Exam e must take place in a room on its own.
//    //
//    ////////////////////////////////////////////////////////////////////////////
//    //
//    // SD (Saturation Degree) graph colouring heuristic for ITC2007
//    //
//    // 1. Initially, create a Priority queue with all exams inserted randomly.
//    //    Set available periods of all unscheduled exams equal to T, where T is the maximum number of periods.
//    //    A period is marked as available for a given exam if the hard constraints are respected:
//    //    - NO-CONFLICTS
//    //    - ROOM-OCCUPANCY
//    //    - PERIOD-UTILISATION
//    //    - PERIOD-RELATED
//    //    - ROOM-RELATED
//    //
//    //    That is, if there aren't conflicts with exams scheduled in that period,
//    //    if there exists at least one room (from the set of R rooms)
//    //    with sufficient seats, and if the exam does not exceed the time available for that period.
//    //    Also, if there are no free rooms (only free seats in shared rooms are available) and an exam 'e'
//    //    must take place in a room on its own, then the period becomes unavailable for exam 'e'.
//    //
//    // 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and schedule it into
//    //    a random available period 'tj' and room 'rk'. The selected period 'tj' only respects the NO-CONFLICTS
//    //    hard constraint. The remainder hard constraints (ROOM-OCCUPANCY, PERIOD-UTILISATION, PERIOD-RELATED, and
//    //    ROOM-RELATED) must also be satisfied. If the selected period is not feasible with respect to the remainder
//    //    hard constraints, then remove this period from the available period list and choose another available period
//    //    randomly. If no feasible period exists then return false (no feasible solution was found).
//    //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unavailable, because they have common
//    //         registered students (NO-CONFLICTS hard constraint).
//    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
//    //
//    // 3. Goto step 2.
//    //===

//    cout << endl << "GCHeuristics::SaturationDegreeITC2007 method" << endl;

//    // Generate new seed for random_shuffle
//    srand(time(0));
//    // Random generator used to generate periods
//    boost::random::mt19937 rng;
//    // Create new seed for random generator
//    rng.seed(std::time(0));

//    // N is the number of vertices
//    const int N = _chrom.getNumExams();
//    // Create vertex priority queue
//    VertexPriorityQueue pq(N);
//    // Number of rooms
//    const int numRooms = _chrom.getNumRooms();
//    // Number of periods
//    const int numPeriods = _chrom.getNumPeriods();

//#ifdef _DEBUG
//    cout << "N = " << N << endl;
//    cout << "numRooms = " << numRooms << endl;
//    cout << "numPeriods = " << numPeriods << endl;
//#endif

//    // Chromosome's room x periods timetable
//    boost::shared_ptr<ChromosomeCapacitated::TimetableMatrix> timetable(
//                new ChromosomeCapacitated::TimetableMatrix(numRooms, numPeriods));
//    // Set chromosome's timetable
//    _chrom.setTimetable(timetable);

//    //
//    // 1. Initially, create a Priority queue with all exams inserted randomly.
//    //    Set available periods of all unscheduled exams equal to T, where T is the maximum number of periods.
//    //    A period is marked as available for a given exam if the hard constraints are respected.
//    //

//    // Exam's vector. Exams indexes start at 0 (as specified by the ITC 2007 rules)
//    vector<int> exams;
//    for (int ei = 0; ei < N; ++ei)
//        exams.push_back(ei);

//    // Shuffle exams
//    random_shuffle(exams.begin(), exams.end());

//#ifdef _DEBUG
//    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));
//#endif

//    // Insert exams and respective priority (number of feasible available periods) in the priority queue
//    for (int i = 0; i < N; ++i) {
//        pq.push(exams[i], numPeriods);
//    }
//    //
//    // Auxiliary data structure - Feasible available period's list.
//    // Periods indexes start at 0 (as specified by the ITC 2007 rules).
//    // Each entry in the 'examsAvailablePeriodsList' vector comprise a pair containing
//    // the total number of feasible available periods and the corresponding periods vector
//    // where each element with negative value indicates the number of exams which declare a conflict.
//    // A zero value menas that the period is feasible.
//    vector<pair<int, vector<int> > > examsAvailablePeriodsList(N);
//    vector<int> allPeriods(numPeriods);
//    for (int p = 0; p < numPeriods; ++p)
//        allPeriods[p] = 0; // allPeriods[p] == 0 means that period 'p' is feasible

//#ifdef _DEBUG
////    copy(allPeriods.begin(), allPeriods.end(), ostream_iterator<bool>(cout, " "));
////    cout << endl;
//#endif

//    // Exams indexes start at 0 (as specified by the ITC 2007 rules)
//    for (int exam_i = 0; exam_i < N; ++exam_i) {
//        // Initially, all periods for all exams are feasible
//        examsAvailablePeriodsList[exam_i] = pair<int, vector<int> >(numPeriods, allPeriods);
//    }

//    // Auxiliary data structure - Boolean vector containing information about scheduled exams
//    vector<bool> scheduled_exams(N); // Initially all false

//    int ei;
//    int numAvailablePeriods;
//    // While exams's priority queue is not empty
//    while (!pq.empty()) {
//        //
//        // 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and schedule it into
//        //    a random available period 'tj' and room 'rk'. The selected period 'tj' only respects the NO-CONFLICTS
//        //    hard constraint.
//        //
//        VertexPriorityQueue::heap_data data = pq.top();
//        ei = data.vertex;
//        numAvailablePeriods = data.priority;
//        pq.pop();

//#ifdef _DEBUG
//        cout << "ei = " << ei << ", numAvailablePeriods = " << numAvailablePeriods << endl;
//#endif

//        int tj; // Period where exam 'ei' is to be scheduled
//        int rk; // Room where exam 'ei' is to be scheduled
//        bool feasiblePeriodFound = false;

//        if (numAvailablePeriods > 0) {

////////////////////////////////////////////////////////////
///// TODO
/////
/////
/////

//            feasiblePeriodFound = generateFeasiblePeriodAndRoom(ei, tj, rk, _chrom, examsAvailablePeriodsList[ei].second,
//                                                                numAvailablePeriods, rng);

//            if (!feasiblePeriodFound) {
//#ifdef _DEBUG
//                cout << "No feasible period was found. Infeasible solution due to violations in the hard constraints." << endl;
//#endif
//                return false;
//            }
//            // Else, The period is feasible
//            //

//            // Schedule exam 'ei' in time slot 'tj' and room 'rk'
//            Exam& scheduledExam = *_chrom.getExamVector()[ei];
//            scheduledExam.setPeriod(tj);
//            scheduledExam.setRoom(rk);
//            // Get room vector
//            auto const& roomVector = _chrom.getRoomVector();
//            // Get number of currently occupied seats for room _rk
//            int numOccupiedSeats = roomVector[rk]->getNumOccupiedSeats();
//            // Get number of students for exam _ei
//            int thisExamNumStudents = scheduledExam.getNumStudents();
//            roomVector[rk]->setNumOccupiedSeats(numOccupiedSeats + thisExamNumStudents);
//            // Insert exam in random feasible room-period
//            (*timetable)(rk, tj).insert(ei);

//#ifdef _DEBUG
//            cout << "timetable(" << rk << ", " << tj << ") = ";
//            auto const& unord_set = (*timetable)(rk, tj);
//            for (auto const& ex : unord_set) {
//                cout << ex << " ";
//            }
//            cout << endl << endl;
//#endif


//#ifdef _DEBUG
//            cout << "Matrix size: " << timetable->size1() << " x " << timetable->size2() << endl;
//            cout << "Matrix contents:" << endl;
//            for (unsigned i = 0; i < timetable->size1(); ++i) {
//                cout << i << ": ";
//                for (unsigned j = 0; j < timetable->size2(); ++j) {
//                    for (auto const& ex : (*timetable)(i, j)) {
//                        cout << ex << ",";
//                    }
//                    cout << " ";
//                }
//                cout << endl;
//            }
//#endif

////////////////////////////////////////////////////////////

//        }
//        else {
//            // Solution is not feasible because it is not possible to generate
//            // a timetable with the given number of periods.
//#ifdef _DEBUG
//            cout << "Infeasible solution" << endl;
//#endif
//            return false;
//        }
//        //
//        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unavailable, because they have common
//        //         registered students (NO-CONFLICTS hard constraint).
//        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
//        //

//#ifdef _DEBUG
//            cout << endl << "Get adjacent vertices" << endl;
//#endif

//        // Get adjacent vertices
//        auto const& examGraph = _chrom.getExamGraph();
//        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, examGraph);
//        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
//        boost::tie(ai, a_end) = adjacent_vertices(ei, examGraph);
//        for (; ai != a_end; ++ai) {
//            // Get adjacent exam
//            int ej = get(index_map, *ai);
//#ifdef _DEBUG
//            cout << "ej = " << ej << ", tj = " << tj << endl;
//#endif
//            // If exam ej was not scheduled yet, mark adjacent exam's tj period as unavailable
////            if (!scheduled_exams[ej])  {
//#ifdef _DEBUG
//                copy(examsAvailablePeriodsList[ej].second.begin(), examsAvailablePeriodsList[ej].second.end(),
//                     ostream_iterator<bool>(cout, " "));
//                cout << endl;
//                cout << "numFeasibleSlots = " << examsAvailablePeriodsList[ej].first << endl;
//                int numFeasibleSlots = 0;
//                for (auto const& i : examsAvailablePeriodsList[ej].second) {
//                     if (i == 0)
//                        ++numFeasibleSlots;
//                }
//                cout << "numFeasibleSlots = " << numFeasibleSlots << endl;
//#endif

//                // If adjacent exam's tj period was not marked as unavailable yet
//                if (examsAvailablePeriodsList[ej].second[tj] == 0) {
//                    // Decrement number of feasible available periods for exam 'ej'
//                    --examsAvailablePeriodsList[ej].first;
//                }
//                // Mark as unavailable period tj of adjacent exam ej.
//                // We decrement a reference counter that represent the number of exams
//                // that declare conflict with this one.
//                examsAvailablePeriodsList[ej].second[tj]--;
//                // If exam was not scheduled
//                if (!scheduled_exams[ej])  {
//                    // Update priority queue
//                    pq.update(ej, examsAvailablePeriodsList[ej].first);
//                }
////                // If adjacent exam's tj period was not marked as unavailable yet
////                if (examsAvailablePeriodsList[ej].second[tj] == 0) {
////                    // Mark as unavailable period tj of adjacent exam ej.
////                    // We decrement a reference counter that represent the number of exams
////                    // that declare conflict with this one.
////                    examsAvailablePeriodsList[ej].second[tj]--;
////                    // Decrement number of feasible available periods for exam 'ej'
////                    --examsAvailablePeriodsList[ej].first;
////                    // Update priority queue
////                    pq.update(ej, examsAvailablePeriodsList[ej].first);
////                }
////            }
//        }
//        // After marking adjacent exams tj period, mark as scheduled exam 'ei'
//        scheduled_exams[ei] = true;

//        // 3. Goto step 2.
//    }

//    // Solution is feasible
//    return true;
//}


//template <typename EOT>
//bool GCHeuristicsITC2007<EOT>::SaturationDegree(TimetableProblemData const& _timetableProblemData, EOT& _chrom) {
//    //===
//    //
//    // ITC2007 Hard constraints
//    //
//    // The STRICT-HARD constraints
//    //
//    // All solutions must, without exception, satisfy the following constraints:
//    // COMPLETE-ALLOCATION : All exams must actually take place. Scheduling problems are
//    //   never a good reason to not run an exam!
//    // NO-PERIOD-SPLITTING : Exams cannot be split between periods.
//    // NO-ROOM-SPLITTING : Exams cannot be split between rooms.
//    // Observe that these correspond to requiring that all exams are assigned to precisely one
//    // period and one room.
//    //
//    // The RELAXABLE-HARD constraints
//    //
//    // NO-CONFLICTS: Conflicting exams cannot be assigned to the same period. (As usual,
//    //   two exams are said to conflict whenever they have some student taking them both.)
//    // ROOM-OCCUPANCY: For every room and period no more seats are used than are available
//    //   for that room.
//    // PERIOD-UTILISATION: No exam assigned to a period uses more time than available for
//    //   that period.
//    // PERIOD-RELATED: All of a set of time-ordering requirements between pairs of exams
//    //   are obeyed. Specifically, for any pair (e1, e2) of exams, one can specify any of:
//    //   - ‘AFTER’: e1 must take place strictly after e2,
//    //   - ‘EXAM_COINCIDENCE’: e1 must take place at the same time as e2,
//    //   - ‘EXCLUSION’: e1 must not take place at the same time as e2.
//    // ROOM-RELATED: Room requirements are obeyed. Specifically, for any exam one can
//    //   disallow the usual sharing of rooms and specify
//    //   - ‘EXCLUSIVE’: Exam e must take place in a room on its own.
//    //
//    ////////////////////////////////////////////////////////////////////////////
//    //
//    // SD (Saturation Degree) graph colouring heuristic for ITC2007
//    //
//    // 1. Initially, create a Priority queue with all exams inserted randomly.
//    //    Set available periods of all unscheduled exams equal to T, where T is the maximum number of periods.
//    //    A period is marked as available for a given exam if the hard constraints are respected:
//    //    - NO-CONFLICTS
//    //    - ROOM-OCCUPANCY
//    //    - PERIOD-UTILISATION
//    //    - PERIOD-RELATED
//    //    - ROOM-RELATED
//    //
//    //    That is, if there aren't conflicts with exams scheduled in that period,
//    //    if there exists at least one room (from the set of R rooms)
//    //    with sufficient seats, and if the exam does not exceed the time available for that period.
//    //    Also, if there are no free rooms (only free seats in shared rooms are available) and an exam 'e'
//    //    must take place in a room on its own, then the period becomes unavailable for exam 'e'.
//    //
//    // 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and schedule it into
//    //    a random available period 'tj' and room 'rk'. The selected period 'tj' only respects the NO-CONFLICTS
//    //    hard constraint. The remainder hard constraints (ROOM-OCCUPANCY, PERIOD-UTILISATION, PERIOD-RELATED, and
//    //    ROOM-RELATED) must also be satisfied. If the selected period is not feasible with respect to the remainder
//    //    hard constraints, then remove this period from the available period list and choose another available period
//    //    randomly. If no feasible period exists then return false (no feasible solution was found).
//    //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unavailable, because they have common
//    //         registered students (NO-CONFLICTS hard constraint).
//    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
//    //
//    // 3. Goto step 2.
//    //===

//    cout << endl << "GCHeuristics::SaturationDegreeITC2007 method" << endl;

//    // Generate new seed for random_shuffle
//    srand(time(0));
//    // Random generator used to generate periods
//    boost::random::mt19937 rng;
//    // Create new seed for random generator
//    rng.seed(std::time(0));


//    // N is the number of vertices
//    const int N = _chrom.getNumExams();
//    // Create vertex priority queue
//    VertexPriorityQueue pq(N);
//    // Number of rooms
//    const int numRooms = _chrom.getNumRooms();
//    // Number of periods
//    const int numPeriods = _chrom.getNumPeriods();

//#ifdef _DEBUG
//    cout << "N = " << N << endl;
//    cout << "numRooms = " << numRooms << endl;
//    cout << "numPeriods = " << numPeriods << endl;
//#endif

//    // Chromosome's room x periods timetable
//    boost::shared_ptr<ChromosomeCapacitated::TimetableMatrix> timetable(
//                new ChromosomeCapacitated::TimetableMatrix(numRooms, numPeriods));
//    // Set chromosome's timetable
//    _chrom.setTimetable(timetable);

//    //
//    // 1. Initially, create a Priority queue with all exams inserted randomly.
//    //    Set available periods of all unscheduled exams equal to T, where T is the maximum number of periods.
//    //    A period is marked as available for a given exam if the hard constraints are respected.
//    //

//    // Exam's vector. Exams indexes start at 0 (as specified by the ITC 2007 rules)
//    vector<int> exams;
//    for (int ei = 0; ei < N; ++ei)
//        exams.push_back(ei);

//    // Shuffle exams
//    random_shuffle(exams.begin(), exams.end());

//#ifdef _DEBUG
//    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));
//#endif

//    // Insert exams and respective priority (number of feasible available periods) in the priority queue
//    for (int i = 0; i < N; ++i) {
//        pq.push(exams[i], numPeriods);
//    }
//    //
//    // Auxiliary data structure - Feasible available period's list.
//    // Periods indexes start at 0 (as specified by the ITC 2007 rules).
//    // Each entry in the 'examsAvailablePeriodsList' vector comprise a pair containing
//    // the total number of feasible available periods and the corresponding periods vector
//    // where each bool position indicates the period's availability.
//#ifdef USE_DYNAMIC_BIN_SET
//    vector<pair<int, boost::dynamic_bitset<> > > examsAvailablePeriodsList(N);
//    boost::dynamic_bitset<> allPeriods(numPeriods);
//    allPeriods.set(); // Set all bits to 1. Each bit represents a period, so 1 means that the period is feasible.
//#else
//    /// 2ND PROCESS
//    vector<pair<int, vector<bool> > > examsAvailablePeriodsList1(N);
//    vector<bool> allPeriods1(numPeriods);
//    for (int p = 0; p < numPeriods; ++p)
//        allPeriods1[p] = true; // allPeriods[p] = true means that period 'p' is feasible
//#endif

//#ifdef _DEBUG
////    copy(allPeriods.begin(), allPeriods.end(), ostream_iterator<bool>(cout, " "));
////    cout << endl;
//#endif

//    // Exams indexes start at 0 (as specified by the ITC 2007 rules)
//    for (int exam_i = 0; exam_i < N; ++exam_i) {
//#ifdef USE_DYNAMIC_BIN_SET
//        // Initially, all periods for all exams are feasible
//        examsAvailablePeriodsList[exam_i] = pair<int, boost::dynamic_bitset<> >(numPeriods, allPeriods);
//#else
//        /// 2ND PROCESS
//        examsAvailablePeriodsList1[exam_i] = pair<int, vector<bool> >(numPeriods, allPeriods1);
//#endif
//    }

//    // Auxiliary data structure - Boolean vector containing information about scheduled exams
//    vector<bool> scheduled_exams(N); // Initially all false

//    int ei;
//    int numAvailablePeriods;
//    // While exams's priority queue is not empty
//    while (!pq.empty()) {
//        //
//        // 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and schedule it into
//        //    a random available period 'tj' and room 'rk'. The selected period 'tj' only respects the NO-CONFLICTS
//        //    hard constraint.
//        //
//        VertexPriorityQueue::heap_data data = pq.top();
//        ei = data.vertex;
//        numAvailablePeriods = data.priority;
//        pq.pop();

//#ifdef _DEBUG
//        cout << "ei = " << ei << ", numAvailablePeriods = " << numAvailablePeriods << endl;
//#endif

//        int tj; // Period where exam 'ei' is to be scheduled
//        int rk; // Room where exam 'ei' is to be scheduled
//        bool feasiblePeriodFound = false;

//        if (numAvailablePeriods > 0) {

//            //////////////////////////////////////////////////////////
//            /// TODO
//            ///

//            feasiblePeriodFound = generateFeasiblePeriodAndRoom(ei, tj, rk, _chrom, examsAvailablePeriodsList[ei].second,
//                                                                numAvailablePeriods, rng);

////            cout << "feasiblePeriodFound? " << feasiblePeriodFound << endl;
////            cout << "ei = " << ei << ", tj = " << tj << ", rk = " << rk << endl;

////            cin.get();

//            if (!feasiblePeriodFound) {
//#ifdef _DEBUG
//                cout << "No feasible period was found. Infeasible solution due to violations in the hard constraints." << endl;
//#endif
//                return false;
//            }
//            // Else, The period is feasible
//            //

//            // Schedule exam 'ei' in time slot 'tj' and room 'rk'
//            Exam& scheduledExam = *_chrom.getExamVector()[ei];
//            scheduledExam.setPeriod(tj);
//            scheduledExam.setRoom(rk);

////            cout << "After scheduledExam" << endl;

//            // Get room vector
//            auto const& roomVector = _chrom.getRoomVector();
//            // Get number of currently occupied seats for room _rk
//            int numOccupiedSeats = roomVector[rk]->getNumOccupiedSeats();

////            cout << "numOccupiedSeats = " << numOccupiedSeats << endl;

//            // Get number of students for exam _ei
//            int thisExamNumStudents = scheduledExam.getNumStudents();

////            cout << "thisExamNumStudents = " << thisExamNumStudents << endl;

//            roomVector[rk]->setNumOccupiedSeats(numOccupiedSeats + thisExamNumStudents);

////            cout << "After roomVector" << endl;

//            // Insert exam in random feasible room-period
//            (*timetable)(rk, tj).insert(ei);



//#ifdef _DEBUG
//            cout << "timetable(" << rk << ", " << tj << ") = ";
//            auto const& unord_set = (*timetable)(rk, tj);
//            for (auto const& ex : unord_set) {
//                cout << ex << " ";
//            }
//            cout << endl << endl;
//#endif


//#ifdef _DEBUG
//            cout << "Matrix size: " << timetable->size1() << " x " << timetable->size2() << endl;
//            cout << "Matrix contents:" << endl;
//            for (unsigned i = 0; i < timetable->size1(); ++i) {
//                cout << i << ": ";
//                for (unsigned j = 0; j < timetable->size2(); ++j) {
//                    for (auto const& ex : (*timetable)(i, j)) {
//                        cout << ex << ",";
//                    }
//                    cout << " ";
//                }
//                cout << endl;
//            }
//#endif

//            //////////////////////////////////////////////////////////

//        }
//        else {
//            // Solution is not feasible because it is not possible to generate
//            // a timetable with the given number of periods.
//#ifdef _DEBUG
//            cout << "Infeasible solution" << endl;
//#endif
//            return false;
//        }
//        //
//        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unavailable, because they have common
//        //         registered students (NO-CONFLICTS hard constraint).
//        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
//        //

//#ifdef _DEBUG
//            cout << endl << "Get adjacent vertices" << endl;
//#endif

//        // Get adjacent vertices
//        auto const& examGraph = _chrom.getExamGraph();
//        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, examGraph);
//        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
//        boost::tie(ai, a_end) = adjacent_vertices(ei, examGraph);
//        for (; ai != a_end; ++ai) {
//            // Get adjacent exam
//            int ej = get(index_map, *ai);
//#ifdef _DEBUG
//            cout << "ej = " << ej << ", tj = " << tj << endl;
//#endif
//            // If exam ej was not scheduled yet, mark adjacent exam's tj period as unavailable
//            if (!scheduled_exams[ej])  {
//#ifdef _DEBUG

//#ifdef USE_DYNAMIC_BIN_SET
//                cout << examsAvailablePeriodsList[ej].second;
//                cout << endl;
//                cout << "numFeasibleSlots = " << examsAvailablePeriodsList[ej].first << endl;
//                int numFeasibleSlots = 0;
//                numFeasibleSlots = examsAvailablePeriodsList[ej].second.count();
//                cout << "numFeasibleSlots = " << numFeasibleSlots << endl;
//#else
//                /// 2ND PROCESS
//                ///
//                copy(examsAvailablePeriodsList1[ej].second.begin(), examsAvailablePeriodsList1[ej].second.end(),
//                     ostream_iterator<bool>(cout, " "));
//                cout << endl;
//                cout << "numFeasibleSlots = " << examsAvailablePeriodsList1[ej].first << endl;
//                numFeasibleSlots = 0;
//                for (auto const& b : examsAvailablePeriodsList1[ej].second) {
//                    if (b)
//                        ++numFeasibleSlots;
//                }
//                cout << "numFeasibleSlots = " << numFeasibleSlots << endl;
//#endif
//#endif

//#ifdef USE_DYNAMIC_BIN_SET
//                // If adjacent exam's tj period was not marked as unavailable yet
//                if (examsAvailablePeriodsList[ej].second[tj] == true) {
//                    // Mark as unavailable period tj of adjacent exam ej
//                    examsAvailablePeriodsList[ej].second[tj] = false;
//                    // Decrement number of feasible available periods for exam 'ej'
//                    --examsAvailablePeriodsList[ej].first;
//                    // Update priority queue
//                    pq.update(ej, examsAvailablePeriodsList[ej].first);
//                }
//#else
//                /// 2ND PROCESS
//                ///
//                // If adjacent exam's tj period was not marked as unavailable yet
//                if (examsAvailablePeriodsList1[ej].second[tj] == true) {
//                    // Mark as unavailable period tj of adjacent exam ej
//                    examsAvailablePeriodsList1[ej].second[tj] = false;
//                    // Decrement number of feasible available periods for exam 'ej'
//                    --examsAvailablePeriodsList1[ej].first;
//                    // Update priority queue
//                    pq.update(ej, examsAvailablePeriodsList1[ej].first);
//                }
//#endif
//            }
//        }
//        // After marking adjacent exams tj period, mark as scheduled exam 'ei'
//        scheduled_exams[ei] = true;

//        // 3. Goto step 2.
//    }

//    // Solution is feasible
//    return true;
//}

/*



template <typename EOT>
bool GCHeuristicsITC2007<EOT>::generateFeasiblePeriodAndRoom(int _ei, int &_tj, int &_rk, EOT &_chrom,
                                                        const vector<int> & _availablePeriodsList,
                                                        int _numAvailablePeriods, random::mt19937 &_rng)
{
    bool feasiblePeriodFound = false;

    do {
        // Select a random available (feasible) period 'tj' for scheduling exam 'ei'.
        // Note that we have a vector of bool values, so we have
        // to select a random index within the set of 'true' positions (feasible periods).
        _tj = generateRandomPeriod(_availablePeriodsList, _numAvailablePeriods, _rng);

        //
        // The remainder hard constraints (ROOM-OCCUPANCY, PERIOD-UTILISATION, PERIOD-RELATED, and
        //    ROOM-RELATED) must also be satisfied. If the selected period is not feasible with respect to
        //    the remainder hard constraints, then remove this period from the available period list
        //    and choose another available period randomly. If no feasible period exists then return
        //    false (no feasible solution was found).
        //
        // Verify if period 'tj' is feasible for exam 'ei'. The method sets 'rk' to a feasible room.
        // The method 'getFeasiblePeriodRoom' returns false if the period is not feasible. Otherwise, returns true.
        feasiblePeriodFound = _chrom.getFeasiblePeriodRoom(_ei, _tj, _rk);
        // If the selected period is not feasible, try another random period.
        // If no feasible period can be found return false.

        // Decrement number of available periods
        --_numAvailablePeriods;
    }
    while (_numAvailablePeriods > 0 && !feasiblePeriodFound);

    return feasiblePeriodFound;
}




template <typename EOT>
int GCHeuristicsITC2007<EOT>::generateRandomPeriod(const vector<int> & _availablePeriodsList,
                                                   int _numAvailablePeriods, boost::random::mt19937& _rng)
{
    // period distribution
    boost::random::uniform_int_distribution<> periodsDist(0, _numAvailablePeriods-1);
    int index = periodsDist(_rng);

    /// O(T) complexity.
    ///

    int tj = -1;
    // Find period that corresponds to the random period distribution index
    for (int p = 0, selectedPeriod = 0; p < _availablePeriodsList.size(); ++p) {
        if (_availablePeriodsList[p] == 0) {
            // Found a feasible period. Check if it's the selected period
            if (selectedPeriod == index) {
                tj = p;
                break;
            }
            ++selectedPeriod;
        }
    }

#ifdef _DEBUG
//    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;
//    cout << endl << "Available period vector" << endl;
//    copy(valueTrue.begin(), valueTrue.end(), ostream_iterator<size_t>(cout, " "));
//    cout << endl;
//    cout << "period distribution random index = " << index << ", tj = " << tj << endl;
//    cin.get();
#endif
    return tj;
}
*/

/// OLD CODE

//template <typename EOT>
//bool GCHeuristicsITC2007<EOT>::generateFeasiblePeriodAndRoom(int _ei, int &_tj, int &_rk, EOT &_chrom,
//                                                        const boost::dynamic_bitset<> &_availablePeriodsSet,
//                                                        int _numAvailablePeriods, random::mt19937 &_rng)
//{
//    bool feasiblePeriodFound = false;

//    do {
//        // Select a random available (feasible) period 'tj' for scheduling exam 'ei'.
//        // Note that we have a vector of bool values, so we have
//        // to select a random index within the set of 'true' positions (feasible periods).
//        _tj = generateRandomPeriod(_availablePeriodsSet, _numAvailablePeriods, _rng);

//        //
//        // The remainder hard constraints (ROOM-OCCUPANCY, PERIOD-UTILISATION, PERIOD-RELATED, and
//        //    ROOM-RELATED) must also be satisfied. If the selected period is not feasible with respect to
//        //    the remainder hard constraints, then remove this period from the available period list
//        //    and choose another available period randomly. If no feasible period exists then return
//        //    false (no feasible solution was found).
//        //
//        // Verify if period 'tj' is feasible for exam 'ei'. The method sets 'rk' to a feasible room.
//        // The method 'getFeasiblePeriodRoom' returns false if the period is not feasible. Otherwise, returns true.
//        feasiblePeriodFound = _chrom.getFeasiblePeriodRoom(_ei, _tj, _rk);
//        // If the selected period is not feasible, try another random period.
//        // If no feasible period can be found return false.

//        // Decrement number of available periods
//        --_numAvailablePeriods;

//        /// JUST A TEST... Considering only conflicts, it is easy to obtain a feasible solution using SD heuristic.
//        ///
////        feasiblePeriodFound = true;
////        _rk = 0;
//    }
//    while (_numAvailablePeriods > 0 && !feasiblePeriodFound);

//    return feasiblePeriodFound;
//}




//template <typename EOT>
//int GCHeuristicsITC2007<EOT>::generateRandomPeriod(const boost::dynamic_bitset<> &_availablePeriodsSet,
//                                                   int _numAvailablePeriods, boost::random::mt19937& _rng)
//{
//    // period distribution
//    boost::random::uniform_int_distribution<> periodsDist(0, _numAvailablePeriods-1);
//    int index = periodsDist(_rng);
//#ifdef USE_DYNAMIC_BIN_SET
//    /// Complexity?
//    // Find period that corresponds to the random period distribution index
//    /// NOTE: bit 0 is the rightmost bit
//    size_t bitIndex = _availablePeriodsSet.find_first(); // Find index of first bit == 1
//    int numBitsOne = 0;
//    while (bitIndex != boost::dynamic_bitset<>::npos) {
//        ++numBitsOne;
//        if (numBitsOne == index+1)
//            break;
//        // Find index of next bit == 1
//        bitIndex = _availablePeriodsSet.find_next(bitIndex);
//    }
//    // Random time slot
//    int tj = bitIndex;
//    return tj;
//#else
//    /// 2ND PROCESS
//    vector<bool> const& availablePeriodsList1 = examsAvailablePeriodsList1[ei].second;
//    /// O(T) complexity.
//    ///

//    int tj1 = -1;
//    // Find period that corresponds to the random period distribution index
//    for (int p = 0, selectedPeriod = 0; p < availablePeriodsList1.size(); ++p) {
//        if (availablePeriodsList1[p] == true) {
//            // Found a feasible period. Check if it's the selected period
//            if (selectedPeriod == index) {
//                tj1 = p;
//                break;
//            }
//            ++selectedPeriod;
//        }
//    }
//#endif

//#ifdef _DEBUG
//    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;
//    cout << endl << "Available period vector" << endl;
//    cout << _availablePeriodsSet << endl;
////            copy(valueTrue.begin(), valueTrue.end(), ostream_iterator<size_t>(cout, " "));
////            cout << endl;
//    cout << "period distribution random index = " << index << ", tj = " << tj << endl;
////    cout << "tj1 = " << tj1 << endl;
////    cin.get();
//#endif
//}


#endif
