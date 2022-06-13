---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/semi_relaxed_convolution.hpp
    title: Semi Relaxed Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc213/tasks/abc213_h
    links:
    - https://atcoder.jp/contests/abc213/tasks/abc213_h
  bundledCode: "#line 1 \"test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc213/tasks/abc213_h\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\
    \nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\n#line 1 \"library/convolution/semi_relaxed_convolution.hpp\"\n\n\n\
    \n#include <vector>\n\nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
    \    template <typename T>\n    struct SemiRelaxedConvolution {\n        using\
    \ value_type = T;\n        using polynomial_type = std::vector<value_type>;\n\
    \        using convolution_type = polynomial_type(*)(const polynomial_type&, const\
    \ polynomial_type&);\n\n        SemiRelaxedConvolution() = default;\n        SemiRelaxedConvolution(const\
    \ polynomial_type &f) : _n(0), _f(f) {}\n        SemiRelaxedConvolution(const\
    \ polynomial_type &f, const convolution_type &convolve) : _convolve(convolve),\
    \ _n(0), _f(f), _g{}, _h{} {}\n\n        void set_convolve_function(const convolution_type\
    \ &convolve) {\n            _convolve = convolve;\n        }\n\n        value_type\
    \ append(const value_type &gi) {\n            ++_n;\n            _g.push_back(gi);\n\
    \            for (int p = 1;; p <<= 1) {\n                int l1 = p - 1, r1 =\
    \ l1 + p, l2 = _n - p, r2 = _n;\n                add(l1 + l2, range_convolve(l1,\
    \ r1, l2, r2));\n                if (p == (-_n & _n)) break;\n            }\n\
    \            return _h[_n - 1];\n        }\n\n        const value_type& operator[](int\
    \ i) const {\n            return _h[i];\n        }\n        polynomial_type get()\
    \ const {\n            return _h;\n        }\n\n    private:\n        convolution_type\
    \ _convolve = [](const polynomial_type&, const polynomial_type&) -> polynomial_type\
    \ { assert(false); };\n        int _n;\n        polynomial_type _f, _g, _h;\n\n\
    \        polynomial_type range_convolve(int l1, int r1, int l2, int r2) {\n  \
    \          r1 = std::min(r1, int(_f.size())), l1 = std::min(l1, r1);\n       \
    \     return _convolve(polynomial_type(_f.begin() + l1, _f.begin() + r1), polynomial_type(_g.begin()\
    \ + l2, _g.begin() + r2));\n        }\n\n        void add(std::size_t bias, const\
    \ polynomial_type &h) {\n            if (_h.size() < bias + h.size()) _h.resize(bias\
    \ + h.size());\n            for (std::size_t i = 0; i < h.size(); ++i) _h[bias\
    \ + i] += h[i];\n        }\n    };\n} // namespace suisen\n\n\n\n#line 22 \"test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp\"\
    \nusing suisen::SemiRelaxedConvolution;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m, t;\n    std::cin >> n >> m >> t;\n\
    \n    std::vector<std::vector<std::pair<int, SemiRelaxedConvolution<mint>>>> p(n);\n\
    \    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin >> u >>\
    \ v;\n        --u, --v;\n\n        std::vector<mint> l(t);\n        for (auto\
    \ &e : l) std::cin >> e;\n\n        SemiRelaxedConvolution<mint> conv { l, [](const\
    \ auto &a, const auto &b) { return atcoder::convolution(a, b); } };\n        p[u].emplace_back(v,\
    \ conv);\n        p[v].emplace_back(u, conv);\n    }\n\n    std::vector<std::vector<mint>>\
    \ f(n, std::vector<mint>(t + 1, 0));\n    f[0][0] = 1;\n\n    for (int i = 0;\
    \ i < t; ++i) {\n        for (int u = 0; u < n; ++u) for (auto &[v, conv] : p[u])\
    \ {\n            f[u][i + 1] += conv.append(f[v][i]);\n        }\n    }\n\n  \
    \  std::cout << f[0][t].val() << std::endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc213/tasks/abc213_h\"\n\n\
    #include <iostream>\n#include <tuple>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\
    \nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\n#include \"library/convolution/semi_relaxed_convolution.hpp\"\nusing\
    \ suisen::SemiRelaxedConvolution;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m, t;\n    std::cin >> n >> m >> t;\n\
    \n    std::vector<std::vector<std::pair<int, SemiRelaxedConvolution<mint>>>> p(n);\n\
    \    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin >> u >>\
    \ v;\n        --u, --v;\n\n        std::vector<mint> l(t);\n        for (auto\
    \ &e : l) std::cin >> e;\n\n        SemiRelaxedConvolution<mint> conv { l, [](const\
    \ auto &a, const auto &b) { return atcoder::convolution(a, b); } };\n        p[u].emplace_back(v,\
    \ conv);\n        p[v].emplace_back(u, conv);\n    }\n\n    std::vector<std::vector<mint>>\
    \ f(n, std::vector<mint>(t + 1, 0));\n    f[0][0] = 1;\n\n    for (int i = 0;\
    \ i < t; ++i) {\n        for (int u = 0; u < n; ++u) for (auto &[v, conv] : p[u])\
    \ {\n            f[u][i + 1] += conv.append(f[v][i]);\n        }\n    }\n\n  \
    \  std::cout << f[0][t].val() << std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/convolution/semi_relaxed_convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
  requiredBy: []
  timestamp: '2022-06-07 17:31:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
- /verify/test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp.html
title: test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
---
