#ifndef LINEAR_ALGEBRA_IVECTOR_H
#define LINEAR_ALGEBRA_IVECTOR_H

#include "algorithm"
#include "Helpers.h"

namespace Linear {

    template<std::size_t M, typename Field>
    class Vector;

    template<std::size_t M, typename Field, typename Iterator>
    class IVector {
    public:
        template<typename OtherIterator>
        bool operator==(const IVector<M, Field, OtherIterator> &vector) const {
            return std::equal(begin(), end(), vector.begin());
        }

        template<typename OtherIterator>
        bool operator!=(const IVector<M, Field, OtherIterator> &vector) const {
            return !std::equal(begin(), end(), vector.begin());
        }

        template<typename OtherIterator>
        Vector<M, Field> operator+(const IVector<M, Field, OtherIterator> &vector) const {
            Vector<M, Field> res;
            std::transform(begin(), end(), vector.begin(), res.begin(), std::plus<Field>{});
            return res;;
        }

        template<typename OtherIterator>
        Vector<M, Field> operator-(const IVector<M, Field, OtherIterator> &vector) const {
            Vector<M, Field> res;
            std::transform(begin(), end(), vector.begin(), res.begin(), std::minus<Field>{});
            return res;;
        }

        Vector<M, Field> operator*(const Field &scalar) const {
            Vector<M, Field> res;
            std::transform(begin(), end(), res.begin(), multiply_by_scalar(scalar));
            return res;;
        }

        Vector<M, Field> operator/(const Field &scalar) const {
            Vector<M, Field> res;
            std::transform(begin(), end(), res.begin(), divide_by_scalar(scalar));
            return res;;
        }

        virtual Iterator begin() const = 0;
        virtual Iterator end() const = 0;

    protected:
        virtual ~IVector() = default;
    };



}

#endif //LINEAR_ALGEBRA_IVECTOR_H
