#ifndef LINER_ALGEBRA_MATRIX_H
#define LINER_ALGEBRA_MATRIX_H

#include "Vector.h"
#include "Helpers.h"
#include "Permutation.h"
#include "jump_iterator.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class RowRef;

    template<std::size_t M, std::size_t N, typename Field>
    class ConstRowRef;

    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef;

    template<std::size_t M, std::size_t N, typename Field>
    class ConstColumnRef;

    template<std::size_t M, std::size_t N, typename Field>
    class Matrix {

        template<typename Ref>
        class MatrixIterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Ref;

            MatrixIterator(const Matrix &matrix, std::size_t index)
            : matrix_(const_cast<Matrix &>(matrix)), index_(index) {}

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
        using data_type = std::array<Field, M * N>;

        using ColumnIterator = MatrixIterator<ColumnRef<M, N, Field>>;
        using RowIterator = MatrixIterator<RowRef<M, N, Field>>;
        using ElemIterator = data_type::iterator;

        using ConstColumnIterator = MatrixIterator<ConstColumnRef<M, N, Field>>;
        using ConstRowIterator = MatrixIterator<ConstRowRef<M, N, Field>>;
        using ConstElemIterator = data_type::const_iterator;

        Matrix() = default;

        template<typename Iter>
        Matrix(Iter begin, Iter end) {
            if (std::distance(begin, end) != M * N) {
                throw std::invalid_argument("too many or too few arguments in matrix");
            }
            std::copy(begin, end, data_.begin());
        }

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

        Matrix(std::initializer_list<Field> list) : Matrix(list.begin(), list.end()) {}

        template<typename Range>
        explicit Matrix(const Range &range) : Matrix(std::begin(range), std::end(range)) {}

        explicit Matrix(const Field &value) : data_{value} {}

        static Matrix<M, M, Field> identity() {
            Matrix<M, M, Field> res;
            std::fill_n(jump_iterator(res.elems().begin(), M + 1), M, 1);
            return res;
        }

        ColumnRef<M, N, Field> column(std::size_t index) {
            return {*this, index};
        }

        RowRef<M, N, Field> row(std::size_t index) {
            return {*this, index};
        }

        ConstColumnRef<M, N, Field> column(std::size_t index) const {
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

            return data_[index];
        }

        Field &operator()(std::size_t i, std::size_t j) {
            const Field &ref = std::as_const(*this)(i, j);
            return const_cast<Field &>(ref);
        }

        Range<ElemIterator> elems() {
            return {
                [&] { return data_.begin(); },
                [&] { return data_.end(); }
            };
        }

        Range<ConstElemIterator> elems() const {
            return {
                [&] { return data_.cbegin(); },
                [&] { return data_.cend(); }
            };
        }

        Range<RowIterator> rows() {
            return {
                [&] { return RowIterator(*this, 0); },
                [&] { return RowIterator(*this, M); }
            };
        }

        Range<ConstRowIterator> rows() const {
            return {
                [&] { return ConstRowIterator(*this, 0); },
                [&] { return ConstRowIterator(*this, M); }
            };
        }

        Range<ColumnIterator> columns() {
            return {
                [&] { return ColumnIterator(*this, 0); },
                [&] { return ColumnIterator(*this, N); }
            };
        }

        Range<ConstColumnIterator> columns() const {
            return {
                [&] { return ConstColumnIterator(*this, 0); },
                [&] { return ConstColumnIterator(*this, N); }
            };
        }

        template<std::size_t K>
        Matrix<M, K, Field> operator*(const Matrix<N, K, Field> &left) const {
            Matrix<M, N, Field> res;
            auto it = res.elems().begin();

            for (auto col_ref : left.columns()) {
                for (auto row_ref : this->rows()) {
                    *it++ = scalar_product(Vector<K, Field>{col_ref}, Vector<M, Field>{row_ref});
                }
            }

            return res;
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

    private:
        data_type data_{Field{0}};
    };

    template<std::size_t M, std::size_t N, std::size_t K, typename Field>
    auto join_matrices(const Matrix<M, N, Field> &right, const Matrix<M, K, Field> &left) {
        Matrix<M, N + K, Field> res;
        std::copy_n(right.elems().begin(), M * N, res.elems().begin());
        std::copy_n(left.elems().begin() + M * N, M * K, res.elems().begin());
        return res;
    }

    template<std::size_t N, typename Field>
    auto invert(const Matrix<N, N, Field> &matrix) {
        Matrix<N, N * 2, Field> augmented = join_matrices(matrix, Matrix<N, N, Field>::identity());

        augmented.row(0) /= augmented(0, 0);
        std::ranges::for_each(augmented.rows(), [&](auto &vector) { vector -= augmented.row(0); });

        return;
    }

//    template<std::size_t M, typename Field, typename ...Args>
//    Matrix(Vector<M, Field>, Args...) -> Matrix<M, sizeof...(Args) + 1, Field>;
}

#endif //LINER_ALGEBRA_MATRIX_H
