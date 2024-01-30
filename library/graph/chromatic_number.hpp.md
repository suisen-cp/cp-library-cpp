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
  bundledCode: "#line 1 \"library/graph/chromatic_number.hpp\"\n\n\n\n#include <vector>\n\
    \n#include <atcoder/modint>\n\nnamespace suisen {\n    namespace detail {\n  \
    \      template <int mod>\n        int chromatic_number(const int n, const std::vector<int>\
    \ &I) {\n            std::vector<int> f(1 << n);\n            for (int s = 0;\
    \ s < 1 << n; ++s) {\n                f[s] = (n - __builtin_popcount(s)) & 1 ?\
    \ mod - 1 : 1;\n            }\n            for (int k = 1; k < n; ++k) {\n   \
    \             long long sum = 0;\n                for (int s = 0; s < 1 << n;\
    \ ++s) {\n                    f[s] = static_cast<long long>(f[s]) * I[s] % mod;\n\
    \                    sum += f[s];\n                }\n                if (sum\
    \ % mod) return k;\n            }\n            return n;\n        }\n\n    } //\
    \ namespace detail::chromatic_number\n    \n    int chromatic_number(const int\
    \ n, const std::vector<std::pair<int, int>>& edges) {\n        if (n == 0) return\
    \ 0;\n\n        const int m = edges.size();\n        std::vector<int> g(n);\n\
    \        for (const auto& [u, v] : edges) {\n            g[u] |= 1 << v;\n   \
    \         g[v] |= 1 << u;\n        }\n\n        std::vector<int> I(1 << n); //\
    \ I[S] := # of independent sets T \\subseteq S\n        I[0] = 1;\n        for\
    \ (int s = 1; s < 1 << n; ++s) {\n            const int v = __builtin_ctz(s),\
    \ t = s ^ (1 << v);\n            I[s] = I[t] + I[t & ~g[v]];\n        }\n\n  \
    \      return std::min(detail::chromatic_number<998244353>(n, I), detail::chromatic_number<1000000007>(n,\
    \ I));\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_CHROMATIC_NUMBER\n#define SUISEN_CHROMATIC_NUMBER\n\n#include\
    \ <vector>\n\n#include <atcoder/modint>\n\nnamespace suisen {\n    namespace detail\
    \ {\n        template <int mod>\n        int chromatic_number(const int n, const\
    \ std::vector<int> &I) {\n            std::vector<int> f(1 << n);\n          \
    \  for (int s = 0; s < 1 << n; ++s) {\n                f[s] = (n - __builtin_popcount(s))\
    \ & 1 ? mod - 1 : 1;\n            }\n            for (int k = 1; k < n; ++k) {\n\
    \                long long sum = 0;\n                for (int s = 0; s < 1 <<\
    \ n; ++s) {\n                    f[s] = static_cast<long long>(f[s]) * I[s] %\
    \ mod;\n                    sum += f[s];\n                }\n                if\
    \ (sum % mod) return k;\n            }\n            return n;\n        }\n\n \
    \   } // namespace detail::chromatic_number\n    \n    int chromatic_number(const\
    \ int n, const std::vector<std::pair<int, int>>& edges) {\n        if (n == 0)\
    \ return 0;\n\n        const int m = edges.size();\n        std::vector<int> g(n);\n\
    \        for (const auto& [u, v] : edges) {\n            g[u] |= 1 << v;\n   \
    \         g[v] |= 1 << u;\n        }\n\n        std::vector<int> I(1 << n); //\
    \ I[S] := # of independent sets T \\subseteq S\n        I[0] = 1;\n        for\
    \ (int s = 1; s < 1 << n; ++s) {\n            const int v = __builtin_ctz(s),\
    \ t = s ^ (1 << v);\n            I[s] = I[t] + I[t & ~g[v]];\n        }\n\n  \
    \      return std::min(detail::chromatic_number<998244353>(n, I), detail::chromatic_number<1000000007>(n,\
    \ I));\n    }\n} // namespace suisen\n\n#endif // SUISEN_CHROMATIC_NUMBER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/chromatic_number.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/chromatic_number.hpp
layout: document
title: Chromatic Number
---
## Chromatic Number
