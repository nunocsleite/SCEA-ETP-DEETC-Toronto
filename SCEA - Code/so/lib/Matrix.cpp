

#include "Matrix.h"



ostream& operator<<(ostream& os, const Matrix& matrix) {
	os << endl << "Matrix" << endl;
    os << "nlines = " << matrix.getLines() << ", ncols = " << matrix.getCols() << endl;
    os << "size = " << matrix.getLines()*matrix.getCols() << endl;
	os << "vec.size = " << matrix.vec.size() << endl;

    for (int i = 0; i < matrix.getLines(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            os << matrix.getVal(i, j) << " ";
        }
        os << endl;
    }
	return os;
}

