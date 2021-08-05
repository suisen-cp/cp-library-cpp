---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: Bitwise And Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/supset.hpp
    title: library/transform/supset.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/src/convolution/and_convolution/and_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/convolution/and_convolution.hpp\"\
    \n\n\n\n#line 1 \"library/transform/supset.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace suisen {\n\nnamespace supset_transform {\n\nnamespace\
    \ internal {\n\ntemplate <typename T, typename AssignOp>\nvoid transform(std::vector<T>\
    \ &f, AssignOp assign_op) {\n    const int n = f.size();\n    assert((-n & n)\
    \ == n);\n    for (int k = 1; k < n; k <<= 1) {\n        for (int l = 0; l < n;\
    \ l += 2 * k) {\n            int m = l + k;\n            for (int p = 0; p < k;\
    \ ++p) assign_op(f[l + p], f[m + p]);\n        }\n    }\n}\n\n} // namespace internal\n\
    \ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign\
    \ add_assign) {\n    internal::transform(f, add_assign);\n}\ntemplate <typename\
    \ T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    internal::transform(f, sub_assign);\n}\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    internal::transform(f, [](T &a, const T &b) { a += b; });\n}\ntemplate\
    \ <typename T>\nvoid mobius(std::vector<T> &f) {\n    internal::transform(f, [](T\
    \ &a, const T &b) { a -= b; });\n}\n\n} // namespace supset_transform\n\ntemplate\
    \ <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign\
    \ sub_assign>\nstruct SupsetTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        supset_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        supset_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct SupsetTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        supset_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        supset_transform::mobius(a);\n\
    \    }\n};\n\n} // namespace suisen\n\n\n\n#line 1 \"library/convolution/convolution.hpp\"\
    \n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n\
    \ntemplate <typename T, template <typename> class Transform>\nstruct Convolution\
    \ {\n    static std::vector<T> convolution(std::vector<T> a, std::vector<T> b)\
    \ {\n        const int n = a.size();\n        assert(n == int(b.size()));\n  \
    \      Transform<T>::transform(a);\n        Transform<T>::transform(b);\n    \
    \    for (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        const int num = a.size();\n        if (num == 0) return {};\n\
    \        const int n = a[0].size();\n        for (auto &v : a) {\n           \
    \ assert(n == int(v.size()));\n            Transform<T>::transform(v);\n     \
    \   }\n        auto &res = a[0];\n        for (int i = 1; i < num; ++i) {\n  \
    \          for (int j = 0; j < n; ++j) res[j] *= a[i][j];\n        }\n       \
    \ Transform<T>::inverse_transform(res);\n        return res;\n    }\n};\n\n} //\
    \ namespace suisen\n\n\n\n#line 6 \"library/convolution/and_convolution.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T>\nusing AndConvolution = Convolution<T,\
    \ SupsetTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> and_convolution(Args\
    \ &&...args) {\n    return AndConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n#line 7 \"test/src/convolution/and_convolution/and_convolution.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::and_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/convolution/and_convolution.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::and_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/convolution/and_convolution.hpp
  - library/transform/supset.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/and_convolution/and_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/and_convolution/and_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/and_convolution/and_convolution.test.cpp
- /verify/test/src/convolution/and_convolution/and_convolution.test.cpp.html
title: test/src/convolution/and_convolution/and_convolution.test.cpp
---
