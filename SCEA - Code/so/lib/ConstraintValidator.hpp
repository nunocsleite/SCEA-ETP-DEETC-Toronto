#ifndef CONSTRAINTVALIDATOR_HPP
#define CONSTRAINTVALIDATOR_HPP


#include "base/chromosome/eoChromosomeCapacitated.hpp"
#include "ITC2007Constraints.hpp"
#include <vector>



class ConstraintValidator : public eoConstUF<eoChromosomeCapacitated const&, double> {
public:
    // Constructor
    ConstraintValidator() { }

    // Public interface
    void addConstraint(boost::shared_ptr<Constraint> constraint) {
        constraints.push_back(constraint);
    }

    // Compute constraints total penalty
    double operator()(eoChromosomeCapacitated const& _chrom) const override {
        double penalty = 0;
        for (auto const& c : constraints)
            penalty += c.get()->operator()(_chrom); // Invoke each constraint and sum up resulting penalties
        return penalty;
    }

private:
    // Fields
    vector<boost::shared_ptr<Constraint> > constraints;
};


#endif // CONSTRAINTVALIDATOR_HPP
