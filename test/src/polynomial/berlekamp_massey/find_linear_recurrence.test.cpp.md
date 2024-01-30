---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/polynomial/berlekamp_massey.hpp
    title: "Berlekamp Massey (\u7DDA\u5F62\u56DE\u5E30\u6570\u5217\u306E\u4FC2\u6570\
      \u8A08\u7B97)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/find_linear_recurrence
    links:
    - https://judge.yosupo.jp/problem/find_linear_recurrence
  bundledCode: "#line 1 \"test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/polynomial/berlekamp_massey.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    /**\n\
    \     * @brief Find linear recurrence in O(|s|^2) time\n     * @tparam F Arbitrary\
    \ field (operator +, -, *, /, +=, -=, *=, /= must be defined)\n     * @param s\
    \ Prefix of a linearly reccurent sequence\n     * @return The vector of length\
    \ L+1 c s.t. c_0=1 and s_i=Sum[j=1,L]c_i*s_{i-j} for all i>=L, where L is the\
    \ minimum integer s.t. there exists such c of length L+1.\n     */\n    template\
    \ <typename F>\n    std::vector<F> find_linear_recuurence(const std::vector<F>&\
    \ s) {\n        std::vector<F> B{ 1 }, C{ 1 };\n        B.reserve(s.size()), C.reserve(s.size());\n\
    \        F b = 1;\n        std::size_t L = 0;\n        for (std::size_t N = 0,\
    \ x = 1; N < s.size(); ++N) {\n            F d = s[N];\n            for (std::size_t\
    \ i = 1; i <= L; ++i) d += C[i] * s[N - i];\n            if (d == 0) {\n     \
    \           ++x;\n            } else {\n                F c = d / b;\n       \
    \         if (C.size() < B.size() + x) C.resize(B.size() + x);\n             \
    \   if (2 * L > N) {\n                    for (std::size_t i = 0; i < B.size();\
    \ ++i) C[x + i] -= c * B[i];\n                    ++x;\n                } else\
    \ {\n                    std::vector<F> T = C;\n                    for (std::size_t\
    \ i = 0; i < B.size(); ++i) C[x + i] -= c * B[i];\n                    L = N +\
    \ 1 - L, B = std::move(T), b = d, x = 1;\n                }\n            }\n \
    \       }\n        C.resize(L + 1);\n        for (std::size_t N = 1; N <= L; ++N)\
    \ C[N] = -C[N];\n        return C;\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 7 \"test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp\"\n\
    \nusing mint = atcoder::modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::size_t n;\n    std::cin >> n;\n    std::vector<mint>\
    \ s(n);\n    for (auto &e : s) {\n        int v;\n        std::cin >> v, e = v;\n\
    \    }\n    std::vector<mint> C = suisen::find_linear_recuurence(s);\n    std::cout\
    \ << C.size() - 1 << '\\n';\n    for (std::size_t i = 1; i < C.size(); ++i) {\n\
    \        std::cout << C[i].val();\n        if (i + 1 != C.size()) std::cout <<\
    \ ' ';\n    }\n    std::cout << '\\n';\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/polynomial/berlekamp_massey.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::size_t n;\n    std::cin >> n;\n    std::vector<mint>\
    \ s(n);\n    for (auto &e : s) {\n        int v;\n        std::cin >> v, e = v;\n\
    \    }\n    std::vector<mint> C = suisen::find_linear_recuurence(s);\n    std::cout\
    \ << C.size() - 1 << '\\n';\n    for (std::size_t i = 1; i < C.size(); ++i) {\n\
    \        std::cout << C[i].val();\n        if (i + 1 != C.size()) std::cout <<\
    \ ' ';\n    }\n    std::cout << '\\n';\n\n    return 0;\n}"
  dependsOn:
  - library/polynomial/berlekamp_massey.hpp
  isVerificationFile: true
  path: test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 20:59:32+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
- /verify/test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp.html
title: test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
---
