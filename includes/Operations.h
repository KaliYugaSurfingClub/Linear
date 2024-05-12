#ifndef LINEAR_ALGEBRA_OPERATIONS_H
#define LINEAR_ALGEBRA_OPERATIONS_H


#include "Matrix.h"
#include "Range.h"

namespace Linear {

    template<std::size_t M, std::size_t N, std::size_t K, typename Field>
    Matrix<M, N, Field> operator*(const Matrix<M, K, Field> &right, const Matrix<K, N, Field> &left) {
        Matrix<M, N, Field> res;
        auto it = MatrixElmRange(res).begin();

        for (auto col_ref : MatrixColRange(left)) {
            for (auto row_ref : MatrixRowRange(right)) {
                *it = scalar_product(Vector<K, Field>{col_ref}, Vector<M, Field>{row_ref});
                ++it;
            }
        }

        return res;
    }

}

#endif //LINEAR_ALGEBRA_OPERATIONS_H
