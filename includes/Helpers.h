
#ifndef LINEAR_ALGEBRA_HELPERS_H
#define LINEAR_ALGEBRA_HELPERS_H

#include <vector>
#include <algorithm>

namespace Linear::Details {

    template<typename T>
    auto multiply_by_scalar(const T &scalar) {
        return [&scalar](const T &other) {
            return scalar * other;
        };
    }

    template<typename T>
    auto less_than(const T &scalar) {
        return [&scalar](const T &other) {
            return other < scalar;
        };
    }

    template<typename T>
    auto create_counter(T start) {
        return [&]() mutable {
            return start++;
        };
    }

    template<typename T>
    T factorial(T num) {
        T res = 1;
        for (std::size_t i = 2; i <= num; ++i) {
            res *= i;
        }
        return res;
    }

    template<typename Iter>
    class Range {
    public:
        Range(std::function<Iter()> &&begin, std::function<Iter()> &&end)
        : begin_(begin), end_(end) {}

        Iter begin() const {
            return begin_();
        }

        Iter end() const {
            return end_();
        }

    private:
        std::function<Iter()> begin_;
        std::function<Iter()> end_;
    };

}

#endif //LINEAR_ALGEBRA_HELPERS_H
