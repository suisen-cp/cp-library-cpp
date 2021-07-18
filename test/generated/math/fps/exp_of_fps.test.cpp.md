---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':x:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "#line 1 \"test/generated/math/fps/exp_of_fps.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/exp_of_formal_power_series\"\n\n#include <iostream>\n\
    #include <vector>\n\n#include <atcoder/modint>\n\n#include <library/math/fps.hpp>\n\
    \nusing mint = atcoder::modint998244353;\n\nint main() {\n    int n;\n    std::cin\
    \ >> n;\n    suisen::FPS<mint> f(n);\n    for (int i = 0; i < n; ++i) {\n    \
    \    int coef;\n        std::cin >> coef;\n        f[i] = coef;\n    }\n    auto\
    \ g = f.exp(n - 1);\n    for (int i = 0; i < n; ++i) {\n        std::cout << g[i].val()\
    \ << \" \\n\"[i == n - 1];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_formal_power_series\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include <atcoder/modint>\n\n#include\
    \ <library/math/fps.hpp>\n\nusing mint = atcoder::modint998244353;\n\nint main()\
    \ {\n    int n;\n    std::cin >> n;\n    suisen::FPS<mint> f(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int coef;\n        std::cin >> coef;\n       \
    \ f[i] = coef;\n    }\n    auto g = f.exp(n - 1);\n    for (int i = 0; i < n;\
    \ ++i) {\n        std::cout << g[i].val() << \" \\n\"[i == n - 1];\n    }\n  \
    \  return 0;\n}\n"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: true
  path: test/generated/math/fps/exp_of_fps.test.cpp
  requiredBy: []
  timestamp: '2021-07-18 16:50:59+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/generated/math/fps/exp_of_fps.test.cpp
layout: document
redirect_from:
- /verify/test/generated/math/fps/exp_of_fps.test.cpp
- /verify/test/generated/math/fps/exp_of_fps.test.cpp.html
title: test/generated/math/fps/exp_of_fps.test.cpp
---
