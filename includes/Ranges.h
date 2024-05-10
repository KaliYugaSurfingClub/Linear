#ifndef LINER_ALGEBRA_RANGES_H
#define LINER_ALGEBRA_RANGES_H

#include "Matrix.h"

namespace Liner {

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixElemIter : public std::iterator<std::contiguous_iterator_tag, const Field> {
    public:
        using Matrix = Matrix<M, N, Field>;

        MatrixElemIter(const Matrix &matrix, std::size_t index) : matrix_(matrix), index_(index) {}

        bool operator!=(MatrixElemIter other) const {
            return index_ != other.index_;
        }

        bool operator==(MatrixElemIter other) const {
            return index_ == other.index_;
        }

        MatrixElemIter &operator++() {
            ++index_;
            return *this;
        }

        const typename MatrixElemIter::reference &operator*() const {
            return matrix_.data_[index_];
        }

        typename MatrixElemIter::difference_type operator-(const MatrixElemIter &other) {
            return index_ - other.index_;
        }

    private:
        const Matrix &matrix_;
        std::size_t index_;
    };

    template<std::size_t M, std::size_t N, typename Field = int>
    class MatrixRange {
    public:
        using Matrix = Matrix<M, N, Field>;

        explicit MatrixRange(const Matrix &matrix, std::size_t start = 0, std::size_t finish = M * N)
                : matrix_(matrix), start_(start), finish_(finish) {}

        auto begin() const {
            return MatrixElemIter{matrix_, start_};
        }

        auto end() const {
            return MatrixElemIter{matrix_, finish_};
        }

    private:
        const Matrix &matrix_;
        std::size_t start_;
        std::size_t finish_;
    };

    template<std::size_t M, std::size_t N, typename Field>
    MatrixRange(Matrix<M, N, Field>) -> MatrixRange<M, N, Field>;
}

#endif //LINER_ALGEBRA_RANGES_H
