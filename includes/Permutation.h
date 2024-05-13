#ifndef LINEAR_ALGEBRA_PERMUTATION_H
#define LINEAR_ALGEBRA_PERMUTATION_H

class Permutation {
public:
    explicit Permutation(std::size_t len) : sign_(1), permutation_(len) {
        std::ranges::iota(permutation_, 0);
    }

    void next() {
        std::next_permutation(permutation_.begin(), permutation_.end());
    }

    std::pair<short, std::vector<std::size_t>> get() {
        return {sign_, permutation_};
    };

private:
    short sign_;
    std::vector<std::size_t> permutation_;
};

#endif //LINEAR_ALGEBRA_PERMUTATION_H
