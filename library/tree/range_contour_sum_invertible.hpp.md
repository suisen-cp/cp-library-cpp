---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/range_contour_sum_invertible.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <array>\n#include <cassert>\n#include <deque>\n\
    #include <iostream>\n#include <queue>\n#include <random>\n#include <utility>\n\
    #include <vector>\n \n#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace\
    \ suisen {\n    namespace default_operator {\n        template <typename T>\n\
    \        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template\
    \ <typename T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n\
    \        template <typename T>\n        auto add(const T &x, const T &y) -> decltype(x\
    \ + y) { return x + y; }\n        template <typename T>\n        auto sub(const\
    \ T &x, const T &y) -> decltype(x - y) { return x - y; }\n        template <typename\
    \ T>\n        auto mul(const T &x, const T &y) -> decltype(x * y) { return x *\
    \ y; }\n        template <typename T>\n        auto div(const T &x, const T &y)\
    \ -> decltype(x / y) { return x / y; }\n        template <typename T>\n      \
    \  auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }\n   \
    \     template <typename T>\n        auto neg(const T &x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(const T &x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n    namespace default_operator_noref\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(T\
    \ x, T y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(T x, T y) -> decltype(x - y) { return x - y; }\n        template\
    \ <typename T>\n        auto mul(T x, T y) -> decltype(x * y) { return x * y;\
    \ }\n        template <typename T>\n        auto div(T x, T y) -> decltype(x /\
    \ y) { return x / y; }\n        template <typename T>\n        auto mod(T x, T\
    \ y) -> decltype(x % y) { return x % y; }\n        template <typename T>\n   \
    \     auto neg(T x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(T x) -> decltype(one<T>() / x)  { return one<T>() / x;\
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 15 \"library/tree/range_contour_sum_invertible.hpp\"\
    \n \nnamespace suisen {\n    template <typename T, T(*_add)(T, T) = default_operator_noref::add<T>,\
    \ T(*_zero)() = default_operator_noref::zero<T>, T(*_neg)(T) = default_operator_noref::neg>\n\
    \    struct RangeContourSumOnTree {\n        using value_type = T;\n    private:\n\
    \        struct InternalCumulativeSum {\n            InternalCumulativeSum(int\
    \ n = 0) : _n(n), _dat(n + 1, _zero()) {}\n            template <typename InputIterator>\n\
    \            InternalCumulativeSum(InputIterator first, InputIterator last) :\
    \ _n(last - first), _dat(_n + 1) {\n                _dat[0] = _zero();\n     \
    \           for (int i = 0; i < _n; ++i) _dat[i + 1] = _add(_dat[i], *first++);\n\
    \            }\n            value_type sum(int l, int r) const {\n           \
    \     l = std::max(0, l), r = std::min(r, _n);\n                return l < r ?\
    \ _add(_dat[r], _neg(_dat[l])) : _zero();\n            }\n        private:\n \
    \           int _n;\n            std::vector<value_type> _dat;\n        };\n \
    \       using sequence_type = InternalCumulativeSum;\n \n        struct AuxInfo\
    \ {\n            int8_t child_index;\n            int dist;\n        };\n \n \
    \       struct TreeNode {\n            std::vector<int> adj;\n            typename\
    \ std::array<AuxInfo, 30>::iterator info_it;\n            value_type dat;\n  \
    \      };\n    public:\n        RangeContourSumOnTree(int n = 0, const value_type&\
    \ fill_value = _zero()) : RangeContourSumOnTree(std::vector<value_type>(n, fill_value))\
    \ {}\n        RangeContourSumOnTree(const std::vector<value_type>& a) : _n(a.size()),\
    \ _nodes(_n), _par(2 * _n, -1), _info(_n), _subtrees(2 * _n), _ord(_n) {\n   \
    \         for (int i = 0; i < _n; ++i) _nodes[i].dat = a[i];\n        }\n \n \
    \       void add_edge(int u, int v) {\n            _nodes[u].adj.push_back(v);\n\
    \            _nodes[v].adj.push_back(u);\n        }\n        // O(NlogN)\n   \
    \     void build() {\n            std::mt19937 rng{ std::random_device{}() };\n\
    \            reorder(std::uniform_int_distribution<int>{ 0, _n - 1 }(rng));\n\
    \ \n            int new_node = _n;\n            std::vector<int> sub_size(2 *\
    \ _n, 0);\n            std::vector<int> ctr(2 * _n, -1);\n \n            std::vector<int>\
    \ head(2 * _n), tail(2 * _n), link(2 * _n);\n            for (int i = 0; i < _n;\
    \ ++i) head[i] = tail[i] = i;\n \n            std::vector<value_type> dat(_n);\n\
    \ \n            auto rec = [&](auto rec, int r, int siz) -> int {\n          \
    \      int c = -1;\n                auto get_centroid = [&](auto get_centroid,\
    \ int u, int p) -> void {\n                    sub_size[u] = 1;\n            \
    \        for (int v : _nodes[u].adj) if (v != p) {\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub_size[u]\
    \ = siz - sub_size[c];\n                            break;\n                 \
    \       }\n                        sub_size[u] += sub_size[v];\n             \
    \       }\n                    if (c < 0 and sub_size[u] * 2 > siz) c = u;\n \
    \               };\n                get_centroid(get_centroid, r, -1);\n \n  \
    \              for (int v : _nodes[c].adj) {\n                    const int comp_size\
    \ = sub_size[v];\n                    _nodes[v].adj.erase(std::find(_nodes[v].adj.begin(),\
    \ _nodes[v].adj.end(), c));\n                    ctr[v] = rec(rec, v, comp_size);\n\
    \                    sub_size[v] = comp_size;\n                }\n \n        \
    \        auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };\n\
    \                std::priority_queue<int, std::vector<int>, decltype(comp)> pq{\
    \ comp };\n \n                for (int v : _nodes[c].adj) {\n                \
    \    link[v] = -1;\n                    pq.push(v);\n                }\n \n  \
    \              auto build_sequence = [&, this](const int root_head, const bool\
    \ child_index) {\n                    std::deque<std::pair<int, int>> dq;\n  \
    \                  for (int root = root_head; root >= 0; root = link[root]) dq.emplace_back(root,\
    \ -1);\n                    value_type sum = _zero();\n                    auto\
    \ dat_it = dat.begin();\n                    int nxt = -1;\n                 \
    \   while (dq.size()) {\n                        const auto [u, pu] = dq.front();\n\
    \                        dq.pop_front();\n                        if (u == nxt)\
    \ *dat_it++ = std::exchange(sum, _zero()), nxt = -1;\n                       \
    \ auto& node = _nodes[u];\n                        *node.info_it++ = { child_index,\
    \ int(dat_it - dat.begin()) };\n                        sum = _add(sum, node.dat);\n\
    \                        for (int v : node.adj) if (v != pu) {\n             \
    \               dq.emplace_back(v, u);\n                            if (nxt <\
    \ 0) nxt = v;\n                        }\n                    }\n            \
    \        *dat_it++ = sum;\n                    return sequence_type(dat.begin(),\
    \ dat_it);\n                };\n \n                while (pq.size() >= 2) {\n\
    \                    const int u = pq.top(); pq.pop();\n                    const\
    \ int v = pq.top(); pq.pop();\n                    if (pq.empty()) {\n       \
    \                 _par[ctr[u]] = _par[ctr[v]] = c;\n                        _subtrees[c][0]\
    \ = build_sequence(head[u], 0);\n                        _subtrees[c][1] = build_sequence(head[v],\
    \ 1);\n                        break;\n                    }\n               \
    \     sub_size[new_node] = sub_size[u] + sub_size[v];\n                    ctr[new_node]\
    \ = new_node;\n                    _par[ctr[u]] = _par[ctr[v]] = new_node;\n \
    \                   _subtrees[new_node][0] = build_sequence(head[u], 0);\n   \
    \                 _subtrees[new_node][1] = build_sequence(head[v], 1);\n     \
    \               head[new_node] = head[u], tail[new_node] = tail[v], link[tail[u]]\
    \ = head[v];\n                    pq.push(new_node);\n                    ++new_node;\n\
    \                }\n                if (pq.size()) {\n                    int\
    \ u = pq.top(); pq.pop();\n                    _par[ctr[u]] = c;\n           \
    \         _subtrees[c][0] = build_sequence(head[u], 0);\n                }\n \
    \               for (int v : _nodes[c].adj) _nodes[v].adj.push_back(c);\n    \
    \            return c;\n            };\n            rec(rec, 0, _n);\n       \
    \     _par.resize(new_node), _par.shrink_to_fit();\n            _subtrees.resize(new_node),\
    \ _subtrees.shrink_to_fit();\n        }\n        // O(logN)\n        value_type\
    \ sum(int u, int dl, int dr) const {\n            u = _ord[u];\n            value_type\
    \ res = dl <= 0 and 0 < dr ? _nodes[u].dat : _zero();\n            res = _add(res,\
    \ _subtrees[u][0].sum(dl - 1, dr - 1));\n            res = _add(res, _subtrees[u][1].sum(dl\
    \ - 1, dr - 1));\n            int v = _par[u];\n            const auto it_end\
    \ = _nodes[u].info_it;\n            for (auto it = _info[u].begin(); it != it_end;\
    \ ++it) {\n                int ql = dl - it->dist - 2, qr = dr - it->dist - 2;\n\
    \                if (v < _n and ql <= -1 and -1 < qr) res = _add(res, _nodes[v].dat);\n\
    \                res = _add(res, _subtrees[std::exchange(v, _par[v])][it->child_index\
    \ ^ 1].sum(ql, qr));\n            }\n            return res;\n        }\n \n \
    \   private:\n        int _n;\n        std::vector<TreeNode> _nodes;\n       \
    \ std::vector<int> _par;\n        std::vector<std::array<AuxInfo, 30>> _info;\n\
    \        std::vector<std::array<sequence_type, 2>> _subtrees;\n \n        std::vector<int>\
    \ _ord;\n \n        void reorder(int s) {\n            _ord.assign(_n, -1);\n\
    \            int t = 0;\n            std::deque<int> dq{ s };\n            while\
    \ (dq.size()) {\n                int u = dq.front(); dq.pop_front();\n       \
    \         _ord[u] = t++;\n                for (int v : _nodes[u].adj) if (_ord[v]\
    \ < 0) dq.push_back(v);\n            }\n            assert(t == _n);\n       \
    \     std::vector<TreeNode> tmp(_n);\n            for (int i = 0; i < _n; ++i)\
    \ {\n                for (int& e : _nodes[i].adj) e = _ord[e];\n             \
    \   _nodes[i].info_it = _info[_ord[i]].begin();\n                tmp[_ord[i]]\
    \ = std::move(_nodes[i]);\n            }\n            _nodes.swap(tmp);\n    \
    \    }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_RANGE_CONTOUR_SUM_INVERTIBLE\n#define SUISEN_RANGE_CONTOUR_SUM_INVERTIBLE\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <deque>\n\
    #include <iostream>\n#include <queue>\n#include <random>\n#include <utility>\n\
    #include <vector>\n \n#include \"library/util/default_operator.hpp\"\n \nnamespace\
    \ suisen {\n    template <typename T, T(*_add)(T, T) = default_operator_noref::add<T>,\
    \ T(*_zero)() = default_operator_noref::zero<T>, T(*_neg)(T) = default_operator_noref::neg>\n\
    \    struct RangeContourSumOnTree {\n        using value_type = T;\n    private:\n\
    \        struct InternalCumulativeSum {\n            InternalCumulativeSum(int\
    \ n = 0) : _n(n), _dat(n + 1, _zero()) {}\n            template <typename InputIterator>\n\
    \            InternalCumulativeSum(InputIterator first, InputIterator last) :\
    \ _n(last - first), _dat(_n + 1) {\n                _dat[0] = _zero();\n     \
    \           for (int i = 0; i < _n; ++i) _dat[i + 1] = _add(_dat[i], *first++);\n\
    \            }\n            value_type sum(int l, int r) const {\n           \
    \     l = std::max(0, l), r = std::min(r, _n);\n                return l < r ?\
    \ _add(_dat[r], _neg(_dat[l])) : _zero();\n            }\n        private:\n \
    \           int _n;\n            std::vector<value_type> _dat;\n        };\n \
    \       using sequence_type = InternalCumulativeSum;\n \n        struct AuxInfo\
    \ {\n            int8_t child_index;\n            int dist;\n        };\n \n \
    \       struct TreeNode {\n            std::vector<int> adj;\n            typename\
    \ std::array<AuxInfo, 30>::iterator info_it;\n            value_type dat;\n  \
    \      };\n    public:\n        RangeContourSumOnTree(int n = 0, const value_type&\
    \ fill_value = _zero()) : RangeContourSumOnTree(std::vector<value_type>(n, fill_value))\
    \ {}\n        RangeContourSumOnTree(const std::vector<value_type>& a) : _n(a.size()),\
    \ _nodes(_n), _par(2 * _n, -1), _info(_n), _subtrees(2 * _n), _ord(_n) {\n   \
    \         for (int i = 0; i < _n; ++i) _nodes[i].dat = a[i];\n        }\n \n \
    \       void add_edge(int u, int v) {\n            _nodes[u].adj.push_back(v);\n\
    \            _nodes[v].adj.push_back(u);\n        }\n        // O(NlogN)\n   \
    \     void build() {\n            std::mt19937 rng{ std::random_device{}() };\n\
    \            reorder(std::uniform_int_distribution<int>{ 0, _n - 1 }(rng));\n\
    \ \n            int new_node = _n;\n            std::vector<int> sub_size(2 *\
    \ _n, 0);\n            std::vector<int> ctr(2 * _n, -1);\n \n            std::vector<int>\
    \ head(2 * _n), tail(2 * _n), link(2 * _n);\n            for (int i = 0; i < _n;\
    \ ++i) head[i] = tail[i] = i;\n \n            std::vector<value_type> dat(_n);\n\
    \ \n            auto rec = [&](auto rec, int r, int siz) -> int {\n          \
    \      int c = -1;\n                auto get_centroid = [&](auto get_centroid,\
    \ int u, int p) -> void {\n                    sub_size[u] = 1;\n            \
    \        for (int v : _nodes[u].adj) if (v != p) {\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub_size[u]\
    \ = siz - sub_size[c];\n                            break;\n                 \
    \       }\n                        sub_size[u] += sub_size[v];\n             \
    \       }\n                    if (c < 0 and sub_size[u] * 2 > siz) c = u;\n \
    \               };\n                get_centroid(get_centroid, r, -1);\n \n  \
    \              for (int v : _nodes[c].adj) {\n                    const int comp_size\
    \ = sub_size[v];\n                    _nodes[v].adj.erase(std::find(_nodes[v].adj.begin(),\
    \ _nodes[v].adj.end(), c));\n                    ctr[v] = rec(rec, v, comp_size);\n\
    \                    sub_size[v] = comp_size;\n                }\n \n        \
    \        auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };\n\
    \                std::priority_queue<int, std::vector<int>, decltype(comp)> pq{\
    \ comp };\n \n                for (int v : _nodes[c].adj) {\n                \
    \    link[v] = -1;\n                    pq.push(v);\n                }\n \n  \
    \              auto build_sequence = [&, this](const int root_head, const bool\
    \ child_index) {\n                    std::deque<std::pair<int, int>> dq;\n  \
    \                  for (int root = root_head; root >= 0; root = link[root]) dq.emplace_back(root,\
    \ -1);\n                    value_type sum = _zero();\n                    auto\
    \ dat_it = dat.begin();\n                    int nxt = -1;\n                 \
    \   while (dq.size()) {\n                        const auto [u, pu] = dq.front();\n\
    \                        dq.pop_front();\n                        if (u == nxt)\
    \ *dat_it++ = std::exchange(sum, _zero()), nxt = -1;\n                       \
    \ auto& node = _nodes[u];\n                        *node.info_it++ = { child_index,\
    \ int(dat_it - dat.begin()) };\n                        sum = _add(sum, node.dat);\n\
    \                        for (int v : node.adj) if (v != pu) {\n             \
    \               dq.emplace_back(v, u);\n                            if (nxt <\
    \ 0) nxt = v;\n                        }\n                    }\n            \
    \        *dat_it++ = sum;\n                    return sequence_type(dat.begin(),\
    \ dat_it);\n                };\n \n                while (pq.size() >= 2) {\n\
    \                    const int u = pq.top(); pq.pop();\n                    const\
    \ int v = pq.top(); pq.pop();\n                    if (pq.empty()) {\n       \
    \                 _par[ctr[u]] = _par[ctr[v]] = c;\n                        _subtrees[c][0]\
    \ = build_sequence(head[u], 0);\n                        _subtrees[c][1] = build_sequence(head[v],\
    \ 1);\n                        break;\n                    }\n               \
    \     sub_size[new_node] = sub_size[u] + sub_size[v];\n                    ctr[new_node]\
    \ = new_node;\n                    _par[ctr[u]] = _par[ctr[v]] = new_node;\n \
    \                   _subtrees[new_node][0] = build_sequence(head[u], 0);\n   \
    \                 _subtrees[new_node][1] = build_sequence(head[v], 1);\n     \
    \               head[new_node] = head[u], tail[new_node] = tail[v], link[tail[u]]\
    \ = head[v];\n                    pq.push(new_node);\n                    ++new_node;\n\
    \                }\n                if (pq.size()) {\n                    int\
    \ u = pq.top(); pq.pop();\n                    _par[ctr[u]] = c;\n           \
    \         _subtrees[c][0] = build_sequence(head[u], 0);\n                }\n \
    \               for (int v : _nodes[c].adj) _nodes[v].adj.push_back(c);\n    \
    \            return c;\n            };\n            rec(rec, 0, _n);\n       \
    \     _par.resize(new_node), _par.shrink_to_fit();\n            _subtrees.resize(new_node),\
    \ _subtrees.shrink_to_fit();\n        }\n        // O(logN)\n        value_type\
    \ sum(int u, int dl, int dr) const {\n            u = _ord[u];\n            value_type\
    \ res = dl <= 0 and 0 < dr ? _nodes[u].dat : _zero();\n            res = _add(res,\
    \ _subtrees[u][0].sum(dl - 1, dr - 1));\n            res = _add(res, _subtrees[u][1].sum(dl\
    \ - 1, dr - 1));\n            int v = _par[u];\n            const auto it_end\
    \ = _nodes[u].info_it;\n            for (auto it = _info[u].begin(); it != it_end;\
    \ ++it) {\n                int ql = dl - it->dist - 2, qr = dr - it->dist - 2;\n\
    \                if (v < _n and ql <= -1 and -1 < qr) res = _add(res, _nodes[v].dat);\n\
    \                res = _add(res, _subtrees[std::exchange(v, _par[v])][it->child_index\
    \ ^ 1].sum(ql, qr));\n            }\n            return res;\n        }\n \n \
    \   private:\n        int _n;\n        std::vector<TreeNode> _nodes;\n       \
    \ std::vector<int> _par;\n        std::vector<std::array<AuxInfo, 30>> _info;\n\
    \        std::vector<std::array<sequence_type, 2>> _subtrees;\n \n        std::vector<int>\
    \ _ord;\n \n        void reorder(int s) {\n            _ord.assign(_n, -1);\n\
    \            int t = 0;\n            std::deque<int> dq{ s };\n            while\
    \ (dq.size()) {\n                int u = dq.front(); dq.pop_front();\n       \
    \         _ord[u] = t++;\n                for (int v : _nodes[u].adj) if (_ord[v]\
    \ < 0) dq.push_back(v);\n            }\n            assert(t == _n);\n       \
    \     std::vector<TreeNode> tmp(_n);\n            for (int i = 0; i < _n; ++i)\
    \ {\n                for (int& e : _nodes[i].adj) e = _ord[e];\n             \
    \   _nodes[i].info_it = _info[_ord[i]].begin();\n                tmp[_ord[i]]\
    \ = std::move(_nodes[i]);\n            }\n            _nodes.swap(tmp);\n    \
    \    }\n    };\n} // namespace suisen\n\n#endif // SUISEN_RANGE_CONTOUR_SUM_INVERTIBLE\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/tree/range_contour_sum_invertible.hpp
  requiredBy: []
  timestamp: '2022-08-07 20:14:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/range_contour_sum_invertible.hpp
layout: document
title: Range Contour Sum Invertible
---
## Range Contour Sum Invertible