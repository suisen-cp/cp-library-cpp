---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/bigint.hpp
    title: library/math/bigint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_A
  bundledCode: "#line 1 \"test/src/math/bigint/NTL_2_A.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_A\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/math/bigint.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#line 7 \"library/math/bigint.hpp\"\n#include <vector>\n\n\
    namespace suisen {\n    struct BigInt {\n        BigInt() : BigInt(0) {}\n   \
    \     template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        BigInt(T v) {\n            if (v < 0) {\n              \
    \  negative = true;\n                v = -v;\n            } else {\n         \
    \       negative = false;\n            }\n            for (; v; v /= 10) d.push_back(v\
    \ % 10);\n            ensure_size(1);\n            fix_sign();\n        }\n  \
    \      BigInt(const std::string &s) {\n            negative = false;\n       \
    \     for (auto it = s.rbegin(); it != s.rend(); ++it) {\n                if (*it\
    \ == '-') {\n                    negative = true;\n                } else {\n\
    \                    int v = *it - '0';\n                    assert(0 <= v and\
    \ v <= 9);\n                    d.push_back(v);\n                }\n         \
    \   }\n            ensure_size(1);\n            fix_sign();\n        }\n\n   \
    \     void swap(BigInt &other) { d.swap(other.d), std::swap(negative, other.negative);\
    \ }\n\n        friend int compare_abs(const BigInt &lhs, const BigInt &rhs) {\n\
    \            if (lhs.d.size() != rhs.d.size()) return lhs.d.size() < rhs.d.size()\
    \ ? -1 : +1;\n            for (size_t i = lhs.d.size(); i --> 0;) {\n        \
    \        if (lhs.d[i] != rhs.d[i]) return lhs.d[i] < rhs.d[i] ? -1 : +1;\n   \
    \         }\n            return 0;\n        }\n        friend int compare(const\
    \ BigInt &lhs, const BigInt &rhs) {\n            if (lhs.negative != rhs.negative)\
    \ return lhs.negative ? -1 : +1;\n            int res = compare_abs(lhs, rhs);\n\
    \            return lhs.negative ? -res : +res;\n        }\n        friend bool\
    \ operator< (const BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs)\
    \ <  0; }\n        friend bool operator<=(const BigInt &lhs, const BigInt &rhs)\
    \ { return compare(lhs, rhs) <= 0; }\n        friend bool operator> (const BigInt\
    \ &lhs, const BigInt &rhs) { return compare(lhs, rhs) >  0; }\n        friend\
    \ bool operator>=(const BigInt &lhs, const BigInt &rhs) { return compare(lhs,\
    \ rhs) >= 0; }\n        friend bool operator==(const BigInt &lhs, const BigInt\
    \ &rhs) { return compare(lhs, rhs) == 0; }\n        friend bool operator!=(const\
    \ BigInt &lhs, const BigInt &rhs) { return compare(lhs, rhs) != 0; }\n\n     \
    \   operator bool() const { return d != std::vector<int32_t>{ 0 }; }\n\n     \
    \   BigInt operator+() const {\n            return *this;\n        }\n       \
    \ BigInt operator-() const {\n            BigInt res = *this;\n            res.negative\
    \ = not res.negative;\n            res.fix_sign();\n            return res;\n\
    \        }\n\n        friend BigInt operator+(const BigInt &lhs, const BigInt\
    \ &rhs) {\n            if (not rhs) return lhs;\n            if (lhs.negative\
    \ == rhs.negative) {\n                BigInt res = BigInt::add_unsigned(lhs.d,\
    \ rhs.d);\n                res.negative = lhs.negative;\n                res.fix_sign();\n\
    \                return res;\n            } else {\n                return lhs\
    \ - (-rhs);\n            }\n        }\n        friend BigInt operator-(const BigInt\
    \ &lhs, const BigInt &rhs) {\n            if (not rhs) return lhs;\n         \
    \   if (lhs.negative == rhs.negative) {\n                int c = compare_abs(lhs,\
    \ rhs);\n                BigInt res;\n                if (c >= 0) {\n        \
    \            res = BigInt::sub_unsigned(lhs.d, rhs.d);\n                } else\
    \ {\n                    res = BigInt::sub_unsigned(rhs.d, lhs.d);\n         \
    \           res.negative = not res.negative;\n                }\n            \
    \    if (lhs.negative) res.negative = not res.negative;\n                res.fix_sign();\n\
    \                return res;\n            } else {\n                return lhs\
    \ + (-rhs);\n            }\n        }\n        friend BigInt operator*(const BigInt\
    \ &lhs, const BigInt &rhs) { return karatsuba(lhs, rhs); }\n\n        BigInt&\
    \ operator+=(const BigInt &rhs) { return *this = *this + rhs; }\n        BigInt&\
    \ operator-=(const BigInt &rhs) { return *this = *this - rhs; }\n        BigInt&\
    \ operator*=(const BigInt &rhs) { return *this = *this * rhs; }\n\n        BigInt&\
    \ operator++() { return *this += BigInt(1); }\n        BigInt& operator--() {\
    \ return *this -= BigInt(1); }\n        BigInt operator++(int) { return std::exchange(*this,\
    \ *this + BigInt(1)); }\n        BigInt operator--(int) { return std::exchange(*this,\
    \ *this - BigInt(1)); }\n\n        BigInt& muleq_pow_of_10(size_t shamt) {\n \
    \           if (*this) d.insert(d.begin(), shamt, 0);\n            return *this;\n\
    \        }\n        BigInt mul_pow_of_10(size_t shamt) {\n            return BigInt(*this).muleq_pow_of_10(shamt);\n\
    \        }\n        BigInt& diveq_pow_of_10(size_t shamt) {\n            d.erase(d.begin(),\
    \ d.begin() + std::min(d.size() - 1, shamt));\n            fix_sign();\n     \
    \       return *this;\n        }\n        BigInt div_pow_of_10(size_t shamt) {\n\
    \            return BigInt(*this).diveq_pow_of_10(shamt);\n        }\n\n     \
    \   friend std::ostream& operator<<(std::ostream &out, const BigInt &v) {\n  \
    \          if (v.negative) out << '-';\n            for (auto it = v.d.rbegin();\
    \ it != v.d.rend(); ++it) out << *it;\n            return out;\n        }\n  \
    \      friend std::istream& operator>>(std::istream &in, BigInt &v) {\n      \
    \      std::string s;\n            in >> s;\n            v = BigInt(std::move(s));\n\
    \            return in;\n        }\n\n    private:\n        bool negative;\n \
    \       std::vector<int32_t> d;\n\n        BigInt(std::vector<int32_t> &&d) :\
    \ negative(false), d(std::move(d)) {}\n        BigInt(const std::vector<int32_t>\
    \ &d) : negative(false), d(d) {}\n        BigInt(std::vector<int32_t>::const_iterator\
    \ start, std::vector<int32_t>::const_iterator last) : negative(false), d(start,\
    \ last) {}\n\n        BigInt substr(size_t l, size_t r) const { return BigInt(d.begin()\
    \ + l, d.begin() + r); }\n\n        void ensure_size(size_t n) { if (d.size()\
    \ < n) d.resize(n, 0); }\n\n        void cut_leading_zeros() { while (d.size()\
    \ > 1 and d.back() == 0) d.pop_back(); }\n\n        void fix_sign() {\n      \
    \      if (not *this) negative = false;\n        }\n\n        void fix_carry()\
    \ {\n            int32_t carry = 0;\n            for (size_t i = 0; i < d.size();\
    \ ++i) {\n                d[i] += carry;\n                int32_t q = d[i] / 10,\
    \ r = d[i] % 10;\n                if (r < 0) --q, r += 10;\n                carry\
    \ = q, d[i] = r;\n            }\n            for (; carry; carry /= 10) d.push_back(carry\
    \ % 10);\n            cut_leading_zeros();\n        }\n\n        static BigInt\
    \ add_unsigned(std::vector<int32_t> lhs, const std::vector<int32_t> &rhs) {\n\
    \            if (lhs.size() < rhs.size()) return add_unsigned(rhs, lhs);\n   \
    \         for (size_t i = 0; i < rhs.size(); ++i) lhs[i] += rhs[i];\n        \
    \    BigInt res(lhs);\n            res.fix_carry();\n            return res;\n\
    \        }\n        static BigInt sub_unsigned(std::vector<int32_t> lhs, const\
    \ std::vector<int32_t> &rhs) {\n            assert(lhs.size() >= rhs.size());\n\
    \            for (size_t i = 0; i < rhs.size(); ++i) lhs[i] -= rhs[i];\n     \
    \       BigInt res(lhs);\n            res.fix_carry();\n            return res;\n\
    \        }\n\n        static BigInt naive_multiplication(const BigInt &lhs, const\
    \ BigInt &rhs) {\n            size_t n = lhs.d.size(), m = rhs.d.size();\n   \
    \         BigInt res;\n            res.ensure_size(lhs.d.size() + rhs.d.size());\n\
    \            for (size_t i = 0; i < n; ++i) {\n                for (size_t j =\
    \ 0; j < m; ++j) res.d[i + j] += lhs.d[i] * rhs.d[j];\n            }\n       \
    \     res.fix_carry();\n            res.cut_leading_zeros();\n            res.negative\
    \ = lhs.negative ^ rhs.negative;\n            res.fix_sign();\n            return\
    \ res;\n        }\n        static BigInt karatsuba(const BigInt &lhs, const BigInt\
    \ &rhs) {\n            constexpr size_t THRESHOLD_NAIVE_MULTIPLICATION = 100;\n\
    \            if (lhs.d.size() < rhs.d.size()) return karatsuba(rhs, lhs);\n  \
    \          const size_t k = lhs.d.size(), l = rhs.d.size();\n            if (l\
    \ <= THRESHOLD_NAIVE_MULTIPLICATION) return naive_multiplication(lhs, rhs);\n\
    \            BigInt res;\n            if (k >= 2 * l) {\n                for (size_t\
    \ i = 0; i < k; i += l) res += karatsuba(lhs.substr(i, std::min(i + l, k)), rhs).muleq_pow_of_10(i);\n\
    \            } else {\n                size_t m = k / 2;\n                BigInt\
    \ ld(lhs.d.begin(), lhs.d.begin() + m), lu(lhs.d.begin() + m, lhs.d.end());\n\
    \                BigInt rd(rhs.d.begin(), rhs.d.begin() + m), ru(rhs.d.begin()\
    \ + m, rhs.d.end());\n                BigInt res_d = karatsuba(ld, rd), res_u\
    \ = karatsuba(lu, ru);\n                BigInt res_m = karatsuba(lu + ld, ru +\
    \ rd) - (res_d + res_u);\n                res = res_u.muleq_pow_of_10(2 * m) +\
    \ res_m.muleq_pow_of_10(m) + res_d;\n            }\n            res.fix_carry();\n\
    \            res.cut_leading_zeros();\n            res.negative = lhs.negative\
    \ ^ rhs.negative;\n            res.fix_sign();\n            return res;\n    \
    \    }\n    };\n} // namespace suisen\n\n\n\n#line 6 \"test/src/math/bigint/NTL_2_A.test.cpp\"\
    \nusing suisen::BigInt;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    BigInt a, b;\n    std::cin >> a >> b;\n   \
    \ std::cout << a + b << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_A\"\
    \n\n#include <iostream>\n\n#include \"library/math/bigint.hpp\"\nusing suisen::BigInt;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    BigInt a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << std::endl;\n\
    \    return 0;\n}"
  dependsOn:
  - library/math/bigint.hpp
  isVerificationFile: true
  path: test/src/math/bigint/NTL_2_A.test.cpp
  requiredBy: []
  timestamp: '2021-11-28 20:20:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/bigint/NTL_2_A.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/bigint/NTL_2_A.test.cpp
- /verify/test/src/math/bigint/NTL_2_A.test.cpp.html
title: test/src/math/bigint/NTL_2_A.test.cpp
---
