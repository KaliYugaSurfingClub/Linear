#ifndef LINER_ALGEBRA_MATRIX_H
#define LINER_ALGEBRA_MATRIX_H

#include "Vector.h"
#include "Helpers.h"
#include "Permutation.h"
#include "jump_iterator.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class Matrix {
    public:
        template<typename Ref>
        class Iterator : public std::iterator<std::random_access_iterator_tag, Ref, std::ptrdiff_t, Ref, Ref> {
        public:
            Iterator(const Matrix &matrix, std::size_t index)
            : matrix_(const_cast<Matrix &>(matrix)), index_(index) {}

            bool operator!=(const Iterator &other) const {
                return index_ != other.index_;
            }

            bool operator==(const Iterator &other) const {
                return index_ == other.index_;
            }

            bool operator<(const Iterator &other) const {
                return index_ < other.index_;
            }

            std::ptrdiff_t operator-(const Iterator &other) {
                return index_ - other.index_;
            }

            Iterator &operator++() {
                ++index_;
                return *this;
            }

            Iterator operator+(std::ptrdiff_t n) {
                return {matrix_, index_ + n};
            }

            Iterator &operator--() {
                --index_;
                return *this;
            }

            Ref operator*() {
                return {matrix_, index_};
            }

        private:
            Matrix &matrix_;
            std::size_t index_;
        };

        template<bool is_const, typename Iterator, std::size_t VectorSize>
        class Ref : public IVector<VectorSize, Field, Iterator> {
        public:
            Ref(const Matrix &const_matrix, std::size_t index) {
                auto &mut_matrix = const_cast<Matrix &>(const_matrix);

                if constexpr (std::is_same_v<Iterator, ConstElemIterator>) {
                    begin_ = const_matrix.elems().begin() + index * M,
                    end_ = const_matrix.elems().begin() + index * M + M;
                }
                else if constexpr (std::is_same_v<Iterator, jump_iterator<ConstElemIterator>>) {
                    begin_ = jump_iterator(const_matrix.elems().begin() + index, M);
                    end_ = jump_iterator(const_matrix.elems().end() + index, M);
                }
                else if constexpr (std::is_same_v<Iterator, ElemIterator>) {
                    begin_ = mut_matrix.elems().begin() + index * M,
                    end_ = mut_matrix.elems().begin() + index * M + M;
                }
                else if constexpr (std::is_same_v<Iterator, jump_iterator<ElemIterator>>) {
                    begin_ = jump_iterator(mut_matrix.elems().begin() + index, M);
                    end_ = jump_iterator(mut_matrix.elems().end() + index, M);
                }
            }

            template<typename OtherIterator>
            const Ref &operator=(const IVector<VectorSize, Field, OtherIterator> &vector) const requires (!is_const) {
                std::copy(vector.begin(), vector.end(), this->begin());
                return *this;
            }

            const Ref &operator=(const Ref &ref) const requires (!is_const) {
                std::copy(ref.begin(), ref.end(), this->begin());
                return *this;
            }

            const Field &operator[](std::size_t index) const requires is_const {
                return *std::next(begin_, index);
            }

            Field &operator[](std::size_t index) const requires (!is_const) {
                return *std::next(begin_, index);
            }

            template<typename OtherIterator>
            void operator+=(const IVector<VectorSize, Field, OtherIterator> &vector) const requires (!is_const) {
                std::transform(begin(), end(), vector.begin(), begin(), std::plus<Field>{});
            }

            template<typename OtherIterator>
            void operator-=(const IVector<VectorSize, Field, OtherIterator> &vector) const requires (!is_const) {
                std::transform(begin(), end(), vector.begin(), begin(), std::minus<Field>{});
            }

            void operator*=(const Field &scalar) const requires (!is_const) {
                std::for_each(begin(), end(), [&](Field &item) { item *= scalar; });
            }

            void operator/=(const Field &scalar) const requires (!is_const) {
                std::for_each(begin(), end(), [&](Field &item) { item /= scalar; });
            }

            Iterator begin() const override {
                return begin_;
            }

            Iterator end() const override {
                return end_;
            }

        protected:
            Iterator begin_;
            Iterator end_;
        };

    public:
        using data_type = std::array<Field, M * N>;

        using ElemIterator = data_type::iterator;
        using ConstElemIterator = data_type::const_iterator;

        using ColumnRef = Ref<false, ElemIterator, M>;
        using ConstColumnRef = Ref<true, ConstElemIterator, M>;

        using ColumnIterator = Iterator<ColumnRef>;
        using ConstColumnIterator = Iterator<ConstColumnRef>;

        using RowRef = Ref<false, jump_iterator<ElemIterator>, N>;
        using ConstRowRef = Ref<true, jump_iterator<ConstElemIterator>, N>;

        using RowIterator = Iterator<RowRef>;
        using ConstRowIterator = Iterator<ConstRowRef>;

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

        ColumnRef column(std::size_t index) {
            return {*this, index};
        }

        RowRef row(std::size_t index) {
            return {*this, index};
        }

        ConstColumnRef column(std::size_t index) const {
            return {*this, index};
        }

        ConstRowRef row(std::size_t index) const {
            return {*this, index};
        }

        ConstColumnRef const_column(std::size_t index) {
            return {*this, index};
        }

        ConstRowRef const_row(std::size_t index) {
            return {*this, index};
        }

        Range<ElemIterator> elems() {
            return {
                [&] { return data_.begin(); },
                [&] { return data_.end(); }
            };
        }

        Range<RowIterator> rows() {
            return {
                [&] { return RowIterator(*this, 0); },
                [&] { return RowIterator(*this, M); }
            };
        }

        Range<ColumnIterator> columns() {
            return {
                [&] { return ColumnIterator(*this, 0); },
                [&] { return ColumnIterator(*this, N); }
            };
        }

        Range<ConstElemIterator> elems() const {
            return {
                [&] { return data_.cbegin(); },
                [&] { return data_.cend(); }
            };
        }

        Range<ConstRowIterator> rows() const {
            return {
                [&] { return ConstRowIterator(*this, 0); },
                [&] { return ConstRowIterator(*this, M); }
            };
        }

        Range<ConstColumnIterator> columns() const {
            return {
                [&] { return ConstColumnIterator(*this, 0); },
                [&] { return ConstColumnIterator(*this, N); }
            };
        }

        Range<ConstElemIterator> const_elems() {
            return const_cast<const Matrix &>(*this).elems();
        }

        Range<ConstRowIterator> const_rows() {
            return const_cast<const Matrix &>(*this).rows();
        }

        Range<ConstColumnIterator> const_columns() {
            return const_cast<const Matrix &>(*this).columns();
        }

        template<std::size_t K>
        Matrix<M, K, Field> operator*(const Matrix<N, K, Field> &left) const {
            Matrix<M, N, Field> res;
            auto it = res.elems().begin();

            for (auto col_ref : left.columns()) {
                for (auto row_ref : this->rows()) {
                    *it++ = scalar_product(col_ref, row_ref);
                }
            }

            return res;
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

    private:
        data_type data_{Field{0}};
    };

