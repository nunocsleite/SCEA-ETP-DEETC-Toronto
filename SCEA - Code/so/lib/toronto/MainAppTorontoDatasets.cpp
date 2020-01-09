#include <eo>

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "ITC2007TestSet.h"
#include "TestSetDescription.h"
#include "Data.h"
#include "ETTPInit.h"

#include "ProximityCostEval.h"
#include "base/neighbourhood/ETTPneighborEval.h"
#include "eoETTPEval.h"
#include "base/neighbourhood/ETTPneighbor.h"
#include "TorontoTestSet.h"
//#include "eoCellularEARing.h"
//#include "eoCellularEAMatrix.h"
#include <eoDetSelect.h>
#include "Mutation.h"
#include "Crossover.h"

//#include "eoSimpleGA.h"
#include "eoGenerationContinue.h"

#include "base/statistics/ExamMoveStatistics.h"


using namespace std;


// These function is defined below
void runCellularEA(TestSet const& testSet);


///////////////// TESTS ////////////////////////////////////////////////////////////////////////////

// Get index in the threshold array given a threshold
int getThresholdIndex(double _threshold, boost::shared_array<double> _thresholdArray, int _numThresholds) {
    const double EPSILON_ERROR = 1e-8;          // Error
    // Threshold array is sorted in descending order. Example: [0.1, 0.01, 0.001, 0.0001, ..., 2e-5]
    if (_threshold > _thresholdArray[0]) // If threshold is greater than the first threshold, print an error
        cerr << "Error: threshold > lower threshold: " << _threshold << " > " << _thresholdArray[0] << endl;

    // Threshold index
    int threshIndex;
    for (threshIndex = 0; threshIndex < _numThresholds-1; ++threshIndex) {
        double upperThresh = _thresholdArray[threshIndex+1]; // Get upper threshold
        cout << "_threshold = " << _threshold << ", upperThresh = " << upperThresh << endl;
        if (_threshold > upperThresh + EPSILON_ERROR)  // If threshold value is greater than the upper threshold stop
            break;
    }
    return threshIndex;
}


