---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
    title: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/bostan_mori.hpp\"\n\n\n\nnamespace suisen\
    \ {\n    template <typename FPSType>\n    typename FPSType::value_type bostan_mori(FPSType\
    \ P, FPSType Q, unsigned long long n) {\n        auto alternate = [](FPSType&&\
    \ a, bool odd) -> FPSType&& {\n            int i = 0;\n            for (int j\
    \ = odd; j < int(a.size()); j += 2) a[i++] = a[j];\n            a.erase(a.begin()\
    \ + i, a.end());\n            return std::move(a);\n        };\n        for (;\
    \ n; n >>= 1) {\n            if (n < (unsigned long long)(P.size())) P.resize(n\
    \ + 1);\n            if (n < (unsigned long long)(Q.size())) Q.resize(n + 1);\n\
    \            FPSType mQ = Q;\n            for (int i = 1; i < int(Q.size()); i\
    \ += 2) mQ[i] = -mQ[i];\n            P = alternate(P * mQ, n & 1);\n         \
    \   Q = alternate(Q * mQ, 0);\n        }\n        return P.size() ? P[0] / Q[0]\
    \ : 0;\n    }\n\n    template <typename FPSType>\n    typename FPSType::value_type\
    \ nth_term_of_linearly_recurrent_sequence(const FPSType& a, const FPSType& c,\
    \ const unsigned long long n) {\n        const int K = c.size();\n        assert(K\
    \ <= a.size());\n        FPSType Q(K + 1);\n        Q[0] = 1;\n        for (int\
    \ i = 0; i < K; ++i) {\n            Q[i + 1] = -c[i];\n        }\n        FPSType\
    \ P = a * Q;\n        P.cut(K);\n        return bostan_mori(P, Q, n);\n    }\n\
    \n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BOSTAN_MORI\n#define SUISEN_BOSTAN_MORI\n\nnamespace suisen\
    \ {\n    template <typename FPSType>\n    typename FPSType::value_type bostan_mori(FPSType\
    \ P, FPSType Q, unsigned long long n) {\n        auto alternate = [](FPSType&&\
    \ a, bool odd) -> FPSType&& {\n            int i = 0;\n            for (int j\
    \ = odd; j < int(a.size()); j += 2) a[i++] = a[j];\n            a.erase(a.begin()\
    \ + i, a.end());\n            return std::move(a);\n        };\n        for (;\
    \ n; n >>= 1) {\n            if (n < (unsigned long long)(P.size())) P.resize(n\
    \ + 1);\n            if (n < (unsigned long long)(Q.size())) Q.resize(n + 1);\n\
    \            FPSType mQ = Q;\n            for (int i = 1; i < int(Q.size()); i\
    \ += 2) mQ[i] = -mQ[i];\n            P = alternate(P * mQ, n & 1);\n         \
    \   Q = alternate(Q * mQ, 0);\n        }\n        return P.size() ? P[0] / Q[0]\
    \ : 0;\n    }\n\n    template <typename FPSType>\n    typename FPSType::value_type\
    \ nth_term_of_linearly_recurrent_sequence(const FPSType& a, const FPSType& c,\
    \ const unsigned long long n) {\n        const int K = c.size();\n        assert(K\
    \ <= a.size());\n        FPSType Q(K + 1);\n        Q[0] = 1;\n        for (int\
    \ i = 0; i < K; ++i) {\n            Q[i + 1] = -c[i];\n        }\n        FPSType\
    \ P = a * Q;\n        P.cut(K);\n        return bostan_mori(P, Q, n);\n    }\n\
    \n} // namespace suisen\n\n#endif // SUISEN_BOSTAN_MORI"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/bostan_mori.hpp
  requiredBy: []
  timestamp: '2024-01-30 21:00:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
  - test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
documentation_of: library/polynomial/bostan_mori.hpp
layout: document
title: Bostan Mori
---
## Bostan Mori