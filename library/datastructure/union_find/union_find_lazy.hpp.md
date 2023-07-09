---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/union_find/linked_union_find.hpp
    title: "\u9023\u7D50\u6210\u5206\u3092\u53D6\u5F97\u3067\u304D\u308B Union Find"
  - icon: ':x:'
    path: library/datastructure/union_find/union_find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Union Find with lazy propagation
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find/union_find_lazy.hpp\"\n\
    \n\n\n#line 1 \"library/datastructure/union_find/linked_union_find.hpp\"\n\n\n\
    \n#include <numeric>\n#line 1 \"library/datastructure/union_find/union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct\
    \ UnionFind {\n        UnionFind() = default;\n        explicit UnionFind(int\
    \ _n) : _n(_n), _dat(_n, -1) {}\n        // Get the root of `x`. equivalent to\
    \ `operator[](x)`\n        int root(int x) {\n            static std::vector<int>\
    \ buf;\n            while (_dat[x] >= 0) buf.push_back(x), x = _dat[x];\n    \
    \        while (buf.size()) _dat[buf.back()] = x, buf.pop_back();\n          \
    \  return x;\n        }\n        // Get the root of `x`. euivalent to `root(x)`\n\
    \        int operator[](int x) {\n            return root(x);\n        }\n   \
    \     // Merge two vertices `x` and `y`.\n        bool merge(int x, int y) {\n\
    \            x = root(x), y = root(y);\n            if (x == y) return false;\n\
    \            if (_dat[x] > _dat[y]) std::swap(x, y);\n            _dat[x] += _dat[y],\
    \ _dat[y] = x;\n            return true;\n        }\n        // Check if `x` and\
    \ `y` belongs to the same connected component.\n        bool same(int x, int y)\
    \ {\n            return root(x) == root(y);\n        }\n        // Get the size\
    \ of connected componet to which `x` belongs.\n        int size(int x) {\n   \
    \         return -_dat[root(x)];\n        }\n        // Get all of connected components.\n\
    \        std::vector<std::vector<int>> groups() {\n            std::vector<std::vector<int>>\
    \ res(_n);\n            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n\
    \            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g)\
    \ { return g.empty(); }), res.end());\n            return res;\n        }\n  \
    \  protected:\n        int _n;\n        std::vector<int> _dat;\n    };\n} // namespace\
    \ suisen\n\n\n#line 6 \"library/datastructure/union_find/linked_union_find.hpp\"\
    \n\nnamespace suisen {\n    struct LinkedUnionFind : public UnionFind {\n    \
    \    LinkedUnionFind() = default;\n        explicit LinkedUnionFind(int n) : UnionFind(n),\
    \ _link(n) {\n            std::iota(_link.begin(), _link.end(), 0);\n        }\n\
    \        // Merge two vertices `x` and `y`.\n        bool merge(int x, int y)\
    \ {\n            if (UnionFind::merge(x, y)) {\n                std::swap(_link[x],\
    \ _link[y]);\n                return true;\n            }\n            return\
    \ false;\n        }\n        // Get items connected to `x` (including `x`). Let\
    \ the size of return value be `m`, time complexity is O(m).\n        std::vector<int>\
    \ connected_component(int x) const {\n            std::vector<int> comp{ x };\n\
    \            for (int y = _link[x]; y != x; y = _link[y]) comp.push_back(y);\n\
    \            return comp;\n        }\n    protected:\n        std::vector<int>\
    \ _link;\n    };\n} // namespace suisen\n\n\n#line 5 \"library/datastructure/union_find/union_find_lazy.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * @brief Union Find with lazy propagation\n\
    \     * @tparam T type of sum/value: commutative monoid\n     * @tparam F type\
    \ of operator: (possibly non-commutative) group\n     * @tparam merge_sum (T&\
    \ sum_parent, T sum_child) -> void\n     * @tparam neg (T x) -> -x\n     * @tparam\
    \ mapping (F f, T& sum, int num) -> void\n     * @tparam composition (F f, F g)\
    \ -> f * g\n     * @tparam id () -> identity\n     * @tparam inv (F f) -> f^(-1)\n\
    \     */\n    template <typename T, void(*merge_sum)(T&, T), T(*neg)(T), typename\
    \ F, void(*mapping)(F, T&, int), F(*composition)(F, F), F(*id)(), F(*inv)(F)>\n\
    \    struct UnionFindLazy : LinkedUnionFind {\n        UnionFindLazy() : UnionFindLazy(0)\
    \ {}\n        explicit UnionFindLazy(int n, const T &init_value = T{}) : UnionFindLazy(std::vector<T>(n,\
    \ init_value)) {}\n        explicit UnionFindLazy(const std::vector<T> &init_values)\
    \ : LinkedUnionFind(init_values.size()), _val(init_values), _sum(init_values),\
    \ _laz(_n, id()) {}\n\n        bool merge(int x, int y) {\n            x = root(x),\
    \ y = root(y);\n            if (x == y) return false;\n\n            UnionFind::merge(x,\
    \ y);\n            if (root(x) == y) std::swap(x, y);\n            \n        \
    \    F laz = composition(inv(_laz[x]), _laz[y]);\n            for (int v : connected_component(y))\
    \ {\n                mapping(laz, _val[v], 1);\n            }\n\n            merge_sum(_sum[x],\
    \ std::move(_sum[y]));\n\n            std::swap(_link[x], _link[y]);\n       \
    \     return true;\n        }\n\n        const T& get_component(int x) {\n   \
    \         return _sum[root(x)];\n        }\n        T get_point(int x) {\n   \
    \         T val = _val[x];\n            mapping(_laz[root(x)], val, 1);\n    \
    \        return val;\n        }\n        void apply_component(int x, const F&\
    \ f) {\n            x = root(x);\n            mapping(f, _sum[x], size(x));\n\
    \            _laz[x] = composition(f, _laz[x]);\n        }\n        void apply_point(int\
    \ x, const F& f) {\n            _apply_point(x, [&f](T& old_value) { mapping(f,\
    \ old_value, 1); });\n        }\n        void set_point(int x, const T &new_value)\
    \ {\n            _apply_point(x, [&new_value](T& old_value) { old_value = new_value;\
    \ });\n        }\n\n        void propagate(int x) {\n            x = root(x);\n\
    \            F laz = std::exchange(_laz[x], id());\n            for (int v : connected_component(x))\
    \ {\n                mapping(laz, _val[v], 1);\n            }\n        }\n\n \
    \       T& raw_value(int x) {\n            return _val[x];\n        }\n      \
    \  const T& raw_value(int x) const {\n            return _val[x];\n        }\n\
    \    private:\n        std::vector<T> _val;\n        std::vector<T> _sum;\n  \
    \      std::vector<F> _laz;\n\n        template <typename Mapping>\n        void\
    \ _apply_point(int x, const Mapping& f) {\n            int r = root(x);\n    \
    \        T v = get_point(x);\n            merge_sum(_sum[r], neg(v));\n      \
    \      f(v);\n            merge_sum(_sum[r], v);\n            mapping(inv(_laz[r]),\
    \ _val[x] = std::move(v), 1);\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_UNION_FIND_COMPONENT_SUM\n#define SUISEN_UNION_FIND_COMPONENT_SUM\n\
    \n#include \"library/datastructure/union_find/linked_union_find.hpp\"\n\nnamespace\
    \ suisen {\n    /**\n     * @brief Union Find with lazy propagation\n     * @tparam\
    \ T type of sum/value: commutative monoid\n     * @tparam F type of operator:\
    \ (possibly non-commutative) group\n     * @tparam merge_sum (T& sum_parent, T\
    \ sum_child) -> void\n     * @tparam neg (T x) -> -x\n     * @tparam mapping (F\
    \ f, T& sum, int num) -> void\n     * @tparam composition (F f, F g) -> f * g\n\
    \     * @tparam id () -> identity\n     * @tparam inv (F f) -> f^(-1)\n     */\n\
    \    template <typename T, void(*merge_sum)(T&, T), T(*neg)(T), typename F, void(*mapping)(F,\
    \ T&, int), F(*composition)(F, F), F(*id)(), F(*inv)(F)>\n    struct UnionFindLazy\
    \ : LinkedUnionFind {\n        UnionFindLazy() : UnionFindLazy(0) {}\n       \
    \ explicit UnionFindLazy(int n, const T &init_value = T{}) : UnionFindLazy(std::vector<T>(n,\
    \ init_value)) {}\n        explicit UnionFindLazy(const std::vector<T> &init_values)\
    \ : LinkedUnionFind(init_values.size()), _val(init_values), _sum(init_values),\
    \ _laz(_n, id()) {}\n\n        bool merge(int x, int y) {\n            x = root(x),\
    \ y = root(y);\n            if (x == y) return false;\n\n            UnionFind::merge(x,\
    \ y);\n            if (root(x) == y) std::swap(x, y);\n            \n        \
    \    F laz = composition(inv(_laz[x]), _laz[y]);\n            for (int v : connected_component(y))\
    \ {\n                mapping(laz, _val[v], 1);\n            }\n\n            merge_sum(_sum[x],\
    \ std::move(_sum[y]));\n\n            std::swap(_link[x], _link[y]);\n       \
    \     return true;\n        }\n\n        const T& get_component(int x) {\n   \
    \         return _sum[root(x)];\n        }\n        T get_point(int x) {\n   \
    \         T val = _val[x];\n            mapping(_laz[root(x)], val, 1);\n    \
    \        return val;\n        }\n        void apply_component(int x, const F&\
    \ f) {\n            x = root(x);\n            mapping(f, _sum[x], size(x));\n\
    \            _laz[x] = composition(f, _laz[x]);\n        }\n        void apply_point(int\
    \ x, const F& f) {\n            _apply_point(x, [&f](T& old_value) { mapping(f,\
    \ old_value, 1); });\n        }\n        void set_point(int x, const T &new_value)\
    \ {\n            _apply_point(x, [&new_value](T& old_value) { old_value = new_value;\
    \ });\n        }\n\n        void propagate(int x) {\n            x = root(x);\n\
    \            F laz = std::exchange(_laz[x], id());\n            for (int v : connected_component(x))\
    \ {\n                mapping(laz, _val[v], 1);\n            }\n        }\n\n \
    \       T& raw_value(int x) {\n            return _val[x];\n        }\n      \
    \  const T& raw_value(int x) const {\n            return _val[x];\n        }\n\
    \    private:\n        std::vector<T> _val;\n        std::vector<T> _sum;\n  \
    \      std::vector<F> _laz;\n\n        template <typename Mapping>\n        void\
    \ _apply_point(int x, const Mapping& f) {\n            int r = root(x);\n    \
    \        T v = get_point(x);\n            merge_sum(_sum[r], neg(v));\n      \
    \      f(v);\n            merge_sum(_sum[r], v);\n            mapping(inv(_laz[r]),\
    \ _val[x] = std::move(v), 1);\n        }\n    };\n} // namespace suisen\n\n\n\
    #endif // SUISEN_UNION_FIND_COMPONENT_SUM\n"
  dependsOn:
  - library/datastructure/union_find/linked_union_find.hpp
  - library/datastructure/union_find/union_find.hpp
  isVerificationFile: false
  path: library/datastructure/union_find/union_find_lazy.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:27+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/union_find/union_find_lazy.hpp
layout: document
redirect_from:
- /library/library/datastructure/union_find/union_find_lazy.hpp
- /library/library/datastructure/union_find/union_find_lazy.hpp.html
title: Union Find with lazy propagation
---
