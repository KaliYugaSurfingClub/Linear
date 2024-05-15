#ifndef LINEAR_ALGEBRA_OPERATIONS_H
#define LINEAR_ALGEBRA_OPERATIONS_H


#include "Matrix.h"
#include "Range.h"

namespace Linear {

    template<std::size_t M, std::size_t N, std::size_t K, typename Field>
    Matrix<M, N, Field> operator*(const Matrix<M, K, Field> &right, const Matrix<K, N, Field> &left) {
//        Matrix<M, N, Field> res;
//        auto it = res.elems().begin();
//
//        for (auto col_ref : left.columns()) {
//            for (auto row_ref : right.rows()) {
//                *it = scalar_product(Vector<K, Field>{col_ref}, Vector<M, Field>{row_ref});
//                ++it;
//            }
//        }
//
//        return res;
    }

    template<size_t M, typename Field>
    Vector<M, Field> vector_product(const Vector<M, Field> &left, const Vector<M, Field> &right) {

    }

    template<size_t M, typename Filed = int>
    Filed scalar_product(const Vector<M, Filed> &left, const Vector<M, Filed> &right) {
        return std::inner_product(left.begin(), left.end(), right.begin(), Filed(0));
    }

}

#endif //LINEAR_ALGEBRA_OPERATIONS_H
