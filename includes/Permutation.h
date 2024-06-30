#ifndef LINEAR_ALGEBRA_PERMUTATION_H
#define LINEAR_ALGEBRA_PERMUTATION_H

#include "Helpers.h"

namespace Linear {

    class PermutationsStorage {
    public:
        using permutation_t = std::pair<short, std::vector<std::size_t>>;

        static std::vector<permutation_t> get(std::size_t len) {
            if (permutations_.find(len) == permutations_.end()) {
                fill(len);
            }

            return permutations_[len];
        }

    private:
        static inline std::unordered_map<std::size_t, std::vector<permutation_t>> permutations_;

        static void fill(std::size_t len) {
            permutations_[len] = std::vector<permutation_t>{factorial(len)};

            std::vector<std::size_t> current_permutation(len);
            std::ranges::iota(current_permutation, 0);

            for (auto &[sign, permutation] : permutations_[len]) {
                permutation = current_permutation;
                sign = 1;

                for (auto it = permutation.begin(); it != permutation.end(); ++it) {
                    std::size_t inv_count = std::count_if(it + 1, permutation.end(), less_than(*it));
                    sign *= (inv_count % 2 == 0) ? 1 : -1;
                }

                std::ranges::next_permutation(current_permutation);
            }
        }
    };

}

#endif //LINEAR_ALGEBRA_PERMUTATION_H
