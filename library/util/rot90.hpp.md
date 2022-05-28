---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/rot90.hpp\"\n\n\n\n#include <string>\n#include\
    \ <vector>\n\nnamespace suisen {\n    /**\n     * O|             O|       \n \
    \    * -+------->j    -+----->j\n     *  | a c e    =>  | e f   \n     *  | b\
    \ d f        | c d   \n     *  v              | a b   \n     *   i           \
    \  v       \n     *                  i      \n     */\n    template <typename\
    \ T>\n    std::vector<std::vector<T>> rot90(const std::vector<std::vector<T>>\
    \ &A) {\n        if (A.empty()) return A;\n        const int N = A.size(), M =\
    \ A[0].size();\n        std::vector<std::vector<T>> B(M, std::vector<T>(N));\n\
    \        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][M\
    \ - j - 1];\n        return B;\n    }\n    std::vector<std::string> rot90(const\
    \ std::vector<std::string> &A) {\n        if (A.empty()) return A;\n        const\
    \ int N = A.size(), M = A[0].size();\n        std::vector<std::string> B(M, std::string(N,\
    \ '\\0'));\n        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i]\
    \ = A[i][M - j - 1];\n        return B;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ROT_90\n#define SUISEN_ROT_90\n\n#include <string>\n#include\
    \ <vector>\n\nnamespace suisen {\n    /**\n     * O|             O|       \n \
    \    * -+------->j    -+----->j\n     *  | a c e    =>  | e f   \n     *  | b\
    \ d f        | c d   \n     *  v              | a b   \n     *   i           \
    \  v       \n     *                  i      \n     */\n    template <typename\
    \ T>\n    std::vector<std::vector<T>> rot90(const std::vector<std::vector<T>>\
    \ &A) {\n        if (A.empty()) return A;\n        const int N = A.size(), M =\
    \ A[0].size();\n        std::vector<std::vector<T>> B(M, std::vector<T>(N));\n\
    \        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][M\
    \ - j - 1];\n        return B;\n    }\n    std::vector<std::string> rot90(const\
    \ std::vector<std::string> &A) {\n        if (A.empty()) return A;\n        const\
    \ int N = A.size(), M = A[0].size();\n        std::vector<std::string> B(M, std::string(N,\
    \ '\\0'));\n        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i]\
    \ = A[i][M - j - 1];\n        return B;\n    }\n} // namespace suisen\n\n\n#endif\
    \ // SUISEN_ROT_90\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/rot90.hpp
  requiredBy: []
  timestamp: '2022-05-28 20:11:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/rot90.hpp
layout: document
title: Rot90
---
## Rot90