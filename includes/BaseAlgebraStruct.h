#ifndef LINER_ALGEBRA_DETAILS_H
#define LINER_ALGEBRA_DETAILS_H


namespace Linear::Details {

    template<std::size_t Size, typename Field>
    class BaseAlgebraStruct {
    public:
        using data_type = std::array<Field, Size>;

        BaseAlgebraStruct() = default;

        explicit BaseAlgebraStruct(const Field &value) : data_{value} {}

        template<typename Iter>
        BaseAlgebraStruct(Iter begin, Iter end) {
            if (std::distance(begin, end) != Size) {
                throw std::invalid_argument("too many or too few arguments in base algebra struct");
            }
            std::copy(begin, end, data_.begin());
        }

        template<typename Range>
        explicit BaseAlgebraStruct(const Range &range)
        : BaseAlgebraStruct(std::begin(range), std::end(range)) {}

        BaseAlgebraStruct(std::initializer_list<Field> list)
        : BaseAlgebraStruct(list.begin(), list.end()) {}


    protected:
        virtual ~BaseAlgebraStruct() = default;
        data_type data_{Field{0}};
    };

}

namespace Linear {
    using namespace Details;
}


#endif //LINER_ALGEBRA_DETAILS_H
