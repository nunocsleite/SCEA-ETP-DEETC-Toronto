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

//#include "ITC2007SolutionInitialiser.h"
//#include "ETTPneighborhood.h"
#include "ProximityCostEval.h"
#include "base/neighbourhood/ETTPneighborEval.h"
#include "eoETTPEval.h"
#include "base/neighbourhood/ETTPneighbor.h"
#include "TorontoTestSet.h"
#include "eoSCEA.h"
#include "eoSCEAConstrained.h"
#include "base/algorithms/moGDA.h"
//#include "eoCellularEARing.h"
//#include "eoCellularEAMatrix.h"
#include <eoDetSelect.h>
#include "Mutation.h"
#include "Crossover.h"

//#include "eoSimpleGA.h"
#include "eoGenerationContinue.h"


// Handling Ctrl+c signal
#include <signal.h>

bool volatile keepRunning = true;

void intHandler(int dummy=0) {
    keepRunning = false;
}

using namespace std;




// These functions are defined below

//void runHeuristicAlg1(ofstream& outFile, TestSet const& testSet);
//void runHeuristicAlg(ofstream& outFile, TestSet const& testSet);

//void runSCEA(string const& outputDir, TestSet const& testSet);
//void runGDA(ofstream& outFile, TestSet const& testSet);
//void runTA(ofstream& outFile, TestSet const& testSet);
//void runStandardEA(ofstream& outFile, TestSet const& testSet);

// DEETC benchmarks
extern void runDEETCDatasets(string const& outputDir);

// Toronto benchmarks
extern void runTorontoDatasets(int datasetIndex, const string& outputDir);

// ITC 2007 benchmarks
void runITC2007Datasets(int datasetIndex, const string& outputDir);

extern void thresholdTest();


void testMOEA(int datasetIndex, string const& outputDir) {
    // Handling Ctrl+c signal
    signal(SIGINT, intHandler);

//    runDEETCDatasets(outputDir);

    runTorontoDatasets(datasetIndex, outputDir);
//    thresholdTest();

//    runITC2007Datasets(datasetIndex, outputDir);

}




/*

////////////////////////////////////////////////////////
// ITC 2007 benchmarks
//
//
void runITC2007Datasets(int datasetIndex, const string &outputDir)
{
    cout << endl << "Start Date/Time = " << currentDateTime() << endl;
    const clock_t begin_time = clock();


    vector<TestSetDescription> itc2007Benchmarks;
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set1.exam", "ITC2007 Examination Track Dataset 1"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set2.exam", "ITC2007 Examination Track Dataset 2"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set3.exam", "ITC2007 Examination Track Dataset 3"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set4.exam", "ITC2007 Examination Track Dataset 4"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set5.exam", "ITC2007 Examination Track Dataset 5"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set6.exam", "ITC2007 Examination Track Dataset 6"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set7.exam", "ITC2007 Examination Track Dataset 7"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set8.exam", "ITC2007 Examination Track Dataset 8"));
    // Hidden datasets
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set9.exam",  "ITC2007 Examination Track Dataset 9"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set10.exam", "ITC2007 Examination Track Dataset 10"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set11.exam", "ITC2007 Examination Track Dataset 11"));
    itc2007Benchmarks.push_back(TestSetDescription("exam_comp_set12.exam", "ITC2007 Examination Track Dataset 12"));

    /////////////////////////////////////////////////////////////////////////////////////////////////
    copy(itc2007Benchmarks.begin(), itc2007Benchmarks.end(), ostream_iterator<TestSetDescription>(cout, "\n"));

    // ITC 2007 benchmarks
    string rootDir = "./ITC2007";
    // Iterator to test set
    vector<TestSetDescription>::iterator it = itc2007Benchmarks.begin() + datasetIndex;
    // Create ITC07TestSet instance
    ITC2007TestSet itc2007TestSet((*it).getName(), (*it).getDescription(), rootDir);
    // Load dataset
    ITC2007TestSet* ptrITC2007TestSet = &itc2007TestSet;
    ptrITC2007TestSet->load((*it).getName(), rootDir);



    ///
    /// TODO
    ///

    eoChromosomeCapacitated chrom(*itc2007TestSet.getTimetableProblemData());

//    cout << endl << "Evaluating Soft Constraints:" << endl << endl;

//    // Evaluate Soft Constraints
//    auto const& softConstraintPenaltyCalculator = itc2007TestSet.getSoftConstraintValidator();
//    double softPenalty = softConstraintPenaltyCalculator(chrom);
//    cout << "Soft penalty = " << softPenalty << endl;

//    cout << endl << "Evaluating Hard Constraints:" << endl << endl;

//    // Evaluate Hard Constraints
//    auto const& hardConstraintPenaltyCalculator = itc2007TestSet.getHardConstraintValidator();
//    double distanceToFeasibily = hardConstraintPenaltyCalculator(chrom);
//    cout << "Distance to feasibility = " << distanceToFeasibily << endl;


    /// TODO
    /// Exams indexes should start at zero on Toronto and DEETC datasets. Currently, they begin at 1.


    /// Gives exception

//    cout << "timetableProblemData.getNumPeriods() = ";
//    cout << itc2007TestSet.getTimetableProblemData()->getNumPeriods() << endl;

//    TimetableProblemData const* data = itc2007TestSet.getTimetableProblemData();

//    cout << "timetableProblemData.getNumExams() = ";
//    cout << data->getNumExams() << endl;

//    cout << "chrom.getNumPeriods() = " << chrom.getNumPeriods() << endl;


    // Solution initialiser
//    ETTPInit<eoChromosomeCapacitated> init(*itc2007TestSet.getTimetableProblemData());
    ITC2007SolutionInitialiser<eoChromosomeCapacitated> init(itc2007TestSet);
    init(chrom);


//    // Generate initial population
//    eoPop<eoChromosome> pop(_F, init);
//    // Objective function evaluation
//    eoETTPEval proximityCostEval;

    // Run test set
//   runCellularEA(testSet);
//    runSCEA(outputDir, testSet);


    cout << endl << "END Date/Time = " << currentDateTime() << endl;

    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;


    if (chrom.isFeasible()) {
        cout << "Found feasible solution" << endl;
        // Write solution to .sln file
        ofstream slnFile(itc2007TestSet.getRootDirectory() + "/" + itc2007TestSet.getName() + ".sln");
        slnFile << chrom;
    }
    else
        cout << "> No feasible solution was found" << endl;
}
*/





