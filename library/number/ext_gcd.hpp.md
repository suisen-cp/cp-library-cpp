---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':question:'
    path: library/number/garner.hpp
    title: Garner's Algorithm
  - icon: ':warning:'
    path: library/number/index_calculus.hpp
    title: Index Calculus
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/ext_gcd.hpp\"\n\n\n\n#include <cassert>\n\
    #include <tuple>\n#include <utility>\n\nnamespace suisen {\nconstexpr long long\
    \ safe_mod(long long x, long long m) {\n    x %= m;\n    return x < 0 ? x + m\
    \ : x;\n}\n\n// returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \nstd::tuple<long long,\
    \ long long, long long> ext_gcd(long long a, long long b) {\n    long long x =\
    \ 1, y = 0;\n    long long z = 0, w = 1;\n    long long tmp;\n    while (b) {\n\
    \        long long p = a / b, q = a % b;\n        tmp = x - y * p; x = y; y =\
    \ tmp;\n        tmp = z - w * p; z = w; w = tmp;\n        a = b; b = q;\n    }\n\
    \    if (a >= 0) return {x, z, a};\n    else return {-x, -z, -a};\n}\n\n// returns\
    \ {x,g} s.t. a*x=g (mod m)\nstd::pair<long long, long long> gcd_inv(long long\
    \ a, long long m) {\n    auto [x, y, g] = ext_gcd(a, m);\n    return {safe_mod(x,\
    \ m), g};\n}\n\n// returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime\
    \ error.\nlong long inv_mod(long long a, long long mod) {\n    auto [inv, y, g]\
    \ = ext_gcd(a, mod);\n    assert(g == 1);\n    return safe_mod(inv, mod);\n}\n\
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_EXT_GCD\n#define SUISEN_EXT_GCD\n\n#include <cassert>\n#include\
    \ <tuple>\n#include <utility>\n\nnamespace suisen {\nconstexpr long long safe_mod(long\
    \ long x, long long m) {\n    x %= m;\n    return x < 0 ? x + m : x;\n}\n\n//\
    \ returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \nstd::tuple<long long, long long,\
    \ long long> ext_gcd(long long a, long long b) {\n    long long x = 1, y = 0;\n\
    \    long long z = 0, w = 1;\n    long long tmp;\n    while (b) {\n        long\
    \ long p = a / b, q = a % b;\n        tmp = x - y * p; x = y; y = tmp;\n     \
    \   tmp = z - w * p; z = w; w = tmp;\n        a = b; b = q;\n    }\n    if (a\
    \ >= 0) return {x, z, a};\n    else return {-x, -z, -a};\n}\n\n// returns {x,g}\
    \ s.t. a*x=g (mod m)\nstd::pair<long long, long long> gcd_inv(long long a, long\
    \ long m) {\n    auto [x, y, g] = ext_gcd(a, m);\n    return {safe_mod(x, m),\
    \ g};\n}\n\n// returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime\
    \ error.\nlong long inv_mod(long long a, long long mod) {\n    auto [inv, y, g]\
    \ = ext_gcd(a, mod);\n    assert(g == 1);\n    return safe_mod(inv, mod);\n}\n\
    } // namespace suisen\n\n#endif // SUISEN_EXT_GCD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/ext_gcd.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  - library/number/index_calculus.hpp
  - library/number/garner.hpp
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
documentation_of: library/number/ext_gcd.hpp
layout: document
title: Ext Gcd
---
## Ext Gcd