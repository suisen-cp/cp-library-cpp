#ifndef SUISEN_STRING_BIGINT
#define SUISEN_STRING_BIGINT

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace suisen {
    struct BigInt {
        BigInt() : BigInt(0) {}
        template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
        BigInt(T v) {
            if (v < 0) {
                negative = true;
                v = -v;
            } else {
                negative = false;
            }
            for (; v; v /= 10) d.push_back(v % 10);
            ensure_size(1);
            fix_sign();
        }
        BigInt(const std::string &s) {
            negative = false;
            for (auto it = s.rbegin(); it != s.rend(); ++it) {
                if (*it == '-') {
                    negative = true;
                } else {
                    int v = *it - '0';
                    assert(0 <= v and v <= 9);
                    d.push_back(v);
                }
            }
            ensure_size(1);
            fix_sign();
        }

        void swap(BigInt &other) { d.swap(other.d), std::swap(negative, other.negative); }

        friend int compare_abs(const BigInt &lhs, const BigInt &rhs) {
            if (lhs.d.size() != rhs.d.size()) return lhs.d.size() < rhs.d.size() ? -1 : +1;
            for (size_t i = lhs.d.size(); i --> 0;) {
                if (lhs.d[i] != rhs.d[i]) return lhs.d[i] < rhs.d[i] ? -1 : +1;
            }
            return 0;
        }
        friend int compare(const BigInt &lhs, const BigInt &rhs) {
            if (lhs.negative != rhs.negative) return lhs.negative ? -1 : +1;
            int res = compare_abs(lhs, rhs);
            return lhs.negative ? -res : +res;
        }
        friend bool operator< (const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) <  0; }
        friend bool operator<=(const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) <= 0; }
        friend bool operator> (const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) >  0; }
        friend bool operator>=(const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) >= 0; }
        friend bool operator==(const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) == 0; }
        friend bool operator!=(const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) != 0; }

        operator bool() const { return d != std::vector<int32_t>{ 0 }; }

        BigInt operator+() const {
            return *this;
        }
        BigInt operator-() const {
            BigInt res = *this;
            res.negative = not res.negative;
            res.fix_sign();
            return res;
        }

        friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
            if (not rhs) return lhs;
            if (lhs.negative == rhs.negative) {
                BigInt res = BigInt::add_unsigned(lhs.d, rhs.d);
                res.negative = lhs.negative;
                res.fix_sign();
                return res;
            } else {
                return lhs - (-rhs);
            }
        }
        friend BigInt operator-(const BigInt &lhs, const BigInt &rhs) {
            if (not rhs) return lhs;
            if (lhs.negative == rhs.negative) {
                int c = compare_abs(lhs, rhs);
                BigInt res;
                if (c >= 0) {
                    res = BigInt::sub_unsigned(lhs.d, rhs.d);
                } else {
                    res = BigInt::sub_unsigned(rhs.d, lhs.d);
                    res.negative = not res.negative;
                }
                if (lhs.negative) res.negative = not res.negative;
                res.fix_sign();
                return res;
            } else {
                return lhs + (-rhs);
            }
        }
        friend BigInt operator*(const BigInt &lhs, const BigInt &rhs) { return karatsuba(lhs, rhs); }

        BigInt& operator+=(const BigInt &rhs) { return *this = *this + rhs; }
        BigInt& operator-=(const BigInt &rhs) { return *this = *this - rhs; }
        BigInt& operator*=(const BigInt &rhs) { return *this = *this * rhs; }

        BigInt& operator++() { return *this += BigInt(1); }
        BigInt& operator--() { return *this -= BigInt(1); }
        BigInt operator++(int) { return std::exchange(*this, *this + BigInt(1)); }
        BigInt operator--(int) { return std::exchange(*this, *this - BigInt(1)); }

        BigInt& muleq_pow_of_10(size_t shamt) {
            if (*this) d.insert(d.begin(), shamt, 0);
            return *this;
        }
        BigInt mul_pow_of_10(size_t shamt) {
            return BigInt(*this).muleq_pow_of_10(shamt);
        }
        BigInt& diveq_pow_of_10(size_t shamt) {
            d.erase(d.begin(), d.begin() + std::min(d.size() - 1, shamt));
            fix_sign();
            return *this;
        }
        BigInt div_pow_of_10(size_t shamt) {
            return BigInt(*this).diveq_pow_of_10(shamt);
        }

        friend std::ostream& operator<<(std::ostream &out, const BigInt &v) {
            if (v.negative) out << '-';
            for (auto it = v.d.rbegin(); it != v.d.rend(); ++it) out << *it;
            return out;
        }
        friend std::istream& operator>>(std::istream &in, BigInt &v) {
            std::string s;
            in >> s;
            v = BigInt(std::move(s));
            return in;
        }

    private:
        bool negative;
        std::vector<int32_t> d;

        BigInt(std::vector<int32_t> &&d) : negative(false), d(std::move(d)) {}
        BigInt(const std::vector<int32_t> &d) : negative(false), d(d) {}
        BigInt(std::vector<int32_t>::const_iterator start, std::vector<int32_t>::const_iterator last) : negative(false), d(start, last) {}

        BigInt substr(size_t l, size_t r) const { return BigInt(d.begin() + l, d.begin() + r); }

        void ensure_size(size_t n) { if (d.size() < n) d.resize(n, 0); }

        void cut_leading_zeros() { while (d.size() > 1 and d.back() == 0) d.pop_back(); }

        void fix_sign() {
            if (not *this) negative = false;
        }

        void fix_carry() {
            int32_t carry = 0;
            for (size_t i = 0; i < d.size(); ++i) {
                d[i] += carry;
                int32_t q = d[i] / 10, r = d[i] % 10;
                if (r < 0) --q, r += 10;
                carry = q, d[i] = r;
            }
            for (; carry; carry /= 10) d.push_back(carry % 10);
            cut_leading_zeros();
        }

        static BigInt add_unsigned(std::vector<int32_t> lhs, const std::vector<int32_t> &rhs) {
            if (lhs.size() < rhs.size()) return add_unsigned(rhs, lhs);
            for (size_t i = 0; i < rhs.size(); ++i) lhs[i] += rhs[i];
            BigInt res(lhs);
            res.fix_carry();
            return res;
        }
        static BigInt sub_unsigned(std::vector<int32_t> lhs, const std::vector<int32_t> &rhs) {
            assert(lhs.size() >= rhs.size());
            for (size_t i = 0; i < rhs.size(); ++i) lhs[i] -= rhs[i];
            BigInt res(lhs);
            res.fix_carry();
            return res;
        }

        static BigInt naive_multiplication(const BigInt &lhs, const BigInt &rhs) {
            size_t n = lhs.d.size(), m = rhs.d.size();
            BigInt res;
            res.ensure_size(lhs.d.size() + rhs.d.size());
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < m; ++j) res.d[i + j] += lhs.d[i] * rhs.d[j];
            }
            res.fix_carry();
            res.cut_leading_zeros();
            res.negative = lhs.negative ^ rhs.negative;
            res.fix_sign();
            return res;
        }
        static BigInt karatsuba(const BigInt &lhs, const BigInt &rhs) {
            constexpr size_t THRESHOLD_NAIVE_MULTIPLICATION = 100;
            if (lhs.d.size() < rhs.d.size()) return karatsuba(rhs, lhs);
            const size_t k = lhs.d.size(), l = rhs.d.size();
            if (l <= THRESHOLD_NAIVE_MULTIPLICATION) return naive_multiplication(lhs, rhs);
            BigInt res;
            if (k >= 2 * l) {
                for (size_t i = 0; i < k; i += l) res += karatsuba(lhs.substr(i, std::min(i + l, k)), rhs).muleq_pow_of_10(i);
            } else {
                size_t m = k / 2;
                BigInt ld(lhs.d.begin(), lhs.d.begin() + m), lu(lhs.d.begin() + m, lhs.d.end());
                BigInt rd(rhs.d.begin(), rhs.d.begin() + m), ru(rhs.d.begin() + m, rhs.d.end());
                BigInt res_d = karatsuba(ld, rd), res_u = karatsuba(lu, ru);
                BigInt res_m = karatsuba(lu + ld, ru + rd) - (res_d + res_u);
                res = res_u.muleq_pow_of_10(2 * m) + res_m.muleq_pow_of_10(m) + res_d;
            }
            res.fix_carry();
            res.cut_leading_zeros();
            res.negative = lhs.negative ^ rhs.negative;
            res.fix_sign();
            return res;
        }
    };
} // namespace suisen


#endif // SUISEN_STRING_BIGINT
