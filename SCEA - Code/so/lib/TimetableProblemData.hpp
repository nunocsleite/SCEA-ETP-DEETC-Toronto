#ifndef TIMETABLEPROBLEMDATA_H
#define TIMETABLEPROBLEMDATA_H

#include <vector>
#include <iostream>
#include "Matrix.h"
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include "base/Common.h"
#include "Room.h"
#include "Exam.h"
#include "ITC2007Period.h"


using namespace std;
using namespace boost;


class TimetableProblemData {

public:
    // Constructors
    TimetableProblemData() { }

    TimetableProblemData(int _numPeriods, int _numRooms, int _numStudents, int _numExams, int _numEnrolments,
//                         boost::shared_ptr<unordered_map<int, int> > _courseClassSizeUnorderedMap,
                         boost::shared_ptr<map<int, int> > _courseClassSizeSortedMap,
                         boost::shared_ptr<Matrix> _conflictMatrix,
                         boost::shared_ptr<AdjacencyList> _examGraph,
                         boost::shared_ptr<vector<boost::shared_ptr<Exam> > > _examVector,
                         boost::shared_ptr<vector<boost::shared_ptr<Room> > > _roomVector,
                         boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > > _periodVector)

        : numPeriods(_numPeriods), numRooms(_numRooms), numStudents(_numStudents), numExams(_numExams),
          numEnrolments(_numEnrolments),
//          courseClassSizeUnorderedMap(_courseClassSizeUnorderedMap),
          courseClassSizeSortedMap(_courseClassSizeSortedMap),
          conflictMatrix(_conflictMatrix),
          examGraph(_examGraph),
          examVector(_examVector),
          roomVector(_roomVector),
          periodVector(_periodVector)
    {
        // Compute conflict matrix density
        computeConflictMatrixDensity();

    }

    // Public interface
    //
    // Getters & setters
    int getNumPeriods() const;
    void setNumPeriods(int value);

    int getNumRooms() const;
    void setNumRooms(int value);

    int getNumStudents() const;
    void setNumStudents(int value);

    int getNumExams() const;
    void setNumExams(int value);

    int getNumEnrolments() const;
    void setNumEnrolments(int value);

    double getConflictMatrixDensity() const;
    void setConflictMatrixDensity(double value);

//    const unordered_map<int, int> &getCourseClassSizeUnorderedMap() const;
//    void setCourseClassSizeUnorderedMap(const boost::shared_ptr<unordered_map<int, int> > &value);

    const map<int, int> &getCourseClassSizeSortedMap() const;
    void setCourseClassSizeSortedMap(const boost::shared_ptr<map<int, int> > &value);

    const Matrix &getConflictMatrix() const;
    void setConflictMatrix(const boost::shared_ptr<Matrix> &value);

    const AdjacencyList &getExamGraph() const;
    void setExamGraph(const boost::shared_ptr<AdjacencyList> &value);

    const vector<boost::shared_ptr<Exam> > &getExamVector() const;
    void setExamVector(const boost::shared_ptr<vector<boost::shared_ptr<Exam> > > &value);

    const vector<boost::shared_ptr<Room> > &getRoomVector() const;
    void setRoomVector(const boost::shared_ptr<vector<boost::shared_ptr<Room> > > &value);

    const vector<boost::shared_ptr<itc2007::Period> > &getPeriodVector() const;
    void setPeriodVector(const boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > > &value);

private:

    //--
    // Auxiliary methods
    //--
    void computeConflictMatrixDensity() {
        // Compute conflict matrix density

        // Count the number of non-zero elements
        int nonZeroElements = 0;
        for (auto elem : conflictMatrix->getVec()) {
            if (elem != 0)
                ++nonZeroElements;
        }

        // The ‘conflict’ density is the ratio of the number of non-zero elements
        // in the conflict matrix to the total number of conflict matrix elements.
        double numMatrixElements = conflictMatrix->getCols() * conflictMatrix->getCols();
        conflictMatrixDensity = nonZeroElements / (numMatrixElements - conflictMatrix->getCols());
    }


    //--
    // Fields
    //--
    // Number of Periods
    int numPeriods;
    // Number of Rooms
    int numRooms;
    // Number of students
    int numStudents;
    // Number of exams
    int numExams;
    // Number of enrolments
    int numEnrolments;
    // Conflict matrix density
    double conflictMatrixDensity;

