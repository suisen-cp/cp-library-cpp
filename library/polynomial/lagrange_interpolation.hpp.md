---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/product_of_differences.hpp
    title: Product Of Differences
  - icon: ':heavy_check_mark:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/sum_i^d_r^i.hpp
    title: $\displaystyle \sum _ i i ^ d r ^ i$
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/lagrange_interpolation.hpp\"\n\n\n\n\
    #line 1 \"library/math/product_of_differences.hpp\"\n\n\n\n#include <deque>\n\
    #line 1 \"library/polynomial/multi_point_eval.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename FPSType, typename T>\n    std::vector<typename\
    \ FPSType::value_type> multi_point_eval(const FPSType& f, const std::vector<T>&\
    \ xs) {\n        int n = xs.size();\n        if (n == 0) return {};\n        std::vector<FPSType>\
    \ seg(2 * n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i],\
    \ 1 };\n        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i *\
    \ 2 + 1];\n        seg[1] = f % seg[1];\n        for (int i = 2; i < 2 * n; ++i)\
    \ seg[i] = seg[i / 2] % seg[i];\n        std::vector<typename FPSType::value_type>\
    \ ys(n);\n        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];\n       \
    \ return ys;\n    }\n} // namespace suisen\n\n\n#line 6 \"library/math/product_of_differences.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * O(N(logN)^2)\n     * return the vector\
    \ p of length xs.size() s.t. p[i]=\u03A0[j!=i](x[i]-x[j])\n     */\n    template\
    \ <typename FPSType, typename T>\n    std::vector<typename FPSType::value_type>\
    \ product_of_differences(const std::vector<T>& xs) {\n        // f(x):=\u03A0\
    _i(x-x[i])\n        // => f'(x)=\u03A3_i \u03A0[j!=i](x-x[j])\n        // => f'(x[i])=\u03A0\
    [j!=i](x[i]-x[j])\n        const int n = xs.size();\n        std::deque<FPSType>\
    \ dq;\n        for (int i = 0; i < n; ++i) dq.push_back(FPSType{ -xs[i], 1 });\n\
    \        while (dq.size() >= 2) {\n            auto f = std::move(dq.front());\n\
    \            dq.pop_front();\n            auto g = std::move(dq.front());\n  \
    \          dq.pop_front();\n            dq.push_back(f * g);\n        }\n    \
    \    auto f = std::move(dq.front());\n        f.diff_inplace();\n        return\
    \ multi_point_eval<FPSType, T>(f, xs);\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 5 \"library/polynomial/lagrange_interpolation.hpp\"\n\nnamespace suisen {\n\
    \    // O(N^2+NlogP)\n    template <typename T>\n    T lagrange_interpolation_naive(const\
    \ std::vector<T>& xs, const std::vector<T>& ys, const T t) {\n        const int\
    \ n = xs.size();\n        assert(int(ys.size()) == n);\n\n        T p{ 1 };\n\
    \        for (int i = 0; i < n; ++i) p *= t - xs[i];\n\n        T res{ 0 };\n\
    \        for (int i = 0; i < n; ++i) {\n            T w = 1;\n            for\
    \ (int j = 0; j < n; ++j) if (j != i) w *= xs[i] - xs[j];\n            res +=\
    \ ys[i] * (t == xs[i] ? 1 : p / (w * (t - xs[i])));\n        }\n        return\
    \ res;\n    }\n\n    // O(N(logN)^2+NlogP)\n    template <typename FPSType, typename\
    \ T>\n    typename FPSType::value_type lagrange_interpolation(const std::vector<T>&\
    \ xs, const std::vector<T>& ys, const T t) {\n        const int n = xs.size();\n\
    \        assert(int(ys.size()) == n);\n\n        std::vector<FPSType> seg(2 *\
    \ n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPSType {-xs[i], 1};\n\
    \        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n\
    \        seg[1] = seg[1].diff() % seg[1];\n        for (int i = 2; i < 2 * n;\
    \ ++i) seg[i] = seg[i / 2] % seg[i];\n\n        using mint = typename FPSType::value_type;\n\
    \        mint p{ 1 };\n        for (int i = 0; i < n; ++i) p *= t - xs[i];\n\n\
    \        mint res{ 0 };\n        for (int i = 0; i < n; ++i) {\n            mint\
    \ w = seg[n + i][0];\n            res += ys[i] * (t == xs[i] ? 1 : p / (w * (t\
    \ - xs[i])));\n        }\n        return res;\n    }\n\n    // xs[i] = ai + b\n\
    \    // requirement: for all 0\u2264i<j<n, ai+b \u2262 aj+b mod p\n    template\
    \ <typename T>\n    T lagrange_interpolation_arithmetic_progression(T a, T b,\
    \ const std::vector<T>& ys, const T t) {\n        const int n = ys.size();\n \
    \       T fac = 1;\n        for (int i = 1; i < n; ++i) fac *= i;\n        std::vector<T>\
    \ fac_inv(n), suf(n);\n        fac_inv[n - 1] = T(1) / fac;\n        suf[n - 1]\
    \ = 1;\n        for (int i = n - 1; i > 0; --i) {\n            fac_inv[i - 1]\
    \ = fac_inv[i] * i;\n            suf[i - 1] = suf[i] * (t - (a * i + b));\n  \
    \      }\n        T pre = 1, res = 0;\n        for (int i = 0; i < n; ++i) {\n\
    \            T val = ys[i] * pre * suf[i] * fac_inv[i] * fac_inv[n - i - 1];\n\
    \            if ((n - 1 - i) & 1) res -= val;\n            else              \
    \   res += val;\n            pre *= t - (a * i + b);\n        }\n        return\
    \ res / a.pow(n - 1);\n    }\n    // x = 0, 1, ...\n    template <typename T>\n\
    \    T lagrange_interpolation_arithmetic_progression(const std::vector<T>& ys,\
    \ const T t) {\n        return lagrange_interpolation_arithmetic_progression(T{1},\
    \ T{0}, ys, t);\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_INTERPOLATION\n#define SUISEN_INTERPOLATION\n\n#include \"\
    library/math/product_of_differences.hpp\"\n\nnamespace suisen {\n    // O(N^2+NlogP)\n\
    \    template <typename T>\n    T lagrange_interpolation_naive(const std::vector<T>&\
    \ xs, const std::vector<T>& ys, const T t) {\n        const int n = xs.size();\n\
    \        assert(int(ys.size()) == n);\n\n        T p{ 1 };\n        for (int i\
    \ = 0; i < n; ++i) p *= t - xs[i];\n\n        T res{ 0 };\n        for (int i\
    \ = 0; i < n; ++i) {\n            T w = 1;\n            for (int j = 0; j < n;\
    \ ++j) if (j != i) w *= xs[i] - xs[j];\n            res += ys[i] * (t == xs[i]\
    \ ? 1 : p / (w * (t - xs[i])));\n        }\n        return res;\n    }\n\n   \
    \ // O(N(logN)^2+NlogP)\n    template <typename FPSType, typename T>\n    typename\
    \ FPSType::value_type lagrange_interpolation(const std::vector<T>& xs, const std::vector<T>&\
    \ ys, const T t) {\n        const int n = xs.size();\n        assert(int(ys.size())\
    \ == n);\n\n        std::vector<FPSType> seg(2 * n);\n        for (int i = 0;\
    \ i < n; ++i) seg[n + i] = FPSType {-xs[i], 1};\n        for (int i = n - 1; i\
    \ > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n        seg[1] = seg[1].diff()\
    \ % seg[1];\n        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];\n\
    \n        using mint = typename FPSType::value_type;\n        mint p{ 1 };\n \
    \       for (int i = 0; i < n; ++i) p *= t - xs[i];\n\n        mint res{ 0 };\n\
    \        for (int i = 0; i < n; ++i) {\n            mint w = seg[n + i][0];\n\
    \            res += ys[i] * (t == xs[i] ? 1 : p / (w * (t - xs[i])));\n      \
    \  }\n        return res;\n    }\n\n    // xs[i] = ai + b\n    // requirement:\
    \ for all 0\u2264i<j<n, ai+b \u2262 aj+b mod p\n    template <typename T>\n  \
    \  T lagrange_interpolation_arithmetic_progression(T a, T b, const std::vector<T>&\
    \ ys, const T t) {\n        const int n = ys.size();\n        T fac = 1;\n   \
    \     for (int i = 1; i < n; ++i) fac *= i;\n        std::vector<T> fac_inv(n),\
    \ suf(n);\n        fac_inv[n - 1] = T(1) / fac;\n        suf[n - 1] = 1;\n   \
    \     for (int i = n - 1; i > 0; --i) {\n            fac_inv[i - 1] = fac_inv[i]\
    \ * i;\n            suf[i - 1] = suf[i] * (t - (a * i + b));\n        }\n    \
    \    T pre = 1, res = 0;\n        for (int i = 0; i < n; ++i) {\n            T\
    \ val = ys[i] * pre * suf[i] * fac_inv[i] * fac_inv[n - i - 1];\n            if\
    \ ((n - 1 - i) & 1) res -= val;\n            else                 res += val;\n\
    \            pre *= t - (a * i + b);\n        }\n        return res / a.pow(n\
    \ - 1);\n    }\n    // x = 0, 1, ...\n    template <typename T>\n    T lagrange_interpolation_arithmetic_progression(const\
    \ std::vector<T>& ys, const T t) {\n        return lagrange_interpolation_arithmetic_progression(T{1},\
    \ T{0}, ys, t);\n    }\n} // namespace suisen\n\n#endif // SUISEN_INTERPOLATION\n\
    \n"
  dependsOn:
  - library/math/product_of_differences.hpp
  - library/polynomial/multi_point_eval.hpp
  isVerificationFile: false
  path: library/polynomial/lagrange_interpolation.hpp
  requiredBy:
  - library/math/sum_i^d_r^i.hpp
  timestamp: '2023-02-16 15:43:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
  - test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
