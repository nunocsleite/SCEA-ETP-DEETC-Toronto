
#include "ITC2007TestSet.h"
#include <boost/regex.hpp>
#include <boost/unordered_map.hpp>


using namespace itc2007;
/*

////
/// \brief ITC2007TestSet::load
/// \param _testSetName
/// \param _rootDir
///
void ITC2007TestSet::load(string _testSetName, string _rootDir) {

    //Input Format

    //The problem instance files have the following format;

    //Number of Exams:
    //Number of exams to be timetabled e.g. [Exams:2176]. As with all other entities the numbering of Exams starts at 0.
    //Sequence of lines detailing information regarding each exam:
    //The first number is the duration of the examination (specified in minutes). This is followed by the student numbers of
    //those students taking the exam. Students numbers are integers starting with 0.
    //The line ends with a return character and line feed and is comma separated.

    //Number of Periods:
    //Number of Periods specified within the Timetabling Session e.g. [Periods:42]
    //Sequence of lines detailing Period Dates, Times, Durations associated Penalty:
    //E.g.  31:05:2005, 09:00:00, 180, 0.   The Date is in a standard date format. The time is in 24 hour format, the duration
    //is in minutes and the penalty has a value which is a positive integer. It should be noted that 0 represents no penalty.
    //In relation to other periods a relative value may be present here which indicates that a penalty is added when this period
    //is used by placing an exam. The higher the relative value the least the period should be used.

    //Number of Rooms:
    //Number of Rooms to be used e.g.. [Rooms:10]
    //Sequence of lines detailing room capacity and associated penalty:
    //Room penalty has a value which is a positive integer. It should be noted that 0 represents no penalty. In relation to other
    //rooms a relative value may be present here which indicates that a penalty is added when this room is used by placing an exam.
    //The higher the relative value the least the room should be used.
    //E.g. 500, 7
    //Rooms are numbered in the order from the problem file, starting at zero

    //Period Related Hard Constraints
    //This section begins with the tag [PeriodHardConstraints] and provides data on conditions which are necessary for a feasible solution.
    //These are EXAM_COINCIDENCE, EXCLUSION, and AFTER.  It should be noted that not all these may be present for any one data set.
    //E.g.
    //0, EXAM_COINCIDENCE, 1   Exam ‘0' and Exam ‘1' should be timetabled in the same period. If two exams are set associated in
    //                         this manner yet 'clash' with each other due to student enrolment, this hard constraint is ignored.
    //0, EXCLUSION, 2          Exam ‘0' and Exam ‘2' should be not be timetabled in the same period
    //0, AFTER, 3              Exam ‘0' should be timetabled after Exam ‘3'

    //Room Related Hard Constraints
    //This section begins with the line [RoomHardConstraints] and provides data on conditions which are necessary for a feasible solution.
    //This is
    //ROOM_EXCLUSIVE.  An exam must be timetabled in a room by itself e.g.
    //2, ROOM_EXCLUSIVE      Exam ‘2' must be timetabled in a room by itself.


    //Institutional Model Weightings
    //This section begins with the line [InstitutionalWeightings] and provides information on values given
    //to 'global' soft constraints.

    //TWOINAROW, 7
    //TWOINADAY, 5
    //PERIODSPREAD, 3
    //NONMIXEDDURATIONS, 10
    //FRONTLOAD, 100, 30, 5

    //These are all fully explained and illustrated in the evaluation section.

    //It should be noted that the format of the input file should not be altered in any way.
    //In addition, it is recomended that competitors should ignore unknown lines in the provided format.

    string filename = _rootDir + "/" + _testSetName;
    string wholeFile = read_from_file(filename.c_str());
    // Get line tokenizer
    tokenizer<escaped_list_separator<char> > tok(wholeFile, escaped_list_separator<char>('\\', '\r')); // Lines terminate with \r\n
    // Get line iterator
    tokenizer<escaped_list_separator<char> >::iterator it = tok.begin();
    // Read exams and students
    readExams(it, tok);
    // Read periods
    readPeriods(it, tok);
    // Read rooms
    readRooms(it, tok);
    // Read constraints and weightings
    readConstraints(it, tok);

//    // Instantiate constraint validators
//    for (auto const& c : hardConstraints)
//        hardConstraintValidator.addConstraint(c);

//    for (auto const& c : softConstraints)
//        softConstraintValidator.addConstraint(c);

}


/////////////////////////////////////
// Read exams and students
/////////////////////////////////////

////
/// \brief ITC2007TestSet::readExams
/// \param it
/// \param tok
///
void ITC2007TestSet::readExams(tokenizer<escaped_list_separator<char> >::iterator& it,
                               tokenizer<escaped_list_separator<char> > const& tok) {
    //
    // The problem instance files have the following format;
    // Number of Exams:
    // Number of exams to be timetabled e.g. [Exams:2176]. As with all other entities the numbering of Exams starts at 0.
    // Sequence of lines detailing information regarding each exam:
    // The first number is the duration of the examination (specified in minutes). This is followed by the student numbers of
    // those students taking the exam. Students numbers are integers starting with 0.
    // The line ends with a return character and line feed and is comma separated.
    ////

    // Number of exams
    int numExams = 0;
    if (it != tok.end()) {
        // Read number of exams
        std::string s(*it);
        boost::cmatch matches;
        boost::regex re("(\\[Exams:)(\\d+)(\\])");

        if (boost::regex_match(s.c_str(), matches, re)) {
            //            cout << "\tmatches" << endl;
            //            // matches[0] contains the original string.  matches[n]
            //            // contains a sub_match object for each matching
            //            // subexpression
            //            for (int i = 1; i < matches.size(); i++)
            //            {
            //               // sub_match::first and sub_match::second are iterators that
            //               // refer to the first and one past the last chars of the
            //               // matching subexpression
            //               string match(matches[i].first, matches[i].second);
            //               cout << "\tmatches[" << i << "] = " << match << endl;
            //            }

            // Extract digits from string. The digits are the third subexpression, index = 2.
            string match(matches[2].first, matches[2].second);
            numExams = atoi(match.c_str());
            cout << "\tnumExams: " << numExams << endl;

            ///
            /// TODO: fill base class fields instead of creating local fields
            /// Fill exam vector
            ///

            // Set number of exams
            timetableProblemData->setNumExams(numExams);
            // Create exam vector
            boost::shared_ptr<vector<boost::shared_ptr<Exam> > > examVector(new vector<boost::shared_ptr<Exam> >());
            // Set exam vector
            timetableProblemData->setExamVector(examVector);

            //////////////////////////////////////////
            // Build Conflict matrix and graph
            //////////////////////////////////////////

            buildConflictMatrix(it, tok, examVector);

            Matrix const& conflictMatrix = timetableProblemData.get()->getConflictMatrix();

            cout << "nlines = " << conflictMatrix.nLines() << endl;
            cout << "ncols = " << conflictMatrix.nCols() << endl;

            // Verify if it's symmetric
            for (int i = 0; i < conflictMatrix.nLines(); ++i) {
                for (int j = 0; j < conflictMatrix.nCols(); ++j) {
                    if (conflictMatrix.getVal(i, j) != conflictMatrix.getVal(j, i))
                        throw runtime_error("Not symmetric");
                }
            }

            // Print the conflict matrix density
            double conflictDensity = timetableProblemData.get()->getConflictMatrixDensity();
            cout << "conflictDensity = " << conflictDensity << endl;
            cout << "conflictDensity [%] = " << setprecision(3) << (conflictDensity * 100) << endl;

            // Build exam graph representing exam relations
            buildExamGraph(timetableProblemData.get()->getConflictMatrix());
        }
        else
        {
            cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
            cin.get();
        }
    }
    else
        throw runtime_error("Error while reading ITC07 exams");
}



////
/// \brief ITC2007TestSet::buildConflictMatrix
/// \param it
/// \param tok
///
void ITC2007TestSet::buildConflictMatrix(tokenizer<escaped_list_separator<char> >::iterator& it,
                                         tokenizer<escaped_list_separator<char> > const& tok,
                                         boost::shared_ptr<vector<boost::shared_ptr<Exam> > >& examVector) {

    // Unordered map to keep course total students. Exams indexed from [0..numExams-1].
//    boost::shared_ptr<unordered_map<int, int> > courseClassSizeUnorderedMap(new unordered_map<int, int>());

    int numExams = timetableProblemData->getNumExams();
    // Create shared ptr to manage Conflict Matrix
    boost::shared_ptr<Matrix> ptrConflictMatrix(new Matrix(numExams, numExams));
    // Obtain internal vector
    vector<int>& v = ptrConflictMatrix->getVec();
    //
    // Define student map containing the list of exams for each student
    //
    unordered_map<int, vector<int> > studentMap;
    int examDuration;

    int numEnrolments1 = 0;

    // Go to the first line of exams
    ++it;
    for (int i = 0; i < numExams && it != tok.end(); ++i, ++it) {
        string line(*it);
//        cout << i << ": " << line << endl; // Lines start with \n because it wasn't removed
        // Get number tokenizer
        tokenizer<escaped_list_separator<char> > numberTok(line, escaped_list_separator<char>('\\', ','));
        // Get number iterator
        tokenizer<escaped_list_separator<char> >::iterator beg = numberTok.begin();
        examDuration = atoi((*beg).c_str());
//        cout << "examDuration: " << examDuration << " - Students: ";

        ++beg; // Go to the first student
        // Exam number start at 1
//            int exam = i+1;
/// SEE
        // Exam number (start at 0)
        int exam = i;
//        // Instantiate Exam object
//        examVector->push_back(boost::shared_ptr<Exam>(new Exam(exam)));

        // Number of students enrolled in each exam
        int numExamStudents = 0;

        for (; beg != numberTok.end(); ++beg) {
//            cout << *beg << " ";
            //////////////////////////////////////////
            // Build student map
            //////////////////////////////////////////
            // Current student
            int student = atoi((*beg).c_str());

            // Insert current exam, given by the index i, in the student map
            // If student doesn't exist yet, create entry <student, exam>
            unordered_map<int, vector<int> >::iterator mapIt = studentMap.find(student);
            if (mapIt == studentMap.end()) {
                vector<int> exams;
                exams.push_back(exam);
                studentMap.insert(pair<int, vector<int> >(student, exams));
            }
            else {
                // Else add exam to the student exams
                mapIt->second.push_back(exam);
            }
            // Increment # students
            ++numExamStudents;
        }
//        cout << endl << endl;

        /// TODO
        ///

        // Insert total number of students associated to each exam
//        courseClassSizeUnorderedMap->insert(pair<int,int>(exam, numExamStudents));

        // Instantiate Exam object
        examVector->push_back(boost::shared_ptr<Exam>(new Exam(exam, numExamStudents, examDuration)));

        numEnrolments1 += numExamStudents;
    }

    // Print student info
    cout << "Print student info" << endl << endl;
    int numStudents = 0, smallest = INT_MAX, greatest = INT_MIN;
    int numEnrolments = 0;
    for (auto const&s : studentMap) {
        //                cout << "Student: " << s.first << " - total exams: " << s.second.size() << endl;
        ++numStudents;
        smallest = min(smallest, s.first);
        greatest = max(greatest, s.first);
        numEnrolments += s.second.size();
    }
    cout << "numStudents = " << numStudents << endl;
    cout << "smallest = " << smallest << endl;
    cout << "greatest = " << greatest << endl;
    cout << "numEnrolments = " << numEnrolments << endl;

//    // Print total number of students associated to each exam
//    for (const auto& it : *courseClassSizeUnorderedMap.get()) {
//        cout << "Exam = " << it.first << ", # students = " << it.second << endl;
//    }
    cout << "numEnrolments1 = " << numEnrolments1 << endl;

    // Print exam vector
    for (const auto& ptrExam : *examVector.get()) {
        cout << "Exam = " << ptrExam->getId()
             << ", Period = " << ptrExam->getPeriod()
             << ", Room = " << ptrExam->getRoom()
             << ", # students = " << ptrExam->getNumStudents()
             << ", duration = " << ptrExam->getDuration()
             << endl;
    }

    //////////////////////////////////////////
    // Build Conflict matrix
    //////////////////////////////////////////
    // Reserve space for matrix
    ptrConflictMatrix->reserve(ptrConflictMatrix->nLines(), ptrConflictMatrix->nCols());

    for (auto entry : studentMap) {
        vector<int>& exams = entry.second;
        int examListSize = exams.size();
        for (int i = 0; i < examListSize; ++i) {
            for (int j = 0; j < examListSize; ++j) {
                if (j != i) {
                    ++v[exams[j] * ptrConflictMatrix->nCols() + exams[i]];
                }
            }
        }
    }
    //
    // and set TimetableProblemData field
    //
    // Set conflict matrix
    timetableProblemData.get()->setConflictMatrix(ptrConflictMatrix);
    // Set number of students
    timetableProblemData.get()->setNumStudents(numStudents);
    // Set number of enrolments
    timetableProblemData.get()->setNumEnrolments(numEnrolments);
    // Set course class size unordered map
//    timetableProblemData->setCourseClassSizeUnorderedMap(courseClassSizeUnorderedMap);
}




////
/// \brief ITC2007TestSet::buildExamGraph
/// \param conflictMatrix
///
void ITC2007TestSet::buildExamGraph(Matrix const& conflictMatrix) {
    // Instantiate graph with ncols vertices
    boost::shared_ptr<AdjacencyList> ptrGraphAux(new AdjacencyList(conflictMatrix.nCols()+1));
    // and set TimetableProblemData field
    timetableProblemData.get()->setExamGraph(ptrGraphAux);
    int cost;
    // Vertices start at 0 as specified by the ITC 2007 rules
    for (int v1 = 0; v1 < conflictMatrix.nLines(); ++v1) {
        for (int v2 = 0; v2 < conflictMatrix.nCols(); ++v2) {
            cost = conflictMatrix.getVal(v1, v2);
            if (cost != 0) {
                if (v2 > v1) {
                    add_edge(v1, v2, *ptrGraphAux.get());
                }
            }
        }
    }
}




/////////////////////////////////////
// Read periods
/////////////////////////////////////

////
/// \brief ITC2007TestSet::readPeriods
/// \param it
/// \param tok
///
void ITC2007TestSet::readPeriods(tokenizer<escaped_list_separator<char> >::iterator& it,
                                 tokenizer<escaped_list_separator<char> > const& tok) {
    //
    // The problem instance files have the following format;
    // Number of Periods:
    // Number of Periods specified within the Timetabling Session e.g. [Periods:42]
    // Sequence of lines detailing Period Dates, Times, Durations and associated Penalty:
    // E.g.  31:05:2005, 09:00:00, 180, 0.   The Date is in a standard date format. The time is in 24 hour format, the duration
    // is in minutes and the penalty has a value which is a positive integer. It should be noted that 0 represents no penalty.
    // In relation to other periods a relative value may be present here which indicates that a penalty is added when this period
    // is used by placing an exam. The higher the relative value the least the period should be used.
    ////

    boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > > periodVector(
                new vector<boost::shared_ptr<itc2007::Period> >());

    if (it != tok.end()) {
        // Match period number
        int numPeriods = matchPeriods(it);
        int periodId = 0; // Period index
        ++it; // Read next line
        // Read periods info
        for (int i = 0; i < numPeriods; ++i) {
//            cout << "line " << (i+1) << ":" << endl;
            // Match a sequence line
            matchPeriodSequenceLine(periodId, it, periodVector);
            ++periodId; // Increment period index
            ++it; // Read next line
        }
        //
        // Set TimetableProblemData field
        //
        // Set number of periods
        timetableProblemData.get()->setNumPeriods(numPeriods);
        // Set period vector
        timetableProblemData->setPeriodVector(periodVector);

        // Processed period information
        cout << "Processed period information: " << endl;
        cout << "numPeriods = " << numPeriods << endl;
        cout << "period vector # entries = " << timetableProblemData->getPeriodVector().size() << endl;
    }
    else
        throw runtime_error("Error while reading ITC07 periods");
}




////
/// \brief ITC2007TestSet::matchPeriods
/// \param it
/// \return
///
int ITC2007TestSet::matchPeriods(tokenizer<escaped_list_separator<char> >::iterator& it) {
    /////////////////////////////////////////////////
    // Lines start with \n because it wasn't removed
    //
    // Remove first \n in the regexp
    /////////////////////////////////////////////////

    // Number of periods
    int numPeriods = 0;
    // Read number of periods specified within the Timetabling Session e.g. [Periods:42]
    std::string s(*it);
    boost::cmatch matches;
    //        boost::regex re("(\\[Periods:)(\\d+)(\\])");
    boost::regex re("(\\\n)(\\[Periods:)(\\d+)(\\])");

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract digits from string. The digits are the third subexpression, index = 3.
        string match(matches[3].first, matches[3].second);
        numPeriods = atoi(match.c_str());
//        cout << "\tnumPeriods: " << numPeriods << endl;
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        cin.get();
    }
    return numPeriods;
}



////
/// \brief ITC2007TestSet::matchPeriodSequenceLine
/// \param _periodId
/// \param _it
/// \param _periodVector
/// \return
///
int ITC2007TestSet::matchPeriodSequenceLine(int _periodId,
                                            tokenizer<escaped_list_separator<char> >::iterator& _it,
                                            boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > >& _periodVector) {

    // Read sequence of lines detailing Period Dates, Times, Durations and associated Penalty:
    //  E.g.  31:05:2005, 09:00:00, 180, 0.
    std::string s(*_it);
    //    std::string s("\n15:04:2005, 09:30:00");

    boost::cmatch matches;
    //    boost::regex re("(\\\n)(\\d{2}):(\\d{2}):(\\d{4}), (\\d{2}):(\\d{2}):(\\d{2})");

    boost::regex re("(\\\n)(\\d{2}):(\\d{2}):(\\d{4}), (\\d{2}):(\\d{2}):(\\d{2}), (\\d+), (\\d+)");

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract values from string. E.g., the day part is the second subexpression, index = 2.
        string matchDay(matches[2].first, matches[2].second);
        int day = atoi(matchDay.c_str());
        string matchMonth(matches[3].first, matches[3].second);
        int month = atoi(matchMonth.c_str());
        string matchYear(matches[4].first, matches[4].second);
        int year = atoi(matchYear.c_str());

        string matchHour(matches[5].first, matches[5].second);
        int hour = atoi(matchHour.c_str());
        string matchMinute(matches[6].first, matches[6].second);
        int minute = atoi(matchMinute.c_str());
        string matchSecond(matches[7].first, matches[7].second);
        int second = atoi(matchSecond.c_str());

        string matchDuration(matches[8].first, matches[8].second);
        int duration = atoi(matchDuration.c_str());

        string matchPenalty(matches[9].first, matches[9].second);
        int penalty = atoi(matchPenalty.c_str());

//        cout << "\tday: " << day << endl;
//        cout << "\tmonth: " << month << endl;
//        cout << "\tyear: " << year << endl;
//        cout << "\thour: " << hour << endl;
//        cout << "\tminute: " << minute << endl;
//        cout << "\tsecond: " << second << endl;
//        cout << "\tduration: " << duration << endl;
//        cout << "\tpenalty: " << penalty << endl;
//        cout << endl;

        // Create Period instance for keeping period information
        boost::shared_ptr<itc2007::Period> period(new itc2007::Period(_periodId, Date(day, month, year),
                                                                      Time(hour, minute, second), duration, penalty));
        _periodVector->push_back(period);
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        cin.get();
    }
}



/////////////////////////////////////
// Read rooms
/////////////////////////////////////

////
/// \brief ITC2007TestSet::readRooms
/// \param it
/// \param tok
///
void ITC2007TestSet::readRooms(tokenizer<escaped_list_separator<char> >::iterator& it,
                               tokenizer<escaped_list_separator<char> > const& tok) {
    //
    // The problem instance files have the following format;
    // Number of Rooms:
    // Number of Rooms to be used e.g.. [Rooms:10]
    // Sequence of lines detailing room capacity and associated penalty:
    // Room penalty has a value which is a positive integer. It should be noted that 0 represents no penalty.
    // In relation to other rooms a relative value may be present here which indicates that a penalty is added
    // when this room is used by placing an exam.
    // The higher the relative value the least the room should be used.
    // E.g. 500, 7
    // Rooms are numbered in the order from the problem file, starting at zero
    ////

    boost::shared_ptr<vector<boost::shared_ptr<Room> > > roomVector(
                new vector<boost::shared_ptr<Room> >());

    if (it != tok.end()) {
        // Match rooms number
        int numRooms = matchRooms(it);
        int roomId = 0; // Room index
        ++it; // Read next line
        // Read rooms info
        for (int i = 0; i < numRooms; ++i) {
//            cout << "line " << (i+1) << ":" << endl;
            // Match a sequence line
            matchRoomSequenceLine(roomId, it, roomVector);
            ++roomId; // Increment room index
            ++it; // Read next line
        }
        //
        // Set TimetableProblemData field
        //
        // Set number of rooms
        timetableProblemData.get()->setNumRooms(numRooms);
        // Set room vector
        timetableProblemData->setRoomVector(roomVector);

        // Processed period information
        cout << "Processed room information: " << endl;
        cout << "numRooms = " << numRooms << endl;
        cout << "room vector # entries = " << timetableProblemData->getRoomVector().size() << endl;
    }
    else
        throw runtime_error("Error while reading ITC07 rooms");
}



////
/// \brief ITC2007TestSet::matchRooms
/// \param it
/// \return
///
int ITC2007TestSet::matchRooms(tokenizer<escaped_list_separator<char> >::iterator& it) {
    /////////////////////////////////////////////////
    // Lines start with \n because it wasn't removed
    //
    // Remove first \n in the regexp
    /////////////////////////////////////////////////

    // Number of rooms
    int numRooms = 0;
    // Read number of rooms used e.g. [Rooms:10]
    std::string s(*it);
    boost::cmatch matches;
    //        boost::regex re("(\\[Rooms:)(\\d+)(\\])");
    boost::regex re("(\\\n)(\\[Rooms:)(\\d+)(\\])");

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract digits from string. The digits are the third subexpression, index = 3.
        string match(matches[3].first, matches[3].second);
        numRooms = atoi(match.c_str());
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        cin.get();
    }

    return numRooms;
}


////
/// \brief ITC2007TestSet::matchRoomSequenceLine
/// \param _roomId
/// \param _it
/// \param _roomVector
/// \return
///
int ITC2007TestSet::matchRoomSequenceLine(int _roomId, tokenizer<escaped_list_separator<char> >::iterator& _it,
                                          boost::shared_ptr<vector<boost::shared_ptr<Room> > > &_roomVector) {
    // Read sequence of lines detailing room capacity and associated penalty:
    //  E.g.  260, 0
    std::string s(*_it);
    boost::cmatch matches;
    boost::regex re("(\\\n)(\\d+), (\\d+)");

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract values from string.
        string matchCapacity(matches[2].first, matches[2].second);
        int roomCapacity = atoi(matchCapacity.c_str());

        string matchPenalty(matches[3].first, matches[3].second);
        int penalty = atoi(matchPenalty.c_str());

//        cout << "\tcapacity: " << roomCapacity << endl;
//        cout << "\tpenalty: " << penalty << endl;
//        cout << endl;

        // Create Period instance for keeping period information
        boost::shared_ptr<Room> room(new Room(_roomId, roomCapacity, penalty));
        _roomVector->push_back(room);
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        cin.get();
    }
}



/////////////////////////////////////
// Read constraints and weightings
/////////////////////////////////////

////
/// \brief ITC2007TestSet::readConstraints
/// \param it
/// \param tok
///
void ITC2007TestSet::readConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                     tokenizer<escaped_list_separator<char> > const& tok) {

    //
    // The problem instance files have the following format:
    //
    // Period Related Hard Constraints
    //
    // This section begins with the tag [PeriodHardConstraints] and provides data on conditions which are necessary for a feasible solution.
    // These are EXAM_COINCIDENCE, EXCLUSION, and AFTER.  It should be noted that not all these may be present for any one data set.
    // E.g.
    // 0, EXAM_COINCIDENCE, 1   Exam ‘0' and Exam ‘1' should be timetabled in the same period. If two exams are set associated in
    //                          this manner yet 'clash' with each other due to student enrolment, this hard constraint is ignored.
    // 0, EXCLUSION, 2          Exam ‘0' and Exam ‘2' should be not be timetabled in the same period
    // 0, AFTER, 3              Exam ‘0' should be timetabled after Exam ‘3'

    // Room Related Hard Constraints
    //
    // This section begins with the line [RoomHardConstraints] and provides data on conditions which are necessary for a feasible solution.
    // This is
    // ROOM_EXCLUSIVE.  An exam must be timetabled in a room by itself e.g.
    // 2, ROOM_EXCLUSIVE      Exam ‘2' must be timetabled in a room by itself.

    // Institutional Model Weightings
    //
    // This section begins with the line [InstitutionalWeightings] and
    // provides information on values given to 'global' soft constraints.
    //
    // TWOINAROW, 7
    // TWOINADAY, 5
    // PERIODSPREAD, 3
    // NONMIXEDDURATIONS, 10
    // FRONTLOAD, 100, 30, 5
    ////


    if (it != tok.end()) {
        readPeriodHardConstraints(it, hardConstraints);
        cout << "Finished reading Period hard constraints" << endl;

        readRoomHardConstraints(it, hardConstraints);
        cout << "Finished reading Room hard constraints" << endl;

        // Read Institutional Weightings soft constraints
        readInstitutionalWeightingsSoftConstraints(it, softConstraints);
        cout << "Finished reading Institutional Weightings soft constraints" << endl;
    }

    // Add Soft Room penalty and Soft Period penalty constraints
    boost::shared_ptr<Constraint> roomPenaltysoftConstr(
                new RoomPenaltySoftConstraint()
                );
    softConstraints.push_back(roomPenaltysoftConstr);

    boost::shared_ptr<Constraint> periodPenaltysoftConstr(
                new PeriodPenaltySoftConstraint()
                );
    softConstraints.push_back(periodPenaltysoftConstr);
}


////
/// \brief ITC2007TestSet::readPeriodHardConstraints
/// \param it
/// \param hardConstraints
///
void ITC2007TestSet::readPeriodHardConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                               vector<boost::shared_ptr<Constraint> > &hardConstraints) {
    std::string s(*it);
    boost::cmatch matches;
    // Section begins with the tag [PeriodHardConstraints]
    boost::regex re("(\\\n)(\\[PeriodHardConstraints\\])");
    if (!boost::regex_match(s.c_str(), matches, re))
    {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        // throw exception
        throw runtime_error("No PeriodHardConstraints specified");
    }

    cout << "Read period hard constraints header" << endl;
    ++it; // Proceed to read the next line

    // Read constraints if any.
    // If line starts with a number then is a Period hard constraint
    while (readPeriodConstraint(it, hardConstraints))
        ++it;
}



////
/// \brief ITC2007TestSet::readPeriodConstraint
/// \param it
/// \param hardConstraints
/// \return
///
bool ITC2007TestSet::readPeriodConstraint(tokenizer<escaped_list_separator<char> >::iterator& it,
                                          vector<boost::shared_ptr<Constraint> >& hardConstraints) {
    std::string s(*it);

    boost::cmatch matches;

    boost::regex re("(\\\n)(\\d+), (AFTER|EXAM_COINCIDENCE|EXCLUSION), (\\d+)");

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract values from string.
        // Read Exam 1
        string matchExam1(matches[2].first, matches[2].second);
        int exam1 = atoi(matchExam1.c_str());
        // Read Constraint type
        string constraintType(matches[3].first, matches[3].second);
        // Read Exam 2
        string matchExam2(matches[4].first, matches[4].second);
        int exam2 = atoi(matchExam2.c_str());

//        cout << "\texam1: " << exam1 << endl;
//        cout << "\ttype of constraint: " << constraintType << endl;
//        cout << "\texam2: " << exam2 << endl;
//        cout << endl;

        ///
        /// Improve code generality
        ///

        auto const& examVector = this->getTimetableProblemData()->getExamVector();

        // Period Related Hard Constraints
        if (constraintType == "EXAM_COINCIDENCE") {
            boost::shared_ptr<Constraint> hardConstr(
                        new ExamCoincidenceConstraint(exam1, exam2)
                        );
            hardConstraints.push_back(hardConstr);
            // Insert this hard constraint into each associated exam, 'exam1' and 'exam2'
//            examVector[exam1]->insertPeriodRelatedHardConstraint(hardConstr);
//            examVector[exam2]->insertPeriodRelatedHardConstraint(hardConstr);
        }
        else if (constraintType == "EXCLUSION") {
            boost::shared_ptr<Constraint> hardConstr(
                        new ExamExclusionConstraint(exam1, exam2)
                        );
            hardConstraints.push_back(hardConstr);
            // Insert this hard constraint into each associated exam, 'exam1' and 'exam2'
//            examVector[exam1]->insertPeriodRelatedHardConstraint(hardConstr);
//            examVector[exam2]->insertPeriodRelatedHardConstraint(hardConstr);
        }
        else if (constraintType == "AFTER") {
            boost::shared_ptr<Constraint> hardConstr(
                        new AfterConstraint(exam1, exam2)
                        );
            hardConstraints.push_back(hardConstr);
            // Insert this hard constraint into each associated exam, 'exam1' and 'exam2'
//            examVector[exam1]->insertPeriodRelatedHardConstraint(hardConstr);
//            examVector[exam2]->insertPeriodRelatedHardConstraint(hardConstr);
        }
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        //        cin.get();
        return false; // It couldn't read a period constraint.
        // There are two possibilities: (1) the file format is incorrect,
        // (2) Read the header of Room hard constraint
    }
    return true;
}


/////
/// \brief ITC07TestSet::readRoomHardConstraints
/// \param it
/// \param hardConstraints
///
void ITC2007TestSet::readRoomHardConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                             vector<boost::shared_ptr<Constraint> >& hardConstraints) {
    std::string s(*it);
    boost::cmatch matches;
    // Room Related Hard Constraints
    //
    // This section begins with the line [RoomHardConstraints] and provides data on conditions which are
    // necessary for a feasible solution.
    // This is
    // ROOM_EXCLUSIVE.  An exam must be timetabled in a room by itself e.g.
    // 2, ROOM_EXCLUSIVE      Exam ‘2' must be timetabled in a room by itself.
    boost::regex re("(\\\n)(\\[RoomHardConstraints\\])");
    if (!boost::regex_match(s.c_str(), matches, re))
    {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        // throw exception
        throw runtime_error("No RoomHardConstraints specified");
    }

    cout << "Read room hard constraints header" << endl;
    ++it; // Proceed to read the next line

    // Read constraints if any.
    // If line starts with a number then is a Room hard constraint
    while (readRoomConstraint(it, hardConstraints))
        ++it;
}


/////
/// \brief ITC07TestSet::readRoomConstraint
/// \param it
/// \param hardConstraints
/// \return
///
bool ITC2007TestSet::readRoomConstraint(tokenizer<escaped_list_separator<char> >::iterator& it,
                                        vector<boost::shared_ptr<Constraint> >& hardConstraints) {
    std::string s(*it);
    boost::cmatch matches;
    boost::regex re("(\\\n)(\\d+), (ROOM_EXCLUSIVE)");

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract values from string.
        // Read Exam
        string matchExam(matches[2].first, matches[2].second);
        int exam = atoi(matchExam.c_str());
        // Read Constraint type
        string constraintType(matches[3].first, matches[3].second);

//        cout << "\texam: " << exam << endl;
//        cout << "\ttype of constraint: " << constraintType << endl;
//        cout << endl;

        ///
        /// Improve code generality
        ///
        // Room Related Hard Constraints
        if (constraintType == "ROOM_EXCLUSIVE") {
            boost::shared_ptr<Constraint> hardConstr(
                        new RoomExclusiveConstraint(exam)
                        );
            hardConstraints.push_back(hardConstr);
        }
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        return false; // It couldn't read a room constraint.
        // There are two possibilities: (1) the file format is incorrect,
        // (2) Read the header of InstitutionalWeightings
    }
    return true;
}


////
/// \brief ITC2007TestSet::readInstitutionalWeightingsSoftConstraints
/// \param it
/// \param softConstraints
///
void ITC2007TestSet::readInstitutionalWeightingsSoftConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                                                vector<boost::shared_ptr<Constraint> > &softConstraints) {
    // Institutional Model Weightings
    //
    // This section begins with the line [InstitutionalWeightings] and
    // provides information on values given to 'global' soft constraints.
    //
    // TWOINAROW, 7
    // TWOINADAY, 5
    // PERIODSPREAD, 3
    // NONMIXEDDURATIONS, 10
    // FRONTLOAD, 100, 30, 5
    //
    std::string s(*it);
    boost::cmatch matches;
    // Section begins with the tag [InstitutionalWeightings]
    boost::regex re("(\\\n)(\\[InstitutionalWeightings\\])");
    if (!boost::regex_match(s.c_str(), matches, re))
    {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        // throw exception
        throw runtime_error("No InstitutionalWeightings specified");
    }

    cout << "Read [InstitutionalWeightings] header" << endl;
    ++it; // Proceed to read the next line

    // Read constraints if any.
    while (readInstitutionalWeightingsConstraint(it, softConstraints))
        ++it;
}


////
/// \brief ITC2007TestSet::readInstitutionalWeightingsConstraint
/// \param it
/// \param softConstraints
/// \return
///
bool ITC2007TestSet::readInstitutionalWeightingsConstraint(tokenizer<escaped_list_separator<char> >::iterator& it,
                                                           vector<boost::shared_ptr<Constraint> >& softConstraints) {
    std::string s(*it);
    boost::cmatch matches;

    ///
    /// Improve code generality and regex parsing robustness
    ///

    // E. g.
    // TWOINAROW, 7
    // TWOINADAY, 5
    // PERIODSPREAD, 3
    // NONMIXEDDURATIONS, 10
    // FRONTLOAD, 100, 30, 5
    boost::regex re("(\\\n)(((TWOINAROW|TWOINADAY|PERIODSPREAD|NONMIXEDDURATIONS),(\\s*)(\\d+))|((FRONTLOAD),(\\s*)(\\d+),(\\s*)(\\d+),(\\s*)(\\d+)))");
    // For printing matches structure
    //    if (boost::regex_match(s.c_str(), matches, re)) {
    //        cout << "\tmatches structure:" << endl;
    //        // matches[0] contains the original string.  matches[n]
    //        // contains a sub_match object for each matching
    //        // subexpression
    //        for (int i = 0; i < matches.size(); i++)
    //        {
    //           // sub_match::first and sub_match::second are iterators that
    //           // refer to the first and one past the last chars of the
    //           // matching subexpression
    //           string match(matches[i].first, matches[i].second);
    //           cout << "\tmatches[" << i << "] = " << match << endl;
    //        }
    //    }

    if (boost::regex_match(s.c_str(), matches, re)) {
        // Extract values from string.
        //
        // In the case of the constraints:
        //  TWOINAROW, 7
        //  TWOINADAY, 5
        //  PERIODSPREAD, 3
        //  NONMIXEDDURATIONS, 10
        //
        // matches[4] and matches[6] contain the <constraint type> and <id> fields.
        //
        // In the constraint:
        // FRONTLOAD, 100, 30, 5
        //
        // matches[8], matches[10], matches[12], and matches[14] contain the <constraint type> and <id1>,<id2>,<id3> fields.
        //
        //  Input line containing constraint info
        string inputLine(matches[2].first, matches[2].second);

        ///
        /// TODO - Improve code generality
        ///

        if (inputLine.find("FRONTLOAD") != std::string::npos) {
            // Constraint type
            string constraintType(matches[8].first, matches[8].second);
            // Id1
            string matchId1(matches[10].first, matches[10].second);
            int id1 = atoi(matchId1.c_str());
            // Id2
            string matchId2(matches[12].first, matches[12].second);
            int id2 = atoi(matchId2.c_str());
            // Id3
            string matchId3(matches[14].first, matches[14].second);
            int id3 = atoi(matchId3.c_str());

//            cout << "\ttype of constraint: " << constraintType << endl;
//            cout << "\tid1: " << id1 << endl;
//            cout << "\tid2: " << id2 << endl;
//            cout << "\tid3: " << id3 << endl;
//            cout << endl;

            // FRONTLOAD soft constraint
            if (constraintType == "FRONTLOAD") {
//                cout << "FRONTLOAD READ OK" << endl;
                // First parameter  = number of largest exams. Largest exams are specified by class size
                // Second parameter = number of last periods to take into account
                // Third parameter  = the penalty or weighting
                int numberLargestExams = id1;
                int numberLastPeriods = id2;
                int weightFL = id3;
                boost::shared_ptr<Constraint> softConstr(
                            new FrontLoadSoftConstraint(numberLargestExams, numberLastPeriods, weightFL)
                            );
                softConstraints.push_back(softConstr);
            }
        }
        else {
            // Constraint type
            string constraintType(matches[4].first, matches[4].second);
            // Id
            string matchId(matches[6].first, matches[6].second);
            int id = atoi(matchId.c_str());

//            cout << "\ttype of constraint: " << constraintType << endl;
//            cout << "\tid: " << id << endl;

            // TWOINAROW soft constraint
            if (constraintType == "TWOINAROW") {
//                cout << "TWOINAROW READ OK" << endl;
                int weight2R = id;
                boost::shared_ptr<Constraint> softConstr(
                            new TwoInARowSoftConstraint(weight2R)
                            );
                softConstraints.push_back(softConstr);
            }
            else if (constraintType == "TWOINADAY") { // TWOINADAY soft constraint
//                cout << "TWOINADAY READ OK" << endl;
                int weight2D = id;
                boost::shared_ptr<Constraint> softConstr(
                            new TwoInADaySoftConstraint(weight2D)
                            );
                softConstraints.push_back(softConstr);
            }
            else if (constraintType == "PERIODSPREAD") { // PERIODSPREAD soft constraint
//                cout << "PERIODSPREAD READ OK" << endl;
                int weightPS = id;
                boost::shared_ptr<Constraint> softConstr(
                            new PeriodSpreadSoftConstraint(weightPS)
                            );
                softConstraints.push_back(softConstr);
            }
            else if (constraintType == "NONMIXEDDURATIONS") { // NONMIXEDDURATIONS soft constraint
//                cout << "NONMIXEDDURATIONS READ OK" << endl;
                int weightNMD = id;
                boost::shared_ptr<Constraint> softConstr(
                            new NoMixedDurationsSoftConstraint(weightNMD)
                            );
                softConstraints.push_back(softConstr);
            }
        }
    }
    else {
        cout << "The regexp \"" << re << "\" does not match \"" << s << "\"" << endl;
        return false; // It couldn't read a period constraint.
        // There are two possibilities: (1) the file format is incorrect,
        // (2) Reach the end of file
    }
    return true;
}




*/