void thresholdTest() {
    int numThresholds = 11;
    boost::shared_array<double> thresholdArray(new double[numThresholds]()); // Threshold array sorted in descending order
    double values[] = {
        0.1, // Added, Index 0
        0.0426681,   // 1
        0.0182057,   // 2
        0.007768,    // 3
        0.00331446,  // 4
        0.00141422,  // 5
        0.000603419, // 6
        0.000257467, // 7
        0.000109856, // 8
        4.68736e-05, // 9
        2.00001e-05  // 10
    };
    // Populate array
    for (int i = 0; i < numThresholds; ++i)
        thresholdArray[i] = values[i];

    // Test
    double values1[] = {
        0.1, // Added, Index 0
        0.08,
        0.0426681, // 1
        0.03,
        0.0182057, // 2
        0.01,
        0.007768, // 3
        0.006,
        0.00331446, // 4
        0.003,
        0.002,
        0.00141422, // 5
        0.001,
        0.000603419,// 6
        0.0006,
        0.000257467, // 7
        0.0002,
        0.000109856, // 8
        0.0001,
        4.68736e-05, // 9
        4e-05,
        2.00001e-05, // 10
        1e-05
    };
    int len = sizeof(values) / sizeof(values[0]);
    int len1 = sizeof(values1) / sizeof(values1[0]);
    cout << "len = " << len << ", len1 = " << len1 << endl;
    cout << "Testing values: " << endl;
    for (int i = 0; i < len; ++i)
        cout << "Threshold: " << values[i] << ", index: " << getThresholdIndex(values[i], thresholdArray, numThresholds) << endl;
    cout << endl << "Testing values1: " << endl;
    for (int i = 0; i < len1; ++i)
        cout << "Threshold: " << values1[i] << ", index: " << getThresholdIndex(values1[i], thresholdArray, numThresholds) << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void runTorontoDatasets(int datasetIndex, string const& outputDir) {

    vector<TestSetDescription> torontoTestSet;
    torontoTestSet.push_back(TestSetDescription("car-f-92", "Carleton University", 32));
    torontoTestSet.push_back(TestSetDescription("car-s-91", "Carleton University", 35));
    torontoTestSet.push_back(TestSetDescription("ear-f-83", "Earl Haig Collegiate", 24));
    torontoTestSet.push_back(TestSetDescription("hec-s-92", "Ecole des Hautes Etudes Commerciales", 18));
    torontoTestSet.push_back(TestSetDescription("kfu-s-93", "King Fahd University", 20));
    torontoTestSet.push_back(TestSetDescription("lse-f-91", "London School of Economics", 18));
    torontoTestSet.push_back(TestSetDescription("pur-s-93", "Purdue University", 42));
    torontoTestSet.push_back(TestSetDescription("rye-s-93", "Ryerson University", 23));
    torontoTestSet.push_back(TestSetDescription("sta-f-83", "St. Andrews High school", 13));
    torontoTestSet.push_back(TestSetDescription("tre-s-92", "Trent University", 23));
    torontoTestSet.push_back(TestSetDescription("uta-s-92", "University of Toronto, Arts & Science", 35));
    torontoTestSet.push_back(TestSetDescription("ute-s-92", "University of Toronto, Engineering", 10));
    torontoTestSet.push_back(TestSetDescription("yor-f-83", "York Mills Collegiate", 21));
    /////////////////////////////////////////////////////////////////////////////////////////////////
//    copy(torontoTestSet.begin(), torontoTestSet.end(), ostream_iterator<TestSetDescription>(cout, "\n"));

    // Version I of Toronto benchmarks
    string rootDir = "./Toronto Testprob/Toronto";
    vector<TestSetDescription>::iterator it = torontoTestSet.begin() + datasetIndex;

    // Periods range definition.
    int periods = (*it).getPeriods();
    // MinPeriods, MaxPeriods, NumPeriods
    Data data(periods, periods, periods); // Fixed length timetables
    // Create TestSet instance
    TorontoTestSet testSet((*it).getName(), (*it).getDescription(), data, rootDir);
    // Load dataset
    TorontoTestSet* ptr = &testSet;
    ptr->load((*it).getName(), rootDir);

    // Run test set
//    runCellularEA(testSet);


//    examMoveStatistics(testSet, outputDir);

    ///////////////////////////////////////////////////
    //
    // Generate exam move statistics
    //
    ///////////////////////////////////////////////////

    // Number of thresholds
//    int numBins = 3;
        int numBins = 10;
//    int numThresholds = 10;
//    int numThresholds = 100;
//    int numThresholds = 1000;
    // SA cooling schedule
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.00001, 5, 1e-7);
    // TA cooling schedule
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.99, 3, 2e-5); // Sch #0
//      moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.5, 0.001, 5, 2e-5); // Sch #11
      moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.001, 5, 2e-5); // Sch #1
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.00001, 5, 2e-5); // Uta 3.13, Sch #3
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.5, 0.00001, 5, 2e-5); // Uta 3..., Sch #3.5
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.000001, 5, 2e-5); // Uta 3.03, Sch #4

    ExamMoveStatistics examMoveStats(testSet, outputDir, numBins, coolSchedule);
    examMoveStats.run();
    // Creating the output file containing threshold information
    stringstream sstream;
    sstream << outputDir << "/ExamMoveStatistics_" << testSet.getName() << "_cool_"
            << coolSchedule.initT << "_" << coolSchedule.alpha << "_"
            << coolSchedule.span << "_" << coolSchedule.finalT << "_Thresholds.txt";
    string filename;
    sstream >> filename;
    ofstream thresholdFile(filename);
    // Export to file
    thresholdFile << examMoveStats;

    // Creating the output file containing information of move counts in each threshold per exam
    stringstream sstream2;
    sstream2 << outputDir << "/ExamMoveStatistics_" << testSet.getName() << "_cool_"
            << coolSchedule.initT << "_" << coolSchedule.alpha << "_"
            << coolSchedule.span << "_" << coolSchedule.finalT << "_MoveCountsPerExam.txt";
    string filename2;
    sstream2 >> filename2;
    ofstream moveCountsPerExamFile(filename2);
    // Export to file
    examMoveStats.printExamMoveCountInfo(moveCountsPerExamFile);
    //    moveCountsPerExamFile << examMoveStats;



