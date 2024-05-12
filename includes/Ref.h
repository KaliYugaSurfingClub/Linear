#ifndef LINER_ALGEBRA_COLUMNREF_H
#define LINER_ALGEBRA_COLUMNREF_H

#include "Vector.h"
#include "Range.h"

namespace Linear {

    namespace Details {

        template<typename Iterator, std::size_t M, std::size_t N, typename Field>
        class MatrixRefBase {
        public:
            using Matrix = Matrix<M, N, Field>;
            using Vector = Vector<M, Field>;

            MatrixRefBase(Iterator begin, Iterator end, std::size_t index)
            : begin_(begin), end_(end), index_(index) {}

            Field &operator[](std::size_t index) {
                return *std::next(begin_, index);
            }

            void operator*=(const Field &scalar) {
                std::transform(begin_, end_, begin_, Details::multiply_by_scalar(scalar));
            }

            void operator+=(const Vector &vector) {
                std::transform(vector.begin(), vector.end(), begin_, begin_, std::plus<Field>{});
            }

            Iterator begin() const {
                return begin_;
            }

            Iterator end() const {
                return end_;
            }

        protected:
            std::size_t index_;
            Iterator begin_;
            Iterator end_;
        };
    }



//    template<std::size_t M, std::size_t N, typename Field>
//    class RowRef : public Details::MatrixRefBase<jump_iterator<Field>, M, N, Field> {
//
//    using Base = Details::MatrixRefBase<jump_iterator<Field>, M, N, Field>;
//
//    public:
//        using Matrix = Matrix<M, N, Field>;
//        using Vector = Vector<M, Field>;
//
//        RowRef(Matrix &ref, std::size_t index) : Base(
//                jump_iterator(MatrixElmRange(ref).begin() + index, M),
//                jump_iterator(MatrixElmRange(ref).end() - M + index, M),
//                index
//        ) {}
//
//        RowRef &operator=(const Vector &vector) {
//            std::ranges::copy(vector, Base::begin_);
//            return *this;
//        }
//    };


    template<std::size_t M, std::size_t N, typename Field>
    class ColumnRef : public Details::MatrixRefBase<typename MatrixElmRange<M, N, Field>::iterator, M, N, Field> {

    using Base = Details::MatrixRefBase<typename MatrixElmRange<M, N, Field>::iterator, M, N, Field>;

    public:
        using Matrix = Matrix<M, N, Field>;
        using Vector = Vector<M, Field>;

        ColumnRef(Matrix &ref, std::size_t index) : Base(
                MatrixElmRange(ref).begin() + index * M,
                MatrixElmRange(ref).begin() + index * M + M,
                index
        ) {}

        ColumnRef &operator=(const Vector &vector) {
            std::ranges::copy(vector, Base::begin_);
            return *this;
        }
    };
}

#endif //LINER_ALGEBRA_COLUMNREF_H
