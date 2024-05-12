#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "Range.h"
#include "jump_iterator.h"

//todo операции между вектором и ссылкой на часть матрицы


namespace Linear::Details {

    template<typename Iterator, typename Field, std::size_t VectorSize, typename Derived>
    class MatrixRefBase {
    public:
        using Vector = Vector<VectorSize, Field>;

        Field &operator[](std::size_t index) {
            return *std::next(begin_, index);
        }

        void operator*=(const Field &scalar) {
            std::transform(begin_, end_, begin_, multiply_by_scalar(scalar));
        }

        template<typename T>
        std::enable_if_t<std::is_same_v<Vector, T> || std::is_base_of_v<MatrixRefBase, T>>
        operator+=(const T &vector) {
            std::transform(vector.begin(), vector.end(), begin_, begin_, std::plus<Field>{});
        }

        template<typename T>
        std::enable_if_t<std::is_same_v<Vector, T> || std::is_base_of_v<MatrixRefBase, T>>
        operator-=(const T &vector) {
            std::transform(vector.begin(), vector.end(), begin_, begin_, std::minus<Field>{});
        }

        template<typename T>
        std::enable_if_t<std::is_same_v<Vector, T> || std::is_base_of_v<MatrixRefBase, T>, Vector>
        operator+(const T &other) const {
            Vector res;
            std::transform(begin_, end_, other.begin_, res.begin(), std::plus<Field>{});
            return res;
        }

        template<typename T>
        std::enable_if_t<std::is_same_v<Vector, T> || std::is_base_of_v<MatrixRefBase, T>, Vector>
        operator-(const T &other) const {
            Vector res;
            std::transform(begin_, end_, other.begin_, res.begin(), std::minus<Field>{});
            return res;
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
    class RowRef : public MatrixRefBase<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N, RowRef<M, N, Field>> {

    using Base = MatrixRefBase<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N, RowRef<M, N, Field>>;

    public:
        RowRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(MatrixElmRange(ref).begin() + index, M),
            jump_iterator(MatrixElmRange(ref).end() + index, M),
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef : public MatrixRefBase<typename MatrixElmRange<M, N, Field>::iterator, Field, M, ColumnRef<M, N, Field>> {

    using Base = MatrixRefBase<typename MatrixElmRange<M, N, Field>::iterator, Field, M, ColumnRef<M, N, Field>>;

    public:
        ColumnRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            MatrixElmRange(ref).begin() + index * M,
            MatrixElmRange(ref).begin() + index * M + M,
            index
        ) {}
    };

}

#endif //LINER_ALGEBRA_COLUMNREF_H
