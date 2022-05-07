---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/math/circulant_matrix.hpp
    title: Circulant Matrix
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: Factorial
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"test/src/math/circulant_matrix/arc139_e.test.cpp\"\n#include\
    \ <iostream>\n#include <vector>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\
    \nusing mint = atcoder::modint998244353;\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, typename U = T>\n    struct factorial {\n\
    \        factorial() {}\n        factorial(int n) { ensure(n); }\n\n        static\
    \ void ensure(const int n) {\n            int sz = _fac.size();\n            if\
    \ (n + 1 <= sz) return;\n            int new_size = std::max(n + 1, sz * 2);\n\
    \            _fac.resize(new_size), _fac_inv.resize(new_size);\n            for\
    \ (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size\
    \ - 1] = U(1) / _fac[new_size - 1];\n            for (int i = new_size - 1; i\
    \ > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n        }\n\n        const T&\
    \ fac(const int i) {\n            ensure(i);\n            return _fac[i];\n  \
    \      }\n        const T& operator()(int i) {\n            return fac(i);\n \
    \       }\n        const U& fac_inv(const int i) {\n            ensure(i);\n \
    \           return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 1 \"library/math/circulant_matrix.hpp\"\n\n\n\n#line 7 \"\
    library/math/circulant_matrix.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T>\n    struct CirculantMatrix {\n        using value_type = T;\n        using\
    \ convolution_t = std::vector<value_type>(*)(const std::vector<value_type>&, const\
    \ std::vector<value_type>&);\n\n        // empty matrix\n        CirculantMatrix()\
    \ : CirculantMatrix(std::vector<value_type>{}) {}\n\n        /**\n         * +-\
    \                        -+\n         * | a[0] a[4] a[3] a[2] a[1] |\n       \
    \  * | a[1] a[0] a[4] a[3] a[2] |\n         * | a[2] a[1] a[0] a[4] a[3] |\n \
    \        * | a[3] a[2] a[1] a[0] a[4] |\n         * | a[4] a[3] a[2] a[1] a[0]\
    \ |\n         * +-                        -+\n         */\n        explicit CirculantMatrix(const\
    \ std::vector<value_type>& a) : _dat(a) {}\n\n        static void set_multiplication(convolution_t\
    \ multiplication) {\n            convolve = multiplication;\n        }\n\n   \
    \     static CirculantMatrix<value_type> e0(int n, const value_type& zero = value_type{\
    \ 0 }) {\n            return CirculantMatrix<value_type>{ std::vector<value_type>(n,\
    \ zero) };\n        }\n        static CirculantMatrix<value_type> e1(int n, const\
    \ value_type& zero = value_type{ 0 }, const value_type& one = value_type{ 1 })\
    \ {\n            auto dat = std::vector<value_type>(n, zero);\n            dat[0]\
    \ = one;\n            return CirculantMatrix<value_type>{ dat };\n        }\n\n\
    \        int size() const {\n            return _dat.size();\n        }\n\n  \
    \      value_type get(int i, int j) const {\n            const int n = size();\n\
    \            int k = i - j;\n            if (k < 0) k += n;\n            return\
    \ _dat[k];\n        }\n        value_type operator[](const std::pair<int, int>\
    \ &p) const {\n            return get(p.first, p.second);\n        }\n\n     \
    \   friend CirculantMatrix<value_type> operator+(const CirculantMatrix<value_type>&\
    \ mat) {\n            return mat;\n        }\n        friend CirculantMatrix<value_type>\
    \ operator-(const CirculantMatrix<value_type>& mat) {\n            const int n\
    \ = mat.size();\n            std::vector<value_type> res(n);\n            for\
    \ (int i = 0; i < n; ++i) res[i] = -mat._dat[i];\n            return CirculantMatrix<value_type>\
    \ { std::move(res) };\n        }\n        friend CirculantMatrix<value_type> operator+(const\
    \ CirculantMatrix<value_type>& lhs, const CirculantMatrix<value_type>& rhs) {\n\
    \            const int n = lhs.size();\n            assert(n == int(rhs.size()));\n\
    \            std::vector<value_type> res(n);\n            for (int i = 0; i <\
    \ n; ++i) res[i] = lhs._dat[i] + rhs._dat[i];\n            return CirculantMatrix<value_type>\
    \ { std::move(res) };\n        }\n        friend CirculantMatrix<value_type> operator-(const\
    \ CirculantMatrix<value_type>& lhs, const CirculantMatrix<value_type>& rhs) {\n\
    \            const int n = lhs.size();\n            assert(n == int(rhs.size()));\n\
    \            std::vector<value_type> res(n);\n            for (int i = 0; i <\
    \ n; ++i) res[i] = lhs._dat[i] - rhs._dat[i];\n            return CirculantMatrix<value_type>\
    \ { std::move(res) };\n        }\n        friend CirculantMatrix<value_type> operator*(const\
    \ CirculantMatrix<value_type>& lhs, const CirculantMatrix<value_type>& rhs) {\n\
    \            const int n = lhs.size();\n            assert(n == int(rhs.size()));\n\
    \            std::vector<value_type> res = convolve(lhs._dat, rhs._dat);\n   \
    \         for (int i = n; i < int(res.size()); ++i) res[i - n] += res[i];\n  \
    \          res.resize(n);\n            return CirculantMatrix<value_type> { std::move(res)\
    \ };\n        }\n        friend std::vector<value_type> operator*(const CirculantMatrix<value_type>&\
    \ mat, const std::vector<value_type>& x) {\n            return std::move((mat\
    \ * CirculantMatrix<value_type> { x })._dat);\n        }\n        friend CirculantMatrix<value_type>\
    \ operator*(const CirculantMatrix<value_type>& mat, const value_type& coef) {\n\
    \            const int n = mat.size();\n            std::vector<value_type> res(n);\n\
    \            for (int i = 0; i < n; ++i) res[i] = coef * mat._dat[i];\n      \
    \      return CirculantMatrix<value_type> { res };\n        }\n        friend\
    \ CirculantMatrix<value_type> operator*(const value_type& coef, const CirculantMatrix<value_type>&\
    \ mat) {\n            return mat * coef;\n        }\n\n        CirculantMatrix<value_type>&\
    \ operator+=(const CirculantMatrix<value_type>& rhs) {\n            return *this\
    \ = *this + rhs;\n        }\n        CirculantMatrix<value_type>& operator-=(const\
    \ CirculantMatrix<value_type>& rhs) {\n            return *this = *this - rhs;\n\
    \        }\n        CirculantMatrix<value_type>& operator*=(const CirculantMatrix<value_type>&\
    \ rhs) {\n            return *this = *this * rhs;\n        }\n        CirculantMatrix<value_type>&\
    \ operator*=(const value_type& coef) {\n            return *this = *this * coef;\n\
    \        }\n\n        CirculantMatrix<value_type> pow(long long b) {\n       \
    \     auto res = CirculantMatrix<value_type>::e1(size());\n            for (auto\
    \ p = *this; b; b >>= 1) {\n                if (b & 1) res *= p;\n           \
    \     p *= p;\n            }\n            return res;\n        }\n\n    private:\n\
    \        static inline convolution_t convolve{\n            [](const auto&, const\
    \ auto&) {\n                std::cerr << \"convolution function is not available.\"\
    \ << std::endl;\n                assert(false);\n                return std::vector<value_type>{};\n\
    \            }\n        };\n\n        std::vector<value_type> _dat;\n    };\n\
    } // namespace suisen\n\n\n#line 11 \"test/src/math/circulant_matrix/arc139_e.test.cpp\"\
    \n\nusing suisen::factorial;\nusing suisen::CirculantMatrix;\n\nvoid solve(long\
    \ long n, long long m) {\n    if (n % 2 == 0 and m % 2 == 0) {\n        std::cout\
    \ << 2 << std::endl;\n    } else if (n % 2 == 0) {\n        factorial<mint> fac(n\
    \ + 1);\n        mint ans = 0;\n        for (int k = 0; k <= n; ++k) if ((n -\
    \ 2 * k) % m == 0) ans += fac.binom(n, k);\n        std::cout << (ans * m).val()\
    \ << std::endl;\n    } else {\n        CirculantMatrix<mint>::set_multiplication([](const\
    \ std::vector<mint>& a, const std::vector<mint>& b) { return atcoder::convolution(a,\
    \ b); });\n        if (m % 2 == 1 and n > m) std::swap(n, m);\n        std::vector<mint>\
    \ dat(n);\n        dat[1] = dat[n - 1] = 1;\n        std::vector<mint> x(n);\n\
    \        x[0] = 1;\n        std::cout << ((CirculantMatrix<mint>{dat}.pow(m) *\
    \ x)[0] * n).val() << std::endl;\n    }\n}\n\nint main() {\n    long long n, m;\n\
    \    std::cin >> n >> m;\n    solve(n, m);\n    return 0;\n}\n"
  code: "#include <iostream>\n#include <vector>\n\n#include <atcoder/modint>\n#include\
    \ <atcoder/convolution>\n\nusing mint = atcoder::modint998244353;\n\n#include\
    \ \"library/math/factorial.hpp\"\n#include \"library/math/circulant_matrix.hpp\"\
    \n\nusing suisen::factorial;\nusing suisen::CirculantMatrix;\n\nvoid solve(long\
    \ long n, long long m) {\n    if (n % 2 == 0 and m % 2 == 0) {\n        std::cout\
    \ << 2 << std::endl;\n    } else if (n % 2 == 0) {\n        factorial<mint> fac(n\
    \ + 1);\n        mint ans = 0;\n        for (int k = 0; k <= n; ++k) if ((n -\
    \ 2 * k) % m == 0) ans += fac.binom(n, k);\n        std::cout << (ans * m).val()\
    \ << std::endl;\n    } else {\n        CirculantMatrix<mint>::set_multiplication([](const\
    \ std::vector<mint>& a, const std::vector<mint>& b) { return atcoder::convolution(a,\
    \ b); });\n        if (m % 2 == 1 and n > m) std::swap(n, m);\n        std::vector<mint>\
    \ dat(n);\n        dat[1] = dat[n - 1] = 1;\n        std::vector<mint> x(n);\n\
    \        x[0] = 1;\n        std::cout << ((CirculantMatrix<mint>{dat}.pow(m) *\
    \ x)[0] * n).val() << std::endl;\n    }\n}\n\nint main() {\n    long long n, m;\n\
    \    std::cin >> n >> m;\n    solve(n, m);\n    return 0;\n}"
  dependsOn:
  - library/math/factorial.hpp
  - library/math/circulant_matrix.hpp
  isVerificationFile: true
  path: test/src/math/circulant_matrix/arc139_e.test.cpp
  requiredBy: []
  timestamp: '2022-05-07 15:41:34+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/math/circulant_matrix/arc139_e.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/circulant_matrix/arc139_e.test.cpp
- /verify/test/src/math/circulant_matrix/arc139_e.test.cpp.html
title: test/src/math/circulant_matrix/arc139_e.test.cpp
---
