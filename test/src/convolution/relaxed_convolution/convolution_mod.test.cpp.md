---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/relaxed_convolution.hpp
    title: library/convolution/relaxed_convolution.hpp
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
  bundledCode: "#line 1 \"test/src/convolution/relaxed_convolution/convolution_mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\n\
    using mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint& a) {\n    out << a.val();\n    return\
    \ out;\n}\n\n#line 1 \"library/convolution/relaxed_convolution.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
    \    template <typename T>\n    struct RelaxedConvolution {\n        using value_type\
    \ = T;\n        using polynomial_type = std::vector<value_type>;\n        using\
    \ convolution_type = polynomial_type(*)(const polynomial_type&, const polynomial_type&);\n\
    \n        RelaxedConvolution() = default;\n        RelaxedConvolution(const convolution_type\
    \ &convolve) : _convolve(convolve), _n(0), _f{}, _g{}, _h{} {}\n\n        void\
    \ set_convolve_function(const convolution_type &convolve) {\n            _convolve\
    \ = convolve;\n        }\n\n        value_type append(const value_type &fi, const\
    \ value_type &gi) {\n            ++_n;\n            _f.push_back(fi), _g.push_back(gi);\n\
    \            for (int p = 1;; p <<= 1) {\n                int l1 = _n - p, r1\
    \ = _n, l2 = p - 1, r2 = l2 + p;\n                add(l1 + l2, range_convolve(l1,\
    \ r1, l2, r2));\n                if (l1 == l2) break;\n                add(l1\
    \ + l2, range_convolve(l2, r2, l1, r1));\n                if (not (_n & p)) break;\n\
    \            }\n            return _h[_n - 1];\n        }\n\n        const value_type&\
    \ operator[](int i) const {\n            return _h[i];\n        }\n        polynomial_type\
    \ get() const {\n            return _h;\n        }\n\n    private:\n        convolution_type\
    \ _convolve = [](const polynomial_type&, const polynomial_type&) -> polynomial_type\
    \ { assert(false); };\n        int _n;\n        polynomial_type _f, _g, _h;\n\n\
    \        polynomial_type range_convolve(int l1, int r1, int l2, int r2) {\n  \
    \          return _convolve(polynomial_type(_f.begin() + l1, _f.begin() + r1),\
    \ polynomial_type(_g.begin() + l2, _g.begin() + r2));\n        }\n\n        void\
    \ add(std::size_t bias, const polynomial_type &h) {\n            if (_h.size()\
    \ < bias + h.size()) _h.resize(bias + h.size());\n            for (std::size_t\
    \ i = 0; i < h.size(); ++i) _h[bias + i] += h[i];\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n#line 21 \"test/src/convolution/relaxed_convolution/convolution_mod.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::size_t n, m;\n    std::cin >> n >> m;\n\n    std::vector<mint> a(n),\
    \ b(m);\n    for (auto& e : a) std::cin >> e;\n    for (auto& e : b) std::cin\
    \ >> e;\n\n    suisen::RelaxedConvolution<mint> conv{ [](const auto& a, const\
    \ auto& b) { return atcoder::convolution(a, b); } };\n\n    for (std::size_t i\
    \ = 0; i < n + m - 1; ++i) {\n        conv.append(i < a.size() ? a[i] : 0, i <\
    \ b.size() ? b[i] : 0);\n    }\n    auto c = conv.get();\n    for (std::size_t\
    \ i = 0; i < n + m - 1; ++i) {\n        std::cout << c[i] << \" \\n\"[i == n +\
    \ m - 2];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\n\
    using mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint& a) {\n    out << a.val();\n    return\
    \ out;\n}\n\n#include \"library/convolution/relaxed_convolution.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ std::size_t n, m;\n    std::cin >> n >> m;\n\n    std::vector<mint> a(n), b(m);\n\
    \    for (auto& e : a) std::cin >> e;\n    for (auto& e : b) std::cin >> e;\n\n\
    \    suisen::RelaxedConvolution<mint> conv{ [](const auto& a, const auto& b) {\
    \ return atcoder::convolution(a, b); } };\n\n    for (std::size_t i = 0; i < n\
    \ + m - 1; ++i) {\n        conv.append(i < a.size() ? a[i] : 0, i < b.size() ?\
    \ b[i] : 0);\n    }\n    auto c = conv.get();\n    for (std::size_t i = 0; i <\
    \ n + m - 1; ++i) {\n        std::cout << c[i] << \" \\n\"[i == n + m - 2];\n\
    \    }\n    return 0;\n}"
  dependsOn:
  - library/convolution/relaxed_convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/relaxed_convolution/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2022-06-07 17:31:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/relaxed_convolution/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/relaxed_convolution/convolution_mod.test.cpp
- /verify/test/src/convolution/relaxed_convolution/convolution_mod.test.cpp.html
title: test/src/convolution/relaxed_convolution/convolution_mod.test.cpp
---
