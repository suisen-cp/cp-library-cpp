---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/union_find/union_find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/union_find/linked_union_find/past202203_h.test.cpp
    title: test/src/datastructure/union_find/linked_union_find/past202203_h.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find/linked_union_find.hpp\"\
    \n\n\n\n#include <numeric>\n#line 1 \"library/datastructure/union_find/union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct\
    \ UnionFind {\n        UnionFind() {}\n        explicit UnionFind(int _n) : _n(_n),\
    \ _dat(_n, -1) {}\n        // Get the root of `x`. equivalent to `operator[](x)`\n\
    \        int root(int x) {\n            static std::vector<int> buf;\n       \
    \     while (_dat[x] >= 0) buf.push_back(x), x = _dat[x];\n            while (buf.size())\
    \ _dat[buf.back()] = x, buf.pop_back();\n            return x;\n        }\n  \
    \      // Get the root of `x`. euivalent to `root(x)`\n        int operator[](int\
    \ x) {\n            return root(x);\n        }\n        // Merge two vertices\
    \ `x` and `y`.\n        bool merge(int x, int y) {\n            x = root(x), y\
    \ = root(y);\n            if (x == y) return false;\n            if (_dat[x] >\
    \ _dat[y]) std::swap(x, y);\n            _dat[x] += _dat[y], _dat[y] = x;\n  \
    \          return true;\n        }\n        // Check if `x` and `y` belongs to\
    \ the same connected component.\n        bool same(int x, int y) {\n         \
    \   return root(x) == root(y);\n        }\n        // Get the size of connected\
    \ componet to which `x` belongs.\n        int size(int x) {\n            return\
    \ -_dat[root(x)];\n        }\n        // Get all of connected components.\n  \
    \      std::vector<std::vector<int>> groups() {\n            std::vector<std::vector<int>>\
    \ res(_n);\n            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n\
    \            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g)\
    \ { return g.empty(); }), res.end());\n            return res;\n        }\n  \
    \  protected:\n        int _n;\n        std::vector<int> _dat;\n    };\n} // namespace\
    \ suisen\n\n\n#line 6 \"library/datastructure/union_find/linked_union_find.hpp\"\
    \n\nnamespace suisen {\n    struct LinkedUnionFind : public UnionFind {\n    \
    \    LinkedUnionFind() {}\n        explicit LinkedUnionFind(int n) : UnionFind(n),\
    \ _link(n) {\n            std::iota(_link.begin(), _link.end(), 0);\n        }\n\
    \        // Merge two vertices `x` and `y`.\n        bool merge(int x, int y)\
    \ {\n            if (UnionFind::merge(x, y)) {\n                std::swap(_link[x],\
    \ _link[y]);\n                return true;\n            }\n            return\
    \ false;\n        }\n        // Get items connected to `x` (including `x`). Let\
    \ the size of return value be `m`, time complexity is O(m).\n        std::vector<int>\
    \ connected_component(int x) const {\n            std::vector<int> comp{ x };\n\
    \            for (int y = _link[x]; y != x; y = _link[y]) comp.push_back(y);\n\
    \            return comp;\n        }\n    protected:\n        std::vector<int>\
    \ _link;\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_LINKED_UNION_FIND\n#define SUISEN_LINKED_UNION_FIND\n\n#include\
    \ <numeric>\n#include \"library/datastructure/union_find/union_find.hpp\"\n\n\
    namespace suisen {\n    struct LinkedUnionFind : public UnionFind {\n        LinkedUnionFind()\
    \ {}\n        explicit LinkedUnionFind(int n) : UnionFind(n), _link(n) {\n   \
    \         std::iota(_link.begin(), _link.end(), 0);\n        }\n        // Merge\
    \ two vertices `x` and `y`.\n        bool merge(int x, int y) {\n            if\
    \ (UnionFind::merge(x, y)) {\n                std::swap(_link[x], _link[y]);\n\
    \                return true;\n            }\n            return false;\n    \
    \    }\n        // Get items connected to `x` (including `x`). Let the size of\
    \ return value be `m`, time complexity is O(m).\n        std::vector<int> connected_component(int\
    \ x) const {\n            std::vector<int> comp{ x };\n            for (int y\
    \ = _link[x]; y != x; y = _link[y]) comp.push_back(y);\n            return comp;\n\
    \        }\n    protected:\n        std::vector<int> _link;\n    };\n} // namespace\
    \ suisen\n\n#endif // SUISEN_LINKED_UNION_FIND\n"
  dependsOn:
  - library/datastructure/union_find/union_find.hpp
  isVerificationFile: false
  path: library/datastructure/union_find/linked_union_find.hpp
  requiredBy: []
  timestamp: '2022-06-27 18:51:28+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/datastructure/union_find/linked_union_find/past202203_h.test.cpp
documentation_of: library/datastructure/union_find/linked_union_find.hpp
layout: document
title: "\u9023\u7D50\u6210\u5206\u3092\u53D6\u5F97\u3067\u304D\u308B Union Find"
---
## 連結成分を取得できる Union Find

名前が分かりません。[素集合の要素の列挙と併合 (単方向循環リスト)](https://noshi91.hatenablog.com/entry/2019/07/19/180606) これです。

頂点 $v$ が属する連結成分 $C$ を $O(\vert C\vert)$ で取得可能である。
