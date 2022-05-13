---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/vec_sparse_fps.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename IndexType, typename ValueType, std::enable_if_t<std::is_integral_v<IndexType>,\
    \ std::nullptr_t> = nullptr>\n    struct VecSparseFPS {\n        using index_type\
    \ = IndexType;\n        using value_type = ValueType;\n\n        using convolution_t\
    \ = std::vector<value_type> (*)(const std::vector<value_type> &, const std::vector<value_type>\
    \ &);\n\n        VecSparseFPS() {}\n        template <typename IT, typename VT>\n\
    \        VecSparseFPS(std::vector<std::pair<IT, VT>> data, bool sorted = false)\
    \ {\n            if (not sorted) std::sort(data.begin(), data.end(), [](auto &p1,\
    \ auto &p2) { return p1.first < p2.first; });\n            for (const auto &[i,\
    \ v] : data) add_to_last(i, v);\n        }\n\n        static void set_multiplication(convolution_t\
    \ multiplication) {\n            VecSparseFPS<index_type, value_type>::mult =\
    \ multiplication;\n        }\n\n        value_type operator[](index_type i) {\n\
    \            auto it = std::upper_bound(_f.begin(), _f.end(), i, [](index_type\
    \ i, const auto& p) { return i < p.first; });\n            if (it == _f.begin())\
    \ return 0;\n            const auto &[j, p] = *--it;\n            return i - j\
    \ < int(p.size()) ? p[i - j] : value_type(0);\n        }\n\n        VecSparseFPS\
    \ operator-() const {\n            VecSparseFPS res;\n            for (const auto\
    \ &[i, f] : _f) {\n                auto &back = res._f.emplace_back(i, {});\n\
    \                for (const auto &v : f) back.second.push_back(-v);\n        \
    \    }\n            return res;\n        }\n        friend VecSparseFPS operator+(const\
    \ VecSparseFPS &f, const VecSparseFPS &g) {\n            const int n = f._f.size(),\
    \ m = g._f.size();\n            VecSparseFPS h;\n            for (int i = 0, j\
    \ = 0; i < n and j < m;) {\n                if (j == m or (i < n and f._f[i].first\
    \ < g._f[j].first)) {\n                    h.add_to_last(f._f[i++]);\n       \
    \         } else {\n                    h.add_to_last(g._f[j++]);\n          \
    \      }\n            }\n            return h;\n        }\n        friend VecSparseFPS\
    \ operator-(const VecSparseFPS &f, const VecSparseFPS &g) {\n            return\
    \ f + -g;\n        }\n        friend VecSparseFPS operator*(const VecSparseFPS\
    \ &f, const VecSparseFPS &g) {\n            std::vector<std::pair<index_type,\
    \ std::vector<value_type>>> data;\n            for (const auto &[i, a] : f._f)\
    \ for (const auto &[j, b] : g._f) {\n                data.emplace_back(i + j,\
    \ VecSparseFPS<index_type, value_type>::mult(a, b));\n            }\n        \
    \    std::sort(data.begin(), data.end(), [](auto &p1, auto &p2) { return p1.first\
    \ < p2.first; });\n            VecSparseFPS h;\n            for (auto &[i, a]\
    \ : data) {\n                h.add_to_last(i, std::move(a));\n            }\n\
    \            return h;\n        }\n        friend VecSparseFPS operator*(const\
    \ VecSparseFPS &f, const std::vector<value_type> &g) {\n            VecSparseFPS\
    \ h;\n            for (const auto &[i, a] : f._f) h.add_to_last({ i, VecSparseFPS<index_type,\
    \ value_type>::mult(a, g) });\n            return h;\n        }\n        friend\
    \ VecSparseFPS operator*(const std::vector<value_type> &f, const VecSparseFPS\
    \ &g) {\n            return g * f;\n        }\n\n        auto begin() { return\
    \ _f.begin(); }\n        auto end() { return _f.end(); }\n\n        void clear()\
    \ { _f.clear(); }\n\n        void add_to_last(index_type i, const value_type &v)\
    \ {\n            if (_f.size()) {\n                auto &[j, p] = _f.back();\n\
    \                assert(j <= i);\n                int d = p.size();\n        \
    \        if (j + d == i) {\n                    p.push_back(v);\n            \
    \        return;\n                } else if (j + d > i) {\n                  \
    \  p[i - j] += v;\n                    return;\n                }\n          \
    \  }\n            _f.emplace_back(i, std::vector<value_type> { v });\n       \
    \ }\n\n        void add_to_last(const std::pair<index_type, std::vector<value_type>>\
    \ &ig) {\n            const auto &[i, g] = ig;\n            if (_f.size()) {\n\
    \                auto &[j, p] = _f.back();\n                assert(j <= i);\n\
    \                int pd = p.size();\n                if (j + pd >= i) {\n    \
    \                int gd = g.size();\n                    int offset = i - j;\n\
    \                    p.resize(std::max(pd, offset + gd));\n                  \
    \  for (int k = 0; k < gd; ++k) p[offset + k] += g[k];\n                    return;\n\
    \                }\n            }\n            _f.push_back(ig);\n        }\n\n\
    \        static value_type bostan_mori(VecSparseFPS P, std::vector<value_type>\
    \ Q, long long m) {\n            for (; m; m >>= 1) {\n                std::vector<mint>\
    \ mQ = Q;\n                for (int i = 1; i < int(Q.size()); i += 2) mQ[i] =\
    \ -mQ[i];\n                auto nP = P * mQ;\n                P.clear();\n   \
    \             for (auto &[i, f] : nP) {\n                    int sz = f.size();\n\
    \                    for (int k = (i % 2 != m % 2); k < sz; k += 2) P.add_to_last((i\
    \ + k) >> 1, f[k]);\n                }\n                auto nQ = VecSparseFPS<index_type,\
    \ value_type>::mult(Q, mQ);\n                Q.clear();\n                for (int\
    \ i = 0; i < int(nQ.size()); i += 2) Q.push_back(nQ[i]);\n            }\n    \
    \        return P[0];\n        }\n\n    private:\n        static inline convolution_t\
    \ mult = [](const auto &, const auto &) {\n            std::cerr << \"convolution\
    \ function is not available.\" << std::endl;\n            assert(false);\n   \
    \         return std::vector<value_type>{};\n        };\n\n        std::vector<std::pair<index_type,\
    \ std::vector<value_type>>> _f;\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_VEC_SPARSE_FPS\n#define SUISEN_VEC_SPARSE_FPS\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename IndexType, typename ValueType, std::enable_if_t<std::is_integral_v<IndexType>,\
    \ std::nullptr_t> = nullptr>\n    struct VecSparseFPS {\n        using index_type\
    \ = IndexType;\n        using value_type = ValueType;\n\n        using convolution_t\
    \ = std::vector<value_type> (*)(const std::vector<value_type> &, const std::vector<value_type>\
    \ &);\n\n        VecSparseFPS() {}\n        template <typename IT, typename VT>\n\
    \        VecSparseFPS(std::vector<std::pair<IT, VT>> data, bool sorted = false)\
    \ {\n            if (not sorted) std::sort(data.begin(), data.end(), [](auto &p1,\
    \ auto &p2) { return p1.first < p2.first; });\n            for (const auto &[i,\
    \ v] : data) add_to_last(i, v);\n        }\n\n        static void set_multiplication(convolution_t\
    \ multiplication) {\n            VecSparseFPS<index_type, value_type>::mult =\
    \ multiplication;\n        }\n\n        value_type operator[](index_type i) {\n\
    \            auto it = std::upper_bound(_f.begin(), _f.end(), i, [](index_type\
    \ i, const auto& p) { return i < p.first; });\n            if (it == _f.begin())\
    \ return 0;\n            const auto &[j, p] = *--it;\n            return i - j\
    \ < int(p.size()) ? p[i - j] : value_type(0);\n        }\n\n        VecSparseFPS\
    \ operator-() const {\n            VecSparseFPS res;\n            for (const auto\
    \ &[i, f] : _f) {\n                auto &back = res._f.emplace_back(i, {});\n\
    \                for (const auto &v : f) back.second.push_back(-v);\n        \
    \    }\n            return res;\n        }\n        friend VecSparseFPS operator+(const\
    \ VecSparseFPS &f, const VecSparseFPS &g) {\n            const int n = f._f.size(),\
    \ m = g._f.size();\n            VecSparseFPS h;\n            for (int i = 0, j\
    \ = 0; i < n and j < m;) {\n                if (j == m or (i < n and f._f[i].first\
    \ < g._f[j].first)) {\n                    h.add_to_last(f._f[i++]);\n       \
    \         } else {\n                    h.add_to_last(g._f[j++]);\n          \
    \      }\n            }\n            return h;\n        }\n        friend VecSparseFPS\
    \ operator-(const VecSparseFPS &f, const VecSparseFPS &g) {\n            return\
    \ f + -g;\n        }\n        friend VecSparseFPS operator*(const VecSparseFPS\
    \ &f, const VecSparseFPS &g) {\n            std::vector<std::pair<index_type,\
    \ std::vector<value_type>>> data;\n            for (const auto &[i, a] : f._f)\
    \ for (const auto &[j, b] : g._f) {\n                data.emplace_back(i + j,\
    \ VecSparseFPS<index_type, value_type>::mult(a, b));\n            }\n        \
    \    std::sort(data.begin(), data.end(), [](auto &p1, auto &p2) { return p1.first\
    \ < p2.first; });\n            VecSparseFPS h;\n            for (auto &[i, a]\
    \ : data) {\n                h.add_to_last(i, std::move(a));\n            }\n\
    \            return h;\n        }\n        friend VecSparseFPS operator*(const\
    \ VecSparseFPS &f, const std::vector<value_type> &g) {\n            VecSparseFPS\
    \ h;\n            for (const auto &[i, a] : f._f) h.add_to_last({ i, VecSparseFPS<index_type,\
    \ value_type>::mult(a, g) });\n            return h;\n        }\n        friend\
    \ VecSparseFPS operator*(const std::vector<value_type> &f, const VecSparseFPS\
    \ &g) {\n            return g * f;\n        }\n\n        auto begin() { return\
    \ _f.begin(); }\n        auto end() { return _f.end(); }\n\n        void clear()\
    \ { _f.clear(); }\n\n        void add_to_last(index_type i, const value_type &v)\
    \ {\n            if (_f.size()) {\n                auto &[j, p] = _f.back();\n\
    \                assert(j <= i);\n                int d = p.size();\n        \
    \        if (j + d == i) {\n                    p.push_back(v);\n            \
    \        return;\n                } else if (j + d > i) {\n                  \
    \  p[i - j] += v;\n                    return;\n                }\n          \
    \  }\n            _f.emplace_back(i, std::vector<value_type> { v });\n       \
    \ }\n\n        void add_to_last(const std::pair<index_type, std::vector<value_type>>\
    \ &ig) {\n            const auto &[i, g] = ig;\n            if (_f.size()) {\n\
    \                auto &[j, p] = _f.back();\n                assert(j <= i);\n\
    \                int pd = p.size();\n                if (j + pd >= i) {\n    \
    \                int gd = g.size();\n                    int offset = i - j;\n\
    \                    p.resize(std::max(pd, offset + gd));\n                  \
    \  for (int k = 0; k < gd; ++k) p[offset + k] += g[k];\n                    return;\n\
    \                }\n            }\n            _f.push_back(ig);\n        }\n\n\
    \        static value_type bostan_mori(VecSparseFPS P, std::vector<value_type>\
    \ Q, long long m) {\n            for (; m; m >>= 1) {\n                std::vector<mint>\
    \ mQ = Q;\n                for (int i = 1; i < int(Q.size()); i += 2) mQ[i] =\
    \ -mQ[i];\n                auto nP = P * mQ;\n                P.clear();\n   \
    \             for (auto &[i, f] : nP) {\n                    int sz = f.size();\n\
    \                    for (int k = (i % 2 != m % 2); k < sz; k += 2) P.add_to_last((i\
    \ + k) >> 1, f[k]);\n                }\n                auto nQ = VecSparseFPS<index_type,\
    \ value_type>::mult(Q, mQ);\n                Q.clear();\n                for (int\
    \ i = 0; i < int(nQ.size()); i += 2) Q.push_back(nQ[i]);\n            }\n    \
    \        return P[0];\n        }\n\n    private:\n        static inline convolution_t\
    \ mult = [](const auto &, const auto &) {\n            std::cerr << \"convolution\
    \ function is not available.\" << std::endl;\n            assert(false);\n   \
    \         return std::vector<value_type>{};\n        };\n\n        std::vector<std::pair<index_type,\
    \ std::vector<value_type>>> _f;\n    };\n} // namespace suisen\n\n#endif // SUISEN_VEC_SPARSE_FPS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/vec_sparse_fps.hpp
  requiredBy: []
  timestamp: '2022-05-14 03:01:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/polynomial/vec_sparse_fps.hpp
layout: document
title: Vec Sparse Fps
---
## Vec Sparse Fps