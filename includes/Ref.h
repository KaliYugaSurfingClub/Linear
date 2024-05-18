#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "jump_iterator.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class Matrix;

    template<bool is_const, typename Iterator, typename Field, std::size_t VectorSize>
    class MatrixRefBase : public IVector<VectorSize, Field, Iterator> {
    public:
        const Field &operator[](std::size_t index) const requires is_const {
            return *std::next(begin_, index);
        }

        Field &operator[](std::size_t index) const requires (!is_const) {
            return *std::next(begin_, index);
        }

        template<typename OtherIterator>
        void operator+=(const IVector<VectorSize, Field, OtherIterator> &vector) const requires (!is_const) {
            std::transform(begin(), end(), vector.begin(), begin(), std::plus<Field>{});
        }

        template<typename OtherIterator>
        void operator-=(const IVector<VectorSize, Field, OtherIterator> &vector) const requires (!is_const) {
            std::transform(begin(), end(), vector.begin(), begin(), std::minus<Field>{});
        }

        void operator*=(const Field &scalar) const requires (!is_const) {
            std::transform(begin(), end(), begin(), multiply_by_scalar(scalar));
        }

        void operator/=(const Field &scalar) const requires (!is_const) {
            std::transform(begin(), end(), begin(), divide_by_scalar(scalar));
        }

        Iterator begin() const override {
            return begin_;
        }

        Iterator end() const override {
            return end_;
        }

    protected:
        MatrixRefBase(Iterator begin, Iterator end)
        : begin_(begin), end_(end) {}

        virtual ~MatrixRefBase() = default;

        Iterator begin_;
        Iterator end_;
    };


    template<std::size_t M, std::size_t N, typename Field>
    class RowRef : public MatrixRefBase<false, jump_iterator<typename Matrix<M, N, Field>::ElemIterator>, Field, N> {

    using Base = MatrixRefBase<false, jump_iterator<typename Matrix<M, N, Field>::ElemIterator>, Field, N>;

    public:
        RowRef(Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(ref.elems().begin() + index, M),
            jump_iterator(ref.elems().end() + index, M)
        ) {}

        template<typename OtherIterator>
        const RowRef &operator=(const IVector<N, Field, OtherIterator> &vector) const {
            std::copy(vector.begin(), vector.end(), this->begin());
            return *this;
        }

        template<typename OtherIterator>
        RowRef &operator=(const IVector<N, Field, OtherIterator> &vector) {
            std::copy(vector.begin(), vector.end(), this->begin());
            return *this;
        }

        RowRef &operator=(const RowRef &row) {
            std::copy(row.begin(), row.end(), this->begin());
            return *this;
        }

        const RowRef &operator=(const RowRef &row) const {
            std::copy(row.begin(), row.end(), this->begin());
            return *this;
        }
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ConstRowRef : public MatrixRefBase<true, jump_iterator<typename Matrix<M, N, Field>::ConstElemIterator>, Field, N> {

    using Base = MatrixRefBase<true, jump_iterator<typename Matrix<M, N, Field>::ConstElemIterator>, Field, N> ;

    public:
        ConstRowRef(const Matrix<M, N, Field> &ref, std::size_t index) : Base(
            jump_iterator(ref.elems().begin() + index, M),
            jump_iterator(ref.elems().end() + index, M)
        ) {}
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef : public MatrixRefBase<false, typename Matrix<M, N, Field>::ElemIterator, Field, M> {

    using Base = MatrixRefBase<false, typename Matrix<M, N, Field>::ElemIterator, Field, M>;

    public:
        ColumnRef(Matrix <M, N, Field> &ref, std::size_t index) : Base(
            ref.elems().begin() + index * M,
            ref.elems().begin() + index * M + M
        ) {}

        //todo возможно лучше копирование от любого рэнжа
        template<typename OtherIterator>
        ColumnRef &operator=(const IVector<M, Field, OtherIterator> &vector) const {
            std::copy(vector.begin(), vector.end(), this->begin());
            return *this;
        }

        template<typename OtherIterator>
        ColumnRef &operator=(const IVector<M, Field, OtherIterator> &vector) {
            std::copy(vector.begin(), vector.end(), this->begin());
            return *this;
        }

        ColumnRef &operator=(const ColumnRef &col) {
            std::copy(col.begin(), col.end(), this->begin());
            return *this;
        }

        const ColumnRef &operator=(const ColumnRef &col) const {
            std::copy(col.begin(), col.end(), this->begin());
            return *this;
        }
    };


    template<std::size_t M, std::size_t N, typename Field>
    class ConstColumnRef : public MatrixRefBase<true, typename Matrix<M, N, Field>::ConstElemIterator, Field, M> {

    using Base = MatrixRefBase<true, typename Matrix<M, N, Field>::ConstElemIterator, Field, M>;

    public:
        ConstColumnRef(const Matrix <M, N, Field> &ref, std::size_t index) : Base(
                ref.elems().begin() + index * M,
                ref.elems().begin() + index * M + M
        ) {}
    };

}

#endif //LINER_ALGEBRA_COLUMNREF_H
