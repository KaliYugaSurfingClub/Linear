
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
    auto create_counter(T start)  {
        return [&]() mutable {
            return start++;
        };
    }

    template<typename T>
    T factorial(T num) {
        T res = 1;
        for (std::size_t i = 2; i < num; ++i) {
            res *= 2;
        }
        return res;
    }

    short get_sign_of_permutation(const std::vector<std::size_t> &per) {
        short sign = 1;
        for (std::size_t i = 0; i < per.size(); ++i) {
            std::size_t inv_count = std::count_if(per.begin() + i + 1, per.end(), less_than(per[i]));

            if (inv_count % 2 != 0) {
                sign *= -1;
            }
        }

        return sign;
    }


//    class Permutations {
//    public:
//        static std::vector<std::vector<std::size_t>> get_permutations(std::size_t len) {
//            using namespace std;
//
//            if (permutations_.find(len) == permutations_.end()) {
//                size_t count_of_permutations = factorial(len);
//                permutations_[len] = {count_of_permutations, vector<size_t>(len)};
//
//                std::ranges::iota(permutations_[len][0], 0);
//
//
//            }
//
//            return permutations_.at(len);
//        }
//
//        static inline std::map<std::size_t, std::vector<std::vector<std::size_t>>> permutations_;
//    };

}

#endif //LINEAR_ALGEBRA_HELPERS_H
