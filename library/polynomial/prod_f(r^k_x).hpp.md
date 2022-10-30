---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/pow_mods.hpp
    title: "\u51AA\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
    title: test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
    links: []
  bundledCode: "#line 1 \"library/polynomial/prod_f(r^k_x).hpp\"\n\n\n\n#line 1 \"\
    library/math/pow_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen {\n \
    \   template <int base_as_int, typename mint>\n    struct static_pow_mods {\n\
    \        static_pow_mods() {}\n        static_pow_mods(int n) { ensure(n); }\n\
    \        const mint& operator[](int i) const {\n            ensure(i);\n     \
    \       return pows[i];\n        }\n        static void ensure(int n) {\n    \
    \        int sz = pows.size();\n            if (sz > n) return;\n            pows.resize(n\
    \ + 1);\n            for (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];\n\
    \        }\n    private:\n        static inline std::vector<mint> pows { 1 };\n\
    \        static inline mint base = base_as_int;\n        static constexpr int\
    \ mod = mint::mod();\n    };\n\n    template <typename mint>\n    struct pow_mods\
    \ {\n        pow_mods() {}\n        pow_mods(mint base, int n) : base(base) {\
    \ ensure(n); }\n        const mint& operator[](int i) const {\n            ensure(i);\n\
    \            return pows[i];\n        }\n        void ensure(int n) const {\n\
    \            int sz = pows.size();\n            if (sz > n) return;\n        \
    \    pows.resize(n + 1);\n            for (int i = sz; i <= n; ++i) pows[i] =\
    \ base * pows[i - 1];\n        }\n    private:\n        mutable std::vector<mint>\
    \ pows { 1 };\n        mint base;\n        static constexpr int mod = mint::mod();\n\
    \    };\n}\n\n\n#line 5 \"library/polynomial/prod_f(r^k_x).hpp\"\n\n/**\n * @brief\
    \ $\\left(\\prod_{k=0}^{m-1} f(r^k x)\\right) \\bmod x^N$\n */\n\nnamespace suisen\
    \ {\n    namespace internal::prod_f_rk_x {\n        template <typename FPSType>\n\
    \        FPSType prod_f_rk_x(FPSType f, typename FPSType::value_type r, int m,\
    \ int result_size) {\n            using mint = typename FPSType::value_type;\n\
    \            pow_mods<mint> pow_r(r, result_size), pow_rm(r.pow(m), result_size);\n\
    \            if (auto opt_sp_f = f.sparse_fps_format(15); opt_sp_f.has_value())\
    \ {\n                bool all_invertible = true;\n                for (int i =\
    \ 1; i < result_size; ++i) {\n                    if (pow_r[i] == mint{ 1 }) {\n\
    \                        all_invertible = false;\n                        break;\n\
    \                    }\n                }\n                if (all_invertible)\
    \ {\n                    auto &sp_f = *opt_sp_f;\n                    sp_f.erase(sp_f.begin());\n\
    \                    FPSType g(result_size);\n                    g[0] = 1;\n\
    \                    for (int i = 1; i < result_size; ++i) {\n               \
    \         for (auto [j, fj] : sp_f) {\n                            if (j > i)\
    \ break;\n                            g[i] += g[i - j] * fj * (pow_r[i - j] -\
    \ pow_rm[j]);\n                        }\n                        g[i] /= 1 -\
    \ pow_r[i];\n                    }\n                    return g;\n          \
    \      }\n            }\n            f = f.log(result_size);\n            for\
    \ (int i = 1; i < result_size; ++i) f[i] *= pow_r[i] == mint{ 1 } ? mint{ m }\
    \ : (pow_rm[i] - 1) / (pow_r[i] - 1);\n            return f.exp(result_size);\n\
    \        }\n    }\n    /**\n     * \\brief Calculates \u03A0[k=0,m-1] f(r^k x)\
    \ mod x^N in O(NlogN) time.\n     * \\tparam FPSType type of formal power series\n\
    \     * \\param f formal power series\n     * \\param r ratio\n     * \\param\
    \ m the number of terms of the product\n     * \\param result_size N (default:\
    \ size of f)\n     * \\return \u03A0[k=0,m-1] f(r^k x) mod x^N \n     */\n   \
    \ template <typename FPSType>\n    FPSType prod_f_rk_x(FPSType f, const typename\
    \ FPSType::value_type r, const int m, int result_size = -1) {\n        using mint\
    \ = typename FPSType::value_type;\n        if (result_size < 0) result_size =\
    \ f.size();\n        if (r == mint{ 1 }) return f.pow(m, result_size);\n     \
    \   if (m == 0) { FPSType res{ 1 }; res.resize(result_size); return res; }\n \
    \       int z = 0;\n        while (z < int(f.size()) and f[z] == mint{ 0 }) ++z;\n\
    \        if (z == int(f.size()) or z >= (result_size + m - 1) / m) return FPSType(result_size,\
    \ mint{ 0 });\n        const mint c = f[z], d = c.pow(m) * r.pow((long long) m\
    \ * (m - 1) / 2 * z);\n        f >>= z, f /= c; // => f[0] = 1\n        f = internal::prod_f_rk_x::prod_f_rk_x(f,\
    \ r, m, result_size - z * m);\n        f *= d, f <<= z * m;\n        return f;\n\
    \    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_PROD_F_RK_X\n#define SUISEN_PROD_F_RK_X\n\n#include \"library/math/pow_mods.hpp\"\
    \n\n/**\n * @brief $\\left(\\prod_{k=0}^{m-1} f(r^k x)\\right) \\bmod x^N$\n */\n\
    \nnamespace suisen {\n    namespace internal::prod_f_rk_x {\n        template\
    \ <typename FPSType>\n        FPSType prod_f_rk_x(FPSType f, typename FPSType::value_type\
    \ r, int m, int result_size) {\n            using mint = typename FPSType::value_type;\n\
    \            pow_mods<mint> pow_r(r, result_size), pow_rm(r.pow(m), result_size);\n\
    \            if (auto opt_sp_f = f.sparse_fps_format(15); opt_sp_f.has_value())\
    \ {\n                bool all_invertible = true;\n                for (int i =\
    \ 1; i < result_size; ++i) {\n                    if (pow_r[i] == mint{ 1 }) {\n\
    \                        all_invertible = false;\n                        break;\n\
    \                    }\n                }\n                if (all_invertible)\
    \ {\n                    auto &sp_f = *opt_sp_f;\n                    sp_f.erase(sp_f.begin());\n\
    \                    FPSType g(result_size);\n                    g[0] = 1;\n\
    \                    for (int i = 1; i < result_size; ++i) {\n               \
    \         for (auto [j, fj] : sp_f) {\n                            if (j > i)\
    \ break;\n                            g[i] += g[i - j] * fj * (pow_r[i - j] -\
    \ pow_rm[j]);\n                        }\n                        g[i] /= 1 -\
    \ pow_r[i];\n                    }\n                    return g;\n          \
    \      }\n            }\n            f = f.log(result_size);\n            for\
    \ (int i = 1; i < result_size; ++i) f[i] *= pow_r[i] == mint{ 1 } ? mint{ m }\
    \ : (pow_rm[i] - 1) / (pow_r[i] - 1);\n            return f.exp(result_size);\n\
    \        }\n    }\n    /**\n     * \\brief Calculates \u03A0[k=0,m-1] f(r^k x)\
    \ mod x^N in O(NlogN) time.\n     * \\tparam FPSType type of formal power series\n\
    \     * \\param f formal power series\n     * \\param r ratio\n     * \\param\
    \ m the number of terms of the product\n     * \\param result_size N (default:\
    \ size of f)\n     * \\return \u03A0[k=0,m-1] f(r^k x) mod x^N \n     */\n   \
    \ template <typename FPSType>\n    FPSType prod_f_rk_x(FPSType f, const typename\
    \ FPSType::value_type r, const int m, int result_size = -1) {\n        using mint\
    \ = typename FPSType::value_type;\n        if (result_size < 0) result_size =\
    \ f.size();\n        if (r == mint{ 1 }) return f.pow(m, result_size);\n     \
    \   if (m == 0) { FPSType res{ 1 }; res.resize(result_size); return res; }\n \
    \       int z = 0;\n        while (z < int(f.size()) and f[z] == mint{ 0 }) ++z;\n\
    \        if (z == int(f.size()) or z >= (result_size + m - 1) / m) return FPSType(result_size,\
    \ mint{ 0 });\n        const mint c = f[z], d = c.pow(m) * r.pow((long long) m\
    \ * (m - 1) / 2 * z);\n        f >>= z, f /= c; // => f[0] = 1\n        f = internal::prod_f_rk_x::prod_f_rk_x(f,\
    \ r, m, result_size - z * m);\n        f *= d, f <<= z * m;\n        return f;\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_PROD_F_RK_X\n"
  dependsOn:
  - library/math/pow_mods.hpp
  isVerificationFile: false
  path: library/polynomial/prod_f(r^k_x).hpp
  requiredBy: []
  timestamp: '2022-10-08 20:12:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
