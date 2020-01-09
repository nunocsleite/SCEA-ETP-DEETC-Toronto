#ifndef ITC2007SOLUTIONINITIALISER_H
#define ITC2007SOLUTIONINITIALISER_H


#include "ITC2007TestSet.h"
#include "GraphColouringHeuristics.h"


/// TODO


//// ITC 2007

//template <typename EOT>
//class ITC2007SolutionInitialiser : public eoInit<EOT> {

//public:
//    ITC2007SolutionInitialiser(ITC2007TestSet const& _itc2007TestSet)
//        : itc2007TestSet(_itc2007TestSet) { }

//    virtual void operator()(EOT& _chrom) {
//        bool feasibleSolution;

//        cout << "ITC2007SolutionInitialiser::operator()" << endl;

//        feasibleSolution = GCHeuristicsITC2007<EOT>::saturationDegree(itc2007TestSet, _chrom);


//        if (feasibleSolution)
//            _chrom.setFeasible(true);
//    }

//private:

//    // Instance fields
//    ITC2007TestSet const& itc2007TestSet;
//};

#endif // ITC2007SOLUTIONINITIALISER_H
