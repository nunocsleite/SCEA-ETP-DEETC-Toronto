#ifndef ITC2007CONSTRAINTS_H
#define ITC2007CONSTRAINTS_H




/// TODO



//#include "base/chromosome/eoChromosomeCapacitated.hpp"
//#include "Exam.h"
//#include "Room.h"
//#include "Matrix.h"
//#include <boost/shared_ptr.hpp>

//#include "Constraint.hpp"




//////////////////////////////////////////////////////////////////////////////
////
//// Hard constraints
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
//// NO-CONFLICTS : Conflicting exams cannot be assigned to the same period. (As usual,
////   two exams are said to conflict whenever they have some student taking them both.)
//// ROOM-OCCUPANCY : For every room and period no more seats are used than are available
////   for that room.
//// PERIOD-UTILISATION : No exam assigned to a period uses more time than available for
////   that period.
//// PERIOD-RELATED : All of a set of time-ordering requirements between pairs of exams
////   are obeyed. Specifically, for any pair (e1, e2) of exams, one can specify any of:
////   - ‘AFTER’: e1 must take place strictly after e2 ,
////   - ‘EXAM_COINCIDENCE’: e1 must take place at the same time as e2 ,
////   - ‘EXCLUSION’: e1 must not take place at the same time as e2 .
//// ROOM-RELATED : Room requirements are obeyed. Specifically, for any exam one can
////   disallow the usual sharing of rooms and specify
////   - ‘EXCLUSIVE’: Exam e must take place in a room on its own.
//////////////////////////////////////////////////////////////////////////////




//// E.g.
//// [PeriodHardConstraints]
//// 0, AFTER, 3           Exam ‘0' should be timetabled after Exam ‘3'
//class AfterConstraint : public BinaryConstraint {
//public:
//    // Constructor
//    // Pre-cond: exams indexes e1 and e2 in [0, size-1]
//    // Exams must be scheduled
//    AfterConstraint(int _e1, int _e2)
////        : e1(_e1), e2(_e2) { }
//        : BinaryConstraint(_e1, _e2) { }

//    double operator()(ChromosomeCapacitated const& _chrom) const override {
////        cout << "[AfterConstraint] e1 = " << e1 << ", e2 = " << e2 << endl;
//        cout << "[AfterConstraint] e1 = " << getE1() << ", e2 = " << getE2() << endl;


//        // Get exams references
//        vector<boost::shared_ptr<Exam> > const& examVec = _chrom.getExamVector();
////        Exam const& exam1 = *examVec[e1].get();
////        Exam const& exam2 = *examVec[e2].get();
//        Exam const& exam1 = *examVec[getE1()].get();
//        Exam const& exam2 = *examVec[getE2()].get();

//        // If exam1 is scheduled after exam2 then return penalty = 0, else return penalty = 1
//        double penalty = (exam1.getPeriod() > exam2.getPeriod()) ? 0 : 1;

////        double penalty = 0;

//        return penalty;
//    }

//private:
////    int e1, e2; // Exams indexes
//};



//// E.g.
//// [PeriodHardConstraints]
//// 0, EXAM_COINCIDENCE, 1   Exam ‘0' and Exam ‘1' should be timetabled in the same period. If two exams are set associated in
////                          this manner yet 'clash' with each other due to student enrolment, this hard constraint is ignored.
//class ExamCoincidenceConstraint : public BinaryConstraint {
//public:
//    // Constructor
//    // Pre-cond: exams indexes e1 and e2 in [0, size-1]
//    // Exams must be scheduled
//    ExamCoincidenceConstraint(int _e1, int _e2)
////        : e1(_e1), e2(_e2) { }
//        : BinaryConstraint(_e1, _e2) { }

//     double operator()(ChromosomeCapacitated const& _chrom) const override {
////        cout << "[ExamCoincidenceConstraint] e1 = " << e1 << ", e2 = " << e2 << endl;
//        cout << "[ExamCoincidenceConstraint] e1 = " << getE1() << ", e2 = " << getE2() << endl;

