#ifndef LINER_ALGEBRA_DETAILS_H
#define LINER_ALGEBRA_DETAILS_H


namespace Linear::Details {

    template<typename T>
    auto multiply_by_scalar(const T &scalar) {
        return [&scalar](const T &item) {
            return scalar * item;
        };
    }

    template<typename Derived, std::size_t Size, typename Field>
    class Base_algebra_struct {
    public:
        using value_type = Field;
        using data_type = std::array<Field, Size>;

        Base_algebra_struct() = default;

        template<typename Iter>
        Base_algebra_struct(Iter begin, const Iter &end) {
            if (std::distance(begin, end) != Size) {
                throw std::invalid_argument("too many or too few arguments in base algebra struct");
            }
            std::copy(begin, end, data_.begin());
        }

        template<typename Range>
        explicit Base_algebra_struct(const Range &range)
        : Base_algebra_struct(std::begin(range), std::end(range)) {}

        Base_algebra_struct(std::initializer_list<value_type> list)
        : Base_algebra_struct(list.begin(), list.end()) {}

        bool operator==(const Base_algebra_struct &other) const {
            return data_ == other.data_;
        }

        bool operator!=(const Base_algebra_struct &other) const {
            return data_ != other.data_;
        }

        Derived operator*(const value_type &scalar) const {
            Derived res;
            std::ranges::transform(data_, res.begin(), Details::multiply_by_scalar(scalar));
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
            return res;;
        }

        void operator*=(const value_type &scalar) {
            std::ranges::transform(data_, data_.begin(), Details::multiply_by_scalar(scalar));
        }

        void operator+=(const Derived &right) {
            std::ranges::transform(data_, right.data_, data_.begin(), std::plus<value_type>{});
        }

        void operator-=(const Derived &right) {
            std::ranges::transform(data_, right.data_, data_.begin(), std::minus<value_type>{});
        }

        virtual ~Base_algebra_struct() = default;

    protected:
        data_type data_{Field{0}};
    };

}

namespace Linear {
    using namespace Details;
}


#endif //LINER_ALGEBRA_DETAILS_H
