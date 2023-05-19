---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/number/ext_gcd.hpp
    title: Ext Gcd
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':x:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - icon: ':x:'
    path: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime
      each other.
    links: []
  bundledCode: "#line 1 \"library/number/garner.hpp\"\n\n\n\n#include <vector>\n#line\
    \ 1 \"library/number/ext_gcd.hpp\"\n\n\n\n#include <cassert>\n#include <cmath>\n\
    #include <limits>\n#include <optional>\n#include <tuple>\n#include <utility>\n\
    \nnamespace suisen {\n    constexpr long long safe_mod(long long x, long long\
    \ m) {\n        x %= m;\n        return x < 0 ? x + m : x;\n    }\n\n    // returns\
    \ {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \n    std::tuple<long long, long long, long\
    \ long> ext_gcd(long long a, long long b) {\n        long long x = 1, y = 0;\n\
    \        long long z = 0, w = 1;\n        while (b) {\n            long long p\
    \ = a / b, q = a % b;\n            x -= y * p, std::swap(x, y);\n            z\
    \ -= w * p, std::swap(z, w);\n            a = b, b = q;\n        }\n        if\
    \ (a < 0) {\n            x = -x, z = -z, a = -a;\n        }\n        return {\
    \ x, z, a };\n    }\n\n    // returns {x,g} s.t. a*x=g (mod m)\n    std::pair<long\
    \ long, long long> gcd_inv(long long a, long long m) {\n        auto [x, y, g]\
    \ = ext_gcd(a, m);\n        return { safe_mod(x, m), g };\n    }\n\n    // returns\
    \ x s.t. a*x=1 (mod m) if exists, otherwise throws runtime error.\n    long long\
    \ inv_mod(long long a, long long mod) {\n        auto [inv, y, g] = ext_gcd(a,\
    \ mod);\n        assert(g == 1);\n        return safe_mod(inv, mod);\n    }\n\n\
    \    class Solution {\n        enum class SolutionType {\n            None, Arbitrary,\
    \ Linear\n        };\n\n        friend struct Equation;\n\n        static constexpr\
    \ long long neginf = std::numeric_limits<long long>::min() / 2;\n        static\
    \ constexpr long long posinf = std::numeric_limits<long long>::max() / 2;\n\n\
    \        SolutionType t;\n        // if t == Linear:\n        //      x = x0 +\
    \ k * cx,\n        //      y = y0 + k * cy         (kxmin <= k <= kxmax and kymin\
    \ <= k <= kymax)\n        // if t == Arbitrary:\n        //      x = x0 + k *\
    \ cx = k,    (kxmin <= k <= kxmax)\n        //      y = y0 + l * cy = l     (kymin\
    \ <= l <= kymax)\n        // if t == None:\n        //      No solution\n    \
    \    long long x0, cx, y0, cy;\n        long long kxmin = neginf, kxmax = posinf;\n\
    \        long long kymin = neginf, kymax = posinf;\n\n        Solution(SolutionType\
    \ t, long long x0 = 0, long long cx = 0, long long y0 = 0, long long cy = 0) :\
    \ t(t), x0(x0), cx(cx), y0(y0), cy(cy) {}\n\n        long long get_x(long long\
    \ k) const {\n            return x0 + k * cx;\n        }\n        long long get_y(long\
    \ long k) const {\n            return y0 + k * cy;\n        }\n        std::pair<long\
    \ long, long long> get_pair(long long k) const {\n            return { get_x(k),\
    \ get_y(k) };\n        }\n\n        std::optional<std::pair<long long, long long>>\
    \ get_k_range() const {\n            long long kmin = std::max(kxmin, kymin);\n\
    \            long long kmax = std::min(kxmax, kymax);\n            if (kmin <=\
    \ kmax) {\n                return std::pair{ kmin, kmax };\n            } else\
    \ {\n                return std::nullopt;\n            }\n        }\n\n      \
    \  template <typename T>\n        static constexpr T fld(T x, T y) {\n       \
    \     return x / y - ((x ^ y) < 0 and x % y);\n        }\n        template <typename\
    \ T>\n        static constexpr T cld(T x, T y) {\n            return x / y + ((x\
    \ ^ y) >= 0 and x % y);\n        }\n    public:\n        static Solution make_none()\
    \ {\n            return Solution(SolutionType::None);\n        }\n        static\
    \ Solution make_arbitrary() {\n            return Solution(SolutionType::Arbitrary,\
    \ 0, 1, 0, 1);\n        }\n        static Solution make_linear(long long x0, long\
    \ long cx, long long y0, long long cy) {\n            return Solution(SolutionType::Linear,\
    \ x0, cx, y0, cy);\n        }\n\n        bool has_solution() const {\n       \
    \     if (t == SolutionType::None) {\n                return false;\n        \
    \    } else if (t == SolutionType::Arbitrary) {\n                return true;\n\
    \            } else {\n                return get_k_range().has_value();\n   \
    \         }\n        }\n        template <typename T = long long>\n        T count()\
    \ const {\n            if (t == SolutionType::None) {\n                return\
    \ 0;\n            } else if (t == SolutionType::Arbitrary) {\n               \
    \ return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);\n            } else {\n\
    \                auto k_range = get_k_range();\n                if (k_range) {\n\
    \                    return k_range->second - k_range->first + 1;\n          \
    \      } else {\n                    return 0;\n                }\n          \
    \  }\n        }\n\n        // restrict to x <= upper.\n        bool set_upper_x(long\
    \ long upper) {\n            if (t == SolutionType::None) return false;\n    \
    \        // x0 + k * cx <= upper\n            if (cx == 0) {\n               \
    \ if (x0 > upper) t = SolutionType::None;\n            } else {\n            \
    \    if (cx > 0) { // k <= (upper - x0) / cx\n                    kxmin = std::min(kxmin,\
    \ fld(upper - x0, cx));\n                } else { // k >= (upper - x0) / cx\n\
    \                    kxmax = std::max(kxmax, cld(upper - x0, cx));\n         \
    \       }\n                if (kxmin > kxmax) t = SolutionType::None;\n      \
    \      }\n            return t != SolutionType::None;\n        }\n        // restrict\
    \ to x >= lower.\n        bool set_lower_x(long long lower) {\n            if\
    \ (t == SolutionType::None) return false;\n            // x0 + k * cx >= lower\n\
    \            if (cx == 0) {\n                if (x0 < lower) t = SolutionType::None;\n\
    \            } else {\n                if (cx > 0) { // k >= (lower - x0) / cx\n\
    \                    kxmin = std::max(kxmin, cld(lower - x0, cx));\n         \
    \       } else { // k <= (lower - x0) / cx\n                    kxmax = std::min(kxmax,\
    \ fld(lower - x0, cx));\n                }\n                if (kxmin > kxmax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n        bool set_lower_y(long long lower) {\n            if (t ==\
    \ SolutionType::None) return false;\n            // y0 + k * cy >= lower\n   \
    \         if (cy == 0) {\n                if (y0 < lower) t = SolutionType::None;\n\
    \            } else {\n                if (cy > 0) { // k >= (lower - y0) / cy\n\
    \                    kymin = std::max(kymin, cld(lower - y0, cy));\n         \
    \       } else { // k <= (lower - y0) / cy\n                    kymax = std::min(kymax,\
    \ fld(lower - y0, cy));\n                }\n                if (kymin > kymax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n        bool set_upper_y(long long upper) {\n            if (t ==\
    \ SolutionType::None) return false;\n            // y0 + k * cy <= upper\n   \
    \         if (cy == 0) {\n                if (y0 > upper) t = SolutionType::None;\n\
    \            } else {\n                if (cy > 0) { // k <= (upper - y0) / cy\n\
    \                    kymin = std::min(kymin, fld(upper - y0, cy));\n         \
    \       } else { // k >= (upper - y0) / cy\n                    kymax = std::max(kymax,\
    \ cld(upper - y0, cy));\n                }\n                if (kymin > kymax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n\n        std::pair<long long, long long> xmin_solution() const {\n\
    \            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmin, kymin };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cx == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cx >= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> xmax_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmax,\
    \ kymax };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cx == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cx <= 0 ? kl : kr);\n    \
    \        }\n        }\n        std::pair<long long, long long> ymin_solution()\
    \ const {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmin, kymin };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cy == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cy >= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> ymax_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmax,\
    \ kymax };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cy == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cy <= 0 ? kl : kr);\n    \
    \        }\n        }\n    };\n\n    struct Equation {\n        long long a, b;\n\
    \        long long x, y, g;\n\n        Equation(long long a, long long b): a(a),\
    \ b(b) {\n            std::tie(x, y, g) = ext_gcd(a, b);\n        }\n\n      \
    \  // solve ax + by = z\n        Solution solve(long long z) {\n            if\
    \ (g == 0) {\n                if (z != 0) {\n                    return Solution::make_none();\n\
    \                } else {\n                    return Solution::make_arbitrary();\n\
    \                }\n            } else {\n                if (z % g) {\n     \
    \               return Solution::make_none();\n                } else {\n    \
    \                z /= g;\n                    return Solution::make_linear(x *\
    \ z, b / g, y * z, -a / g);\n                }\n            }\n        }\n   \
    \ };\n} // namespace suisen\n\n\n#line 6 \"library/number/garner.hpp\"\n\nnamespace\
    \ suisen {\n    /**\n     * @brief Calculates x mod m s.t. x = x_i (mod m_i).\
    \ m_i should be coprime each other.\n     * @param eq vector of { x_i, m_i }\n\
    \     * @return x mod m s.t. x = x_i (mod m_i)\n     */\n    int garner(std::vector<std::pair<int,\
    \ int>> eq, int m) {\n        const int n = eq.size();\n        std::vector<long\
    \ long> a(n);\n\n        auto calc_prefix = [&](int i, long long mod) {\n    \
    \        long long res = 0;\n            long long prd = 1;\n            for (int\
    \ j = 0; j < i; ++j) {\n                (res += a[j] * prd) %= mod;\n        \
    \        (prd *= eq[j].second) %= mod;\n            }\n            return res;\n\
    \        };\n    \n        for (int i = 0; i < n; ++i) {\n            auto [xi,\
    \ mi] = eq[i];\n            a[i] = (xi - calc_prefix(i, mi)) % mi;\n         \
    \   if (a[i] < 0) a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n   \
    \             long long mj = eq[j].second;\n                a[i] *= inv_mod(mj,\
    \ mi);\n                a[i] %= mi;\n            }\n        }\n        return\
    \ calc_prefix(n, m);\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_GARNER\n#define SUISEN_GARNER\n\n#include <vector>\n#include\
    \ \"library/number/ext_gcd.hpp\"\n\nnamespace suisen {\n    /**\n     * @brief\
    \ Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime each other.\n\
    \     * @param eq vector of { x_i, m_i }\n     * @return x mod m s.t. x = x_i\
    \ (mod m_i)\n     */\n    int garner(std::vector<std::pair<int, int>> eq, int\
    \ m) {\n        const int n = eq.size();\n        std::vector<long long> a(n);\n\
    \n        auto calc_prefix = [&](int i, long long mod) {\n            long long\
    \ res = 0;\n            long long prd = 1;\n            for (int j = 0; j < i;\
    \ ++j) {\n                (res += a[j] * prd) %= mod;\n                (prd *=\
    \ eq[j].second) %= mod;\n            }\n            return res;\n        };\n\
    \    \n        for (int i = 0; i < n; ++i) {\n            auto [xi, mi] = eq[i];\n\
    \            a[i] = (xi - calc_prefix(i, mi)) % mi;\n            if (a[i] < 0)\
    \ a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n                long\
    \ long mj = eq[j].second;\n                a[i] *= inv_mod(mj, mi);\n        \
    \        a[i] %= mi;\n            }\n        }\n        return calc_prefix(n,\
    \ m);\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_GARNER\n"
  dependsOn:
  - library/number/ext_gcd.hpp
  isVerificationFile: false
  path: library/number/garner.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