//        // Get exams references
//        vector<boost::shared_ptr<Exam> > const& examVec = _chrom.getExamVector();
////        Exam const& exam1 = *examVec[e1].get();
////        Exam const& exam2 = *examVec[e2].get();
//        Exam const& exam1 = *examVec[getE1()].get();
//        Exam const& exam2 = *examVec[getE2()].get();

//        Matrix const& conflictMatrix = _chrom.getConflictMatrix();
//        // if exam1 and exam2 have not conflicts then they should be scheduled on the same period
//        // return true if exams clash with each other (ignoring the constraint)
//        // or if exams don't clash and are scheduled in the same period. Return false otherwise
//        if (conflictMatrix.getVal(getE1(), getE2()) > 0)
//            return 0;

//        // Then conflictMatrix.getVal(e1, e2) == 0
//        double penalty = (exam1.getPeriod() == exam2.getPeriod()) ? 0 : 1;

////        double penalty = 0;

//        return penalty;
//    }

//private:
////    int e1, e2; // Exams indexes
//};



//// E.g.
//// [PeriodHardConstraints]
//// 0, EXCLUSION, 2       Exam ‘0' and Exam ‘2' should be not be timetabled in the same period
//class ExamExclusionConstraint : public BinaryConstraint {
//public:
//    // Constructor
//    // Pre-cond: exams indexes e1 and e2 in [0, size-1]
//    // Exams must be scheduled
//    ExamExclusionConstraint(int _e1, int _e2)
////        : e1(_e1), e2(_e2) { }
//        : BinaryConstraint(_e1, _e2) { }

//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[ExamExclusionConstraint] e1 = " << getE1() << ", e2 = " << getE2() << endl;

//        // Get exams references
//        vector<boost::shared_ptr<Exam> > const& examVec = _chrom.getExamVector();
////        Exam const& exam1 = *examVec[e1].get();
////        Exam const& exam2 = *examVec[e2].get();
//        Exam const& exam1 = *examVec[getE1()].get();
//        Exam const& exam2 = *examVec[getE2()].get();

//        // if exam1 is scheduled in a different period than exam2 then return penalty = 0, else return penalty = 1
//        double penalty = (exam1.getPeriod() != exam2.getPeriod()) ? 0 : 1;

//        cout << "exam1.getPeriod() = " << exam1.getPeriod() << ", exam2.getPeriod() = " << exam2.getPeriod()
//             << ", distance to feasibility = " << penalty << endl;

//        return penalty;

//    }

//private:
////    int e1, e2; // Exams indexes
//};



//// E.g.
//// [RoomHardConstraints]
//// 2, ROOM_EXCLUSIVE      Exam ‘2' must be timetabled in a room by itself.
//class RoomExclusiveConstraint : public UnaryConstraint {
//public:
//    // Constructor
//    // Pre-cond: exam index e and room index in [0, size-1]
//    // Exam must be scheduled
//    RoomExclusiveConstraint(int _e)
////        : e(_e) { }
//        : UnaryConstraint(_e) { }

//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[RoomExclusiveConstraint] e = " << getE() << endl;

//        // Get exam reference
//        vector<boost::shared_ptr<Exam> > const& examVec = _chrom.getExamVector();
////        Exam const& exam = *examVec[e].get();
//        Exam const& exam = *examVec[getE()].get();
//        // If exam is scheduled in a room by itself then return true, else return false
//        vector<boost::shared_ptr<Room> > const& roomVec = _chrom.getRoomVector();
//        Room const& room = *roomVec[exam.getRoom()].get();
//        // Return true if this room only has exam 'e' timetabled in it
//        double penalty = (room.getNumExamsScheduled() == 1) ? 0 : 1;

////        double penalty = 0;

//        return penalty;

//    }

//private:
////     int e; // Exam index
//};





//////////////////////////////////////////////////////////////////////////////
////
//// Soft constraints
////
//// See http://www.cs.qub.ac.uk/itc2007/examtrack/exam_track_index_files/examevaluation.htm
//// and McCollum's et al. Ann Oper Res 2012 article
////
//////////////////////////////////////////////////////////////////////////////


