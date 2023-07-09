---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/union_find/union_find.hpp
    title: Union Find
  - icon: ':x:'
    path: library/datastructure/union_find/union_find_component_sum.hpp
    title: "\u9023\u7D50\u6210\u5206\u306E\u53EF\u63DB\u30E2\u30CE\u30A4\u30C9\u548C\
      \u3092\u53D6\u5F97\u3067\u304D\u308B Union Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc183/tasks/abc183_f
    links:
    - https://atcoder.jp/contests/abc183/tasks/abc183_f
  bundledCode: "#line 1 \"test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc183/tasks/abc183_f\"\n\n#include\
    \ <iostream>\n#include <map>\n\n#line 1 \"library/datastructure/union_find/union_find_component_sum.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/union_find/union_find.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct UnionFind {\n\
    \        UnionFind() = default;\n        explicit UnionFind(int _n) : _n(_n),\
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
    \ suisen\n\n\n#line 5 \"library/datastructure/union_find/union_find_component_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, void(*merge_data)(T&, T)>\n\
    \    struct UnionFindComponentSum : UnionFind {\n        UnionFindComponentSum()\
    \ : UnionFindComponentSum(0) {}\n        explicit UnionFindComponentSum(int n,\
    \ const T &init_value = T{}) : UnionFindComponentSum(std::vector<T>(n, init_value))\
    \ {}\n        explicit UnionFindComponentSum(const std::vector<T> &init_values)\
    \ : UnionFind(init_values.size()), _sum(init_values) {}\n\n        bool merge(int\
    \ x, int y) {\n            x = root(x), y = root(y);\n            bool res = UnionFind::merge(x,\
    \ y);\n            if (res) {\n                if (root(x) == y) std::swap(x,\
    \ y);\n                merge_data(_sum[x], std::move(_sum[y]));\n            }\n\
    \            return res;\n        }\n        const T& sum(int x) {\n         \
    \   return _sum[root(x)];\n        }\n    private:\n        std::vector<T> _sum;\n\
    \    };\n} // namespace suisen\n\n\n\n#line 7 \"test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp\"\
    \n\nusing sum_type = std::map<int, int>;\n\nvoid merge(sum_type &par_data, sum_type\
    \ ch_data) {\n    for (auto &[k, v] : ch_data) par_data[k] += v;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int> c(n);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> c[i];\n\n    std::vector<sum_type> init_data(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        ++init_data[i][c[i]];\n    }\n   \
    \ suisen::UnionFindComponentSum<sum_type, merge> uf(init_data);\n\n    while (q\
    \ --> 0) {\n        int query_type;\n        std::cin >> query_type;\n       \
    \ if (query_type == 1) {\n            int a, b;\n            std::cin >> a >>\
    \ b;\n            --a, --b;\n            uf.merge(a, b);\n        } else {\n \
    \           int x, y;\n            std::cin >> x >> y;\n            --x;\n   \
    \         const auto& sum = uf.sum(x);\n            if (auto it = sum.find(y);\
    \ it == sum.end()) {\n                std::cout << 0 << '\\n';\n            }\
    \ else {\n                std::cout << it->second << '\\n';\n            }\n \
    \       }\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc183/tasks/abc183_f\"\n\n\
    #include <iostream>\n#include <map>\n\n#include \"library/datastructure/union_find/union_find_component_sum.hpp\"\
    \n\nusing sum_type = std::map<int, int>;\n\nvoid merge(sum_type &par_data, sum_type\
    \ ch_data) {\n    for (auto &[k, v] : ch_data) par_data[k] += v;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int> c(n);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> c[i];\n\n    std::vector<sum_type> init_data(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        ++init_data[i][c[i]];\n    }\n   \
    \ suisen::UnionFindComponentSum<sum_type, merge> uf(init_data);\n\n    while (q\
    \ --> 0) {\n        int query_type;\n        std::cin >> query_type;\n       \
    \ if (query_type == 1) {\n            int a, b;\n            std::cin >> a >>\
    \ b;\n            --a, --b;\n            uf.merge(a, b);\n        } else {\n \
    \           int x, y;\n            std::cin >> x >> y;\n            --x;\n   \
    \         const auto& sum = uf.sum(x);\n            if (auto it = sum.find(y);\
    \ it == sum.end()) {\n                std::cout << 0 << '\\n';\n            }\
    \ else {\n                std::cout << it->second << '\\n';\n            }\n \
    \       }\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/datastructure/union_find/union_find_component_sum.hpp
  - library/datastructure/union_find/union_find.hpp
  isVerificationFile: true
  path: test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
- /verify/test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp.html
title: test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
---
