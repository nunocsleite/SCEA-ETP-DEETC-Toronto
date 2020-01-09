

/// TODO

//#include "ChromosomeCapacitated.hpp"
//#include "Constraint.hpp"


//#define _DEBUG



////==========================================================//
////                                                          //
//// Private methods                                          //
////                                                          //
////==========================================================//


//// ROOM-OCCUPANCY: For every room and period no more seats are used than are available
////   for that room.
//bool ChromosomeCapacitated::verifyRoomOccupancyConstraint(int _ei, int _tj, int _rk) const
//{
//#ifdef _DEBUG
//    cout << endl << "[verifyRoomOccupancyConstraint]" << endl;
//    cout << "_ei = " << _ei << ", _tj = " << _tj << ", _rk = " << _rk << endl;
//#endif

//    // Get room vector
//    auto const& roomVector = this->getRoomVector();
//    // Get number of currently occupied seats for room _rk
//    int numOccupiedSeats = roomVector[_rk]->getNumOccupiedSeats();
//    // Get seat capacity for room _rk
//    int roomSeatCapacity = roomVector[_rk]->getCapacity();
//    // Get number of students for exam _ei
//    auto const& examVector = this->getExamVector();
//    int thisExamNumStudents = examVector[_ei]->getNumStudents();
//    // Verify room occupancy constraint
//    if (numOccupiedSeats + thisExamNumStudents > roomSeatCapacity) {
//#ifdef _DEBUG
//        cout << " > constraint [verifyRoomOccupancyConstraint] FAILED" << endl;
//        cout << "numOccupiedSeats = " << numOccupiedSeats << ", thisExamNumStudents = " << thisExamNumStudents
//             << ", roomSeatCapacity = " << roomSeatCapacity << endl;
//#endif
//        return false;
//    }
//    else {
//#ifdef _DEBUG
//        cout << " > constraint [verifyRoomOccupancyConstraint] OK" << endl;
//#endif
//        return true;
//    }
//}




//// PERIOD-UTILISATION: No exam assigned to a period uses more time than available for
////   that period.
//bool ChromosomeCapacitated::verifyPeriodUtilisationConstraint(int _ei, int _tj, int _rk) const {
//#ifdef _DEBUG
//    cout << endl << "[verifyPeriodUtilisationConstraint]" << endl;
//    cout << "_ei = " << _ei << ", _tj = " << _tj << ", _rk = " << _rk << endl;
//#endif

//    // Get exam vector
//    auto const& examVector = this->getExamVector();
//    // Get period vector
//    auto const& periodVector = this->getPeriodVector();
//    // Get period duration
//    int periodDuration = periodVector[_tj]->getDuration();
//    // Get exam duration
//    int examDuration = examVector[_ei]->getDuration();
//    // Verify period utilisation constraint
//    if (examDuration > periodDuration) {
//#ifdef _DEBUG
//        cout << " > constraint [verifyPeriodUtilisationConstraint] FAILED" << endl;
//#endif
//        return false;
//    }
//    else {
//#ifdef _DEBUG
//        cout << " > constraint [verifyPeriodUtilisationConstraint] OK" << endl;
//#endif
//        return true;
//    }
//}



//// PERIOD-RELATED: All of a set of time-ordering requirements between pairs of exams
////   are obeyed. Specifically, for any pair (e1, e2) of exams, one can specify any of:
////   - ‘AFTER’: e1 must take place strictly after e2,
////   - ‘EXAM_COINCIDENCE’: e1 must take place at the same time as e2,
////   - ‘EXCLUSION’: e1 must not take place at the same time as e2.
//bool ChromosomeCapacitated::verifyPeriodRelatedConstraints(int _ei, int _tj, int _rk) const
//{
///*    // Get exam vector
//    auto const& examVector = this->getExamVector();
//    // Get exam 'ei' Period-Related Hard constraints
//    auto const& periodRelatedHardConstraintsVector = examVector[_ei]->getPeriodRelatedHardConstraints();

//    /// We have to set the period for exam 'ei' in order to verify the constraints
//    Exam& ei = *examVector[_ei].get();
//    ei.setPeriod(_tj);

//    // Verify if constraints are satisfied for exam 'ei' scheduled at period 'tj'
//    for (auto const& ptrConstraint : periodRelatedHardConstraintsVector) {
//        boost::shared_ptr<BinaryConstraint> ptrBinConstraint =
//                boost::dynamic_pointer_cast<BinaryConstraint, Constraint>(ptrConstraint);
//        // Verify if exams are scheduled. Only if both exams are scheduled the constraint is verified.
//        if (examVector[ptrBinConstraint->getE1()]->isScheduled() &&
//            examVector[ptrBinConstraint->getE2()]->isScheduled()) {

