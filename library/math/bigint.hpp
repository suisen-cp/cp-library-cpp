#ifndef SUISEN_STRING_BIGINT
#define SUISEN_STRING_BIGINT

#include "library/math/unsigned_bigint.hpp"

namespace suisen {
    struct bigint {
        static inline struct { operator bigint() const { return bigint{ unsigned_bigint::ZERO }; }; } const ZERO{};
        static inline struct { operator bigint() const { return bigint{ unsigned_bigint::ONE }; }; } const ONE{};

        bigint() : _neg(false), _dat{} {}

        template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
        bigint(T v) {
            _neg = false;
            if constexpr (std::is_signed_v<T>) {
                if (v < 0) {
                    _neg = true;
                    v = -v;
                }
            }
            _dat = unsigned_bigint(v);
        }
        bigint(const std::string& s) {
            if (s.front() == '-') {
                _neg = true;
                _dat = unsigned_bigint(s.substr(1));
                fix_sign();
            } else {
                _neg = false;
                _dat = unsigned_bigint(s);
            }
        }
        bigint(const char* s) : bigint(std::string(s)) {}

        bigint(const unsigned_bigint& dat) : _neg(false), _dat(dat) {}
        bigint(unsigned_bigint&& dat) : _neg(false), _dat(std::move(dat)) {}

        operator bool() const {
            return bool(_dat);
        }

        friend bool operator==(const bigint& a, const bigint& b) {
            if (a._neg xor b._neg) {
                return false;
            } else {
                return a._dat == b._dat;
            }
        }
        friend bool operator!=(const bigint& a, const bigint& b) {
            return not (a == b);
        }

        friend bool operator<(const bigint& a, const bigint& b) {
            if (a._neg xor b._neg) {
                return a._neg;
            } else if (a._neg) {
                return a._dat > b._dat;
            } else {
                return a._dat < b._dat;
            }
        }
        friend bool operator<=(const bigint& a, const bigint& b) {
            return not (b < a);
        }
        friend bool operator>(const bigint& a, const bigint& b) {
            return b < a;
        }
        friend bool operator>=(const bigint& a, const bigint& b) {
            return not (a < b);
        }

        friend bigint& operator<<=(bigint& a, int shamt) {
            a._dat <<= shamt;
            return a;
        }
        friend bigint operator<<(bigint a, int shamt) {
            a <<= shamt;
            return a;
        }
        friend bigint& operator>>=(bigint& a, int shamt) {
            a._dat >>= shamt;
            a.fix_sign();
            return a;
        }
        friend bigint operator>>(bigint a, int shamt) {
            a >>= shamt;
            a.fix_sign();
            return a;
        }

        bigint operator+() const {
            return *this;
        }
        bigint operator-() const {
            return bigint(_dat, not _neg);
        }

        bigint& operator++() {
            if (_neg) {
                --_dat;
                fix_sign();
            } else {
                ++_dat;
            }
            return *this;
        }
        bigint operator++(int) {
            bigint res = *this;
            ++*this;
            return res;
        }
        bigint& operator--() {
            if (_neg) {
                ++_dat;
            } else if (_dat) {
                --_dat;
            } else {
                _neg = true;
                _dat = unsigned_bigint::ONE;
            }
            return *this;
        }
        bigint operator--(int) {
            bigint res = *this;
            --*this;
            return res;
        }
        friend bigint& operator+=(bigint& a, const bigint& b) {
            if (a._neg xor b._neg) {
                if (a._dat >= b._dat) {
                    a._dat -= b._dat;
                } else {
                    a._dat = b._dat - a._dat;
                    a._neg = not a._neg;
                }
                a.fix_sign();
            } else {
                a._dat += b._dat;
            }
            return a;
        }
        friend bigint operator+(const bigint& a, const bigint& b) {
            bigint c = a;
            c += b;
            return c;
        }
        friend bigint& operator-=(bigint& a, const bigint& b) {
            if (a._neg xor b._neg) {
                a._dat += b._dat;
            } else {
                if (a._dat >= b._dat) {
                    a._dat -= b._dat;
                } else {
                    a._dat = b._dat - a._dat;
                    a._neg = not a._neg;
                }
                a.fix_sign();
            }
            return a;
        }
        friend bigint operator-(const bigint& a, const bigint& b) {
            bigint c = a;
            c -= b;
            return c;
        }
        friend bigint& operator*=(bigint& a, const bigint& b) {
            return a = a * b;
        }
        friend bigint operator*(const bigint& a, const bigint& b) {
            return bigint(a._dat * b._dat, a._neg xor b._neg);
        }

        static std::pair<bigint, bigint> divmod(bigint a, bigint b) {
            auto [q, r] = unsigned_bigint::divmod(a._dat, b._dat);
            return { bigint(std::move(q), a._neg xor b._neg), bigint(std::move(r), a._neg) };
        }
        friend bigint& operator/=(bigint& a, const bigint& b) {
            return a = a / b;
        }
        friend bigint operator/(const bigint& a, const bigint& b) {
            return divmod(a, b).first;
        }
        friend bigint& operator%=(bigint& a, const bigint& b) {
            return a = a % b;
        }
        friend bigint operator%(const bigint& a, const bigint& b) {
            return divmod(a, b).second;
        }

#define CAST_PRIMITIVE(type)                \
        operator type() const {             \
            type res = _dat;                \
            return _neg ? -res : res;       \
        }                                   \

        CAST_PRIMITIVE(unsigned int)
        CAST_PRIMITIVE(unsigned long)
        CAST_PRIMITIVE(unsigned long long)
        CAST_PRIMITIVE(__uint128_t)
        CAST_PRIMITIVE(float)
        CAST_PRIMITIVE(double)
        CAST_PRIMITIVE(long double)
#undef CAST_PRIMITIVE

#define CAST_SIGNED_INT(type)                                       \
        operator type() const {                                     \
            return static_cast<std::make_unsigned_t<type>>(*this);  \
        }                                                           \

        CAST_SIGNED_INT(int)
        CAST_SIGNED_INT(long)
        CAST_SIGNED_INT(long long)
#undef CAST_SIGNED_INT

        operator __int128_t() const {
            return static_cast<__uint128_t>(*this);
        }

        operator unsigned_bigint() const {
            assert(not _neg);
            return _dat;
        }

        operator std::string() const {
            if (_neg) {
                return '-' + std::string(_dat);
            } else {
                return std::string(_dat);
            }
        }

        friend std::istream& operator>>(std::istream& in, bigint& v) {
            std::string s;
            in >> s, v = s;
            return in;
        }
        friend std::ostream& operator<<(std::ostream& out, const bigint& v) {
            return out << std::string(v);
        }
    private:
        bigint(const unsigned_bigint& dat, bool neg) : _neg(neg), _dat(dat) { fix_sign(); }
        bigint(unsigned_bigint&& dat, bool neg) : _neg(neg), _dat(std::move(dat)) { fix_sign(); }

        bool _neg;
        unsigned_bigint _dat;

        void fix_sign() {
            if (_neg and not _dat) _neg = false;
        }
    };
} // namespace suisen


#endif // SUISEN_STRING_BIGINT
