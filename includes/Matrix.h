#ifndef LINER_ALGEBRA_MATRIX_H
#define LINER_ALGEBRA_MATRIX_H

#include "Vector.h"

namespace Liner {

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixRange;

    template<std::size_t M, std::size_t N, typename Field = int>
    class Matrix : public Details::Base_algebra_struct<Matrix<M, N, Field>, M * N, Field> {
    public:
        using value_type = Field;
        using Base = Details::Base_algebra_struct<Matrix<M, N, Field>, M * N, Field>;

        using Base::Base;

        Matrix(std::initializer_list<Vector<M, Field>> list) {
            if (list.size() != N) {
                throw std::invalid_argument("too many or too few columns");
            }

            auto back_it = Base::data_.begin();
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
            std::copy_n(std::next(Base::data_.begin(), M * index), M, res.begin());
            return res;
        }

        //todo extract
        Vector<N, Field> row(std::size_t index) {
            if (index >= M) {
                throw std::out_of_range("out_of_range in get row");
            }

            Vector<N, Field> res;
            for (std::size_t i = 0; i < N; ++i) {
                res[i] = Base::data_[i * M + index];
            }
            return res;
        }

        const Field &operator()(std::size_t i, std::size_t j) const {
            std::size_t index = i + j * M;
            if (i >= M || j >= N) {
                throw std::invalid_argument("invalid argument (i, j)");
            }

            return Base::data_[index];
        }

        Field &operator()(std::size_t i, std::size_t j) {
            const Field &ref = std::as_const(*this)(i, j);
            return const_cast<Field &>(ref);
        }

        friend class MatrixRange<M, N, Field>;
    };
}

#endif //LINER_ALGEBRA_MATRIX_H