documentation_of: library/polynomial/lagrange_interpolation.hpp
layout: document
title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
---
## ラグランジュ補間

$\mathbb{F} _ p$ 上の高々 $N - 1$ 次の多項式 $f(x)$ について、次の情報が分かっている。

$$
f(x _ i) = y _ i\ (i = 0, \ldots, N - 1).
$$

$x _ i$ が全て互いに相異なるとき、$f$ は存在して一意であり、次のような表示を持つ。

$$
f(x) = \sum _ {i = 0} ^ {N - 1} y _ i \dfrac{\prod _ {j \neq i} (x - x _ j)}{\prod _ {j \neq i} (x _ i - x _ j)}.
$$

この $f$ を __補間多項式__ と呼ぶ。

$x _ i$ および $y _ i$ に対して定まる補間多項式 $f$ に対して、ある与えられた $t$ に関する $f(t)$ を計算する。

## アルゴリズム (一般の場合)

多項式 $l$ を以下で定義する。

$$l(x) = \prod _ {i = 0} ^ {N - 1} (x - x _ i)$$

このとき、$\displaystyle l'(x _ i) = \prod _ {j \neq i} (x _ i - x _ j)$ が成り立つ。

$l$ はマージテクおよび高速フーリエ変換による畳み込みなどを用いて $\Theta(N (\log N) ^ 2)$ 時間で計算でき、$l$ に対して $l'$ は $\Theta(N)$ 時間で計算できる。

