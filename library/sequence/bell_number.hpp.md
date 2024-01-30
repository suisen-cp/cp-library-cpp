---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/bell_number.hpp\"\n\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, typename U = T>\n    struct factorial {\n        factorial() =\
    \ default;\n        factorial(int n) { ensure(n); }\n\n        static void ensure(const\
    \ int n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n\n        T fac(const int i) {\n            ensure(i);\n\
    \            return _fac[i];\n        }\n        T operator()(int i) {\n     \
    \       return fac(i);\n        }\n        U fac_inv(const int i) {\n        \
    \    ensure(i);\n            return _fac_inv[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return _fac[n] * _fac_inv[r] * _fac_inv[n\
    \ - r];\n        }\n        template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        U polynom(const int n, const Ds& ...ds)\
    \ {\n            if (n < 0) return 0;\n            ensure(n);\n            int\
    \ sumd = 0;\n            U res = _fac[n];\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= _fac_inv[d];\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= _fac_inv[n - sumd];\n            return res;\n\
    \        }\n        U perm(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return _fac[n]\
    \ * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T> _fac;\n\
    \        static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 5 \"library/sequence/bell_number.hpp\"\n\nnamespace suisen\
    \ {\n    /**\n     * return:\n     *   vector<mint> v s.t. v[i] = B_i = \u03A3\
    _j S2[i,j] for i=0,...,n\n     * constraints:\n     *   0 <= n <= 10^6\n     *\
    \ note:\n     *   EGF of B is e^(e^x-1)\n     */\n    template <typename FPSType>\n\
    \    std::vector<typename FPSType::value_type> bell_number(int n) {\n        using\
    \ mint = typename FPSType::value_type;\n        factorial<mint> fac(n);\n    \
    \    FPSType f(n + 1);\n        for (int i = 1; i <= n; ++i) f[i] = fac.fac_inv(i);\n\
    \        f.exp_inplace(n);\n        for (int i = 0; i <= n; ++i) f[i] *= fac.fac(i);\n\
    \        return f;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BELL_NUMBER\n#define SUISEN_BELL_NUMBER\n\n#include \"library/math/factorial.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * return:\n     *   vector<mint> v s.t.\
    \ v[i] = B_i = \u03A3_j S2[i,j] for i=0,...,n\n     * constraints:\n     *   0\
    \ <= n <= 10^6\n     * note:\n     *   EGF of B is e^(e^x-1)\n     */\n    template\
    \ <typename FPSType>\n    std::vector<typename FPSType::value_type> bell_number(int\
    \ n) {\n        using mint = typename FPSType::value_type;\n        factorial<mint>\
    \ fac(n);\n        FPSType f(n + 1);\n        for (int i = 1; i <= n; ++i) f[i]\
    \ = fac.fac_inv(i);\n        f.exp_inplace(n);\n        for (int i = 0; i <= n;\
    \ ++i) f[i] *= fac.fac(i);\n        return f;\n    }\n} // namespace suisen\n\n\
    #endif // SUISEN_BELL_NUMBER\n"
  dependsOn:
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/sequence/bell_number.hpp
  requiredBy: []
  timestamp: '2024-01-30 20:57:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/sequence/bell_number.hpp
layout: document
title: Bell Number
---
## Bell Number