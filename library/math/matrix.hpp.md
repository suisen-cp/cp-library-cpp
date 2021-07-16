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
  bundledCode: "#line 1 \"library/math/matrix.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <typename T>\nclass matrix_ops {\n\
    \    public:\n        std::vector<std::vector<T>> E0(int n, int m) {\n       \
    \     std::vector<std::vector<T>> e0(n, std::vector<T>(m, _zero));\n         \
    \   return e0;\n        }\n        std::vector<std::vector<T>> E0(int n) {\n \
    \           std::vector<std::vector<T>> e0(n, std::vector<T>(n, _zero));\n   \
    \         return e0;\n        }\n        std::vector<std::vector<T>> E1(int n)\
    \ {\n            std::vector<std::vector<T>> e1(n, std::vector<T>(n, _zero));\n\
    \            for (int i = 0; i < n; ++i) e1[i][i] = _one;\n            return\
    \ e1;\n        }\n        std::vector<std::vector<T>> add(std::vector<std::vector<T>>&\
    \ A, std::vector<std::vector<T>>& B) {\n            int n = A.size(), m = A[0].size();\n\
    \            assert(int(B.size()) == n and int(B[0].size()) == m);\n         \
    \   std::vector<std::vector<T>> C = E0(n, m);\n            for (int i = 0; i <\
    \ n; ++i) for (int j = 0; j < m; ++j) {\n                C[i][j] = A[i][j] + B[i][j];\n\
    \            }\n            return C;\n        }\n        std::vector<std::vector<T>>\
    \ mul(std::vector<std::vector<T>>& A, std::vector<std::vector<T>>& B) {\n    \
    \        int n = A.size(), m = A[0].size(), l = B[0].size();\n            assert(int(B.size())\
    \ == m);\n            std::vector<std::vector<T>> C(n, std::vector<T>(l, _zero));\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int\
    \ k = 0; k < l; ++k)  {\n                C[i][k] += A[i][j] * B[j][k];\n     \
    \       }\n            return C;\n        }\n        std::vector<T> mul(std::vector<std::vector<T>>&\
    \ A, std::vector<T>& x) {\n            int n = A.size(), m = A[0].size();\n  \
    \          assert(m == int(x.size()));\n            std::vector<T> b(n, _zero);\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n     \
    \           b[i] += A[i][j] * x[j];\n            }\n            return b;\n  \
    \      }\n        std::vector<std::vector<T>> pow(std::vector<std::vector<T>>&\
    \ A, unsigned long long b) {\n            int n = A.size();\n            std::vector<std::vector<T>>\
    \ res = E1(n);\n            while (b) {\n                if (b & 1) res = mul(res,\
    \ A);\n                A = mul(A, A);\n                b >>= 1;\n            }\n\
    \            return res;\n        }\n    private:\n        T _zero = 0, _one =\
    \ 1;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MATRIX\n#define SUISEN_MATRIX\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <typename T>\nclass matrix_ops {\n\
    \    public:\n        std::vector<std::vector<T>> E0(int n, int m) {\n       \
    \     std::vector<std::vector<T>> e0(n, std::vector<T>(m, _zero));\n         \
    \   return e0;\n        }\n        std::vector<std::vector<T>> E0(int n) {\n \
    \           std::vector<std::vector<T>> e0(n, std::vector<T>(n, _zero));\n   \
    \         return e0;\n        }\n        std::vector<std::vector<T>> E1(int n)\
    \ {\n            std::vector<std::vector<T>> e1(n, std::vector<T>(n, _zero));\n\
    \            for (int i = 0; i < n; ++i) e1[i][i] = _one;\n            return\
    \ e1;\n        }\n        std::vector<std::vector<T>> add(std::vector<std::vector<T>>&\
    \ A, std::vector<std::vector<T>>& B) {\n            int n = A.size(), m = A[0].size();\n\
    \            assert(int(B.size()) == n and int(B[0].size()) == m);\n         \
    \   std::vector<std::vector<T>> C = E0(n, m);\n            for (int i = 0; i <\
    \ n; ++i) for (int j = 0; j < m; ++j) {\n                C[i][j] = A[i][j] + B[i][j];\n\
    \            }\n            return C;\n        }\n        std::vector<std::vector<T>>\
    \ mul(std::vector<std::vector<T>>& A, std::vector<std::vector<T>>& B) {\n    \
    \        int n = A.size(), m = A[0].size(), l = B[0].size();\n            assert(int(B.size())\
    \ == m);\n            std::vector<std::vector<T>> C(n, std::vector<T>(l, _zero));\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int\
    \ k = 0; k < l; ++k)  {\n                C[i][k] += A[i][j] * B[j][k];\n     \
    \       }\n            return C;\n        }\n        std::vector<T> mul(std::vector<std::vector<T>>&\
    \ A, std::vector<T>& x) {\n            int n = A.size(), m = A[0].size();\n  \
    \          assert(m == int(x.size()));\n            std::vector<T> b(n, _zero);\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n     \
    \           b[i] += A[i][j] * x[j];\n            }\n            return b;\n  \
    \      }\n        std::vector<std::vector<T>> pow(std::vector<std::vector<T>>&\
    \ A, unsigned long long b) {\n            int n = A.size();\n            std::vector<std::vector<T>>\
    \ res = E1(n);\n            while (b) {\n                if (b & 1) res = mul(res,\
    \ A);\n                A = mul(A, A);\n                b >>= 1;\n            }\n\
    \            return res;\n        }\n    private:\n        T _zero = 0, _one =\
    \ 1;\n};\n} // namespace suisen\n\n#endif // SUISEN_MATRIX\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/matrix.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/matrix.hpp
layout: document
redirect_from:
- /library/library/math/matrix.hpp
- /library/library/math/matrix.hpp.html
title: library/math/matrix.hpp
---