//   runStandardEA(outFile, testSet);

//  runSCEA(outputDir, testSet);

//   runGDA(outFile, testSet);

//   runTA(outFile, testSet);

}





void runCellularEA(TestSet const& testSet) {
    //
    // cEA parameters
    //
    // LAST
    const int NLINES = 3;
    const int NCOLS = 10;

//    const int NLINES = 5;
//    const int NCOLS = 5;

//    const int NLINES = 5;
//    const int NCOLS = 2;

    const int P = NLINES*NCOLS;  // Population size
    const int L = 5000000; // Number of generations

    // Crossover, mutation and improve probabilities
    const double cp = 0.6;
    const double mp = 0.1;
    const double ip = 0.1;
    // TA parameters
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.99, 3, 2e-5);
//    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.00001, 5, 2e-5); // Uta 3.13
/*    moSimpleCoolingSchedule<eoChromosome> coolSchedule(0.1, 0.000001, 5, 2e-5); // Uta 3.03
*/
    // Creating the output file
    stringstream sstream;
/*    sstream << testSet.getName() << "_NLINES_" << NLINES << "_NCOLS_" << NCOLS
            << "_cp_" << cp << "_mp_" << mp << "_ip_" << ip
            << "_cool_" << coolSchedule.initT << "_" << coolSchedule.alpha << "_"
            << coolSchedule.span << "_" << coolSchedule.finalT << ".txt";
*/
    string filename;
    sstream >> filename;
    ofstream outFile(filename);
/*
    cout << "Start Date/Time = " << currentDateTime() << endl;
    // Write Start time and algorithm parameters to file
    outFile << "Start Date/Time = " << currentDateTime() << endl;
    outFile << "cEA parameters:" << endl;
    outFile << "NLINES = " << NLINES << ", NCOLS = " << NCOLS << endl;
    outFile << "cp = " << cp << ", mp = " << mp << ", ip = " << ip << endl;
    outFile << "TA parameters:" << endl;
    outFile << "cooling schedule: " << coolSchedule.initT << ", " << coolSchedule.alpha << ", "
            << coolSchedule.span << ", " << coolSchedule.finalT << endl;

    cout << "Run CellularEA" << endl;

    cout << testSet << endl;
    outFile << testSet << endl;

    // Solution initializer
    ETTPInit<eoChromosome> init(testSet.getData(),
                                *(testSet.getConflictMatrix()), *(testSet.getGraph()));
    // Generate initial population
    eoPop<eoChromosome> pop(P, init);
    // Objective function evaluation
    eoETTPEval eval;

    for (int i = 0; i < pop.size(); ++i)
        eval(pop[i]);

    // Terminate after concluding L time loops or 'Ctrl+C' signal is received
    eoGenerationContinue<eoChromosome> terminator(L);
    eoCheckPoint<eoChromosome> checkpoint(terminator);

    // Build CellularEA

//    eoCellularRingEA (eoContinue <EOT> & _cont,
//                      eoEvalFunc <EOT> & _eval,
//                      eoSelectOne <EOT> & _sel_neigh,
//                      eoQuadOp <EOT> & _cross,
//                      eoMonOp <EOT> & _mut,
//                      eoSelectOne <EOT> & _sel_child, // To choose one from
//                                                      // the both children
//                      eoSelectOne <EOT> & _sel_repl
//                    )

    // Declare 1-selectors
    eoDetTournamentSelect<eoChromosome> detSelectNeighbour;
    // Crossover and mutation
    Mutation mutation;
    Crossover crossover;
    eoSelectBestOne<eoChromosome> selectBestOne;

//    eoCellularEARing<eoChromosome> cEA(checkpoint, eval, detSelectNeighbour,
//                      crossover, mutation,
//                     selectBestOne,
//                     selectBestOne
//                    );

    eoCellularEAMatrix<eoChromosome> cEA(outFile, NLINES, NCOLS,
                                         cp, mp, ip, coolSchedule,
                                         checkpoint, eval, detSelectNeighbour,
//                                         checkpoint, eval, selectBestOne, /// TODO Use this one? See the difference
                                         crossover, mutation,
                                         selectBestOne,
                                         selectBestOne
                                       );

    // Run the algorithm
    cEA(pop);

    cout << "End of evolution cycle" << endl
         << "Writing best solution to file..." << endl;

    // Write best solution to file
    outFile << "==============================================================" << endl;
    outFile << "Date/Time = " << currentDateTime() << endl;
    outFile << cEA.getBestSolution()->getChromosome() << endl;
    outFile << "==============================================================" << endl;
*/
    cout << "End Date/Time = " << currentDateTime() << endl;

    // Write to file
    outFile << "End Date/Time = " << currentDateTime() << endl;
}




