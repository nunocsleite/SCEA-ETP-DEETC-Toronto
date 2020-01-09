#ifndef EXAMMOVESTATISTICS_H
#define EXAMMOVESTATISTICS_H

#include <eo>

#include <iostream>
#include <fstream>
#include <string>

#include "base/algorithms/moSimpleCoolingSchedule.h"
#include "ExamInfo.h"
#include "base/chromosome/eoChromosome.h"
#include "TestSet.h"
#include "eoETTPEval.h"

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/make_shared.hpp>


using namespace std;
using namespace boost;




class ExamMoveStatistics {

public:
    /**
     * @brief ExamMoveStatistics
     * @param _numThresholds
     * @param _coolSchedule
     * @return
     */
    ExamMoveStatistics(TestSet const& _testSet, string const& _outputDir,
                       int _numBins, moSimpleCoolingSchedule<eoChromosome> & _coolSchedule);

    //
    // Public interface
    //
    inline eoChromosome& getInitialSolution();
    inline eoChromosome& getOptimizedSolution();

    void run();
    // Update exame move
    void updateExamMove(int _exam, double _threshold);


    friend ostream& operator<<(ostream& _os, const ExamMoveStatistics& _examMoveStats);

    void printExamMoveCountInfo(ofstream &_moveCountsPerExamFile);


private:
    boost::shared_ptr<string> generateFilename();
    // Determine exams color degree necessary for sorting ExamInfo array by color degree
    void determineExamsColorDegree();
    // Generate initial and optimized solutions
    void generateInitialSolution();
    // Generate thresholds for the specified cooling schedule
    void generateThresholds();
    // Sort ExamInfo array in descending order by exam conflict degree
    void sort();
    // Get index in the threshold array given a threshold
    int getThresholdIndex(double _threshold) const;


    //
    // Fields
    //
    eoETTPEval<eoChromosome> eval;              // Objective function evaluation
    eoChromosome initialSolution;               // Initial solution
    eoChromosome optimizedSolution;             // Optimized solution
    TestSet const& testSet;                     // Test set
    string const& outputDir;                    // Output directory
    //< ExamInfo array. Each examInfo object contains information about exam move counts for each threshold
    vector<boost::shared_ptr<ExamInfo> > examInfoVector;
    //< Colling schedule used to generate the statistics
    moSimpleCoolingSchedule<eoChromosome> & coolSchedule;
    int numBins;                                // Threshold array has # thresholds equal to # of bins + 1
    int thresholdArraySize;
    boost::shared_array<double> thresholdArray; // Threshold array sorted in descending order
//    const double EPSILON_ERROR = 1e-8;          // Error
    string outFilename;                         // Output filename
    ofstream outFile;                           // Output file
};


#endif // EXAMMOVESTATISTICS_H
