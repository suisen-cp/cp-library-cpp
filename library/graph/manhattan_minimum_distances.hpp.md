---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
    title: Fenwick Tree Prefix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/manhattan_minimum_distances.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <limits>\n#include <numeric>\n#include <vector>\n\
    \n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp\"\n\n\n\
    \n#line 5 \"library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n    struct FenwickTreePrefix\
    \ {\n        FenwickTreePrefix() : FenwickTreePrefix(0) {}\n        explicit FenwickTreePrefix(int\
    \ n) : _n(n), _dat(_n + 1, e()) {}\n        FenwickTreePrefix(const std::vector<T>\
    \ &dat) : _n(dat.size()), _dat(_n + 1, e()) {\n            for (int i = _n; i\
    \ > 0; --i) {\n                _dat[i] = op(_dat[i], dat[i - 1]);\n          \
    \      if (int p = i + (-i & i); p <= _n) _dat[p] = op(_dat[p], _dat[i]);\n  \
    \          }\n        }\n        void apply(int i, const T& val) {\n         \
    \   for (++i; i <= _n; i += -i & i) _dat[i] = op(_dat[i], val);\n        }\n \
    \       T prefix_query(int r) const {\n            T res = e();\n            for\
    \ (; r; r -= -r & r) res = op(res, _dat[r]);\n            return res;\n      \
    \  }\n    private:\n        int _n;\n        std::vector<T> _dat;\n    };\n} //\
    \ namespace suisen\n\n\n\n#line 10 \"library/graph/manhattan_minimum_distances.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::manhattan_minimum_distances {\n\
    \        template <typename T>\n        T op(T x, T y) { return std::max(x, y);\
    \ };\n        template <typename T>\n        T e() { return std::numeric_limits<T>::min();\
    \ };\n        template <typename T>\n        using PrefixMaxQuery = FenwickTreePrefix<T,\
    \ op<T>, e<T>>;\n    } // namespace internal::manhattan_minimum_distances\n\n\
    \    template <typename T>\n    std::vector<T> manhattan_minimum_distances(std::vector<std::pair<T,\
    \ T>> points) {\n        using namespace internal::manhattan_minimum_distances;\n\
    \n        const int n = points.size();\n        std::vector<int> p(n);\n     \
    \   std::iota(p.begin(), p.end(), 0);\n\n        std::vector<T> res(n, std::numeric_limits<T>::max());\n\
    \n        auto sweep = [&] {\n            std::sort(\n                p.begin(),\
    \ p.end(),\n                [&points](int i, int j) {\n                    const\
    \ auto &[xi, yi] = points[i];\n                    const auto &[xj, yj] = points[j];\n\
    \                    return yi - xi == yj - xj ? xi < xj : yi - xi < yj - xj;\n\
    \                }\n            );\n\n            std::vector<T> comp_x(n);\n\
    \            for (int i = 0; i < n; ++i) comp_x[i] = points[i].first;\n      \
    \      std::sort(comp_x.begin(), comp_x.end());\n            comp_x.erase(std::unique(comp_x.begin(),\
    \ comp_x.end()), comp_x.end());\n            const int m = comp_x.size();\n\n\
    \            auto compress = [&](const T& x) { return std::lower_bound(comp_x.begin(),\
    \ comp_x.end(), x) - comp_x.begin(); };\n\n            PrefixMaxQuery<T> pmq(m);\n\
    \n            for (int i : p) {\n                const auto& [x, y] = points[i];\n\
    \                const int cx = compress(x);\n                if (const auto v\
    \ = pmq.prefix_query(cx + 1); v != e<T>()) {\n                    res[i] = std::min(res[i],\
    \ x + y - v);\n                }\n                pmq.apply(cx, x + y);\n    \
    \        }\n        };\n\n        for (int x_rev = 0; x_rev < 2; ++x_rev) {\n\
    \            for (int y_rev = 0; y_rev < 2; ++y_rev) {\n                for (int\
    \ xy_rev = 0; xy_rev < 2; ++xy_rev) {\n                    sweep();\n        \
    \            for (auto& [x, y] : points) std::swap(x, y);\n                }\n\
    \                for (auto& [x, _] : points) x = -x;\n            }\n        \
    \    for (auto& [_, y] : points) y = -y;\n        }\n\n        return res;\n \
    \   }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MANHATTAN_MINIMUM_DISTANCES\n#define SUISEN_MANHATTAN_MINIMUM_DISTANCES\n\
    \n#include <algorithm>\n#include <limits>\n#include <numeric>\n#include <vector>\n\
    \n#include \"library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp\"\n\n\
    namespace suisen {\n    namespace internal::manhattan_minimum_distances {\n  \
    \      template <typename T>\n        T op(T x, T y) { return std::max(x, y);\
    \ };\n        template <typename T>\n        T e() { return std::numeric_limits<T>::min();\
    \ };\n        template <typename T>\n        using PrefixMaxQuery = FenwickTreePrefix<T,\
    \ op<T>, e<T>>;\n    } // namespace internal::manhattan_minimum_distances\n\n\
    \    template <typename T>\n    std::vector<T> manhattan_minimum_distances(std::vector<std::pair<T,\
    \ T>> points) {\n        using namespace internal::manhattan_minimum_distances;\n\
    \n        const int n = points.size();\n        std::vector<int> p(n);\n     \
    \   std::iota(p.begin(), p.end(), 0);\n\n        std::vector<T> res(n, std::numeric_limits<T>::max());\n\
    \n        auto sweep = [&] {\n            std::sort(\n                p.begin(),\
    \ p.end(),\n                [&points](int i, int j) {\n                    const\
    \ auto &[xi, yi] = points[i];\n                    const auto &[xj, yj] = points[j];\n\
    \                    return yi - xi == yj - xj ? xi < xj : yi - xi < yj - xj;\n\
    \                }\n            );\n\n            std::vector<T> comp_x(n);\n\
    \            for (int i = 0; i < n; ++i) comp_x[i] = points[i].first;\n      \
    \      std::sort(comp_x.begin(), comp_x.end());\n            comp_x.erase(std::unique(comp_x.begin(),\
    \ comp_x.end()), comp_x.end());\n            const int m = comp_x.size();\n\n\
    \            auto compress = [&](const T& x) { return std::lower_bound(comp_x.begin(),\
    \ comp_x.end(), x) - comp_x.begin(); };\n\n            PrefixMaxQuery<T> pmq(m);\n\
    \n            for (int i : p) {\n                const auto& [x, y] = points[i];\n\
    \                const int cx = compress(x);\n                if (const auto v\
    \ = pmq.prefix_query(cx + 1); v != e<T>()) {\n                    res[i] = std::min(res[i],\
    \ x + y - v);\n                }\n                pmq.apply(cx, x + y);\n    \
    \        }\n        };\n\n        for (int x_rev = 0; x_rev < 2; ++x_rev) {\n\
    \            for (int y_rev = 0; y_rev < 2; ++y_rev) {\n                for (int\
    \ xy_rev = 0; xy_rev < 2; ++xy_rev) {\n                    sweep();\n        \
    \            for (auto& [x, y] : points) std::swap(x, y);\n                }\n\
    \                for (auto& [x, _] : points) x = -x;\n            }\n        \
    \    for (auto& [_, y] : points) y = -y;\n        }\n\n        return res;\n \
    \   }\n} // namespace suisen\n\n\n#endif // SUISEN_MANHATTAN_MINIMUM_DISTANCES\n"
  dependsOn:
  - library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
  isVerificationFile: false
  path: library/graph/manhattan_minimum_distances.hpp
  requiredBy: []
  timestamp: '2022-06-14 00:04:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/manhattan_minimum_distances.hpp
layout: document
title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u3082\u8FD1\u3044\
  \u70B9\u3078\u306E\u8DDD\u96E2\u306E\u5217\u6319"
---
## マンハッタン距離で最も近い点への距離の列挙

$N$ 個の点 $(x_i,y_i)$ が与えられるので，以下で定まる $d _ i$ を全ての $i$ に対して $O(N\log N)$ 時間で計算する．

$$
d _ i = \min _ {j \neq i} |x _ i - x _ j| + |y _ i - y _ j|
$$
