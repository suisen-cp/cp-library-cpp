---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/relaxed_convolution_ntt.hpp
    title: Relaxed Convolution Ntt
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/formal_power_series_relaxed/exp_of_formal_power_series.test.cpp
    title: test/src/polynomial/formal_power_series_relaxed/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/formal_power_series_relaxed/inv_of_formal_power_series.test.cpp
    title: test/src/polynomial/formal_power_series_relaxed/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/formal_power_series_relaxed/log_of_formal_power_series.test.cpp
    title: test/src/polynomial/formal_power_series_relaxed/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/formal_power_series_relaxed/pow_of_formal_power_series.test.cpp
    title: test/src/polynomial/formal_power_series_relaxed/pow_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/formal_power_series_relaxed/sqrt_of_formal_power_series.test.cpp
    title: test/src/polynomial/formal_power_series_relaxed/sqrt_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/formal_power_series_relaxed.hpp\"\n\n\
    \n\n#include <atcoder/convolution>\n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\
    \n#include <vector>\n\nnamespace suisen {\n    template <typename mint>\n    class\
    \ inv_mods {\n    public:\n        inv_mods() = default;\n        inv_mods(int\
    \ n) { ensure(n); }\n        const mint& operator[](int i) const {\n         \
    \   ensure(i);\n            return invs[i];\n        }\n        static void ensure(int\
    \ n) {\n            int sz = invs.size();\n            if (sz < 2) invs = { 0,\
    \ 1 }, sz = 2;\n            if (sz < n + 1) {\n                invs.resize(n +\
    \ 1);\n                for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod\
    \ / i) * invs[mod % i];\n            }\n        }\n    private:\n        static\
    \ std::vector<mint> invs;\n        static constexpr int mod = mint::mod();\n \
    \   };\n    template <typename mint>\n    std::vector<mint> inv_mods<mint>::invs{};\n\
    \n    template <typename mint>\n    std::vector<mint> get_invs(const std::vector<mint>&\
    \ vs) {\n        const int n = vs.size();\n\n        mint p = 1;\n        for\
    \ (auto& e : vs) {\n            p *= e;\n            assert(e != 0);\n       \
    \ }\n        mint ip = p.inv();\n\n        std::vector<mint> rp(n + 1);\n    \
    \    rp[n] = 1;\n        for (int i = n - 1; i >= 0; --i) {\n            rp[i]\
    \ = rp[i + 1] * vs[i];\n        }\n        std::vector<mint> res(n);\n       \
    \ for (int i = 0; i < n; ++i) {\n            res[i] = ip * rp[i + 1];\n      \
    \      ip *= vs[i];\n        }\n        return res;\n    }\n}\n\n\n#line 1 \"\
    library/convolution/relaxed_convolution_ntt.hpp\"\n\n\n\n#line 5 \"library/convolution/relaxed_convolution_ntt.hpp\"\
    \n\nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
    \    template <typename mint>\n    struct RelaxedConvolutionNTT {\n        RelaxedConvolutionNTT():\
    \ _n(0), _f{}, _g{}, _h{} {}\n\n        mint append(const mint& fi, const mint&\
    \ gi) {\n            static constexpr int threshold_log = 6;\n            static\
    \ constexpr int threshold = 1 << threshold_log;\n            static constexpr\
    \ int threshold_mask = threshold - 1;\n\n            ++_n;\n            _f.push_back(fi),\
    \ _g.push_back(gi);\n\n            const int q = _n >> threshold_log, r = _n &\
    \ threshold_mask;\n            if (r == 0) {\n                if (q == (-q & q))\
    \ {\n                    std::vector<mint> f_fft = _f;\n                    std::vector<mint>\
    \ g_fft = _g;\n                    f_fft.resize(2 * _n);\n                   \
    \ g_fft.resize(2 * _n);\n                    atcoder::internal::butterfly(f_fft);\n\
    \                    atcoder::internal::butterfly(g_fft);\n                  \
    \  std::vector<mint> h(2 * _n);\n                    for (int i = 0; i < 2 * _n;\
    \ ++i) {\n                        h[i] = f_fft[i] * g_fft[i];\n              \
    \      }\n                    atcoder::internal::butterfly_inv(h);\n         \
    \           ensure(2 * _n);\n                    const mint z = mint(2 * _n).inv();\n\
    \                    for (int i = _n - 1; i < 2 * _n; ++i) {\n               \
    \         _h[i] += h[i] * z;\n                    }\n                    _f_fft.push_back(std::move(f_fft));\n\
    \                    _g_fft.push_back(std::move(g_fft));\n                } else\
    \ {\n                    const int log_q = __builtin_ctz(q);\n               \
    \     const int k = (-q & q) << threshold_log;\n\n                    std::vector<mint>\
    \ f_fft(_f.end() - k, _f.end());\n                    std::vector<mint> g_fft(_g.end()\
    \ - k, _g.end());\n                    f_fft.resize(2 * k);\n                \
    \    g_fft.resize(2 * k);\n                    atcoder::internal::butterfly(f_fft);\n\
    \                    atcoder::internal::butterfly(g_fft);\n                  \
    \  std::vector<mint> h(2 * k);\n                    for (int i = 0; i < 2 * k;\
    \ ++i) {\n                        h[i] = _f_fft[log_q + 1][i] * g_fft[i] + f_fft[i]\
    \ * _g_fft[log_q + 1][i];\n                    }\n                    atcoder::internal::butterfly_inv(h);\n\
    \                    const mint z = mint(2 * k).inv();\n                    for\
    \ (int i = 0; i < k; ++i) {\n                        _h[_n - 1 + i] += h[k - 1\
    \ + i] * z;\n                    }\n                }\n            } else {\n\
    \                // naive convolve\n                ensure(_n);\n            \
    \    for (int i = 0; i < r; ++i) {\n                    _h[_n - 1] += _f[i] *\
    \ _g[_n - 1 - i];\n                }\n                if (_n != r) {\n       \
    \             for (int i = 0; i < r; ++i) {\n                        _h[_n - 1]\
    \ += _f[_n - i - 1] * _g[i];\n                    }\n                }\n     \
    \       }\n            return _h[_n - 1];\n        }\n\n        const mint& operator[](int\
    \ i) const {\n            return _h[i];\n        }\n        std::vector<mint>\
    \ get() const {\n            return _h;\n        }\n\n    private:\n        int\
    \ _n;\n        std::vector<mint> _f, _g, _h;\n\n        std::vector<std::vector<mint>>\
    \ _f_fft, _g_fft;\n\n        void ensure(std::size_t n) {\n            if (_h.size()\
    \ < n) _h.resize(n);\n        }\n    };\n} // namespace suisen\n\n\n\n#line 1\
    \ \"library/math/modint_extension.hpp\"\n\n\n\n#include <cassert>\n#include <optional>\n\
    \n/**\n * refernce: https://37zigen.com/tonelli-shanks-algorithm/\n * calculates\
    \ x s.t. x^2 = a mod p in O((log p)^2).\n */\ntemplate <typename mint>\nstd::optional<mint>\
    \ safe_sqrt(mint a) {\n    static int p = mint::mod();\n    if (a == 0) return\
    \ std::make_optional(0);\n    if (p == 2) return std::make_optional(a);\n    if\
    \ (a.pow((p - 1) / 2) != 1) return std::nullopt;\n    mint b = 1;\n    while (b.pow((p\
    \ - 1) / 2) == 1) ++b;\n    static int tlz = __builtin_ctz(p - 1), q = (p - 1)\
    \ >> tlz;\n    mint x = a.pow((q + 1) / 2);\n    b = b.pow(q);\n    for (int shift\
    \ = 2; x * x != a; ++shift) {\n        mint e = a.inv() * x * x;\n        if (e.pow(1\
    \ << (tlz - shift)) != 1) x *= b;\n        b *= b;\n    }\n    return std::make_optional(x);\n\
    }\n\n/**\n * calculates x s.t. x^2 = a mod p in O((log p)^2).\n * if not exists,\
    \ raises runtime error.\n */\ntemplate <typename mint>\nauto sqrt(mint a) -> decltype(mint::mod(),\
    \ mint()) {\n    return *safe_sqrt(a);\n}\ntemplate <typename mint>\nauto log(mint\
    \ a) -> decltype(mint::mod(), mint()) {\n    assert(a == 1);\n    return 0;\n\
    }\ntemplate <typename mint>\nauto exp(mint a) -> decltype(mint::mod(), mint())\
    \ {\n    assert(a == 0);\n    return 1;\n}\ntemplate <typename mint, typename\
    \ T>\nauto pow(mint a, T b) -> decltype(mint::mod(), mint()) {\n    return a.pow(b);\n\
    }\ntemplate <typename mint>\nauto inv(mint a) -> decltype(mint::mod(), mint())\
    \ {\n    return a.inv();\n}\n\n\n#line 8 \"library/polynomial/formal_power_series_relaxed.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    struct RelaxedInv {\n\
    \        mint append(const mint& fi) {\n            const int i = g.size();\n\
    \            if (i == 0) {\n                assert(fi != 0);\n               \
    \ g.push_back(fi.inv());\n            } else {\n                g.push_back(-g[0]\
    \ * fg.append(fi, g[i - 1]));\n            }\n            return g.back();\n \
    \       }\n        mint operator[](int i) const {\n            return g[i];\n\
    \        }\n    private:\n        std::vector<mint> g;\n        RelaxedConvolutionNTT<mint>\
    \ fg;\n    };\n\n    template <typename mint>\n    struct RelaxedExp {\n     \
    \   mint append(const mint& fi) {\n            static inv_mods<mint> invs;\n \
    \           const int i = g.size();\n            if (i == 0) {\n             \
    \   assert(fi == 0);\n                g.push_back(1);\n            } else {\n\
    \                g.push_back(df_g.append(i * fi, g[i - 1]) * invs[i]);\n     \
    \       }\n            return g.back();\n        }\n        mint operator[](int\
    \ i) const {\n            return g[i];\n        }\n    private:\n        std::vector<mint>\
    \ g;\n        RelaxedConvolutionNTT<mint> df_g;\n    };\n\n    template <typename\
    \ mint>\n    struct RelaxedLog {\n        mint append(const mint& fi) {\n    \
    \        static inv_mods<mint> invs;\n            f.push_back(fi);\n         \
    \   const int i = g.size();\n            if (i == 0) {\n                assert(f[i]\
    \ == 1);\n                g.push_back(0);\n            } else if (i == 1) {\n\
    \                g.push_back(f[i]);\n            } else {\n                g.push_back(f[i]\
    \ - fg.append((i - 1) * g[i - 1], f[i - 1]) * invs[i]);\n            }\n     \
    \       return g.back();\n        }\n        mint operator[](int i) const {\n\
    \            return g[i];\n        }\n    private:\n        std::vector<mint>\
    \ f, g;\n        RelaxedConvolutionNTT<mint> fg;\n    };\n\n    template <typename\
    \ mint>\n    struct RelaxedPow {\n        RelaxedPow(long long k = 0) : k(k) {}\n\
    \n        mint append(const mint& fi) {\n            if (k == 0) {\n         \
    \       return g.emplace_back(g.empty() ? 1 : 0);\n            }\n           \
    \ static inv_mods<mint> invs;\n            if (is_zero) {\n                if\
    \ (fi == 0) {\n                    z = std::min(z + k, 1000000000LL);\n      \
    \          } else {\n                    is_zero = false;\n                  \
    \  inv_base = fi.inv();\n                }\n            }\n            if (not\
    \ is_zero) {\n                f.push_back(fi);\n            }\n            if\
    \ (index < z) {\n                g.push_back(0);\n            } else if (index\
    \ == z) {\n                g.push_back(f[0].pow(k));\n            } else {\n \
    \               int i = index - z;\n                mint v1 = fg1.append(mint(k\
    \ - (i - 1)) * g[z + i - 1], f[i]);\n                mint v2 = fg2.append(g[z\
    \ + i - 1], mint(k) * (i - 1) * f[i]);\n                g.push_back((v1 + v2)\
    \ * inv_base * invs[i]);\n            }\n            ++index;\n            return\
    \ g.back();\n        }\n        mint operator[](int i) const {\n            return\
    \ g[i];\n        }\n    private:\n        long long k;\n        long long z =\
    \ 0;\n        long long index = 0;\n        bool is_zero = true;\n        mint\
    \ inv_base = 0;\n\n        std::vector<mint> f, g;\n        RelaxedConvolutionNTT<mint>\
    \ fg1;\n        RelaxedConvolutionNTT<mint> fg2;\n    };\n\n    template <typename\
    \ mint>\n    struct RelaxedSqrt {\n        std::optional<mint> append(const mint&\
    \ fi) {\n            if (g.empty()) {\n                auto opt_g0 = safe_sqrt(fi);\n\
    \                if (not opt_g0) return std::nullopt;\n                mint g0\
    \ = *opt_g0;\n                c = (2 * g0).inv();\n                return g.emplace_back(g0);\n\
    \            } else if (g.size() == 1) {\n                return g.emplace_back(c\
    \ * fi);\n            } else {\n                mint gi = c * (fi - gg.append(g.back(),\
    \ g.back()));\n                return g.emplace_back(gi);\n            }\n   \
    \     }\n        mint operator[](int i) const {\n            return g[i];\n  \
    \      }\n    private:\n        mint c = 0;\n        std::vector<mint> g;\n  \
    \      RelaxedConvolutionNTT<mint> gg;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_FPS_RELAXED\n#define SUISEN_FPS_RELAXED\n\n#include <atcoder/convolution>\n\
    #include \"library/math/inv_mods.hpp\"\n#include \"library/convolution/relaxed_convolution_ntt.hpp\"\
    \n#include \"library/math/modint_extension.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    struct RelaxedInv {\n        mint append(const mint& fi)\
    \ {\n            const int i = g.size();\n            if (i == 0) {\n        \
    \        assert(fi != 0);\n                g.push_back(fi.inv());\n          \
    \  } else {\n                g.push_back(-g[0] * fg.append(fi, g[i - 1]));\n \
    \           }\n            return g.back();\n        }\n        mint operator[](int\
    \ i) const {\n            return g[i];\n        }\n    private:\n        std::vector<mint>\
    \ g;\n        RelaxedConvolutionNTT<mint> fg;\n    };\n\n    template <typename\
    \ mint>\n    struct RelaxedExp {\n        mint append(const mint& fi) {\n    \
    \        static inv_mods<mint> invs;\n            const int i = g.size();\n  \
    \          if (i == 0) {\n                assert(fi == 0);\n                g.push_back(1);\n\
    \            } else {\n                g.push_back(df_g.append(i * fi, g[i - 1])\
    \ * invs[i]);\n            }\n            return g.back();\n        }\n      \
    \  mint operator[](int i) const {\n            return g[i];\n        }\n    private:\n\
    \        std::vector<mint> g;\n        RelaxedConvolutionNTT<mint> df_g;\n   \
    \ };\n\n    template <typename mint>\n    struct RelaxedLog {\n        mint append(const\
    \ mint& fi) {\n            static inv_mods<mint> invs;\n            f.push_back(fi);\n\
    \            const int i = g.size();\n            if (i == 0) {\n            \
    \    assert(f[i] == 1);\n                g.push_back(0);\n            } else if\
    \ (i == 1) {\n                g.push_back(f[i]);\n            } else {\n     \
    \           g.push_back(f[i] - fg.append((i - 1) * g[i - 1], f[i - 1]) * invs[i]);\n\
    \            }\n            return g.back();\n        }\n        mint operator[](int\
    \ i) const {\n            return g[i];\n        }\n    private:\n        std::vector<mint>\
    \ f, g;\n        RelaxedConvolutionNTT<mint> fg;\n    };\n\n    template <typename\
    \ mint>\n    struct RelaxedPow {\n        RelaxedPow(long long k = 0) : k(k) {}\n\
    \n        mint append(const mint& fi) {\n            if (k == 0) {\n         \
    \       return g.emplace_back(g.empty() ? 1 : 0);\n            }\n           \
    \ static inv_mods<mint> invs;\n            if (is_zero) {\n                if\
    \ (fi == 0) {\n                    z = std::min(z + k, 1000000000LL);\n      \
    \          } else {\n                    is_zero = false;\n                  \
    \  inv_base = fi.inv();\n                }\n            }\n            if (not\
    \ is_zero) {\n                f.push_back(fi);\n            }\n            if\
    \ (index < z) {\n                g.push_back(0);\n            } else if (index\
    \ == z) {\n                g.push_back(f[0].pow(k));\n            } else {\n \
    \               int i = index - z;\n                mint v1 = fg1.append(mint(k\
    \ - (i - 1)) * g[z + i - 1], f[i]);\n                mint v2 = fg2.append(g[z\
    \ + i - 1], mint(k) * (i - 1) * f[i]);\n                g.push_back((v1 + v2)\
    \ * inv_base * invs[i]);\n            }\n            ++index;\n            return\
    \ g.back();\n        }\n        mint operator[](int i) const {\n            return\
    \ g[i];\n        }\n    private:\n        long long k;\n        long long z =\
    \ 0;\n        long long index = 0;\n        bool is_zero = true;\n        mint\
    \ inv_base = 0;\n\n        std::vector<mint> f, g;\n        RelaxedConvolutionNTT<mint>\
    \ fg1;\n        RelaxedConvolutionNTT<mint> fg2;\n    };\n\n    template <typename\
    \ mint>\n    struct RelaxedSqrt {\n        std::optional<mint> append(const mint&\
    \ fi) {\n            if (g.empty()) {\n                auto opt_g0 = safe_sqrt(fi);\n\
    \                if (not opt_g0) return std::nullopt;\n                mint g0\
    \ = *opt_g0;\n                c = (2 * g0).inv();\n                return g.emplace_back(g0);\n\
    \            } else if (g.size() == 1) {\n                return g.emplace_back(c\
    \ * fi);\n            } else {\n                mint gi = c * (fi - gg.append(g.back(),\
    \ g.back()));\n                return g.emplace_back(gi);\n            }\n   \
    \     }\n        mint operator[](int i) const {\n            return g[i];\n  \
    \      }\n    private:\n        mint c = 0;\n        std::vector<mint> g;\n  \
    \      RelaxedConvolutionNTT<mint> gg;\n    };\n} // namespace suisen\n\n\n#endif\
    \ // SUISEN_FPS_RELAXED\n"
  dependsOn:
  - library/math/inv_mods.hpp
  - library/convolution/relaxed_convolution_ntt.hpp
  - library/math/modint_extension.hpp
  isVerificationFile: false
  path: library/polynomial/formal_power_series_relaxed.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/formal_power_series_relaxed/exp_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/log_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/inv_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/pow_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/sqrt_of_formal_power_series.test.cpp
