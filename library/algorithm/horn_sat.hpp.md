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
  bundledCode: "#line 1 \"library/algorithm/horn_sat.hpp\"\n\n\n\n#include <cassert>\n\
    #include <tuple>\n#include <queue>\n#include <optional>\n#include <vector>\n\n\
    namespace suisen {\n\nclass HornSAT {\n    public:\n        HornSAT() : HornSAT(0)\
    \ {}\n        HornSAT(const int n) : n(n), ans(n, false), ls(n) {}\n\n       \
    \ void add_clause(const std::vector<int> &lhs, int rhs, bool val) {\n        \
    \    const int sz = cnt.size();\n            cnt.push_back(lhs.size());\n    \
    \        for (int i : lhs) ls[i].push_back(sz);\n            r.emplace_back(rhs,\
    \ val);\n            has_answer = false;\n        }\n\n        void add_clause(const\
    \ std::vector<int> &lhs) {\n            add_clause(lhs, -1, false);\n        }\n\
    \n        bool satisfiable() {\n            const int m = r.size();\n        \
    \    std::deque<std::pair<int, bool>> dq;\n            std::vector<int> c = cnt;\n\
    \            for (int j = 0; j < m; ++j) {\n                if (c[j] == 0) dq.push_back(r[j]);\n\
    \            }\n            std::vector<bool> seen(n, false);\n            while\
    \ (dq.size()) {\n                const auto [i, val] = dq.front();\n         \
    \       dq.pop_front();\n                assert(i < n);\n                if (i\
    \ < 0) return has_answer = false;\n                if (not seen[i]) {\n      \
    \              ans[i] = val;\n                    seen[i] = true;\n          \
    \          for (const int j : ls[i]) {\n                        if (--c[j] ==\
    \ 0) dq.push_back(r[j]);\n                    }\n                } else if (val\
    \ != ans[i]) return has_answer = false;\n            }\n            return has_answer\
    \ = true;\n        }\n\n        // Call after `satisfiable()`.\n        const\
    \ std::vector<bool>& answer() {\n            assert(has_answer);\n           \
    \ return ans;\n        }\n\n    private:\n        const int n;\n        std::vector<bool>\
    \ ans;\n        std::vector<int> cnt;\n        std::vector<std::vector<int>> ls;\n\
    \        std::vector<std::pair<int, bool>> r;\n        bool has_answer = true;\n\
    };\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_HORN_SAT\n#define SUISEN_HORN_SAT\n\n#include <cassert>\n\
    #include <tuple>\n#include <queue>\n#include <optional>\n#include <vector>\n\n\
    namespace suisen {\n\nclass HornSAT {\n    public:\n        HornSAT() : HornSAT(0)\
    \ {}\n        HornSAT(const int n) : n(n), ans(n, false), ls(n) {}\n\n       \
    \ void add_clause(const std::vector<int> &lhs, int rhs, bool val) {\n        \
    \    const int sz = cnt.size();\n            cnt.push_back(lhs.size());\n    \
    \        for (int i : lhs) ls[i].push_back(sz);\n            r.emplace_back(rhs,\
    \ val);\n            has_answer = false;\n        }\n\n        void add_clause(const\
    \ std::vector<int> &lhs) {\n            add_clause(lhs, -1, false);\n        }\n\
    \n        bool satisfiable() {\n            const int m = r.size();\n        \
    \    std::deque<std::pair<int, bool>> dq;\n            std::vector<int> c = cnt;\n\
    \            for (int j = 0; j < m; ++j) {\n                if (c[j] == 0) dq.push_back(r[j]);\n\
    \            }\n            std::vector<bool> seen(n, false);\n            while\
    \ (dq.size()) {\n                const auto [i, val] = dq.front();\n         \
    \       dq.pop_front();\n                assert(i < n);\n                if (i\
    \ < 0) return has_answer = false;\n                if (not seen[i]) {\n      \
    \              ans[i] = val;\n                    seen[i] = true;\n          \
    \          for (const int j : ls[i]) {\n                        if (--c[j] ==\
    \ 0) dq.push_back(r[j]);\n                    }\n                } else if (val\
    \ != ans[i]) return has_answer = false;\n            }\n            return has_answer\
    \ = true;\n        }\n\n        // Call after `satisfiable()`.\n        const\
    \ std::vector<bool>& answer() {\n            assert(has_answer);\n           \
    \ return ans;\n        }\n\n    private:\n        const int n;\n        std::vector<bool>\
    \ ans;\n        std::vector<int> cnt;\n        std::vector<std::vector<int>> ls;\n\
    \        std::vector<std::pair<int, bool>> r;\n        bool has_answer = true;\n\
    };\n\n} // namespace suisen\n\n\n#endif // SUISEN_HORN_SAT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/horn_sat.hpp
  requiredBy: []
  timestamp: '2021-08-24 05:45:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/horn_sat.hpp
layout: document
redirect_from:
- /library/library/algorithm/horn_sat.hpp
- /library/library/algorithm/horn_sat.hpp.html
title: library/algorithm/horn_sat.hpp
---
