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
  bundledCode: "#line 1 \"library/util/permutation.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\n    struct Permutation\
    \ : public std::vector<int> {\n        using base_type = std::vector<int>;\n \
    \       using base_type::base_type;\n\n        Permutation() : Permutation(0)\
    \ {}\n        Permutation(std::size_t n) : Permutation(int(n)) {}\n        Permutation(int\
    \ n) : base_type(n) {\n            std::iota(begin(), end(), 0);\n        }\n\
    \        Permutation(const std::vector<int>& a) : std::vector<int>(a) {}\n   \
    \     Permutation(std::vector<int>&& a) : std::vector<int>(std::move(a)) {}\n\n\
    \        // returns b s.t. b[i] = a[p[i]]\n        template <typename T>\n   \
    \     std::vector<T> permute(const std::vector<T>& a) const {\n            const\
    \ int n = a.size();\n            std::vector<T> res(n);\n            for (int\
    \ i = 0; i < n; ++i) res[i] = a[(*this)[i]];\n            return res;\n      \
    \  }\n        // returns b s.t. b[p[i]] = a[i]\n        template <typename T>\n\
    \        std::vector<T> inv_permute(const std::vector<T>& a) const {\n       \
    \     const int n = a.size();\n            std::vector<T> res(n);\n          \
    \  for (int i = 0; i < n; ++i) res[(*this)[i]] = a[i];\n            return res;\n\
    \        }\n\n        // returns p * q s.t. (p * q)[i] = p[q[i]]\n        friend\
    \ Permutation operator*(const Permutation& p, const Permutation& q) {\n      \
    \      return q.permute(p);\n        }\n        Permutation& operator*=(const\
    \ Permutation& q) {\n            return *this = *this * q;\n        }\n      \
    \  Permutation inv() const {\n            const int n = size();\n            Permutation\
    \ res(n);\n            for (int i = 0; i < n; ++i) res[(*this)[i]] = i;\n    \
    \        return res;\n        }\n        Permutation pow(long long k) const {\n\
    \            const int n = size();\n            Permutation res(n), p = *this;\n\
    \            for (; k; k >>= 1) {\n                if (k & 1) res *= p;\n    \
    \            p *= p;\n            }\n            return res;\n        }\n\n  \
    \      template <typename T, typename Comp = std::less<T>>\n        static Permutation\
    \ index_sort(const std::vector<T>& a, Comp comp = Comp{}) {\n            Permutation\
    \ p(a.size());\n            std::sort(p.begin(), p.end(), [&](int i, int j) {\
    \ return comp(a[i], a[j]); });\n            return p;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n"
  code: "#ifndef SUISEN_PERMUTATION\n#define SUISEN_PERMUTATION\n\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\n    struct Permutation\
    \ : public std::vector<int> {\n        using base_type = std::vector<int>;\n \
    \       using base_type::base_type;\n\n        Permutation() : Permutation(0)\
    \ {}\n        Permutation(std::size_t n) : Permutation(int(n)) {}\n        Permutation(int\
    \ n) : base_type(n) {\n            std::iota(begin(), end(), 0);\n        }\n\
    \        Permutation(const std::vector<int>& a) : std::vector<int>(a) {}\n   \
    \     Permutation(std::vector<int>&& a) : std::vector<int>(std::move(a)) {}\n\n\
    \        // returns b s.t. b[i] = a[p[i]]\n        template <typename T>\n   \
    \     std::vector<T> permute(const std::vector<T>& a) const {\n            const\
    \ int n = a.size();\n            std::vector<T> res(n);\n            for (int\
    \ i = 0; i < n; ++i) res[i] = a[(*this)[i]];\n            return res;\n      \
    \  }\n        // returns b s.t. b[p[i]] = a[i]\n        template <typename T>\n\
    \        std::vector<T> inv_permute(const std::vector<T>& a) const {\n       \
    \     const int n = a.size();\n            std::vector<T> res(n);\n          \
    \  for (int i = 0; i < n; ++i) res[(*this)[i]] = a[i];\n            return res;\n\
    \        }\n\n        // returns p * q s.t. (p * q)[i] = p[q[i]]\n        friend\
    \ Permutation operator*(const Permutation& p, const Permutation& q) {\n      \
    \      return q.permute(p);\n        }\n        Permutation& operator*=(const\
    \ Permutation& q) {\n            return *this = *this * q;\n        }\n      \
    \  Permutation inv() const {\n            const int n = size();\n            Permutation\
    \ res(n);\n            for (int i = 0; i < n; ++i) res[(*this)[i]] = i;\n    \
    \        return res;\n        }\n        Permutation pow(long long k) const {\n\
    \            const int n = size();\n            Permutation res(n), p = *this;\n\
    \            for (; k; k >>= 1) {\n                if (k & 1) res *= p;\n    \
    \            p *= p;\n            }\n            return res;\n        }\n\n  \
    \      template <typename T, typename Comp = std::less<T>>\n        static Permutation\
    \ index_sort(const std::vector<T>& a, Comp comp = Comp{}) {\n            Permutation\
    \ p(a.size());\n            std::sort(p.begin(), p.end(), [&](int i, int j) {\
    \ return comp(a[i], a[j]); });\n            return p;\n        }\n    };\n} //\
    \ namespace suisen\n\n#endif // SUISEN_PERMUTATION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/permutation.hpp
  requiredBy: []
  timestamp: '2021-10-16 19:54:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/permutation.hpp
layout: document
redirect_from:
- /library/library/util/permutation.hpp
- /library/library/util/permutation.hpp.html
title: library/util/permutation.hpp
---
