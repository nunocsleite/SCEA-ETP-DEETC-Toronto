
#include "GraphColouringHeuristics.h"
#include <boost/random.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "VertexPriorityQueue.h"
#include "boost/unordered_set.hpp"

/*
template <typename EOT>
void GCHeuristics<EOT>::SD(TimetableProblemData const& _timetableProblemData, EOT& _timetable) {
    //===
    // SD (Saturation Degree) graph colouring heuristic
    //
    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the maximum number of periods.
    // 2. If the queue is not empty, pop exam 'ei' from the top of exam's priority queue and schedule it into
    //    a random available period 'tj'.
    //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
    // 3. Goto step 2.
    //===


//    cout << "GCHeuristics::SD method" << endl;


    // random generator
    boost::random::mt19937 rng;
    // Timetable's periods
    vector<boost::unordered_set<int> >& periods = _timetable.getPeriods();

    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    //
    // N is the number of vertices
    const int N = _conflictMatrix.nCols();
    VertexPriorityQueue pq(N);

    // Max number of periods
    const int numPeriods = _timetable.getNumPeriods();
#ifdef _DEBUG
    cout << "N = " << N << endl;
    cout << "numPeriods = " << numPeriods << endl;
#endif

    // Exam's vector
    vector<int> exams;
    for (int ei = 1; ei <= N; ++ei)
        exams.push_back(ei);
    // Removed exams
    vector<bool> removed_exams(N+1); // Initially all false


    // shuffle exams
    random_shuffle(exams.begin(), exams.end());
    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));
    // Insert them in the priority queue
    for (int i = 0; i < N; ++i) {
        pq.push(exams[i], numPeriods);
    }
    // available period's list
    vector<vector<int> > examsAvailablePeriodsList(N+1);
    vector<int> allPeriods(numPeriods);
    for (int p = 0; p < numPeriods; ++p)
        allPeriods[p] = p+1;

#ifdef _DEBUG
    copy(allPeriods.begin(), allPeriods.end(), ostream_iterator<int>(cout, " "));
#endif


    for (int exam_i = 1; exam_i <= N; ++exam_i)
        examsAvailablePeriodsList[exam_i] = allPeriods;

    while (!pq.empty()) {
        // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random period 'tj'.
        VertexPriorityQueue::heap_data data = pq.top();
        int ei = data.vertex;
        int availablePeriods = data.priority;
        pq.pop();

#ifdef _DEBUG
        cout << "ei = " << ei << ", availablePeriods = " << availablePeriods << endl;
#endif
        int tj;
        if (availablePeriods > 0) {
            // schedule it into a random available period 'tj'.
            boost::random::uniform_int_distribution<> periodsDist(1, availablePeriods); // period distribution
            int index = periodsDist(rng);
            // get available period's list
            vector<int> availablePeriodsList = examsAvailablePeriodsList[ei];
            tj = availablePeriodsList[index-1];

#ifdef _DEBUG
            cout << "index-1 = " << index-1 << ", tj = " << tj << endl;
#endif
//			periods[tj-1].push_back(ei);
            periods[tj-1].insert(ei);
        }
        else {
            // Add a new period to the end of timetable
//			vector<exam_t> newPeriod;
//			newPeriod.push_back(ei);
            unordered_set<int> newPeriod;
            newPeriod.insert(ei);
            periods.push_back(newPeriod);

            tj = numPeriods;

//			timetable.setNumPeriods(numPeriods+1);

#ifdef _DEBUG
            cout << "add new period" << endl;
#endif
        }
        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.

        // get adjacent vertices
        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, _graph);
//
//	for (boost::tie(i, end) = vertices(graph); i != end; ++i) {
//		std::cout << get(index_map, *i);
        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
        boost::tie(ai, a_end) = adjacent_vertices(ei, _graph);
        for (; ai != a_end; ++ai) {
            // get adjacent exam
            int ej = get(index_map, *ai);


#ifdef _DEBUG
            //cout << "ej = " << ej << ", tj = " << tj << endl;
            cout << "ej = " << ej << endl;

#endif
            // If exam ej was not scheduled yet, mark adjacent exam's tj period as unvailable
            if (!removed_exams[ej])  {
                bool removed = false;

                // Remove period tj from ej's exams periods list
                // OPTIMIZATION: USE a bool array
                vector<int>::iterator it;
                for (it = examsAvailablePeriodsList[ej].begin(); it != examsAvailablePeriodsList[ej].end(); ++it) {
                    if (*it == tj) {
#ifdef _DEBUG
                        cout << "size before removing = " << examsAvailablePeriodsList[ej].size() << endl;
#endif

                        examsAvailablePeriodsList[ej].erase(it);

#ifdef _DEBUG
                        cout << "size after removing = " << examsAvailablePeriodsList[ej].size() << endl;
#endif

                        pq.update(ej, examsAvailablePeriodsList[ej].size());
                        removed = true;
                        break;
                    }
                }

                //if (!removed) {
                //	cout << "not removed" << endl;
                //	//cin.get();
                //}

                //copy(examsAvailablePeriodsList[ej].begin(), examsAvailablePeriodsList[ej].end(), ostream_iterator<int>(cout, " "));


                //examsAvailablePeriodsList[ej].erase(examsAvailablePeriodsList[ej].begin()+(tj-1));

                // Decrement available periods (the priority) and update priority queue

                //cout << "examsAvailablePeriodsList[ej].size() = " << examsAvailablePeriodsList[ej].size() << endl;

                //cout << "updating..." << endl;

//				if (removed) {
//					pq.update(ej, examsAvailablePeriodsList[ej].size());
//				}
            }

            removed_exams[ei] = true;

            //cin.get();

        }
        //cin.get();
//		if (ai == a_end)
//			std::cout << " empty";
//		else
//			std::cout << " links: ";
//		for (; ai != a_end; ++ai) {
//			std::cout << get(index_map, *ai);
//			if (boost::next(ai) != a_end)
//			std::cout << ", ";
//		}

//		cin.get();

        // 3. Goto step 2.
    }

//    cout << "Good" << endl;

    // Compute timetable conflicts
//    timetable.computeProximityCosts();

    //cin.get();

}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//* ORIGINAL CODE
//
// SD (Saturation Degree) graph colouring heuristic variant
// where some given exams are placed on fixed time slots and the remainder
// are fitted following SD heuristic.
//
void GCHeuristics::SD(Matrix const& conflictMatrix, AdjacencyList const& graph, Chromosome& timetable,
                      vector<int> const& fixedExams, unordered_map<int, int> const& examsPeriods,
                      vector<int> &remainderExams) {
    //===
    // SD (Saturation Degree) graph colouring heuristic
    //
    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random available period 'tj'.
    //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
    // 3. Goto step 2.
    //===

    // random generator
    boost::random::mt19937 rng;
    // Timetable's periods
    vector<unordered_set<int> >& periods = timetable.getPeriods();

    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    //
    // N is the number of vertices
    const int N = conflictMatrix.getCols();
    VertexPriorityQueue pq(N);

    // Max number of periods
    const int numPeriods = timetable.getNumPeriods();
//    cout << "N = " << N << endl;
//    cout << "numPeriods = " << numPeriods << endl;

    // Exam's vector. Used for shuffling exams order.
//    vector<int> exams;
//    for (int ei = 1; ei <= N; ++ei)
//        exams.push_back(ei);

    // Removed exams
    vector<bool> removed_exams(N+1); // Initially all false
    // Available period's list. Initially all periods are available
    vector<unordered_set<int> > examsAvailablePeriodsList(N+1);
    unordered_set<int> allPeriods;
    for (int period = 1; period <= numPeriods; ++period) {
        allPeriods.insert(period); // period's set
    }
    //    copy(allPeriods.begin(), allPeriods.end(), ostream_iterator<int>(cout, " "));

    for (int exam_i = 1; exam_i <= N; ++exam_i)
        examsAvailablePeriodsList[exam_i] = allPeriods;


    //
    // Insert fixed exams
    //
    GCHeuristics::insertFixedExams(periods, removed_exams, numPeriods, pq, examsAvailablePeriodsList,
                                   fixedExams, examsPeriods, remainderExams, N, graph);

    // shuffle exams
//    random_shuffle(exams.begin(), exams.end());
    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));
    // Insert them in the priority queue
//    for (int i = 0; i < N; ++i) {
//        pq.push(exams[i], numPeriods);
//    }

    while (!pq.empty()) {
        // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random period 'tj'.
        VertexPriorityQueue::heap_data data = pq.top();
        int ei = data.vertex;
        int availablePeriods = data.priority;
        pq.pop();

//        cout << "ei = " << ei << ", availablePeriods = " << availablePeriods << endl;

        int tj;
        if (availablePeriods > 0) {
            // schedule it into a random available period 'tj'.
            boost::random::uniform_int_distribution<> periodsDist(1, availablePeriods); // period distribution
            int index = periodsDist(rng);
            // get available period's list
//            vector<int> availablePeriodsList = examsAvailablePeriodsList[ei];
//            tj = availablePeriodsList[index-1];
            unordered_set<int>& availablePeriodsList = examsAvailablePeriodsList[ei];
//            tj = availablePeriodsList.at(index-1);
            int k = 0;
            // Consider vectors, hum
            auto it = availablePeriodsList.begin();
            for (; k < index-1; ++k, ++it)
                ;

            tj = *it;


//            cout << "tj = " << tj << endl;

            periods[tj-1].insert(ei);
        }
        else {
//            cout << endl << "Add a new period to the end of timetable" << endl << endl;

//            cin.get();

            // Add a new period to the end of timetable
            unordered_set<int> newPeriod;
            newPeriod.insert(ei);
            periods.push_back(newPeriod);

            tj = numPeriods;

            ///
            /// Add tj as new available period??
            ///

        }
        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.

        // Get adjacent vertices
        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, graph);

        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
        boost::tie(ai, a_end) = adjacent_vertices(ei, graph);
        for (; ai != a_end; ++ai) {
            // Get adjacent exam
            int ej = get(index_map, *ai);

//            cout << "ej = " << ej << endl;

            // If exam ej was not scheduled yet, mark tj period as unvailable
            if (!removed_exams[ej])  {
                bool removed = false;
                // Remove period tj from ej's exams periods list
                unordered_set<int>& remainingPeriods = examsAvailablePeriodsList[ej];
                remainingPeriods.erase(tj);
//                if (remainingPeriods.erase(tj) != remainingPeriods.end()) {
//                    throw runtime_error("Period tj should exist!!!")
//                }

//                cout << "Before update" << endl;

//                pq.update(ej, examsAvailablePeriodsList[ej].size());
                pq.update(ej, remainingPeriods.size());
//                removed = true;
//                break;
            }
            removed_exams[ei] = true;
        }
        // 3. Goto step 2.
    }
    // Compute timetable conflicts
//    timetable.computeProximityCosts();


    //cin.get();
}




void GCHeuristics::insertFixedExams(vector<unordered_set<int> >& periods, vector<bool>& removed_exams, int numPeriods,
                                    VertexPriorityQueue& pq, vector<unordered_set<int> >& examsAvailablePeriodsList,
                                    vector<int> const& fixedExams, unordered_map<int, int> const& examsPeriods,
                                    vector<int> & remainderExams, int N, AdjacencyList const& graph) {

    // random generator
    boost::random::mt19937 rng;

    // shuffle exams
    //random_shuffle(exams.begin(), exams.end());
    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));

    // Insert them in the priority queue
//    for (int i = 0; i < N; ++i) {
//        pq.push(exams[i], numPeriods);
//    }
    // Adaptation:
    // Push only fixed exams first and then push the remainder
    for (int i = 0; i < fixedExams.size(); ++i) {
        pq.push(fixedExams[i], -1); // Set high priority
    }

    // shuffle remainder exams
    random_shuffle(remainderExams.begin(), remainderExams.end());
    // Push remainder
    for (int i = 0; i < remainderExams.size(); ++i) {
        pq.push(remainderExams[i], numPeriods); // Set low priority
    }

    // Schedule only the fixed exams
    int z = 0;
    while (z < fixedExams.size()) {
        // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random period 'tj'.
        VertexPriorityQueue::heap_data data = pq.top();
        int ei = data.vertex;
        int availablePeriods = data.priority;
        pq.pop();

//        cout << "availablePeriods = " << availablePeriods << endl;

//        cout << "ei = " << ei;

        // Insert exam into fixed position
        if (examsPeriods.find(ei) == examsPeriods.end()) {
            throw runtime_error("Could not find key in examsPeriods");
        }

        int tj = examsPeriods.at(ei); // tj must be >= 1

        // Insert exam into the timetable
        //periods[tj-1].insert(ei);
        //
        //   The exam is already inserted!!!
        //

//        cout << ", tj = " << tj << endl;
        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.

        // get adjacent vertices
        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, graph);

        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
        boost::tie(ai, a_end) = adjacent_vertices(ei, graph);
        for (; ai != a_end; ++ai) {
            // get adjacent exam
            int ej = get(index_map, *ai);

            // If exam ej was not scheduled yet, mark adjacent exam's tj period as unvailable
            if (!removed_exams[ej])  {
                bool removed = false;
                // Remove period tj from ej's exams periods list
                unordered_set<int>& remainingPeriods = examsAvailablePeriodsList[ej];
//                if (remainingPeriods.erase(tj) != remainingPeriods.end()) { // COMPILATION ERROR, SEE
//                    throw runtime_error("Period tj should exist!!!");
//                }

                remainingPeriods.erase(tj);

//                cout << "Before update" << endl;


                // If not a fixed exam, update it
                if (examsPeriods.find(ej) == examsPeriods.end()) {
                    pq.update(ej, examsAvailablePeriodsList[ej].size());
//                    cout << "  Updated" << endl;
                }

//                pq.update(ej, examsAvailablePeriodsList[ej].size());
//                pq.update(ej, remainingPeriods.size());
//                removed = true;
//                break;
            }
            removed_exams[ei] = true;

        }
        // 3. Goto step 2.
        ++z;
    }

    cout << "Finished inserting fixed exams " << endl;

//    cin.get();

}


/////////////////////////////////////////////////////////////////////////////////////////

void GCHeuristics::SD(Matrix const& _conflictMatrix, AdjacencyList const& _graph, Chromosome& _timetable) {
    //===
    // SD (Saturation Degree) graph colouring heuristic
    //
    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random available period 'tj'.
    //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
    // 3. Goto step 2.
    //===

    // random generator
    boost::random::mt19937 rng;
    // Timetable's periods
//	vector<vector<exam_t> >& periods = timetable.getPeriods();
    vector<unordered_set<int> >& periods = _timetable.getPeriods();

    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    //
    // N is the number of vertices
    const int N = _conflictMatrix.getCols();
    VertexPriorityQueue pq(N);

    // Max number of periods
    const int numPeriods = _timetable.getNumPeriods();
#ifdef _DEBUG
    cout << "N = " << N << endl;
    cout << "numPeriods = " << numPeriods << endl;
#endif

    // Exam's vector
    vector<int> exams;
    for (int ei = 1; ei <= N; ++ei)
        exams.push_back(ei);
    // Removed exams
    vector<bool> removed_exams(N+1); // Initially all false


    // shuffle exams
    random_shuffle(exams.begin(), exams.end());
    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));
    // Insert them in the priority queue
    for (int i = 0; i < N; ++i) {
        pq.push(exams[i], numPeriods);
    }
    // available period's list
    vector<vector<int> > examsAvailablePeriodsList(N+1);
    vector<int> allPeriods(numPeriods);
    for (int p = 0; p < numPeriods; ++p)
        allPeriods[p] = p+1;

#ifdef _DEBUG
    copy(allPeriods.begin(), allPeriods.end(), ostream_iterator<int>(cout, " "));
#endif


    for (int exam_i = 1; exam_i <= N; ++exam_i)
        examsAvailablePeriodsList[exam_i] = allPeriods;

    while (!pq.empty()) {
        // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random period 'tj'.
        VertexPriorityQueue::heap_data data = pq.top();
        int ei = data.vertex;
        int availablePeriods = data.priority;
        pq.pop();

#ifdef _DEBUG
        cout << "ei = " << ei << ", availablePeriods = " << availablePeriods << endl;
#endif
        int tj;
        if (availablePeriods > 0) {
            // schedule it into a random available period 'tj'.
            boost::random::uniform_int_distribution<> periodsDist(1, availablePeriods); // period distribution
            int index = periodsDist(rng);
            // get available period's list
            vector<int> availablePeriodsList = examsAvailablePeriodsList[ei];
            tj = availablePeriodsList[index-1];

#ifdef _DEBUG
            cout << "index-1 = " << index-1 << ", tj = " << tj << endl;
#endif
//			periods[tj-1].push_back(ei);
            periods[tj-1].insert(ei);
        }
        else {
            // Add a new period to the end of timetable
//			vector<exam_t> newPeriod;
//			newPeriod.push_back(ei);
            unordered_set<int> newPeriod;
            newPeriod.insert(ei);
            periods.push_back(newPeriod);

            tj = numPeriods;

//			timetable.setNumPeriods(numPeriods+1);

#ifdef _DEBUG
            cout << "add new period" << endl;
#endif
        }
        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.

        // get adjacent vertices
        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, _graph);
//
//	for (boost::tie(i, end) = vertices(graph); i != end; ++i) {
//		std::cout << get(index_map, *i);
        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
        boost::tie(ai, a_end) = adjacent_vertices(ei, _graph);
        for (; ai != a_end; ++ai) {
            // get adjacent exam
            int ej = get(index_map, *ai);


#ifdef _DEBUG
            //cout << "ej = " << ej << ", tj = " << tj << endl;
            cout << "ej = " << ej << endl;

#endif
            // If exam ej was not scheduled yet, mark adjacent exam's tj period as unvailable
            if (!removed_exams[ej])  {
                bool removed = false;

                // Remove period tj from ej's exams periods list
                // OPTIMIZATION: USE a bool array
                vector<int>::iterator it;
                for (it = examsAvailablePeriodsList[ej].begin(); it != examsAvailablePeriodsList[ej].end(); ++it) {
                    if (*it == tj) {
#ifdef _DEBUG
                        cout << "size before removing = " << examsAvailablePeriodsList[ej].size() << endl;
#endif

                        examsAvailablePeriodsList[ej].erase(it);

#ifdef _DEBUG
                        cout << "size after removing = " << examsAvailablePeriodsList[ej].size() << endl;
#endif

                        pq.update(ej, examsAvailablePeriodsList[ej].size());
                        removed = true;
                        break;
                    }
                }

                //if (!removed) {
                //	cout << "not removed" << endl;
                //	//cin.get();
                //}

                //copy(examsAvailablePeriodsList[ej].begin(), examsAvailablePeriodsList[ej].end(), ostream_iterator<int>(cout, " "));


                //examsAvailablePeriodsList[ej].erase(examsAvailablePeriodsList[ej].begin()+(tj-1));

                // Decrement available periods (the priority) and update priority queue

                //cout << "examsAvailablePeriodsList[ej].size() = " << examsAvailablePeriodsList[ej].size() << endl;

                //cout << "updating..." << endl;

//				if (removed) {
//					pq.update(ej, examsAvailablePeriodsList[ej].size());
//				}
            }

            removed_exams[ei] = true;

            //cin.get();

        }
        //cin.get();
//		if (ai == a_end)
//			std::cout << " empty";
//		else
//			std::cout << " links: ";
//		for (; ai != a_end; ++ai) {
//			std::cout << get(index_map, *ai);
//			if (boost::next(ai) != a_end)
//			std::cout << ", ";
//		}

//		cin.get();

        // 3. Goto step 2.
    }

//    cout << "Good" << endl;

    // Compute timetable conflicts
//    timetable.computeProximityCosts();

    //cin.get();
}


//
// This method is used for solving the 2-epoch DEETC problem,
// where a new hard constraint (H2 - minimum exam distance) must be observed
//
void GCHeuristics::SD(Matrix const& _conflictMatrix, AdjacencyList const& _graph, Chromosome& _timetable,
                      vector<int> const& _firstEpochPeriodsUpperBound) {


    //===
    // SD (Saturation Degree) graph colouring heuristic
    //
    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random available period 'tj'.
    //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
    //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.
    // 3. Goto step 2.
    //===

    // random generator
    boost::random::mt19937 rng;
    // Timetable's periods
//	vector<vector<exam_t> >& periods = timetable.getPeriods();
    vector<unordered_set<int> >& periods = _timetable.getPeriods();

    // 1. Initially, create a Priority queue with all exams inserted randomly.
    //    Set available periods of all unscheduled exams equal to T, where T is the max. number of periods.
    //
    // N is the number of vertices
    const int N = _conflictMatrix.getCols();
    VertexPriorityQueue pq(N);

    // Max number of periods
    const int numPeriods = _timetable.getNumPeriods();
#ifdef _DEBUG
    cout << "N = " << N << endl;
    cout << "numPeriods = " << numPeriods << endl;
#endif

    // Exam's vector
    vector<int> exams;
    for (int ei = 1; ei <= N; ++ei)
        exams.push_back(ei);
    // Removed exams
    vector<bool> removed_exams(N+1); // Initially all false


    // shuffle exams
    random_shuffle(exams.begin(), exams.end());
    //copy(exams.begin(), exams.end(), ostream_iterator<int>(cout, " "));

    ///
    /// CHANGED IN ORDER TO SUPPORT THE 2-EPOCH PROBLEM
    ///
    // Insert them in the priority queue
    int numFreePeriodsExam;
    for (int i = 0; i < N; ++i) {
        // Number of free periods is the upper bound period + 1
        numFreePeriodsExam = _firstEpochPeriodsUpperBound[i+1]+1; // vector _firstEpochPeriodsUpperBound base index is 1
//        pq.push(exams[i], numPeriods);
        pq.push(exams[i], numFreePeriodsExam);
    }
    // available period's list
    vector<vector<int> > examsAvailablePeriodsList(N+1);
    vector<int> allPeriods(numPeriods);
    for (int p = 0; p < numPeriods; ++p)
        allPeriods[p] = p+1;

#ifdef _DEBUG
    copy(allPeriods.begin(), allPeriods.end(), ostream_iterator<int>(cout, " "));
#endif

    ///
    /// CHANGED IN ORDER TO SUPPORT THE 2-EPOCH PROBLEM
    ///

    for (int exam_i = 1; exam_i <= N; ++exam_i) {
//        examsAvailablePeriodsList[exam_i] = allPeriods;
        // Create copy of available periods vector
        auto allPeriodsCopy = allPeriods;
        // Remove periods above upper bound period for exam_i
        int periodUpperBound = _firstEpochPeriodsUpperBound[exam_i];
        allPeriodsCopy.erase(allPeriodsCopy.begin() + periodUpperBound + 1, allPeriodsCopy.end());
        // Add available periods for exam_i
        examsAvailablePeriodsList[exam_i] = allPeriodsCopy;
    }

    while (!pq.empty()) {
        // 2. Pop exam 'ei' from the top of exam's priority queue and schedule it into a random period 'tj'.
        VertexPriorityQueue::heap_data data = pq.top();
        int ei = data.vertex;
        int availablePeriods = data.priority;
        pq.pop();

#ifdef _DEBUG
        cout << "ei = " << ei << ", availablePeriods = " << availablePeriods << endl;
#endif
        int tj;
        if (availablePeriods > 0) {
            // schedule it into a random available period 'tj'.
            boost::random::uniform_int_distribution<> periodsDist(1, availablePeriods); // period distribution
            int index = periodsDist(rng);
            // get available period's list
            vector<int> availablePeriodsList = examsAvailablePeriodsList[ei];
            tj = availablePeriodsList[index-1];

#ifdef _DEBUG
            cout << "index-1 = " << index-1 << ", tj = " << tj << endl;
#endif
//			periods[tj-1].push_back(ei);
            periods[tj-1].insert(ei);
        }
        else {
            // Add a new period to the end of timetable
//			vector<exam_t> newPeriod;
//			newPeriod.push_back(ei);
            unordered_set<int> newPeriod;
            newPeriod.insert(ei);
            periods.push_back(newPeriod);

            tj = numPeriods;

//			timetable.setNumPeriods(numPeriods+1);

#ifdef _DEBUG
            cout << "add new period" << endl;
#endif
        }
        //    2.1. Mark period 'tj' of all the exams connected to 'ei' as unvailable, because they have common registered students.
        //         The number of available periods is the priority used to sort the priority queue of unscheduled exams.

        // get adjacent vertices
        property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, _graph);
//
//	for (boost::tie(i, end) = vertices(graph); i != end; ++i) {
//		std::cout << get(index_map, *i);
        graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
        boost::tie(ai, a_end) = adjacent_vertices(ei, _graph);
        for (; ai != a_end; ++ai) {
            // get adjacent exam
            int ej = get(index_map, *ai);


#ifdef _DEBUG
            //cout << "ej = " << ej << ", tj = " << tj << endl;
            cout << "ej = " << ej << endl;

#endif
            // If exam ej was not scheduled yet, mark adjacent exam's tj period as unvailable
            if (!removed_exams[ej])  {
                bool removed = false;

                // Remove period tj from ej's exams periods list
                // OPTIMIZATION: USE a bool array
                vector<int>::iterator it;
                for (it = examsAvailablePeriodsList[ej].begin(); it != examsAvailablePeriodsList[ej].end(); ++it) {
                    if (*it == tj) {
#ifdef _DEBUG
                        cout << "size before removing = " << examsAvailablePeriodsList[ej].size() << endl;
#endif

                        examsAvailablePeriodsList[ej].erase(it);

#ifdef _DEBUG
                        cout << "size after removing = " << examsAvailablePeriodsList[ej].size() << endl;
#endif

                        pq.update(ej, examsAvailablePeriodsList[ej].size());
                        removed = true;
                        break;
                    }
                }

                //if (!removed) {
                //	cout << "not removed" << endl;
                //	//cin.get();
                //}

                //copy(examsAvailablePeriodsList[ej].begin(), examsAvailablePeriodsList[ej].end(), ostream_iterator<int>(cout, " "));


                //examsAvailablePeriodsList[ej].erase(examsAvailablePeriodsList[ej].begin()+(tj-1));

                // Decrement available periods (the priority) and update priority queue

                //cout << "examsAvailablePeriodsList[ej].size() = " << examsAvailablePeriodsList[ej].size() << endl;

                //cout << "updating..." << endl;

//                if (removed) {
//                    pq.update(ej, examsAvailablePeriodsList[ej].size());
//                }
            }

            removed_exams[ei] = true;

            //cin.get();

        }
        //cin.get();
//        if (ai == a_end)
//            std::cout << " empty";
//        else
//            std::cout << " links: ";
//        for (; ai != a_end; ++ai) {
//            std::cout << get(index_map, *ai);
//            if (boost::next(ai) != a_end)
//            std::cout << ", ";
//        }

//        cin.get();

        // 3. Goto step 2.
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	graph_traits<AdjacencyList>::vertex_iterator i, end;
//	graph_traits<AdjacencyList>::adjacency_iterator ai, a_end;
//	property_map<AdjacencyList, vertex_index_t>::type index_map = get(vertex_index, graph);
//
//	for (boost::tie(i, end) = vertices(graph); i != end; ++i) {
//		std::cout << get(index_map, *i);
//		boost::tie(ai, a_end) = adjacent_vertices(*i, graph);
//		if (ai == a_end)
//			std::cout << " empty";
//		else
//			std::cout << " links: ";
//		for (; ai != a_end; ++ai) {
//			std::cout << get(index_map, *ai);
//			if (boost::next(ai) != a_end)
//			std::cout << ", ";
//		}



