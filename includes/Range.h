#ifndef LINER_ALGEBRA_RANGE_H
#define LINER_ALGEBRA_RANGE_H

#include "Matrix.h"
#include "Ref.h"

//положить к класс матрицы

namespace Linear {

    template<typename Ref, std::size_t M, std::size_t N, typename Field>
    class MatrixIterator {
    public:
        using Matrix = Matrix<M, N, Field>;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Ref;

        MatrixIterator(Matrix &matrix, std::size_t index) : index_(index), matrix_(matrix) {}

        bool operator!=(const MatrixIterator &other) const {
            return index_ != other.index_;
        }

        bool operator==(const MatrixIterator &other) const {
            return index_ == other.index_;
        }

        difference_type operator-(const MatrixIterator &other) {
            return index_ - other.index_;
        }

        MatrixIterator &operator++() {
            ++index_;
            return *this;
        }

        Ref operator*() {
            return {matrix_, index_};
        }

    protected:
        Matrix &matrix_;
        std::size_t index_;
    };

}

#endif //LINER_ALGEBRA_RANGE_H
