#ifndef KEMPECHAIN_H
#define KEMPECHAIN_H

#include <boost/unordered_set.hpp>

/**
 * @brief The ETTPKempeChain class
 *
 * This class keeps information about a Kempe chain, namely: the selected exam ei to move,
 * the source and destination time slots where the exam is being moved to in a feasible way,
 *
 */
template <typename EOT>
class ETTPKempeChain {

public:
    /**
     * @brief ETTPKempeChain ctor
     * @param _chrom     The solution where the Kempe chain information is associated
     * @param _ei        The selected exam ei to move
     * @param _ti        Source time slot
     * @param _tj        Destination time slot
     * @param _tiPeriod  Source time slot exams
     * @param _tjPeriod  Destination time slot exams
     */
    ETTPKempeChain(EOT &_chrom, int _ei, int _ti, int _tj,
                   boost::unordered_set<int> *_tiPeriod,
                   boost::unordered_set<int> *_tjPeriod)
        : chrom(_chrom), ei(_ei), ti(_ti), tj(_tj),
          tiPeriod(_tiPeriod), tjPeriod(_tjPeriod)  { }


    EOT &getSolution() const;
    void setSolution(EOT const &_chrom);

    int getEi() const;
    void setEi(int _ei);

    int getTi() const;
    void setTi(int _ti);

    int getTj() const;
    void setTj(int _tj);

    boost::unordered_set<int> *getTiPeriod() const;
    void setTiPeriod(boost::unordered_set<int> *_tiPeriod);

    boost::unordered_set<int> *getTjPeriod() const;
    void setTjPeriod(boost::unordered_set<int> *_tjPeriod);

private:
    /**
     * @brief chrom The solution where the Kempe chain information is associated
     */
    EOT &chrom;
    /**
     * @brief ei The selected exam ei to move
     */
    int ei;
    /**
     * @brief ti Source time slot
     */
    int ti;
    /**
     * @brief tj Destination time slot
     */
    int tj;
    /**
     * @brief tiPeriod Source time slot exams
     */
    boost::unordered_set<int> *tiPeriod;
    /**
     * @brief tjPeriod Destination time slot exams
     */
    boost::unordered_set<int> *tjPeriod;
};


template <typename EOT>
EOT &ETTPKempeChain<EOT>::getSolution() const
{
    return chrom;
}

template <typename EOT>
void ETTPKempeChain<EOT>::setSolution(EOT const &_chrom)
{
    chrom = _chrom;
}

template <typename EOT>
int ETTPKempeChain<EOT>::getEi() const
{
    return ei;
}

template <typename EOT>
void ETTPKempeChain<EOT>::setEi(int _ei)
{
    ei = _ei;
}

template <typename EOT>
int ETTPKempeChain<EOT>::getTi() const
{
    return ti;
}

template <typename EOT>
void ETTPKempeChain<EOT>::setTi(int _ti)
{
    ti = _ti;
}

template <typename EOT>
int ETTPKempeChain<EOT>::getTj() const
{
    return tj;
}

template <typename EOT>
void ETTPKempeChain<EOT>::setTj(int _tj)
{
    tj = _tj;
}

template <typename EOT>
boost::unordered_set<int> *ETTPKempeChain<EOT>::getTiPeriod() const
{
    return tiPeriod;
}

template <typename EOT>
void ETTPKempeChain<EOT>::setTiPeriod(boost::unordered_set<int> *_tiPeriod)
{
    tiPeriod = _tiPeriod;
}

template <typename EOT>
boost::unordered_set<int> *ETTPKempeChain<EOT>::getTjPeriod() const
{
    return tjPeriod;
}

template <typename EOT>
void ETTPKempeChain<EOT>::setTjPeriod(boost::unordered_set<int> *_tjPeriod)
{
    tjPeriod = _tjPeriod;
}




#endif // KEMPECHAIN_H
