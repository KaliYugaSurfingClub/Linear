#ifndef LINER_ALGEBRA_DETAILS_H
#define LINER_ALGEBRA_DETAILS_H


namespace Linear::Details {

    //todo array не работает с jump iterator, переделать (работает только vector)
    template<typename Derived, std::size_t Size, typename Field>
    class BaseAlgebraStruct {
    public:
        using value_type = Field;
        using data_type = std::vector<Field>;

        BaseAlgebraStruct() = default;

        template<typename Iter>
        BaseAlgebraStruct(Iter begin, const Iter &end) {
            if (std::distance(begin, end) != Size) {
                throw std::invalid_argument("too many or too few arguments in base algebra struct");
            }
            std::copy(begin, end, data_.begin());
        }

        template<typename Range>
        explicit BaseAlgebraStruct(const Range &range)
        : BaseAlgebraStruct(std::begin(range), std::end(range)) {}

        BaseAlgebraStruct(std::initializer_list<value_type> list)
        : BaseAlgebraStruct(list.begin(), list.end()) {}

        bool operator==(const BaseAlgebraStruct &other) const {
            return data_ == other.data_;
        }

        bool operator!=(const BaseAlgebraStruct &other) const {
            return data_ != other.data_;
        }

        Derived operator*(const value_type &scalar) const {
            Derived res;
            std::ranges::transform(data_, res.begin(), multiply_by_scalar(scalar));
            return res;
        }

        Derived operator+(const Derived &right) const {
            Derived res;
            std::ranges::transform(data_, right.data_, res.begin(), std::plus<value_type>{});
            return res;;
        }

        Derived operator-(const Derived &right) const {
            Derived res;
            std::ranges::transform(data_, right.data_, res.begin(), std::minus<value_type>{});
            return res;
        }

        void operator*=(const value_type &scalar) {
            std::ranges::transform(data_, data_.begin(), multiply_by_scalar(scalar));
        }

        void operator+=(const Derived &right) {
            std::ranges::transform(data_, right.data_, data_.begin(), std::plus<value_type>{});
        }

        void operator-=(const Derived &right) {
            std::ranges::transform(data_, right.data_, data_.begin(), std::minus<value_type>{});
        }

    protected:
        virtual ~BaseAlgebraStruct() = default;

        data_type data_ = data_type(Size, Field{0});
    };

}

namespace Linear {
    using namespace Details;
}


#endif //LINER_ALGEBRA_DETAILS_H
