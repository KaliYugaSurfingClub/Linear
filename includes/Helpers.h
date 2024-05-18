
#ifndef LINEAR_ALGEBRA_HELPERS_H
#define LINEAR_ALGEBRA_HELPERS_H

#include <vector>
#include <algorithm>

namespace Linear {

    template<typename T>
    auto less_than(const T &scalar) {
        return [&scalar](const T &other) {
            return other < scalar;
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

    template<typename Iterator>
    class Range {
    public:
        Range(std::function<Iterator()> &&begin, std::function<Iterator()> &&end)
        : begin_(begin), end_(end) {}

        Iterator begin() const {
            return begin_();
        }

        Iterator end() const {
            return end_();
        }

    private:
        std::function<Iterator()> begin_;
        std::function<Iterator()> end_;
    };

}

#endif //LINEAR_ALGEBRA_HELPERS_H