documentation_of: library/polynomial/formal_power_series_relaxed.hpp
layout: document
title: Formal Power Series Relaxed
---
## Formal Power Series Relaxed

形式的べき級数 $f\in \mathbb{K}\lbrack\lbrack x\rbrack\rbrack$ の $x ^ i$ の係数を $f_i$ と書く．

以下に示す漸化式に従って Relaxed Convolution を適用することで，$\Theta(N (\log N) ^ 2)$ 時間で $\mathrm{inv},\log,\exp$ などをオンラインで計算できる．

### $h = f / g$ (未実装)

$g _ 0 \in \mathbb{K} ^ {\times}$ を仮定する．

$$
\begin{aligned}
f _ n 
&= \sum _ {i = 0} ^ n h _ i g _ {n - i}\\
&= h _ n g _ 0 + \sum _ {i = 0} ^ {n - 1} h _ i g _ {n - i},\\
h _ n 
&= \dfrac{1}{g _ 0}\left(f _ n - \sum _ {i = 0} ^ {n - 1}h _ i g _ {n - i} \right).
\end{aligned}
$$

### $g = 1/f$

$f _ 0 \in \mathbb{K} ^ {\times}$ を仮定する．

$$
g _ n = \begin{cases}
f _ 0 ^ {-1} & \text{if } n = 0\\
\displaystyle -f _ 0 ^ {-1} \sum _ {i = 0} ^ {n - 1} g _ i f _ {n - i} & \text{otherwise}
\end{cases}
$$

