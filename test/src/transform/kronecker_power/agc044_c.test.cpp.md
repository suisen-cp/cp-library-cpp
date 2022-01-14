---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: library/util/default_operator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/agc044/tasks/agc044_c
    links:
    - https://atcoder.jp/contests/agc044/tasks/agc044_c
  bundledCode: "#line 1 \"test/src/transform/kronecker_power/agc044_c.test.cpp\"\n\
    #define PROBLEM \"https://atcoder.jp/contests/agc044/tasks/agc044_c\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n#include <numeric>\n#include <string>\n#include\
    \ <vector>\n\n#line 1 \"library/transform/kronecker_power.hpp\"\n\n\n\n#include\
    \ <cassert>\n#line 6 \"library/transform/kronecker_power.hpp\"\n\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    } // namespace suisen\n\n\n#line 8 \"library/transform/kronecker_power.hpp\"\n\
    \nnamespace suisen {\n    namespace kronecker_power_transform {\n        namespace\
    \ internal {\n            template <typename UnitTransform, typename ReferenceGetter,\
    \ std::size_t... Seq>\n            void unit_transform(UnitTransform transform,\
    \ ReferenceGetter ref_getter, std::index_sequence<Seq...>) {\n               \
    \ transform(ref_getter(Seq)...);\n            }\n        }\n\n        template\
    \ <typename T, std::size_t D, auto unit_transform>\n        void kronecker_power_transform(std::vector<T>\
    \ &x) {\n            const std::size_t n = x.size();\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
    \ i) -> T& { return x[offset + i * block]; };\n                        internal::unit_transform(unit_transform,\
    \ ref_getter, std::make_index_sequence<D>());\n                    }\n       \
    \         }\n            }\n        }\n\n        template <typename T, typename\
    \ UnitTransform>\n        void kronecker_power_transform(std::vector<T> &x, const\
    \ std::size_t D, UnitTransform unit_transform) {\n            const std::size_t\
    \ n = x.size();\n            std::vector<T> work(D);\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        for (std::size_t i = 0; i\
    \ < D; ++i) work[i] = x[offset + i * block];\n                        unit_transform(work);\n\
    \                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block]\
    \ = work[i];\n                    }\n                }\n            }\n      \
    \  }\n\n        template <typename T, auto e = default_operator::zero<T>, auto\
    \ add = default_operator::add<T>, auto mul = default_operator::mul<T>>\n     \
    \   auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>>\
    \ &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(),\
    \ std::declval<T>()), void()) {\n            const std::size_t D = A.size();\n\
    \            assert(D == A[0].size());\n            auto unit_transform = [&](std::vector<T>\
    \ &x) {\n                std::vector<T> y(D, e());\n                for (std::size_t\
    \ i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {\n                 \
    \   y[i] = add(y[i], mul(A[i][j], x[j]));\n                }\n               \
    \ x.swap(y);\n            };\n            kronecker_power_transform<T>(x, D, unit_transform);\n\
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 10 \"test/src/transform/kronecker_power/agc044_c.test.cpp\"\
    \nusing suisen::kronecker_power_transform::kronecker_power_transform;\n\nvoid\
    \ utit_transform(int&, int &x1, int &x2) {\n    std::swap(x1, x2);\n}\n\nconstexpr\
    \ int pow3(int b) {\n    int res = 1;\n    while (b --> 0) res *= 3;\n    return\
    \ res;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n    const int sz = pow3(n), lsz = pow3(n - n\
    \ / 2), usz = pow3(n / 2);\n\n    std::string s;\n    std::cin >> s;\n    const\
    \ int k = s.size();\n\n    std::vector<bool> cnt_s(k + 1, false);\n    std::vector<int>\
    \ ql(lsz);\n    std::iota(ql.begin(), ql.end(), 0);\n    std::vector<std::vector<int>>\
    \ carry(lsz);\n    for (int i = 0; i < k; ++i) {\n        cnt_s[i + 1] = cnt_s[i]\
    \ ^ (s[i] == 'S');\n        if (s[i] == 'S') {\n            kronecker_power_transform<int,\
    \ 3, utit_transform>(ql);\n        } else {\n            std::rotate(ql.begin(),\
    \ ql.end() - 1, ql.end());\n            carry[ql[0]].push_back(i);\n        }\n\
    \    }\n\n    std::vector<int> p(sz);\n\n    for (int lower = 0; lower < lsz;\
    \ ++lower) {\n        std::vector<int> qu(usz);\n        std::iota(qu.begin(),\
    \ qu.end(), 0);\n        int pj = 0;\n        for (int j : carry[ql[lower]]) {\n\
    \            if (cnt_s[j] ^ cnt_s[pj]) kronecker_power_transform<int, 3, utit_transform>(qu);\n\
    \            pj = j;\n            std::rotate(qu.begin(), qu.end() - 1, qu.end());\n\
    \        }\n        if (cnt_s[pj] ^ cnt_s[k]) kronecker_power_transform<int, 3,\
    \ utit_transform>(qu);\n        for (int upper = 0; upper < usz; ++upper) {\n\
    \            int pos = upper * lsz + lower;\n            int idx = qu[upper] *\
    \ lsz + ql[lower];\n            p[idx] = pos;\n        }\n    }\n    \n    for\
    \ (int i = 0; i < sz; ++i) {\n        std::cout << p[i] << \" \\n\"[i == sz -\
    \ 1];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/agc044/tasks/agc044_c\"\n\n\
    #include <algorithm>\n#include <iostream>\n#include <numeric>\n#include <string>\n\
    #include <vector>\n\n#include \"library/transform/kronecker_power.hpp\"\nusing\
    \ suisen::kronecker_power_transform::kronecker_power_transform;\n\nvoid utit_transform(int&,\
    \ int &x1, int &x2) {\n    std::swap(x1, x2);\n}\n\nconstexpr int pow3(int b)\
    \ {\n    int res = 1;\n    while (b --> 0) res *= 3;\n    return res;\n}\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n    const int sz = pow3(n), lsz = pow3(n - n\
    \ / 2), usz = pow3(n / 2);\n\n    std::string s;\n    std::cin >> s;\n    const\
    \ int k = s.size();\n\n    std::vector<bool> cnt_s(k + 1, false);\n    std::vector<int>\
    \ ql(lsz);\n    std::iota(ql.begin(), ql.end(), 0);\n    std::vector<std::vector<int>>\
    \ carry(lsz);\n    for (int i = 0; i < k; ++i) {\n        cnt_s[i + 1] = cnt_s[i]\
    \ ^ (s[i] == 'S');\n        if (s[i] == 'S') {\n            kronecker_power_transform<int,\
    \ 3, utit_transform>(ql);\n        } else {\n            std::rotate(ql.begin(),\
    \ ql.end() - 1, ql.end());\n            carry[ql[0]].push_back(i);\n        }\n\
    \    }\n\n    std::vector<int> p(sz);\n\n    for (int lower = 0; lower < lsz;\
    \ ++lower) {\n        std::vector<int> qu(usz);\n        std::iota(qu.begin(),\
    \ qu.end(), 0);\n        int pj = 0;\n        for (int j : carry[ql[lower]]) {\n\
    \            if (cnt_s[j] ^ cnt_s[pj]) kronecker_power_transform<int, 3, utit_transform>(qu);\n\
    \            pj = j;\n            std::rotate(qu.begin(), qu.end() - 1, qu.end());\n\
    \        }\n        if (cnt_s[pj] ^ cnt_s[k]) kronecker_power_transform<int, 3,\
    \ utit_transform>(qu);\n        for (int upper = 0; upper < usz; ++upper) {\n\
    \            int pos = upper * lsz + lower;\n            int idx = qu[upper] *\
    \ lsz + ql[lower];\n            p[idx] = pos;\n        }\n    }\n    \n    for\
    \ (int i = 0; i < sz; ++i) {\n        std::cout << p[i] << \" \\n\"[i == sz -\
    \ 1];\n    }\n    return 0;\n}"
  dependsOn:
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/transform/kronecker_power/agc044_c.test.cpp
  requiredBy: []
  timestamp: '2022-01-15 00:27:35+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/transform/kronecker_power/agc044_c.test.cpp
layout: document
redirect_from:
- /verify/test/src/transform/kronecker_power/agc044_c.test.cpp
- /verify/test/src/transform/kronecker_power/agc044_c.test.cpp.html
title: test/src/transform/kronecker_power/agc044_c.test.cpp
---
