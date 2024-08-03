#ifndef LINEAR_ALGEBRA_FRACTION_H
#define LINEAR_ALGEBRA_FRACTION_H

namespace Linear {

    //todo может быть класс int_no_zero
    template<typename T>
    const T &check_zero(const T &value) {
        if (value == 0) {
            throw std::invalid_argument("denominator must not be zero");
        }

        return value;
    }

    template<typename T>
    short signum(const T &value) {
        return (value >= T{0}) ? 1 : -1;
    }

    template<std::unsigned_integral Uint_t = unsigned>
    class fraction {
    public:
        fraction() = default;

        fraction(short sign, const Uint_t &numerator, const Uint_t &denominator)
        : sign_{sign}, numerator_{numerator}, denominator_{check_zero(denominator)} {
            simplify();
        }

        template<std::signed_integral Int_t>
        fraction(const Int_t &numerator, const Int_t &denominator)
        {
            simplify();
        }

        void simplify() {
            if (numerator_ < 2) {
                return;
            }

            Uint_t gcd = std::gcd(numerator_, denominator_);
            numerator_ /= gcd;
            denominator_ /= gcd;
        }

        [[nodiscard]] short sign() const {
            return sign_;
        }

        const Uint_t &get_numerator() const {
            return numerator_;
        }

        const Uint_t &get_denominator() const {
            return denominator_;
        }

        void set_numerator(const Uint_t &numerator) {
            numerator_ = numerator;
            simplify();
        }

        void set_denominator(const Uint_t &denominator) {
            denominator = check_zero(denominator);
            simplify();
        }

    private:
        short sign_ = 1;
        Uint_t numerator_ = 0;
        Uint_t denominator_ = 1;
    };

    template<typename Uint_t>
    std::ostream &operator<<(std::ostream &os, const fraction <Uint_t> fraction) {
        os << std::format("{1}{2}/{3}", fraction.sign(), fraction.numerator_, fraction.denominator_);
        return os;
    }

    template<typename T>
    class fraction<std::complex<T>> {

    };

}

#endif //LINEAR_ALGEBRA_FRACTION_H
