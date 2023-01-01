---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
    title: test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/semi_relaxed_convolution/convolution_mod.test.cpp
    title: test/src/convolution/semi_relaxed_convolution/convolution_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
  bundledCode: "#line 1 \"library/convolution/semi_relaxed_convolution.hpp\"\n\n\n\
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
    \ + i] += h[i];\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_SEMI_RELAXED_CONVOLUTION\n#define SUISEN_SEMI_RELAXED_CONVOLUTION\n\
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
    \ + i] += h[i];\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_SEMI_RELAXED_CONVOLUTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/semi_relaxed_convolution.hpp
  requiredBy: []
  timestamp: '2022-06-07 17:31:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/semi_relaxed_convolution/convolution_mod.test.cpp
  - test/src/convolution/semi_relaxed_convolution/abc213_h.test.cpp
documentation_of: library/convolution/semi_relaxed_convolution.hpp
layout: document
title: Semi Relaxed Convolution
---
## Semi Relaxed Convolution

[オンライン畳み込み](https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c) に詳しい．
