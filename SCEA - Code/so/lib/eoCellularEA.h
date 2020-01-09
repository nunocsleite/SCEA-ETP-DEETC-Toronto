#ifndef EOCELLULARGA_H
#define EOCELLULARGA_H

#include <eoContinue.h>
#include <eoEvalFunc.h>
#include <eoSelectOne.h>
#include <eoPopEvalFunc.h>
#include <eoAlgo.h>
#include <eoOp.h>

#include "ETTPneighborhood.h"
#include "ProximityCostEval.h"
#include "ETTPneighborEval.h"

#include "moSimpleCoolingSchedule.h"
#include "moSA.h"
#include "moTA.h"
#include "moGDA.h"



// Using boost accumulators framework for computing the variance
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

// I'm importing the accumulators namespace as "a" to make clear which
// elements belong to it
namespace a = boost::accumulators;




/**
   The abstract cellular evolutionary algorithm.

   @ingroup Algorithms
 */
template <class EOT>
class eoCellularEA : public eoAlgo<EOT> {

public :

    /**
     Two constructors
     */

    eoCellularEA(ofstream & _outFile, int _nrows, int _ncols, double _cp, double _mp, double _ip,
                 moSimpleCoolingSchedule<EOT> const& _coolSchedule,
                 eoContinue <EOT> & _cont, // Stop. criterion
                 eoEvalFunc <EOT> & _eval, // Evaluation function
                 eoSelectOne <EOT> & _sel_neigh, // To choose a partner
                 eoQuadOp <EOT> & _cross,
                 eoMonOp<EOT> & _mut, // Mutation operator
                 eoSelectOne <EOT> & _sel_child, /* To choose one from the both children */
                 eoSelectOne<EOT> & _sel_repl /* Which to keep between the new
                                                 child and the old individual ? */
                 ) :
        outFile(_outFile),
        nrows(_nrows), ncols(_ncols),
        cp(_cp), mp(_mp), ip(_ip), coolSchedule(_coolSchedule),
        cont (_cont),
        fullEval(_eval),
        popEval(_eval),
        sel_neigh(_sel_neigh),
        cross(_cross),
        mut(_mut),
        sel_child(_sel_child),
        sel_repl(_sel_repl),
        bestSolution(nullptr),
        popVariance(0)
    { }