/*

void runStandardEA(ofstream& outFile, TestSet const& testSet) {

    cout << "Start Date/Time = " << currentDateTime() << endl;
    outFile << "Start Date/Time = " << currentDateTime() << endl;

    cout << "Run Standard EA Memetic" << endl;

    cout << testSet << endl;
    outFile << testSet << endl;


    const int NLINES = 3;
    const int NCOLS = 10;

    const int P = NLINES*NCOLS;  // Population size

    const int L = 5000000; // Number of generations

    // Solution initializer
    ETTPInit<eoChromosome> init(testSet.getData(),
                                *(testSet.getConflictMatrix()), *(testSet.getGraph()));
    // Generate initial population
    eoPop<eoChromosome> pop(P, init);
    // Objective function evaluation
    eoETTPEval eval;
    // Timetable packing and Continuation
//    eoRepair<eoChromosome> repair(pop);
//    eoRepair<eoChromosome> repair(pop, init);

//    cout << pop << endl;

    for (int i = 0; i < pop.size (); ++i)
        eval(pop[i]);

//    cin.get();


    eoGenContinue<eoChromosome> terminator(L); // Terminate after concluding L time loops
    eoCheckPoint<eoChromosome> checkpoint(terminator);


//    // Declare 1-selectors
//    eoDetTournamentSelect<eoChromosome> detSelectNeighbour;
//    eoSelectBestOne<eoChromosome> selectBestOne;
//    eoSelectFirstOne<eoChromosome> selFirstOne;

//    eoCellularEAMatrix<eoChromosome> cEA(NLINES, NCOLS,
//                                        checkpoint, eval, detSelectNeighbour,
//                                        crossover, mutation,
//                                        selectBestOne,
//                                        selectBestOne
//                                       );



    // Crossover and mutation
    Crossover crossover;
    Mutation mutation;
    const double crossProb = 0.6;
    const double mutProb = 0.1;
    // Breeding
//    eoSGATransform<eoChromosome> transform(crossover, crossProb, mutation, mutProb);
    // Selection
    // Declare 1-selectors
    eoDetTournamentSelect<eoChromosome> detSelectNeighbour;


    // GA generation
//    eoEasyEA<Chrom> standardEA(lottery, breeder, inclusion, eval, term);
    // Constructor used:
    // eoContinue<EOT>& _continuator, eoPopEvalFunc<EOT>& _eval, eoSelect<EOT>& _select, eoTransform<EOT>& _transform,
    // eoReplacement<EOT>& _replace
//    eoEasyEA<eoChromosome> standardEA(//continuator/checkpoint, eval, select, transform, replace);

//    eoSGA(
//           eoSelectOne<EOT>& _select,
//           eoQuadraticOp<EOT>& _cross, float _crate,
//           eoMonOp<EOT>& _mutate, float _mrate,
//           eoEvalFunc<EOT>& _eval,
//           eoContinue<EOT>& _cont)
    eoSimpleGA<eoChromosome> standardEA(detSelectNeighbour, crossover, crossProb, mutation, mutProb, eval, checkpoint);

    // Evolution
    standardEA(pop);


    cout << "Fim" << endl;

    //    outFile << sfla.getBestFrog().fitness() << " - " << sfla.getBestFrog().getNumPeriods() << endl;

    // Print best frog
//    outFile << csea.getBestFrog().getChromosome() << endl;

//    pop.printOn(cout);
//    cout << endl;

    cout << "End Date/Time = " << currentDateTime() << endl;
    outFile << "End Date/Time = " << currentDateTime() << endl;

    //    cin.get();


}
*/


