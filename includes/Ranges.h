#ifndef LINER_ALGEBRA_RANGES_H
#define LINER_ALGEBRA_RANGES_H

#include "Matrix.h"

namespace Liner {

    template<typename T>
    class MatrixElemIterBase : public std::iterator<std::contiguous_iterator_tag, T> {
    public:
        explicit MatrixElemIterBase(std::size_t index) : index_(index) {}

        bool operator!=(MatrixElemIterBase other) const {
            return index_ != other.index_;
        }

        bool operator==(MatrixElemIterBase other) const {
            return index_ == other.index_;
        }

        typename MatrixElemIterBase::difference_type operator-(const MatrixElemIterBase &other) {
            return index_ - other.index_;
        }

    protected:
        std::size_t index_;
    };

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixElemIterConst : public MatrixElemIterBase<Field> {
    public:
        using Matrix = Matrix<M, N, Field>;
        using Base = MatrixElemIterBase<Field>;

        MatrixElemIterConst(const Matrix &matrix, std::size_t index)
        : MatrixElemIterBase<Field>(index), matrix_(matrix) {}

        MatrixElemIterConst &operator++() {
            ++Base::index_;
            return *this;
        }

        const typename MatrixElemIterConst::value_type &operator*() const {
            return matrix_.data_[Base::index_];
        }

    private:
        const Matrix &matrix_;
    };

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixElemIter : public MatrixElemIterBase<Field> {
    public:
        using Matrix = Matrix<M, N, Field>;
        using Base = MatrixElemIterBase<Field>;

        MatrixElemIter(Matrix &matrix, std::size_t index)
        : MatrixElemIterBase<Field>(index), matrix_(matrix) {}

        MatrixElemIter &operator++() {
            ++Base::index_;
            return *this;
        }

        typename MatrixElemIter::value_type &operator*() const {
            return matrix_.data_[Base::index_];
        }

    private:
        Matrix &matrix_;
    };

    template<std::size_t M, std::size_t N, typename Field = int>
    class MatrixRange {
    public:
        using Matrix = Matrix<M, N, Field>;

        explicit MatrixRange(Matrix &matrix, std::size_t start = 0, std::size_t finish = M * N)
                : matrix_(matrix), start_(start), finish_(finish) {}

        auto begin() const {
            return MatrixElemIter{matrix_, start_};
        }

        auto end() const {
            return MatrixElemIter{matrix_, finish_};
        }

    private:
        Matrix &matrix_;
        std::size_t start_;
        std::size_t finish_;
    };

    template<std::size_t M, std::size_t N, typename Field>
    MatrixRange(Matrix<M, N, Field>) -> MatrixRange<M, N, Field>;
}

#endif //LINER_ALGEBRA_RANGES_H
