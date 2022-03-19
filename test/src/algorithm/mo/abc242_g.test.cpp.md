---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/algorithm/mo.hpp
    title: Mo
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc242/tasks/abc242_g
    links:
    - https://atcoder.jp/contests/abc242/tasks/abc242_g
  bundledCode: "#line 1 \"test/src/algorithm/mo/abc242_g.test.cpp\"\n#define PROBLEM\
    \ \"https://atcoder.jp/contests/abc242/tasks/abc242_g\"\n\n#include <iostream>\n\
    \n#line 1 \"library/algorithm/mo.hpp\"\n\n\n\n#include <algorithm>\n#include <cmath>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\n    struct Mo {\n\
    \        Mo() {}\n        Mo(const int n, const std::vector<std::pair<int, int>>\
    \ &queries) : n(n), q(queries.size()), b(bucket_size(n, q)), qs(queries), ord(q)\
    \ {\n            std::iota(ord.begin(), ord.end(), 0);\n            std::sort(\n\
    \                ord.begin(), ord.end(),\n                [&, this](int i, int\
    \ j) {\n                    const auto &[li, ri] = qs[i];\n                  \
    \  const auto &[lj, rj] = qs[j];\n                    const int bi = li / b, bj\
    \ = lj / b;\n                    if (bi != bj) return bi < bj;\n             \
    \       if (ri != rj) return bi & 1 ? ri > rj : ri < rj;\n                   \
    \ return li < lj;\n                }\n            );\n        }\n\n        //\
    \ getter methods used in updating functions: AddL, DelL, etc.\n        auto get_left()\
    \  const { return l; }\n        auto get_right() const { return r; }\n       \
    \ auto get_range() const { return std::make_pair(l, r); }\n        auto get_query_id()\
    \ const { return query_id; }\n\n        /**\n         * [Parameters]\n       \
    \  * Eval : () -> T : return the current answer\n         * AddL : int -> any\
    \ (discarded) : add    `l` to   the current range [l + 1, r)\n         * DelL\
    \ : int -> any (discarded) : delete `l` from the current range [l, r)\n      \
    \   * AddR : int -> any (discarded) : add    `r` to   the current range [l, r)\n\
    \         * DelR : int -> any (discarded) : delete `r` from the current range\
    \ [l, r + 1)\n         * \n         * [Note]\n         * starting from the range\
    \ [0, 0).\n         */\n        template <typename Eval, typename AddL, typename\
    \ DelL, typename AddR, typename DelR>\n        auto solve(Eval eval, AddL add_l,\
    \ DelL del_l, AddR add_r, DelR del_r) {\n            l = 0, r = 0;\n         \
    \   std::vector<decltype(eval())> res(q);\n            for (int qi : ord) {\n\
    \                const auto &[nl, nr] = qs[query_id = qi];\n                while\
    \ (r < nr) add_r(r), ++r;\n                while (l > nl) --l, add_l(l);\n   \
    \             while (r > nr) --r, del_r(r);\n                while (l < nl) del_l(l),\
    \ ++l;\n                res[qi] = eval();\n            }\n            return res;\n\
    \        }\n    \n        /**\n         * [Parameters]\n         * Eval : () ->\
    \ T : return the current answer\n         * Add : int -> any (discarded) : add\
    \    `i` to   the current range [i + 1, r) or [l, i)\n         * Del : int ->\
    \ any (discarded) : delete `i` from the current range [i, r) or [l, i + 1)\n \
    \        * \n         * [Note]\n         * starting from the range [0, 0).\n \
    \        */\n        template <typename Eval, typename Add, typename Del>\n  \
    \      auto solve(Eval eval, Add add, Del del) {\n            return solve(eval,\
    \ add, del, add, del);\n        }\n\n    private:\n        int n, q, b;\n    \
    \    int query_id = -1;\n        std::vector<std::pair<int, int>> qs;\n      \
    \  std::vector<int> ord;\n        int l = 0, r = 0;\n\n        static int bucket_size(int\
    \ n, int q) {\n            return std::max(1, int(::sqrt(3) * n / ::sqrt(std::max(1,\
    \ 2 * q))));\n        }\n    };\n} // namespace suisen\n\n\n#line 6 \"test/src/algorithm/mo/abc242_g.test.cpp\"\
    \nusing suisen::Mo;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n \
    \   std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<int>\
    \ a(n);\n    for (auto& e : a) std::cin >> e, --e;\n\n    int q;\n    std::cin\
    \ >> q;\n\n    std::vector<std::pair<int, int>> qs;\n    for (int i = 0; i < q;\
    \ ++i) {\n        int l, r;\n        std::cin >> l >> r;\n        --l;\n     \
    \   qs.emplace_back(l, r);\n    }\n\n    std::vector<int8_t> cnt(n);\n    int\
    \ cur = 0;\n\n    auto ans = Mo(n, qs).solve(\n        [&] {\n            return\
    \ cur;\n        },\n        [&](int i) {\n            auto &v = cnt[a[i]];\n \
    \           cur += v, v ^= 1;\n        },\n        [&](int i) {\n            auto\
    \ &v = cnt[a[i]];\n            v ^= 1, cur -= v;\n        }\n    );\n\n    for\
    \ (int e : ans) std::cout << e << '\\n';\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc242/tasks/abc242_g\"\n\n\
    #include <iostream>\n\n#include \"library/algorithm/mo.hpp\"\nusing suisen::Mo;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<int> a(n);\n    for (auto&\
    \ e : a) std::cin >> e, --e;\n\n    int q;\n    std::cin >> q;\n\n    std::vector<std::pair<int,\
    \ int>> qs;\n    for (int i = 0; i < q; ++i) {\n        int l, r;\n        std::cin\
    \ >> l >> r;\n        --l;\n        qs.emplace_back(l, r);\n    }\n\n    std::vector<int8_t>\
    \ cnt(n);\n    int cur = 0;\n\n    auto ans = Mo(n, qs).solve(\n        [&] {\n\
    \            return cur;\n        },\n        [&](int i) {\n            auto &v\
    \ = cnt[a[i]];\n            cur += v, v ^= 1;\n        },\n        [&](int i)\
    \ {\n            auto &v = cnt[a[i]];\n            v ^= 1, cur -= v;\n       \
    \ }\n    );\n\n    for (int e : ans) std::cout << e << '\\n';\n\n    return 0;\n\
    }"
  dependsOn:
  - library/algorithm/mo.hpp
  isVerificationFile: true
  path: test/src/algorithm/mo/abc242_g.test.cpp
  requiredBy: []
  timestamp: '2022-03-19 20:36:40+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/algorithm/mo/abc242_g.test.cpp
layout: document
redirect_from:
- /verify/test/src/algorithm/mo/abc242_g.test.cpp
- /verify/test/src/algorithm/mo/abc242_g.test.cpp.html
title: test/src/algorithm/mo/abc242_g.test.cpp
---
