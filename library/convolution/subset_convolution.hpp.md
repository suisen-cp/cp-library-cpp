---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/sps.hpp
    title: Set Power Series
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc213_g.test.cpp
    title: test/src/math/sps/abc213_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc236_h.test.cpp
    title: test/src/math/sps/abc236_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc253_h.test.cpp
    title: test/src/math/sps/abc253_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc253_h_2.test.cpp
    title: test/src/math/sps/abc253_h_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/arc105_f.test.cpp
    title: test/src/math/sps/arc105_f.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/convolution/subset_convolution.hpp: line 5: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef SUISEN_SUBSET_CONVOLUTION\n#define SUISEN_SUBSET_CONVOLUTION\n\n\
    #ifdef USE_ARRAY_FPS\n#include \"library/polynomial/array_fps_naive.hpp\"\n#else\n\
    #include \"library/polynomial/fps_naive.hpp\"\n#endif\n\n#include \"library/transform/subset.hpp\"\
    \n\nnamespace suisen {\n    namespace ranked_subset_transform {\n#ifdef USE_ARRAY_FPS\n\
    \        template <typename T>\n        using polynomial_t = ArrayFPSNaive<T,\
    \ USE_ARRAY_FPS>;\n#else\n        template <typename T>\n        using polynomial_t\
    \ = FPSNaive<T>;\n#endif\n\n        namespace internal {\n            template\
    \ <typename T>\n            std::vector<polynomial_t<T>> ranked(const std::vector<T>&\
    \ a) {\n                const int n = a.size();\n                assert((-n &\
    \ n) == n);\n#ifdef USE_ARRAY_FPS\n                std::vector fs(n, polynomial_t<T>{});\n\
    #else\n                std::vector fs(n, polynomial_t<T>(__builtin_ctz(n) + 1,\
    \ T{ 0 }));\n#endif\n                for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)]\
    \ = a[i];\n                return fs;\n            }\n            template <typename\
    \ T>\n            std::vector<T> deranked(const std::vector<polynomial_t<T>>&\
    \ polys) {\n                const int n = polys.size();\n                assert((-n\
    \ & n) == n);\n                std::vector<T> a(n);\n                for (int\
    \ i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n               \
    \ return a;\n            }\n        } // suisen::ranked_subset_transform::internal\n\
    \n        template <typename T>\n        std::vector<polynomial_t<T>> ranked_zeta(const\
    \ std::vector<T>& a) {\n            std::vector<polynomial_t<T>> ranked = internal::ranked<T>(a);\n\
    \            subset_transform::zeta(ranked);\n            return ranked;\n   \
    \     }\n        template <typename T>\n        std::vector<T> deranked_mobius(std::vector<polynomial_t<T>>&\
    \ ranked) {\n            subset_transform::mobius(ranked);\n            return\
    \ internal::deranked<T>(ranked);\n        }\n    } // suisen::ranked_subset_transform\n\
    \n    template <typename T>\n    std::vector<T> subset_convolution(const std::vector<T>&\
    \ a, const std::vector<T>& b) {\n        const int n = a.size();\n        auto\
    \ ra = ranked_subset_transform::ranked_zeta(a), rb = ranked_subset_transform::ranked_zeta(b);\n\
    \        for (int i = 0; i < n; ++i) ra[i] = ra[i].mul(rb[i], ra[i].deg());\n\
    \        return ranked_subset_transform::deranked_mobius(ra);\n    }\n} // namespace\
    \ suisen\n\n#endif // SUISEN_SUBSET_CONVOLUTION\n"
  dependsOn:
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/transform/subset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/convolution/subset_convolution.hpp
  requiredBy:
  - library/math/sps.hpp
  timestamp: '2022-06-27 18:52:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/sps/abc253_h_2.test.cpp
  - test/src/math/sps/arc105_f.test.cpp
  - test/src/math/sps/abc236_h.test.cpp
  - test/src/math/sps/abc253_h.test.cpp
  - test/src/math/sps/abc213_g.test.cpp
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
documentation_of: library/convolution/subset_convolution.hpp
layout: document
title: Subset Convolution
---

### subset_convolution

__TODO__: 抽象化

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の直和演算で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \sqcup j = k } A _ i \cdot B _ j $$

  ここで，$i\sqcup j=k$ は $i\And j=0$ かつ $i\mid j=k$ と等価です．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=`，`operator*` が定義されている必要があります．

- 返り値
  
  $A\ast B$

- 制約

  - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N(\log N)^2)$，あるいは $\Theta(L^2\cdot 2^L)$
