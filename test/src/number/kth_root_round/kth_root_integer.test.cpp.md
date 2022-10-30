---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/kth_root_round.hpp
    title: $\lfloor a ^ {\frac{1}{k}}\rfloor, \lceil a ^ {\frac{1}{k}}\rceil$
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_root_integer
    links:
    - https://judge.yosupo.jp/problem/kth_root_integer
  bundledCode: "#line 1 \"test/src/number/kth_root_round/kth_root_integer.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_integer\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/number/kth_root_round.hpp\"\n\n\n\n#include\
    \ <cmath>\n#include <type_traits>\n\nnamespace suisen {\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    T\
    \ floor_kth_root(T x, int k) {\n        if (k == 1 or x == 0 or x == 1) return\
    \ x;\n        if (k == 2) return ::sqrtl(x);\n        if (k >= 64) return 1;\n\
    \        T res = ::powl(x, ::nextafterl(1 / (long double) k, 0));\n        while\
    \ (::powl(res + 1, k) <= x) ++res;\n        return res;\n    }\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    T\
    \ ceil_kth_root(T x, int k) {\n        T res = floor_kth_root(x, k);\n       \
    \ res += ::powl(res, k) < x;\n        return res;\n    }\n} // namespace suisen\n\
    \n\n\n#line 6 \"test/src/number/kth_root_round/kth_root_integer.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n    while (t --> 0) {\n        uint64_t a;\n\
    \        int k;\n        std::cin >> a >> k;\n        std::cout << suisen::floor_kth_root(a,\
    \ k) << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_integer\"\n\n\
    #include <iostream>\n\n#include \"library/number/kth_root_round.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int t;\n    std::cin >> t;\n    while (t --> 0) {\n        uint64_t a;\n   \
    \     int k;\n        std::cin >> a >> k;\n        std::cout << suisen::floor_kth_root(a,\
    \ k) << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/number/kth_root_round.hpp
  isVerificationFile: true
  path: test/src/number/kth_root_round/kth_root_integer.test.cpp
  requiredBy: []
  timestamp: '2022-10-31 01:25:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/kth_root_round/kth_root_integer.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/kth_root_round/kth_root_integer.test.cpp
- /verify/test/src/number/kth_root_round/kth_root_integer.test.cpp.html
title: test/src/number/kth_root_round/kth_root_integer.test.cpp
---