documentation_of: library/number/garner.hpp
layout: document
title: Garner's Algorithm
---
## Garner's Algorithm

## 問題

連立合同式 $x \equiv x _ i \pmod{m _ i}\; (i=1,\ldots,n)$ と正整数 $M$ が与えられる。ただし、 $i \neq j \Rightarrow \gcd(m _ i, m _ j) = 1$ が成り立つ。

連立合同式を満たす整数 $x$ は $0$ 以上 $\displaystyle\prod _ {i = 1} ^ n m _ i$ 未満の範囲に一意存在するので、この $x$ の値を $\mathrm{mod}\; M$ で求めよ。

---

本ライブラリは上記の問題を $O(n ^ 2 \log (\max_i m_i))$ 時間で解く実装である。$\displaystyle\prod _ {i = 1} ^ n m _ i$ が非常に大きくなりうる場合にもオーバーフローせずに解くことができる。

## アルゴリズム

$0\leq a _ i \lt m _ i$ を満たす整数 $a _ 1, \ldots, a _ n$ を用いて $x$ を以下のように表す。

$$\begin{aligned}
x
&= a _ 1 + a _ 2 m _ 1 + a _ 3 m _ 1 m _ 2 + \cdots + a _ n m _ 1 m _ 2 \cdots m _ {n - 1} \newline
&= \sum _ {i = 1} ^ n a _ i \prod _ {j = 1} ^ {i - 1} m _ j\tag{1}.
\end{aligned}$$

