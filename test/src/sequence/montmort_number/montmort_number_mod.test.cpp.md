---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/sequence/montmort_number.hpp
    title: Montmort Number
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/montmort_number_mod
    links:
    - https://judge.yosupo.jp/problem/montmort_number_mod
  bundledCode: "#line 1 \"test/src/sequence/montmort_number/montmort_number_mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\nusing mint = atcoder::modint;\n\
    \n#line 1 \"library/sequence/montmort_number.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    template <typename mint>\n    std::vector<mint> montmort_number(int\
    \ n) {\n        std::vector<mint> res{ 1, 0 };\n        for (int i = 2; i <= n;\
    \ ++i) res.push_back((i - 1) * (res[i - 1] + res[i - 2]));\n        res.resize(n\
    \ + 1);\n        return res;\n    }\n} // namespace suisen\n\n\n#line 8 \"test/src/sequence/montmort_number/montmort_number_mod.test.cpp\"\
    \nusing suisen::montmort_number;\n\nint main() {\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    mint::set_mod(m);\n    std::vector<mint> res = montmort_number<mint>(n);\n\
    \    for (int i = 1; i <= n; ++i) {\n        std::cout << res[i].val() << \" \\\
    n\"[i == n];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\nusing mint = atcoder::modint;\n\
    \n#include \"library/sequence/montmort_number.hpp\"\nusing suisen::montmort_number;\n\
    \nint main() {\n    int n, m;\n    std::cin >> n >> m;\n    mint::set_mod(m);\n\
    \    std::vector<mint> res = montmort_number<mint>(n);\n    for (int i = 1; i\
    \ <= n; ++i) {\n        std::cout << res[i].val() << \" \\n\"[i == n];\n    }\n\
    \    return 0;\n}"
  dependsOn:
  - library/sequence/montmort_number.hpp
  isVerificationFile: true
  path: test/src/sequence/montmort_number/montmort_number_mod.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 22:02:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/sequence/montmort_number/montmort_number_mod.test.cpp
layout: document
redirect_from:
- /verify/test/src/sequence/montmort_number/montmort_number_mod.test.cpp
- /verify/test/src/sequence/montmort_number/montmort_number_mod.test.cpp.html
title: test/src/sequence/montmort_number/montmort_number_mod.test.cpp
---