documentation_of: library/polynomial/prod_f(r^k_x).hpp
layout: document
title: $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
---
## $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$

$\displaystyle F(x) := \prod_{k=0}^{m-1} f(r^k x)$ とする。形式的冪級数 $f$ の $i$ 次の係数を $f_i$ と書く。

$f(x)=0$ の場合は自明なので、$f(x)\neq 0$ を仮定する。また、$f _ 0=1$ と仮定する。

$f _ 0\neq 1$ の場合は $f = c\cdot x ^ a\cdot f'\; (f' _ 0 = 1)$ とすれば、次のようにして定数項が $1$ のケースに帰着できる。

$$F(x)=c ^ m r ^ {\frac{m(m-1)}{2}a} x ^ {\frac{m(m-1)}{2}} \prod _ {k = 0} ^ {m - 1} f'(r ^ k x).$$

$g=\log f$ とおくと、$F = \exp (\log F)$ を用いることで、$F \bmod x ^ N$ を $O(N \log N)$ 時間で計算できる。

$$\begin{aligned}
\log F
&= \sum _ {k = 0} ^ {m - 1} \log f(r ^ k x) \newline
&= \sum _ {k = 0} ^ {m - 1} g(r ^ k x) \newline
&= \sum _ {i = 0} ^ {\infty} g _ i x ^ i\sum _ {k = 0} ^ {m - 1} (r ^ i) ^ k \newline
&= \sum _ {i = 0} ^ {\infty} g _ i x ^ i \cdot \begin{cases}
\displaystyle m \cdot x ^ i & \text {if}\quad r ^ i = 1 \newline
\displaystyle \dfrac{(r ^ m) ^ i - 1}{r ^ i - 1} & \text{otherwise}
\end{cases}.
\end{aligned}$$

