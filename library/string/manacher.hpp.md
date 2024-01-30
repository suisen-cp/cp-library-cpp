---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/manacher/enumerate_palindromes.test.cpp
    title: test/src/string/manacher/enumerate_palindromes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/manacher.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    struct Manacher {\n        Manacher() = default;\n \
    \       template <typename Container>\n        Manacher(const Container& container,\
    \ const typename Container::value_type& dummy) : _n(container.size()), _r(2 *\
    \ _n + 1) {\n            std::vector v{ dummy };\n            for (const auto&\
    \ val : container) v.push_back(val), v.push_back(dummy);\n            build(v);\n\
    \        }\n\n        int operator[](int i) const { return _r[i]; }\n        int\
    \ odd_length(int i) const { return _r[2 * i + 1]; }\n        int even_length(int\
    \ i) const { return _r[2 * i]; }\n    private:\n        int _n;\n        std::vector<int>\
    \ _r;\n\n        template <typename T>\n        void build(const std::vector<T>&\
    \ v) {\n            for (int i = 0, j = 0, siz = v.size(); i < siz;) {\n     \
    \           while (i - j >= 0 and i + j < siz and v[i - j] == v[i + j]) ++j;\n\
    \                _r[i] = j;\n                int k = 1;\n                while\
    \ (i - k >= 0 and k + _r[i - k] < j) _r[i + k] = _r[i - k], ++k;\n           \
    \     i += k, j -= k;\n            }\n            for (int& r : _r) --r;\n   \
    \     }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MANACHER\n#define SUISEN_MANACHER\n\n#include <vector>\n\n\
    namespace suisen {\n    struct Manacher {\n        Manacher() = default;\n   \
    \     template <typename Container>\n        Manacher(const Container& container,\
    \ const typename Container::value_type& dummy) : _n(container.size()), _r(2 *\
    \ _n + 1) {\n            std::vector v{ dummy };\n            for (const auto&\
    \ val : container) v.push_back(val), v.push_back(dummy);\n            build(v);\n\
    \        }\n\n        int operator[](int i) const { return _r[i]; }\n        int\
    \ odd_length(int i) const { return _r[2 * i + 1]; }\n        int even_length(int\
    \ i) const { return _r[2 * i]; }\n    private:\n        int _n;\n        std::vector<int>\
    \ _r;\n\n        template <typename T>\n        void build(const std::vector<T>&\
    \ v) {\n            for (int i = 0, j = 0, siz = v.size(); i < siz;) {\n     \
    \           while (i - j >= 0 and i + j < siz and v[i - j] == v[i + j]) ++j;\n\
    \                _r[i] = j;\n                int k = 1;\n                while\
    \ (i - k >= 0 and k + _r[i - k] < j) _r[i + k] = _r[i - k], ++k;\n           \
    \     i += k, j -= k;\n            }\n            for (int& r : _r) --r;\n   \
    \     }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_MANACHER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/manacher.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/manacher/enumerate_palindromes.test.cpp
documentation_of: library/string/manacher.hpp
layout: document
title: Manacher
---
## Manacher