### $g = \exp f$

$f _ 0 = 0$ を仮定する．$g' = f' g$ より，

$$
\begin{aligned}
(n + 1) g _ {n + 1}
&= \sum _ {i = 0} ^ n (n - i + 1) f _ {n - i + 1} g _ i,\\
g _ n &= \begin{cases}
1 & \text{if }n = 0 \\
\dfrac{1}{n}\displaystyle\sum _ {i = 0} ^ {n - 1} (n - i) f _ {n - i } g _ i &\text{otherwise}

\end{cases}
\end{aligned}
$$

### $g = \log f$

$g _ 0 = 1$ を仮定する．$fg'=f'$ より，

$$
\begin{aligned}
\sum _ {i = 0} ^ n (i+1) g _ {i + 1} f _ {n - i} &= (n + 1)f _ {n + 1},\\
(n + 1) f _ 0 g _ {n + 1} &= (n + 1) f _ {n + 1} - \sum _ {i = 0} ^ {n - 1}(i+1) g _ {i + 1} f _ {n - i},\\
g _ {n + 1} &= \dfrac{1}{(n+1)f_0}\left((n + 1) f _ {n + 1} - \sum _ {i = 0} ^ {n - 1}(i+1) g _ {i + 1} f _ {n - i}\right),\\
g _ n &= \begin{cases}
0 & \text{if }n = 0\\
\displaystyle \dfrac{1}{nf_0}\left(n f _ {n} - \sum _ {i = 1} ^ {n - 1}i g _ i f _ {n - i}\right) & \text{otherwise}
\end{cases}
\end{aligned}
$$

