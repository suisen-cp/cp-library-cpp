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

## Mo's Algorithm

### コンストラクタ

- シグネチャ

  ```cpp
  Mo(const int n, const std::vector<std::pair<int, int>> &queries)
  ```

- 概要

  クエリに答える順番を計算しておく．

- 引数

  - `n` : 区間の右端の上限値．
  - `queries` : クエリの区間 $[l_i,r_i)$ を $i$ 番目の要素として持つ `std::vector<std::pair<int, int>>`．$0\leq l_i\leq r_i\leq n$ を満たす必要がある．

- 時間計算量

  $Q$ をクエリの数として，$O(Q\log Q)$

### solve

- シグネチャ

  ```cpp
  // (1)
  template <typename Eval, typename AddL, typename DelL, typename AddR, typename DelR>
  auto solve(Eval eval, AddL add_l, DelL del_l, AddR add_r, DelR del_r)
  // (2)
  template <typename Eval, typename Add, typename Del>
  auto solve(Eval eval, Add add, Del del)
  ```

- 概要

  $i$ 番目のクエリの答えを $i$ 番目の要素として持つ `std::vector` を返す．クエリの答えを求めるのに必要な状態を外に置いて，引数の `add_l` や `del_l` の中で追加処理や削除処理に応じて状態を更新する．(2) は (1) において `add_l = add_r` かつ `del_l = del_r` の場合に用いる．

  具体的な使用法に関してはテストファイルを参照．

- 引数

  - `eval : () -> T` : 現時点の答えを返す関数
  - `add_l : int -> any` : 現時点の区間を $[l+1,r)$ として，$l$ を追加する関数．返り値は捨てられる．
  - `del_l : int -> any` : 現時点の区間を $[l,r)$ として，$l$ を削除する関数．返り値は捨てられる．
  - `add_r : int -> any` : 現時点の区間を $[l,r)$ として，$r$ を追加する関数．返り値は捨てられる．
  - `del_r : int -> any` : 現時点の区間を $[l,r+1)$ として，$r$ を削除する関数．返り値は捨てられる．

- 返り値

  $i$ 番目のクエリの答えを $i$ 番目の要素として持つ `std::vector<decltype(eval())>`．つまり，`std::vector` の要素の型は `eval()` が返す型．

- 制約

  - `eval` は引数を取らず，default constructiveな型の値を返す関数
  - `add_l`, `del_l`, `add_r`, `del_r` は，`int` を 1 つ受け取る関数

- 時間計算量

  `eval` や `add_l` などの計算量を $O(1)$ として，$O(N\sqrt Q)$

- 参考

  - [Mo's algorithm](https://ei1333.hateblo.jp/entry/2017/09/11/211011)
  - [Mo's algorithm とその上位互換の話](https://snuke.hatenablog.com/entry/2016/07/01/000000)
