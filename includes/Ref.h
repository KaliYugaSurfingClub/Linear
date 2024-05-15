#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "Range.h"
#include "jump_iterator.h"

//todo операции между вектором и ссылкой на часть матрицы, базовый класс будет убран

namespace Linear {

    template<typename Iterator, typename Field, std::size_t VectorSize>
    class MatrixRefBaseConst {
    public:
        using Vector = Vector<VectorSize, Field>;

        virtual const Field &operator[](std::size_t index) const {
            return *std::next(begin_, index);
        }

        Iterator begin() const {
            return begin_;
        }

        Iterator end() const {
            return end_;
        }

    protected:
        MatrixRefBaseConst(Iterator begin, Iterator end, std::size_t index)
        : begin_(begin), end_(end), index_(index) {}

        std::size_t index_;
        Iterator begin_;
        Iterator end_;
    };

    template<typename Iterator, typename Field, std::size_t VectorSize>
    class MatrixRefBase : public MatrixRefBaseConst<Iterator, Field, VectorSize> {

    using Base = MatrixRefBaseConst<Iterator, Field, VectorSize>;

    public:
        Field &operator[](std::size_t index) const override {
            return *std::next(Base::begin_, index);
        }

        void operator*=(const Field &scalar) const {
            std::transform(Base::begin_, Base::end_, Base::begin_, multiply_by_scalar(scalar));
        }

        void operator+=(const Base::Vector &vector) const {
            std::transform(vector.begin(), vector.end(), Base::begin_, Base::begin_, std::plus<Field>{});
        }

        void operator-=(const Base::Vector &vector) const {
            std::transform(vector.begin(), vector.end(), Base::begin_, Base::begin_, std::minus<Field>{});
        }

    protected:
        MatrixRefBase(Iterator begin, Iterator end, std::size_t index)
        : Base(begin, end, index) {}

    };


    template<std::size_t M, std::size_t N, typename Field>
    class RowRef : public MatrixRefBase<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N> {

    using Base = MatrixRefBase<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N>;

    public:
        RowRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(ref.elems().begin() + index, M),
            jump_iterator(ref.elems().end() + index, M),
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ConstRowRef : public MatrixRefBaseConst<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N> {

    using Base = MatrixRefBaseConst<jump_iterator<typename Matrix<M, N, Field>::data_type::iterator>, Field, N>;

    public:
        ConstRowRef(const Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(ref.elems().begin() + index, M),
            jump_iterator(ref.elems().end() + index, M),
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef : public MatrixRefBase<typename Matrix<M, N, Field>::data_type::iterator, Field, M> {

    using Base = MatrixRefBase<typename Matrix<M, N, Field>::data_type::iterator, Field, M>;

    public:
        ColumnRef(Matrix <M, N, Field> &ref, std::size_t index) : Base(
            ref.elems().begin() + index * M,
            ref.elems().begin() + index * M + M,
            index
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ConstColumnRef : public MatrixRefBaseConst<typename Matrix<M, N, Field>::data_type::iterator, Field, M> {

    using Base = MatrixRefBaseConst<typename Matrix<M, N, Field>::data_type::iterator, Field, M>;

    public:
        ConstColumnRef(const Matrix <M, N, Field> &ref, std::size_t index) : Base(
                ref.elems().begin() + index * M,
                ref.elems().begin() + index * M + M,
                index
        ) {}
    };

}

#endif //LINER_ALGEBRA_COLUMNREF_H
