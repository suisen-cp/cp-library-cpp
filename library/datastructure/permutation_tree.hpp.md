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
  bundledCode: "#line 1 \"library/datastructure/permutation_tree.hpp\"\n\n\n\n#include\
    \ <atcoder/lazysegtree>\n#include <deque>\n#include <iostream>\n#include <limits>\n\
    \nnamespace suisen {\n\n    namespace internal::permutation_tree {\n        using\
    \ S = std::pair<int, int>;\n        using F = int;\n        S op(S x, S y) { return\
    \ (x.first == y.first ? x.second > y.second : x.first < y.first) ? x : y; }\n\
    \        S e() { return { std::numeric_limits<int>::max(), -1 }; }\n        S\
    \ mapping(F f, S x) { return { f + x.first, x.second }; }\n        F composition(F\
    \ f, F g) { return f + g; }\n        F id() { return 0; }\n        using RangeAddRangeMin\
    \ = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;\n    }\n\n \
    \   struct PermutationTree : std::vector<PermutationTree> {\n        using base_type\
    \ = std::vector<PermutationTree>;\n\n        template <typename RandomAccessibleContainer>\n\
    \        PermutationTree(const RandomAccessibleContainer& p) : PermutationTree(build(p))\
    \ {}\n\n        int size() const { return vr - vl; }\n\n        int begin_index()\
    \ const { return idx; }\n        int end_index() const { return idx + size();\
    \ }\n        int min_index() const { return begin_index(); }\n        int max_index()\
    \ const { return end_index() - 1; }\n        std::pair<int, int> get_index_range()\
    \ const { return { begin_index(), end_index() }; }\n        std::pair<int, int>\
    \ get_index_range_closed() const { return { min_index(), max_index() }; }\n  \
    \  \n        int begin_value() const { return vl; }\n        int end_value() const\
    \ { return vr; }\n        int min_value() const { return begin_value(); }\n  \
    \      int max_value() const { return end_value() - 1; }\n        std::pair<int,\
    \ int> get_value_range() const { return { begin_value(), end_value() }; }\n  \
    \      std::pair<int, int> get_value_range_closed() const { return { min_value(),\
    \ max_value() }; }\n\n        bool is_join_node() const { return _is_join_node;\
    \ }\n\n        friend std::ostream& operator<<(std::ostream& out, const PermutationTree&\
    \ t) {\n            std::vector<std::string> lines;\n            auto dfs = [&](auto\
    \ dfs, const PermutationTree &u, std::size_t d) -> void {\n                if\
    \ (d >= lines.size()) lines.emplace_back(t.size(), ' ');\n                if (u.size()\
    \ == 1) {\n                    lines[d][u.min_index()] = '|';\n              \
    \  } else {\n                    lines[d][u.min_index()] = '[';\n            \
    \        lines[d][u.max_index()] = ']';\n                }\n                for\
    \ (const auto& ch : u) dfs(dfs, ch, d + 1);\n            };\n            dfs(dfs,\
    \ t, 0);\n            for (const auto& line : lines) out << line << '\\n';\n \
    \           return out;\n        }\n\n    private:\n        int idx, vl, vr;\n\
    \        bool _is_join_node;\n\n        PermutationTree() : PermutationTree(0,\
    \ 0, 0, false) {}\n        template <typename ...Args>\n        PermutationTree(int\
    \ idx, int vl, int vr, bool is_join_node, Args &&...args) :\n            base_type(std::forward<Args>(args)...),\
    \ idx(idx), vl(vl), vr(vr), _is_join_node(is_join_node) {}\n\n        bool try_add_child(const\
    \ PermutationTree& node) {\n            if (not is_join_node() or (node.vl !=\
    \ vr and node.vr != vl) or empty()) return false;\n            int l0 = end()[-2].vl,\
    \ l1 = end()[-1].vl, l2 = node.vl;\n            if ((l0 < l1) ^ (l1 < l2)) return\
    \ false;\n            push_back(node);\n            vl = std::min(vl, node.vl),\
    \ vr = std::max(vr, node.vr);\n            return true;\n        }\n\n       \
    \ template <typename RandomAccessibleContainer>\n        static PermutationTree\
    \ build(const RandomAccessibleContainer& p) {\n            std::vector<PermutationTree>\
    \ st;\n            const int n = p.size();\n\n            internal::permutation_tree::RangeAddRangeMin\
    \ seg(n);\n\n            std::vector<std::pair<int, int>> max_val, min_val;\n\n\
    \            for (int i = 0; i < n; ++i) {\n                auto update = [&](std::vector<std::pair<int,\
    \ int>>& vals, auto comp) {\n                    seg.set(i, { i, i });\n     \
    \               int start = i;\n                    while (vals.size()) {\n  \
    \                      const auto& [val, idx] = vals.back();\n               \
    \         if (comp(val, p[i])) break;\n                        seg.apply(idx,\
    \ start, std::abs(val - p[i]));\n                        start = idx;\n      \
    \                  vals.pop_back();\n                    }\n                 \
    \   vals.emplace_back(p[i], start);\n                };\n                update(max_val,\
    \ std::greater<int>());\n                update(min_val, std::less<int>());\n\n\
    \                PermutationTree node{ i, p[i], p[i] + 1, true };\n          \
    \      while (true) {\n                    if (st.empty()) break;\n          \
    \          if (auto& top_node = st.back(); top_node.try_add_child(node)) {\n \
    \                       node = std::move(top_node);\n                        st.pop_back();\n\
    \                    } else if (node.vl == top_node.vr or node.vr == top_node.vl)\
    \ {\n                        node = PermutationTree {\n                      \
    \      top_node.idx,\n                            std::min(node.vl, top_node.vl),\n\
    \                            std::max(node.vr, top_node.vr),\n               \
    \             true,\n                            std::vector<PermutationTree>\
    \ { std::move(top_node), std::move(node) }\n                        };\n     \
    \                   st.pop_back();\n                    } else {\n           \
    \             int st_sum = i + 1 - (node.vr - node.vl);\n                    \
    \    const auto& [val, idx] = seg.prod(0, st_sum);\n                        if\
    \ (val != i) break;\n                        int vl = node.vl, vr = node.vr;\n\
    \                        auto it = st.end();\n                        for (int\
    \ erase_num = st_sum - idx; erase_num;) {\n                            --it;\n\
    \                            erase_num -= it->vr - it->vl;\n                 \
    \           vl = std::min(vl, it->vl), vr = std::max(vr, it->vr);\n          \
    \              }\n                        std::vector<PermutationTree> ch;\n \
    \                       std::move(it, st.end(), std::back_inserter(ch));\n   \
    \                     ch.push_back(std::move(node));\n                       \
    \ st.erase(it, st.end());\n                        node = PermutationTree { ch.front().idx,\
    \ vl, vr, false, std::move(ch) };\n                    }\n                }\n\
    \                st.push_back(std::move(node));\n            }\n            return\
    \ st.back();\n        }\n    };\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_PERMUTATION_TREE\n#define SUISEN_PERMUTATION_TREE\n\n#include\
    \ <atcoder/lazysegtree>\n#include <deque>\n#include <iostream>\n#include <limits>\n\
    \nnamespace suisen {\n\n    namespace internal::permutation_tree {\n        using\
    \ S = std::pair<int, int>;\n        using F = int;\n        S op(S x, S y) { return\
    \ (x.first == y.first ? x.second > y.second : x.first < y.first) ? x : y; }\n\
    \        S e() { return { std::numeric_limits<int>::max(), -1 }; }\n        S\
    \ mapping(F f, S x) { return { f + x.first, x.second }; }\n        F composition(F\
    \ f, F g) { return f + g; }\n        F id() { return 0; }\n        using RangeAddRangeMin\
    \ = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;\n    }\n\n \
    \   struct PermutationTree : std::vector<PermutationTree> {\n        using base_type\
    \ = std::vector<PermutationTree>;\n\n        template <typename RandomAccessibleContainer>\n\
    \        PermutationTree(const RandomAccessibleContainer& p) : PermutationTree(build(p))\
    \ {}\n\n        int size() const { return vr - vl; }\n\n        int begin_index()\
    \ const { return idx; }\n        int end_index() const { return idx + size();\
    \ }\n        int min_index() const { return begin_index(); }\n        int max_index()\
    \ const { return end_index() - 1; }\n        std::pair<int, int> get_index_range()\
    \ const { return { begin_index(), end_index() }; }\n        std::pair<int, int>\
    \ get_index_range_closed() const { return { min_index(), max_index() }; }\n  \
    \  \n        int begin_value() const { return vl; }\n        int end_value() const\
    \ { return vr; }\n        int min_value() const { return begin_value(); }\n  \
    \      int max_value() const { return end_value() - 1; }\n        std::pair<int,\
    \ int> get_value_range() const { return { begin_value(), end_value() }; }\n  \
    \      std::pair<int, int> get_value_range_closed() const { return { min_value(),\
    \ max_value() }; }\n\n        bool is_join_node() const { return _is_join_node;\
    \ }\n\n        friend std::ostream& operator<<(std::ostream& out, const PermutationTree&\
    \ t) {\n            std::vector<std::string> lines;\n            auto dfs = [&](auto\
    \ dfs, const PermutationTree &u, std::size_t d) -> void {\n                if\
    \ (d >= lines.size()) lines.emplace_back(t.size(), ' ');\n                if (u.size()\
    \ == 1) {\n                    lines[d][u.min_index()] = '|';\n              \
    \  } else {\n                    lines[d][u.min_index()] = '[';\n            \
    \        lines[d][u.max_index()] = ']';\n                }\n                for\
    \ (const auto& ch : u) dfs(dfs, ch, d + 1);\n            };\n            dfs(dfs,\
    \ t, 0);\n            for (const auto& line : lines) out << line << '\\n';\n \
    \           return out;\n        }\n\n    private:\n        int idx, vl, vr;\n\
    \        bool _is_join_node;\n\n        PermutationTree() : PermutationTree(0,\
    \ 0, 0, false) {}\n        template <typename ...Args>\n        PermutationTree(int\
    \ idx, int vl, int vr, bool is_join_node, Args &&...args) :\n            base_type(std::forward<Args>(args)...),\
    \ idx(idx), vl(vl), vr(vr), _is_join_node(is_join_node) {}\n\n        bool try_add_child(const\
    \ PermutationTree& node) {\n            if (not is_join_node() or (node.vl !=\
    \ vr and node.vr != vl) or empty()) return false;\n            int l0 = end()[-2].vl,\
    \ l1 = end()[-1].vl, l2 = node.vl;\n            if ((l0 < l1) ^ (l1 < l2)) return\
    \ false;\n            push_back(node);\n            vl = std::min(vl, node.vl),\
    \ vr = std::max(vr, node.vr);\n            return true;\n        }\n\n       \
    \ template <typename RandomAccessibleContainer>\n        static PermutationTree\
    \ build(const RandomAccessibleContainer& p) {\n            std::vector<PermutationTree>\
    \ st;\n            const int n = p.size();\n\n            internal::permutation_tree::RangeAddRangeMin\
    \ seg(n);\n\n            std::vector<std::pair<int, int>> max_val, min_val;\n\n\
    \            for (int i = 0; i < n; ++i) {\n                auto update = [&](std::vector<std::pair<int,\
    \ int>>& vals, auto comp) {\n                    seg.set(i, { i, i });\n     \
    \               int start = i;\n                    while (vals.size()) {\n  \
    \                      const auto& [val, idx] = vals.back();\n               \
    \         if (comp(val, p[i])) break;\n                        seg.apply(idx,\
    \ start, std::abs(val - p[i]));\n                        start = idx;\n      \
    \                  vals.pop_back();\n                    }\n                 \
    \   vals.emplace_back(p[i], start);\n                };\n                update(max_val,\
    \ std::greater<int>());\n                update(min_val, std::less<int>());\n\n\
    \                PermutationTree node{ i, p[i], p[i] + 1, true };\n          \
    \      while (true) {\n                    if (st.empty()) break;\n          \
    \          if (auto& top_node = st.back(); top_node.try_add_child(node)) {\n \
    \                       node = std::move(top_node);\n                        st.pop_back();\n\
    \                    } else if (node.vl == top_node.vr or node.vr == top_node.vl)\
    \ {\n                        node = PermutationTree {\n                      \
    \      top_node.idx,\n                            std::min(node.vl, top_node.vl),\n\
    \                            std::max(node.vr, top_node.vr),\n               \
    \             true,\n                            std::vector<PermutationTree>\
    \ { std::move(top_node), std::move(node) }\n                        };\n     \
    \                   st.pop_back();\n                    } else {\n           \
    \             int st_sum = i + 1 - (node.vr - node.vl);\n                    \
    \    const auto& [val, idx] = seg.prod(0, st_sum);\n                        if\
    \ (val != i) break;\n                        int vl = node.vl, vr = node.vr;\n\
    \                        auto it = st.end();\n                        for (int\
    \ erase_num = st_sum - idx; erase_num;) {\n                            --it;\n\
    \                            erase_num -= it->vr - it->vl;\n                 \
    \           vl = std::min(vl, it->vl), vr = std::max(vr, it->vr);\n          \
    \              }\n                        std::vector<PermutationTree> ch;\n \
    \                       std::move(it, st.end(), std::back_inserter(ch));\n   \
    \                     ch.push_back(std::move(node));\n                       \
    \ st.erase(it, st.end());\n                        node = PermutationTree { ch.front().idx,\
    \ vl, vr, false, std::move(ch) };\n                    }\n                }\n\
    \                st.push_back(std::move(node));\n            }\n            return\
    \ st.back();\n        }\n    };\n\n} // namespace suisen\n\n\n#endif // SUISEN_PERMUTATION_TREE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/permutation_tree.hpp
  requiredBy: []
  timestamp: '2022-01-15 00:27:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/permutation_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/permutation_tree.hpp
- /library/library/datastructure/permutation_tree.hpp.html
title: library/datastructure/permutation_tree.hpp
---
