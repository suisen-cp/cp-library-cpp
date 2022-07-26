---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence.test.cpp
    title: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
    title: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/dp/longest_increasing_subsequence.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    namespace internal::lis\
    \ {\n        template <typename T, typename ComparatorType>\n        std::vector<int>\
    \ solve(const std::vector<T>& a) {\n            if (a.empty()) return {};\n  \
    \          const int n = a.size();\n            std::vector<T> dp;\n         \
    \   dp.reserve(n);\n            std::vector<int> pd(n, -1), id(n, -1);\n     \
    \       for (int i = 0; i < n; ++i) {\n                const int pos = std::lower_bound(dp.begin(),\
    \ dp.end(), a[i], ComparatorType{}) - dp.begin();\n                id[pos] = i;\n\
    \                if (pos >= 1) pd[i] = id[pos - 1];\n                if (pos ==\
    \ int(dp.size())) dp.push_back(a[i]);\n                else dp[pos] = a[i];\n\
    \            }\n            int len = dp.size();\n            std::vector<int>\
    \ ans(len);\n            for (int cur = id[len - 1]; cur >= 0; cur = pd[cur])\
    \ ans[--len] = cur;\n            return ans;\n        }\n    }\n    // @returns\
    \ ** indices ** of longest increasing subsequence\n    template <typename T>\n\
    \    std::vector<int> longest_increasing_subsequence(const std::vector<T>& a)\
    \    { return internal::lis::solve<T, std::less<T>>(a); }\n    // @returns **\
    \ indices ** of longest nondecreasing subsequence\n    template <typename T>\n\
    \    std::vector<int> longest_nondecreasing_subsequence(const std::vector<T>&\
    \ a) { return internal::lis::solve<T, std::less_equal<T>>(a); }\n    // @returns\
    \ ** indices ** of longest nonincreasing subsequence\n    template <typename T>\n\
    \    std::vector<int> longest_nonincreasing_subsequence(const std::vector<T>&\
    \ a) { return internal::lis::solve<T, std::greater_equal<T>>(a); }\n    // @returns\
    \ ** indices ** of longest decreasing subsequence\n    template <typename T>\n\
    \    std::vector<int> longest_decreasing_subsequence(const std::vector<T>& a)\
    \    { return internal::lis::solve<T, std::greater<T>>(a); }\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_LONGEST_INCREASING_SUBSEQUENCE\n#define SUISEN_LONGEST_INCREASING_SUBSEQUENCE\n\
    \n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    namespace\
    \ internal::lis {\n        template <typename T, typename ComparatorType>\n  \
    \      std::vector<int> solve(const std::vector<T>& a) {\n            if (a.empty())\
    \ return {};\n            const int n = a.size();\n            std::vector<T>\
    \ dp;\n            dp.reserve(n);\n            std::vector<int> pd(n, -1), id(n,\
    \ -1);\n            for (int i = 0; i < n; ++i) {\n                const int pos\
    \ = std::lower_bound(dp.begin(), dp.end(), a[i], ComparatorType{}) - dp.begin();\n\
    \                id[pos] = i;\n                if (pos >= 1) pd[i] = id[pos -\
    \ 1];\n                if (pos == int(dp.size())) dp.push_back(a[i]);\n      \
    \          else dp[pos] = a[i];\n            }\n            int len = dp.size();\n\
    \            std::vector<int> ans(len);\n            for (int cur = id[len - 1];\
    \ cur >= 0; cur = pd[cur]) ans[--len] = cur;\n            return ans;\n      \
    \  }\n    }\n    // @returns ** indices ** of longest increasing subsequence\n\
    \    template <typename T>\n    std::vector<int> longest_increasing_subsequence(const\
    \ std::vector<T>& a)    { return internal::lis::solve<T, std::less<T>>(a); }\n\
    \    // @returns ** indices ** of longest nondecreasing subsequence\n    template\
    \ <typename T>\n    std::vector<int> longest_nondecreasing_subsequence(const std::vector<T>&\
    \ a) { return internal::lis::solve<T, std::less_equal<T>>(a); }\n    // @returns\
    \ ** indices ** of longest nonincreasing subsequence\n    template <typename T>\n\
    \    std::vector<int> longest_nonincreasing_subsequence(const std::vector<T>&\
    \ a) { return internal::lis::solve<T, std::greater_equal<T>>(a); }\n    // @returns\
    \ ** indices ** of longest decreasing subsequence\n    template <typename T>\n\
    \    std::vector<int> longest_decreasing_subsequence(const std::vector<T>& a)\
    \    { return internal::lis::solve<T, std::greater<T>>(a); }\n} // namespace suisen\n\
    \n#endif // SUISEN_LONGEST_INCREASING_SUBSEQUENCE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/dp/longest_increasing_subsequence.hpp
  requiredBy: []
  timestamp: '2022-07-26 15:08:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
  - test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence.test.cpp
documentation_of: library/dp/longest_increasing_subsequence.hpp
layout: document
redirect_from:
- /library/library/dp/longest_increasing_subsequence.hpp
- /library/library/dp/longest_increasing_subsequence.hpp.html
title: library/dp/longest_increasing_subsequence.hpp
---
