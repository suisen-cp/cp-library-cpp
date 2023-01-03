---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/number/min_of_mod_of_linear.hpp
    title: library/number/min_of_mod_of_linear.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_of_mod_of_linear
    links:
    - https://judge.yosupo.jp/problem/min_of_mod_of_linear
  bundledCode: "#line 1 \"test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_of_mod_of_linear\"\n\n\
    #include <iostream>\n\n#line 1 \"library/number/min_of_mod_of_linear.hpp\"\n\n\
    \n\n#include <numeric>\n#include <vector>\n\n#include <atcoder/math>\n\nnamespace\
    \ suisen {\n    // min{ (ax+b) mod m | 0<=x<n }\n    int min_of_mod_of_linear(int\
    \ n, int m, int a, int b) {\n        // let k be an integer s.t. 0<=k<m.\n   \
    \     //     ax+b mod M <= k\n        // <=> (ax+b-k)/m <= floor((ax+b)/m)\n \
    \       // <=> floor((ax+b+(m-1-k))/m) <= floor((ax+b)/m)\n        // <=> floor((ax+b+(m-1-k))/m)\
    \  = floor((ax+b)/m)    (because 0<=m-1-k<m)\n\n        // if there exists an\
    \ integer x in [0,n) s.t. floor((ax+b+(m-1-k))/m) = floor((ax+b)/m),\n       \
    \ //   floor_sum(n, m, a, b+(m-1-k)) < floor_sum(n, m, a, b) + n\n        // holds.\n\
    \n        // Applying binary search on k, we can get min{ (ax+b) mod m | 0<=x<n\
    \ } in O((log m)^2) time.\n\n        long long v = atcoder::floor_sum(n, m, a,\
    \ b) + n;\n\n        int l = -1, r = m - 1;\n        while (r - l > 1) {\n   \
    \         int k = (l + r) >> 1;\n            if (atcoder::floor_sum(n, m, a, b\
    \ + (m - 1 - k)) < v) {\n                r = k;\n            } else {\n      \
    \          l = k;\n            }\n        }\n        return r;\n    }\n} // namespace\
    \ suisen\n\n\n\n#line 6 \"test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n\n    for (int test_case_id = 0; test_case_id\
    \ < t; ++test_case_id) {\n        int n, m, a, b;\n        std::cin >> n >> m\
    \ >> a >> b;\n        \n        std::cout << suisen::min_of_mod_of_linear(n, m,\
    \ a, b) << std::endl;\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_of_mod_of_linear\"\n\
    \n#include <iostream>\n\n#include \"library/number/min_of_mod_of_linear.hpp\"\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n\n    for (int test_case_id = 0; test_case_id\
    \ < t; ++test_case_id) {\n        int n, m, a, b;\n        std::cin >> n >> m\
    \ >> a >> b;\n        \n        std::cout << suisen::min_of_mod_of_linear(n, m,\
    \ a, b) << std::endl;\n    }\n}"
  dependsOn:
  - library/number/min_of_mod_of_linear.hpp
  isVerificationFile: true
  path: test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
  requiredBy: []
  timestamp: '2023-01-02 12:13:30+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
- /verify/test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp.html
title: test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
---
