---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/semi_relaxed_convolution_ntt.hpp
    title: Semi Relaxed Convolution Ntt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\n\
    using mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint& a) {\n    out << a.val();\n    return\
    \ out;\n}\n\n#line 1 \"library/convolution/semi_relaxed_convolution_ntt.hpp\"\n\
    \n\n\n#line 5 \"library/convolution/semi_relaxed_convolution_ntt.hpp\"\n\nnamespace\
    \ suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
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
    \ n) _h.resize(n);\n        }\n    };\n} // namespace suisen\n\n\n\n#line 21 \"\
    test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp\"\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::size_t n, m;\n    std::cin >> n >> m;\n\n    std::vector<mint> a(n),\
    \ b(m);\n    for (auto& e : a) std::cin >> e;\n    for (auto& e : b) std::cin\
    \ >> e;\n\n    suisen::SemiRelaxedConvolutionNTT<mint> conv(a);\n\n    for (std::size_t\
    \ i = 0; i < n + m - 1; ++i) {\n        conv.append(i < b.size() ? b[i] : 0);\n\
    \    }\n    auto c = conv.get();\n    for (std::size_t i = 0; i < n + m - 1; ++i)\
    \ {\n        std::cout << c[i] << \" \\n\"[i == n + m - 2];\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\n\
    using mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint& a) {\n    out << a.val();\n    return\
    \ out;\n}\n\n#include \"library/convolution/semi_relaxed_convolution_ntt.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::size_t n, m;\n    std::cin >> n >> m;\n\n    std::vector<mint> a(n),\
    \ b(m);\n    for (auto& e : a) std::cin >> e;\n    for (auto& e : b) std::cin\
    \ >> e;\n\n    suisen::SemiRelaxedConvolutionNTT<mint> conv(a);\n\n    for (std::size_t\
    \ i = 0; i < n + m - 1; ++i) {\n        conv.append(i < b.size() ? b[i] : 0);\n\
    \    }\n    auto c = conv.get();\n    for (std::size_t i = 0; i < n + m - 1; ++i)\
    \ {\n        std::cout << c[i] << \" \\n\"[i == n + m - 2];\n    }\n    return\
    \ 0;\n}"
  dependsOn:
  - library/convolution/semi_relaxed_convolution_ntt.hpp
  isVerificationFile: true
  path: test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp
- /verify/test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp.html
title: test/src/convolution/semi_relaxed_convolution_ntt/convolution_mod.test.cpp
---