    /**
    For a given population.
    */
    void operator() (eoPop<EOT> & _pop) {

        do {
            eoPop<EOT> old_pop;
            for (unsigned i = 0; i < _pop.size(); ++i)
                old_pop.push_back(_pop[i]);

            // Evolve generation
            for (unsigned i = 0; i < _pop.size(); ++i) {
                // Who are neighbouring to the current individual ?
                eoPop<EOT> neigh = neighbours(_pop, i);

                // cout << "Neighbours: " << endl;

                // cout << "_pop[i].fitness() = " << _pop[i].fitness() << endl;


                // To select a partner
                EOT part, old_sol = _pop[i];
                part = sel_neigh(neigh);

                // To perform cross-over
                if (rng.uniform() < cp) {
                    cross(_pop[i], part);
                }
                // To perform mutation
                if (rng.uniform() < mp) {
                    mut(_pop[i]);
                    mut(part);
                }

                _pop[i].invalidate();
                part.invalidate();
                fullEval(_pop[i]);
                fullEval(part);

                //
                // Improvement by Local search
                //
                ETTPneighborhood<ETTPneighborProximityCost> neighborhood;
                ETTPneighborEval<ETTPneighborProximityCost> neighEval;
                ProximityCostEval<eoChromosome> fullEval;

                // -> GOOD
                // moSimpleCoolingSchedule<eoChromosome> cool(0.5, 0.0001, 15, 2e-5); // cool 88, Uta 3.27 cGA + TA -> LAST, 3.39 (only TA)

                // LAST
//                moSimpleCoolingSchedule<eoChromosome> cool(0.1, 0.00001, 5, 2e-5); // Uta 3.13
                // Copy of cool schedule to use in TA solver
                auto cool = coolSchedule;
                moTA<ETTPneighborProximityCost> ta(neighborhood, fullEval, neighEval, cool);

                if (rng.uniform() < ip) {
                    // gda(_pop[i]);
                    // gda(part);
                    // sa(_pop[i]);
                    // sa(part);
                    ta(_pop[i]);
                    ta(part);
                }

                fullEval(_pop[i]);
                fullEval(part);

                // To choose one of the two children ...
                eoPop <EOT> pop_loc;
                pop_loc.push_back(_pop[i]);
                pop_loc.push_back(part);

                _pop[i] = sel_child(pop_loc);

                // To choose only one between the new made child and the old individual
                pop_loc.clear();
                pop_loc.push_back(_pop[i]);
                pop_loc.push_back(old_sol);

                _pop[i] = sel_repl(pop_loc);

                // Syncronous cGA
                eoChromosome aux = old_pop[i];
                old_pop[i] = _pop[i];
                _pop[i] = aux;

            } // End of generation evolution

            for (unsigned i = 0; i < _pop.size (); ++i) {
                _pop[i] = old_pop[i];
                fullEval(_pop[i]);
            }

            // The accumulator set which will calculate the properties for us:
            a::accumulator_set< double, a::stats<a::tag::mean, a::tag::variance> > acc_variance;
            // Compute population variance
            for (unsigned i = 0; i < _pop.size(); ++i)
                acc_variance(_pop[i].fitness());
            // Set variance value
            popVariance = a::variance(acc_variance);


            // Determine the best solution
            for (unsigned i = 0; i < _pop.size(); ++i) {
                if (bestSolution == 0 || _pop[i].fitness() < bestSolution->fitness())
                    bestSolution = &_pop[i];
            }

            // Print population
            cout << endl;
//            for (unsigned i = 0; i < _pop.size(); ++i)
//                cout << _pop[i].fitness() << "\t";

            unsigned k = 0;
            for (int i = 0; i < nrows; ++i) {
                for (int j = 0; j < ncols; ++j, ++k) {
                    cout << _pop[k].fitness() << "\t";
                }
                cout << endl;
            }
            cout << endl << "Date/Time = " << currentDateTime() << ", popVariance = " << popVariance
                 << ", best sol = " << bestSolution->fitness() << endl;

            // Save population information into file
            outFile << endl;
            for (unsigned i = 0; i < _pop.size(); ++i)
                outFile << _pop[i].fitness() << "\t";
            outFile << endl << "Date/Time = " << currentDateTime() << ", popVariance = " << popVariance
                    << ", best sol = " << bestSolution->fitness() << endl;

            // Save best solution to file
            outFile << "==============================================================" << endl;
            outFile << "Date/Time = " << currentDateTime() << endl;
            outFile << getBestSolution()->getChromosome() << endl;
            outFile << "==============================================================" << endl;

        } while (cont(_pop));
    }


    EOT* getBestSolution() { return bestSolution; }

protected :

    virtual eoPop <EOT> neighbours (const eoPop <EOT> & pop, int rank) = 0;

private :

    ofstream & outFile;
    int nrows, ncols;
    double cp, mp, ip;
    moSimpleCoolingSchedule<EOT> const& coolSchedule;
    eoContinue<EOT> & cont;
    eoEvalFunc<EOT> & fullEval;
    eoPopLoopEval<EOT> popEval;
    eoSelectOne<EOT> & sel_neigh;
    eoBF<EOT &, EOT &, bool> & cross;
    eoMonOp<EOT> & mut;
    eoSelectOne<EOT> & sel_child;
    eoSelectOne<EOT> & sel_repl;
    EOT* bestSolution; // Reference to the best solution
    double popVariance; // Population variance
};


template <class EOT>
class eoSelectBestOne : public eoSelectOne<EOT> {

public :
    const EOT & operator () (const eoPop <EOT> & _pop) {
        size_t bestIdx = 0;
        for (unsigned i = 1; i < _pop.size(); ++i) {
            if (_pop[i].fitness() < _pop[bestIdx].fitness()) {
                bestIdx = i;
            }
        }
        return _pop[bestIdx];
    }
};


#endif // EOCELLULARGA_H
