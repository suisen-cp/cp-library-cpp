---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
    title: test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/min_of_mod_of_linear.hpp\"\n\n\n\n#include\
    \ <numeric>\n#include <vector>\n\n#include <atcoder/math>\n\nnamespace suisen\
    \ {\n    // min{ (ax+b) mod m | 0<=x<n }\n    int min_of_mod_of_linear(int n,\
    \ int m, int a, int b) {\n        // let k be an integer s.t. 0<=k<m.\n      \
    \  //     ax+b mod M <= k\n        // <=> (ax+b-k)/m <= floor((ax+b)/m)\n    \
    \    // <=> floor((ax+b+(m-1-k))/m) <= floor((ax+b)/m)\n        // <=> floor((ax+b+(m-1-k))/m)\
    \  = floor((ax+b)/m)    (because 0<=m-1-k<m)\n\n        // if there exists an\
    \ integer x in [0,n) s.t. floor((ax+b+(m-1-k))/m) = floor((ax+b)/m),\n       \
    \ //   floor_sum(n, m, a, b+(m-1-k)) < floor_sum(n, m, a, b) + n\n        // holds.\n\
    \n        // Applying binary search on k, we can get min{ (ax+b) mod m | 0<=x<n\
    \ } in O((log m)^2) time.\n\n        long long v = atcoder::floor_sum(n, m, a,\
    \ b) + n;\n\n        int l = -1, r = m - 1;\n        while (r - l > 1) {\n   \
    \         int k = (l + r) >> 1;\n            if (atcoder::floor_sum(n, m, a, b\
    \ + (m - 1 - k)) < v) {\n                r = k;\n            } else {\n      \
    \          l = k;\n            }\n        }\n        return r;\n    }\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_MIN_OF_MOD_OF_LINEAR\n#define SUISEN_MIN_OF_MOD_OF_LINEAR\n\
    \n#include <numeric>\n#include <vector>\n\n#include <atcoder/math>\n\nnamespace\
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
    \ suisen\n\n\n#endif // SUISEN_MIN_OF_MOD_OF_LINEAR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/min_of_mod_of_linear.hpp
  requiredBy: []
  timestamp: '2023-01-02 12:13:30+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/number/min_of_mod_of_linear/min_of_mod_of_linear.test.cpp
documentation_of: library/number/min_of_mod_of_linear.hpp
layout: document
redirect_from:
- /library/library/number/min_of_mod_of_linear.hpp
- /library/library/number/min_of_mod_of_linear.hpp.html
title: library/number/min_of_mod_of_linear.hpp
---
