---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/semi_relaxed_convolution_ntt.hpp
    title: Semi Relaxed Convolution Ntt
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/exp_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/exp_of_formal_power_series
  bundledCode: "#line 1 \"test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_formal_power_series\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/math/inv_mods.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <typename mint>\n\
    \    class inv_mods {\n    public:\n        inv_mods() = default;\n        inv_mods(int\
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
    library/convolution/semi_relaxed_convolution_ntt.hpp\"\n\n\n\n#include <atcoder/convolution>\n\
    \nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
    \    template <typename mint>\n    struct SemiRelaxedConvolutionNTT {\n      \
    \  SemiRelaxedConvolutionNTT() = default;\n        SemiRelaxedConvolutionNTT(const\
    \ std::vector<mint> &f) : _n(0), _f(f), _g{}, _h{} {}\n\n        mint append(const\
    \ mint& gi) {\n            static constexpr int threshold_log = 6;\n         \
    \   static constexpr int threshold = 1 << threshold_log;\n            static constexpr\
    \ int threshold_mask = threshold - 1;\n\n            ++_n;\n            _g.push_back(gi);\n\
    \n            int q = _n >> threshold_log, r = _n & threshold_mask;\n        \
    \    if (r == 0) {\n                if (q == (-q & q)) {\n                   \
    \ std::vector<mint> f_fft(_f.begin(), _f.begin() + std::min(int(_f.size()), 2\
    \ * _n));\n                    f_fft.resize(2 * _n);\n                    atcoder::internal::butterfly(f_fft);\n\
    \                    _f_fft.push_back(std::move(f_fft));\n                }\n\
    \                const int log_q = __builtin_ctz(q);\n                const int\
    \ k = (-q & q) << threshold_log;\n                std::vector<mint> g_fft(_g.end()\
    \ - k, _g.end());\n                g_fft.resize(2 * k);\n                atcoder::internal::butterfly(g_fft);\n\
    \                const mint z = mint(2 * k).inv();\n                std::vector<mint>\
    \ h(2 * k);\n                for (int i = 0; i < 2 * k; ++i) h[i] = _f_fft[log_q][i]\
    \ * g_fft[i] * z;\n                atcoder::internal::butterfly_inv(h);\n    \
    \            ensure(_n - 1 + k);\n                for (int i = 0; i < k; ++i)\
    \ _h[_n - 1 + i] += h[k - 1 + i];\n            } else {\n                // naive\
    \ convolve\n                r = std::min(r, int(_f.size()));\n               \
    \ ensure(_n);\n                for (int i = 0; i < r; ++i) {\n               \
    \     _h[_n - 1] += _f[i] * _g[_n - 1 - i];\n                }\n            }\n\
    \            return _h[_n - 1];\n        }\n\n        const mint& operator[](int\
    \ i) const {\n            return _h[i];\n        }\n        std::vector<mint>\
    \ get() const {\n            return _h;\n        }\n\n    private:\n        int\
    \ _n;\n        std::vector<mint> _f, _g, _h;\n\n        std::vector<std::vector<mint>>\
    \ _f_fft;\n\n        void ensure(std::size_t n) {\n            if (_h.size() <\
    \ n) _h.resize(n);\n        }\n    };\n} // namespace suisen\n\n\n\n#line 8 \"\
    test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint& a) {\n    out << a.val();\n    return\
    \ out;\n}\n\nnamespace suisen {\n    template <typename mint>\n    std::vector<mint>\
    \ exp(const std::vector<mint>& f) {\n        inv_mods<mint> invs;\n        const\
    \ int n = f.size();\n        std::vector<mint> df(n - 1);\n        for (int i\
    \ = 1; i < n; ++i) {\n            df[i - 1] = i * f[i];\n        }\n        SemiRelaxedConvolutionNTT<mint>\
    \ df_g(df);\n        std::vector<mint> g(n);\n        g[0] = 1;\n        for (int\
    \ i = 1; i < n; ++i) {\n            g[i] = df_g.append(g[i - 1]) * invs[i];\n\
    \        }\n        return g;\n    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<mint>\
    \ f(n);\n    for (auto &e : f) std::cin >> e;\n\n    std::vector<mint> exp_f =\
    \ suisen::exp(f);\n    for (int i = 0; i < n; ++i) {\n        std::cout << exp_f[i]\
    \ << \" \\n\"[i == n - 1];\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_formal_power_series\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/math/inv_mods.hpp\"\
    \n#include \"library/convolution/semi_relaxed_convolution_ntt.hpp\"\n\nusing mint\
    \ = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream& in, mint&\
    \ a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream&\
    \ out, const mint& a) {\n    out << a.val();\n    return out;\n}\n\nnamespace\
    \ suisen {\n    template <typename mint>\n    std::vector<mint> exp(const std::vector<mint>&\
    \ f) {\n        inv_mods<mint> invs;\n        const int n = f.size();\n      \
    \  std::vector<mint> df(n - 1);\n        for (int i = 1; i < n; ++i) {\n     \
    \       df[i - 1] = i * f[i];\n        }\n        SemiRelaxedConvolutionNTT<mint>\
    \ df_g(df);\n        std::vector<mint> g(n);\n        g[0] = 1;\n        for (int\
    \ i = 1; i < n; ++i) {\n            g[i] = df_g.append(g[i - 1]) * invs[i];\n\
    \        }\n        return g;\n    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<mint>\
    \ f(n);\n    for (auto &e : f) std::cin >> e;\n\n    std::vector<mint> exp_f =\
    \ suisen::exp(f);\n    for (int i = 0; i < n; ++i) {\n        std::cout << exp_f[i]\
    \ << \" \\n\"[i == n - 1];\n    }\n}"
  dependsOn:
  - library/math/inv_mods.hpp
  - library/convolution/semi_relaxed_convolution_ntt.hpp
  isVerificationFile: true
  path: test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp
- /verify/test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp.html
title: test/src/convolution/semi_relaxed_convolution_ntt/exp_of_formal_power_series.test.cpp
---