/*

void runSCEA(const string &outputDir, TestSet const& testSet) {
    //
    // SCEA parameters
    //
    const int m = 3;  // m is the number of memeplexes
    const int N = 8;  // N is the number of frogs in each memeplex
    const int q = 8;  // q is the number of frogs in each submemeplex
//    const double up = 0.99;
//    const double up = 0.01; // Uta 3.63 cp=0.2, mp=0, ip=1 Replace worst frog if better
//    const double up = 0.001;
//    const double up = 0.0001;
//    const double up = 0.00001;
//    const double up = 0.000001;
    const double up = 0.0000001; // ECTA 2014

// const double UP = 0.0000001; // Uta 3.05 m = 1, n = 4, q = 4
// const double UP = 0.000001; // Uta 3.23 3.34
// LAST
// const double UP = 0.00001; // Yor 35.05, Uta 3.52, Hec 10.46
// const double UP = 0.0001; // Yor 36.68, Uta 3.61,
// const double UP = 0.001; // Uta 3.86
// const double UP = 0.01; // Uta 3.93 with m = 1, n = 4, q = 4
                        // Uta 3.76 with m = 3, n = 10, q = 10
                        // Uta 3.75 with m = 5, n = 25, q = 20
// const double UP = 0.01; // Hec 10.56

    const int F = m*N; // The total sample size, F, in the swamp is given by F = mN.


    // Number of consecutive time loops
//    int L = 1;
//    int L = 15;
//    int L = 50;
    int L = 100000000;

    // Crossover, mutation and improve probabilities
//    const double cp = 0.6;
//    const double mp = 0.1;

    const double cp = 0.2;
//    const double mp = 1;

//    const double cp = 0;
    const double mp = 0;

    const double ip = 1;

    // Creating the output file
    stringstream filenameStr;
    filenameStr << testSet.getName() << "_m_" << m << "_N_" << N << "_q_" << q
            << "_L_" << L << "_cp_" << cp << "_mp_" << mp << "_ip_" << ip
            << "_up_" << up;

    string filename;
    filenameStr >> filename;
    ofstream outFile(outputDir + filename + ".txt");

    cout << "Start Date/Time = " << currentDateTime() << endl;
    // Write Start time and algorithm parameters to file
    outFile << "Start Date/Time = " << currentDateTime() << endl;
    outFile << "SCEA parameters:" << endl;
    outFile << "m = " << m << ", N = " << N << ", q = " << q << ", L = " << L << endl;
    outFile << "cp = " << cp << ", mp = " << mp << ", ip = " << ip << endl;
    outFile << "GDA parameters:" << endl;
    outFile << "up: " << up << endl;

    cout << "Run SCEA" << endl;

    cout << testSet << endl;
    outFile << testSet << endl;

    // Solution initializer
    ETTPInit<eoChromosome> init(testSet.getData(),
                                *(testSet.getConflictMatrix()), *(testSet.getGraph()));
    // Generate initial population
    eoPop<eoChromosome> pop(F, init);
    // Objective function evaluation
    eoETTPEval eval;

    for (int i = 0; i < pop.size(); ++i)
        eval(pop[i]);

    // Terminate after concluding L time loops or 'Ctrl+C' signal is received
    eoGenerationContinue<eoChromosome> terminator(L);
    eoCheckPoint<eoChromosome> checkpoint(terminator);

    // Crossover and mutation
    Mutation mutation;
    Crossover crossover;

    // Chromosome evolution operator
//    eoSFLAEvolOperator_3<eoChromosome> evolutionOperator; // generic hum...
    eoSFLAEvolOperator_3 evolutionOperator; // generic hum...

    // Build CSEA
    eoSCEA<eoChromosome> scea(outputDir, outFile, filename, m, N, q, F, L, up,
                              cp, mp, ip,
                              init, checkpoint, eval,
                              crossover, mutation, evolutionOperator);

    // Run the algorithm
    scea(pop);

    cout << "End of evolution cycle" << endl
         << "Writing best solution to file..." << endl;

    // Write best solution to file
    ofstream solutionFile;
    string solutionFilename = outputDir + filename + ".sol";
    solutionFile.open(solutionFilename, ios::out | ios::trunc);
    solutionFile << "==============================================================" << endl;
    solutionFile << "Date/Time = " << currentDateTime() << endl;
    solutionFile << scea.getBestFrog().getChromosome() << endl;
    solutionFile << "==============================================================" << endl;
    solutionFile.close();

    cout << "End Date/Time = " << currentDateTime() << endl;

    // Write to file
    outFile << "End Date/Time = " << currentDateTime() << endl;
}



/*
void runGDA(ofstream& outFile, TestSet const& testSet) {

    cout << "Start Date/Time = " << currentDateTime() << endl;
    outFile << "Start Date/Time = " << currentDateTime() << endl;

    cout << "Run GDA" << endl;

    cout << testSet << endl;
    outFile << testSet << endl;

    // Neighborhood
    ETTPneighborhood neighborhood;
    // Full evaluation function
    ProximityCostEval<eoChromosome> fullEval;
    // Neighbor evaluation function
    ETTPneighborEval neighEval;
    //  Choose the rain speed UP ; /∗ UP > 0 ∗/
    //    const double UP = 0.0001; // Kempe swap Ute 25.07
//    const double UP = 0.00001; // Kempe swap Ute 24.98, Simple Kemp 24.92, 24.86
        const double UP = 0.000001; // Simple Kemp 24.85
    //    const double UP = 0.0000001;

    // GDA
    moGDA<ETTPneighbor> gda(neighborhood, fullEval, neighEval, UP);
    // Solution initializer
    ETTPInit<eoChromosome> init(testSet.getData(), *(testSet.getConflictMatrix()), *(testSet.getGraph()));
    // Generate initial population
//    eoPop<eoChromosome> pop(F, init);
    // Objective function evaluation
    eoETTPEval eval;

    eoChromosome sol;
    init(sol);

    while (true)
        gda(sol);


    cout << "Fim" << endl;

    // Print best solution
    outFile << sol.fitness() << endl;
    cout << "Best solution found: " << sol.fitness() << endl;


    cout << "End Date/Time = " << currentDateTime() << endl;
    outFile << "End Date/Time = " << currentDateTime() << endl;
}



void runTA(ofstream& outFile, TestSet const& testSet) {

    cout << "Start Date/Time = " << currentDateTime() << endl;
    outFile << "Start Date/Time = " << currentDateTime() << endl;

    cout << "Run TA" << endl;

    cout << testSet << endl;
    outFile << testSet << endl;

    // Solution initializer
    ETTPInit<eoChromosome> init(testSet.getData(), *(testSet.getConflictMatrix()), *(testSet.getGraph()));
    // Generate initial population
//    eoPop<eoChromosome> pop(F, init);
    // Objective function evaluation
    eoETTPEval eval;

    //================
    // TA algorithm
    //================
    // Neighborhood
    ETTPneighborhood neighborhood;
    // Full evaluation function
    ProximityCostEval<eoChromosome> fullEval;
    // Neighbor evaluation function
    ETTPneighborEval neighEval;
//    double qmax = 1; // Threshold annealing
//    double qmax = 3; // Threshold annealing

//    moSimpleCoolingSchedule<eoChromosome> cool(qmax, 0.1, 5, 0); // qmax=0.2, First = 14.69 to 13.22 +10 h
//    moSimpleCoolingSchedule<eoChromosome> cool(qmax, 0.0001, 5, 0); // qmax=1, FAST, Ute 24.89
//    moSimpleCoolingSchedule<eoChromosome> cool(qmax, 0.00001, 5, 0.0003); // qmax=1, Ute 24.85, Hec 10.33
//    moSimpleCoolingSchedule<eoChromosome> cool(qmax, 0.000001, 2, 0.0003); // qmax=1, Hec 10.28, Ute 24.88
//    moSimpleCoolingSchedule<eoChromosome> cool(qmax, 0.000001, 10, 0.0003); // qmax=3, Hec 10.26

    double qmax = 10; // Threshold annealing
    moSimpleCoolingSchedule<eoChromosome> cool(qmax, 0.00001, 5, 0.0008); // qmax=10, Ute 24.86 Kempe swap



    moTA<ETTPneighbor> ta(neighborhood, fullEval, neighEval, cool);

    eoChromosome sol;
    init(sol);
    ta(sol);

    cout << "Fim" << endl;

    // Print best solution
    outFile << sol.fitness() << endl;
    cout << "Best solution found: " << sol.fitness() << endl;


    cout << "End Date/Time = " << currentDateTime() << endl;
    outFile << "End Date/Time = " << currentDateTime() << endl;
}
*/