//    template<std::size_t M, typename Field, typename ...Args>
//    Matrix(Vector<M, Field>, Args...) -> Matrix<M, sizeof...(Args) + 1, Field>;

    //updet for MxN + KxN + ... +
    template<std::size_t M, std::size_t N, std::size_t K, typename Field>
    auto join_matrices(const Matrix<M, N, Field> &right, const Matrix<M, K, Field> &left) {
        Matrix<M, N + K, Field> res;
        std::copy_n(right.elems().begin(), M * N, res.elems().begin());
        std::copy_n(left.elems().begin(), M * K, res.elems().begin() + M * N);
        return res;
    }

    template<std::size_t N, typename Field>
    auto invert(const Matrix<N, N, Field> &matrix) {
        Matrix<N, N * 2, Field> augmented = join_matrices(matrix, Matrix<N, N, Field>::identity());

        for (std::size_t i = 0; i < N; ++i) {
            Field for_divide = augmented(i, i);
            augmented.row(i) /= for_divide;
            std::for_each(augmented.rows().begin() + 1 + i, augmented.rows().end(), [&](auto row_ref) {
                Field for_mult = row_ref[i];
                row_ref -= augmented.row(i) * for_mult;
            });
        }

        std::reverse(augmented.columns().begin(), augmented.columns().begin() + N);

        return augmented;
    }
}


#endif //LINER_ALGEBRA_MATRIX_H
