---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/dp/number_of_subsequences.hpp
    title: library/dp/number_of_subsequences.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/number_of_subsequences
    links:
    - https://judge.yosupo.jp/problem/number_of_subsequences
  bundledCode: "#line 1 \"test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_subsequences\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/dp/number_of_subsequences.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    //\
    \ Requirement: T is comparable \n    template <typename Int, typename T>\n   \
    \ auto number_of_nonempty_subsequences(const std::vector<T> &a) -> decltype(std::declval<T>()\
    \ < std::declval<T>(), Int{}) {\n        const int n = a.size();\n        std::vector<std::pair<T,\
    \ int>> sorted(n);\n        for (int i = 0; i < n; ++i) sorted[i] = { a[i], i\
    \ };\n        std::sort(sorted.begin(), sorted.end());\n\n        std::vector<int>\
    \ last(n, -1);\n        for (int i = 0; i < n;) {\n            for (auto [v, p]\
    \ = sorted[i]; ++i < n and sorted[i].first == v;) {\n                const int\
    \ c = sorted[i].second;\n                last[c] = std::exchange(p, c);\n    \
    \        }\n        }\n\n        std::vector<Int> sdp(n + 2);\n        sdp[1]\
    \ = 1;\n        for (int i = 0; i < n; ++i) sdp[i + 2] = sdp[i + 1] + sdp[i +\
    \ 1] - sdp[last[i] + 1];\n        return sdp[n + 1] - 1;\n    }\n} // namespace\
    \ suisen\n\n\n#line 7 \"test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<int> a(n);\n    for (auto\
    \ &e : a) std::cin >> e;\n\n    std::cout << suisen::number_of_nonempty_subsequences<atcoder::modint998244353>(a).val()\
    \ << '\\n';\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_subsequences\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/dp/number_of_subsequences.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<int> a(n);\n    for (auto\
    \ &e : a) std::cin >> e;\n\n    std::cout << suisen::number_of_nonempty_subsequences<atcoder::modint998244353>(a).val()\
    \ << '\\n';\n\n    return 0;\n}"
  dependsOn:
  - library/dp/number_of_subsequences.hpp
  isVerificationFile: true
  path: test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
  requiredBy: []
  timestamp: '2022-07-26 15:37:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
layout: document
redirect_from:
- /verify/test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
- /verify/test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp.html
title: test/src/dp/number_of_subsequences/number_of_subsequences.test.cpp
---
