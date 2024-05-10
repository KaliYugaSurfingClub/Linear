#ifndef LINER_ALGEBRA_MATRIX_H
#define LINER_ALGEBRA_MATRIX_H

#include "Vector.h"

namespace Liner {

    template<std::size_t M, std::size_t N, typename Field = int>
    class MatrixElemIter;

    template<std::size_t M, std::size_t N, typename Field = int>
    class Matrix {
        friend class MatrixElemIter<M, N, Field>;

    public:
        using data_t = std::array<Field, M * N>;

        Matrix() = default;

        template<typename Iter>
        explicit Matrix(const Iter &begin, const Iter &end) {
            if (std::distance(begin, end) != M * N) {
                throw std::invalid_argument("to many or too few arguments");
            }
            std::copy(begin, end, data_.begin());
        }

        template<typename Range>
        explicit Matrix(const Range &range) : Matrix(std::begin(range), std::end(range)) {}

        Matrix(std::initializer_list<Field> list) : Matrix(list.begin(), list.end()) {}

        Matrix(std::initializer_list<Vector<M, Field>> list) {
            if (list.size() != N) {
                throw std::invalid_argument("too many or too few columns");
            }

            auto back_it = data_.begin();
            for (auto it = list.begin(); it != list.end(); ++it) {
                std::ranges::copy(*it, back_it);
                back_it = std::next(back_it, M);
            }
        }

        //todo extract
        Vector<M, Field> column(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("out_of_range get column");
            }

            Vector<M, Field> res;
            std::copy_n(std::next(data_.begin(), M * index), M, res.begin());
            return res;
        }

        //todo extract
        Vector<N, Field> row(std::size_t index) {
            if (index >= M) {
                throw std::out_of_range("out_of_range in get row");
            }

            Vector<N, Field> res;
            for (std::size_t i = 0; i < N; ++i) {
                res[i] = data_[i * M + index];
            }
            return res;
        }

        const Field &operator()(std::size_t i, std::size_t j) const {
            std::size_t index = i + j * M;
            if (i >= M || j >= N) {
                throw std::invalid_argument("invalid argument (i, j)");
            }

            return data_[index];
        }

        Field &operator()(std::size_t i, std::size_t j) {
            const Field &ref = std::as_const(*this)(i, j);
            return const_cast<Field &>(ref);
        }

        Matrix operator+(const Matrix &other) const {
            Matrix res = other;
            std::transform(data_.begin(), data_.end(), res.data_.begin(), res.data_.end(), std::plus<Field>{});
            return res;
        }

        Matrix operator*(const Field &scalar) {
            Matrix<M, N> res;
            std::ranges::transform(data_, res.data_.begin(), Details::multiply_by_scalar(scalar));
            return res;
        }

    private:
        data_t data_{0};
    };

    template<std::size_t M, std::size_t N, typename Field = int>
    Matrix<M, N, Field> operator*(const Field &scalar, const Matrix<M, N, Field> &matrix) {
        return matrix * scalar;
    }
}

#endif //LINER_ALGEBRA_MATRIX_H
