#ifndef EOCELLULAREAMATRIX_H
#define EOCELLULAREAMATRIX_H


#include "eoCellularEA.h"


/**
   The cellular evolutionary algorithm - matrix grid.

   @ingroup Algorithms
 */
template <class EOT>
class eoCellularEAMatrix : public eoCellularEA<EOT> {

public :

  /**
     Two constructors
   */

    eoCellularEAMatrix(ofstream & _outFile, int _nrows, int _ncols,
                     double _cp, double _mp, double _ip, moSimpleCoolingSchedule<EOT> const& _coolSchedule,
                     eoContinue <EOT> & _cont, // Stop. criterion
                     eoEvalFunc <EOT> & _eval, // Evaluation function
                     eoSelectOne <EOT> & _sel_neigh, // To choose a partner
                     eoQuadOp <EOT> & _cross, // Cross-over operator
                     eoMonOp <EOT> & _mut, // Mutation operator
                     eoSelectOne <EOT> & _sel_child, /* To choose one from
                                                      the both children */
                     eoSelectOne <EOT> & _sel_repl /* Which to keep between the new
                                                     child and the old individual ? */
                    ) :
        nrows(_nrows), ncols(_ncols),
        eoCellularEA<EOT>(_outFile, _nrows, _ncols, _cp, _mp, _ip, _coolSchedule,
                          _cont, _eval, _sel_neigh, _cross, _mut, _sel_child, _sel_repl)
  { }

    // Neighbouring of the current individual with rank _rank
    virtual eoPop<EOT> neighbours(const eoPop <EOT> & _pop, int _rank) override {

        // Matrix cEA
        int row, col;
        row = _rank / ncols; // Integer division
        col = _rank % ncols;

        eoPop<EOT> neighs;
        // 4-Neighbourhood
        int leftCoords[2]  = { row, col-1 < 0 ? ncols-1 : col-1 };
        int rightCoords[2] = { row, col+1 > ncols-1 ? 0 : col+1 };
        int northCoords[2] = { row-1 < 0 ? nrows-1 : row-1, col };
        int southCoords[2] = { row+1 > nrows-1 ? 0 : row+1, col };

//        cout << "rank = " << _rank << ", row = " << row << ", col = " << col << endl;
//        cout << "nrows = " << nrows << ", ncols = " << ncols << endl;
//        cout << "leftCoords[0]*ncols  + leftCoords[1] = " << (leftCoords[0]*ncols  + leftCoords[1]) << endl;

//        cin.get();

        EOT leftNeigh  = _pop[leftCoords[0]*ncols  + leftCoords[1]];
        EOT rightNeigh = _pop[rightCoords[0]*ncols + rightCoords[1]];
        EOT northNeigh = _pop[northCoords[0]*ncols + northCoords[1]];
        EOT southNeigh = _pop[southCoords[0]*ncols + southCoords[1]];

        neighs.push_back(leftNeigh);
        neighs.push_back(rightNeigh);
        neighs.push_back(northNeigh);
        neighs.push_back(southNeigh);

        return neighs;
    }

private:

    int nrows, ncols;
};



#endif // EOCELLULAREAMATRIX_H
