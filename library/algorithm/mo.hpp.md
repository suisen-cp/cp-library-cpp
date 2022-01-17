---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/mo/abc174_f.test.cpp
    title: test/src/algorithm/mo/abc174_f.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/mo.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen {\n\
    \    struct Mo {\n        Mo() {}\n        Mo(const int n, const std::vector<std::pair<int,\
    \ int>> &queries) : n(n), q(queries.size()), b(n / (::sqrt(q) + 1)), qs(queries),\
    \ ord(q) {\n            std::iota(ord.begin(), ord.end(), 0);\n            std::sort(\n\
    \                ord.begin(), ord.end(),\n                [&, this](int i, int\
    \ j) {\n                    const auto &[li, ri] = qs[i];\n                  \
    \  const auto &[lj, rj] = qs[j];\n                    const int bi = li / b, bj\
    \ = lj / b;\n                    if (bi != bj) return bi < bj;\n             \
    \       if (ri != rj) return bi & 1 ? ri > rj : ri < rj;\n                   \
    \ return li < lj;\n                }\n            );\n        }\n\n        //\
    \ getter methods used in updating functions: AddL, DelL, etc.\n        auto get_left()\
    \  const { return l; }\n        auto get_right() const { return r; }\n       \
    \ auto get_range() const { return std::make_pair(l, r); }\n\n        /**\n   \
    \      * [Parameters]\n         * Eval : () -> T : return the current answer\n\
    \         * AddL : int -> any (discarded) : add    `l` to   the current range\
    \ [l + 1, r)\n         * DelL : int -> any (discarded) : delete `l` from the current\
    \ range [l, r)\n         * AddR : int -> any (discarded) : add    `r` to   the\
    \ current range [l, r)\n         * DelR : int -> any (discarded) : delete `r`\
    \ from the current range [l, r + 1)\n         * \n         * [Note]\n        \
    \ * starting from the range [0, 0).\n         */\n        template <typename Eval,\
    \ typename AddL, typename DelL, typename AddR, typename DelR>\n        auto solve(Eval\
    \ eval, AddL add_l, DelL del_l, AddR add_r, DelR del_r) {\n            l = 0,\
    \ r = 0;\n            std::vector<decltype(eval())> res(q);\n            for (int\
    \ qi : ord) {\n                const auto &[nl, nr] = qs[qi];\n              \
    \  while (r < nr) add_r(r), ++r;\n                while (l > nl) --l, add_l(l);\n\
    \                while (r > nr) --r, del_r(r);\n                while (l < nl)\
    \ del_l(l), ++l;\n                res[qi] = eval();\n            }\n         \
    \   return res;\n        }\n    \n        /**\n         * [Parameters]\n     \
    \    * Eval : () -> T : return the current answer\n         * Add : int -> any\
    \ (discarded) : add    `i` to   the current range [i + 1, r) or [l, i)\n     \
    \    * Del : int -> any (discarded) : delete `i` from the current range [i, r)\
    \ or [l, i + 1)\n         * \n         * [Note]\n         * starting from the\
    \ range [0, 0).\n         */\n        template <typename Eval, typename Add, typename\
    \ Del>\n        auto solve(Eval eval, Add add, Del del) {\n            return\
    \ solve(eval, add, del, add, del);\n        }\n\n    private:\n        int n,\
    \ q, b;\n        std::vector<std::pair<int, int>> qs;\n        std::vector<int>\
    \ ord;\n        int l = 0, r = 0;\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MO\n#define SUISEN_MO\n\n#include <algorithm>\n#include <cmath>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\n    struct Mo {\n\
    \        Mo() {}\n        Mo(const int n, const std::vector<std::pair<int, int>>\
    \ &queries) : n(n), q(queries.size()), b(n / (::sqrt(q) + 1)), qs(queries), ord(q)\
    \ {\n            std::iota(ord.begin(), ord.end(), 0);\n            std::sort(\n\
    \                ord.begin(), ord.end(),\n                [&, this](int i, int\
    \ j) {\n                    const auto &[li, ri] = qs[i];\n                  \
    \  const auto &[lj, rj] = qs[j];\n                    const int bi = li / b, bj\
    \ = lj / b;\n                    if (bi != bj) return bi < bj;\n             \
    \       if (ri != rj) return bi & 1 ? ri > rj : ri < rj;\n                   \
    \ return li < lj;\n                }\n            );\n        }\n\n        //\
    \ getter methods used in updating functions: AddL, DelL, etc.\n        auto get_left()\
    \  const { return l; }\n        auto get_right() const { return r; }\n       \
    \ auto get_range() const { return std::make_pair(l, r); }\n\n        /**\n   \
    \      * [Parameters]\n         * Eval : () -> T : return the current answer\n\
    \         * AddL : int -> any (discarded) : add    `l` to   the current range\
    \ [l + 1, r)\n         * DelL : int -> any (discarded) : delete `l` from the current\
    \ range [l, r)\n         * AddR : int -> any (discarded) : add    `r` to   the\
    \ current range [l, r)\n         * DelR : int -> any (discarded) : delete `r`\
    \ from the current range [l, r + 1)\n         * \n         * [Note]\n        \
    \ * starting from the range [0, 0).\n         */\n        template <typename Eval,\
    \ typename AddL, typename DelL, typename AddR, typename DelR>\n        auto solve(Eval\
    \ eval, AddL add_l, DelL del_l, AddR add_r, DelR del_r) {\n            l = 0,\
    \ r = 0;\n            std::vector<decltype(eval())> res(q);\n            for (int\
    \ qi : ord) {\n                const auto &[nl, nr] = qs[qi];\n              \
    \  while (r < nr) add_r(r), ++r;\n                while (l > nl) --l, add_l(l);\n\
    \                while (r > nr) --r, del_r(r);\n                while (l < nl)\
    \ del_l(l), ++l;\n                res[qi] = eval();\n            }\n         \
    \   return res;\n        }\n    \n        /**\n         * [Parameters]\n     \
    \    * Eval : () -> T : return the current answer\n         * Add : int -> any\
    \ (discarded) : add    `i` to   the current range [i + 1, r) or [l, i)\n     \
    \    * Del : int -> any (discarded) : delete `i` from the current range [i, r)\
    \ or [l, i + 1)\n         * \n         * [Note]\n         * starting from the\
    \ range [0, 0).\n         */\n        template <typename Eval, typename Add, typename\
    \ Del>\n        auto solve(Eval eval, Add add, Del del) {\n            return\
    \ solve(eval, add, del, add, del);\n        }\n\n    private:\n        int n,\
    \ q, b;\n        std::vector<std::pair<int, int>> qs;\n        std::vector<int>\
    \ ord;\n        int l = 0, r = 0;\n    };\n} // namespace suisen\n\n#endif //\
    \ SUISEN_MO\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/mo.hpp
  requiredBy: []
  timestamp: '2021-11-21 01:23:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/mo/abc174_f.test.cpp
documentation_of: library/algorithm/mo.hpp
layout: document
title: Mo
---
## Mo