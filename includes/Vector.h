#ifndef LINER_ALGEBRA_VECTOR_H
#define LINER_ALGEBRA_VECTOR_H

#include <array>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <utility>

#include "BaseAlgebraStruct.h"

namespace Linear {

    template<std::size_t M, typename Field>
    class Vector : private BaseAlgebraStruct<M, Field> {

    using Base = BaseAlgebraStruct<M, Field>;

    public:
        using value_type = Field;
        using iterator = Base::data_type::iterator;
        using const_iterator = Base::data_type::const_iterator;

        using Base::Base;

        const Field &operator[](size_t i) const {
            if (i >= M) {
                throw std::out_of_range("out of range get from vec");
            }
            return Base::data_[i];
        }

        Field &operator[](size_t i) {
            const Field &ref = std::as_const(*this)[i];
            return const_cast<Field &>(ref);
        }

        iterator begin() {
            return Base::data_.begin();
        }

        iterator end() {
            return Base::data_.end();
        }

        const_iterator begin() const {
            return Base::data_.begin();
        }

        const_iterator end() const {
            return Base::data_.end();
        }
    };

    template<typename Head, typename ...T>
    Vector(Head, T...) -> Vector<sizeof...(T) + 1, Head>;

    template<size_t M, typename Field>
    Vector<M, Field> vector_product(const Vector<M, Field> &left, const Vector<M, Field> &right) {

    }

    template<size_t M, typename Filed = int>
    Filed scalar_product(const Vector<M, Filed> &left, const Vector<M, Filed> &right) {
        return std::inner_product(left.begin(), left.end(), right.begin(), Filed(0));
    }

}

#endif //LINER_ALGEBRA_VECTOR_H
