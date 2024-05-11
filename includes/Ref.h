#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "Range.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef {
    public:
        using Matrix = Matrix<M, N, Field>;
        using Vector = Vector<M, Field>;

        ColumnRef(Matrix &ref, std::size_t index) : ref_(ref), column_index_(index) {}

        void operator*=(const Field &scalar) {
            auto begin = std::next(MatrixElmRange(ref_).begin(), column_index_ * M);
            auto end = std::next(begin, M);
            std::transform(begin, end, begin, Details::multiply_by_scalar(scalar));
        }

    private:
        std::size_t column_index_;
        Matrix &ref_;
    };

    template<std::size_t M, std::size_t N, typename Field>
    class RowRef {
    public:
        using Matrix = Matrix<M, N, Field>;
        using Vector = Vector<M, Field>;

        RowRef(Matrix &ref, std::size_t index) : ref_(ref), row_index_(index) {}

        void operator*=(const Field &scalar) {
            for (std::size_t i = 0; i < M; ++i) {
                ref_(i, row_index_) *= scalar;
            }
        }

        //todo возможность сложения с вектором
//        void operator+=(const Vector &vector) {
//            std::ranges::transform()
//        }

    private:
        std::size_t row_index_;
        Matrix &ref_;
    };
}

#endif //LINER_ALGEBRA_COLUMNREF_H
