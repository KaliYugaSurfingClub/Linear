#ifndef LINER_ALGEBRA_MATRIX_H
#define LINER_ALGEBRA_MATRIX_H

#include "Vector.h"
#include "Helpers.h"
#include "Permutation.h"
#include "jump_iterator.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef;

    template<std::size_t M, std::size_t N, typename Field>
    class ConstColumnRef;

    template<std::size_t M, std::size_t N, typename Field>
    class RowRef;

    template<std::size_t M, std::size_t N, typename Field>
    class ConstRowRef;


    template<std::size_t M, std::size_t N, typename Field>
    class Matrix : public BaseAlgebraStruct<Matrix<M, N, Field>, M * N, Field> {

        using Base = BaseAlgebraStruct<Matrix<M, N, Field>, M * N, Field>;

        template<typename Ref>
        class MatrixIterator {
        public:
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

        private:
            Matrix &matrix_;
            std::size_t index_;
        };

    public:
        using value_type = Field;

        using ColumnIterator = MatrixIterator<ColumnRef<M, N, Field>>;
        using RowIterator = MatrixIterator<RowRef<M, N, Field>>;

        using ConstColumnIterator = MatrixIterator<ConstColumnRef<M, N, Field>>;
        using ConstRowIterator = MatrixIterator<ConstRowRef<M, N, Field>>;

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

        static Matrix<M, M, Field> identity() {
            Matrix<M, M, Field> res;
            std::fill_n(jump_iterator(res.elems().begin(), M + 1), M, 1);
            return res;
        }

        ColumnRef<M, N, Field> column(std::size_t index) {
            return {*this, index};
        }

        ConstColumnRef<M, N, Field> column(std::size_t index) const {
            return {*this, index};
        }

        RowRef<M, N, Field> row(std::size_t index) {
            return {*this, index};
        }

        ConstRowRef<M, N, Field> row(std::size_t index) const {
            return {*this, index};
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

        auto elems() {
            return Range<typename Base::iterator>(
                    [&] { return Base::data_.begin(); },
                    [&] { return Base::data_.end(); }
            );
        }

        auto elems() const {
            return Range<typename Base::const_iterator>(
                    [&] { return Base::data_.cbegin(); },
                    [&] { return Base::data_.cend(); }
            );
        }

        auto rows() {
            return Range<RowIterator>(
                    [&] { return RowIterator(*this, 0); },
                    [&] { return RowIterator(*this, M); }
            );
        }

        auto rows() const {
            return Range<ConstRowIterator>(
                    [&] { return ConstRowIterator(*this, 0); },
                    [&] { return ConstRowIterator(*this, M); }
            );
        }

        auto columns() {
            return Range<ColumnIterator>(
                    [&] { return ColumnIterator(*this, 0); },
                    [&] { return ColumnIterator(*this, N); }
            );
        }

        auto columns() const {
            return Range<ConstColumnIterator>(
                    [&] { return ConstColumnIterator(*this, 0); },
                    [&] { return ConstColumnIterator(*this, N); }
            );
        }

        Field det() const requires (M == N) {
            const auto &all_permutations = PermutationsStorage::get(M);

            Field res = 0;

            for (auto &[sign, permutation]: all_permutations) {
                Field curr_product = sign;
                for (std::size_t i = 0; i < permutation.size(); ++i) {
                    curr_product *= (*this)(i, permutation[i]);
                }
                res += curr_product;
            }

            return res;
        }

        template<std::size_t K>
        Matrix<M, K, Field> operator*(const Matrix<N, K, Field> &left) {
            Matrix<M, N, Field> res;
            auto it = res.elems().begin();

            for (auto col_ref : left.columns()) {
                for (auto row_ref : rows()) {
                    *it = scalar_product(Vector<K, Field>{col_ref}, Vector<M, Field>{row_ref});
                    ++it;
                }
            }

            return res;
        }
    };

//    template<std::size_t M, typename Field, typename ...Args>
//    Matrix(Vector<M, Field>, Args...) -> Matrix<M, sizeof...(Args) + 1, Field>;
}

#endif //LINER_ALGEBRA_MATRIX_H
