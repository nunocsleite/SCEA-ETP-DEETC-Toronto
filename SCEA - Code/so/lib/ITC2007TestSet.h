#ifndef ITC07TESTSET_H
#define ITC07TESTSET_H

#include "ITC2007Constraints.hpp"
#include "TestSet.h"
#include <string>
#include "DateTime.h"
#include "Exam.h"
#include "Period.h"
#include "ITC2007Period.h"

#include "ConstraintValidator.hpp"


using namespace std;

/*

class ITC2007TestSet : public TestSet {

public:
    // Constructor
    ITC2007TestSet(string _testSetName, string _description, string _rootDir)
        : TestSet(_testSetName, _description, _rootDir, boost::shared_ptr<TimetableProblemData>(new TimetableProblemData()))
    {

        cout << "ITC07TestSet ctor" << endl;

        // After creating the instance, the caller should invoke the load method
    }


public:
    // Overriden method
    void load(string _testSetName, string _rootDir);

//    ConstraintValidator const& getSoftConstraintValidator() const { return softConstraintValidator; }
//    ConstraintValidator const& getHardConstraintValidator() const { return hardConstraintValidator; }

    vector<boost::shared_ptr<Constraint> > const& getHardConstraints() const { return hardConstraints; }
    vector<boost::shared_ptr<Constraint> > const& getSoftConstraints() const { return softConstraints; }

private:
    // Read exams and students
    void readExams(tokenizer<escaped_list_separator<char> >::iterator& it,
                   tokenizer<escaped_list_separator<char> > const& tok);
    // Read periods
    void readPeriods(tokenizer<escaped_list_separator<char> >::iterator& it,
                     tokenizer<escaped_list_separator<char> > const& tok);
    // Read rooms
    void readRooms(tokenizer<escaped_list_separator<char> >::iterator& it,
                   tokenizer<escaped_list_separator<char> > const& tok);
    // Read constraints and weightings
    void readConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                         tokenizer<escaped_list_separator<char> > const& tok);


    ///////////////////////////
    // Auxiliary methods
    ///////////////////////////
    int matchPeriods(tokenizer<escaped_list_separator<char> >::iterator& it);
    int matchPeriodSequenceLine(int _periodId, tokenizer<escaped_list_separator<char> >::iterator& _it,
                                boost::shared_ptr<vector<boost::shared_ptr<itc2007::Period> > > &_periodVector);

    int matchRooms(tokenizer<escaped_list_separator<char> >::iterator& it);
    int matchRoomSequenceLine(int _roomId, tokenizer<escaped_list_separator<char> >::iterator& _it,
                              boost::shared_ptr<vector<boost::shared_ptr<Room> > > &_roomVector);

    void readPeriodHardConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                   vector<boost::shared_ptr<Constraint> > &hardConstraints);
    bool readPeriodConstraint(tokenizer<escaped_list_separator<char> >::iterator& it,
                              vector<boost::shared_ptr<Constraint> >& hardConstraints);

    void readRoomHardConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                  vector<boost::shared_ptr<Constraint> >& hardConstraints);
    bool readRoomConstraint(tokenizer<escaped_list_separator<char> >::iterator& it,
                            vector<boost::shared_ptr<Constraint> >& hardConstraints);

    void readInstitutionalWeightingsSoftConstraints(tokenizer<escaped_list_separator<char> >::iterator& it,
                                                 vector<boost::shared_ptr<Constraint> > &softConstraints);
    bool readInstitutionalWeightingsConstraint(tokenizer<escaped_list_separator<char> >::iterator& it,
                                                 vector<boost::shared_ptr<Constraint> > &softConstraints);

    void buildConflictMatrix(tokenizer<escaped_list_separator<char> >::iterator &it,
                             const tokenizer<escaped_list_separator<char> > &tok,
                             boost::shared_ptr<vector<boost::shared_ptr<Exam> > > &examVector);

    void buildExamGraph(const Matrix &conflictMatrix);


private:
    // Fields

    // Hard and Soft constraints
    vector<boost::shared_ptr<Constraint> > hardConstraints;
    vector<boost::shared_ptr<Constraint> > softConstraints;

//    // Timetable problem data
//    ConstraintValidator softConstraintValidator;
//    ConstraintValidator hardConstraintValidator;
};

*/
#endif // ITC07TESTSET_H
