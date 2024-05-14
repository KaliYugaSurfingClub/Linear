#ifndef LINEAR_ALGEBRA_JUMP_ITERATOR_H
#define LINEAR_ALGEBRA_JUMP_ITERATOR_H

#include "iterator"
#include "BaseAlgebraStruct.h"

namespace Linear::Details {

    template<typename Iter>
    class jump_iterator {
    public:
        using value_type = Iter::value_type;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = Iter::difference_type;

        jump_iterator(Iter it, std::size_t jump_len)
        : it_(it), jump_len_(jump_len) {}

        value_type &operator*() const {
            return *it_;
        }

        jump_iterator &operator++() {
            it_ = std::next(it_, jump_len_);
            return *this;
        }

        jump_iterator &operator--() {
            it_ = std::prev(it_, jump_len_);
            return *this;
        }

        jump_iterator &operator+(std::size_t n) {
            it_ = std::next(it_, n * jump_len_);
            return *this;
        }

        difference_type &operator-(jump_iterator other) {
            return it_ - other.it_;
        }

        bool operator!=(jump_iterator other) const {
            return it_ < other.it_;
        }

        bool operator==(jump_iterator other) const {
            return it_ == other.it_;
        }

    private:
        Iter it_;
        std::size_t jump_len_;
    };

}


namespace std {

    template<typename Iter>
    struct iterator_traits<Linear::Details::jump_iterator<Iter>> {
        using value_type = Linear::Details::jump_iterator<Iter>::value_type;
        using iterator_category = Linear::Details::jump_iterator<Iter>::iterator_category;
        using difference_type = Linear::Details::jump_iterator<Iter>::difference_type;
    };

}

#endif //LINEAR_ALGEBRA_JUMP_ITERATOR_H
