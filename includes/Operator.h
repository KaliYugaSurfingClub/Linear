#ifndef LINEAR_ALGEBRA_OPERATOR_H
#define LINEAR_ALGEBRA_OPERATOR_H

#include "Matrix.h"

namespace Linear {

    template<std::size_t M, std::size_t N, typename Field>
    class Operator : public Matrix<M, N, Field> {

        using Base = Matrix<M, N, Field>;

    public:

        using Base::Base;
        
    };
    
}

#endif //LINEAR_ALGEBRA_OPERATOR_H
