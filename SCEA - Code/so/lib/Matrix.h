#ifndef MATRIX
#define MATRIX

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

/**
 * @brief The Matrix class Fixed size matrix
 */
template <typename T>
class Matrix {

public:
    // Constructor
	Matrix(int nlines, int ncols);
    // Public interface
    T& getVal(int i, int j) const;
    int getLines() const;
    int getCols() const;
	friend ostream& operator<<(ostream& os, const Matrix& Matrix);

private:
    /**
     * @brief nlines Number of lines
     */
    int nlines;
    /**
     * @brief ncols Number of columns
     */
    int ncols;
    /**
     * @brief vec Internal vector used as a container of data
     */
    vector<T> vec;
};



/**
 * @brief Matrix::Matrix Create a matrix with the specified # lines and # columns
 * @param nlines Number of lines
 * @param ncols Number of columns
 */
template <typename T>
Matrix<T>::Matrix(int nlines, int ncols)
    : nlines(nlines), ncols(ncols), vec(nlines*ncols) { }


/**
 * @brief Matrix::getVal Returns the value in cell (i,j). Indexes start at zero.
 * @param i Line index
 * @param j Column index
 * @return The cell value in coordinates (i,j)
 */
template <typename T>
T &Matrix<T>::getVal(int i, int j) const {
//    assert(i >= 0 && i < nlines && j >= 0 && j < ncols);
    return vec[i*ncols+j];
}

/**
 * @brief Matrix::getLines Returns the number of lines
 * @return The number of lines
 */
template <typename T>
int Matrix<T>::getLines() const { return nlines; }

/**
 * @brief Matrix::getCols Returns the number of columns
 * @return Returns the number of columns
 */
template <typename T>
int Matrix<T>::getCols() const { return ncols; }




#endif
