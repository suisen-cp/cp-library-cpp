---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/math/circulant_matrix/arc139_e.test.cpp
    title: test/src/math/circulant_matrix/arc139_e.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/circulant_matrix.hpp\"\n\n\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
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
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_CIRCULANT_MATRIX\n#define SUISEN_CIRCULANT_MATRIX\n\n#include\
    \ <cassert>\n#include <iostream>\n#include <vector>\n\nnamespace suisen {\n  \
    \  template <typename T>\n    struct CirculantMatrix {\n        using value_type\
    \ = T;\n        using convolution_t = std::vector<value_type>(*)(const std::vector<value_type>&,\
    \ const std::vector<value_type>&);\n\n        // empty matrix\n        CirculantMatrix()\
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
    } // namespace suisen\n\n#endif // SUISEN_CIRCULANT_MATRIX\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/circulant_matrix.hpp
  requiredBy: []
  timestamp: '2022-04-30 04:34:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/math/circulant_matrix/arc139_e.test.cpp
documentation_of: library/math/circulant_matrix.hpp
layout: document
title: "Circulant Matrix (\u5DE1\u56DE\u884C\u5217)"
---
## Circulant Matrix (巡回行列)

積を高速に計算できる行列の一種。

列 $a = ( a _ 0 , \ldots , a _ { n - 1 } )$ に対して、$n\times n$ 行列 $\mathrm{Cir}(a _ 0, \ldots, a _ {n - 1})$ を以下で定義すると、これは巡回行列である。

$$
\mathrm{Cir}(a _ 0, \ldots, a _ {n - 1}) \coloneqq (a _ {i - j \bmod n}) _ {0\leq i,j\lt n} =\begin{pmatrix}
a _ 0 & a _ {n - 1} & a _ {n - 3} & \cdots & a _ 1\\
a _ 1 & a _ 0 & a _ {n - 2} & \cdots & a _ 2\\
a _ 2 & a _ 1 & a _ 0 & \cdots & a _ 3\\
\vdots & \vdots & \vdots & \ddots & \vdots \\
a _ {n - 1} & a _ {n - 2} & a _ {n - 3} & \cdots & a _ 0
\end{pmatrix}
$$

$2$ つの巡回行列 $A\coloneqq\mathrm{Cir}(a _ 0, \ldots, a _ {n - 1}),\; B \coloneqq \mathrm{Cir}(b _ 0, \ldots, b _ {n - 1})$ に対して $C\coloneqq AB$ とすれば、次が成り立つ。

$$
C _ {i,j} = \sum _ {k = 0} ^ {n - 1} a _ {i - k \bmod n} b _ {k - j \bmod n} = \sum _ {k+l\equiv i-j\pmod{n}} a _ k b _ l
$$

右辺は $i-j\bmod n$ の値にのみ依存するから、$\displaystyle c _ i \coloneqq \sum _ {k+l\equiv i\pmod{n}} a _ k b _ l$ に対して $C=\mathrm{Cir}(c _ 0, \ldots, c _ {n - 1})$ である。これは、巡回行列の積はまた巡回行列となることを表している。更に、$c$ は $a,b$ の巡回畳み込みであるから、FFT などを用いることで $C$ は $\Theta(n\log n)$ 時間で計算可能である。
