#ifndef LINER_ALGEBRA_VECTOR_H
#define LINER_ALGEBRA_VECTOR_H

#include <array>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <utility>

#include "Details.h"

namespace Liner {

    template<std::size_t M, typename Field = int>
    class Vector {
    public:
        using value_type = Field;

        Vector() = default;

        template<typename Iter>
        Vector(Iter begin, const Iter &end) {
            if (std::distance(begin, end) != M) {
                throw std::invalid_argument("to many or too few arguments");
            }
            std::copy(begin, end, data_.begin());
        }

        template<typename Range>
        explicit Vector(const Range &range) : Vector(std::begin(range), std::end(range)) {}

        Vector(std::initializer_list<Field> list) : Vector(list.begin(), list.end()) {}

        bool operator==(const Vector &other) const {
            return data_ == other.data_;
        }

        bool operator!=(const Vector &other) const {
            return data_ != other.data_;
        }

        const Field &operator[](size_t i) const {
            if (i >= M) {
                throw std::out_of_range("out of range get from vec");
            }
            return data_[i];
        }

        Field &operator[](size_t i) {
            const Field &ref = std::as_const(*this)[i];
            return const_cast<Field &>(ref);
        }

        Vector operator*(const Field &scalar) const {
            Vector res;
            std::ranges::transform(data_, res.begin(), Details::multiply_by_scalar(scalar));
            return res;
        }

        Vector &operator*=(const Field &scalar) {
            std::ranges::transform(data_, data_.begin(), Details::multiply_by_scalar(scalar));
            return *this;
        }

        Vector operator+(const Vector<M, Field> &right) const {
            Vector res;
            std::ranges::transform(data_, right.data_, res.begin(), std::plus<Field>{});
            return res;;
        }

        Vector &operator+=(const Vector<M, Field> &right) {
            std::ranges::transform(data_, right.data_, data_.begin(), std::plus<Field>{});
            return *this;
        }

        auto begin() {
            return data_.begin();
        }

        auto end() {
            return data_.end();
        }

        auto begin() const {
            return data_.begin();
        }

        auto end() const {
            return data_.end();
        }

    private:
        std::array<Field, M> data_{0};
    };

    template<size_t M, typename Field = int>
    Vector<M, Field> vector_product(const Vector<M, Field> &left, const Vector<M, Field> &right) {

    }

    template<size_t M, typename Filed = int>
    Filed scalar_product(const Vector<M, Filed> &left, const Vector<M, Filed> &right) {
        return std::inner_product(left.begin(), left.end(), right.begin(), Filed(0));
    }

    template<size_t M, typename Field = int>
    Vector<M, Field> operator*(const Field &scalar, const Vector<M, Field> &vector) {
        return vector * scalar;
    }

    template<typename Head, typename ...T>
    Vector(Head, T...) -> Vector<sizeof...(T) + 1, Head>;
}

#endif //LINER_ALGEBRA_VECTOR_H
