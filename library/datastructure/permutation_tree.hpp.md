---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/permutation_tree/common_interval_decomposition_tree.test.cpp
    title: test/src/datastructure/permutation_tree/common_interval_decomposition_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/permutation_tree.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct PermutationTree : std::vector<PermutationTree>\
    \ {\n        using base_type = std::vector<PermutationTree>;\n\n        PermutationTree()\
    \ : PermutationTree(0, 0, 0) {}\n\n        PermutationTree(const std::vector<int>&\
    \ p) : PermutationTree(build(p)) {}\n\n        int length() const { return len;\
    \ }\n\n        int begin_index() const { return il; }\n        int end_index()\
    \ const { return il + len; }\n        int min_index() const { return begin_index();\
    \ }\n        int max_index() const { return end_index() - 1; }\n        std::pair<int,\
    \ int> get_index_range() const { return { begin_index(), end_index() }; }\n  \
    \      std::pair<int, int> get_index_range_closed() const { return { min_index(),\
    \ max_index() }; }\n\n        int begin_value() const { return vl; }\n       \
    \ int end_value() const { return vl + len; }\n        int min_value() const {\
    \ return begin_value(); }\n        int max_value() const { return end_value()\
    \ - 1; }\n        std::pair<int, int> get_value_range() const { return { begin_value(),\
    \ end_value() }; }\n        std::pair<int, int> get_value_range_closed() const\
    \ { return { min_value(), max_value() }; }\n\n        bool is_join_node() const\
    \ { return _is_join_node; }\n\n        friend std::ostream& operator<<(std::ostream&\
    \ out, const PermutationTree& t) {\n            std::vector<std::string> lines;\n\
    \            auto dfs = [&](auto dfs, const PermutationTree& u, std::size_t d)\
    \ -> void {\n                if (d >= lines.size()) lines.emplace_back(t.length(),\
    \ ' ');\n                if (u.length() == 1) {\n                    lines[d][u.min_index()]\
    \ = '|';\n                } else {\n                    if (u.is_join_node())\
    \ {\n                        lines[d][u.min_index()] = '[';\n                \
    \        lines[d][u.max_index()] = ']';\n                    } else {\n      \
    \                  lines[d][u.min_index()] = '{';\n                        lines[d][u.max_index()]\
    \ = '}';\n                    }\n                }\n                for (const\
    \ auto& ch : u) dfs(dfs, ch, d + 1);\n            };\n            dfs(dfs, t,\
    \ 0);\n            for (const auto& line : lines) out << line << '\\n';\n    \
    \        return out;\n        }\n\n    private:\n        int len;\n        int\
    \ il, vl;\n        bool _is_join_node;\n\n        PermutationTree(int len, int\
    \ il, int vl) : base_type(), len(len), il(il), vl(vl), _is_join_node(true) {}\n\
    \n        static std::vector<std::vector<int>> left_strong_intervals(const std::vector<int>&\
    \ p) {\n            const int n = p.size();\n\n            struct DoublyLinkedList\
    \ {\n                using list_node_pointer = DoublyLinkedList*;\n          \
    \      int idx, delta, max_idx, min_idx;\n                list_node_pointer prv\
    \ = nullptr, nxt = nullptr;\n                DoublyLinkedList(int idx) : idx(idx)\
    \ {}\n            };\n            using list_node_pointer = DoublyLinkedList::list_node_pointer;\n\
    \            list_node_pointer tail = nullptr;\n\n            using minmax_stack\
    \ = std::vector<std::pair<int, list_node_pointer>>;\n            minmax_stack\
    \ max_val, min_val;\n\n            auto erase = [&](list_node_pointer node) ->\
    \ list_node_pointer {\n                list_node_pointer nxt = node->nxt, prv\
    \ = node->prv;\n                if (list_node_pointer& nl = max_val[node->max_idx].second;\
    \ node == nl) nl = nxt and nxt->max_idx == node->max_idx ? nxt : nullptr;\n  \
    \              if (list_node_pointer& nl = min_val[node->min_idx].second; node\
    \ == nl) nl = nxt and nxt->min_idx == node->min_idx ? nxt : nullptr;\n       \
    \         if (nxt) nxt->prv = prv, nxt->delta += node->delta;\n              \
    \  if (prv) prv->nxt = nxt;\n                delete node;\n                return\
    \ nxt;\n            };\n            auto pop_tail = [&] { erase(std::exchange(tail,\
    \ tail->prv)); };\n\n            std::vector<std::vector<int>> select(n);\n  \
    \          for (int i = 0, pl = n; i < n; ++i) {\n                while (tail\
    \ and tail->idx > pl) pop_tail();\n                list_node_pointer new_node\
    \ = new DoublyLinkedList(i);\n                auto rec_update = [&](auto rec_update,\
    \ minmax_stack& vals, list_node_pointer nr, auto comp) -> bool {\n           \
    \         if (vals.empty()) return false;\n                    auto [val, nl]\
    \ = vals.back();\n                    if (comp(val, p[i])) return false;\n   \
    \                 vals.pop_back();\n                    if (not nl) nl = nr;\n\
    \                    if (not rec_update(rec_update, vals, nl, comp)) {\n     \
    \                   list_node_pointer new_tail = nullptr;\n                  \
    \      if (nl) {\n                            new_tail = nl->prv;\n          \
    \                  nl->delta -= std::abs(val - p[i]);\n                      \
    \      while (nl != nr and nl->delta < 0) nl = erase(nl);\n                  \
    \          if (nl == nr) {\n                                nl = new_node;\n \
    \                           } else {\n                                new_tail\
    \ = nr ? nr->prv : tail;\n                            }\n                    \
    \    } else {\n                            nl = new_node;\n                  \
    \          new_tail = nr ? nr->prv : tail;\n                        }\n      \
    \                  for (list_node_pointer cur = nr; cur;) cur = erase(cur);\n\
    \                        vals.emplace_back(p[i], nl);\n                      \
    \  tail = new_tail;\n                    }\n                    return true;\n\
    \                };\n                if (not rec_update(rec_update, max_val, nullptr,\
    \ std::greater<int>())) max_val.emplace_back(p[i], new_node);\n              \
    \  if (not rec_update(rec_update, min_val, nullptr, std::less<int>()))    min_val.emplace_back(p[i],\
    \ new_node);\n                new_node->max_idx = max_val.size() - 1;\n      \
    \          new_node->min_idx = min_val.size() - 1;\n\n                auto splitter_num\
    \ = [&](list_node_pointer node) {\n                    return (max_val[node->max_idx].first\
    \ - min_val[node->min_idx].first) - (i - node->idx);\n                };\n\n \
    \               if (tail) {\n                    new_node->prv = tail;\n     \
    \               tail->nxt = new_node;\n                    new_node->delta = splitter_num(tail);\n\
    \                } else {\n                    new_node->delta = std::numeric_limits<int>::max()\
    \ / 2;\n                }\n                tail = new_node;\n                if\
    \ (list_node_pointer& nl = min_val.back().second; not nl) nl = tail;\n       \
    \         if (list_node_pointer& nl = max_val.back().second; not nl) nl = tail;\n\
    \n                for (list_node_pointer cur = tail; cur and splitter_num(cur)\
    \ == 0; cur = cur->prv) {\n                    select[i].push_back(cur->idx);\n\
    \                }\n                pl = select[i].back();\n            }\n  \
    \          while (tail) pop_tail();\n\n            return select;\n        }\n\
    \n        static std::vector<std::vector<int>> right_strong_intervals(std::vector<int>\
    \ p) {\n            const int n = p.size();\n            std::reverse(p.begin(),\
    \ p.end());\n            std::vector<std::vector<int>> res(n);\n            auto\
    \ tmp = left_strong_intervals(p);\n            for (int r = 0; r < n; ++r) for\
    \ (int l : tmp[r]) res[n - l - 1].push_back(n - r - 1);\n            return res;\n\
    \        }\n\n        static bool connectable(const std::pair<int, int>& p, const\
    \ std::pair<int, int>& q) {\n            return std::max(p.second, q.second) -\
    \ std::min(p.first, q.first) == (p.second - p.first) + (q.second - q.first);\n\
    \        }\n\n        static PermutationTree build(const std::vector<int>& p)\
    \ {\n            const int n = p.size();\n            std::vector<std::vector<int>>\
    \ sel_l = left_strong_intervals(p);\n            std::vector<std::vector<int>>\
    \ sel_r = right_strong_intervals(p);\n\n            std::vector<PermutationTree>\
    \ ch;\n            ch.reserve(n);\n\n            // strong intervals are enumerated\
    \ in post order of dfs.\n            for (int r = 0; r < n; ++r) {\n         \
    \       // iterate on the intersection of sel_l[r] and sel_r[r]\n            \
    \    for (auto it1 = sel_l[r].cbegin(), end1 = sel_l[r].cend(), it2 = sel_r[r].cbegin(),\
    \ end2 = sel_r[r].cend(); ; ++it1, ++it2) {\n                    while (it1 !=\
    \ end1 and it2 != end2 and *it1 != *it2) ++(*it1 > *it2 ? it1 : it2);\n      \
    \              if (it1 == end1 or it2 == end2) break;\n                    const\
    \ int l = *it1;\n                    if (l == r) { // leaf\n                 \
    \       ch.push_back(PermutationTree(1, l, p[l]));\n                        continue;\n\
    \                    }\n                    int vl = std::numeric_limits<int>::max();\n\
    \                    auto it = ch.end();\n                    while ((--it)->il\
    \ != l) vl = std::min(vl, it->vl);\n                    PermutationTree t(r -\
    \ l + 1, l, std::min(vl, it->vl));\n                    t.resize(ch.end() - it);\n\
    \                    std::move(it, ch.end(), t.begin());\n                   \
    \ t._is_join_node = connectable(t[0].get_value_range(), t[1].get_value_range());\n\
    \                    ch.erase(it, ch.end());\n                    ch.push_back(std::move(t));\n\
    \                }\n            }\n            return std::move(ch.back());\n\
    \        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_PERMUTATION_TREE\n#define SUISEN_PERMUTATION_TREE\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct PermutationTree : std::vector<PermutationTree>\
    \ {\n        using base_type = std::vector<PermutationTree>;\n\n        PermutationTree()\
    \ : PermutationTree(0, 0, 0) {}\n\n        PermutationTree(const std::vector<int>&\
    \ p) : PermutationTree(build(p)) {}\n\n        int length() const { return len;\
    \ }\n\n        int begin_index() const { return il; }\n        int end_index()\
    \ const { return il + len; }\n        int min_index() const { return begin_index();\
    \ }\n        int max_index() const { return end_index() - 1; }\n        std::pair<int,\
    \ int> get_index_range() const { return { begin_index(), end_index() }; }\n  \
    \      std::pair<int, int> get_index_range_closed() const { return { min_index(),\
    \ max_index() }; }\n\n        int begin_value() const { return vl; }\n       \
    \ int end_value() const { return vl + len; }\n        int min_value() const {\
    \ return begin_value(); }\n        int max_value() const { return end_value()\
    \ - 1; }\n        std::pair<int, int> get_value_range() const { return { begin_value(),\
    \ end_value() }; }\n        std::pair<int, int> get_value_range_closed() const\
    \ { return { min_value(), max_value() }; }\n\n        bool is_join_node() const\
    \ { return _is_join_node; }\n\n        friend std::ostream& operator<<(std::ostream&\
    \ out, const PermutationTree& t) {\n            std::vector<std::string> lines;\n\
    \            auto dfs = [&](auto dfs, const PermutationTree& u, std::size_t d)\
    \ -> void {\n                if (d >= lines.size()) lines.emplace_back(t.length(),\
    \ ' ');\n                if (u.length() == 1) {\n                    lines[d][u.min_index()]\
    \ = '|';\n                } else {\n                    if (u.is_join_node())\
    \ {\n                        lines[d][u.min_index()] = '[';\n                \
    \        lines[d][u.max_index()] = ']';\n                    } else {\n      \
    \                  lines[d][u.min_index()] = '{';\n                        lines[d][u.max_index()]\
    \ = '}';\n                    }\n                }\n                for (const\
    \ auto& ch : u) dfs(dfs, ch, d + 1);\n            };\n            dfs(dfs, t,\
    \ 0);\n            for (const auto& line : lines) out << line << '\\n';\n    \
    \        return out;\n        }\n\n    private:\n        int len;\n        int\
    \ il, vl;\n        bool _is_join_node;\n\n        PermutationTree(int len, int\
    \ il, int vl) : base_type(), len(len), il(il), vl(vl), _is_join_node(true) {}\n\
    \n        static std::vector<std::vector<int>> left_strong_intervals(const std::vector<int>&\
    \ p) {\n            const int n = p.size();\n\n            struct DoublyLinkedList\
    \ {\n                using list_node_pointer = DoublyLinkedList*;\n          \
    \      int idx, delta, max_idx, min_idx;\n                list_node_pointer prv\
    \ = nullptr, nxt = nullptr;\n                DoublyLinkedList(int idx) : idx(idx)\
    \ {}\n            };\n            using list_node_pointer = DoublyLinkedList::list_node_pointer;\n\
    \            list_node_pointer tail = nullptr;\n\n            using minmax_stack\
    \ = std::vector<std::pair<int, list_node_pointer>>;\n            minmax_stack\
    \ max_val, min_val;\n\n            auto erase = [&](list_node_pointer node) ->\
    \ list_node_pointer {\n                list_node_pointer nxt = node->nxt, prv\
    \ = node->prv;\n                if (list_node_pointer& nl = max_val[node->max_idx].second;\
    \ node == nl) nl = nxt and nxt->max_idx == node->max_idx ? nxt : nullptr;\n  \
    \              if (list_node_pointer& nl = min_val[node->min_idx].second; node\
    \ == nl) nl = nxt and nxt->min_idx == node->min_idx ? nxt : nullptr;\n       \
    \         if (nxt) nxt->prv = prv, nxt->delta += node->delta;\n              \
    \  if (prv) prv->nxt = nxt;\n                delete node;\n                return\
    \ nxt;\n            };\n            auto pop_tail = [&] { erase(std::exchange(tail,\
    \ tail->prv)); };\n\n            std::vector<std::vector<int>> select(n);\n  \
    \          for (int i = 0, pl = n; i < n; ++i) {\n                while (tail\
    \ and tail->idx > pl) pop_tail();\n                list_node_pointer new_node\
    \ = new DoublyLinkedList(i);\n                auto rec_update = [&](auto rec_update,\
    \ minmax_stack& vals, list_node_pointer nr, auto comp) -> bool {\n           \
    \         if (vals.empty()) return false;\n                    auto [val, nl]\
    \ = vals.back();\n                    if (comp(val, p[i])) return false;\n   \
    \                 vals.pop_back();\n                    if (not nl) nl = nr;\n\
    \                    if (not rec_update(rec_update, vals, nl, comp)) {\n     \
    \                   list_node_pointer new_tail = nullptr;\n                  \
    \      if (nl) {\n                            new_tail = nl->prv;\n          \
    \                  nl->delta -= std::abs(val - p[i]);\n                      \
    \      while (nl != nr and nl->delta < 0) nl = erase(nl);\n                  \
    \          if (nl == nr) {\n                                nl = new_node;\n \
    \                           } else {\n                                new_tail\
    \ = nr ? nr->prv : tail;\n                            }\n                    \
    \    } else {\n                            nl = new_node;\n                  \
    \          new_tail = nr ? nr->prv : tail;\n                        }\n      \
    \                  for (list_node_pointer cur = nr; cur;) cur = erase(cur);\n\
    \                        vals.emplace_back(p[i], nl);\n                      \
    \  tail = new_tail;\n                    }\n                    return true;\n\
    \                };\n                if (not rec_update(rec_update, max_val, nullptr,\
    \ std::greater<int>())) max_val.emplace_back(p[i], new_node);\n              \
    \  if (not rec_update(rec_update, min_val, nullptr, std::less<int>()))    min_val.emplace_back(p[i],\
    \ new_node);\n                new_node->max_idx = max_val.size() - 1;\n      \
    \          new_node->min_idx = min_val.size() - 1;\n\n                auto splitter_num\
    \ = [&](list_node_pointer node) {\n                    return (max_val[node->max_idx].first\
    \ - min_val[node->min_idx].first) - (i - node->idx);\n                };\n\n \
    \               if (tail) {\n                    new_node->prv = tail;\n     \
    \               tail->nxt = new_node;\n                    new_node->delta = splitter_num(tail);\n\
    \                } else {\n                    new_node->delta = std::numeric_limits<int>::max()\
    \ / 2;\n                }\n                tail = new_node;\n                if\
    \ (list_node_pointer& nl = min_val.back().second; not nl) nl = tail;\n       \
    \         if (list_node_pointer& nl = max_val.back().second; not nl) nl = tail;\n\
    \n                for (list_node_pointer cur = tail; cur and splitter_num(cur)\
    \ == 0; cur = cur->prv) {\n                    select[i].push_back(cur->idx);\n\
    \                }\n                pl = select[i].back();\n            }\n  \
    \          while (tail) pop_tail();\n\n            return select;\n        }\n\
    \n        static std::vector<std::vector<int>> right_strong_intervals(std::vector<int>\
    \ p) {\n            const int n = p.size();\n            std::reverse(p.begin(),\
    \ p.end());\n            std::vector<std::vector<int>> res(n);\n            auto\
    \ tmp = left_strong_intervals(p);\n            for (int r = 0; r < n; ++r) for\
    \ (int l : tmp[r]) res[n - l - 1].push_back(n - r - 1);\n            return res;\n\
    \        }\n\n        static bool connectable(const std::pair<int, int>& p, const\
    \ std::pair<int, int>& q) {\n            return std::max(p.second, q.second) -\
    \ std::min(p.first, q.first) == (p.second - p.first) + (q.second - q.first);\n\
    \        }\n\n        static PermutationTree build(const std::vector<int>& p)\
    \ {\n            const int n = p.size();\n            std::vector<std::vector<int>>\
    \ sel_l = left_strong_intervals(p);\n            std::vector<std::vector<int>>\
    \ sel_r = right_strong_intervals(p);\n\n            std::vector<PermutationTree>\
    \ ch;\n            ch.reserve(n);\n\n            // strong intervals are enumerated\
    \ in post order of dfs.\n            for (int r = 0; r < n; ++r) {\n         \
    \       // iterate on the intersection of sel_l[r] and sel_r[r]\n            \
    \    for (auto it1 = sel_l[r].cbegin(), end1 = sel_l[r].cend(), it2 = sel_r[r].cbegin(),\
    \ end2 = sel_r[r].cend(); ; ++it1, ++it2) {\n                    while (it1 !=\
    \ end1 and it2 != end2 and *it1 != *it2) ++(*it1 > *it2 ? it1 : it2);\n      \
    \              if (it1 == end1 or it2 == end2) break;\n                    const\
    \ int l = *it1;\n                    if (l == r) { // leaf\n                 \
    \       ch.push_back(PermutationTree(1, l, p[l]));\n                        continue;\n\
    \                    }\n                    int vl = std::numeric_limits<int>::max();\n\
    \                    auto it = ch.end();\n                    while ((--it)->il\
    \ != l) vl = std::min(vl, it->vl);\n                    PermutationTree t(r -\
    \ l + 1, l, std::min(vl, it->vl));\n                    t.resize(ch.end() - it);\n\
    \                    std::move(it, ch.end(), t.begin());\n                   \
    \ t._is_join_node = connectable(t[0].get_value_range(), t[1].get_value_range());\n\
    \                    ch.erase(it, ch.end());\n                    ch.push_back(std::move(t));\n\
    \                }\n            }\n            return std::move(ch.back());\n\
    \        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_PERMUTATION_TREE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/permutation_tree.hpp
  requiredBy: []
  timestamp: '2022-08-21 18:21:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/permutation_tree/common_interval_decomposition_tree.test.cpp
documentation_of: library/datastructure/permutation_tree.hpp
layout: document
title: Permutation Tree
---
## Permutation Tree

$[l,r]:=\{l,l+1,\ldots,r\}$

$\sigma$ : $[1,n]$ の順列

$\sigma([l,r]) = \{\sigma(l),\ldots,\sigma(r)\}$

$[l,r]$ が common interval: $\exists x,y\in [1,n]\; \text{s.t.}\; \sigma([l,r])=[x,y]$

common interval の集合 : $\mathcal{F}$

$[l,r]\in\mathcal{F}$ が Right-Strong Interval : $l\lt l'\leq r \lt r'$ ならば $[l',r']\notin\mathcal{F}$ (i.e. $l$ を含まず $r$ をまたぐような common interval がない)

$i$ に対して $r\in [i,n]$ が useless : 任意の $l\leq i$ に対して $[l,r]$ は right-strong interval でない

$\mathrm{Select}(i) = \{j \mid [i,j]\in\mathcal{F} \text{が right-strong interval} \}$

補題 1.

$m_i = \max\{j\mid [i,j]\in\mathcal{F} \}$ とすると、以下の 1,2 が成立

1. $\max \mathrm{Select}(i) = m_i$
2. $i\lt r\lt m_{i+1}$ なる $r$ は $i$ に対して useless

証明.

1. 背理法。$i \lt i' \leq m \lt m'$ で $[i',m']\in\mathcal{F}$ とすると $[i,m']\in\mathcal{F}$ で $m_i$ の最大性に矛盾。
2. $l\lt i+1\leq r\lt m_{i+1}$ かつ $[i+1,m_{i+1}]\in\mathcal{F}$ より $[l,r]$ は right-strong interval でない。

系 1.

$\sum_i \vert \mathrm{Select}(i) \vert \leq 2n$

証明.

$\mathrm{Select}(i) \setminus \{m_i\}$ たちはどの 2 つも共通要素を持たないことを示せば十分。任意に $i,j\in[1,n]\; (i\neq j)$ を固定する。

1. $j\lt i$ のとき
  
  任意に $r\in \mathrm{Select}(i) \setminus \{m_i\}$ を取る。
  $j \leq i - 1 \lt r \lt m _ {(i - 1) + 1}$ と補題 1 より $r\notin\mathrm{Select}(j)$。

2. $j \gt i$ のとき
  
  任意に $r\in \mathrm{Select}(i) \setminus \{m_i\}$ を取る。$r\in \mathrm{Select}(j) \setminus \{m_j\}$ と仮定する。$i\lt j \leq r \lt m_j$ かつ $[r,m_j]\in\mathcal{F}$ であるから、$[i,r]\in \mathrm{Select}(i)$ に矛盾。

アルゴリズム.

アイデア: $i$ を $n\to 1$ の順に走査し、$\mathrm{Select}(i)$ たちを変数 `Potential` を用いて計算する。`Potential` は $\{r \mid \exists l\leq i\leq r \;\text{s.t.}\;[l,r] \text{が right-strong interval}\}$ と等しくなるように上手く差分更新していく。

はじめ、`Potential` は空。