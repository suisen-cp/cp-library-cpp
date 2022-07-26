---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
    title: test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/dp/number_of_subsequences.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace suisen {\n    // Requirement: T\
    \ is comparable \n    template <typename Int, typename T>\n    auto number_of_nonempty_subsequences(const\
    \ std::vector<T> &a) -> decltype(std::declval<T>() < std::declval<T>(), Int{})\
    \ {\n        const int n = a.size();\n        std::vector<std::pair<T, int>> sorted(n);\n\
    \        for (int i = 0; i < n; ++i) sorted[i] = { a[i], i };\n        std::sort(sorted.begin(),\
    \ sorted.end());\n\n        std::vector<int> last(n, -1);\n        for (int i\
    \ = 0; i < n;) {\n            for (auto [v, p] = sorted[i]; ++i < n and sorted[i].first\
    \ == v;) {\n                const int c = sorted[i].second;\n                last[c]\
    \ = std::exchange(p, c);\n            }\n        }\n\n        std::vector<Int>\
    \ sdp(n + 2);\n        sdp[1] = 1;\n        for (int i = 0; i < n; ++i) sdp[i\
    \ + 2] = sdp[i + 1] + sdp[i + 1] - sdp[last[i] + 1];\n        return sdp[n + 1]\
    \ - 1;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_NUMBER_OF_SUBSEQUENCES\n#define SUISEN_NUMBER_OF_SUBSEQUENCES\n\
    \n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    // Requirement:\
    \ T is comparable \n    template <typename Int, typename T>\n    auto number_of_nonempty_subsequences(const\
    \ std::vector<T> &a) -> decltype(std::declval<T>() < std::declval<T>(), Int{})\
    \ {\n        const int n = a.size();\n        std::vector<std::pair<T, int>> sorted(n);\n\
    \        for (int i = 0; i < n; ++i) sorted[i] = { a[i], i };\n        std::sort(sorted.begin(),\
    \ sorted.end());\n\n        std::vector<int> last(n, -1);\n        for (int i\
    \ = 0; i < n;) {\n            for (auto [v, p] = sorted[i]; ++i < n and sorted[i].first\
    \ == v;) {\n                const int c = sorted[i].second;\n                last[c]\
    \ = std::exchange(p, c);\n            }\n        }\n\n        std::vector<Int>\
    \ sdp(n + 2);\n        sdp[1] = 1;\n        for (int i = 0; i < n; ++i) sdp[i\
    \ + 2] = sdp[i + 1] + sdp[i + 1] - sdp[last[i] + 1];\n        return sdp[n + 1]\
    \ - 1;\n    }\n} // namespace suisen\n\n#endif // SUISEN_NUMBER_OF_SUBSEQUENCES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/dp/number_of_subsequences.hpp
  requiredBy: []
  timestamp: '2022-07-26 15:37:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
documentation_of: library/dp/number_of_subsequences.hpp
layout: document
redirect_from:
- /library/library/dp/number_of_subsequences.hpp
- /library/library/dp/number_of_subsequences.hpp.html
title: library/dp/number_of_subsequences.hpp
---