//            double distanceToFeasibility;
//            // If the constraint is not satisfied return false
//            if ( (distanceToFeasibility = ptrConstraint->operator()(*this)) != 0)
//                return false;
//        }
//    }*/
//    return true;
//}




//// ROOM-RELATED: Room requirements are obeyed. Specifically, for any exam one can
////   disallow the usual sharing of rooms and specify
////   - ‘EXCLUSIVE’: Exam e must take place in a room on its own.
//bool ChromosomeCapacitated::verifyRoomRelatedConstraints(int _ei, int _tj, int _rk) const
//{
//    ///
//    /// TO DO
//    ///

//    //    bool verifiesConstraint = false;
//    bool verifiesConstraint = true;



//    return verifiesConstraint;
//}



////==========================================================//
////                                                          //
//// Public methods                                           //
////                                                          //
////==========================================================//



////===
////
//// ITC2007 Hard constraints
////
//// The STRICT-HARD constraints
////
//// All solutions must, without exception, satisfy the following constraints:
//// COMPLETE-ALLOCATION : All exams must actually take place. Scheduling problems are
////   never a good reason to not run an exam!
//// NO-PERIOD-SPLITTING : Exams cannot be split between periods.
//// NO-ROOM-SPLITTING : Exams cannot be split between rooms.
//// Observe that these correspond to requiring that all exams are assigned to precisely one
//// period and one room.
////
//// The RELAXABLE-HARD constraints
////
//// NO-CONFLICTS: Conflicting exams cannot be assigned to the same period. (As usual,
////   two exams are said to conflict whenever they have some student taking them both.)
//// ROOM-OCCUPANCY: For every room and period no more seats are used than are available
////   for that room.
//// PERIOD-UTILISATION: No exam assigned to a period uses more time than available for
////   that period.
//// PERIOD-RELATED: All of a set of time-ordering requirements between pairs of exams
////   are obeyed. Specifically, for any pair (e1, e2) of exams, one can specify any of:
////   - ‘AFTER’: e1 must take place strictly after e2,
////   - ‘EXAM_COINCIDENCE’: e1 must take place at the same time as e2,
////   - ‘EXCLUSION’: e1 must not take place at the same time as e2.
//// ROOM-RELATED: Room requirements are obeyed. Specifically, for any exam one can
////   disallow the usual sharing of rooms and specify
////   - ‘EXCLUSIVE’: Exam e must take place in a room on its own.
////===

////bool ChromosomeCapacitated::isFeasiblePeriod() const {
////    bool feasiblePeriod = false;

////    cout << endl << "[isFeasiblePeriod() method]" << endl;

////    return feasiblePeriod;
////}



//// Instantiate chromosome's timetable
//void ChromosomeCapacitated::createTimetable()
//{
//    // Chromosome's room x periods timetable
//    boost::shared_ptr<ChromosomeCapacitated::TimetableMatrix> _timetable(
//                    new ChromosomeCapacitated::TimetableMatrix(getNumRooms(), getNumPeriods()));
//    this->timetable = _timetable;
//}


//bool ChromosomeCapacitated::isFeasible() const {

//    cout << endl << "[isFeasible() method]" << endl;

//    return feasible;

////    int numExams = 0, numEnrolments = 0;
////    unordered_map<int, int> exams;
////    bool unique = true;
////    for (ConstPeriodIterator it = periods.begin(); it != periods.end(); ++it) {
////        for (unordered_set<int>::const_iterator examIt = (*it).begin(); examIt != (*it).end(); ++examIt) {
////            ++numExams;
////            numEnrolments += (*courseStudentCounts).at(*examIt);
////            // Verify unicity of exams
////            pair<unordered_map<int, int>::iterator, bool> p =
////                    exams.insert(pair<int, int>(*examIt, (*courseStudentCounts).at(*examIt)));
////            if (p.second == false) {
////                unique = false;
////                break;
////            }
////        }
////    }

////    cout << "numExams = " << numExams << endl;
////    cout << "numEnrolments = " << numEnrolments << endl;

////    cout << "Original values" << endl;
////    cout << "numExams = " << this->numExams << endl;
////    cout << "numEnrolments = " << this->numEnrolments << endl;

////    if (!unique) {
////        cout << "There are duplicated exams" << endl;
////        cin.get();
////    }
////    else if (numExams != this->numExams) {
////        cout << "numExams is different" << endl;
////        cout << "counted: " << numExams << "; original: " <<  this->numExams << endl;

