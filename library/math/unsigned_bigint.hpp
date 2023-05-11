#ifndef SUISEN_UNSIGNED_BIGINT
#define SUISEN_UNSIGNED_BIGINT

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "library/convolution/arbitrary_mod_convolution.hpp"

namespace suisen {
    struct unsigned_bigint : private std::vector<int> {
        static constexpr int D = 1000000000;
        static constexpr int LogD = 9;

        static inline struct { operator unsigned_bigint() const { return unsigned_bigint{}; }; } const ZERO{};
        static inline struct { operator unsigned_bigint() const { return unsigned_bigint{ 1 }; }; } const ONE{};

        unsigned_bigint() : vector() {}

        template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
        unsigned_bigint(T v) {
            if constexpr (std::is_signed_v<T>) {
                assert(v >= 0);
            }
            for (; v; v /= D) {
                this->push_back(v % D);
            }
        }
        unsigned_bigint(const std::string& s) : vector() {
            int siz = s.size();
            for (int i = siz; i > 0; i -= LogD) {
                int l = std::max(0, i - LogD);
                int r = i;
                int& v = this->emplace_back();
                for (int j = l; j < r; ++j) {
                    int d = s[j] - '0';
                    assert(0 <= d and d <= 9);
                    v = v * 10 + d;
                }
            }
        }
        unsigned_bigint(const char* s) : unsigned_bigint(std::string(s)) {}

        operator bool() const {
            return not this->empty();
        }

        friend bool operator<(const unsigned_bigint& a, const unsigned_bigint& b) {
            if (a.size() != b.size()) {
                return a.size() < b.size();
            }
            for (size_t i = a.size(); i-- > 0;) {
                if (a[i] != b[i]) return a[i] < b[i];
            }
            return false;
        }
        friend bool operator<=(const unsigned_bigint& a, const unsigned_bigint& b) {
            return not (b < a);
        }
        friend bool operator>(const unsigned_bigint& a, const unsigned_bigint& b) {
            return b < a;
        }
        friend bool operator>=(const unsigned_bigint& a, const unsigned_bigint& b) {
            return not (a < b);
        }

        friend unsigned_bigint& operator<<=(unsigned_bigint& a, int shamt) {
            if (a) a.insert(a.begin(), shamt, 0);
            return a;
        }
        friend unsigned_bigint operator<<(unsigned_bigint a, int shamt) {
            a <<= shamt;
            return a;
        }
        friend unsigned_bigint& operator>>=(unsigned_bigint& a, int shamt) {
            a.erase(a.begin(), a.begin() + std::min<int>(shamt, a.size()));
            return a;
        }
        friend unsigned_bigint operator>>(unsigned_bigint a, int shamt) {
            a >>= shamt;
            return a;
        }

        unsigned_bigint& operator++() {
            return _incr_assign(*this);
        }
        unsigned_bigint operator++(int) {
            unsigned_bigint res = *this;
            _incr_assign(*this);
            return res;
        }
        unsigned_bigint& operator--() {
            return _decr_assign(*this);
        }
        unsigned_bigint operator--(int) {
            unsigned_bigint res = *this;
            _decr_assign(*this);
            return res;
        }
        friend unsigned_bigint& operator+=(unsigned_bigint& a, const unsigned_bigint& b) {
            return _add_assign(a, b);
        }
        friend unsigned_bigint operator+(const unsigned_bigint& a, const unsigned_bigint& b) {
            unsigned_bigint c = a;
            c += b;
            return c;
        }
        friend unsigned_bigint& operator-=(unsigned_bigint& a, const unsigned_bigint& b) {
            return _sub_assign(a, b);
        }
        friend unsigned_bigint operator-(const unsigned_bigint& a, const unsigned_bigint& b) {
            unsigned_bigint c = a;
            c -= b;
            return c;
        }
        friend unsigned_bigint& operator*=(unsigned_bigint& a, const unsigned_bigint& b) {
            return a = a * b;
        }
        friend unsigned_bigint operator*(const unsigned_bigint& a, const unsigned_bigint& b) {
            return _mul_fft(a, b);
        }

