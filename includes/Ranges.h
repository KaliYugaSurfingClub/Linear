#ifndef LINER_ALGEBRA_RANGES_H
#define LINER_ALGEBRA_RANGES_H

#include "Matrix.h"

namespace Liner {

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixRange {
    public:
        using Matrix = Matrix<M, N, Field>;

        explicit MatrixRange(Matrix &matrix, std::size_t start = 0, std::size_t finish = M * N)
        : matrix_(matrix), start_(start), finish_(finish) {}

        auto begin() const {
            return std::next(matrix_.data_.begin(), start_);
        }

        auto end() const {
            return std::next(matrix_.data_.begin(), finish_);
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