ここで、式 $(1)$ の両辺の $\mathrm{mod}\; m _ k$ を取ることで、次を得る。

$$
x _ k \equiv \sum _ {i = 1} ^ k a _ i \prod _ {j = 1} ^ {i - 1} m _ j \pmod{m _ k}.
$$

これを $a _ k$ について解いて、式 $(2)$ を得る。

$$
a _ k \equiv \Biggl( x _ k - \sum _ {i = 1} ^ {k - 1} a _ i \prod _ {j = 1} ^ {i - 1} m _ j\Biggr) \displaystyle \prod _ {j = 1} ^ {k - 1} m _ j ^ {-1} \pmod{m _ k}. \tag{2}
$$

ここで、$m _ j ^ {-1}$ は $\mathrm{mod}\; m _ k$ における $m _ j$ の乗法逆元を表す。$i \neq j \Rightarrow \gcd(m _ i, m _ j) = 1$ の仮定より、この逆元は必ず存在することに注意する。

式 $(2)$ の右辺を適切に $\mathrm{mod}\; m _ k$ を取りながら計算することで、計算途中の値を小さく保ったまま $a _ k$ の値を計算できる。$m _ j ^ {-1}$ の計算は合計 $O(k\log m _ k)$ 時間、$\sum a _ i\prod m _ j$ の計算は積を差分更新することで合計 $O(k)$ 時間で計算できる。

最後に、得られた $a _ 1,\ldots, a _ n$ を用いて式 $(1)$ の右辺を適切に $\mathrm{mod}\; M$ を取りながら計算することで、計算途中の値を小さく保ったまま $x\bmod M$ の値を得ることができる。

以上より、全体 $O(n ^ 2 \log (\max _ i m _ i))$ 時間で問題を解くことができた。

## 用途

### 任意 mod 畳み込み

NTT-friendly な素数 $p _ 1, \ldots, p _ k$ を用意して各々で畳みこんだ後、Garner のアルゴリズムを用いることで実現できる。

値が $0$ 以上 $L$ 以下で長さが $x, y$ の列を畳みこむ場合は、例えば $p _ 1 p _ 2 \cdots p _ k \gt L ^ 2 \max(x, y)$ を満たすように $p _ 1, \ldots, p _ k$ を選ぶことで、Garner のアルゴリズムにより復元された値が正しいことを保証できる。

## 参考

- https://redirect.cs.umbc.edu/~lomonaco/s08/441/handouts/Garner-Alg-Example.pdf
