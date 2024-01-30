---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/arbitrary_mod_convolution.hpp
    title: "\u4EFB\u610F $\\mathrm{mod}$ \u7573\u307F\u8FBC\u307F"
  - icon: ':question:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  - icon: ':question:'
    path: library/math/unsigned_bigint.hpp
    title: Unsigned Bigint
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_A.test.cpp
    title: test/src/math/bigint/NTL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_B.test.cpp
    title: test/src/math/bigint/NTL_2_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_D.test.cpp
    title: test/src/math/bigint/NTL_2_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_E.test.cpp
    title: test/src/math/bigint/NTL_2_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_F.test.cpp
    title: test/src/math/bigint/NTL_2_F.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/addition_of_big_integers.test.cpp
    title: test/src/math/bigint/addition_of_big_integers.test.cpp
  - icon: ':x:'
    path: test/src/math/bigint/many_aplusb_128bit.test.cpp
    title: test/src/math/bigint/many_aplusb_128bit.test.cpp
  - icon: ':x:'
    path: test/src/math/bigint/multiplication_of_big_integers.test.cpp
    title: test/src/math/bigint/multiplication_of_big_integers.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/bigint.hpp\"\n\n\n\n#line 1 \"library/math/unsigned_bigint.hpp\"\
    \n\n\n\n#include <iomanip>\n#include <iostream>\n#include <sstream>\n#include\
    \ <vector>\n\n#line 1 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\n\
    \n\n#include <atcoder/convolution>\n#line 6 \"library/convolution/arbitrary_mod_convolution.hpp\"\
    \n\n#line 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution_naive.hpp\"\
    \n\nnamespace suisen::internal {\n    template <typename T, typename R = T>\n\
    \    std::vector<R> convolution_naive(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\n        const int n = a.size(), m = b.size();\n        std::vector<R>\
    \ c(n + m - 1);\n        if (n < m) {\n            for (int j = 0; j < m; j++)\
    \ for (int i = 0; i < n; i++) c[i + j] += R(a[i]) * b[j];\n        } else {\n\
    \            for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j]\
    \ += R(a[i]) * b[j];\n        }\n        return c;\n    }\n} // namespace suisen\n\
    \n\n\n#line 8 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename mint, atcoder::internal::is_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        int n = int(a.size()), m = int(b.size());\n\
    \n        if constexpr (atcoder::internal::is_static_modint<mint>::value) {\n\
    \            if constexpr (not (mint::mod() & 63)) {\n                int maxz\
    \ = 1;\n                while (not ((mint::mod() - 1) & maxz)) maxz <<= 1;\n \
    \               int z = 1;\n                while (z < n + m - 1) z <<= 1;\n \
    \               if (z <= maxz) return atcoder::convolution<mint>(a, b);\n    \
    \        }\n        }\n\n        if (n == 0 or m == 0) return {};\n        if\
    \ (std::min(n, m) <= 120) return internal::convolution_naive(a, b);\n\n      \
    \  static constexpr long long MOD1 = 754974721;  // 2^24\n        static constexpr\
    \ long long MOD2 = 167772161;  // 2^25\n        static constexpr long long MOD3\
    \ = 469762049;  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n\
    \        static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1,\
    \ MOD2).second;\n        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        std::vector<int> a2(n), b2(m);\n        for (int i\
    \ = 0; i < n; ++i) a2[i] = a[i].val();\n        for (int i = 0; i < m; ++i) b2[i]\
    \ = b[i].val();\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n   \
    \     auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n\n        const long long m1m2 = mint(M1M2).val();\n        std::vector<mint>\
    \ c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n            //\
    \ Garner's Algorithm\n            // X = x1 + x2 * m1 + x3 * m1 * m2\n       \
    \     // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 *\
    \ m1) / m2 (mod m3)\n            long long x1 = c1[i];\n            long long\
    \ x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n     \
    \       long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + x3 * m1m2;\n    \
    \    }\n        return c;\n    }\n\n    std::vector<__uint128_t> convolution_int(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n        int n = int(a.size()),\
    \ m = int(b.size());\n\n        auto check_nonnegative = [](int e) { return e\
    \ >= 0; };\n        assert(std::all_of(a.begin(), a.end(), check_nonnegative));\n\
    \        assert(std::all_of(b.begin(), b.end(), check_nonnegative));\n\n     \
    \   if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 120) return\
    \ internal::convolution_naive<int, __uint128_t>(a, b);\n\n        static constexpr\
    \ long long MOD1 = 754974721;  // 2^24\n        static constexpr long long MOD2\
    \ = 167772161;  // 2^25\n        static constexpr long long MOD3 = 469762049;\
    \  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n        static\
    \ constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;\n\
    \        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        auto c1 = atcoder::convolution<MOD1>(a, b);\n     \
    \   auto c2 = atcoder::convolution<MOD2>(a, b);\n        auto c3 = atcoder::convolution<MOD3>(a,\
    \ b);\n        std::vector<__uint128_t> c(n + m - 1);\n        for (int i = 0;\
    \ i < n + m - 1; ++i) {\n            // Garner's Algorithm\n            // X =\
    \ x1 + x2 * m1 + x3 * m1 * m2\n            // x1 = c1[i], x2 = (c2[i] - x1) /\
    \ m1 (mod m2), x3 = (c3[i] - x1 - x2 * m1) / m2 (mod m3)\n            int x1 =\
    \ c1[i];\n            int x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n\
    \            int x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + __uint128_t(x3) *\
    \ M1M2;\n        }\n        return c;\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 10 \"library/math/unsigned_bigint.hpp\"\n\nnamespace suisen {\n    struct unsigned_bigint\
    \ : private std::vector<int> {\n        static constexpr int D = 1000000000;\n\
    \        static constexpr int LogD = 9;\n\n        static inline struct { operator\
    \ unsigned_bigint() const { return unsigned_bigint{}; }; } const ZERO{};\n   \
    \     static inline struct { operator unsigned_bigint() const { return unsigned_bigint{\
    \ 1 }; }; } const ONE{};\n\n        unsigned_bigint() : vector() {}\n\n      \
    \  template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        unsigned_bigint(T v) {\n            if constexpr (std::is_signed_v<T>)\
    \ {\n                assert(v >= 0);\n            }\n            for (; v; v /=\
    \ D) {\n                this->push_back(v % D);\n            }\n        }\n  \
    \      unsigned_bigint(const std::string& s) : vector() {\n            int siz\
    \ = s.size();\n            for (int i = siz; i > 0; i -= LogD) {\n           \
    \     int l = std::max(0, i - LogD);\n                int r = i;\n           \
    \     int& v = this->emplace_back();\n                for (int j = l; j < r; ++j)\
    \ {\n                    int d = s[j] - '0';\n                    assert(0 <=\
    \ d and d <= 9);\n                    v = v * 10 + d;\n                }\n   \
    \         }\n        }\n        unsigned_bigint(const char* s) : unsigned_bigint(std::string(s))\
    \ {}\n\n        operator bool() const {\n            return not this->empty();\n\
    \        }\n\n        friend bool operator==(const unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            if (a.size() != b.size()) {\n                return false;\n\
    \            }\n            for (size_t i = 0; i < a.size(); ++i) {\n        \
    \        if (a[i] != b[i]) return false;\n            }\n            return true;\n\
    \        }\n        friend bool operator!=(const unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            return not (a == b);\n        }\n        friend bool operator<(const\
    \ unsigned_bigint& a, const unsigned_bigint& b) {\n            if (a.size() !=\
    \ b.size()) {\n                return a.size() < b.size();\n            }\n  \
    \          for (size_t i = a.size(); i-- > 0;) {\n                if (a[i] !=\
    \ b[i]) return a[i] < b[i];\n            }\n            return false;\n      \
    \  }\n        friend bool operator<=(const unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            return not (b < a);\n        }\n        friend bool operator>(const\
    \ unsigned_bigint& a, const unsigned_bigint& b) {\n            return b < a;\n\
    \        }\n        friend bool operator>=(const unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            return not (a < b);\n        }\n\n        friend unsigned_bigint&\
    \ operator<<=(unsigned_bigint& a, int shamt) {\n            if (a) a.insert(a.begin(),\
    \ shamt, 0);\n            return a;\n        }\n        friend unsigned_bigint\
    \ operator<<(unsigned_bigint a, int shamt) {\n            a <<= shamt;\n     \
    \       return a;\n        }\n        friend unsigned_bigint& operator>>=(unsigned_bigint&\
    \ a, int shamt) {\n            a.erase(a.begin(), a.begin() + std::min<int>(shamt,\
    \ a.size()));\n            return a;\n        }\n        friend unsigned_bigint\
    \ operator>>(unsigned_bigint a, int shamt) {\n            a >>= shamt;\n     \
    \       return a;\n        }\n\n        unsigned_bigint& operator++() {\n    \
    \        return _incr_assign(*this);\n        }\n        unsigned_bigint operator++(int)\
    \ {\n            unsigned_bigint res = *this;\n            _incr_assign(*this);\n\
    \            return res;\n        }\n        unsigned_bigint& operator--() {\n\
    \            return _decr_assign(*this);\n        }\n        unsigned_bigint operator--(int)\
    \ {\n            unsigned_bigint res = *this;\n            _decr_assign(*this);\n\
    \            return res;\n        }\n        friend unsigned_bigint& operator+=(unsigned_bigint&\
    \ a, const unsigned_bigint& b) {\n            return _add_assign(a, b);\n    \
    \    }\n        friend unsigned_bigint operator+(const unsigned_bigint& a, const\
    \ unsigned_bigint& b) {\n            unsigned_bigint c = a;\n            c +=\
    \ b;\n            return c;\n        }\n        friend unsigned_bigint& operator-=(unsigned_bigint&\
    \ a, const unsigned_bigint& b) {\n            return _sub_assign(a, b);\n    \
    \    }\n        friend unsigned_bigint operator-(const unsigned_bigint& a, const\
    \ unsigned_bigint& b) {\n            unsigned_bigint c = a;\n            c -=\
    \ b;\n            return c;\n        }\n        friend unsigned_bigint& operator*=(unsigned_bigint&\
    \ a, const unsigned_bigint& b) {\n            return a = a * b;\n        }\n \
    \       friend unsigned_bigint operator*(const unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            return _mul_fft(a, b);\n        }\n\n        static std::pair<unsigned_bigint,\
    \ unsigned_bigint> divmod(unsigned_bigint a, unsigned_bigint b) {\n          \
    \  return _divmod(a, b);\n        }\n        friend unsigned_bigint& operator/=(unsigned_bigint&\
    \ a, const unsigned_bigint& b) {\n            return a = a / b;\n        }\n \
    \       friend unsigned_bigint operator/(const unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            return divmod(a, b).first;\n        }\n        friend unsigned_bigint&\
    \ operator%=(unsigned_bigint& a, const unsigned_bigint& b) {\n            return\
    \ a = a % b;\n        }\n        friend unsigned_bigint operator%(const unsigned_bigint&\
    \ a, const unsigned_bigint& b) {\n            return divmod(a, b).second;\n  \
    \      }\n\n#define CAST_PRIMITIVE(type)                                     \
    \   \\\n    operator type() const {                                         \\\
    \n        type res = 0;                                               \\\n   \
    \     for (auto it = this->rbegin(); it != this->rend(); ++it) {  \\\n       \
    \     res = res * D + *it;                                    \\\n        }  \
    \                                                         \\\n        return res;\
    \                                                 \\\n    }                  \
    \                                             \\\n\n        CAST_PRIMITIVE(unsigned\
    \ int)\n            CAST_PRIMITIVE(unsigned long)\n            CAST_PRIMITIVE(unsigned\
    \ long long)\n            CAST_PRIMITIVE(__uint128_t)\n            CAST_PRIMITIVE(float)\n\
    \            CAST_PRIMITIVE(double)\n            CAST_PRIMITIVE(long double)\n\
    #undef CAST_PRIMITIVE\n\n#define CAST_SIGNED_INT(type)                       \
    \            \\\n    operator type() const {                                 \
    \    \\\n        return static_cast<std::make_unsigned_t<type>>(*this);  \\\n\
    \    }                                                           \\\n\n      \
    \      CAST_SIGNED_INT(int)\n            CAST_SIGNED_INT(long)\n            CAST_SIGNED_INT(long\
    \ long)\n#undef CAST_SIGNED_INT\n\n            operator __int128_t() const {\n\
    \            return static_cast<__uint128_t>(*this);\n        }\n\n        operator\
    \ std::string() const {\n            return _to_string();\n        }\n\n     \
    \   friend std::istream& operator>>(std::istream& in, unsigned_bigint& v) {\n\
    \            std::string s;\n            in >> s, v = s;\n            return in;\n\
    \        }\n        friend std::ostream& operator<<(std::ostream& out, const unsigned_bigint&\
    \ v) {\n            return out << v._to_string();\n        }\n    private:\n \
    \       using std::vector<int>::vector;\n\n        void _check_leading_zeros()\
    \ const {\n            assert(this->empty() or this->back());\n        }\n\n \
    \       void _cut_leading_zeros() {\n            while (this->size() and this->back()\
    \ == 0) this->pop_back();\n        }\n\n        static unsigned_bigint& _incr_assign(unsigned_bigint&\
    \ a) {\n            for (int& e : a) {\n                if (++e != D) return a;\n\
    \                e -= D;\n            }\n            a.push_back(1);\n       \
    \     return a;\n        }\n        static unsigned_bigint& _decr_assign(unsigned_bigint&\
    \ a) {\n            assert(a.size());\n            for (int& e : a) {\n      \
    \          if (--e >= 0) break;\n                e += D;\n            }\n    \
    \        a._cut_leading_zeros();\n            return a;\n        }\n\n       \
    \ static unsigned_bigint& _add_assign(unsigned_bigint& a, const unsigned_bigint&\
    \ b) {\n            if (a.size() < b.size()) a.resize(b.size());\n           \
    \ int carry = 0;\n            for (size_t i = 0; i < a.size(); ++i) {\n      \
    \          if (i >= b.size()) {\n                    if (carry) {\n          \
    \              ++a[i];\n                    } else break;\n                } else\
    \ {\n                    a[i] += b[i] + carry;\n                }\n          \
    \      if (a[i] >= D) {\n                    a[i] -= D;\n                    carry\
    \ = 1;\n                } else {\n                    carry = 0;\n           \
    \     }\n            }\n            if (carry) a.push_back(1);\n            return\
    \ a;\n        }\n\n        static unsigned_bigint& _sub_assign(unsigned_bigint&\
    \ a, const unsigned_bigint& b) {\n            assert(a.size() >= b.size());\n\
    \            int borrow = 0;\n            for (size_t i = 0; i < a.size(); ++i)\
    \ {\n                if (i >= b.size()) {\n                    if (borrow) {\n\
    \                        --a[i];\n                    } else break;\n        \
    \        } else {\n                    a[i] -= b[i] + borrow;\n              \
    \  }\n                if (a[i] < 0) {\n                    a[i] += D;\n      \
    \              borrow = 1;\n                } else {\n                    borrow\
    \ = 0;\n                }\n            }\n            assert(not borrow);\n  \
    \          a._cut_leading_zeros();\n            return a;\n        }\n\n     \
    \   unsigned_bigint _cut(int l, int r) const {\n            r = std::min(r, static_cast<int>(this->size()));\n\
    \            unsigned_bigint v = l < r ? unsigned_bigint(this->begin() + l, this->begin()\
    \ + r) : ZERO;\n            v._cut_leading_zeros();\n            return v;\n \
    \       }\n\n        template <typename T>\n        static unsigned_bigint _build(const\
    \ std::vector<T>& dat) {\n            unsigned_bigint res;\n            T carry\
    \ = 0;\n            for (auto v : dat) {\n                carry += v;\n      \
    \          res.push_back(carry % D);\n                carry /= D;\n          \
    \  }\n            while (carry) {\n                res.push_back(carry % D);\n\
    \                carry /= D;\n            }\n            res._cut_leading_zeros();\n\
    \            return res;\n        }\n\n        static unsigned_bigint _mul_naive(const\
    \ unsigned_bigint& a, const unsigned_bigint& b) {\n            return _build(suisen::internal::convolution_naive<int,\
    \ __int128_t>(a, b));\n        }\n\n        static unsigned_bigint _mul_karatsuba(const\
    \ unsigned_bigint& a, const unsigned_bigint& b) {\n            if (std::min(a.size(),\
    \ b.size()) <= 64) {\n                return _mul_naive(a, b);\n            }\n\
    \            const int m = std::max(a.size(), b.size()) / 2;\n\n            unsigned_bigint\
    \ lo_a = a._cut(0, m), hi_a = a._cut(m, a.size());\n            unsigned_bigint\
    \ lo_b = b._cut(0, m), hi_b = b._cut(m, b.size());\n\n            unsigned_bigint\
    \ lo_c = lo_a * lo_b;\n            unsigned_bigint hi_c = hi_a * hi_b;\n\n   \
    \         bool neg = true;\n            unsigned_bigint md_a;\n            if\
    \ (hi_a >= lo_a) md_a = hi_a - lo_a;\n            else              md_a = lo_a\
    \ - hi_a, neg = not neg;\n            unsigned_bigint md_b;\n            if (hi_b\
    \ >= lo_b) md_b = hi_b - lo_b;\n            else              md_b = lo_b - hi_b,\
    \ neg = not neg;\n            unsigned_bigint md_ab = md_a * md_b;\n         \
    \   unsigned_bigint md_c = (hi_c << m) + lo_c + hi_c + lo_c._cut(m, lo_c.size());\n\
    \            if (neg) md_c -= md_ab;\n            else     md_c += md_ab;\n  \
    \          unsigned_bigint c = (md_c << m) + lo_c._cut(0, m);\n            c._cut_leading_zeros();\n\
    \            return c;\n        }\n\n        static unsigned_bigint _mul_fft(const\
    \ unsigned_bigint& a, const unsigned_bigint& b) {\n            if (std::min(a.size(),\
    \ b.size()) <= 64) {\n                return _mul_naive(a, b);\n            }\n\
    \            if (std::max(a.size(), b.size()) <= 200) {\n                return\
    \ _mul_karatsuba(a, b);\n            }\n            return _build(suisen::convolution_int(a,\
    \ b));\n        }\n\n        // compare(a, D^k)\n        static int _compare_powD(const\
    \ unsigned_bigint& a, int k) {\n            const int dA = a.size();\n       \
    \     if (dA <= k) return -1;\n            if (dA >= k + 2) return +1;\n     \
    \       if (a[k] != 1) return +1;\n            for (int i = 0; i < k; ++i) {\n\
    \                if (a[i]) return +1;\n            }\n            return 0;\n\
    \        }\n        static unsigned_bigint _powD(int k) {\n            return\
    \ ONE << k;\n        }\n\n        static std::pair<unsigned_bigint, unsigned_bigint>\
    \ _divmod_int(const unsigned_bigint& a, const unsigned_bigint& b) {\n        \
    \    assert(b.size() == 1);\n            const int b0 = b.front();\n         \
    \   unsigned_bigint q;\n            long long r = 0;\n            for (auto it\
    \ = a.rbegin(); it != a.rend(); ++it) {\n                r = r * D + *it;\n  \
    \              q.push_back(r / b0);\n                r %= b0;\n            }\n\
    \            std::reverse(q.begin(), q.end());\n            q._cut_leading_zeros();\n\
    \            return { q, r ? unsigned_bigint{ int(r) } : ZERO };\n        }\n\n\
    \        static std::pair<unsigned_bigint, unsigned_bigint> _divmod_naive(unsigned_bigint&\
    \ a, unsigned_bigint& b) {\n            if (b.size() == 1) {\n               \
    \ return _divmod_int(a, b);\n            }\n            if (a < b) {\n       \
    \         return { ZERO, a };\n            }\n            const unsigned_bigint\
    \ coef{ D / (b.back() + 1) };\n            a *= coef;\n            b *= coef;\n\
    \            assert(2 * b.back() >= D);\n\n            unsigned_bigint q, r(a.end()\
    \ - b.size(), a.end());\n            for (int i = a.size() - b.size(); i >= 0;\
    \ --i) {\n                if (r.size() < b.size()) {\n                    q.push_back(0);\n\
    \                } else if (r.size() == b.size()) {\n                    if (r\
    \ >= b) {\n                        q.push_back(1);\n                        r\
    \ -= b;\n                    } else {\n                        q.push_back(0);\n\
    \                    }\n                } else {\n                    assert(r.size()\
    \ == b.size() + 1);\n                    int x = (static_cast<long long>(r.end()[-1])\
    \ * D + r.end()[-2]) / b.back();\n                    unsigned_bigint bx = b *\
    \ unsigned_bigint{ x };\n                    while (bx > r) bx -= b, --x;\n  \
    \                  while (bx + b <= r) bx += b, ++x;\n                    q.push_back(x);\n\
    \                    r = r - bx;\n                }\n                if (i) {\n\
    \                    r.insert(r.begin(), a[i - 1]);\n                }\n     \
    \       }\n            std::reverse(q.begin(), q.end());\n            q._cut_leading_zeros();\n\
    \            r._cut_leading_zeros();\n            return { q, _divmod_int(r, coef).first\
    \ };\n        }\n        static std::pair<unsigned_bigint, unsigned_bigint> _divmod_naive(const\
    \ unsigned_bigint& a, const unsigned_bigint& b) {\n            unsigned_bigint\
    \ a_ = a, b_ = b;\n            return _divmod_naive(a_, b_);\n        }\n\n  \
    \      // floor(D^n/b)\n        static unsigned_bigint _div_powD(int n, unsigned_bigint\
    \ b) {\n            assert(b.size() and 2 * b.back() >= D);\n\n            const\
    \ int dB = b.size();\n\n            int k = n - dB;\n            while (k > 64)\
    \ k = (k + 1) >> 1;\n            k = std::min(n, dB + k);\n\n            unsigned_bigint\
    \ c = _divmod_naive(_powD(k), b).first;\n            unsigned_bigint bc = b *\
    \ c;\n            for (; k < n; k = 2 * k - dB) {\n                // loop invariant:\
    \ c = floor(D^k/B)\n                bc.resize(k + 1);\n                int carry\
    \ = 0;\n                for (int i = 0; i < k; ++i) {\n                    bc[i]\
    \ = D - bc[i] + (i ? carry - 1 : 0);\n                    if (bc[i] >= D) {\n\
    \                        bc[i] -= D;\n                        carry = 1;\n   \
    \                 } else {\n                        carry = 0;\n             \
    \       }\n                }\n                ++bc[k];\n                c *= bc;\n\
    \                c.erase(c.begin(), c.begin() + dB);\n                bc = b *\
    \ c;\n                if (_compare_powD(bc + b, 2 * k - dB) <= 0) {\n        \
    \            ++c, bc += b;\n                }\n                assert(_compare_powD(bc\
    \ + b, 2 * k - dB) > 0);\n            }\n            // c = floor(D^k/b)\n   \
    \         c >>= k - n;\n            return c;\n        }\n\n        static std::pair<unsigned_bigint,\
    \ unsigned_bigint> _divmod(unsigned_bigint a, unsigned_bigint b) {\n         \
    \   assert(b.size());\n            if (std::min(static_cast<int>(b.size()), static_cast<int>(a.size())\
    \ - static_cast<int>(b.size())) <= 64) {\n                return _divmod_naive(a,\
    \ b);\n            }\n            if (a < b) {\n                return { ZERO,\
    \ a };\n            }\n\n            const unsigned_bigint coef{ D / (b.back()\
    \ + 1) };\n            a *= coef;\n            b *= coef;\n            assert(2\
    \ * b.back() >= D);\n\n            const int dA = a.size(), dB = b.size();\n \
    \           if (dA == dB) {\n                return { ONE, _divmod_int(a - b,\
    \ coef).first };\n            }\n            unsigned_bigint invB = _div_powD(dA,\
    \ b);\n            unsigned_bigint q = a * invB;\n            q.erase(q.begin(),\
    \ q.begin() + dA);\n            unsigned_bigint qb = q * b, qb2 = qb + b;\n  \
    \          if (qb2 <= a) {\n                return { ++q, _divmod_int(a - qb2,\
    \ coef).first };\n            } else {\n                return { q, _divmod_int(a\
    \ - qb, coef).first };\n            }\n        }\n\n        std::string _to_string()\
    \ const {\n            if (this->empty()) return \"0\";\n            std::ostringstream\
    \ oss;\n            auto it = this->rbegin();\n            oss << *it;\n     \
    \       while (++it != this->rend()) {\n                oss << std::setw(9) <<\
    \ std::setfill('0') << *it;\n            }\n            return oss.str();\n  \
    \      }\n    };\n} // namespace suisen\n\n\n\n#line 5 \"library/math/bigint.hpp\"\
    \n\nnamespace suisen {\n    struct bigint {\n        static inline struct { operator\
    \ bigint() const { return bigint{ unsigned_bigint::ZERO }; }; } const ZERO{};\n\
    \        static inline struct { operator bigint() const { return bigint{ unsigned_bigint::ONE\
    \ }; }; } const ONE{};\n\n        bigint() : _neg(false), _dat{} {}\n\n      \
    \  template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        bigint(T v) {\n            _neg = false;\n            if\
    \ constexpr (std::is_signed_v<T>) {\n                if (v < 0) {\n          \
    \          _neg = true;\n                    v = -v;\n                }\n    \
    \        }\n            _dat = unsigned_bigint(v);\n        }\n        bigint(const\
    \ std::string& s) {\n            if (s.front() == '-') {\n                _neg\
    \ = true;\n                _dat = unsigned_bigint(s.substr(1));\n            \
    \    fix_sign();\n            } else {\n                _neg = false;\n      \
    \          _dat = unsigned_bigint(s);\n            }\n        }\n        bigint(const\
    \ char* s) : bigint(std::string(s)) {}\n\n        bigint(const unsigned_bigint&\
    \ dat) : _neg(false), _dat(dat) {}\n        bigint(unsigned_bigint&& dat) : _neg(false),\
    \ _dat(std::move(dat)) {}\n\n        operator bool() const {\n            return\
    \ bool(_dat);\n        }\n\n        friend bool operator==(const bigint& a, const\
    \ bigint& b) {\n            if (a._neg xor b._neg) {\n                return false;\n\
    \            } else {\n                return a._dat == b._dat;\n            }\n\
    \        }\n        friend bool operator!=(const bigint& a, const bigint& b) {\n\
    \            return not (a == b);\n        }\n\n        friend bool operator<(const\
    \ bigint& a, const bigint& b) {\n            if (a._neg xor b._neg) {\n      \
    \          return a._neg;\n            } else if (a._neg) {\n                return\
    \ a._dat > b._dat;\n            } else {\n                return a._dat < b._dat;\n\
    \            }\n        }\n        friend bool operator<=(const bigint& a, const\
    \ bigint& b) {\n            return not (b < a);\n        }\n        friend bool\
    \ operator>(const bigint& a, const bigint& b) {\n            return b < a;\n \
    \       }\n        friend bool operator>=(const bigint& a, const bigint& b) {\n\
    \            return not (a < b);\n        }\n\n        friend bigint& operator<<=(bigint&\
    \ a, int shamt) {\n            a._dat <<= shamt;\n            return a;\n    \
    \    }\n        friend bigint operator<<(bigint a, int shamt) {\n            a\
    \ <<= shamt;\n            return a;\n        }\n        friend bigint& operator>>=(bigint&\
    \ a, int shamt) {\n            a._dat >>= shamt;\n            a.fix_sign();\n\
    \            return a;\n        }\n        friend bigint operator>>(bigint a,\
    \ int shamt) {\n            a >>= shamt;\n            a.fix_sign();\n        \
    \    return a;\n        }\n\n        bigint operator+() const {\n            return\
    \ *this;\n        }\n        bigint operator-() const {\n            return bigint(_dat,\
    \ not _neg);\n        }\n\n        bigint& operator++() {\n            if (_neg)\
    \ {\n                --_dat;\n                fix_sign();\n            } else\
    \ {\n                ++_dat;\n            }\n            return *this;\n     \
    \   }\n        bigint operator++(int) {\n            bigint res = *this;\n   \
    \         ++*this;\n            return res;\n        }\n        bigint& operator--()\
    \ {\n            if (_neg) {\n                ++_dat;\n            } else if (_dat)\
    \ {\n                --_dat;\n            } else {\n                _neg = true;\n\
    \                _dat = unsigned_bigint::ONE;\n            }\n            return\
    \ *this;\n        }\n        bigint operator--(int) {\n            bigint res\
    \ = *this;\n            --*this;\n            return res;\n        }\n       \
    \ friend bigint& operator+=(bigint& a, const bigint& b) {\n            if (a._neg\
    \ xor b._neg) {\n                if (a._dat >= b._dat) {\n                   \
    \ a._dat -= b._dat;\n                } else {\n                    a._dat = b._dat\
    \ - a._dat;\n                    a._neg = not a._neg;\n                }\n   \
    \             a.fix_sign();\n            } else {\n                a._dat += b._dat;\n\
    \            }\n            return a;\n        }\n        friend bigint operator+(const\
    \ bigint& a, const bigint& b) {\n            bigint c = a;\n            c += b;\n\
    \            return c;\n        }\n        friend bigint& operator-=(bigint& a,\
    \ const bigint& b) {\n            if (a._neg xor b._neg) {\n                a._dat\
    \ += b._dat;\n            } else {\n                if (a._dat >= b._dat) {\n\
    \                    a._dat -= b._dat;\n                } else {\n           \
    \         a._dat = b._dat - a._dat;\n                    a._neg = not a._neg;\n\
    \                }\n                a.fix_sign();\n            }\n           \
    \ return a;\n        }\n        friend bigint operator-(const bigint& a, const\
    \ bigint& b) {\n            bigint c = a;\n            c -= b;\n            return\
    \ c;\n        }\n        friend bigint& operator*=(bigint& a, const bigint& b)\
    \ {\n            return a = a * b;\n        }\n        friend bigint operator*(const\
    \ bigint& a, const bigint& b) {\n            return bigint(a._dat * b._dat, a._neg\
    \ xor b._neg);\n        }\n\n        static std::pair<bigint, bigint> divmod(bigint\
    \ a, bigint b) {\n            auto [q, r] = unsigned_bigint::divmod(a._dat, b._dat);\n\
    \            return { bigint(std::move(q), a._neg xor b._neg), bigint(std::move(r),\
    \ a._neg) };\n        }\n        friend bigint& operator/=(bigint& a, const bigint&\
    \ b) {\n            return a = a / b;\n        }\n        friend bigint operator/(const\
    \ bigint& a, const bigint& b) {\n            return divmod(a, b).first;\n    \
    \    }\n        friend bigint& operator%=(bigint& a, const bigint& b) {\n    \
    \        return a = a % b;\n        }\n        friend bigint operator%(const bigint&\
    \ a, const bigint& b) {\n            return divmod(a, b).second;\n        }\n\n\
    #define CAST_PRIMITIVE(type)                \\\n        operator type() const\
    \ {             \\\n            type res = _dat;                \\\n         \
    \   return _neg ? -res : res;       \\\n        }                            \
    \       \\\n\n        CAST_PRIMITIVE(unsigned int)\n        CAST_PRIMITIVE(unsigned\
    \ long)\n        CAST_PRIMITIVE(unsigned long long)\n        CAST_PRIMITIVE(__uint128_t)\n\
    \        CAST_PRIMITIVE(float)\n        CAST_PRIMITIVE(double)\n        CAST_PRIMITIVE(long\
    \ double)\n#undef CAST_PRIMITIVE\n\n#define CAST_SIGNED_INT(type)            \
    \                           \\\n        operator type() const {              \
    \                       \\\n            return static_cast<std::make_unsigned_t<type>>(*this);\
    \  \\\n        }                                                           \\\n\
    \n        CAST_SIGNED_INT(int)\n        CAST_SIGNED_INT(long)\n        CAST_SIGNED_INT(long\
    \ long)\n#undef CAST_SIGNED_INT\n\n        operator __int128_t() const {\n   \
    \         return static_cast<__uint128_t>(*this);\n        }\n\n        operator\
    \ unsigned_bigint() const {\n            assert(not _neg);\n            return\
    \ _dat;\n        }\n\n        operator std::string() const {\n            if (_neg)\
    \ {\n                return '-' + std::string(_dat);\n            } else {\n \
    \               return std::string(_dat);\n            }\n        }\n\n      \
    \  friend std::istream& operator>>(std::istream& in, bigint& v) {\n          \
    \  std::string s;\n            in >> s, v = s;\n            return in;\n     \
    \   }\n        friend std::ostream& operator<<(std::ostream& out, const bigint&\
    \ v) {\n            return out << std::string(v);\n        }\n    private:\n \
    \       bigint(const unsigned_bigint& dat, bool neg) : _neg(neg), _dat(dat) {\
    \ fix_sign(); }\n        bigint(unsigned_bigint&& dat, bool neg) : _neg(neg),\
    \ _dat(std::move(dat)) { fix_sign(); }\n\n        bool _neg;\n        unsigned_bigint\
    \ _dat;\n\n        void fix_sign() {\n            if (_neg and not _dat) _neg\
    \ = false;\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_STRING_BIGINT\n#define SUISEN_STRING_BIGINT\n\n#include \"\
    library/math/unsigned_bigint.hpp\"\n\nnamespace suisen {\n    struct bigint {\n\
    \        static inline struct { operator bigint() const { return bigint{ unsigned_bigint::ZERO\
    \ }; }; } const ZERO{};\n        static inline struct { operator bigint() const\
    \ { return bigint{ unsigned_bigint::ONE }; }; } const ONE{};\n\n        bigint()\
    \ : _neg(false), _dat{} {}\n\n        template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n        bigint(T v) {\n            _neg = false;\n\
    \            if constexpr (std::is_signed_v<T>) {\n                if (v < 0)\
    \ {\n                    _neg = true;\n                    v = -v;\n         \
    \       }\n            }\n            _dat = unsigned_bigint(v);\n        }\n\
    \        bigint(const std::string& s) {\n            if (s.front() == '-') {\n\
    \                _neg = true;\n                _dat = unsigned_bigint(s.substr(1));\n\
    \                fix_sign();\n            } else {\n                _neg = false;\n\
    \                _dat = unsigned_bigint(s);\n            }\n        }\n      \
    \  bigint(const char* s) : bigint(std::string(s)) {}\n\n        bigint(const unsigned_bigint&\
    \ dat) : _neg(false), _dat(dat) {}\n        bigint(unsigned_bigint&& dat) : _neg(false),\
    \ _dat(std::move(dat)) {}\n\n        operator bool() const {\n            return\
    \ bool(_dat);\n        }\n\n        friend bool operator==(const bigint& a, const\
    \ bigint& b) {\n            if (a._neg xor b._neg) {\n                return false;\n\
    \            } else {\n                return a._dat == b._dat;\n            }\n\
    \        }\n        friend bool operator!=(const bigint& a, const bigint& b) {\n\
    \            return not (a == b);\n        }\n\n        friend bool operator<(const\
    \ bigint& a, const bigint& b) {\n            if (a._neg xor b._neg) {\n      \
    \          return a._neg;\n            } else if (a._neg) {\n                return\
    \ a._dat > b._dat;\n            } else {\n                return a._dat < b._dat;\n\
    \            }\n        }\n        friend bool operator<=(const bigint& a, const\
    \ bigint& b) {\n            return not (b < a);\n        }\n        friend bool\
    \ operator>(const bigint& a, const bigint& b) {\n            return b < a;\n \
    \       }\n        friend bool operator>=(const bigint& a, const bigint& b) {\n\
    \            return not (a < b);\n        }\n\n        friend bigint& operator<<=(bigint&\
    \ a, int shamt) {\n            a._dat <<= shamt;\n            return a;\n    \
    \    }\n        friend bigint operator<<(bigint a, int shamt) {\n            a\
    \ <<= shamt;\n            return a;\n        }\n        friend bigint& operator>>=(bigint&\
    \ a, int shamt) {\n            a._dat >>= shamt;\n            a.fix_sign();\n\
    \            return a;\n        }\n        friend bigint operator>>(bigint a,\
    \ int shamt) {\n            a >>= shamt;\n            a.fix_sign();\n        \
    \    return a;\n        }\n\n        bigint operator+() const {\n            return\
    \ *this;\n        }\n        bigint operator-() const {\n            return bigint(_dat,\
    \ not _neg);\n        }\n\n        bigint& operator++() {\n            if (_neg)\
    \ {\n                --_dat;\n                fix_sign();\n            } else\
    \ {\n                ++_dat;\n            }\n            return *this;\n     \
    \   }\n        bigint operator++(int) {\n            bigint res = *this;\n   \
    \         ++*this;\n            return res;\n        }\n        bigint& operator--()\
    \ {\n            if (_neg) {\n                ++_dat;\n            } else if (_dat)\
    \ {\n                --_dat;\n            } else {\n                _neg = true;\n\
    \                _dat = unsigned_bigint::ONE;\n            }\n            return\
    \ *this;\n        }\n        bigint operator--(int) {\n            bigint res\
    \ = *this;\n            --*this;\n            return res;\n        }\n       \
    \ friend bigint& operator+=(bigint& a, const bigint& b) {\n            if (a._neg\
    \ xor b._neg) {\n                if (a._dat >= b._dat) {\n                   \
    \ a._dat -= b._dat;\n                } else {\n                    a._dat = b._dat\
    \ - a._dat;\n                    a._neg = not a._neg;\n                }\n   \
    \             a.fix_sign();\n            } else {\n                a._dat += b._dat;\n\
    \            }\n            return a;\n        }\n        friend bigint operator+(const\
    \ bigint& a, const bigint& b) {\n            bigint c = a;\n            c += b;\n\
    \            return c;\n        }\n        friend bigint& operator-=(bigint& a,\
    \ const bigint& b) {\n            if (a._neg xor b._neg) {\n                a._dat\
    \ += b._dat;\n            } else {\n                if (a._dat >= b._dat) {\n\
    \                    a._dat -= b._dat;\n                } else {\n           \
    \         a._dat = b._dat - a._dat;\n                    a._neg = not a._neg;\n\
    \                }\n                a.fix_sign();\n            }\n           \
    \ return a;\n        }\n        friend bigint operator-(const bigint& a, const\
    \ bigint& b) {\n            bigint c = a;\n            c -= b;\n            return\
    \ c;\n        }\n        friend bigint& operator*=(bigint& a, const bigint& b)\
    \ {\n            return a = a * b;\n        }\n        friend bigint operator*(const\
    \ bigint& a, const bigint& b) {\n            return bigint(a._dat * b._dat, a._neg\
    \ xor b._neg);\n        }\n\n        static std::pair<bigint, bigint> divmod(bigint\
    \ a, bigint b) {\n            auto [q, r] = unsigned_bigint::divmod(a._dat, b._dat);\n\
    \            return { bigint(std::move(q), a._neg xor b._neg), bigint(std::move(r),\
    \ a._neg) };\n        }\n        friend bigint& operator/=(bigint& a, const bigint&\
    \ b) {\n            return a = a / b;\n        }\n        friend bigint operator/(const\
    \ bigint& a, const bigint& b) {\n            return divmod(a, b).first;\n    \
    \    }\n        friend bigint& operator%=(bigint& a, const bigint& b) {\n    \
    \        return a = a % b;\n        }\n        friend bigint operator%(const bigint&\
    \ a, const bigint& b) {\n            return divmod(a, b).second;\n        }\n\n\
    #define CAST_PRIMITIVE(type)                \\\n        operator type() const\
    \ {             \\\n            type res = _dat;                \\\n         \
    \   return _neg ? -res : res;       \\\n        }                            \
    \       \\\n\n        CAST_PRIMITIVE(unsigned int)\n        CAST_PRIMITIVE(unsigned\
    \ long)\n        CAST_PRIMITIVE(unsigned long long)\n        CAST_PRIMITIVE(__uint128_t)\n\
    \        CAST_PRIMITIVE(float)\n        CAST_PRIMITIVE(double)\n        CAST_PRIMITIVE(long\
    \ double)\n#undef CAST_PRIMITIVE\n\n#define CAST_SIGNED_INT(type)            \
    \                           \\\n        operator type() const {              \
    \                       \\\n            return static_cast<std::make_unsigned_t<type>>(*this);\
    \  \\\n        }                                                           \\\n\
    \n        CAST_SIGNED_INT(int)\n        CAST_SIGNED_INT(long)\n        CAST_SIGNED_INT(long\
    \ long)\n#undef CAST_SIGNED_INT\n\n        operator __int128_t() const {\n   \
    \         return static_cast<__uint128_t>(*this);\n        }\n\n        operator\
    \ unsigned_bigint() const {\n            assert(not _neg);\n            return\
    \ _dat;\n        }\n\n        operator std::string() const {\n            if (_neg)\
    \ {\n                return '-' + std::string(_dat);\n            } else {\n \
    \               return std::string(_dat);\n            }\n        }\n\n      \
    \  friend std::istream& operator>>(std::istream& in, bigint& v) {\n          \
    \  std::string s;\n            in >> s, v = s;\n            return in;\n     \
    \   }\n        friend std::ostream& operator<<(std::ostream& out, const bigint&\
    \ v) {\n            return out << std::string(v);\n        }\n    private:\n \
    \       bigint(const unsigned_bigint& dat, bool neg) : _neg(neg), _dat(dat) {\
    \ fix_sign(); }\n        bigint(unsigned_bigint&& dat, bool neg) : _neg(neg),\
    \ _dat(std::move(dat)) { fix_sign(); }\n\n        bool _neg;\n        unsigned_bigint\
    \ _dat;\n\n        void fix_sign() {\n            if (_neg and not _dat) _neg\
    \ = false;\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_STRING_BIGINT\n"
  dependsOn:
  - library/math/unsigned_bigint.hpp
  - library/convolution/arbitrary_mod_convolution.hpp
  - library/convolution/convolution_naive.hpp
  isVerificationFile: false
  path: library/math/bigint.hpp
  requiredBy: []
  timestamp: '2024-01-30 21:01:49+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/math/bigint/multiplication_of_big_integers.test.cpp
  - test/src/math/bigint/NTL_2_D.test.cpp
  - test/src/math/bigint/NTL_2_B.test.cpp
  - test/src/math/bigint/addition_of_big_integers.test.cpp
  - test/src/math/bigint/NTL_2_F.test.cpp
  - test/src/math/bigint/NTL_2_A.test.cpp
  - test/src/math/bigint/many_aplusb_128bit.test.cpp
  - test/src/math/bigint/NTL_2_E.test.cpp
documentation_of: library/math/bigint.hpp
layout: document
title: "\u591A\u500D\u9577\u6574\u6570"
---
## 多倍長整数

