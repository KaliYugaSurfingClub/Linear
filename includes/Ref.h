#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "Range.h"
#include "jump_iterator.h"

//todo операции между вектором и ссылкой на часть матрицы


namespace Linear::Details {

    template<typename Iterator, std::size_t M, std::size_t N, typename Field>
    class MatrixRefBase {
    public:
        Field &operator[](std::size_t index) {
            return *std::next(begin_, index);
        }

        void operator*=(const Field &scalar) {
            std::transform(begin_, end_, begin_, multiply_by_scalar(scalar));
        }

        Iterator begin() const {
            return begin_;
        }

        Iterator end() const {
            return end_;
        }

    protected:
        MatrixRefBase(Iterator begin, Iterator end, std::size_t index)
        : begin_(begin), end_(end), index_(index) {}

        std::size_t index_;
        Iterator begin_;
        Iterator end_;
    };

}


namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class RowRef : public MatrixRefBase<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, M, N, Field> {

    using Base = MatrixRefBase<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, M, N, Field>;

    public:
        RowRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(MatrixElmRange(ref).begin() + index, M),
            jump_iterator(MatrixElmRange(ref).end() + index, M),
            index
        ) {}

        RowRef &operator=(const Vector<N, Field> &vector) {
            std::copy(vector.begin(), vector.end(), Base::begin_);
            return *this;
        }

        void operator+=(const Vector<N, Field> &vector) {
            std::transform(vector.begin(), vector.end(), Base::begin_, Base::begin_, std::plus<Field>{});
        }
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef : public MatrixRefBase<typename MatrixElmRange<M, N, Field>::iterator, M, N, Field> {

    using Base = MatrixRefBase<typename MatrixElmRange<M, N, Field>::iterator, M, N, Field>;

    public:
        ColumnRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            MatrixElmRange(ref).begin() + index * M,
            MatrixElmRange(ref).begin() + index * M + M,
            index
        ) {}

        ColumnRef &operator=(const Vector<N, Field> &vector) {
            std::ranges::copy(vector, Base::begin_);
            return *this;
        }

        void operator+=(const Vector<M, Field> &vector) {
            std::transform(vector.begin(), vector.end(), Base::begin_, Base::begin_, std::plus<Field>{});
        }
    };

}

#endif //LINER_ALGEBRA_COLUMNREF_H
