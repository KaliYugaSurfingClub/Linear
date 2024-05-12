#ifndef LINER_ALGEBRA_RANGE_H
#define LINER_ALGEBRA_RANGE_H

#include "Matrix.h"
#include "Ref.h"

namespace Linear {

    //todo CONST ITERATORS!
    //ранж теперь может мутировать константу

    namespace Details {

        template<std::size_t M, std::size_t N, typename Field>
        class MatrixRangeBase {
        protected:
            using Matrix = Matrix<M, N, Field>;

            explicit MatrixRangeBase(Matrix &matrix, std::size_t start, std::size_t finish)
            : matrix_(matrix), start_(start), finish_(finish) {}

            Matrix &matrix_;
            std::size_t start_;
            std::size_t finish_;
        };

        template<typename Derived, std::size_t M, std::size_t N, typename Field>
        class MatrixIteratorBase {
        public:
            using Matrix = Matrix<M, N, Field>;
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;

            MatrixIteratorBase(Matrix &matrix, std::size_t index) : index_(index), matrix_(matrix) {}

            bool operator!=(const Derived &other) const {
                return index_ != other.index_;
            }

            bool operator==(const Derived &other) const {
                return index_ == other.index_;
            }

            difference_type operator-(const Derived &other) {
                return index_ - other.index_;
            }

        protected:
            Matrix &matrix_;
            std::size_t index_;
        };

    }


    template<std::size_t M, std::size_t N, typename Field>
    class MatrixElmRange : public Details::MatrixRangeBase<M, N, Field> {

    using Base = Details::MatrixRangeBase<M, N, Field>;

    public:
        using Matrix = Matrix<M, N, Field>;
        using value_type = Matrix::value_type;
        using difference_type = std::ptrdiff_t;
        using iterator = Matrix::data_type::iterator;

        explicit MatrixElmRange(const Matrix &matrix, std::size_t start = 0, std::size_t finish = M * N)
        : Base(const_cast<Matrix &>(matrix), start, finish) {}

        iterator begin() const {
            return std::next(Base::matrix_.data_.begin(), Base::start_);
        }

        iterator end() const {
            return std::next(Base::matrix_.data_.begin(), Base::finish_);
        }
    };


    template<std::size_t M, std::size_t N, typename Field>
    class MatrixColRange : public Details::MatrixRangeBase<M, N, Field> {

    using BaseRange = Details::MatrixRangeBase<M, N, Field>;

    class ColumnIterator;

    public:
        using Matrix = Matrix<M, N, Field>;
        using iterator = ColumnIterator;

        explicit MatrixColRange(const Matrix &matrix, std::size_t start = 0, std::size_t finish = N)
        : BaseRange(const_cast<Matrix &>(matrix), start, finish) {}

        iterator begin() const {
            return {BaseRange::matrix_, BaseRange::start_};
        }

        iterator end() const {
            return {BaseRange::matrix_, BaseRange::finish_};
        }

    private:
        class ColumnIterator : public Details::MatrixIteratorBase<ColumnIterator, M, N, Field> {

        using BaseIterator = Details::MatrixIteratorBase<ColumnIterator, M, N, Field>;

        public:
            using value_type = ColumnRef<M, N, Field>;
            using iterator_category = BaseIterator::iterator_category;
            using difference_type = BaseIterator::difference_type;

            ColumnIterator(Matrix &matrix, std::size_t index) : BaseIterator(matrix, index) {}

            ColumnIterator &operator++() {
                ++BaseIterator::index_;
                return *this;
            }

            value_type operator*() {
                return {BaseIterator::matrix_, BaseIterator::index_};
            }
        };
    };


    template<std::size_t M, std::size_t N, typename Field>
    class MatrixRowRange : public Details::MatrixRangeBase<M, N, Field> {

    using BaseRange = Details::MatrixRangeBase<M, N, Field>;
    class RowIterator;

    public:
        using Matrix = Matrix<M, N, Field>;
        using iterator = RowIterator;

        explicit MatrixRowRange(const Matrix &matrix, std::size_t start = 0, std::size_t finish = M)
        : BaseRange(const_cast<Matrix &>(matrix), start, finish) {}

        iterator begin() const {
            return {BaseRange::matrix_, BaseRange::start_};
        }

        iterator end() const {
            return {BaseRange::matrix_, BaseRange::finish_};
        }

    private:
        class RowIterator : public Details::MatrixIteratorBase<RowIterator, M, N, Field> {

        using BaseIterator = Details::MatrixIteratorBase<RowIterator, M, N, Field>;

        public:
            using value_type = RowRef<M, N, Field>;
            using iterator_category = BaseIterator::iterator_category;
            using difference_type = BaseIterator::difference_type;

            RowIterator(Matrix &matrix, std::size_t index) : BaseIterator(matrix, index) {}

            RowIterator &operator++() {
                ++RowIterator::index_;
                return *this;
            }

            value_type operator*() {
                return {BaseIterator::matrix_, BaseIterator::index_};
            }
        };
    };

}

#endif //LINER_ALGEBRA_RANGE_H
