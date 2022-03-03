---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "#line 1 \"test/src/convolution/subset_convolution/subset_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n#include\
    \ <iostream>\n#include <atcoder/convolution>\n#include <atcoder/modint>\n\n#line\
    \ 1 \"library/convolution/subset_convolution.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    namespace internal::subset_convolution {\n        template\
    \ <typename T>\n        std::vector<T>& addeq(std::vector<T> &a, const std::vector<T>\
    \ &b) {\n            const int n = a.size();\n            for (int i = 0; i <\
    \ n; ++i) a[i] += b[i];\n            return a;\n        }\n        template <typename\
    \ T>\n        std::vector<T>& subeq(std::vector<T> &a, const std::vector<T> &b)\
    \ {\n            const int n = a.size();\n            for (int i = 0; i < n; ++i)\
    \ a[i] -= b[i];\n            return a;\n        }\n        template <typename\
    \ T>\n        std::vector<T>& muleq(std::vector<T> &a, const std::vector<T> &b)\
    \ {\n            const int n = a.size();\n            for (int i = n - 1; i >=\
    \ 0; --i) {\n                for (int j = n - 1 - i; j > 0; --j) a[i + j] += a[i]\
    \ * b[j];\n                a[i] *= b[0];\n            }\n            return a;\n\
    \        }\n        template <typename T>\n        std::vector<T> add(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            std::vector<T> c = a;\n        \
    \    return addeq(c, b);\n        }\n        template <typename T>\n        std::vector<T>\
    \ sub(const std::vector<T> &a, const std::vector<T> &b) {\n            std::vector<T>\
    \ c = a;\n            return subeq(c, b);\n        }\n        template <typename\
    \ T>\n        std::vector<T> mul(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n            std::vector<T> c = a;\n            return muleq(c, b);\n\
    \        }\n\n        template <typename T>\n        std::vector<std::vector<T>>\
    \ ranked(const std::vector<T> &a) {\n            const int n = a.size();\n   \
    \         assert((-n & n) == n);\n            std::vector fs(n, std::vector(__builtin_ctz(n)\
    \ + 1, T(0)));\n            for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)]\
    \ = a[i];\n            return fs;\n        }\n        template <typename T>\n\
    \        std::vector<T> deranked(const std::vector<std::vector<T>> &polys) {\n\
    \            const int n = polys.size();\n            assert((-n & n) == n);\n\
    \            std::vector<T> a(n);\n            for (int i = 0; i < n; ++i) a[i]\
    \ = polys[i][__builtin_popcount(i)];\n            return a;\n        }\n\n   \
    \     template <typename T>\n        std::vector<std::vector<T>> ranked_zeta(const\
    \ std::vector<T> &a) {\n            std::vector<std::vector<T>> ranked_a = ranked<T>(a);\n\
    \            const int n = ranked_a.size();\n            for (int k = 1; k < n;\
    \ k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {\n\
    \                addeq(ranked_a[i + k], ranked_a[i]);\n            }\n       \
    \     return ranked_a;\n        }\n        template <typename T>\n        std::vector<T>\
    \ deranked_mobius(std::vector<std::vector<T>> &ranked_a) {\n            const\
    \ int n = ranked_a.size();\n            for (int k = 1; k < n; k *= 2) for (int\
    \ l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {\n              \
    \  subeq(ranked_a[i + k], ranked_a[i]);\n            }\n            return deranked<T>(ranked_a);\n\
    \        }\n    } // internal::subset_convolution\n\n    template <typename T>\n\
    \    std::vector<T> subset_convolution(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n        using namespace internal::subset_convolution;\n        const\
    \ int n = a.size();\n        auto ranked_a = ranked_zeta(a), ranked_b = ranked_zeta(b);\n\
    \        for (int i = 0; i < n; ++i) muleq(ranked_a[i], ranked_b[i]);\n      \
    \  return deranked_mobius(ranked_a);\n    }\n} // namespace suisen\n\n\n#line\
    \ 8 \"test/src/convolution/subset_convolution/subset_convolution.test.cpp\"\n\n\
    using mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::subset_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n\
    #include <iostream>\n#include <atcoder/convolution>\n#include <atcoder/modint>\n\
    \n#include \"library/convolution/subset_convolution.hpp\"\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\ntemplate <typename\
    \ T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T> &a) {\n\
    \    int n = a.size();\n    for (int i = 0; i < n; ++i) {\n        out << a[i];\n\
    \        if (i != n - 1) out << ' ';\n    }\n    return out;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<mint> a(1 << n), b(1 << n);\n    for\
    \ (auto &v : a) std::cin >> v;\n    for (auto &v : b) std::cin >> v;\n    std::cout\
    \ << suisen::subset_convolution<mint>(std::move(a), std::move(b)) << std::endl;\n\
    \    return 0;\n}"
  dependsOn:
  - library/convolution/subset_convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/subset_convolution/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/subset_convolution/subset_convolution.test.cpp
- /verify/test/src/convolution/subset_convolution/subset_convolution.test.cpp.html
title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
---
