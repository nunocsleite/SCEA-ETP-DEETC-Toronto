#ifndef ETTPNEIGHBOREVAL_H
#define ETTPNEIGHBOREVAL_H

#include <eval/moEval.h>
#include "base/neighbourhood/ETTPneighbor.h"
#include <eoEvalFunc.h>
#include "base/kempeChain/ETTPKempeChain.h"


/**
 * @brief Evaluation function used to evaluate the neighbour solution
 */
template <typename EOT>
class ETTPneighborEval : public moEval<ETTPneighbor<EOT> > {

public:

    /**
     * @brief operator () Eval the _solution moved with the neighbor and stock the result in the neighbor
     * @param _solution The current solution
     * @param _neighbor The neighbour solution. The neigbour doesn't contain the timetable data, it only
     *                  contains the Kempe chain information from which the neighbour solution can be built.
     */
    virtual void operator()(typename ETTPneighbor<EOT>::EOT &_solution, ETTPneighbor<EOT> &_neighbor) {

//        cout << endl << "ETTPneighborEval" << endl;

        //====================================================
        //
        // Incremental evaluation of the neighbour solution
        //
        //====================================================
        double neighFitness;
        // Obtain the Kempe chain object
        ETTPKempeChain const& kempeChain = _neighbor.getKempeChain();

        neighFitness =
        // Set neighbor fitness
        _neighbor.fitness(neighFitness);

     }

protected:

    /**
     * @brief eval Evaluation function used to eval the neighbour solution
     */
    eoEvalFunc<EOT> &eval;

};


#endif // ETTPNEIGHBOREVAL_H
