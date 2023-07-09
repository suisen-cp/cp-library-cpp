---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
  bundledCode: "#line 1 \"test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\
    \nnamespace atcoder {\n    std::istream& operator>>(std::istream& in, mint &a)\
    \ {\n        long long e; in >> e; a = e;\n        return in;\n    }\n    \n \
    \   std::ostream& operator<<(std::ostream& out, const mint &a) {\n        out\
    \ << a.val();\n        return out;\n    }\n} // namespace atcoder\n\n#line 1 \"\
    library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T, typename U = T>\n    struct factorial\
    \ {\n        factorial() = default;\n        factorial(int n) { ensure(n); }\n\
    \n        static void ensure(const int n) {\n            int sz = _fac.size();\n\
    \            if (n + 1 <= sz) return;\n            int new_size = std::max(n +\
    \ 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 21 \"test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t, m;\n    std::cin >> t >> m;\n    mint::set_mod(m);\n\n    suisen::factorial<mint>\
    \ fac(std::min(m - 1, 10000000));\n    while (t --> 0) {\n        int n, k;\n\
    \        std::cin >> n >> k;\n        std::cout << fac.binom(n, k) << '\\n';\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\
    \nnamespace atcoder {\n    std::istream& operator>>(std::istream& in, mint &a)\
    \ {\n        long long e; in >> e; a = e;\n        return in;\n    }\n    \n \
    \   std::ostream& operator<<(std::ostream& out, const mint &a) {\n        out\
    \ << a.val();\n        return out;\n    }\n} // namespace atcoder\n\n#include\
    \ \"library/math/factorial.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t, m;\n    std::cin >> t >> m;\n    mint::set_mod(m);\n\
    \n    suisen::factorial<mint> fac(std::min(m - 1, 10000000));\n    while (t -->\
    \ 0) {\n        int n, k;\n        std::cin >> n >> k;\n        std::cout << fac.binom(n,\
    \ k) << '\\n';\n    }\n}"
  dependsOn:
  - library/math/factorial.hpp
  isVerificationFile: true
  path: test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp
- /verify/test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp.html
title: test/src/math/factorial/binomial_coefficient_prime_mod.test.cpp
---
