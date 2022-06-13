---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
    title: Fenwick Tree Prefix
  - icon: ':heavy_check_mark:'
    path: library/graph/kruscal.hpp
    title: Kruscal
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/manhattan_mst/manhattanmst.test.cpp
    title: test/src/graph/manhattan_mst/manhattanmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/manhattan_mst.hpp\"\n\n\n\n#include <limits>\n\
    #include <numeric>\n#include <tuple>\n\n\n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T,\
    \ T), T(*e)()>\n    struct FenwickTreePrefix {\n        FenwickTreePrefix() :\
    \ FenwickTreePrefix(0) {}\n        explicit FenwickTreePrefix(int n) : _n(n),\
    \ _dat(_n + 1, e()) {}\n        FenwickTreePrefix(const std::vector<T> &dat) :\
    \ _n(dat.size()), _dat(_n + 1, e()) {\n            for (int i = _n; i > 0; --i)\
    \ {\n                _dat[i] = op(_dat[i], dat[i - 1]);\n                if (int\
    \ p = i + (-i & i); p <= _n) _dat[p] = op(_dat[p], _dat[i]);\n            }\n\
    \        }\n        void apply(int i, const T& val) {\n            for (++i; i\
    \ <= _n; i += -i & i) _dat[i] = op(_dat[i], val);\n        }\n        T prefix_query(int\
    \ r) const {\n            T res = e();\n            for (; r; r -= -r & r) res\
    \ = op(res, _dat[r]);\n            return res;\n        }\n    private:\n    \
    \    int _n;\n        std::vector<T> _dat;\n    };\n} // namespace suisen\n\n\n\
    \n#line 1 \"library/graph/kruscal.hpp\"\n\n\n\n#include <atcoder/dsu>\n\nnamespace\
    \ suisen {\n    namespace internal::kruscal {\n        // CostType: a type represents\
    \ weights of edges i.e. (unsigned) int, (unsigned) long long, ...\n        template\
    \ <typename CostType, typename ComparatorType>\n        struct KruscalMST {\n\
    \            using cost_type = CostType;\n            using edge_type = std::tuple<int,\
    \ int, cost_type>;\n            using comparator_type = ComparatorType;\n\n  \
    \          KruscalMST() : KruscalMST(0) {}\n            explicit KruscalMST(const\
    \ int n) : _n(n) {}\n\n            void add_edge(const int u, const int v, const\
    \ cost_type& cost) {\n                _built = false;\n                _edges.emplace_back(u,\
    \ v, cost);\n            }\n            void add_edge(const edge_type& e) {\n\
    \                _built = false;\n                _edges.push_back(e);\n     \
    \       }\n            /**\n             * constructs the MST in O(ElogE) time\
    \ using Kruskal's algprithm (E is the number of edges).\n             * return:\
    \ whether there exists MST or not (i.e. the graph is connected or not)\n     \
    \        */\n            bool build() {\n                _built = true;\n    \
    \            _weight_sum = 0;\n                if (_n == 0) return true;\n   \
    \             atcoder::dsu uf(_n);\n                std::sort(_edges.begin(),\
    \ _edges.end(), [this](const auto& e1, const auto& e2) { return _comp(std::get<2>(e1),\
    \ std::get<2>(e2)); });\n                for (auto& [u, v, w] : _edges) {\n  \
    \                  if (uf.same(u, v)) {\n                        u = v = _n;\n\
    \                    } else {\n                        uf.merge(u, v);\n     \
    \                   _weight_sum += w;\n                    }\n               \
    \ }\n                _edges.erase(std::remove_if(_edges.begin(), _edges.end(),\
    \ [this](auto& e) { return std::get<0>(e) == _n; }), _edges.end());\n        \
    \        return int(_edges.size()) == _n - 1;\n            }\n            /**\n\
    \             * ! This must not be called before calling `solve()`.\n        \
    \     * return:\n             * 1. connected: sum of weights of edges in the minimum\
    \ spanning tree\n             * 2. otherwise: sum of weights of edges in the minimum\
    \ spanning forest\n             */\n            cost_type get_weight() const {\n\
    \                assert(_built);\n                return _weight_sum;\n      \
    \      }\n            /**\n             * ! This must not be called before calling\
    \ `solve()`.\n             * return:\n             * 1. connected: edges in the\
    \ minimum spanning tree\n             * 2. otherwise: edges in the minimum spanning\
    \ forest\n             * It is guaranteed that edges[i] <= edges[j] iff i <= j.\n\
    \             */\n            const std::vector<edge_type>& get_mst() const {\n\
    \                assert(_built);\n                return _edges;\n           \
    \ }\n        private:\n            int _n;\n            cost_type _weight_sum;\n\
    \            std::vector<edge_type> _edges;\n            bool _built = false;\n\
    \            comparator_type _comp{};\n        };\n    } // namespace internal::kruscal\n\
    \n    template <typename CostType>\n    using KruscalMinimumSpanningTree = internal::kruscal::KruscalMST<CostType,\
    \ std::less<CostType>>;\n    template <typename CostType>\n    using KruscalMaximumSpanningTree\
    \ = internal::kruscal::KruscalMST<CostType, std::greater<CostType>>;\n} // namespace\
    \ suisen\n\n\n#line 11 \"library/graph/manhattan_mst.hpp\"\n\nnamespace suisen\
    \ {\n    namespace internal::manhattan_mst {\n        template <typename T>\n\
    \        std::pair<T, int> op(std::pair<T, int> x, std::pair<T, int> y) { return\
    \ std::max(x, y); };\n        template <typename T>\n        std::pair<T, int>\
    \ e() { return { std::numeric_limits<T>::min(), -1 }; };\n        template <typename\
    \ T>\n        using PrefixMaxQuery = FenwickTreePrefix<std::pair<T, int>, op<T>,\
    \ e<T>>;\n    } // namespace internal::manhattan_mst\n\n    template <typename\
    \ WeightType, typename T>\n    KruscalMinimumSpanningTree<WeightType> manhattan_mst(std::vector<std::pair<T,\
    \ T>> points) {\n        using namespace internal::manhattan_mst;\n\n        const\
    \ int n = points.size();\n        std::vector<int> p(n);\n        std::iota(p.begin(),\
    \ p.end(), 0);\n\n        auto make_edges = [&](KruscalMinimumSpanningTree<WeightType>\
    \ &mst) {\n            std::sort(\n                p.begin(), p.end(),\n     \
    \           [&points](int i, int j) {\n                    const auto &[xi, yi]\
    \ = points[i];\n                    const auto &[xj, yj] = points[j];\n      \
    \              return yi - xi == yj - xj ? xi < xj : yi - xi < yj - xj;\n    \
    \            }\n            );\n\n            std::vector<T> comp_x(n);\n    \
    \        for (int i = 0; i < n; ++i) comp_x[i] = points[i].first;\n          \
    \  std::sort(comp_x.begin(), comp_x.end());\n            comp_x.erase(std::unique(comp_x.begin(),\
    \ comp_x.end()), comp_x.end());\n            const int m = comp_x.size();\n\n\
    \            auto compress = [&](const T& x) { return std::lower_bound(comp_x.begin(),\
    \ comp_x.end(), x) - comp_x.begin(); };\n\n            PrefixMaxQuery<T> pmq(m);\n\
    \n            for (int i : p) {\n                const auto& [x, y] = points[i];\n\
    \                const int cx = compress(x);\n                if (const auto p\
    \ = pmq.prefix_query(cx + 1); p != e<T>()) {\n                    const auto&\
    \ [v, j] = p;\n                    mst.add_edge(i, j, x + y - v);\n          \
    \      }\n                pmq.apply(cx, { x + y, i });\n            }\n      \
    \  };\n\n        KruscalMinimumSpanningTree<WeightType> mst(n);\n        for (int\
    \ x_rev = 0; x_rev < 2; ++x_rev) {\n            for (int y_rev = 0; y_rev < 2;\
    \ ++y_rev) {\n                for (int xy_rev = 0; xy_rev < 2; ++xy_rev) {\n \
    \                   make_edges(mst);\n                    for (auto& [x, y] :\
    \ points) std::swap(x, y);\n                }\n                for (auto& [x,\
    \ _] : points) x = -x;\n            }\n            for (auto& [_, y] : points)\
    \ y = -y;\n        }\n        assert(mst.build());\n        return mst;\n    }\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MANHATTAN_MST\n#define SUISEN_MANHATTAN_MST\n\n#include <limits>\n\
    #include <numeric>\n#include <tuple>\n\n\n#include \"library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp\"\
    \n#include \"library/graph/kruscal.hpp\"\n\nnamespace suisen {\n    namespace\
    \ internal::manhattan_mst {\n        template <typename T>\n        std::pair<T,\
    \ int> op(std::pair<T, int> x, std::pair<T, int> y) { return std::max(x, y); };\n\
    \        template <typename T>\n        std::pair<T, int> e() { return { std::numeric_limits<T>::min(),\
    \ -1 }; };\n        template <typename T>\n        using PrefixMaxQuery = FenwickTreePrefix<std::pair<T,\
    \ int>, op<T>, e<T>>;\n    } // namespace internal::manhattan_mst\n\n    template\
    \ <typename WeightType, typename T>\n    KruscalMinimumSpanningTree<WeightType>\
    \ manhattan_mst(std::vector<std::pair<T, T>> points) {\n        using namespace\
    \ internal::manhattan_mst;\n\n        const int n = points.size();\n        std::vector<int>\
    \ p(n);\n        std::iota(p.begin(), p.end(), 0);\n\n        auto make_edges\
    \ = [&](KruscalMinimumSpanningTree<WeightType> &mst) {\n            std::sort(\n\
    \                p.begin(), p.end(),\n                [&points](int i, int j)\
    \ {\n                    const auto &[xi, yi] = points[i];\n                 \
    \   const auto &[xj, yj] = points[j];\n                    return yi - xi == yj\
    \ - xj ? xi < xj : yi - xi < yj - xj;\n                }\n            );\n\n \
    \           std::vector<T> comp_x(n);\n            for (int i = 0; i < n; ++i)\
    \ comp_x[i] = points[i].first;\n            std::sort(comp_x.begin(), comp_x.end());\n\
    \            comp_x.erase(std::unique(comp_x.begin(), comp_x.end()), comp_x.end());\n\
    \            const int m = comp_x.size();\n\n            auto compress = [&](const\
    \ T& x) { return std::lower_bound(comp_x.begin(), comp_x.end(), x) - comp_x.begin();\
    \ };\n\n            PrefixMaxQuery<T> pmq(m);\n\n            for (int i : p) {\n\
    \                const auto& [x, y] = points[i];\n                const int cx\
    \ = compress(x);\n                if (const auto p = pmq.prefix_query(cx + 1);\
    \ p != e<T>()) {\n                    const auto& [v, j] = p;\n              \
    \      mst.add_edge(i, j, x + y - v);\n                }\n                pmq.apply(cx,\
    \ { x + y, i });\n            }\n        };\n\n        KruscalMinimumSpanningTree<WeightType>\
    \ mst(n);\n        for (int x_rev = 0; x_rev < 2; ++x_rev) {\n            for\
    \ (int y_rev = 0; y_rev < 2; ++y_rev) {\n                for (int xy_rev = 0;\
    \ xy_rev < 2; ++xy_rev) {\n                    make_edges(mst);\n            \
    \        for (auto& [x, y] : points) std::swap(x, y);\n                }\n   \
    \             for (auto& [x, _] : points) x = -x;\n            }\n           \
    \ for (auto& [_, y] : points) y = -y;\n        }\n        assert(mst.build());\n\
    \        return mst;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_MANHATTAN_MST\n"
  dependsOn:
  - library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
  - library/graph/kruscal.hpp
  isVerificationFile: false
  path: library/graph/manhattan_mst.hpp
  requiredBy: []
  timestamp: '2022-06-14 00:04:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/manhattan_mst/manhattanmst.test.cpp
documentation_of: library/graph/manhattan_mst.hpp
layout: document
title: Manhattan Mst
---
## Manhattan Mst

$N$ 個の点 $(x_i,y_i)$ が与えられた場合に，点の間の距離をマンハッタン距離 $|x _ i - x _ j| + |y _ i - y _ j|$ としたの重み付き完全無向グラフの最小全域木を $O(N\log N)$ 時間で計算する．