各 $x _ 0, \ldots, x _ {N - 1}$ に対する $l'(x _ i)$ を求めるのは Multipoint Evaluation なので $\Theta(N (\log N) ^ 2)$ 時間で計算できる。

$l'$ を用いれば、求めたい値は次のように書ける。

$$
f(t) = \sum _ {i = 0} ^ {N - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {j \neq i} (t - x _ j).
$$

$i = 0, \ldots, N - 1$ に対して、次を満たす補助的な配列 $\mathrm{pre}, \mathrm{suf}$ を前計算しておく。

$$\begin{aligned}
\mathrm{pre}(i) &= \prod _ {j = 0} ^ {i - 1} (t - x _ j),\\
\mathrm{suf}(i) &= \prod _ {j = i + 1} ^ {N - 1} (t - x _ j).
\end{aligned}$$

このとき、$\displaystyle \prod _ {j \neq i} (t - x _ j) = \left(\prod _ {j = 0} ^ {i - 1} (t - x _ j)\right)\cdot \left(\prod _ {j = i + 1} ^ {N - 1} (t - x _ j)\right) = \mathrm{pre}(i) \cdot \mathrm{suf}(i)$ として計算できる。

従って、全体 $\Theta(N (\log N) ^ 2)$ 時間で $f(t)$ を計算出来る。

## アルゴリズム ($x _ i$ が等差数列を成す場合)

ある $a, b$ に対して $x _ i = a i + b$ が成り立つと仮定すると、求めたい値は次のように書くことが出来る。ここで、$a = 0$ のときは $x _ i$ が全て互いに相異なるという制約から $N = 1$ となり $0 ^ 0$ が現れるが、ここでは $0 ^ 0 = 1$ と定める。

$$
f(t) = \dfrac{1}{a ^ {N - 1}}\sum _ {i = 0} ^ {N - 1} y _ i \dfrac{\prod _ {j \neq i} (t - x _ j)}{\prod _ {j \neq i} (i - j)}.
$$

各 $\prod _ {j \neq i} (t - x _ j)$ については、一般の場合と同様にして $\Theta(N)$ 時間で計算できる。

$\prod _ {j \neq i} (i - j)$ に関しては、次のように計算できる。

$$\begin{aligned}
\prod _ {j \neq i} (i - j)
&= \left(\prod _ {j = 0} ^ {i - 1} (i - j)\right) \cdot \left(\prod _ {j = i + 1} ^ {N - 1} (i - j)\right)\\
&= (i\times (i - 1) \times \cdots \times 1) \cdot ((-1) \times (-2) \times \cdots \times (-(N - i - 1)))\\
&= (-1) ^ {N - i - 1} \times i! \times (N - i - 1)!.
\end{aligned}$$

従って、$0!, \ldots, (N - 1)!$ の乗法逆元を前計算しておけば、各 $i$ に対する $y _ i \dfrac{\prod _ {j \neq i} (t - x _ j)}{\prod _ {j \neq i} (i - j)}$ は $O(1)$ 時間で計算することが出来ます。

$0!, \ldots, (N - 1)!$ の乗法逆元の計算は $\Theta(N + \log p)$ で、$\dfrac{1}{a ^ {N - 1}}$ の計算は $\Theta(\log N)$ で計算できるので、全体 $\Theta(N + \log p)$ 時間で $f(t)$ を計算できる。