//// 1. Two exams in a row
////
//// This calculation considers the number of occurrences where two examinations are taken by
//// students one straight after another, i.e. back to back, and on the same day. Once this has been
//// established, the number of students are summed and multiplied by the number provided in
//// the ‘two in a row’ weighting within the ‘Institutional Model Index’. Note that if a student
//// has an exam in the last period of one day and another the first period the next day, this does
//// not incur a two in a row penalty. (See Sect. 4.9.1.)
//class TwoInARowSoftConstraint : public Constraint {
//public:
//    // Constructor
//    TwoInARowSoftConstraint(int _weight2R)
//        : weight2R(_weight2R) { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[TwoInARowSoftConstraint] weight2R = " << weight2R << endl;
//        ///
//        /// TODO
//        ///
//        ///

//        double penalty = 0;

//        return penalty;
//    }

//private:
//    int weight2R;
//};



//// 2. Two exams in a day
////
//// In the case where there are three periods or more in a day, the number of occurrences of
//// students having two exams in a day which are not directly adjacent, i.e. not back to back,
//// are calculated. The total number is subsequently multiplied by the ‘two in a day’ weighting
//// provided within the ‘Institutional Model Index’. Therefore, two exams in a day are consid-
//// ered as those which are not adjacent i.e. they have at least a free period between them. This
//// is done to ensure a particular exam placing within a solution does not contribute twice to
//// the overall penalty. For example, if two exams were in adjacent periods in the same day,
//// the penalty would be counted only as part of the ‘Two exams in a row penalty’. It should
//// be noted that where the examination session contains days with 2 periods, this component
//// of the penalty, although present for continuity, always is zero and hence superfluous. (See
//// Sect. 4.9.2.)
//class TwoInADaySoftConstraint : public Constraint {
//public:
//    // Constructor
//    TwoInADaySoftConstraint(int _weight2D)
//        : weight2D(_weight2D) { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[TwoInADaySoftConstraint] weight2D = " << weight2D << endl;
//        ///
//        /// TODO
//        ///

//        double penalty = 0;

//        return penalty;

//    }

//private:
//    int weight2D;
//};



//// 3. Period spread
////
//// This soft constraint enables an organisation to ‘spread’ an individual’s examinations over
//// a specified number of periods. This can be thought of as an extension of the two soft con-
//// straints previously described. Within the ‘Institutional Model Index’, a figure is provided
//// (with the “PERIODSPREAD” keyword) relating to how many periods the solution should
//// be ‘spread’ over. The higher this figure, potentially the better the spread of examinations
//// for individual students. In the authors’ commercial experience, constructing solutions while
//// changing this setting has led to timetables with which the institution is much more satisfied.
//// If, for example, PERIODSPREAD within the ‘Institutional Model Index’ is set at 7, for each
//// exam we count all the occurrences of enrolled students who have to sit other exams after-
//// wards but within 7 periods i.e. the desired period spread. This total is added to the overall
//// penalty. It should be noted that the occurrences here will have contributed to the penalty
//// calculated for the ‘two exams in a row’ and ‘two exams in a day’ penalties. Although, a
//// single occurrence within the solution is effectively penalised twice, it is often necessary due
//// to, as indicated above, many institutions requiring certain spreads to be minimised as an
//// indication of solution quality. (See Sect. 4.9.3.)
//class PeriodSpreadSoftConstraint : public Constraint {
//public:
//    // Constructor
//    PeriodSpreadSoftConstraint(int _weightPS)
//        : weightPS(_weightPS) { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[PeriodSpreadSoftConstraint] weightPS = " << weightPS << endl;
//        ///
//        /// TODO
//        ///

//        double penalty = 0;

//        return penalty;

//    }

//private:
//    int weightPS;
//};



