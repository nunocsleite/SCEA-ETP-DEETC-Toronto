#ifndef EOCHROMOSOMECAPACITATED_H
#define EOCHROMOSOMECAPACITATED_H

/// TODO

//#include "ChromosomeCapacitated.hpp"
//#include <EO.h>


////// EO Chromosome (Capacitated) implementation.
////class eoChromosomeCapacitated : public EO<double>, public ChromosomeCapacitated {

////public:

/////*
////    /// TODO: OPTIMIZAR - USAR PONTEIRO PARA CROMOSOMA

////    // Copy constructor
////    eoChromosomeCapacitated(Chromosome const& _chrom)
////        : ChromosomeCapacitated(_chrom)
////    {
////        computeProximityCosts();
////    }

////    eoChromosomeCapacitated() { }
////*/
//////    eoChromosomeCapacitated(const Data& data) { init(data); }

////    eoChromosomeCapacitated(TimetableProblemData const& data) : ChromosomeCapacitated(data) { }

////    string className() const { return "EO Chromosome Capacitated"; }

////    /*virtual*/ void computeProximityCosts() {
////        baseComputeTimetablePenalty();
////    }

////    friend ostream& operator<<(ostream& os, const eoChromosomeCapacitated& timetable);
////};


//// EO Chromosome (Capacitated) implementation.
//// Inherits from EO in order to have a fitness value
//class eoChromosomeCapacitated : public EO<double>, public ChromosomeCapacitated {

//public:
//    // Constructor
//    eoChromosomeCapacitated(TimetableProblemData const& data) : ChromosomeCapacitated(data) { }

//    // Public interface
//    string className() const { return "EO Chromosome Capacitated"; }
//    friend ostream& operator<<(ostream& os, const eoChromosomeCapacitated& timetable);
//};




#endif // EOCHROMOSOMECAPACITATED_H
