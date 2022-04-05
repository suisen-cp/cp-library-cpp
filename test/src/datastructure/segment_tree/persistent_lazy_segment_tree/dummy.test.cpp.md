---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
    title: Persistent Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <limits>\n\n#line 1 \"library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n\n#line 1 \"library/util/object_pool.hpp\"\n\n\n\n\
    #include <deque>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T, bool auto_extend = false>\n    struct ObjectPool {\n        using value_type\
    \ = T;\n        using value_pointer_type = T*;\n\n        template <typename U>\n\
    \        using container_type = std::conditional_t<auto_extend, std::deque<U>,\
    \ std::vector<U>>;\n\n        container_type<value_type> pool;\n        container_type<value_pointer_type>\
    \ stock;\n        decltype(stock.begin()) it;\n\n        ObjectPool() : ObjectPool(0)\
    \ {}\n        ObjectPool(int siz) : pool(siz), stock(siz) {\n            clear();\n\
    \        }\n\n        int capacity() const { return pool.size(); }\n        int\
    \ size() const { return it - stock.begin(); }\n\n        value_pointer_type alloc()\
    \ {\n            if constexpr (auto_extend) ensure();\n            return *it++;\n\
    \        }\n\n        void free(value_pointer_type t) {\n            *--it = t;\n\
    \        }\n\n        void clear() {\n            int siz = pool.size();\n   \
    \         it = stock.begin();\n            for (int i = 0; i < siz; i++) stock[i]\
    \ = &pool[i];\n        }\n\n        void ensure() {\n            if (it != stock.end())\
    \ return;\n            int siz = stock.size();\n            for (int i = siz;\
    \ i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#line 7 \"library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    struct PersistentLazySegmentTree\
    \ {\n        struct Node;\n\n        using value_type = T;\n        using operator_type\
    \ = F;\n\n        using node_type = Node;\n        using node_pointer_type = node_type*;\n\
    \n        struct Node {\n            static inline ObjectPool<node_type> _pool;\n\
    \n            node_pointer_type _ch[2]{ nullptr, nullptr };\n            value_type\
    \ _dat;\n            operator_type _laz;\n\n            Node() : _dat(e()), _laz(id())\
    \ {}\n\n            static node_pointer_type clone(node_pointer_type node) {\n\
    \                return &(*_pool.alloc() = *node);\n            }\n\n        \
    \    static void update(node_pointer_type node) {\n                node->_dat\
    \ = op(node->_ch[0]->_dat, node->_ch[1]->_dat);\n            }\n            template\
    \ <bool do_clone = true>\n            static auto push(node_pointer_type node)\
    \ {\n                node_pointer_type res = node;\n                if constexpr\
    \ (do_clone) res = clone(res);\n                res->_ch[0] = apply_all(res->_ch[0],\
    \ res->_laz);\n                res->_ch[1] = apply_all(res->_ch[1], res->_laz);\n\
    \                res->_laz = id();\n                if constexpr (do_clone) {\n\
    \                    return res;\n                } else {\n                 \
    \   return;\n                }\n            }\n\n            static bool is_leaf(node_pointer_type\
    \ node) {\n                return not node->_ch[0];\n            }\n\n       \
    \     static node_pointer_type build(const std::vector<value_type>& dat) {\n \
    \               auto rec = [&](auto rec, int l, int r) -> node_pointer_type {\n\
    \                    node_pointer_type res = _pool.alloc();\n                \
    \    if (r - l == 1) {\n                        res->_dat = dat[l];\n        \
    \                res->_laz = id();\n                    } else {\n           \
    \             int m = (l + r) >> 1;\n                        res->_ch[0] = rec(rec,\
    \ l, m), res->_ch[1] = rec(rec, m, r);\n                        update(res);\n\
    \                        res->_laz = id();\n                    }\n          \
    \          return res;\n                };\n                return rec(rec, 0,\
    \ dat.size());\n            }\n\n            static value_type prod_all(node_pointer_type\
    \ node) {\n                return node ? node->_dat : e();\n            }\n  \
    \          static value_type prod(node_pointer_type node, int tl, int tr, int\
    \ ql, int qr, const operator_type &f = id()) {\n                if (tr <= ql or\
    \ qr <= tl) return e();\n                if (ql <= tl and tr <= qr) return mapping(f,\
    \ node->_dat);\n                int tm = (tl + tr) >> 1;\n                operator_type\
    \ g = composition(f, node->_laz);\n                return op(prod(node->_ch[0],\
    \ tl, tm, ql, qr, g), prod(node->_ch[1], tm, tr, ql, qr, g));\n            }\n\
    \n            static node_pointer_type apply_all(node_pointer_type node, const\
    \ operator_type &f) {\n                if (not node) return nullptr;\n       \
    \         node_pointer_type res = clone(node);\n                res->_dat = mapping(f,\
    \ res->_dat);\n                res->_laz = composition(f, res->_laz);\n      \
    \          return res;\n            }\n            static node_pointer_type apply(node_pointer_type\
    \ node, int tl, int tr, int ql, int qr, const operator_type &f) {\n          \
    \      if (tr <= ql or qr <= tl) return node;\n                if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f);\n                node_pointer_type res\
    \ = push(node);\n                int tm = (tl + tr) >> 1;\n                res->_ch[0]\
    \ = apply(res->_ch[0], tl, tm, ql, qr, f);\n                res->_ch[1] = apply(res->_ch[1],\
    \ tm, tr, ql, qr, f);\n                update(res);\n                return res;\n\
    \            }\n\n            template <typename Func>\n            static auto\
    \ update_leaf(node_pointer_type node, int siz, int i, Func &&f) {\n          \
    \      static std::vector<node_pointer_type> path;\n\n                node_pointer_type\
    \ res = clone(node);\n                node_pointer_type cur = res;\n\n       \
    \         for (int l = 0, r = siz; r - l > 1;) {\n                    path.push_back(cur);\n\
    \                    push</*do_clone = */false>(cur);\n                    int\
    \ m = (l + r) >> 1;\n                    if (i < m) {\n                      \
    \  cur = cur->_ch[0];\n                        r = m;\n                    } else\
    \ {\n                        cur = cur->_ch[1];\n                        l = m;\n\
    \                    }\n                }\n                cur->_dat = f(cur->_dat);\n\
    \                while (path.size()) update(path.back()), path.pop_back();\n \
    \               return res;\n            }\n\n            static value_type get(node_pointer_type\
    \ node, int siz, int i) {\n                operator_type f = id();\n         \
    \       node_pointer_type cur = node;\n                for (int l = 0, r = siz;\
    \ r - l > 1;) {\n                    f = composition(f, cur->_laz);\n        \
    \            int m = (l + r) >> 1;\n                    if (i < m) {\n       \
    \                 cur = cur->_ch[0];\n                        r = m;\n       \
    \             } else {\n                        cur = cur->_ch[1];\n         \
    \               l = m;\n                    }\n                }\n           \
    \     return mapping(f, cur->_dat);\n            }\n            template <typename\
    \ Func>\n            static node_pointer_type apply(node_pointer_type node, int\
    \ siz, int i, Func&& f) {\n                return update_leaf(node, siz, i, [&](const\
    \ value_type &v) { return f(v); });\n            }\n            static node_pointer_type\
    \ set(node_pointer_type node, int siz, int i, const value_type& dat) {\n     \
    \           return apply(node, siz, i, [&](const value_type&) { return dat; });\n\
    \            }\n\n            template <typename Pred>\n            static int\
    \ max_right(node_pointer_type node, int siz, int l, Pred&& pred) {\n         \
    \       assert(pred(e()));\n                auto rec = [&](auto rec, node_pointer_type\
    \ cur, int tl, int tr, value_type& sum, const operator_type &f) -> int {\n   \
    \                 if (tr <= l) return tr;\n                    if (l <= tl) {\n\
    \                        value_type nxt_sum = op(sum, mapping(f, cur->_dat));\n\
    \                        if (pred(nxt_sum)) {\n                            sum\
    \ = std::move(nxt_sum);\n                            return tr;\n            \
    \            }\n                        if (tr - tl == 1) return tl;\n       \
    \             }\n                    int tm = (tl + tr) >> 1;\n              \
    \      operator_type g = composition(f, cur->_laz);\n                    int res_l\
    \ = rec(rec, cur->_ch[0], tl, tm, sum, g);\n                    return res_l !=\
    \ tm ? res_l : rec(rec, cur->_ch[1], tm, tr, sum, g);\n                };\n  \
    \              value_type sum = e();\n                return rec(rec, node, 0,\
    \ siz, sum, id());\n            }\n            template <typename Pred>\n    \
    \        static int min_left(node_pointer_type node, int siz, int r, Pred&& pred)\
    \ {\n                assert(pred(e()));\n                auto rec = [&](auto rec,\
    \ node_pointer_type cur, int tl, int tr, value_type& sum, const operator_type\
    \ &f) -> int {\n                    if (r <= tl) return tl;\n                \
    \    if (tr <= r) {\n                        value_type nxt_sum = op(mapping(f,\
    \ cur->_dat), sum);\n                        if (pred(nxt_sum)) {\n          \
    \                  sum = std::move(nxt_sum);\n                            return\
    \ tl;\n                        }\n                        if (tr - tl == 1) return\
    \ tr;\n                    }\n                    int tm = (tl + tr) >> 1;\n \
    \                   operator_type g = composition(f, cur->_laz);\n           \
    \         int res_r = rec(rec, cur->_ch[1], tm, tr, sum, g);\n               \
    \     return res_r != tm ? res_r : rec(rec, cur->_ch[0], tl, tm, sum, g);\n  \
    \              };\n                value_type sum = e();\n                return\
    \ rec(rec, node, 0, siz, sum, id());\n            }\n\n            template <typename\
    \ OutputIterator>\n            static void dump(node_pointer_type node, OutputIterator\
    \ it) {\n                if (not node) return;\n                auto rec = [&](auto\
    \ rec, node_pointer_type cur, const operator_type &f) -> void {\n            \
    \        if (is_leaf(cur)) {\n                        *it++ = mapping(f, cur->_dat);\n\
    \                    } else {\n                        *it++ = mapping(f, cur->_dat);\n\
    \                        rec(rec, cur->_ch[0], composition(cur->_laz, f)), rec(rec,\
    \ cur->_ch[1], composition(cur->_laz, f));\n                    }\n          \
    \      };\n                rec(rec, node, id());\n            }\n            static\
    \ std::vector<value_type> dump(node_pointer_type node) {\n                std::vector<value_type>\
    \ res;\n                dump(node, std::back_inserter(res));\n               \
    \ return res;\n            }\n        };\n\n        PersistentLazySegmentTree()\
    \ : _n(0), _root(nullptr) {}\n        explicit PersistentLazySegmentTree(int n)\
    \ : PersistentLazySegmentTree(std::vector<value_type>(n, e())) {}\n        PersistentLazySegmentTree(const\
    \ std::vector<value_type>& dat) : _n(dat.size()), _root(node_type::build(dat))\
    \ {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        value_type prod_all()\
    \ {\n            return node_type::prod_all(_root);\n        }\n        value_type\
    \ prod(int l, int r) {\n            assert(0 <= l and l <= r and r <= _n);\n \
    \           return node_type::prod(_root, 0, _n, l, r);\n        }\n        value_type\
    \ operator()(int l, int r) {\n            return prod(l, r);\n        }\n\n  \
    \      PersistentLazySegmentTree apply_all(const operator_type &f) {\n       \
    \     return PersistentLazySegmentTree(_n, node_type::apply_all(_root, f));\n\
    \        }\n        PersistentLazySegmentTree apply(int l, int r, const operator_type\
    \ &f) {\n            return PersistentLazySegmentTree(_n, node_type::apply(_root,\
    \ 0, _n, l, r, f));\n        }\n\n        value_type get(int i) {\n          \
    \  assert(0 <= i and i < _n);\n            return node_type::get(_root, _n, i);\n\
    \        }\n        value_type operator[](int i) {\n            return get(i);\n\
    \        }\n\n        template <typename Func>\n        PersistentLazySegmentTree\
    \ apply(int i, Func&& f) {\n            assert(0 <= i and i < _n);\n         \
    \   return PersistentLazySegmentTree(_n, node_type::apply(_root, _n, i, std::forward<F>(f)));\n\
    \        }\n        PersistentLazySegmentTree set(int i, const value_type& v)\
    \ {\n            assert(0 <= i and i < _n);\n            return PersistentLazySegmentTree(_n,\
    \ node_type::set(_root, _n, i, v));\n        }\n\n        template <typename Pred>\n\
    \        int max_right(int l, Pred&& pred) {\n            assert(0 <= l and l\
    \ <= _n);\n            return node_type::max_right(_root, _n, l, std::forward<Pred>(pred));\n\
    \        }\n        template <bool(*pred)(value_type)>\n        static int max_right(int\
    \ l) {\n            return max_right(l, pred);\n        }\n        template <typename\
    \ Pred>\n        int min_left(int r, Pred&& pred) {\n            assert(0 <= r\
    \ and r <= _n);\n            return node_type::min_left(_root, _n, r, std::forward<Pred>(pred));\n\
    \        }\n        template <bool(*pred)(value_type)>\n        static int min_left(int\
    \ r) {\n            return min_left(r, pred);\n        }\n\n        template <typename\
    \ OutputIterator>\n        void dump(OutputIterator it) {\n            node_type::dump(_root,\
    \ it);\n        }\n        std::vector<value_type> dump() {\n            return\
    \ node_type::dump(_root);\n        }\n\n    private:\n        int _n;\n      \
    \  node_pointer_type _root;\n        PersistentLazySegmentTree(int n, node_pointer_type\
    \ root) : _n(n), _root(root) {}\n    };\n}\n\n\n#line 7 \"test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp\"\
    \n\ntemplate <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T)>\n\
    struct NaiveSolutionForLazySegmentTree {\n    NaiveSolutionForLazySegmentTree()\
    \ = default;\n    NaiveSolutionForLazySegmentTree(const std::vector<T> &dat) :\
    \ _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const {\n        assert(0 <=\
    \ i and i < _n);\n        return _dat[i];\n    }\n    void set(int i, const T&\
    \ val) {\n        assert(0 <= i and i < _n);\n        _dat[i] = val;\n    }\n\n\
    \    T prod_all() const {\n        return prod(0, _n);\n    }\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l and l <= r and r <= _n);\n        T\
    \ res = e();\n        for (int i = l; i < r; ++i) res = op(res, _dat[i]);\n  \
    \      return res;\n    }\n\n    void apply_all(const F &f) {\n        apply(0,\
    \ _n, f);\n    }\n    void apply(int l, int r, const F &f) {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        for (int i = l; i < r; ++i) _dat[i] =\
    \ mapping(f, _dat[i]);\n    }\n\n    template <typename Pred>\n    int max_right(int\
    \ l, Pred &&pred) const {\n        assert(0 <= l and l <= _n);\n        T sum\
    \ = e();\n        for (int r = l; r < _n; ++r) {\n            T next_sum = op(sum,\
    \ _dat[r]);\n            if (not pred(next_sum)) return r;\n            sum =\
    \ std::move(next_sum);\n        }\n        return _n;\n    }\n\n    template <typename\
    \ Pred>\n    int min_left(int r, Pred &&pred) const {\n        assert(0 <= r and\
    \ r <= _n);\n        T sum = e();\n        for (int l = r; l > 0; --l) {\n   \
    \         T next_sum = op(_dat[l - 1], sum);\n            if (not pred(next_sum))\
    \ return l;\n            sum = std::move(next_sum);\n        }\n        return\
    \ 0;\n    }\nprivate:\n    int _n;\n    std::vector<T> _dat;\n};\n\n/**\n * Range\
    \ Update Range Sum\n */\n\nstruct S {\n    long long sum;\n    int len;\n    S()\
    \ = default;\n    S(long long sum, int len) : sum(sum), len(len) {}\n\n    bool\
    \ operator==(const S &other) const {\n        return sum == other.sum and len\
    \ == other.len;\n    }\n    bool operator!=(const S &other) const {\n        return\
    \ not operator==(other);\n    }\n};\n\nstruct F {\n    static constexpr int identity\
    \ = std::numeric_limits<int>::max();\n\n    int val;\n    F() : val(identity)\
    \ {}\n    F(int val) : val(val) {}\n};\n\nS op(S x, S y) {\n    return S{ x.sum\
    \ + y.sum, x.len + y.len };\n}\nS e() {\n    return S{ 0LL, 0 };\n}\nS mapping(F\
    \ f, S x) {\n    return f.val == F::identity ? x : S{ (long long) f.val * x.len,\
    \ x.len };\n}\nF composition(F f, F g) {\n    return f.val == F::identity ? g\
    \ : f;\n}\nF id() {\n    return F{};\n}\n\nusing Tree = suisen::PersistentLazySegmentTree<S,\
    \ op, e, F, mapping, composition, id>;\nusing Naive = NaiveSolutionForLazySegmentTree<S,\
    \ op, e, F, mapping>;\n\n#include <random>\n#include <algorithm>\n\nconstexpr\
    \ int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_prod = 2;\nconstexpr\
    \ int Q_prod_all = 3;\nconstexpr int Q_apply = 4;\nconstexpr int Q_apply_all =\
    \ 5;\nconstexpr int Q_max_right = 6;\nconstexpr int Q_min_left = 7;\nconstexpr\
    \ int QueryTypeNum = 8;\n\nvoid test() {\n    constexpr int N = 3000, Q = 3000,\
    \ MAX_VAL = 1000000000;\n\n    std::mt19937 rng{std::random_device{}()};\n\n \
    \   Tree::init_pool(1000000);\n\n    std::vector<S> init(N);\n    for (int i =\
    \ 0; i < N; ++i) init[i] = { (long long) rng() % MAX_VAL, 1 };\n    \n    std::vector<Tree>\
    \ ts;\n    std::vector<Naive> naive_sols;\n\n    ts.push_back(Tree{init});\n \
    \   naive_sols.push_back(Naive{init});\n\n    for (int i = 0; i < Q; ++i) {\n\
    \        const int query_type = rng() % QueryTypeNum;\n        const int sequence_id\
    \ = rng() % ts.size();\n        auto &act = ts[sequence_id];\n        auto &exp\
    \ = naive_sols[sequence_id];\n        if (query_type == Q_get) {\n           \
    \ const int i = rng() % N;\n            assert(act.get(i) == exp.get(i));\n  \
    \      } else if (query_type == Q_set) {\n            const int i = rng() % N;\n\
    \            const S v = { (long long) rng() % MAX_VAL, 1 };\n            ts.push_back(act.set(i,\
    \ v));\n            naive_sols.push_back(exp);\n            naive_sols.back().set(i,\
    \ v);\n        } else if (query_type == Q_prod) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ assert(act.prod(l, r) == exp.prod(l, r));\n        } else if (query_type ==\
    \ Q_prod_all) {\n            assert(act.prod_all() == exp.prod_all());\n     \
    \   } else if (query_type == Q_apply) {\n            const int l = rng() % (N\
    \ + 1);\n            const int r = l + rng() % (N - l + 1);\n            const\
    \ int f = rng() % MAX_VAL;\n            ts.push_back(act.apply(l, r, f));\n  \
    \          naive_sols.push_back(exp);\n            naive_sols.back().apply(l,\
    \ r, f);\n        } else if (query_type == Q_apply_all) {\n            const int\
    \ f = rng() % MAX_VAL;\n            ts.push_back(act.apply_all(f));\n        \
    \    naive_sols.push_back(exp);\n            naive_sols.back().apply_all(f);\n\
    \        } else if (query_type == Q_max_right) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ long long sum = std::max(0LL, exp.prod(l, r).sum + int(rng() % MAX_VAL) - MAX_VAL\
    \ / 2);\n            auto pred = [&](const S &x) { return x.sum <= sum; };\n \
    \           assert(act.max_right(l, pred) == exp.max_right(l, pred));\n      \
    \  } else if (query_type == Q_min_left) {\n            const int l = rng() % (N\
    \ + 1);\n            const int r = l + rng() % (N - l + 1);\n            long\
    \ long sum = std::max(0LL, exp.prod(l, r).sum + int(rng() % MAX_VAL) - MAX_VAL\
    \ / 2);\n            auto pred = [&](const S &x) { return x.sum <= sum; };\n \
    \           assert(act.min_left(r, pred) == exp.min_left(r, pred));\n        }\
    \ else {\n            assert(false);\n        }\n    }\n}\n\nint main() {\n  \
    \  test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <limits>\n\n#include \"library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp\"\
    \n\ntemplate <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T)>\n\
    struct NaiveSolutionForLazySegmentTree {\n    NaiveSolutionForLazySegmentTree()\
    \ = default;\n    NaiveSolutionForLazySegmentTree(const std::vector<T> &dat) :\
    \ _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const {\n        assert(0 <=\
    \ i and i < _n);\n        return _dat[i];\n    }\n    void set(int i, const T&\
    \ val) {\n        assert(0 <= i and i < _n);\n        _dat[i] = val;\n    }\n\n\
    \    T prod_all() const {\n        return prod(0, _n);\n    }\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l and l <= r and r <= _n);\n        T\
    \ res = e();\n        for (int i = l; i < r; ++i) res = op(res, _dat[i]);\n  \
    \      return res;\n    }\n\n    void apply_all(const F &f) {\n        apply(0,\
    \ _n, f);\n    }\n    void apply(int l, int r, const F &f) {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        for (int i = l; i < r; ++i) _dat[i] =\
    \ mapping(f, _dat[i]);\n    }\n\n    template <typename Pred>\n    int max_right(int\
    \ l, Pred &&pred) const {\n        assert(0 <= l and l <= _n);\n        T sum\
    \ = e();\n        for (int r = l; r < _n; ++r) {\n            T next_sum = op(sum,\
    \ _dat[r]);\n            if (not pred(next_sum)) return r;\n            sum =\
    \ std::move(next_sum);\n        }\n        return _n;\n    }\n\n    template <typename\
    \ Pred>\n    int min_left(int r, Pred &&pred) const {\n        assert(0 <= r and\
    \ r <= _n);\n        T sum = e();\n        for (int l = r; l > 0; --l) {\n   \
    \         T next_sum = op(_dat[l - 1], sum);\n            if (not pred(next_sum))\
    \ return l;\n            sum = std::move(next_sum);\n        }\n        return\
    \ 0;\n    }\nprivate:\n    int _n;\n    std::vector<T> _dat;\n};\n\n/**\n * Range\
    \ Update Range Sum\n */\n\nstruct S {\n    long long sum;\n    int len;\n    S()\
    \ = default;\n    S(long long sum, int len) : sum(sum), len(len) {}\n\n    bool\
    \ operator==(const S &other) const {\n        return sum == other.sum and len\
    \ == other.len;\n    }\n    bool operator!=(const S &other) const {\n        return\
    \ not operator==(other);\n    }\n};\n\nstruct F {\n    static constexpr int identity\
    \ = std::numeric_limits<int>::max();\n\n    int val;\n    F() : val(identity)\
    \ {}\n    F(int val) : val(val) {}\n};\n\nS op(S x, S y) {\n    return S{ x.sum\
    \ + y.sum, x.len + y.len };\n}\nS e() {\n    return S{ 0LL, 0 };\n}\nS mapping(F\
    \ f, S x) {\n    return f.val == F::identity ? x : S{ (long long) f.val * x.len,\
    \ x.len };\n}\nF composition(F f, F g) {\n    return f.val == F::identity ? g\
    \ : f;\n}\nF id() {\n    return F{};\n}\n\nusing Tree = suisen::PersistentLazySegmentTree<S,\
    \ op, e, F, mapping, composition, id>;\nusing Naive = NaiveSolutionForLazySegmentTree<S,\
    \ op, e, F, mapping>;\n\n#include <random>\n#include <algorithm>\n\nconstexpr\
    \ int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_prod = 2;\nconstexpr\
    \ int Q_prod_all = 3;\nconstexpr int Q_apply = 4;\nconstexpr int Q_apply_all =\
    \ 5;\nconstexpr int Q_max_right = 6;\nconstexpr int Q_min_left = 7;\nconstexpr\
    \ int QueryTypeNum = 8;\n\nvoid test() {\n    constexpr int N = 3000, Q = 3000,\
    \ MAX_VAL = 1000000000;\n\n    std::mt19937 rng{std::random_device{}()};\n\n \
    \   Tree::init_pool(1000000);\n\n    std::vector<S> init(N);\n    for (int i =\
    \ 0; i < N; ++i) init[i] = { (long long) rng() % MAX_VAL, 1 };\n    \n    std::vector<Tree>\
    \ ts;\n    std::vector<Naive> naive_sols;\n\n    ts.push_back(Tree{init});\n \
    \   naive_sols.push_back(Naive{init});\n\n    for (int i = 0; i < Q; ++i) {\n\
    \        const int query_type = rng() % QueryTypeNum;\n        const int sequence_id\
    \ = rng() % ts.size();\n        auto &act = ts[sequence_id];\n        auto &exp\
    \ = naive_sols[sequence_id];\n        if (query_type == Q_get) {\n           \
    \ const int i = rng() % N;\n            assert(act.get(i) == exp.get(i));\n  \
    \      } else if (query_type == Q_set) {\n            const int i = rng() % N;\n\
    \            const S v = { (long long) rng() % MAX_VAL, 1 };\n            ts.push_back(act.set(i,\
    \ v));\n            naive_sols.push_back(exp);\n            naive_sols.back().set(i,\
    \ v);\n        } else if (query_type == Q_prod) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ assert(act.prod(l, r) == exp.prod(l, r));\n        } else if (query_type ==\
    \ Q_prod_all) {\n            assert(act.prod_all() == exp.prod_all());\n     \
    \   } else if (query_type == Q_apply) {\n            const int l = rng() % (N\
    \ + 1);\n            const int r = l + rng() % (N - l + 1);\n            const\
    \ int f = rng() % MAX_VAL;\n            ts.push_back(act.apply(l, r, f));\n  \
    \          naive_sols.push_back(exp);\n            naive_sols.back().apply(l,\
    \ r, f);\n        } else if (query_type == Q_apply_all) {\n            const int\
    \ f = rng() % MAX_VAL;\n            ts.push_back(act.apply_all(f));\n        \
    \    naive_sols.push_back(exp);\n            naive_sols.back().apply_all(f);\n\
    \        } else if (query_type == Q_max_right) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ long long sum = std::max(0LL, exp.prod(l, r).sum + int(rng() % MAX_VAL) - MAX_VAL\
    \ / 2);\n            auto pred = [&](const S &x) { return x.sum <= sum; };\n \
    \           assert(act.max_right(l, pred) == exp.max_right(l, pred));\n      \
    \  } else if (query_type == Q_min_left) {\n            const int l = rng() % (N\
    \ + 1);\n            const int r = l + rng() % (N - l + 1);\n            long\
    \ long sum = std::max(0LL, exp.prod(l, r).sum + int(rng() % MAX_VAL) - MAX_VAL\
    \ / 2);\n            auto pred = [&](const S &x) { return x.sum <= sum; };\n \
    \           assert(act.min_left(r, pred) == exp.min_left(r, pred));\n        }\
    \ else {\n            assert(false);\n        }\n    }\n}\n\nint main() {\n  \
    \  test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
  - library/util/object_pool.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-04-05 23:32:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
- /verify/test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp.html
title: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
---
