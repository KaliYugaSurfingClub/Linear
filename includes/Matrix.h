#ifndef LINER_ALGEBRA_MATRIX_H
#define LINER_ALGEBRA_MATRIX_H

#include "Vector.h"
#include "Helpers.h"
#include "Permutation.h"
#include "jump_iterator.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class MatrixElmRange;

    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef;

    template<std::size_t M, std::size_t N, typename Field>
    class RowRef;


    template<std::size_t M, std::size_t N, typename Field>
    class Matrix : public BaseAlgebraStruct<Matrix<M, N, Field>, M * N, Field> {

    using Base = BaseAlgebraStruct<Matrix<M, N, Field>, M * N, Field>;

    public:
        using value_type = Field;

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

        ColumnRef<M, N, Field> column_ref(std::size_t index) {
            return {*this, index};
        }

        RowRef<M, N, Field> row_ref(std::size_t index) {
            return {*this, index};
        }

        Vector<M, Field> column_copy(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("out_of_range get column_copy");
            }

            auto begin = std::next(Base::data_.begin(), M * index);
            auto end = std::next(begin, M * index);
            return {begin, end};
        }

        Vector<N, Field> row_copy(std::size_t index) {
            if (index >= M) {
                throw std::out_of_range("out_of_range in get row_copy");
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

        Field det() const requires (M == N) {
            const auto &all_permutations = PermutationsStorage::get(M);

            Field res = 0;

            for (auto &[sign, permutation] : all_permutations) {
                Field curr_product = sign;
                for (std::size_t i = 0; i < permutation.size(); ++i) {
                    curr_product *= (*this)(i, permutation[i]);
                }
                res += curr_product;
            }

            return res;
        }

        static Matrix<M, M, Field> identity() {
            Matrix<M, M, Field> res;
            MatrixElmRange range(res);
            std::fill(jump_iterator(range.begin(), M + 1), jump_iterator(range.end(), M), 1);
        }

        friend class MatrixElmRange<M, N, Field>;
    };

//    template<std::size_t M, typename Field, typename ...Args>
//    Matrix(Vector<M, Field>, Args...) -> Matrix<M, sizeof...(Args) + 1, Field>;
}

#endif //LINER_ALGEBRA_MATRIX_H
