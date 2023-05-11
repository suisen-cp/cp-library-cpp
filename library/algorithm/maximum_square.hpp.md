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
  bundledCode: "#line 1 \"library/algorithm/maximum_square.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <tuple>\n#include <vector>\n\nnamespace suisen {\n    // Returns { max_area,\
    \ { u, d, l, r } } where g[u,d)*[l,r) is one of the maximum squares.\n    template\
    \ <typename Grid>\n    std::pair<int, std::tuple<int, int, int, int>> maximum_square(const\
    \ Grid& g) {\n        int max_l = 0;\n        std::tuple<int, int, int, int> max_square;\n\
    \n        const int n = g.size();\n        const int m = n == 0 ? 0 : g[0].size();\n\
    \        \n        std::vector<int> pd(m);\n        for (int i = 0; i < n; ++i)\
    \ {\n            std::vector<int> dp(m);\n            for (int j = 0; j < m; ++j)\
    \ if (g[i][j]) {\n                if (j == 0) {\n                    dp[j] = 1;\n\
    \                } else {\n                    dp[j] = 1 + std::min({ dp[j - 1],\
    \ pd[j - 1], pd[j] });\n                }\n                if (dp[j] > max_l)\
    \ {\n                    max_l = dp[j];\n                    max_square = { i\
    \ + 1 - max_l, i + 1, j + 1 - max_l, j + 1 };\n                }\n           \
    \ }\n            dp.swap(pd);\n        }\n        return { max_l * max_l, max_square\
    \ };\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MAXIMUM_SQUARE\n#define SUISEN_MAXIMUM_SQUARE\n\n#include\
    \ <algorithm>\n#include <tuple>\n#include <vector>\n\nnamespace suisen {\n   \
    \ // Returns { max_area, { u, d, l, r } } where g[u,d)*[l,r) is one of the maximum\
    \ squares.\n    template <typename Grid>\n    std::pair<int, std::tuple<int, int,\
    \ int, int>> maximum_square(const Grid& g) {\n        int max_l = 0;\n       \
    \ std::tuple<int, int, int, int> max_square;\n\n        const int n = g.size();\n\
    \        const int m = n == 0 ? 0 : g[0].size();\n        \n        std::vector<int>\
    \ pd(m);\n        for (int i = 0; i < n; ++i) {\n            std::vector<int>\
    \ dp(m);\n            for (int j = 0; j < m; ++j) if (g[i][j]) {\n           \
    \     if (j == 0) {\n                    dp[j] = 1;\n                } else {\n\
    \                    dp[j] = 1 + std::min({ dp[j - 1], pd[j - 1], pd[j] });\n\
    \                }\n                if (dp[j] > max_l) {\n                   \
    \ max_l = dp[j];\n                    max_square = { i + 1 - max_l, i + 1, j +\
    \ 1 - max_l, j + 1 };\n                }\n            }\n            dp.swap(pd);\n\
    \        }\n        return { max_l * max_l, max_square };\n    }\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_MAXIMUM_SQUARE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/maximum_square.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:17:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/maximum_square.hpp
layout: document
redirect_from:
- /library/library/algorithm/maximum_square.hpp
- /library/library/algorithm/maximum_square.hpp.html
title: library/algorithm/maximum_square.hpp
---