        static std::pair<unsigned_bigint, unsigned_bigint> divmod(unsigned_bigint a, unsigned_bigint b) {
            return _divmod(a, b);
        }
        friend unsigned_bigint& operator/=(unsigned_bigint& a, const unsigned_bigint& b) {
            return a = a / b;
        }
        friend unsigned_bigint operator/(const unsigned_bigint& a, const unsigned_bigint& b) {
            return divmod(a, b).first;
        }
        friend unsigned_bigint& operator%=(unsigned_bigint& a, const unsigned_bigint& b) {
            return a = a % b;
        }
        friend unsigned_bigint operator%(const unsigned_bigint& a, const unsigned_bigint& b) {
            return divmod(a, b).second;
        }

#define CAST_PRIMITIVE(type)                                        \
    operator type() const {                                         \
        type res = 0;                                               \
        for (auto it = this->rbegin(); it != this->rend(); ++it) {  \
            res = res * D + *it;                                    \
        }                                                           \
        return res;                                                 \
    }                                                               \

        CAST_PRIMITIVE(unsigned int)
            CAST_PRIMITIVE(unsigned long)
            CAST_PRIMITIVE(unsigned long long)
            CAST_PRIMITIVE(__uint128_t)
            CAST_PRIMITIVE(float)
            CAST_PRIMITIVE(double)
            CAST_PRIMITIVE(long double)
#undef CAST_PRIMITIVE

#define CAST_SIGNED_INT(type)                                   \
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

        operator std::string() const {
            return _to_string();
        }

        friend std::istream& operator>>(std::istream& in, unsigned_bigint& v) {
            std::string s;
            in >> s, v = s;
            return in;
        }
        friend std::ostream& operator<<(std::ostream& out, const unsigned_bigint& v) {
            return out << v._to_string();
        }
    private:
        using std::vector<int>::vector;

        void _check_leading_zeros() const {
            assert(this->empty() or this->back());
        }

        void _cut_leading_zeros() {
            while (this->size() and this->back() == 0) this->pop_back();
        }

        static unsigned_bigint& _incr_assign(unsigned_bigint& a) {
            for (int& e : a) {
                if (++e != D) return a;
                e -= D;
            }
            a.push_back(1);
            return a;
        }
        static unsigned_bigint& _decr_assign(unsigned_bigint& a) {
            assert(a.size());
            for (int& e : a) {
                if (--e >= 0) break;
                e += D;
            }
            a._cut_leading_zeros();
            return a;
        }

        static unsigned_bigint& _add_assign(unsigned_bigint& a, const unsigned_bigint& b) {
            if (a.size() < b.size()) a.resize(b.size());
            int carry = 0;
            for (size_t i = 0; i < a.size(); ++i) {
                if (i >= b.size()) {
                    if (carry) {
                        ++a[i];
                    } else break;
                } else {
                    a[i] += b[i] + carry;
                }
                if (a[i] >= D) {
                    a[i] -= D;
                    carry = 1;
                } else {
                    carry = 0;
                }
            }
            if (carry) a.push_back(1);
            return a;
        }

