---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/cartesian_tree.hpp
    title: Cartesian Tree
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/convert_to_newton_basis.hpp
    title: Convert To Newton Basis
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/rook_polynomial/abc272_h.test.cpp
    title: test/src/polynomial/rook_polynomial/abc272_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/rook_polynomial/dummy.test.cpp
    title: test/src/polynomial/rook_polynomial/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/rook_polynomial.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n#line\
    \ 1 \"library/polynomial/convert_to_newton_basis.hpp\"\n\n\n\n#include <tuple>\n\
    #line 6 \"library/polynomial/convert_to_newton_basis.hpp\"\n\nnamespace suisen\
    \ {\n    // Returns b=(b_0,...,b_{N-1}) s.t. f(x) = Sum[i=0,N-1] b_i Prod[j=0,i-1](x\
    \ - p_j)\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ convert_to_newton_basis(const FPSType& f, const std::vector<typename FPSType::value_type>&\
    \ p) {\n        const int n = p.size();\n        assert(f.size() == n);\n\n  \
    \      int m = 1;\n        while (m < n) m <<= 1;\n\n        std::vector<FPSType>\
    \ seg(2 * m);\n        for (int i = 0; i < m; ++i) {\n            seg[m + i] =\
    \ { i < n ? -p[i] : 0, 1 };\n        }\n        for (int i = m - 1; i > 0; --i)\
    \ {\n            if (((i + 1) & -(i + 1)) == (i + 1)) continue; // i = 2^k - 1\n\
    \            seg[i] = seg[2 * i] * seg[2 * i + 1];\n        }\n\n        seg[1]\
    \ = f;\n        for (int i = 1; i < m; ++i) {\n            std::tie(seg[2 * i\
    \ + 1], seg[2 * i]) = seg[i].div_mod(seg[2 * i]);\n        }\n\n        std::vector<typename\
    \ FPSType::value_type> b(n);\n        for (int i = 0; i < n; ++i) {\n        \
    \    b[i] = seg[m + i].safe_get(0);\n        }\n        return b;\n    }\n} //\
    \ namespace suisen\n\n\n\n#line 1 \"library/datastructure/cartesian_tree.hpp\"\
    \n\n\n\n#include <array>\n#line 6 \"library/datastructure/cartesian_tree.hpp\"\
    \n#include <functional>\n#line 8 \"library/datastructure/cartesian_tree.hpp\"\n\
    \nnamespace suisen {\n    struct CartesianTree : public std::vector<std::array<int,\
    \ 2>> {\n        using base_type = std::vector<std::array<int, 2>>;\n\n      \
    \  static constexpr int absent = -1;\n\n        const int root;\n\n        CartesianTree()\
    \ : base_type(), root(0) {}\n        CartesianTree(int root, const base_type&\
    \ g) : base_type(g), root(root) {}\n        CartesianTree(int root, base_type&&\
    \ g) : base_type(std::move(g)), root(root) {}\n\n        auto ranges() const {\n\
    \            std::vector<std::pair<int, int>> res;\n            res.reserve(size());\n\
    \            auto rec = [&](auto rec, int l, int m, int r) -> void {\n       \
    \         if (m == absent) return;\n                const auto& [lm, rm] = (*this)[m];\n\
    \                rec(rec, l, lm, m), res.emplace_back(l, r), rec(rec, m + 1, rm,\
    \ r);\n            };\n            rec(rec, 0, root, size());\n            return\
    \ res;\n        }\n    };\n\n    template <typename Comparator>\n    struct CartesianTreeBuilder\
    \ {\n        CartesianTreeBuilder() = default;\n        template <typename RandomAccessibleContainer>\n\
    \        CartesianTreeBuilder(const RandomAccessibleContainer& a, Comparator comp\
    \ = Comparator{}) : n(a.size()), comp(comp), par(calc_par(a, comp)) {}\n\n   \
    \     CartesianTree build() const {\n            int root = -1;\n            std::vector<std::array<int,\
    \ 2>> g(n, { CartesianTree::absent, CartesianTree::absent });\n            for\
    \ (int i = 0; i < n; ++i) {\n                int p = par[i];\n               \
    \ (p >= 0 ? g[p][p <= i] : root) = i;\n            }\n            return CartesianTree{\
    \ root, std::move(g) };\n        }\n\n        template <typename RandomAccessibleContainer>\n\
    \        static CartesianTree build(const RandomAccessibleContainer& a, Comparator\
    \ comp = Comparator{}) {\n            return CartesianTreeBuilder(a, comp).build();\n\
    \        }\n\n        int parent(std::size_t i) const {\n            assert(i\
    \ < std::size_t(n));\n            return par[i];\n        }\n        int operator[](std::size_t\
    \ i) const {\n            return parent(i);\n        }\n    private:\n       \
    \ const int n;\n        const Comparator comp;\n        const std::vector<int>\
    \ par;\n\n        template <typename RandomAccessibleContainer>\n        static\
    \ std::vector<int> calc_par(const RandomAccessibleContainer& a, Comparator comp)\
    \ {\n            const int n = a.size();\n            std::vector<int> par(n,\
    \ -1);\n            for (int i = 1; i < n; ++i) {\n                int p = i -\
    \ 1, l = i;\n                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];\n\
    \                par[l] = i, par[i] = p;\n            }\n            return par;\n\
    \        }\n    };\n\n    using MinCartesianTreeBuilder = CartesianTreeBuilder<std::less<>>;\n\
    \    using MaxCartesianTreeBuilder = CartesianTreeBuilder<std::greater<>>;\n}\
    \ // namespace suisen\n\n\n#line 1 \"library/math/factorial.hpp\"\n\n\n\n#line\
    \ 6 \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T, typename U = T>\n    struct factorial {\n        factorial() = default;\n\
    \        factorial(int n) { ensure(n); }\n\n        static void ensure(const int\
    \ n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n\n        T fac(const int i) {\n            ensure(i);\n\
    \            return _fac[i];\n        }\n        T operator()(int i) {\n     \
    \       return fac(i);\n        }\n        U fac_inv(const int i) {\n        \
    \    ensure(i);\n            return _fac_inv[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return _fac[n] * _fac_inv[r] * _fac_inv[n\
    \ - r];\n        }\n        template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        U polynom(const int n, const Ds& ...ds)\
    \ {\n            if (n < 0) return 0;\n            ensure(n);\n            int\
    \ sumd = 0;\n            U res = _fac[n];\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= _fac_inv[d];\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= _fac_inv[n - sumd];\n            return res;\n\
    \        }\n        U perm(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return _fac[n]\
    \ * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T> _fac;\n\
    \        static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 12 \"library/polynomial/rook_polynomial.hpp\"\n\nnamespace\
    \ suisen {\n    // O(n(log n)^2). returns rook polynomial r s.t. r[k] := # ways\
    \ to put k non-attacking rooks on a ferrers board\n    template <typename FPSType>\n\
    \    FPSType rook_polynomial_ferrers_board(const std::vector<int> &h) {\n    \
    \    using mint = typename FPSType::value_type;\n        assert(std::is_sorted(h.begin(),\
    \ h.end()));\n        const int n = h.size();\n        std::vector<FPSType> fs(n);\n\
    \        for (int i = 0; i < n; ++i) fs[i] = FPSType{ h[i] - i, 1 };\n       \
    \ FPSType f = FPSType::prod(fs);\n        std::vector<mint> p(n + 1);\n      \
    \  std::iota(p.begin(), p.end(), 0);\n        FPSType r = convert_to_newton_basis(f,\
    \ p);\n        std::reverse(r.begin(), r.end());\n        return r;\n    }\n\n\
    \    // O(n^2 log n). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking\
    \ rooks on a skyline board\n    template <typename FPSType>\n    FPSType rook_polynomial_skyline_board(const\
    \ std::vector<int> &h) {\n        using fps = FPSType;\n        using mint = typename\
    \ fps::value_type;\n\n        const int n = h.size();\n\n        factorial<mint>\
    \ fac(n);\n\n        MinCartesianTreeBuilder ct_builder{h};\n        CartesianTree\
    \ t = ct_builder.build();\n        auto dfs = [&](auto dfs, int u, int l, int\
    \ r) -> fps {\n            if (u == t.absent) return { 1 };\n            fps f\
    \ = dfs(dfs, t[u][0], l, u);\n            fps g = dfs(dfs, t[u][1], u + 1, r);\n\
    \            fps fg = f * g; // O(n^2)\n            fg.push_back(0);\n\n     \
    \       const int a = h[u] - (u == t.root ? 0 : h[ct_builder.parent(u)]);\n  \
    \          const int b = r - l;\n            assert(int(fg.size()) == b + 1);\n\
    \n            fps s(b + 1), t(b + 1);\n            mint binom_a_i = 1;\n     \
    \       for (int i = 0; i <= b; ++i) {\n                s[i] = fg[i] * fac.fac(b\
    \ - i);\n                t[i] = binom_a_i;\n                binom_a_i *= (a -\
    \ i) * fac.fac_inv(i + 1) * fac.fac(i);\n            }\n            fps st = s\
    \ * t;\n            st.resize(b + 1);\n            for (int i = 0; i <= b; ++i)\
    \ {\n                st[i] *= fac.fac_inv(b - i);\n            }\n           \
    \ return st;\n        };\n\n        return dfs(dfs, t.root, 0, n);\n    }\n} //\
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ROOK_POLYNOMIAL\n#define SUISEN_ROOK_POLYNOMIAL\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n#include\
    \ \"library/polynomial/convert_to_newton_basis.hpp\"\n#include \"library/datastructure/cartesian_tree.hpp\"\
    \n#include \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    // O(n(log\
    \ n)^2). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking\
    \ rooks on a ferrers board\n    template <typename FPSType>\n    FPSType rook_polynomial_ferrers_board(const\
    \ std::vector<int> &h) {\n        using mint = typename FPSType::value_type;\n\
    \        assert(std::is_sorted(h.begin(), h.end()));\n        const int n = h.size();\n\
    \        std::vector<FPSType> fs(n);\n        for (int i = 0; i < n; ++i) fs[i]\
    \ = FPSType{ h[i] - i, 1 };\n        FPSType f = FPSType::prod(fs);\n        std::vector<mint>\
    \ p(n + 1);\n        std::iota(p.begin(), p.end(), 0);\n        FPSType r = convert_to_newton_basis(f,\
    \ p);\n        std::reverse(r.begin(), r.end());\n        return r;\n    }\n\n\
    \    // O(n^2 log n). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking\
    \ rooks on a skyline board\n    template <typename FPSType>\n    FPSType rook_polynomial_skyline_board(const\
    \ std::vector<int> &h) {\n        using fps = FPSType;\n        using mint = typename\
    \ fps::value_type;\n\n        const int n = h.size();\n\n        factorial<mint>\
    \ fac(n);\n\n        MinCartesianTreeBuilder ct_builder{h};\n        CartesianTree\
    \ t = ct_builder.build();\n        auto dfs = [&](auto dfs, int u, int l, int\
    \ r) -> fps {\n            if (u == t.absent) return { 1 };\n            fps f\
    \ = dfs(dfs, t[u][0], l, u);\n            fps g = dfs(dfs, t[u][1], u + 1, r);\n\
    \            fps fg = f * g; // O(n^2)\n            fg.push_back(0);\n\n     \
    \       const int a = h[u] - (u == t.root ? 0 : h[ct_builder.parent(u)]);\n  \
    \          const int b = r - l;\n            assert(int(fg.size()) == b + 1);\n\
    \n            fps s(b + 1), t(b + 1);\n            mint binom_a_i = 1;\n     \
    \       for (int i = 0; i <= b; ++i) {\n                s[i] = fg[i] * fac.fac(b\
    \ - i);\n                t[i] = binom_a_i;\n                binom_a_i *= (a -\
    \ i) * fac.fac_inv(i + 1) * fac.fac(i);\n            }\n            fps st = s\
    \ * t;\n            st.resize(b + 1);\n            for (int i = 0; i <= b; ++i)\
    \ {\n                st[i] *= fac.fac_inv(b - i);\n            }\n           \
    \ return st;\n        };\n\n        return dfs(dfs, t.root, 0, n);\n    }\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_ROOK_POLYNOMIAL\n"
  dependsOn:
  - library/polynomial/convert_to_newton_basis.hpp
  - library/datastructure/cartesian_tree.hpp
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/polynomial/rook_polynomial.hpp
  requiredBy: []
  timestamp: '2024-01-31 02:33:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/rook_polynomial/abc272_h.test.cpp
  - test/src/polynomial/rook_polynomial/dummy.test.cpp
documentation_of: library/polynomial/rook_polynomial.hpp
layout: document
redirect_from:
- /library/library/polynomial/rook_polynomial.hpp
- /library/library/polynomial/rook_polynomial.hpp.html
title: library/polynomial/rook_polynomial.hpp
---
