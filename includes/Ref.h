#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "Range.h"

namespace Linear {

    namespace Details {

        template<std::size_t M, std::size_t N, typename Field>
        class MatrixRef {



        };

    }


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef {

        using iterator = MatrixElmRange<M, N, Field>::iterator;

    public:
        using Matrix = Matrix<M, N, Field>;
        using Vector = Vector<M, Field>;

        ColumnRef(Matrix &ref, std::size_t index) :
                begin_(MatrixElmRange(ref).begin() + column_index_ * M),
                end_(MatrixElmRange(ref).begin() + column_index_ * M + M),
                column_index_(index) {}

        ColumnRef &operator=(const Vector &vector) {
            std::ranges::copy(vector, begin_);
            return *this;
        }

        Field &operator[](std::size_t index) {
            return *std::next(begin_, index);
        }

        void operator*=(const Field &scalar) {
            std::transform(begin_, end_, begin_, Details::multiply_by_scalar(scalar));
        }

        void operator+=(const Vector &vector) {
            std::ranges::transform(*this, vector, begin_, std::plus<Field>{});
        }

        iterator begin() const {
            return begin_;
        }

        iterator end() const {
            return end_;
        }

    private:
        std::size_t column_index_;
        iterator begin_;
        iterator end_;
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

    private:
        std::size_t row_index_;
        Matrix &ref_;
    };
}

#endif //LINER_ALGEBRA_COLUMNREF_H
