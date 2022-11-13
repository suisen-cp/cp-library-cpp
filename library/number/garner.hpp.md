---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/number/ext_gcd.hpp
    title: Ext Gcd
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: Multi Variate Convolution Circular
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':x:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime
      each other.
    links: []
  bundledCode: "#line 1 \"library/number/garner.hpp\"\n\n\n\n#include <vector>\n#line\
    \ 1 \"library/number/ext_gcd.hpp\"\n\n\n\n#include <cassert>\n#include <tuple>\n\
    #include <utility>\n\nnamespace suisen {\nconstexpr long long safe_mod(long long\
    \ x, long long m) {\n    x %= m;\n    return x < 0 ? x + m : x;\n}\n\n// returns\
    \ {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \nstd::tuple<long long, long long, long long>\
    \ ext_gcd(long long a, long long b) {\n    long long x = 1, y = 0;\n    long long\
    \ z = 0, w = 1;\n    long long tmp;\n    while (b) {\n        long long p = a\
    \ / b, q = a % b;\n        tmp = x - y * p; x = y; y = tmp;\n        tmp = z -\
    \ w * p; z = w; w = tmp;\n        a = b; b = q;\n    }\n    if (a >= 0) return\
    \ {x, z, a};\n    else return {-x, -z, -a};\n}\n\n// returns {x,g} s.t. a*x=g\
    \ (mod m)\nstd::pair<long long, long long> gcd_inv(long long a, long long m) {\n\
    \    auto [x, y, g] = ext_gcd(a, m);\n    return {safe_mod(x, m), g};\n}\n\n//\
    \ returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime error.\nlong\
    \ long inv_mod(long long a, long long mod) {\n    auto [inv, y, g] = ext_gcd(a,\
    \ mod);\n    assert(g == 1);\n    return safe_mod(inv, mod);\n}\n} // namespace\
    \ suisen\n\n\n#line 6 \"library/number/garner.hpp\"\n\nnamespace suisen {\n  \
    \  /**\n     * @brief Calculates x mod m s.t. x = x_i (mod m_i). m_i should be\
    \ coprime each other.\n     * @param eq vector of { x_i, m_i }\n     * @return\
    \ x mod m s.t. x = x_i (mod m_i)\n     */\n    int garner(std::vector<std::pair<int,\
    \ int>> eq, int m) {\n        const int n = eq.size();\n        std::vector<long\
    \ long> a(n);\n\n        auto calc_prefix = [&](int i, long long mod) {\n    \
    \        long long res = 0;\n            for (int j = 0; j < i; ++j) {\n     \
    \           long long t = a[j];\n                for (int k = 0; k < j; ++k) {\n\
    \                    long long mk = eq[k].second;\n                    t *= mk;\n\
    \                    t %= mod;\n                }\n                res += t;\n\
    \                if (res >= mod) res -= mod;\n            }\n            return\
    \ res;\n        };\n    \n        for (int i = 0; i < n; ++i) {\n            auto\
    \ [xi, mi] = eq[i];\n            a[i] = (xi - calc_prefix(i, mi)) % mi;\n    \
    \        if (a[i] < 0) a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n\
    \                long long mj = eq[j].second;\n                a[i] *= inv_mod(mj,\
    \ mi);\n                a[i] %= mi;\n            }\n        }\n        return\
    \ calc_prefix(n, m);\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_GARNER\n#define SUISEN_GARNER\n\n#include <vector>\n#include\
    \ \"library/number/ext_gcd.hpp\"\n\nnamespace suisen {\n    /**\n     * @brief\
    \ Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime each other.\n\
    \     * @param eq vector of { x_i, m_i }\n     * @return x mod m s.t. x = x_i\
    \ (mod m_i)\n     */\n    int garner(std::vector<std::pair<int, int>> eq, int\
    \ m) {\n        const int n = eq.size();\n        std::vector<long long> a(n);\n\
    \n        auto calc_prefix = [&](int i, long long mod) {\n            long long\
    \ res = 0;\n            for (int j = 0; j < i; ++j) {\n                long long\
    \ t = a[j];\n                for (int k = 0; k < j; ++k) {\n                 \
    \   long long mk = eq[k].second;\n                    t *= mk;\n             \
    \       t %= mod;\n                }\n                res += t;\n            \
    \    if (res >= mod) res -= mod;\n            }\n            return res;\n   \
    \     };\n    \n        for (int i = 0; i < n; ++i) {\n            auto [xi, mi]\
    \ = eq[i];\n            a[i] = (xi - calc_prefix(i, mi)) % mi;\n            if\
    \ (a[i] < 0) a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n        \
    \        long long mj = eq[j].second;\n                a[i] *= inv_mod(mj, mi);\n\
    \                a[i] %= mi;\n            }\n        }\n        return calc_prefix(n,\
    \ m);\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_GARNER\n"
  dependsOn:
  - library/number/ext_gcd.hpp
  isVerificationFile: false
  path: library/number/garner.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  timestamp: '2022-11-13 03:53:58+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
documentation_of: library/number/garner.hpp
layout: document
title: Garner
---
## Garner