### $g = f ^ k$

$f_0\neq 0$ を仮定する．$f _ 0 = 0$ の場合は，$f = x ^ p \cdot f'\ (f'_0 \neq 0)$ の形に直してから $g = x ^ {pk} f'^ k$  として計算すればよい．$g'=kf^{k-1} f'$ の両辺に $f$ を掛けることで $fg'=kgf'$ が得られるので，

$$
\begin{aligned}
\sum _ {i = 0} ^ n (i + 1) g _ {i + 1} f _ {n - i} 
&= k\sum _ {i = 0} ^ n g _ i\cdot (n-i+1) f _ {n-i+1}, \\
(n+1)f_0g _ {n+1}
&= k\sum _ {i = 0} ^ n g _ i\cdot (n-i+1) f _ {n-i+1} - \sum _ {i = 1} ^ {n} i g _ i f _ {n - i + 1} \\
&=\sum _ {i = 0} ^ {n} (k(n-i+1)-i)g_i f _{n-i+1},\\
g _ {n + 1} &= \dfrac{1}{(n+1)f_0}\sum _ {i = 0} ^ {n} (k(n-i+1)-i)g_i f _{n-i+1},\\
g _ n &= \begin{cases}
f _ 0 ^ k & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n-1} (k(n-i)-i)g_i f _{n-i} & \text{otherwise}
\end{cases}
\end{aligned}
$$

