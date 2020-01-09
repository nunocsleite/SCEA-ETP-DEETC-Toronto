#ifndef CHROMOSOMECAPACITATED_HPP
#define CHROMOSOMECAPACITATED_HPP


/// TODO
///
///

//// For using ublas matrix (used in chromosome implementation)
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>

//#include "TimetableProblemData.hpp"


//#include <boost/random.hpp>
//#include <vector>
//#include <boost/unordered_set.hpp>
//#include <boost/unordered_map.hpp>

//#include <set>
//#include <cmath>
//#include "Data.h"
//#include "Matrix.h"
//#include "Exam.h"
//#include "Period.h"
//#include "base/Common.h"
//// Armadillo Matrix manipulation library (variance computation)
//#include <armadillo>


//using namespace std;
//using namespace boost;



//// Chromosome (Capacitated) implementation.
//// A chromosome encodes a complete and feasible timetable.
//// Contains a matrix where rows represent rooms and columns represent periods.
//// Each matrix element contains a list of exams to be held in the period and room.
//////
//class ChromosomeCapacitated {

//public:

//    typedef boost::numeric::ublas::matrix<boost::unordered_set<int> > TimetableMatrix;

//    // Constructor
//    ChromosomeCapacitated(TimetableProblemData const& _data)
//        : timetable(nullptr), data(_data), totalPenalty(0), feasible(false) { }

//    // Public interface

//    int getNumPeriods()    const { return data.getNumPeriods();    }
//    int getNumRooms()      const { return data.getNumRooms();      }
//    int getNumStudents()   const { return data.getNumStudents();   }
//    int getNumExams()      const { return data.getNumExams();      }
//    int getNumEnrolments() const { return data.getNumEnrolments(); }
////    unordered_map<int, int> const& getCourseClassSizeUnorderedMap() const { return data.getCourseClassSizeUnorderedMap(); }
//    map<int, int> const& getCourseClassSizeSortedMap() const { return data.getCourseClassSizeSortedMap(); }
//    Matrix const& getConflictMatrix()   const { return data.getConflictMatrix(); }
//    AdjacencyList const& getExamGraph() const { return data.getExamGraph();      }
//    vector<boost::shared_ptr<Exam> > const& getExamVector() const { return data.getExamVector();   }
//    vector<boost::shared_ptr<Room> > const& getRoomVector() const { return data.getRoomVector();   }
//    vector<boost::shared_ptr<itc2007::Period> > const& getPeriodVector() const { return data.getPeriodVector(); }
//    // Get timetable matrix
//    TimetableMatrix& getTimetable() { return *timetable.get(); }
//    TimetableMatrix const& getConstTimetable() const { return *timetable.get(); }
//    // Set timetable matrix
////    void setTimetable(boost::shared_ptr<TimetableMatrix> const& _timetable) { timetable = _timetable; }

//    double getPenalty() const { return totalPenalty; }

/////
///// TODO
/////


////    int getNumStudentsPeriod(int pi) const;
////    bool isFeasiblePeriodExam(int period, int exam) const;
////    double getProximityCostExamPeriod(int exami, int pi) const;


//    // Instantiate chromosome's timetable
//    void createTimetable();


//    bool isFeasible() const;
//    void setFeasible(bool value) { feasible = value; }

//    ChromosomeCapacitated const& getChromosome() const { return *this; }

//    void computeTimetablePenalty();

//    void getFeasibleRoom(int _ei, int _tj, int& _rk);

//    friend ostream& operator<<(ostream& _os, const ChromosomeCapacitated& _chrom);

//protected:
//    // Contains a matrix where rows represent rooms and columns represent periods.
//    // Each matrix element contains a list of exams to be held in the period and room.
//    boost::shared_ptr<TimetableMatrix> timetable;
//    // ITC 2007 Problem data
//    TimetableProblemData const& data;
//    // Timetable total penalty
//    double totalPenalty;
//    // Is feasible solution
//    bool feasible;


//private:
//    //
//    // Private methods
//    //
//    //
//    // Verify ROOM-OCCUPANCY constraint
//    bool verifyRoomOccupancyConstraint(int _ei, int _tj, int _rk) const;
//    // Verify PERIOD-UTILISATION constraint
//    bool verifyPeriodUtilisationConstraint(int _ei, int _tj, int _rk) const;
//    // Verify PERIOD-RELATED constraint
//    bool verifyPeriodRelatedConstraints(int _ei, int _tj, int _rk) const;
//    // Verify ROOM-RELATED constraint
//    bool verifyRoomRelatedConstraints(int _ei, int _tj, int _rk) const;
//};


#endif // CHROMOSOMECAPACITATED_HPP
