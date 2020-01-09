

/// TODO


//#include "ExtendedChromosome.h"



///// [Override]
////
//// This overriden method computes the chromosome's proximity cost considering the extended chromosome,
//// that is, considering also five time slots from the second epoch, in order to spread away first epoch
//// exams from conflicting exams in the second epoch.
////
//void ExtendedChromosome::baseComputeProximityCosts() {
//    // The problem has one hard constraint where conflicting exams cannot be assigned to the same time slot.
//    // In addition, a soft constraint is present where conflicting exams should be spread throughout the timetable
//    // as far as possible from each other. The objective here is to minimise the sum of proximity costs given as:
//    //    sum_{i=0}^{4} (wi x n) / S
//    // where
//    // - wi = 2^{4-i} is the cost of assigning two exams with i time slots apart. Only exams with
//    //   common students and are four or less time slots apart are considered as violations
//    // - n is the number of students involved in the conflict
//    // - S is the total number of students in the problem

//    const int NUM_PERIODS_1ST_EPOCH = this->getNumPeriods();
////    cout << "(this->ptrSecondEpochChrom == nullptr) = " << (this->ptrSecondEpochChrom == nullptr) << endl;
//    auto const& secondEpochPeriods = this->ptrSecondEpochChrom->getConstPeriods();
////    cout << "secondEpochPeriods.size() = " << secondEpochPeriods.size() << endl;
//    examProximityConflicts = 0;
//    int pj;
//    int wi, n;
//    // For each period do
//    for (int pi = 0; pi < timetable.size(); ++pi) {
//        // For each exam do
//        for (unordered_set<int>::const_iterator it_i = timetable[pi].begin(); it_i != timetable[pi].end(); ++it_i) {
//            // Consider exams one to five periods apart
//            for (int i = 0; i <= 4; ++i) {
//                pj = pi+i+1;
//                if (pj < timetable.size()) {
//                    for (unordered_set<int>::const_iterator it_j = timetable[pj].begin(); it_j != timetable[pj].end(); ++it_j) {
//                        int exami = *it_i;
//                        int examj = *it_j;
//                        n = conflictMatrix->getVal(exami, examj);
//                        if (n > 0) {
//                            wi = (int)pow(2.0, 4.0-i);
//                            examProximityConflicts += wi*n;
//                        }
//                    }
//                }
//                else { // Verify 2-epoch chromosome
//                    int idx2epoch = pj-NUM_PERIODS_1ST_EPOCH;
////                    cout << "idx 2epoch = " << idx2epoch << endl;
//                    for (unordered_set<int>::const_iterator it_j = secondEpochPeriods[idx2epoch].begin();
//                         it_j != secondEpochPeriods[idx2epoch].end(); ++it_j) {
//                        int exami = *it_i;
//                        int examj = *it_j;
//                        n = conflictMatrix->getVal(exami, examj);
//                        if (n > 0) {
//                            wi = (int)pow(2.0, 4.0-i);
//                            examProximityConflicts += wi*n;
//                        }
//                    }
//                }
//            }
//        }
//    }

//    examProximityConflicts /= numStudents;
//}