    ///
    /// TODO: Exams index in 0 or 1?
    ///
    // Unordered map to keep course total students. Exams indexed from [1..numExams].
//    boost::shared_ptr<unordered_map<int, int> > courseClassSizeUnorderedMap;

    // Sorted map containing exams sorted by class size and by earliest index.
    // This field is instantiated when evaluating the soft constraints
    boost::shared_ptr<map<int, int> > courseClassSizeSortedMap;
    // Conflict matrix
    boost::shared_ptr<Matrix> conflictMatrix;
    // Graph
    boost::shared_ptr<AdjacencyList> examGraph;
    //--
    // For efficient lookup purposes
    //--
    // Exams vector
    boost::shared_ptr<vector<boost::shared_ptr<Exam> > >examVector;
    // Rooms vector
    boost::shared_ptr<vector<boost::shared_ptr<Room> > >roomVector;
    // Periods vector
    boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > > periodVector;
};


inline int TimetableProblemData::getNumPeriods() const
{
    return numPeriods;
}
inline void TimetableProblemData::setNumPeriods(int value)
{
    numPeriods = value;
}

inline int TimetableProblemData::getNumRooms() const
{
    return numRooms;
}
inline void TimetableProblemData::setNumRooms(int value)
{
    numRooms = value;
}

inline int TimetableProblemData::getNumStudents() const
{
    return numStudents;
}
inline void TimetableProblemData::setNumStudents(int value)
{
    numStudents = value;
}

inline int TimetableProblemData::getNumExams() const
{
    return numExams;
}
inline void TimetableProblemData::setNumExams(int value)
{
    numExams = value;
}

inline int TimetableProblemData::getNumEnrolments() const
{
    return numEnrolments;
}
inline void TimetableProblemData::setNumEnrolments(int value)
{
    numEnrolments = value;
}

inline double TimetableProblemData::getConflictMatrixDensity() const
{
    return conflictMatrixDensity;
}


//inline const unordered_map<int, int> &TimetableProblemData::getCourseClassSizeUnorderedMap() const
//{
//    return *courseClassSizeUnorderedMap.get();
//}
//inline void TimetableProblemData::setCourseClassSizeUnorderedMap(const boost::shared_ptr<unordered_map<int, int> > &value)
//{
//    courseClassSizeUnorderedMap = value;
//}

inline map<int, int> const& TimetableProblemData::getCourseClassSizeSortedMap() const
{
    return *courseClassSizeSortedMap.get();
}
inline void TimetableProblemData::setCourseClassSizeSortedMap(const boost::shared_ptr<map<int, int> > &value)
{
    courseClassSizeSortedMap = value;
}

inline const Matrix &TimetableProblemData::getConflictMatrix() const
{
    return *conflictMatrix.get();
}
inline void TimetableProblemData::setConflictMatrix(const boost::shared_ptr<Matrix> &value)
{
    // Set conflict matrix
    conflictMatrix = value;
    // Compute conflict matrix density
    computeConflictMatrixDensity();
}

inline AdjacencyList const& TimetableProblemData::getExamGraph() const
{
    return *examGraph.get();
}
inline void TimetableProblemData::setExamGraph(const boost::shared_ptr<AdjacencyList> &value)
{
    examGraph = value;
}

inline vector<boost::shared_ptr<Exam> > const& TimetableProblemData::getExamVector() const
{
    return *examVector.get();
}
inline void TimetableProblemData::setExamVector(const boost::shared_ptr<vector<boost::shared_ptr<Exam> > > &value)
{
    examVector = value;
}

inline vector<boost::shared_ptr<Room> > const& TimetableProblemData::getRoomVector() const
{
    return *roomVector.get();
}
inline void TimetableProblemData::setRoomVector(const boost::shared_ptr<vector<boost::shared_ptr<Room> > > &value)
{
    roomVector = value;
}

inline const vector<boost::shared_ptr<itc2007::Period> > &TimetableProblemData::getPeriodVector() const
{
    return *periodVector.get();
}
inline void TimetableProblemData::setPeriodVector(const boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > > &value)
{
    periodVector = value;
}



#endif // TIMETABLEPROBLEMDATA_H











