#ifndef LINER_ALGEBRA_VECTOR_H
#define LINER_ALGEBRA_VECTOR_H

#include <array>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <utility>

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


    template<std::size_t M, typename Field>
    class Vector : public IVector<M, Field, typename std::array<Field, M>::const_iterator> {
    public:
        using data_type = std::array<Field, M>;
        using iterator = data_type::iterator;
        using const_iterator = data_type::const_iterator;

        Vector() = default;

        template<typename Iter>
        Vector(Iter begin, Iter end) {
            if (std::distance(begin, end) != M) {
                throw std::invalid_argument("too many or too few arguments in vector");
            }
            std::copy(begin, end, data_.begin());
        }

        Vector(std::initializer_list<Field> list) : Vector(list.begin(), list.end()) {}

        template<typename Range>
        explicit Vector(const Range &range) : Vector(std::begin(range), std::end(range)) {}

        explicit Vector(const Field &value) : data_{value} {}

        template<typename OtherIterator>
        Vector &operator=(const IVector<M, Field, OtherIterator> &vector) {
            std::copy(vector.begin(), vector.end(), this->begin());
            return *this;
        }

        const Field &operator[](size_t i) const {
            if (i >= M) {
                throw std::out_of_range("out of range get from vec");
            }
            return this->data_[i];
        }

        Field &operator[](size_t i) {
            const Field &ref = std::as_const(*this)[i];
            return const_cast<Field &>(ref);
        }

        template<typename Iterator>
        void operator+=(const IVector<M, Field, Iterator> &vector) {
            std::transform(begin(), end(), vector.begin(), begin(), std::plus<Field>{});
        }

        template<typename Iterator>
        void operator-=(const IVector<M, Field, Iterator> &vector) {
            std::transform(begin(), end(), vector.begin(), begin(), std::minus<Field>{});
        }

        void operator*=(const Field &scalar) {
            std::for_each(begin(), end(), [&](Field &item) { item *= scalar; });
        }

        void operator/=(const Field &scalar) {
            std::for_each(begin(), end(), [&](Field &item) { item *= scalar; });
        }

        iterator begin() {
            return data_.begin();
        }

        iterator end() {
            return data_.end();
        }

        const_iterator begin() const override {
            return data_.begin();
        }

        const_iterator end()  const override {
            return data_.end();
        }

    private:
        data_type data_{Field{0}};
    };

    template<typename Head, typename ...T>
    Vector(Head, T...) -> Vector<sizeof...(T) + 1, Head>;

    template<size_t M, typename Field, typename IteratorLeft, typename IteratorRight>
    Vector<M, Field> vector_product(const IVector<M, Field, IteratorLeft> &left, const IVector<M, Field, IteratorRight> &right) {

    }

    template<size_t M, typename Field, typename IteratorLeft, typename IteratorRight>
    Field scalar_product(const IVector<M, Field, IteratorLeft> &left, const IVector<M, Field, IteratorRight> &right) {
        return std::inner_product(left.begin(), left.end(), right.begin(), Field{0});
    }

}

#endif //LINER_ALGEBRA_VECTOR_H
