#ifndef PROXIMITYCOSTEVAL_H
#define PROXIMITYCOSTEVAL_H

#include <eoEvalFunc.h>


// Single-objective (minimize proximity cost) evaluation
// Used in Local Search exploration
template <typename EOT>
class ProximityCostEval : public eoEvalFunc<EOT> {

public:
    void operator () (EOT& _chrom) {

//        chrom.computeProximityCosts(); // shall include this, hum


//        cout << endl << "ProximityCostEval" << endl;

        // Set solution's proximity cost
        _chrom.fitness(_chrom.getProximityCost());
    }
};




#endif // PROXIMITYCOSTEVAL_H
