#ifndef LINER_ALGEBRA_RANGES_H
#define LINER_ALGEBRA_RANGES_H

#include "Matrix.h"

namespace Liner {

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixElemIter {
    public:
        using Matrix = Matrix<M, N, Field>;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Field;

        MatrixElemIter(Matrix &matrix, std::size_t index)
        : index_(index), matrix_(matrix) {}

        bool operator!=(MatrixElemIter other) const {
            return index_ != other.index_;
        }

        bool operator==(MatrixElemIter other) const {
            return index_ == other.index_;
        }

        value_type &operator*() const {
            return matrix_.data_[index_];
        }

        difference_type operator-(const MatrixElemIter &other) {
            return index_ - other.index_;
        }

        MatrixElemIter &operator++() {
            ++index_;
            return *this;
        }

    private:
        Matrix &matrix_;
        std::size_t index_;
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

namespace std {

    template<std::size_t M, std::size_t N, typename Field>
    struct iterator_traits<Liner::MatrixElemIter<M, N, Field>> {
        using iterator_category = Liner::MatrixElemIter<M, N, Field>::iterator_category;
        using difference_type = Liner::MatrixElemIter<M, N, Field>::difference_type;
        using value_type = Liner::MatrixElemIter<M, N, Field>::value_type;
    };

}

#endif //LINER_ALGEBRA_RANGES_H
