#ifndef LINER_ALGEBRA_RANGE_H
#define LINER_ALGEBRA_RANGE_H

#include "Matrix.h"
#include "Ref.h"

//todo CONST ITERATORS!
//ранж теперь может мутировать константу

namespace Linear {

    namespace Details {

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

            Derived &operator++() {
                ++index_;
                return reinterpret_cast<Derived &>(*this);
            }

        protected:
            Matrix &matrix_;
            std::size_t index_;
        };

    }

    template<std::size_t M, std::size_t N, typename Field>
    class ColumnIterator : public MatrixIteratorBase<ColumnIterator<M, N, Field>, M, N, Field> {

    using BaseIterator = MatrixIteratorBase<ColumnIterator, M, N, Field>;

    public:
        using value_type = ColumnRef<M, N, Field>;
        using iterator_category = BaseIterator::iterator_category;
        using difference_type = BaseIterator::difference_type;

        ColumnIterator(Matrix<M, N, Field> &matrix, std::size_t index) : BaseIterator(matrix, index) {}

        value_type operator*() {
            return {BaseIterator::matrix_, BaseIterator::index_};
        }
    };

    template<std::size_t M, std::size_t N, typename Field>
    class RowIterator : public MatrixIteratorBase<RowIterator<M, N, Field>, M, N, Field> {

    using BaseIterator = MatrixIteratorBase<RowIterator, M, N, Field>;

    public:
        using value_type = RowRef<M, N, Field>;
        using iterator_category = BaseIterator::iterator_category;
        using difference_type = BaseIterator::difference_type;

        RowIterator(Matrix<M, N, Field> &matrix, std::size_t index) : BaseIterator(matrix, index) {}

        value_type operator*() {
            return {BaseIterator::matrix_, BaseIterator::index_};
        }
    };

}

#endif //LINER_ALGEBRA_RANGE_H
