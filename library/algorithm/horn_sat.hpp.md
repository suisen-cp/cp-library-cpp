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
  bundledCode: "#line 1 \"library/algorithm/horn_sat.hpp\"\n\n\n\n#include <cassert>\n\
    #include <queue>\n#include <vector>\n\nnamespace suisen {\n\nclass HornSAT {\n\
    \    public:\n        HornSAT() : HornSAT(0) {}\n        HornSAT(const int n)\
    \ : n(n), ans(n, false), ls(n) {}\n\n        void add_clause(const std::vector<int>\
    \ &lhs, int rhs, bool val) {\n            const int sz = cnt.size();\n       \
    \     cnt.push_back(lhs.size());\n            for (int i : lhs) ls[i].push_back(sz);\n\
    \            r.emplace_back(rhs, val);\n            has_answer = false;\n    \
    \    }\n\n        void add_clause(int rhs, bool val) {\n            add_clause({},\
    \ rhs, val);\n        }\n\n        bool satisfiable() {\n            const int\
    \ m = r.size();\n            std::deque<std::pair<int, bool>> dq;\n          \
    \  std::vector<int> c = cnt;\n            for (int j = 0; j < m; ++j) {\n    \
    \            if (c[j] == 0) dq.push_back(r[j]);\n            }\n            std::vector<bool>\
    \ seen(n, false);\n            while (dq.size()) {\n                const auto\
    \ [i, val] = dq.front();\n                dq.pop_front();\n                assert(i\
    \ < n);\n                if (i < 0) return has_answer = false;\n             \
    \   if (not seen[i]) {\n                    ans[i] = val;\n                  \
    \  seen[i] = true;\n                    for (const int j : ls[i]) {\n        \
    \                if (--c[j] == 0) dq.push_back(r[j]);\n                    }\n\
    \                } else if (val != ans[i]) return has_answer = false;\n      \
    \      }\n            for (int i = 0; i < n; ++i) {\n                if (not seen[i])\
    \ ans[i] = false;\n            }\n            return has_answer = true;\n    \
    \    }\n\n        // Call after `satisfiable()`.\n        const std::vector<bool>&\
    \ answer() {\n            assert(has_answer);\n            return ans;\n     \
    \   }\n\n    private:\n        const int n;\n        std::vector<bool> ans;\n\
    \        std::vector<int> cnt;\n        std::vector<std::vector<int>> ls;\n  \
    \      std::vector<std::pair<int, bool>> r;\n        bool has_answer = true;\n\
    };\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_HORN_SAT\n#define SUISEN_HORN_SAT\n\n#include <cassert>\n\
    #include <queue>\n#include <vector>\n\nnamespace suisen {\n\nclass HornSAT {\n\
    \    public:\n        HornSAT() : HornSAT(0) {}\n        HornSAT(const int n)\
    \ : n(n), ans(n, false), ls(n) {}\n\n        void add_clause(const std::vector<int>\
    \ &lhs, int rhs, bool val) {\n            const int sz = cnt.size();\n       \
    \     cnt.push_back(lhs.size());\n            for (int i : lhs) ls[i].push_back(sz);\n\
    \            r.emplace_back(rhs, val);\n            has_answer = false;\n    \
    \    }\n\n        void add_clause(int rhs, bool val) {\n            add_clause({},\
    \ rhs, val);\n        }\n\n        bool satisfiable() {\n            const int\
    \ m = r.size();\n            std::deque<std::pair<int, bool>> dq;\n          \
    \  std::vector<int> c = cnt;\n            for (int j = 0; j < m; ++j) {\n    \
    \            if (c[j] == 0) dq.push_back(r[j]);\n            }\n            std::vector<bool>\
    \ seen(n, false);\n            while (dq.size()) {\n                const auto\
    \ [i, val] = dq.front();\n                dq.pop_front();\n                assert(i\
    \ < n);\n                if (i < 0) return has_answer = false;\n             \
    \   if (not seen[i]) {\n                    ans[i] = val;\n                  \
    \  seen[i] = true;\n                    for (const int j : ls[i]) {\n        \
    \                if (--c[j] == 0) dq.push_back(r[j]);\n                    }\n\
    \                } else if (val != ans[i]) return has_answer = false;\n      \
    \      }\n            for (int i = 0; i < n; ++i) {\n                if (not seen[i])\
    \ ans[i] = false;\n            }\n            return has_answer = true;\n    \
    \    }\n\n        // Call after `satisfiable()`.\n        const std::vector<bool>&\
    \ answer() {\n            assert(has_answer);\n            return ans;\n     \
    \   }\n\n    private:\n        const int n;\n        std::vector<bool> ans;\n\
    \        std::vector<int> cnt;\n        std::vector<std::vector<int>> ls;\n  \
    \      std::vector<std::pair<int, bool>> r;\n        bool has_answer = true;\n\
    };\n\n} // namespace suisen\n\n\n#endif // SUISEN_HORN_SAT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/horn_sat.hpp
  requiredBy: []
  timestamp: '2021-08-24 06:29:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/horn_sat.hpp
layout: document
title: Horn SAT
---

## Horn SAT

以下の形式で表される充足可能性問題を解きます。

$$
\bigwedge_{i=1}^M \left(\left(x_{a^i_1}\land x_{a^i_2}\land\cdots\land x_{a^i_{c_i}}\right)\to y_{b_i}\right)\tag{1}
$$

ここで、$x$ は正リテラルに限ります ($y$ の正負は問いません)。

### コンストラクタ

- シグネチャ

  ```cpp
  HornSAT() // (1)
  HornSAT(int n) // (2)
  ```

- 概要

  論理変数を $n$ 個用意します。(1) は (2) で $n=0$ とした場合と等価です。

- 制約

  - $0\leq n\leq 10^6$

- 時間計算量

  $O(n)$

### 条件節の追加

- シグネチャ

  ```cpp
  void add_clause(const std::vector<int> &lhs, int rhs, bool val)
  void add_clause(int rhs, bool val)
  ```

- 概要

  式 $(1)$ における $a^i$ と `lhs`、$b_i$ と `rhs` が対応し、`val` は $y$ が正リテラルかどうかを表す `bool` 値です。`true` なら正リテラル、`false` なら負リテラルであることを表します。

  `lhs` を省略すると $a^i$ は空列の場合、すなわち単項の条件節 $y_{b_i}$ を表します。

- 時間計算量

  $O(c_i)$

### 充足可能性判定

- シグネチャ

  ```cpp
  bool satisfiable()
  ```

- 概要

  今までに与えた条件節たちをすべて満たすような真偽値の割り当て方が存在するかどうかを判定します。内部的には、同時に関数 `answer` の返り値として用いる解を一つ求めます。

- 時間計算量

  $O(N+M+\sum c_i)$

### 解の例示

- シグネチャ

  ```cpp
  const std::vector<bool>& answer()
  ```

- 概要

  今までに与えた条件節たちをすべて満たすような真偽値の割り当て方が存在するならば、そのような割り当てを一つ返します。

  __Note__: 必ず先に `satisfiable` を呼んでください。`satisfiable` を呼ばなかった場合、または `satisfiable` を呼んで返り値が `false` だった場合にこのメソッドを呼ぶと assert に引っかかるようになっています。

- 時間計算量

  先に `satisfiable` 内で解を計算するので、$O(1)$
  
## 参考

- https://people.eecs.berkeley.edu/~satishr/cs270.06/lecture1.pdf
