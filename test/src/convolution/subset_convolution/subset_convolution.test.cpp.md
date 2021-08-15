---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':question:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "#line 1 \"test/src/convolution/subset_convolution/subset_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n#include\
    \ <iostream>\n#include <atcoder/convolution>\n#include <atcoder/modint>\n\n#line\
    \ 1 \"library/convolution/subset_convolution.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen::internal::arithmetic_operator {\ntemplate <typename T>\nvoid\
    \ operator+=(std::vector<T> &a, const std::vector<T> &b) {\n    int n = b.size();\n\
    \    for (int i = 0; i < n; ++i) a[i] += b[i];\n}\ntemplate <typename T>\nvoid\
    \ operator-=(std::vector<T> &a, const std::vector<T> &b) {\n    int n = b.size();\n\
    \    for (int i = 0; i < n; ++i) a[i] -= b[i];\n}\ntemplate <typename T>\nvoid\
    \ operator*=(std::vector<T> &a, const std::vector<T> &b) {\n    int n = b.size();\n\
    \    for (int i = n - 1; i >= 0; --i) {\n        for (int j = n - i - 1; j > 0;\
    \ --j) a[i + j] += a[i] * b[j];\n        a[i] *= b[0];\n    }\n}\n}\n\n#line 1\
    \ \"library/transform/subset.hpp\"\n\n\n\n#include <cassert>\n#line 6 \"library/transform/subset.hpp\"\
    \n\nnamespace suisen::internal::arithmetic_operator {}\n\nnamespace suisen {\n\
    namespace subset_transform {\nnamespace internal {\ntemplate <typename T, typename\
    \ AssignOp>\nvoid transform(std::vector<T> &f, AssignOp assign_op) {\n    const\
    \ int n = f.size();\n    assert((-n & n) == n);\n    for (int k = 1; k < n; k\
    \ <<= 1) {\n        for (int l = 0; l < n; l += 2 * k) {\n            int m =\
    \ l + k;\n            for (int p = 0; p < k; ++p) assign_op(f[m + p], f[l + p]);\n\
    \        }\n    }\n}\n} // namespace internal\n\nusing namespace suisen::internal::arithmetic_operator;\n\
    \ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign\
    \ add_assign) {\n    internal::transform(f, add_assign);\n}\ntemplate <typename\
    \ T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    internal::transform(f, sub_assign);\n}\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\ntemplate <typename\
    \ T>\nvoid mobius(std::vector<T> &f) {\n    mobius(f, [](T &a, const T &b) { a\
    \ -= b; });\n}\n\n} // namespace subset_transform\n\ntemplate <typename T, typename\
    \ AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>\n\
    struct SubsetTransformGeneral {\n    static void transform(std::vector<T> &a)\
    \ {\n        subset_transform::zeta(a, add_assign);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        subset_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate\
    \ <typename T>\nstruct SubsetTransform {\n    static void transform(std::vector<T>\
    \ &a) {\n        subset_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        subset_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::arithmetic_operator {}\ntemplate <typename\
    \ T, template <typename> class Transform>\nstruct Convolution {\n    static std::vector<T>\
    \ convolution(std::vector<T> a, std::vector<T> b) {\n        using namespace internal::arithmetic_operator;\n\
    \        const int n = a.size();\n        assert(n == int(b.size()));\n      \
    \  Transform<T>::transform(a);\n        Transform<T>::transform(b);\n        for\
    \ (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        using namespace internal::arithmetic_operator;\n        const\
    \ int num = a.size();\n        if (num == 0) return {};\n        const int n =\
    \ a[0].size();\n        for (auto &v : a) {\n            assert(n == int(v.size()));\n\
    \            Transform<T>::transform(v);\n        }\n        auto &res = a[0];\n\
    \        for (int i = 1; i < num; ++i) {\n            for (int j = 0; j < n; ++j)\
    \ res[j] *= a[i][j];\n        }\n        Transform<T>::inverse_transform(res);\n\
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n\n#line 29 \"library/convolution/subset_convolution.hpp\"\
    \n\nnamespace suisen {\n\nnamespace internal::subset_convolution {\ntemplate <typename\
    \ T, typename Container>\nauto add_rank(const Container &a) {\n    int n = a.size();\n\
    \    assert((-n & n) == n);\n    std::vector<std::vector<T>> fs(n, std::vector<T>(__builtin_ctz(n)\
    \ + 1, T(0)));\n    for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] =\
    \ a[i];\n    return fs;\n}\ntemplate <typename T>\nauto remove_rank(const std::vector<std::vector<T>>\
    \ &polys) {\n    int n = polys.size();\n    assert((-n & n) == n);\n    std::vector<T>\
    \ a(n);\n    for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n\
    \    return a;\n}\n} // namespace internal\n\ntemplate <typename T>\nusing SubsetConvolution\
    \ = Convolution<std::vector<T>, SubsetTransform>;\n\ntemplate <typename T, typename\
    \ ...Args>\nstd::vector<T> subset_convolution(Args &&...args) {\n    using namespace\
    \ internal::subset_convolution;\n    return remove_rank<T>(SubsetConvolution<T>::convolution(add_rank<T>(args)...));\n\
    }\n\n} // namespace suisen\n\n\n#line 8 \"test/src/convolution/subset_convolution/subset_convolution.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    suisen::FPS<mint>::set_multiplication([](const\
    \ auto &a, const auto &b) { return atcoder::convolution(a, b); });\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
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
    \ {\n    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b)\
    \ { return atcoder::convolution(a, b); });\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::subset_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/convolution/subset_convolution.hpp
  - library/transform/subset.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/convolution/subset_convolution/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/subset_convolution/subset_convolution.test.cpp
- /verify/test/src/convolution/subset_convolution/subset_convolution.test.cpp.html
title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
---
