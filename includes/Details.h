#ifndef LINER_ALGEBRA_DETAILS_H
#define LINER_ALGEBRA_DETAILS_H

namespace Liner::Details {

    template<typename T>
    auto multiply_by_scalar(const T &scalar) {
        return [&scalar](const T &item) {
            return scalar * item;
        };
    }

    template

    template<std::size_t M, typename Field>
    class HandleMatrixColumn {

    private:

    };

}


#endif //LINER_ALGEBRA_DETAILS_H
