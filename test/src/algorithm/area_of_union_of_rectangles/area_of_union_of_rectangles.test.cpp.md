---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/area_of_union_of_rectangles.hpp
    title: Calculates area of union of rectangles in O(NlogN) time.
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/area_of_union_of_rectangles
    links:
    - https://judge.yosupo.jp/problem/area_of_union_of_rectangles
  bundledCode: "#line 1 \"test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/area_of_union_of_rectangles\"\
    \n\n#include <iostream>\n\n#line 1 \"library/algorithm/area_of_union_of_rectangles.hpp\"\
    \n\n\n\n#include <limits>\n#include <tuple>\n#include <vector>\n\n#include <atcoder/lazysegtree>\n\
    \nnamespace suisen {\n    namespace internal::area_of_union_of_rectangles {\n\
    \        constexpr int inf = std::numeric_limits<int>::max() / 2;\n\n        template\
    \ <typename T> struct S {\n            int min_cnt;\n            T len;\n    \
    \    };\n        template <typename T> S<T> op(S<T> x, S<T> y) {\n           \
    \ if (x.min_cnt < y.min_cnt) return x;\n            else if (x.min_cnt > y.min_cnt)\
    \ return y;\n            else return { x.min_cnt, x.len + y.len };\n        }\n\
    \        template <typename T> S<T> e() { return { inf , 0 }; }\n        template\
    \ <typename T> S<T> mapping(int f, S<T> x) { return { x.min_cnt + f, x.len };\
    \ }\n        int composition(int f, int g) { return f + g; }\n        int id()\
    \ { return 0; }\n    }\n\n    /**\n     * @brief Calculates area of union of rectangles\
    \ in O(NlogN) time.\n     * @tparam T type of coordinates\n     * @param rects\
    \ vector of { l, r, d, u }.\n     * @return area of union of rectangles\n    \
    \ */\n    template <typename T>\n    T area_of_union_of_rectangles(const std::vector<std::tuple<T,\
    \ T, T, T>> &rects) {\n        if (rects.empty()) return T{0};\n\n        using\
    \ namespace internal::area_of_union_of_rectangles;\n\n        const int k = rects.size();\n\
    \n        std::vector<std::tuple<T, T, T, bool>> event;\n        event.reserve(2\
    \ * k);\n\n        std::vector<T> ys;\n        ys.reserve(2 * k);\n\n        for\
    \ (const auto &[l, r, d, u] : rects) {\n            event.emplace_back(l, d, u,\
    \ true);\n            event.emplace_back(r, d, u, false);\n            ys.push_back(d),\
    \ ys.push_back(u);\n        }\n        std::sort(event.begin(), event.end(), [](const\
    \ auto& e1, const auto &e2) { return std::get<0>(e1) < std::get<0>(e2); });\n\
    \        std::sort(ys.begin(), ys.end()), ys.erase(std::unique(ys.begin(), ys.end()),\
    \ ys.end());\n\n        const int m = ys.size();\n\n        std::vector<S<T>>\
    \ init(m - 1);\n        for (int i = 0; i < m - 1; ++i) {\n            init[i]\
    \ = { 0, ys[i + 1] - ys[i] };\n        }\n        atcoder::lazy_segtree<S<T>,\
    \ op<T>, e<T>, int, mapping<T>, composition, id> seg(init);\n\n        T ans =\
    \ 0;\n        T lx = std::get<0>(event.front());\n        for (int i = 0; lx !=\
    \ std::get<0>(event.back());) {\n            for (;; ++i) {\n                auto\
    \ [xi, d, u, b] = event[i];\n                if (xi != lx) break;\n          \
    \      int ly = std::lower_bound(ys.begin(), ys.end(), d) - ys.begin();\n    \
    \            int ry = std::lower_bound(ys.begin(), ys.end(), u) - ys.begin();\n\
    \                seg.apply(ly, ry, b ? +1 : -1);\n            }\n            T\
    \ rx = std::get<0>(event[i]);\n            auto [min_cnt, len] = seg.all_prod();\n\
    \            ans += (rx - lx) * (ys.back() - ys.front() - (min_cnt == 0 ? len\
    \ : T{0}));\n            lx = rx;\n        }\n        return ans;\n    }\n} //\
    \ namespace suisen\n\n\n#line 6 \"test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::tuple<long long, long\
    \ long, long long, long long>> rects(n);\n    for (auto &[l, r, d, u] : rects)\
    \ {\n        std::cin >> l >> d >> r >> u;\n    }\n\n    std::cout << suisen::area_of_union_of_rectangles(rects)\
    \ << std::endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/area_of_union_of_rectangles\"\
    \n\n#include <iostream>\n\n#include \"library/algorithm/area_of_union_of_rectangles.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::tuple<long long, long\
    \ long, long long, long long>> rects(n);\n    for (auto &[l, r, d, u] : rects)\
    \ {\n        std::cin >> l >> d >> r >> u;\n    }\n\n    std::cout << suisen::area_of_union_of_rectangles(rects)\
    \ << std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/algorithm/area_of_union_of_rectangles.hpp
  isVerificationFile: true
  path: test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp
  requiredBy: []
  timestamp: '2022-10-31 00:07:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp
layout: document
redirect_from:
- /verify/test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp
- /verify/test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp.html
title: test/src/algorithm/area_of_union_of_rectangles/area_of_union_of_rectangles.test.cpp
---
