#ifndef EOCELLULARRINGEA_H
#define EOCELLULARRINGEA_H


#include "eoCellularEA.h"




/**
   The ring cellular evolutionary algorithm.

   @ingroup Algorithms
 */
template <class EOT>
class eoCellularEARing : public eoCellularEA<EOT> {

public :

  /**
     Two constructors
   */

    eoCellularEARing(eoContinue <EOT> & _cont, // Stop. criterion
                     eoEvalFunc <EOT> & _eval, // Evaluation function
                     eoSelectOne <EOT> & _sel_neigh, // To choose a partner
//                      eoBinOp <EOT> & _cross, // Cross-over operator
                     eoQuadOp <EOT> & _cross,
                     eoMonOp <EOT> & _mut, // Mutation operator
                     // ADDED
                     eoSelectOne <EOT> & _sel_child, /* To choose one from
                                                      the both children */
                     eoSelectOne <EOT> & _sel_repl /* Which to keep between the new
                                                     child and the old individual ? */
                    ) :
      eoCellularEA<EOT>(_cont, _eval, _sel_neigh, _cross, _mut, _sel_child, _sel_repl)
  { }

//    eoCellularRingEA (eoContinue <EOT> & _cont,
//                      eoEvalFunc <EOT> & _eval,
//                      eoSelectOne <EOT> & _sel_neigh,
//                      eoQuadOp <EOT> & _cross,
//                      eoMonOp <EOT> & _mut,
//                      eoSelectOne <EOT> & _sel_child, /* To choose one from
//                                                       the both children */
//                      eoSelectOne <EOT> & _sel_repl
//                    ) :
//      eoCellularEA<EOT>(_cont, _eval, _sel_neigh, _cross, _mut, _sel_child, _sel_repl)
//  { }

    // Neighbouring of the current individual with rank _rank
    virtual eoPop<EOT> neighbours (const eoPop <EOT> & _pop, int _rank) override {
// Ring
        eoPop<EOT> neighs;
        int leftNeighIdx = (_rank - 1 < 0) ? _pop.size()-1 : _rank-1;
        EOT leftNeigh = _pop[leftNeighIdx];
        int rightNeighIdx = (_rank + 1) % _pop.size();
        EOT rightNeigh = _pop[rightNeighIdx];

        neighs.push_back(leftNeigh);
        neighs.push_back(rightNeigh);
        return neighs;

     }

};


///**
//   The ring cellular evolutionary algorithm.

//   @ingroup Algorithms
// */
//template <class EOT>
//class eoCellularRingEA_GDA : public eoCellularEA_GDA<EOT> {

//public :

//  /**
//     Two constructors
//   */

//    eoCellularRingEA_GDA(eoContinue <EOT> & _cont, // Stop. criterion
//                     eoEvalFunc <EOT> & _eval, // Evaluation function
//                     eoSelectOne <EOT> & _sel_neigh, // To choose a partner
////                      eoBinOp <EOT> & _cross, // Cross-over operator
//                     eoQuadOp <EOT> & _cross,
//                     eoMonOp <EOT> & _mut, // Mutation operator
//                     // ADDED
//                     eoSelectOne <EOT> & _sel_child, /* To choose one from
//                                                      the both children */
//                     eoSelectOne <EOT> & _sel_repl /* Which to keep between the new
//                                                     child and the old individual ? */
//                    ) :
//      eoCellularEA_GDA<EOT>(_cont, _eval, _sel_neigh, _cross, _mut, _sel_child, _sel_repl)
//  { }

////    eoCellularRingEA (eoContinue <EOT> & _cont,
////                      eoEvalFunc <EOT> & _eval,
////                      eoSelectOne <EOT> & _sel_neigh,
////                      eoQuadOp <EOT> & _cross,
////                      eoMonOp <EOT> & _mut,
////                      eoSelectOne <EOT> & _sel_child, /* To choose one from
////                                                       the both children */
////                      eoSelectOne <EOT> & _sel_repl
////                    ) :
////      eoCellularEA<EOT>(_cont, _eval, _sel_neigh, _cross, _mut, _sel_child, _sel_repl)
////  { }


//    virtual eoPop<EOT> neighbours (const eoPop <EOT> & _pop, int _rank) override {

//        eoPop<EOT> neighs;
//        int leftNeighIdx = (_rank - 1 < 0) ? _pop.size()-1 : _rank-1;
//        EOT leftNeigh = _pop[leftNeighIdx];
//        int rightNeighIdx = (_rank + 1) % _pop.size();
//        EOT rightNeigh = _pop[rightNeighIdx];

//        neighs.push_back(leftNeigh);
//        neighs.push_back(rightNeigh);
//        return neighs;
//    }

//};



#endif // EOCELLULARRINGEA_H