//// 4. No mixed durations
////
//// This applies a penalty to a Room and Period (not Exam) where there are mixed durations.
//// The intention here is to try and ensure that exams occur together which are of equal duration.
//// In calculating this portion of the penalty, the mixed duration component of the ‘Institutional
//// Model Index’ is calculated by the number of violations detected. (See Sect. 4.9.4.)
//class NoMixedDurationsSoftConstraint : public Constraint {
//public:
//    // Constructor
//    NoMixedDurationsSoftConstraint(int _weightNMD)
//        : weightNMD(_weightNMD) { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[NoMixedDurationsSoftConstraint] weightNMD = " << weightNMD << endl;
//        ///
//        /// TODO
//        ///

//        double penalty = 0;

//        return penalty;

//    }

//private:
//    int weightNMD;
//};



//// 5. Front load
////
//// It is often desirable that examinations with the largest numbers of students are timetabled
//// at the beginning of the examination session. In order to take account of this the “FRONT-
//// LOAD” expression is introduced. Within the ‘Institutional Model Index’ the FRONTLOAD
//// expression has three parameters e.g. (100, 30, 5). The first of these is the number of largest
//// exams that are to be considered. Largest exams are specified by class size. If there are ties
//// by size then exams occurring first in the data file are chosen. The second parameter is the
//// number of last periods to take into account and which should be ideally avoided by the large
//// exams. The third parameter is the penalty or weighting that should be added each time the
//// soft constraint is violated. This allows the institution to attempt to ensure that larger exams
//// occur earlier in the examination session. This constraint is very popular in practice as exams
//// with more students enrolled take longer to mark. (See Sect. 4.9.5.)
//class FrontLoadSoftConstraint : public Constraint {
//public:
//    // Constructor
//    // First parameter  = number of largest exams. Largest exams are specified by class size
//    // Second parameter = number of last periods to take into account
//    // Third parameter  = the penalty or weighting
//    FrontLoadSoftConstraint(int _numberLargestExams, int _numberLastPeriods, int _weightFL)
//        : numberLargestExams(_numberLargestExams), numberLastPeriods(_numberLastPeriods),
//          weightFL(_weightFL) { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[FrontLoadSoftConstraint] numberLargestExams = " << numberLargestExams
//             << ", numberLastPeriods = " << numberLastPeriods << ", weightFL = " << weightFL << endl;

//        ///
//        /// TODO
//        ///

//        double penalty = 0;

//        return penalty;

//    }

//private:
//    int numberLargestExams, numberLastPeriods, weightFL;
//};



//// 6. Soft room penalty
////
//// Organisations often want to keep usage of certain rooms to a minimum. As with the ‘Mixed
//// Durations’ component of the overall penalty, this part of the overall penalty should be calcu-
//// lated on a period by period basis. For each period, if a room used within the solution has an
//// associated penalty, then the penalty for that room for that period is calculated by multiplying
//// the associated penalty by the number of exams using that room. (See Sect. 4.9.6.)
//class RoomPenaltySoftConstraint : public Constraint {
//public:
//    // Constructor
//    RoomPenaltySoftConstraint() { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[RoomPenaltySoftConstraint]" << endl;
//        ///
//        /// TODO
//        ///

//        double penalty = 0;

//        return penalty;

//    }

//private:

//};



//// 7. Soft period penalty
////
//// Organisations often want to keep usage of certain time periods to a minimum. As with
//// the ‘Mixed Durations’ and the ‘Room Penalty’ components of the overall penalty, this part
//// of the overall penalty should be calculated on a period by period basis. For each period,
//// the penalty is calculated by multiplying the associated penalty by the number of exams
//// timetabled within that period. (See Sect. 4.9.7.)
//// These constraints are relatively complex, and certainly more complicated than those in
//// previous models. To reduce potential ambiguities due to the above natural language descrip-
//// tion, in the next section, we provide mathematical programming definitions.
//class PeriodPenaltySoftConstraint : public Constraint {
//public:
//    // Constructor
//    PeriodPenaltySoftConstraint() { }

//    // Compute constraint cost = penalty x weight
//    double operator()(ChromosomeCapacitated const& _chrom) const override {
//        cout << "[PeriodPenaltySoftConstraint]" << endl;
//        ///
//        /// TODO
//        ///

//        double penalty = 0;

//        return penalty;

//    }

//private:

//};





#endif // ITC2007CONSTRAINTS_H