<!-- ### $f$ が疎な場合

以下の等式を用いる。

$$F(x) f(r ^ m x) = F(rx) f(x).$$

両辺で $i$ 次の項が等しいことに注目すると、次の等式が得られる。

$$\begin{aligned}
&\sum _ {j = 0} ^ i F _ j f _ {i - j}(r ^ m) ^ {i - j} = \sum _ {j = 0} ^ i F _ j f _ {i - j}r ^ j \newline
\iff &\sum_ {j = 0} ^ i F_j f _ {i - j}(r ^ {m(i - j)} - r ^ j) = 0 \newline
\iff &F _ i f_0(1 - r ^ i) = \sum _ {j = 0} ^ {i - 1} F_j f _ {i - j} (r ^ j - r ^ {m(i - j)})
\end{aligned}$$

$f _ 0 = 1$ より、**$r$ の位数が十分大きいことを仮定すると、** 両辺を $1 - r ^ i$ で割ることで $F _ i$ を得ることができる。$f$ の非零の係数が $K$ 個であれば、$F \bmod x ^ N$ を $O(N(K + \log \mathrm{mod}))$ で計算できる。 -->

## 参考

- https://maspypy.com/%E5%A4%9A%E9%A0%85%E5%BC%8F%E3%83%BB%E5%BD%A2%E5%BC%8F%E7%9A%84%E3%81%B9%E3%81%8D%E7%B4%9A%E6%95%B0-%E9%AB%98%E9%80%9F%E3%81%AB%E8%A8%88%E7%AE%97%E3%81%A7%E3%81%8D%E3%82%8B%E3%82%82%E3%81%AE#toc21