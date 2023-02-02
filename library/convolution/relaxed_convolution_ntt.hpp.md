---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/polynomial/formal_power_series_relaxed.hpp
    title: Formal Power Series Relaxed
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/relaxed_convolution_ntt/convolution_mod.test.cpp
    title: test/src/convolution/relaxed_convolution_ntt/convolution_mod.test.cpp
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
  - icon: ':x:'
    path: test/src/polynomial/formal_power_series_relaxed/sqrt_of_formal_power_series.test.cpp
    title: test/src/polynomial/formal_power_series_relaxed/sqrt_of_formal_power_series.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links:
    - https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
  bundledCode: "#line 1 \"library/convolution/relaxed_convolution_ntt.hpp\"\n\n\n\n\
    #include <atcoder/convolution>\n\nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
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
    \ < n) _h.resize(n);\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_RELAXED_CONVOLUTION_NTT\n#define SUISEN_RELAXED_CONVOLUTION_NTT\n\
    \n#include <atcoder/convolution>\n\nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
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
    \ < n) _h.resize(n);\n        }\n    };\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_RELAXED_CONVOLUTION_NTT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/relaxed_convolution_ntt.hpp
  requiredBy:
  - library/polynomial/formal_power_series_relaxed.hpp
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/polynomial/formal_power_series_relaxed/pow_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/inv_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/sqrt_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/exp_of_formal_power_series.test.cpp
  - test/src/polynomial/formal_power_series_relaxed/log_of_formal_power_series.test.cpp
  - test/src/convolution/relaxed_convolution_ntt/convolution_mod.test.cpp
documentation_of: library/convolution/relaxed_convolution_ntt.hpp
layout: document
title: Relaxed Convolution Ntt
---
## Relaxed Convolution Ntt
