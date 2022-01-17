---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/union_find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A
  bundledCode: "#line 1 \"test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/union_find/union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct\
    \ UnionFind {\n        UnionFind() {}\n        explicit UnionFind(int n) : n(n),\
    \ data(n, -1) {}\n        // Get the root of `x`. equivalent to `operator[](x)`\n\
    \        int root(int x) {\n            static std::vector<int> buf;\n       \
    \     while (data[x] >= 0) buf.push_back(x), x = data[x];\n            while (buf.size())\
    \ data[buf.back()] = x, buf.pop_back();\n            return x;\n        }\n  \
    \      // Get the root of `x`. euivalent to `root(x)`\n        int operator[](int\
    \ x) {\n            return root(x);\n        }\n        // Merge two vertices\
    \ `x` and `y`.\n        bool merge(int x, int y) {\n            x = root(x), y\
    \ = root(y);\n            if (x == y) return false;\n            if (data[x] >\
    \ data[y]) std::swap(x, y);\n            data[x] += data[y], data[y] = x;\n  \
    \          return true;\n        }\n        // Check if `x` and `y` belongs to\
    \ the same connected component.\n        bool same(int x, int y) {\n         \
    \   return root(x) == root(y);\n        }\n        // Get the size of connected\
    \ componet to which `x` belongs.\n        int size(int x) {\n            return\
    \ -data[root(x)];\n        }\n        // Get all of connected components.\n  \
    \      std::vector<std::vector<int>> groups() {\n            std::vector<std::vector<int>>\
    \ res(n);\n            for (int i = 0; i < n; ++i) res[root(i)].push_back(i);\n\
    \            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g)\
    \ { return g.empty(); }), res.end());\n            return res;\n        }\n  \
    \  private:\n        int n;\n        std::vector<int> data;\n    };\n} // namespace\
    \ suisen\n\n\n#line 6 \"test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp\"\
    \nusing suisen::UnionFind;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    UnionFind\
    \ uf(n);\n    for (int i = 0; i < q; ++i) {\n        int t, x, y;\n        std::cin\
    \ >> t >> x >> y;\n        if (t == 0) {\n            uf.merge(x, y);\n      \
    \  } else {\n            std::cout << int(uf.same(x, y)) << '\\n';\n        }\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/union_find/union_find.hpp\"\
    \nusing suisen::UnionFind;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    UnionFind\
    \ uf(n);\n    for (int i = 0; i < q; ++i) {\n        int t, x, y;\n        std::cin\
    \ >> t >> x >> y;\n        if (t == 0) {\n            uf.merge(x, y);\n      \
    \  } else {\n            std::cout << int(uf.same(x, y)) << '\\n';\n        }\n\
    \    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/union_find/union_find.hpp
  isVerificationFile: true
  path: test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
  requiredBy: []
  timestamp: '2022-01-17 22:14:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
- /verify/test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp.html
title: test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
---
