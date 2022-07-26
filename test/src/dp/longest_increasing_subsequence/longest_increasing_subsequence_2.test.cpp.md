---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/dp/longest_increasing_subsequence.hpp
    title: library/dp/longest_increasing_subsequence.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp\"\
    \n#include <iostream>\n\n#line 1 \"library/dp/longest_increasing_subsequence.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    namespace\
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
    \n\n#line 4 \"test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp\"\
    \n\nusing suisen::longest_decreasing_subsequence;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<int>\
    \ a(n);\n    for (auto &e : a) std::cin >> e, e = -e;\n\n    std::vector<int>\
    \ lis = longest_decreasing_subsequence(a);\n    \n    const int k = lis.size();\n\
    \    std::cout << k << std::endl;\n    for (int i = 0; i < k; ++i) {\n       \
    \ std::cout << lis[i];\n        if (i + 1 != k) std::cout << ' ';\n    }\n   \
    \ std::cout << std::endl;\n\n    return 0;\n}\n"
  code: "#include <iostream>\n\n#include \"library/dp/longest_increasing_subsequence.hpp\"\
    \n\nusing suisen::longest_decreasing_subsequence;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<int>\
    \ a(n);\n    for (auto &e : a) std::cin >> e, e = -e;\n\n    std::vector<int>\
    \ lis = longest_decreasing_subsequence(a);\n    \n    const int k = lis.size();\n\
    \    std::cout << k << std::endl;\n    for (int i = 0; i < k; ++i) {\n       \
    \ std::cout << lis[i];\n        if (i + 1 != k) std::cout << ' ';\n    }\n   \
    \ std::cout << std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/dp/longest_increasing_subsequence.hpp
  isVerificationFile: true
  path: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
  requiredBy: []
  timestamp: '2022-07-26 15:08:11+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
layout: document
redirect_from:
- /verify/test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
- /verify/test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp.html
title: test/src/dp/longest_increasing_subsequence/longest_increasing_subsequence_2.test.cpp
---