////        cin.get();
////    }
////    else if (numEnrolments != this->numEnrolments) {
////        cout << "numEnrolments is different" << endl;
////        int count = 0, enrol = 0;
////        // Exams indexed from [1..numExams]
////        vector<int> sorted_exams(this->numExams+1);
////        for (unordered_map<int, int>::iterator it = exams.begin(); it != exams.end(); ++it) {
//////            cout << (*it).first << " " << (*it).second << endl;
////            ++count;
////            enrol += (*it).second;
////            sorted_exams[(*it).first] = (*it).second;
////        }
////        cout << endl << "count = " << count << ", enrol = " << enrol << endl;
////        copy(sorted_exams.begin(), sorted_exams.end(), ostream_iterator<int>(cout, "\n"));

////        cin.get();
////    }

////    // Verify feasibility
////    int i = 0;
////    for (ConstPeriodIterator it = periods.begin(); it != periods.end(); ++it, ++i) {
////        for (unordered_set<int>::const_iterator examIt = (*it).begin(); examIt != (*it).end(); ++examIt) {
////            if (!isFeasiblePeriodExam(i, *examIt)) {
////                cout << endl << "Not FeasiblePeriodExam" << endl;
////                cin.get();
////            }
////        }
////    }

////    return true;
//}




/////
///// \brief ChromosomeCapacitated::getFeasibleRoom
///// \param _ei
///// \param _tj
///// \param _rk
/////
//void ChromosomeCapacitated::getFeasibleRoom(int _ei, int _tj, int &_rk)
//{
//    /// TODO
//    ///
//}





///////
/////// \brief ChromosomeCapacitated::getFeasibleRoom
/////// \param _ei
/////// \param _tj
/////// \param _rk
///////
////bool ChromosomeCapacitated::getFeasibleRoom(int _ei, int _tj, int &_rk)
////{
////    bool feasiblePeriod = false;
////    // Initially, the room to test for feasibility is the first one.
////    // Remainder rooms are tested sequently.
////    for (_rk = 0; _rk < this->getNumRooms(); ++_rk) {
////        // Verify ROOM-OCCUPANCY constraint
////        feasiblePeriod = verifyRoomOccupancyConstraint(_ei, _tj, _rk);
////        if (!feasiblePeriod)
////            continue; // Try next room

////        // Verify PERIOD-UTILISATION constraint
////        feasiblePeriod = verifyPeriodUtilisationConstraint(_ei, _tj, _rk);
////        if (!feasiblePeriod)
////            continue; // Try next room

////        // Verify PERIOD-RELATED constraint
////        feasiblePeriod = verifyPeriodRelatedConstraints(_ei, _tj, _rk);
////        if (!feasiblePeriod)
////            continue; // Try next room

////        // Verify ROOM-RELATED constraint
////        feasiblePeriod = verifyRoomRelatedConstraints(_ei, _tj, _rk);
////        if (!feasiblePeriod)
////            continue; // Try next room
////        else
////            break; // A feasible room-period pair was found
////    }
////    // If feasiblePeriod == true, a feasible room _rk is set by reference.
////    return feasiblePeriod;
////}





//void ChromosomeCapacitated::computeTimetablePenalty() {
//    // ITC 2007 objective function...

//    totalPenalty = 0;


//}




//// Output Format
////
//// The best solution found by the algorithm must be written to an output file with extension .sln in the following format.
////
//// One line should describe each exam. The exams should be in the same order as that given in the input file. The following information relating to an exam should be provided:
////
//// The timeslot number, the room number.
//// The timeslot number is an integer between 0 and 44 representing the timeslots allocated to the event.
//// The room is the room number assigned to the event. Remember, rooms are numbered in the order from the problem file, starting at zero.
//// Example
////
//// 11, 0
////
//// 27, 0
////
//// 24, 2
////
//// Means the first exam is timetabled in Period number 11 and is in Room 0 and so on. Competitors should remember that Rooms and Exams are represented by Integers beginning at zero.
////
//// Every line should end with carriage return + linefeed (AKA "\r\n").
//ostream& operator<<(ostream& _os, const ChromosomeCapacitated& _chrom) {
//    // Get exam vector
//    vector<boost::shared_ptr<Exam> > const& examVec = _chrom.getExamVector();
//    bool firstLine = true;
//    for (auto const& exam : examVec) {
//        if (firstLine)
//            firstLine = false;
//        else
//            _os << endl; // For printing carriage return + linefeed for all lines except the last one.
//        int period = exam->getPeriod();
//        int room = exam->getRoom();
//        _os << period << ", " << room;
//    }
//    return _os;
//}