        static unsigned_bigint& _sub_assign(unsigned_bigint& a, const unsigned_bigint& b) {
            assert(a.size() >= b.size());
            int borrow = 0;
            for (size_t i = 0; i < a.size(); ++i) {
                if (i >= b.size()) {
                    if (borrow) {
                        --a[i];
                    } else break;
                } else {
                    a[i] -= b[i] + borrow;
                }
                if (a[i] < 0) {
                    a[i] += D;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
            }
            assert(not borrow);
            a._cut_leading_zeros();
            return a;
        }

        unsigned_bigint _cut(int l, int r) const {
            r = std::min(r, static_cast<int>(this->size()));
            unsigned_bigint v = l < r ? unsigned_bigint(this->begin() + l, this->begin() + r) : ZERO;
            v._cut_leading_zeros();
            return v;
        }

        template <typename T>
        static unsigned_bigint _build(const std::vector<T>& dat) {
            unsigned_bigint res;
            T carry = 0;
            for (auto v : dat) {
                carry += v;
                res.push_back(carry % D);
                carry /= D;
            }
            while (carry) {
                res.push_back(carry % D);
                carry /= D;
            }
            res._cut_leading_zeros();
            return res;
        }

        static unsigned_bigint _mul_naive(const unsigned_bigint& a, const unsigned_bigint& b) {
            return _build(suisen::internal::convolution_naive<int, __int128_t>(a, b));
        }

        static unsigned_bigint _mul_karatsuba(const unsigned_bigint& a, const unsigned_bigint& b) {
            if (std::min(a.size(), b.size()) <= 64) {
                return _mul_naive(a, b);
            }
            const int m = std::max(a.size(), b.size()) / 2;

            unsigned_bigint lo_a = a._cut(0, m), hi_a = a._cut(m, a.size());
            unsigned_bigint lo_b = b._cut(0, m), hi_b = b._cut(m, b.size());

            unsigned_bigint lo_c = lo_a * lo_b;
            unsigned_bigint hi_c = hi_a * hi_b;

            bool neg = true;
            unsigned_bigint md_a;
            if (hi_a >= lo_a) md_a = hi_a - lo_a;
            else              md_a = lo_a - hi_a, neg = not neg;
            unsigned_bigint md_b;
            if (hi_b >= lo_b) md_b = hi_b - lo_b;
            else              md_b = lo_b - hi_b, neg = not neg;
            unsigned_bigint md_ab = md_a * md_b;
            unsigned_bigint md_c = (hi_c << m) + lo_c + hi_c + lo_c._cut(m, lo_c.size());
            if (neg) md_c -= md_ab;
            else     md_c += md_ab;
            unsigned_bigint c = (md_c << m) + lo_c._cut(0, m);
            c._cut_leading_zeros();
            return c;
        }

        static unsigned_bigint _mul_fft(const unsigned_bigint& a, const unsigned_bigint& b) {
            if (std::min(a.size(), b.size()) <= 64) {
                return _mul_naive(a, b);
            }
            if (std::max(a.size(), b.size()) <= 200) {
                return _mul_karatsuba(a, b);
            }
            return _build(suisen::convolution_int(a, b));
        }

        // compare(a, D^k)
        static int _compare_powD(const unsigned_bigint& a, int k) {
            const int dA = a.size();
            if (dA <= k) return -1;
            if (dA >= k + 2) return +1;
            if (a[k] != 1) return +1;
            for (int i = 0; i < k; ++i) {
                if (a[i]) return +1;
            }
            return 0;
        }
        static unsigned_bigint _powD(int k) {
            return ONE << k;
        }

        static std::pair<unsigned_bigint, unsigned_bigint> _divmod_int(const unsigned_bigint& a, const unsigned_bigint& b) {
            assert(b.size() == 1);
            const int b0 = b.front();
            unsigned_bigint q;
            long long r = 0;
            for (auto it = a.rbegin(); it != a.rend(); ++it) {
                r = r * D + *it;
                q.push_back(r / b0);
                r %= b0;
            }
            std::reverse(q.begin(), q.end());
            q._cut_leading_zeros();
            return { q, r ? unsigned_bigint{ int(r) } : ZERO };
        }

        static std::pair<unsigned_bigint, unsigned_bigint> _divmod_naive(unsigned_bigint& a, unsigned_bigint& b) {
            if (b.size() == 1) {
                return _divmod_int(a, b);
            }
            if (a < b) {
                return { ZERO, a };
            }
            const unsigned_bigint coef{ D / (b.back() + 1) };
            a *= coef;
            b *= coef;
            assert(2 * b.back() >= D);

            unsigned_bigint q, r(a.end() - b.size(), a.end());
            for (int i = a.size() - b.size(); i >= 0; --i) {
                if (r.size() < b.size()) {
                    q.push_back(0);
                } else if (r.size() == b.size()) {
                    if (r >= b) {
                        q.push_back(1);
                        r -= b;
                    } else {
                        q.push_back(0);
                    }
                } else {
                    assert(r.size() == b.size() + 1);
                    int x = (static_cast<long long>(r.end()[-1]) * D + r.end()[-2]) / b.back();
                    unsigned_bigint bx = b * unsigned_bigint{ x };
                    while (bx > r) bx -= b, --x;
                    while (bx + b <= r) bx += b, ++x;
                    q.push_back(x);
                    r = r - bx;
                }
                if (i) {
                    r.insert(r.begin(), a[i - 1]);
                }
            }
            std::reverse(q.begin(), q.end());
            q._cut_leading_zeros();
            r._cut_leading_zeros();
            return { q, _divmod_int(r, coef).first };
        }
        static std::pair<unsigned_bigint, unsigned_bigint> _divmod_naive(const unsigned_bigint& a, const unsigned_bigint& b) {
            unsigned_bigint a_ = a, b_ = b;
            return _divmod_naive(a_, b_);
        }

        // floor(D^n/b)
        static unsigned_bigint _div_powD(int n, unsigned_bigint b) {
            assert(b.size() and 2 * b.back() >= D);

            const int dB = b.size();

            int k = n - dB;
            while (k > 64) k = (k + 1) >> 1;
            k = std::min(n, dB + k);

            unsigned_bigint c = _divmod_naive(_powD(k), b).first;
            unsigned_bigint bc = b * c;
            for (; k < n; k = 2 * k - dB) {
                // loop invariant: c = floor(D^k/B)
                bc.resize(k + 1);
                int carry = 0;
                for (int i = 0; i < k; ++i) {
                    bc[i] = D - bc[i] + (i ? carry - 1 : 0);
                    if (bc[i] >= D) {
                        bc[i] -= D;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                }
                ++bc[k];
                c *= bc;
                c.erase(c.begin(), c.begin() + dB);
                bc = b * c;
                if (_compare_powD(bc + b, 2 * k - dB) <= 0) {
                    ++c, bc += b;
                }
                assert(_compare_powD(bc + b, 2 * k - dB) > 0);
            }
            // c = floor(D^k/b)
            c >>= k - n;
            return c;
        }

        static std::pair<unsigned_bigint, unsigned_bigint> _divmod(unsigned_bigint a, unsigned_bigint b) {
            assert(b.size());
            if (std::min(static_cast<int>(b.size()), static_cast<int>(a.size()) - static_cast<int>(b.size())) <= 64) {
                return _divmod_naive(a, b);
            }
            if (a < b) {
                return { ZERO, a };
            }

            const unsigned_bigint coef{ D / (b.back() + 1) };
            a *= coef;
            b *= coef;
            assert(2 * b.back() >= D);

            const int dA = a.size(), dB = b.size();
            if (dA == dB) {
                return { ONE, _divmod_int(a - b, coef).first };
            }
            unsigned_bigint invB = _div_powD(dA, b);
            unsigned_bigint q = a * invB;
            q.erase(q.begin(), q.begin() + dA);
            unsigned_bigint qb = q * b, qb2 = qb + b;
            if (qb2 <= a) {
                return { ++q, _divmod_int(a - qb2, coef).first };
            } else {
                return { q, _divmod_int(a - qb, coef).first };
            }
        }

        std::string _to_string() const {
            if (this->empty()) return "0";
            std::ostringstream oss;
            auto it = this->rbegin();
            oss << *it;
            while (++it != this->rend()) {
                oss << std::setw(9) << std::setfill('0') << *it;
            }
            return oss.str();
        }
    };
} // namespace suisen


#endif // SUISEN_UNSIGNED_BIGINT
