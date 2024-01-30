---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/csr_graph.hpp
    title: Graph (CSR Format)
  - icon: ':heavy_check_mark:'
    path: library/tree/centroid_decomposition.hpp
    title: "\u91CD\u5FC3\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: library/tree/frequency_table_of_tree_distance.hpp
    title: Frequency Table Of Tree Distance
  - icon: ':heavy_check_mark:'
    path: library/util/timer.hpp
    title: Timer
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 1 \"test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include <iostream>\n\n#line 1 \"library/tree/frequency_table_of_tree_distance.hpp\"\
    \n\n\n\n#include <cmath>\n#line 6 \"library/tree/frequency_table_of_tree_distance.hpp\"\
    \n#include <atcoder/convolution>\n#line 1 \"library/tree/centroid_decomposition.hpp\"\
    \n\n\n\n#include <deque>\n#include <limits>\n#include <queue>\n#include <tuple>\n\
    #include <vector>\n#line 1 \"library/graph/csr_graph.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#line 7 \"library/graph/csr_graph.hpp\"\n#include <optional>\n\
    #include <type_traits>\n#line 10 \"library/graph/csr_graph.hpp\"\n#include <utility>\n\
    #line 12 \"library/graph/csr_graph.hpp\"\n\nnamespace suisen {\n    namespace\
    \ internal::csr_graph { struct graph_base_tag {}; }\n    struct directed_graph_tag\
    \ : internal::csr_graph::graph_base_tag {};\n    struct undirected_graph_tag :\
    \ internal::csr_graph::graph_base_tag {};\n    template <typename T>\n    struct\
    \ is_graph_tag { static constexpr bool value = std::is_base_of_v<internal::csr_graph::graph_base_tag,\
    \ T>; };\n    template <typename T>\n    constexpr bool is_graph_tag_v = is_graph_tag<T>::value;\n\
    \n    template <typename WeightType = void>\n    struct Graph {\n        template\
    \ <typename GraphTag, typename, std::enable_if_t<is_graph_tag_v<GraphTag>, std::nullptr_t>>\n\
    \        friend struct GraphBuilder;\n\n        using weight_type = WeightType;\n\
    \        static constexpr bool weighted = std::negation_v<std::is_same<weight_type,\
    \ void>>;\n\n        using weight_type_or_1 = std::conditional_t<weighted, weight_type,\
    \ int>;\n\n        using input_edge_type = std::conditional_t<weighted, std::tuple<int,\
    \ int, weight_type>, std::pair<int, int>>;\n    private:\n        using internal_edge_type\
    \ = std::conditional_t<weighted, std::pair<int, weight_type>, int>;\n        struct\
    \ Edge : public internal_edge_type {\n            using internal_edge_type::internal_edge_type;\n\
    \            operator int() const { return std::get<0>(*this); }\n        };\n\
    \    public:\n        using edge_type = std::conditional_t<weighted, Edge, int>;\n\
    \    private:\n        struct AdjacentList {\n            friend struct Graph;\n\
    \n            using value_type = edge_type;\n            using iterator = typename\
    \ std::vector<value_type>::iterator;\n            using const_iterator = typename\
    \ std::vector<value_type>::const_iterator;\n            using reverse_iterator\
    \ = typename std::vector<value_type>::reverse_iterator;\n            using const_reverse_iterator\
    \ = typename std::vector<value_type>::const_reverse_iterator;\n\n            AdjacentList()\
    \ = default;\n\n            int size() const { return _siz; }\n            bool\
    \ empty() const { return _siz == 0; }\n            int capacity() const { return\
    \ _cap; }\n\n            value_type& operator[](int i) { return *(begin() + i);\
    \ }\n            const value_type& operator[](int i) const { return *(cbegin()\
    \ + i); }\n            value_type& at(uint32_t i) { assert(i < _siz); return *(begin()\
    \ + i); }\n            const value_type& at(uint32_t i) const { assert(i < _siz);\
    \ return *(cbegin() + i); }\n\n            value_type* data() { return _g->_edges.data()\
    \ + _offset; }\n            const value_type* data() const { return _g->_edges.data()\
    \ + _offset; }\n\n            iterator begin() const { return _g->_edges.begin()\
    \ + _offset; }\n            iterator end() const { return begin() + _siz; }\n\
    \            const_iterator cbegin() const { return _g->_edges.cbegin() + _offset;\
    \ }\n            const_iterator cend() const { return cbegin() + _siz; }\n   \
    \         reverse_iterator rbegin() const { return _g->_edges.rbegin() + (_g->_edges.size()\
    \ - (_offset + _siz)); }\n            reverse_iterator rend() const { return rbegin()\
    \ + _siz; }\n            const_reverse_iterator crbegin() const { return _g->_edges.crbegin()\
    \ + (_g->_edges.size() - (_offset + _siz)); }\n            const_reverse_iterator\
    \ crend() const { return crbegin() + _siz; }\n\n            void erase(const_iterator\
    \ pos) {\n                erase(pos, std::next(pos));\n            }\n       \
    \     void erase(const_iterator first, const_iterator last) {\n              \
    \  const int num = last - first, k = first - cbegin();\n                assert(num\
    \ >= 0);\n                if (num == 0) return;\n                assert(0 <= k\
    \ and k <= _siz - num);\n                std::move(begin() + k + num, end(), begin()\
    \ + k);\n                _siz -= num;\n            }\n            void pop_back()\
    \ {\n                assert(_siz);\n                --_siz;\n            }\n \
    \           void clear() { _siz = 0; }\n\n            const value_type& back()\
    \ const { return *--cend(); }\n            value_type& back() { return *--end();\
    \ }\n            const value_type& front() const { return *cbegin(); }\n     \
    \       value_type& front() { return *begin(); }\n\n            void push_back(const\
    \ value_type& x) {\n                ++_siz;\n                assert(_siz <= _cap);\n\
    \                back() = x;\n            }\n            template <typename ...Args>\n\
    \            void emplace_back(Args &&...args) {\n                ++_siz;\n  \
    \              assert(_siz <= _cap);\n                back() = value_type(std::forward<Args>(args)...);\n\
    \            }\n\n            void insert(const_iterator pos, const value_type&\
    \ x) {\n                emplace(pos, x);\n            }\n            void insert(const_iterator\
    \ pos, int num, const value_type& x) {\n                const int k = pos - cbegin();\n\
    \                assert(0 <= k and k <= _siz);\n                std::fill(begin()\
    \ + k, shift_back(begin() + k, num), x);\n            }\n            template\
    \ <class RandomAccessIterator>\n            auto insert(const_iterator pos, RandomAccessIterator\
    \ first, RandomAccessIterator last) -> decltype(*first++, last - first, void())\
    \ {\n                const int num = last - first, k = pos - cbegin();\n     \
    \           assert(0 <= k and k <= _siz);\n                shift_back(begin()\
    \ + k, num);\n                std::copy(first, last, begin() + k);\n         \
    \   }\n            void insert(const_iterator pos, std::initializer_list<value_type>\
    \ il) { insert(pos, il.begin(), il.end()); }\n            template <typename ...Args>\n\
    \            void emplace(const_iterator pos, Args &&...args) {\n            \
    \    const int k = pos - cbegin();\n                assert(0 <= k and k <= _siz);\n\
    \                *--shift_back(begin() + k) = value_type(std::forward<Args>(args)...);\n\
    \            }\n        private:\n            mutable Graph* _g;\n           \
    \ int _cap;\n            int _offset;\n            int _siz;\n\n            iterator\
    \ shift_back(iterator pos, int num = 1) {\n                _siz += num;\n    \
    \            assert(_siz <= _cap);\n                return std::move_backward(pos,\
    \ end() - num, end());\n            }\n        };\n    public:\n        using\
    \ adjacent_list = AdjacentList;\n\n        Graph() = default;\n\n        template\
    \ <typename GraphTag, std::enable_if_t<is_graph_tag_v<GraphTag>, std::nullptr_t>\
    \ = nullptr>\n        Graph(const int n, const std::vector<input_edge_type>& edges,\
    \ GraphTag, std::vector<int> cap = {}) : _n(n), _adj(_n) {\n            static\
    \ constexpr bool undirected = std::is_same_v<undirected_graph_tag, GraphTag>;\n\
    \n            for (const auto& e : edges) {\n                const int u = std::get<0>(e);\n\
    \                ++_adj[u]._siz;\n                if constexpr (undirected) {\n\
    \                    const int v = std::get<1>(e);\n                    ++_adj[v]._siz;\n\
    \                }\n            }\n            if (cap.empty()) cap.resize(_n,\
    \ std::numeric_limits<int>::max());\n            int edge_num = 0;\n         \
    \   for (int i = 0; i < _n; ++i) {\n                _adj[i]._g = this;\n     \
    \           _adj[i]._cap = std::min(_adj[i]._siz, cap[i]);\n                _adj[i]._offset\
    \ = edge_num;\n                edge_num += _adj[i]._siz;\n            }\n    \
    \        _edges.resize(edge_num);\n            std::vector<typename std::vector<edge_type>::iterator>\
    \ ptr(_n);\n            for (int i = 0; i < _n; ++i) ptr[i] = _adj[i].begin();\n\
    \            for (const auto& e : edges) {\n                const int u = std::get<0>(e);\n\
    \                const int v = std::get<1>(e);\n                if constexpr (weighted)\
    \ {\n                    const weight_type& w = std::get<2>(e);\n            \
    \        *ptr[u]++ = { v, w };\n                    if constexpr (undirected)\
    \ *ptr[v]++ = { u, w };\n                } else {\n                    *ptr[u]++\
    \ = v;\n                    if constexpr (undirected) *ptr[v]++ = u;\n       \
    \         }\n            }\n        }\n        Graph(const std::vector<std::vector<edge_type>>&\
    \ g) : Graph(g.size(), make_edges(g), directed_graph_tag{}) {}\n\n        static\
    \ Graph create_directed_graph(const int n, const std::vector<input_edge_type>&\
    \ edges, const std::vector<int>& cap = {}) {\n            return Graph(n, edges,\
    \ directed_graph_tag{}, cap);\n        }\n        static Graph create_undirected_graph(const\
    \ int n, const std::vector<input_edge_type>& edges, const std::vector<int>& cap\
    \ = {}) {\n            return Graph(n, edges, undirected_graph_tag{}, cap);\n\
    \        }\n\n        adjacent_list& operator[](int i) {\n            _adj[i]._g\
    \ = this;\n            return _adj[i];\n        }\n        const adjacent_list&\
    \ operator[](int i) const {\n            _adj[i]._g = const_cast<Graph*>(this);\n\
    \            return _adj[i];\n        }\n\n        int size() const {\n      \
    \      return _n;\n        }\n\n        void shrink_to_fit() {\n            int\
    \ edge_num = 0;\n            for (const auto& l : _adj) edge_num += l.size();\n\
    \n            std::vector<edge_type> new_edges(edge_num);\n            auto it\
    \ = new_edges.begin();\n            for (int i = 0; i < _n; ++i) {\n         \
    \       int nl = it - new_edges.begin();\n                it = std::move(_adj[i].begin(),\
    \ _adj[i].end(), it);\n                _adj[i]._offset = nl;\n               \
    \ _adj[i]._cap = _adj[i]._siz;\n            }\n            _edges.swap(new_edges);\n\
    \        }\n\n        static weight_type_or_1 get_weight(const edge_type& edge)\
    \ {\n            if constexpr (weighted) return std::get<1>(edge);\n         \
    \   else return 1;\n        }\n\n        Graph reversed(const std::vector<int>&\
    \ cap = {}) const {\n            std::vector<input_edge_type> edges;\n       \
    \     for (int i = 0; i < _n; ++i) {\n                for (const auto& edge :\
    \ (*this)[i]) {\n                    if constexpr (weighted) edges.emplace_back(std::get<0>(edge),\
    \ i, std::get<1>(edge));\n                    else edges.emplace_back(edge, i);\n\
    \                }\n            }\n            return Graph(_n, std::move(edges),\
    \ directed_graph_tag{}, cap);\n        }\n\n        struct DFSTree {\n       \
    \     std::vector<int> par;\n            std::vector<int> pre_ord, pst_ord;\n\
    \            Graph tree, back;\n        };\n\n        DFSTree dfs_tree(int start\
    \ = 0) const {\n            std::vector<input_edge_type> tree_edge, back_edge;\n\
    \n            std::vector<int> pre(_n), pst(_n);\n            auto pre_it = pre.begin(),\
    \ pst_it = pst.begin();\n\n            std::vector<int> eid(_n, -1), par(_n, -2);\n\
    \            std::vector<std::optional<weight_type_or_1>> par_w(_n, std::nullopt);\n\
    \            for (int i = 0; i < _n; ++i) {\n                int cur = (start\
    \ + i) % _n;\n                if (par[cur] != -2) continue;\n                par[cur]\
    \ = -1;\n                while (cur >= 0) {\n                    ++eid[cur];\n\
    \                    if (eid[cur] == 0) *pre_it++ = cur;\n                   \
    \ if (eid[cur] == _adj[cur].size()) {\n                        *pst_it++ = cur;\n\
    \                        cur = par[cur];\n                    } else {\n     \
    \                   const auto &e = _adj[cur][eid[cur]];\n                   \
    \     weight_type_or_1 w = get_weight(e);\n                        int nxt = e;\n\
    \                        if (par[nxt] == -2) {\n                            tree_edge.emplace_back(make_edge(cur,\
    \ e));\n                            par[nxt] = cur;\n                        \
    \    par_w[nxt] = std::move(w);\n                            cur = nxt;\n    \
    \                    } else if (eid[nxt] != _adj[nxt].size()) {\n            \
    \                if (par[cur] != nxt or par_w[cur] != w or not std::exchange(par_w[cur],\
    \ std::nullopt).has_value()) {\n                                back_edge.emplace_back(make_edge(cur,\
    \ e));\n                            }\n                        }\n           \
    \         }\n                }\n            }\n            Graph tree = create_directed_graph(_n,\
    \ tree_edge);\n            Graph back = create_directed_graph(_n, back_edge);\n\
    \            return DFSTree{ std::move(par), std::move(pre), std::move(pst), std::move(tree),\
    \ std::move(back) };\n        }\n\n    private:\n        int _n;\n        std::vector<adjacent_list>\
    \ _adj;\n        std::vector<edge_type> _edges;\n\n        static std::vector<input_edge_type>\
    \ make_edges(const std::vector<std::vector<edge_type>>& g) {\n            const\
    \ int n = g.size();\n            std::vector<input_edge_type> edges;\n       \
    \     for (int i = 0; i < n; ++i) for (const auto& e : g[i]) {\n             \
    \   edges.emplace_back(make_edge(i, e));\n            }\n            return edges;\n\
    \        }\n        static input_edge_type make_edge(int i, const edge_type& e)\
    \ {\n            if constexpr (weighted) return { i, std::get<0>(e), std::get<1>(e)\
    \ };\n            else return { i, e };\n        }\n    };\n\n    template <typename\
    \ GraphTag>\n    Graph(int, std::vector<std::pair<int, int>>, GraphTag, std::vector<int>\
    \ = {})->Graph<void>;\n    template <typename WeightType, typename GraphTag>\n\
    \    Graph(int, std::vector<std::tuple<int, int, WeightType>>, GraphTag, std::vector<int>\
    \ = {})->Graph<WeightType>;\n\n    Graph(std::vector<std::vector<int>>)->Graph<void>;\n\
    \    template <typename WeightType>\n    Graph(std::vector<std::vector<std::pair<int,\
    \ WeightType>>>)->Graph<WeightType>;\n\n    template <typename GraphTag, typename\
    \ WeightType = void,\n        std::enable_if_t<is_graph_tag_v<GraphTag>, std::nullptr_t>\
    \ = nullptr>\n    struct GraphBuilder {\n        using graph_tag = GraphTag;\n\
    \        using weight_type = WeightType;\n        using edge_type = typename Graph<weight_type>::input_edge_type;\n\
    \n        GraphBuilder(int n = 0) : _n(n) {}\n\n        void add_edge(const edge_type&\
    \ edge) {\n            check_not_moved();\n            _edges.push_back(edge);\n\
    \        }\n        template <typename ...Args>\n        void emplace_edge(Args\
    \ &&...args) {\n            check_not_moved();\n            _edges.emplace_back(std::forward<Args>(args)...);\n\
    \        }\n        template <typename EdgeContainer, std::enable_if_t<std::is_constructible_v<edge_type,\
    \ typename EdgeContainer::value_type>, std::nullptr_t> = nullptr>\n        void\
    \ add_edges(const EdgeContainer& edges) {\n            for (const auto& edge :\
    \ edges) add_edge(edge);\n        }\n\n        template <bool move_edges = true>\n\
    \        Graph<weight_type> build() {\n            if constexpr (move_edges) {\n\
    \                _moved = true;\n                return Graph<weight_type>(_n,\
    \ std::move(_edges), graph_tag{});\n            } else {\n                return\
    \ Graph<weight_type>(_n, _edges, graph_tag{});\n            }\n        }\n   \
    \     Graph<weight_type> build_without_move() {\n            return build<false>();\n\
    \        }\n\n        static Graph<weight_type> build(const int n, const std::vector<edge_type>&\
    \ edges) {\n            GraphBuilder builder(n);\n            builder.add_edges(edges);\n\
    \            return builder.build();\n        }\n    private:\n        int _n;\n\
    \        std::vector<edge_type> _edges;\n        bool _moved = false;\n\n    \
    \    void check_not_moved() {\n            if (not _moved) return;\n         \
    \   std::cerr << \"[\\033[31mERROR\\033[m] Edges are already moved. If you want\
    \ to add edges after calling build() and build another graph, you should use build_without_move()\
    \ instead.\" << std::endl;\n            assert(false);\n        }\n    };\n  \
    \  template <typename WeightType = void>\n    using DirectedGraphBuilder = GraphBuilder<directed_graph_tag,\
    \ WeightType>;\n    template <typename WeightType = void>\n    using UndirectedGraphBuilder\
    \ = GraphBuilder<undirected_graph_tag, WeightType>;\n\n    template <typename\
    \ Weight, std::enable_if_t<std::negation_v<std::is_same<Weight, void>>, std::nullptr_t>\
    \ = nullptr>\n    using WeightedGraph = Graph<Weight>;\n    using UnweightedGraph\
    \ = Graph<void>;\n\n    template <typename T>\n    struct is_weighted_graph {\
    \ static constexpr bool value = false; };\n    template <typename WeightType>\n\
    \    struct is_weighted_graph<Graph<WeightType>> { static constexpr bool value\
    \ = Graph<WeightType>::weighted; };\n    template <typename T>\n    constexpr\
    \ bool is_weighted_graph_v = is_weighted_graph<T>::value;\n\n    template <typename\
    \ T>\n    struct is_unweighted_graph { static constexpr bool value = false; };\n\
    \    template <typename WeightType>\n    struct is_unweighted_graph<Graph<WeightType>>\
    \ { static constexpr bool value = not Graph<WeightType>::weighted; };\n    template\
    \ <typename T>\n    constexpr bool is_unweighted_graph_v = is_unweighted_graph<T>::value;\n\
    } // namespace suisen\n\n\n#line 10 \"library/tree/centroid_decomposition.hpp\"\
    \n\nnamespace suisen {\n    namespace internal {\n        template <typename WeightType\
    \ = void>\n        struct CentroidDecomposition : Graph<WeightType> {\n      \
    \      friend struct CentroidDecompositionUnweighted;\n            template <typename\
    \ WeightType_, std::enable_if_t<not std::is_same_v<WeightType_, void>, std::nullptr_t>>\n\
    \            friend struct CentroidDecompositionWeighted;\n\n            using\
    \ graph_type = Graph<WeightType>;\n            using weight_type = WeightType;\n\
    \n            CentroidDecomposition(const graph_type& g) : graph_type(g), n(this->size()),\
    \ cpar(n, -1), cdep(n, std::numeric_limits<int>::max()), csiz(n) {\n         \
    \       build();\n            }\n\n            int dct_parent(int i) const { return\
    \ cpar[i]; }\n            int dct_depth(int i) const { return cdep[i]; }\n   \
    \         int dct_size(int i) const { return csiz[i]; }\n\n        private:\n\
    \            int n;\n            std::vector<int> cpar;\n            std::vector<int>\
    \ cdep;\n            std::vector<int> csiz;\n\n            void build() {\n  \
    \              std::vector<int> eid(n, 0);\n\n                cpar[0] = -1, csiz[0]\
    \ = n;\n                std::deque<std::tuple<int, int>> dq{ { 0, 0 } };\n\n \
    \               while (dq.size()) {\n                    const auto [r, dep] =\
    \ dq.front();\n                    const int siz = csiz[r], prev_ctr = cpar[r];\n\
    \                    dq.pop_front();\n\n                    int c = -1;\n    \
    \                eid[r] = 0, csiz[r] = 1, cpar[r] = -1;\n                    for\
    \ (int cur = r;;) {\n                        for (const int edge_num = int((*this)[cur].size());;)\
    \ {\n                            if (eid[cur] == edge_num) {\n               \
    \                 if (csiz[cur] * 2 > siz) {\n                               \
    \     c = cur;\n                                } else {\n                   \
    \                 const int nxt = cpar[cur];\n                               \
    \     csiz[nxt] += csiz[cur];\n                                    cur = nxt;\n\
    \                                }\n                                break;\n \
    \                           }\n                            const int nxt = (*this)[cur][eid[cur]++];\n\
    \                            if (cdep[nxt] >= dep and nxt != cpar[cur]) {\n  \
    \                              eid[nxt] = 0, csiz[nxt] = 1, cpar[nxt] = cur;\n\
    \                                cur = nxt;\n                                break;\n\
    \                            }\n                        }\n                  \
    \      if (c >= 0) break;\n                    }\n                    for (int\
    \ v : (*this)[c]) if (cdep[v] >= dep) {\n                        if (cpar[c] ==\
    \ v) cpar[v] = c, csiz[v] = siz - csiz[c];\n                        dq.emplace_back(v,\
    \ dep + 1);\n                    }\n                    cpar[c] = prev_ctr, cdep[c]\
    \ = dep, csiz[c] = siz;\n                }\n            }\n        };\n\n    \
    \    struct CentroidDecompositionUnweighted : internal::CentroidDecomposition<void>\
    \ {\n            using base_type = internal::CentroidDecomposition<void>;\n  \
    \          using base_type::base_type;\n\n            std::vector<std::vector<std::pair<int,\
    \ int>>> collect(int root, int root_val = 0) const {\n                std::vector<std::vector<std::pair<int,\
    \ int>>> res{ { { root, root_val } } };\n                for (int sub_root : (*this)[root])\
    \ if (this->cdep[sub_root] > this->cdep[root]) {\n                    res.emplace_back();\n\
    \                    std::deque<std::tuple<int, int, int>> dq{ { sub_root, root,\
    \ root_val + 1 } };\n                    while (dq.size()) {\n               \
    \         auto [u, p, w] = dq.front();\n                        dq.pop_front();\n\
    \                        res.back().emplace_back(u, w);\n                    \
    \    for (int v : (*this)[u]) if (v != p and this->cdep[v] > this->cdep[root])\
    \ {\n                            dq.emplace_back(v, u, w + 1);\n             \
    \           }\n                    }\n                    std::copy(res.back().begin(),\
    \ res.back().end(), std::back_inserter(res.front()));\n                }\n   \
    \             return res;\n            }\n        };\n\n        template <typename\
    \ WeightType, std::enable_if_t<not std::is_same_v<WeightType, void>, std::nullptr_t>\
    \ = nullptr>\n        struct CentroidDecompositionWeighted : internal::CentroidDecomposition<WeightType>\
    \ {\n            using base_type = internal::CentroidDecomposition<WeightType>;\n\
    \            using base_type::base_type;\n\n            using weight_type = typename\
    \ base_type::weight_type;\n\n            template <typename Op, std::enable_if_t<std::is_invocable_r_v<weight_type,\
    \ Op, weight_type, weight_type>, std::nullptr_t> = nullptr>\n            std::vector<std::vector<std::pair<int,\
    \ weight_type>>> collect(int root, Op op, weight_type root_val) const {\n    \
    \            std::vector<std::vector<std::pair<int, weight_type>>> res{ { { root,\
    \ root_val } } };\n                for (auto [sub_root, ew] : (*this)[root]) if\
    \ (this->cdep[sub_root] > this->cdep[root]) {\n                    res.emplace_back();\n\
    \                    std::deque<std::tuple<int, int, weight_type>> dq{ { sub_root,\
    \ root, op(root_val, ew) } };\n                    while (dq.size()) {\n     \
    \                   auto [u, p, w] = dq.front();\n                        dq.pop_front();\n\
    \                        res.back().emplace_back(u, w);\n                    \
    \    for (auto [v, ew] : (*this)[u]) if (v != p and this->cdep[v] > this->cdep[root])\
    \ {\n                            dq.emplace_back(v, u, op(w, ew));\n         \
    \               }\n                    }\n                    std::copy(res.back().begin(),\
    \ res.back().end(), std::back_inserter(res.front()));\n                }\n   \
    \             return res;\n            }\n        };\n    }\n\n    using CentroidDecompositionUnweighted\
    \ = internal::CentroidDecompositionUnweighted;\n    template <typename WeightType,\
    \ std::enable_if_t<not std::is_same_v<WeightType, void>, std::nullptr_t> = nullptr>\n\
    \    using CentroidDecompositionWeighted = internal::CentroidDecompositionWeighted<WeightType>;\n\
    \n} // namespace suisen\n\n\n#line 8 \"library/tree/frequency_table_of_tree_distance.hpp\"\
    \n\n#line 1 \"library/util/timer.hpp\"\n\n\n\n#include <chrono>\n\nnamespace suisen\
    \ {\n    struct Timer {\n        using minutes_t = std::chrono::minutes;\n   \
    \     using seconds_t = std::chrono::seconds;\n        using milliseconds_t =\
    \ std::chrono::milliseconds;\n        using microseconds_t = std::chrono::microseconds;\n\
    \        using nanoseconds_t = std::chrono::nanoseconds;\n\n        Timer() {\
    \ start(); }\n\n        void start() {\n            _start = std::chrono::system_clock::now();\n\
    \        }\n        template <typename TimeUnit = std::chrono::milliseconds>\n\
    \        double elapsed() const {\n            return std::chrono::duration_cast<TimeUnit>(std::chrono::system_clock::now()\
    \ - _start).count();\n        }\n\n        template <typename TimeUnit = std::chrono::milliseconds,\
    \ typename Proc>\n        static double measure(Proc &&proc) {\n            Timer\
    \ timer;\n            proc();\n            return timer.elapsed<TimeUnit>();\n\
    \        }\n    private:\n        decltype(std::chrono::system_clock::now()) _start;\n\
    \    };\n} // namespace suisen\n\n\n\n#line 10 \"library/tree/frequency_table_of_tree_distance.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * @brief Given a tree with N vertices, calculates\
    \ the number of unordered pair (u, v) s.t. dist(u, v) = k for k = 1, ..., N -\
    \ 1.\n     * @param n size of tree\n     * @param edges edges of tree\n     *\
    \ @return std::vector<long long> v : v[k] is the number of unordered pair (u,\
    \ v) s.t. dist(u, v) = k\n     */\n    std::vector<long long> frequency_table_of_tree_distance(const\
    \ size_t n, const std::vector<std::pair<int, int>>& edges) {\n        static constexpr\
    \ long long MOD1 = 998244353;\n        static constexpr long long MOD2 = 754974721;\n\
    \        static constexpr long long INV_MOD1 = atcoder::internal::inv_gcd(MOD1,\
    \ MOD2).second;\n\n        using mint1 = atcoder::static_modint<MOD1>;\n     \
    \   using mint2 = atcoder::static_modint<MOD2>;\n\n        auto garner = [](mint1\
    \ x1, mint2 x2) -> long long {\n            long long v1 = x1.val(), v2 = x2.val();\n\
    \            return mint2((v2 - v1) * INV_MOD1).val() * MOD1 + v1;\n        };\n\
    \n        std::vector<long long> res(n);\n\n        CentroidDecompositionUnweighted\
    \ g(UnweightedGraph::create_undirected_graph(n, edges));\n\n        const int\
    \ garner_threshold = ::sqrt(MOD1);\n\n        for (size_t root = 0; root < n;\
    \ ++root) {\n            std::vector<std::vector<std::pair<int, int>>> d = g.collect(root,\
    \ 0);\n            for (size_t i = 0; i < d.size(); ++i) {\n                int\
    \ max_dep = 0;\n                for (auto [v, w] : d[i]) max_dep = std::max(max_dep,\
    \ w);\n                std::vector<int> f(max_dep + 1);\n                for (auto\
    \ [v, w] : d[i]) ++f[w];\n\n                std::vector<int> sq_f1 = atcoder::convolution<mint1::mod()>(f,\
    \ f);\n                int coef = i == 0 ? +1 : -1;\n                if (d[i].size()\
    \ <= garner_threshold) {\n                    for (size_t i = 0; i < std::min(n,\
    \ sq_f1.size()); ++i) {\n                        res[i] += coef * sq_f1[i];\n\
    \                    }\n                } else {\n                    std::vector<int>\
    \ sq_f2 = atcoder::convolution<mint2::mod()>(f, f);\n                    for (size_t\
    \ i = 0; i < std::min(n, sq_f1.size()); ++i) {\n                        res[i]\
    \ += coef * garner(sq_f1[i], sq_f2[i]);\n                    }\n             \
    \   }\n            }\n        }\n\n        for (size_t i = 1; i < n; ++i) {\n\
    \            res[i] >>= 1;\n        }\n        return res;\n    }\n} // namespace\
    \ suisen\n\n\n\n#line 6 \"test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    size_t n;\n    std::cin >> n;\n\n    std::vector<std::pair<int, int>> edges(n\
    \ - 1);\n    for (size_t i = 0; i < n - 1; ++i) {\n        size_t u, v;\n    \
    \    std::cin >> u >> v;\n        edges[i] = { u, v };\n    }\n\n    std::vector<long\
    \ long> ans = suisen::frequency_table_of_tree_distance(n, edges);\n\n    for (size_t\
    \ d = 1; d < n; ++d) {\n        std::cout << ans[d];\n        if (d + 1 != n)\
    \ std::cout << ' ';\n    }\n    std::cout << '\\n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include <iostream>\n\n#include \"library/tree/frequency_table_of_tree_distance.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    size_t n;\n    std::cin >> n;\n\n    std::vector<std::pair<int, int>> edges(n\
    \ - 1);\n    for (size_t i = 0; i < n - 1; ++i) {\n        size_t u, v;\n    \
    \    std::cin >> u >> v;\n        edges[i] = { u, v };\n    }\n\n    std::vector<long\
    \ long> ans = suisen::frequency_table_of_tree_distance(n, edges);\n\n    for (size_t\
    \ d = 1; d < n; ++d) {\n        std::cout << ans[d];\n        if (d + 1 != n)\
    \ std::cout << ' ';\n    }\n    std::cout << '\\n';\n    return 0;\n}"
  dependsOn:
  - library/tree/frequency_table_of_tree_distance.hpp
  - library/tree/centroid_decomposition.hpp
  - library/graph/csr_graph.hpp
  - library/util/timer.hpp
  isVerificationFile: true
  path: test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
  requiredBy: []
  timestamp: '2022-10-30 21:38:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
- /verify/test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp.html
title: test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
---