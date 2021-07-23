---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/compressed_wavelet_matrix.hpp
    title: library/datastructure/compressed_wavelet_matrix.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/coordinate_compressor.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\ntemplate\
    \ <typename T>\nclass coordinate_compressor {\n    public:\n        explicit coordinate_compressor()\
    \ noexcept {}\n\n        void reserve(int n) { _xs.reserve(n); }\n    \n     \
    \   void push(const T  &first) { _xs.push_back(first), _built = false; }\n   \
    \     void push(const T &&first) { _xs.push_back(first), _built = false; }\n \
    \       template <typename Iterator>\n        auto push(const Iterator first,\
    \ const Iterator last) -> decltype(std::vector<T>{}.push_back(*first), void())\
    \ {\n            for (auto it = first; it != last; ++it) _xs.push_back(*it);\n\
    \            _built = false;\n        }\n        template <typename Iterable>\n\
    \        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()),\
    \ void()) {\n            push(iterable.begin(), iterable.end());\n        }\n\
    \        template <typename ...Args>\n        void emplace(Args  &...args) { _xs.emplace_back(std::forward<Args>(args)...),\
    \ _built = false; }\n        template <typename ...Args>\n        void emplace(Args\
    \ &&...args) { _xs.emplace_back(std::forward<Args>(args)...), _built = false;\
    \ }\n    \n        void build() {\n            std::sort(_xs.begin(), _xs.end());\n\
    \            _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());\n    \
    \        _built = true;\n        }\n    \n        inline int size() const {\n\
    \            assert(_built);\n            return _xs.size();\n        }\n    \
    \    inline int comp(const T e, int default_value = -1) const {\n            const\
    \ int res = lower_bound(e);\n            return res < int(_xs.size()) and _xs[res]\
    \ == e ? res : default_value;\n        }\n        inline T decomp(const int compressed)\
    \ const {\n            assert(_built);\n            return _xs[compressed];\n\
    \        }\n        inline int operator[](const T e) const {\n            return\
    \ comp(e);\n        }\n        inline int lower_bound(const T e) const {\n   \
    \         assert(_built);\n            return std::lower_bound(_xs.begin(), _xs.end(),\
    \ e) - _xs.begin();\n        }\n        inline int upper_bound(const T e) const\
    \ {\n            assert(_built);\n            return std::upper_bound(_xs.begin(),\
    \ _xs.end(), e) - _xs.begin();\n        }\n        inline bool has_key(const T\
    \ e) const {\n            assert(_built);\n            int index = lower_bound(e);\n\
    \            return index < size() and _xs[index] == e;\n        }\n    private:\n\
    \        std::vector<T> _xs;\n        bool _built = true;\n};\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_COORDINATE_COMPRESSOR\n#define SUISEN_COORDINATE_COMPRESSOR\n\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace suisen\
    \ {\ntemplate <typename T>\nclass coordinate_compressor {\n    public:\n     \
    \   explicit coordinate_compressor() noexcept {}\n\n        void reserve(int n)\
    \ { _xs.reserve(n); }\n    \n        void push(const T  &first) { _xs.push_back(first),\
    \ _built = false; }\n        void push(const T &&first) { _xs.push_back(first),\
    \ _built = false; }\n        template <typename Iterator>\n        auto push(const\
    \ Iterator first, const Iterator last) -> decltype(std::vector<T>{}.push_back(*first),\
    \ void()) {\n            for (auto it = first; it != last; ++it) _xs.push_back(*it);\n\
    \            _built = false;\n        }\n        template <typename Iterable>\n\
    \        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()),\
    \ void()) {\n            push(iterable.begin(), iterable.end());\n        }\n\
    \        template <typename ...Args>\n        void emplace(Args  &...args) { _xs.emplace_back(std::forward<Args>(args)...),\
    \ _built = false; }\n        template <typename ...Args>\n        void emplace(Args\
    \ &&...args) { _xs.emplace_back(std::forward<Args>(args)...), _built = false;\
    \ }\n    \n        void build() {\n            std::sort(_xs.begin(), _xs.end());\n\
    \            _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());\n    \
    \        _built = true;\n        }\n    \n        inline int size() const {\n\
    \            assert(_built);\n            return _xs.size();\n        }\n    \
    \    inline int comp(const T e, int default_value = -1) const {\n            const\
    \ int res = lower_bound(e);\n            return res < int(_xs.size()) and _xs[res]\
    \ == e ? res : default_value;\n        }\n        inline T decomp(const int compressed)\
    \ const {\n            assert(_built);\n            return _xs[compressed];\n\
    \        }\n        inline int operator[](const T e) const {\n            return\
    \ comp(e);\n        }\n        inline int lower_bound(const T e) const {\n   \
    \         assert(_built);\n            return std::lower_bound(_xs.begin(), _xs.end(),\
    \ e) - _xs.begin();\n        }\n        inline int upper_bound(const T e) const\
    \ {\n            assert(_built);\n            return std::upper_bound(_xs.begin(),\
    \ _xs.end(), e) - _xs.begin();\n        }\n        inline bool has_key(const T\
    \ e) const {\n            assert(_built);\n            int index = lower_bound(e);\n\
    \            return index < size() and _xs[index] == e;\n        }\n    private:\n\
    \        std::vector<T> _xs;\n        bool _built = true;\n};\n} // namespace\
    \ suisen\n\n#endif // SUISEN_COORDINATE_COMPRESSOR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/coordinate_compressor.hpp
  requiredBy:
  - library/datastructure/compressed_wavelet_matrix.hpp
  timestamp: '2021-07-23 21:54:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
documentation_of: library/util/coordinate_compressor.hpp
layout: document
redirect_from:
- /library/library/util/coordinate_compressor.hpp
- /library/library/util/coordinate_compressor.hpp.html
title: library/util/coordinate_compressor.hpp
---
