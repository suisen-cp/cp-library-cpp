---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/HeavyLightDecomposition.hpp
    title: library/tree/HeavyLightDecomposition.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450
  bundledCode: "#line 1 \"test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450\"\
    \n\n#include <iostream>\n\n#include <algorithm>\n\n#ifdef _MSC_VER\n#include <intrin.h>\n\
    #endif\n\nnamespace atcoder {\n\nnamespace internal {\n\n// @param n `0 <= n`\n\
    // @return minimum non-negative `x` s.t. `n <= 2**x`\nint ceil_pow2(int n) {\n\
    \    int x = 0;\n    while ((1U << x) < (unsigned int)(n)) x++;\n    return x;\n\
    }\n\n// @param n `1 <= n`\n// @return minimum non-negative `x` s.t. `(n & (1 <<\
    \ x)) != 0`\nint bsf(unsigned int n) {\n#ifdef _MSC_VER\n    unsigned long index;\n\
    \    _BitScanForward(&index, n);\n    return index;\n#else\n    return __builtin_ctz(n);\n\
    #endif\n}\n\n}  // namespace internal\n\n}  // namespace atcoder\n\n#include <cassert>\n\
    #line 41 \"test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp\"\
    \n#include <vector>\nnamespace atcoder {\n\ntemplate <class S,\n          S (*op)(S,\
    \ S),\n          S (*e)(),\n          class F,\n          S (*mapping)(F, S),\n\
    \          F (*composition)(F, F),\n          F (*id)()>\nstruct lazy_segtree\
    \ {\n  public:\n    lazy_segtree() : lazy_segtree(0) {}\n    lazy_segtree(int\
    \ n) : lazy_segtree(std::vector<S>(n, e())) {}\n    lazy_segtree(const std::vector<S>&\
    \ v) : _n(int(v.size())) {\n        log = internal::ceil_pow2(_n);\n        size\
    \ = 1 << log;\n        d = std::vector<S>(2 * size, e());\n        lz = std::vector<F>(size,\
    \ id());\n        for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for\
    \ (int i = size - 1; i >= 1; i--) {\n            update(i);\n        }\n    }\n\
    \n    void set(int p, S x) {\n        assert(0 <= p && p < _n);\n        p +=\
    \ size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n        d[p] =\
    \ x;\n        for (int i = 1; i <= log; i++) update(p >> i);\n    }\n\n    S get(int\
    \ p) {\n        assert(0 <= p && p < _n);\n        p += size;\n        for (int\
    \ i = log; i >= 1; i--) push(p >> i);\n        return d[p];\n    }\n\n    S prod(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l ==\
    \ r) return e();\n\n        l += size;\n        r += size;\n\n        for (int\
    \ i = log; i >= 1; i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n\
    \            if (((r >> i) << i) != r) push(r >> i);\n        }\n\n        S sml\
    \ = e(), smr = e();\n        while (l < r) {\n            if (l & 1) sml = op(sml,\
    \ d[l++]);\n            if (r & 1) smr = op(d[--r], smr);\n            l >>= 1;\n\
    \            r >>= 1;\n        }\n\n        return op(sml, smr);\n    }\n\n  \
    \  S all_prod() { return d[1]; }\n\n    void apply(int p, F f) {\n        assert(0\
    \ <= p && p < _n);\n        p += size;\n        for (int i = log; i >= 1; i--)\
    \ push(p >> i);\n        d[p] = mapping(f, d[p]);\n        for (int i = 1; i <=\
    \ log; i++) update(p >> i);\n    }\n    void apply(int l, int r, F f) {\n    \
    \    assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return;\n\n   \
    \     l += size;\n        r += size;\n\n        for (int i = log; i >= 1; i--)\
    \ {\n            if (((l >> i) << i) != l) push(l >> i);\n            if (((r\
    \ >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        {\n            int\
    \ l2 = l, r2 = r;\n            while (l < r) {\n                if (l & 1) all_apply(l++,\
    \ f);\n                if (r & 1) all_apply(--r, f);\n                l >>= 1;\n\
    \                r >>= 1;\n            }\n            l = l2;\n            r =\
    \ r2;\n        }\n\n        for (int i = 1; i <= log; i++) {\n            if (((l\
    \ >> i) << i) != l) update(l >> i);\n            if (((r >> i) << i) != r) update((r\
    \ - 1) >> i);\n        }\n    }\n\n    template <bool (*g)(S)> int max_right(int\
    \ l) {\n        return max_right(l, [](S x) { return g(x); });\n    }\n    template\
    \ <class G> int max_right(int l, G g) {\n        assert(0 <= l && l <= _n);\n\
    \        assert(g(e()));\n        if (l == _n) return _n;\n        l += size;\n\
    \        for (int i = log; i >= 1; i--) push(l >> i);\n        S sm = e();\n \
    \       do {\n            while (l % 2 == 0) l >>= 1;\n            if (!g(op(sm,\
    \ d[l]))) {\n                while (l < size) {\n                    push(l);\n\
    \                    l = (2 * l);\n                    if (g(op(sm, d[l]))) {\n\
    \                        sm = op(sm, d[l]);\n                        l++;\n  \
    \                  }\n                }\n                return l - size;\n  \
    \          }\n            sm = op(sm, d[l]);\n            l++;\n        } while\
    \ ((l & -l) != l);\n        return _n;\n    }\n\n    template <bool (*g)(S)> int\
    \ min_left(int r) {\n        return min_left(r, [](S x) { return g(x); });\n \
    \   }\n    template <class G> int min_left(int r, G g) {\n        assert(0 <=\
    \ r && r <= _n);\n        assert(g(e()));\n        if (r == 0) return 0;\n   \
    \     r += size;\n        for (int i = log; i >= 1; i--) push((r - 1) >> i);\n\
    \        S sm = e();\n        do {\n            r--;\n            while (r > 1\
    \ && (r % 2)) r >>= 1;\n            if (!g(op(d[r], sm))) {\n                while\
    \ (r < size) {\n                    push(r);\n                    r = (2 * r +\
    \ 1);\n                    if (g(op(d[r], sm))) {\n                        sm\
    \ = op(d[r], sm);\n                        r--;\n                    }\n     \
    \           }\n                return r + 1 - size;\n            }\n         \
    \   sm = op(d[r], sm);\n        } while ((r & -r) != r);\n        return 0;\n\
    \    }\n\n  private:\n    int _n, size, log;\n    std::vector<S> d;\n    std::vector<F>\
    \ lz;\n\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n    void\
    \ all_apply(int k, F f) {\n        d[k] = mapping(f, d[k]);\n        if (k < size)\
    \ lz[k] = composition(f, lz[k]);\n    }\n    void push(int k) {\n        all_apply(2\
    \ * k, lz[k]);\n        all_apply(2 * k + 1, lz[k]);\n        lz[k] = id();\n\
    \    }\n};\n\n}  // namespace atcoder\n\n#include <library/tree/HeavyLightDecomposition.hpp>\n\
    \nstruct S {\n    int len;\n    long long pref, max, suff, sum;\n    S(int len,\
    \ long long pref, long long max, long long suff, long long sum) : len(len), pref(pref),\
    \ max(max), suff(suff), sum(sum) {}\n};\n\nconstexpr long long INF = std::numeric_limits<int>::max();\n\
    \nS op1(const S s1, const S s2) {\n    int len = s1.len + s2.len;\n    long long\
    \ pref = std::max(s1.pref, s1.sum + s2.pref);\n    long long max  = std::max({s1.max,\
    \ s2.max, s1.suff + s2.pref});\n    long long suff = std::max(s1.suff + s2.sum,\
    \ s2.suff);\n    long long sum  = s1.sum + s2.sum;\n    return {len, pref, max,\
    \ suff, sum};\n}\nS op2(const S s1, const S s2) {\n    return op1(s2, s1);\n}\n\
    S e() { \n    return {0, -INF, -INF, -INF, 0};\n}\nS mapping(long long f, S x)\
    \ {\n    int len = x.len;\n    if (f == -INF or len == 0) return x;\n    long\
    \ long max = f >= 0 ? f * len : f;\n    return {len, max, max, max, f * len};\n\
    }\nlong long composition(long long f, long long g) {\n    return f == -INF ? g\
    \ : f;\n}\nlong long id() {\n    return -INF;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> w(n);\n    for (long long &e : w) {\n        std::cin >> e;\n    }\n \
    \   std::vector<std::vector<int>> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    suisen::HeavyLightDecomposition hld(g);\n\
    \    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);\n\
    \    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        hld.update_point(i, [&](int j) {\n\
    \            seg1.set(j, {1, w[i], w[i], w[i], w[i]});\n            seg2.set(j,\
    \ {1, w[i], w[i], w[i], w[i]});\n        });\n    }\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        std::cin >> t >> a >> b >> c;\n   \
    \     --a, --b;\n        if (t == 1) {\n            hld.update_path(a, b, [&](int\
    \ l, int r) {\n                seg1.apply(l, r, c);\n                seg2.apply(l,\
    \ r, c);\n            });\n        } else {\n            std::cout << hld.fold_path_noncommutative(\n\
    \                a, b, e(), op1,\n                [&](int l, int r) { return seg1.prod(l,\
    \ r); },\n                [&](int l, int r) { return seg2.prod(l, r); }\n    \
    \        ).max << '\\n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450\"\
    \n\n#include <iostream>\n\n#include <algorithm>\n\n#ifdef _MSC_VER\n#include <intrin.h>\n\
    #endif\n\nnamespace atcoder {\n\nnamespace internal {\n\n// @param n `0 <= n`\n\
    // @return minimum non-negative `x` s.t. `n <= 2**x`\nint ceil_pow2(int n) {\n\
    \    int x = 0;\n    while ((1U << x) < (unsigned int)(n)) x++;\n    return x;\n\
    }\n\n// @param n `1 <= n`\n// @return minimum non-negative `x` s.t. `(n & (1 <<\
    \ x)) != 0`\nint bsf(unsigned int n) {\n#ifdef _MSC_VER\n    unsigned long index;\n\
    \    _BitScanForward(&index, n);\n    return index;\n#else\n    return __builtin_ctz(n);\n\
    #endif\n}\n\n}  // namespace internal\n\n}  // namespace atcoder\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\nnamespace atcoder {\n\ntemplate <class\
    \ S,\n          S (*op)(S, S),\n          S (*e)(),\n          class F,\n    \
    \      S (*mapping)(F, S),\n          F (*composition)(F, F),\n          F (*id)()>\n\
    struct lazy_segtree {\n  public:\n    lazy_segtree() : lazy_segtree(0) {}\n  \
    \  lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}\n    lazy_segtree(const\
    \ std::vector<S>& v) : _n(int(v.size())) {\n        log = internal::ceil_pow2(_n);\n\
    \        size = 1 << log;\n        d = std::vector<S>(2 * size, e());\n      \
    \  lz = std::vector<F>(size, id());\n        for (int i = 0; i < _n; i++) d[size\
    \ + i] = v[i];\n        for (int i = size - 1; i >= 1; i--) {\n            update(i);\n\
    \        }\n    }\n\n    void set(int p, S x) {\n        assert(0 <= p && p <\
    \ _n);\n        p += size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n\
    \        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p >> i);\n \
    \   }\n\n    S get(int p) {\n        assert(0 <= p && p < _n);\n        p += size;\n\
    \        for (int i = log; i >= 1; i--) push(p >> i);\n        return d[p];\n\
    \    }\n\n    S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        if (l == r) return e();\n\n        l += size;\n        r += size;\n\
    \n        for (int i = log; i >= 1; i--) {\n            if (((l >> i) << i) !=\
    \ l) push(l >> i);\n            if (((r >> i) << i) != r) push(r >> i);\n    \
    \    }\n\n        S sml = e(), smr = e();\n        while (l < r) {\n         \
    \   if (l & 1) sml = op(sml, d[l++]);\n            if (r & 1) smr = op(d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n\n        return\
    \ op(sml, smr);\n    }\n\n    S all_prod() { return d[1]; }\n\n    void apply(int\
    \ p, F f) {\n        assert(0 <= p && p < _n);\n        p += size;\n        for\
    \ (int i = log; i >= 1; i--) push(p >> i);\n        d[p] = mapping(f, d[p]);\n\
    \        for (int i = 1; i <= log; i++) update(p >> i);\n    }\n    void apply(int\
    \ l, int r, F f) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l\
    \ == r) return;\n\n        l += size;\n        r += size;\n\n        for (int\
    \ i = log; i >= 1; i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n\
    \            if (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n    \
    \    {\n            int l2 = l, r2 = r;\n            while (l < r) {\n       \
    \         if (l & 1) all_apply(l++, f);\n                if (r & 1) all_apply(--r,\
    \ f);\n                l >>= 1;\n                r >>= 1;\n            }\n   \
    \         l = l2;\n            r = r2;\n        }\n\n        for (int i = 1; i\
    \ <= log; i++) {\n            if (((l >> i) << i) != l) update(l >> i);\n    \
    \        if (((r >> i) << i) != r) update((r - 1) >> i);\n        }\n    }\n\n\
    \    template <bool (*g)(S)> int max_right(int l) {\n        return max_right(l,\
    \ [](S x) { return g(x); });\n    }\n    template <class G> int max_right(int\
    \ l, G g) {\n        assert(0 <= l && l <= _n);\n        assert(g(e()));\n   \
    \     if (l == _n) return _n;\n        l += size;\n        for (int i = log; i\
    \ >= 1; i--) push(l >> i);\n        S sm = e();\n        do {\n            while\
    \ (l % 2 == 0) l >>= 1;\n            if (!g(op(sm, d[l]))) {\n               \
    \ while (l < size) {\n                    push(l);\n                    l = (2\
    \ * l);\n                    if (g(op(sm, d[l]))) {\n                        sm\
    \ = op(sm, d[l]);\n                        l++;\n                    }\n     \
    \           }\n                return l - size;\n            }\n            sm\
    \ = op(sm, d[l]);\n            l++;\n        } while ((l & -l) != l);\n      \
    \  return _n;\n    }\n\n    template <bool (*g)(S)> int min_left(int r) {\n  \
    \      return min_left(r, [](S x) { return g(x); });\n    }\n    template <class\
    \ G> int min_left(int r, G g) {\n        assert(0 <= r && r <= _n);\n        assert(g(e()));\n\
    \        if (r == 0) return 0;\n        r += size;\n        for (int i = log;\
    \ i >= 1; i--) push((r - 1) >> i);\n        S sm = e();\n        do {\n      \
    \      r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n            if (!g(op(d[r],\
    \ sm))) {\n                while (r < size) {\n                    push(r);\n\
    \                    r = (2 * r + 1);\n                    if (g(op(d[r], sm)))\
    \ {\n                        sm = op(d[r], sm);\n                        r--;\n\
    \                    }\n                }\n                return r + 1 - size;\n\
    \            }\n            sm = op(d[r], sm);\n        } while ((r & -r) != r);\n\
    \        return 0;\n    }\n\n  private:\n    int _n, size, log;\n    std::vector<S>\
    \ d;\n    std::vector<F> lz;\n\n    void update(int k) { d[k] = op(d[2 * k], d[2\
    \ * k + 1]); }\n    void all_apply(int k, F f) {\n        d[k] = mapping(f, d[k]);\n\
    \        if (k < size) lz[k] = composition(f, lz[k]);\n    }\n    void push(int\
    \ k) {\n        all_apply(2 * k, lz[k]);\n        all_apply(2 * k + 1, lz[k]);\n\
    \        lz[k] = id();\n    }\n};\n\n}  // namespace atcoder\n\n#include <library/tree/HeavyLightDecomposition.hpp>\n\
    \nstruct S {\n    int len;\n    long long pref, max, suff, sum;\n    S(int len,\
    \ long long pref, long long max, long long suff, long long sum) : len(len), pref(pref),\
    \ max(max), suff(suff), sum(sum) {}\n};\n\nconstexpr long long INF = std::numeric_limits<int>::max();\n\
    \nS op1(const S s1, const S s2) {\n    int len = s1.len + s2.len;\n    long long\
    \ pref = std::max(s1.pref, s1.sum + s2.pref);\n    long long max  = std::max({s1.max,\
    \ s2.max, s1.suff + s2.pref});\n    long long suff = std::max(s1.suff + s2.sum,\
    \ s2.suff);\n    long long sum  = s1.sum + s2.sum;\n    return {len, pref, max,\
    \ suff, sum};\n}\nS op2(const S s1, const S s2) {\n    return op1(s2, s1);\n}\n\
    S e() { \n    return {0, -INF, -INF, -INF, 0};\n}\nS mapping(long long f, S x)\
    \ {\n    int len = x.len;\n    if (f == -INF or len == 0) return x;\n    long\
    \ long max = f >= 0 ? f * len : f;\n    return {len, max, max, max, f * len};\n\
    }\nlong long composition(long long f, long long g) {\n    return f == -INF ? g\
    \ : f;\n}\nlong long id() {\n    return -INF;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> w(n);\n    for (long long &e : w) {\n        std::cin >> e;\n    }\n \
    \   std::vector<std::vector<int>> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    suisen::HeavyLightDecomposition hld(g);\n\
    \    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);\n\
    \    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        hld.update_point(i, [&](int j) {\n\
    \            seg1.set(j, {1, w[i], w[i], w[i], w[i]});\n            seg2.set(j,\
    \ {1, w[i], w[i], w[i], w[i]});\n        });\n    }\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        std::cin >> t >> a >> b >> c;\n   \
    \     --a, --b;\n        if (t == 1) {\n            hld.update_path(a, b, [&](int\
    \ l, int r) {\n                seg1.apply(l, r, c);\n                seg2.apply(l,\
    \ r, c);\n            });\n        } else {\n            std::cout << hld.fold_path_noncommutative(\n\
    \                a, b, e(), op1,\n                [&](int l, int r) { return seg1.prod(l,\
    \ r); },\n                [&](int l, int r) { return seg2.prod(l, r); }\n    \
    \        ).max << '\\n';\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - library/tree/HeavyLightDecomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp
  requiredBy: []
  timestamp: '2021-07-17 02:41:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp
- /verify/test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp.html
title: test/generated/tree/HeavyLightDecomposition/do_use_segment_tree.test.cpp
---