### $g = f ^ {1/2}$

$f _ 0 \neq 0$ であることおよび $f _ 0 ^ {1/2}$ の存在を仮定する．

$$
\begin{aligned}
f _ {n+1} &= \sum _ {i = 0} ^ {n + 1} g _ i g _ {n + 1 - i},\\
2g _ 0 g _ {n + 1} &= f _ {n + 1} - \sum _ {i = 1} ^ {n} g _ i g _ {n + 1 - i},\\
g _ n &= \begin{cases}
f _ 0 ^ {1/2} & \text{if }n = 0\\
\displaystyle \dfrac{1}{2g_0}\left(f _ {n } - \sum _ {i = 1} ^ {n-1} g _ i g _ {n - i}\right) & \text{otherwise}
\end{cases}
\end{aligned}
$$

### $g = f ^ {1/k}$ (未実装)

$f _ 0 \neq 0$ であることおよび $f _ 0 ^ {1/k}$ の存在を仮定する．$g ^ k = f$ を $\mathrm{pow}$ と同様に微分することで，次を得る．

$$
g _ n = \begin{cases}
f _ 0 ^ {1/k} & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n-1} (k^{-1}(n-i)-i)g_i f _{n-i} & \text{otherwise}
\end{cases}
$$

より一般には，$g = f ^ {p/q}$ を満たす $g$ を計算できる．