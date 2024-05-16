#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "jump_iterator.h"

//todo операции между вектором и ссылкой на часть матрицы, базовый класс будет убран
//todo REFACTOR

namespace Linear {

    template<bool is_const, typename Iterator, typename Field, std::size_t VectorSize>
    class MatrixRefBase {
    public:
        using Vector = Vector<VectorSize, Field>;

        const Field &operator[](std::size_t index) const requires is_const {
            return *std::next(begin_, index);
        }

        Field &operator[](std::size_t index) const requires (!is_const) {
            return *std::next(begin_, index);
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


    template<std::size_t M, std::size_t N, typename Field>
    class RowRef : public MatrixRefBase<false, jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N> {

    using Base = MatrixRefBase<false, jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N>;

    public:
        RowRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(ref.elems().begin() + index, M),
            jump_iterator(ref.elems().end() + index, M),
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ConstRowRef : public MatrixRefBase<true, jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N> {

    using Base = MatrixRefBase<true, jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N>;

    public:
        ConstRowRef(const Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(ref.elems().begin() + index, M),
            jump_iterator(ref.elems().end() + index, M),
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef : public MatrixRefBase<false, typename Matrix<M, N, Field>::data_type::iterator, Field, M> {

    using Base = MatrixRefBase<false, typename Matrix<M, N, Field>::data_type::iterator, Field, M>;

    public:
        ColumnRef(Matrix <M, N, Field> &ref, std::size_t index) : Base(
            ref.elems().begin() + index * M,
            ref.elems().begin() + index * M + M,
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ConstColumnRef : public MatrixRefBase<true, typename Matrix<M, N, Field>::data_type::iterator, Field, M> {

    using Base = MatrixRefBase<true, typename Matrix<M, N, Field>::data_type::iterator, Field, M>;

    public:
        ConstColumnRef(const Matrix <M, N, Field> &ref, std::size_t index) : Base(
                ref.elems().begin() + index * M,
                ref.elems().begin() + index * M + M,
                index
        ) {}
    };

}

#endif //LINER_ALGEBRA_COLUMNREF_H
