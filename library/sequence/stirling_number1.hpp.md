---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/math/factorial_large.hpp
    title: Factorial Large
  - icon: ':x:'
    path: library/sequence/stirling_number1_small_prime_mod.hpp
    title: Stirling Number of the First Kind (Small Prime Mod)
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/sequence/stirling_number1/abc247_h.test.cpp
    title: test/src/sequence/stirling_number1/abc247_h.test.cpp
  - icon: ':x:'
    path: test/src/sequence/stirling_number1/stirling_number1.test.cpp
    title: test/src/sequence/stirling_number1/stirling_number1.test.cpp
  - icon: ':x:'
    path: test/src/sequence/stirling_number1/stirling_number1_2.test.cpp
    title: test/src/sequence/stirling_number1/stirling_number1_2.test.cpp
  - icon: ':x:'
    path: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/stirling_number1.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename mint>\n    class inv_mods {\n   \
    \ public:\n        inv_mods() = default;\n        inv_mods(int n) { ensure(n);\
    \ }\n        const mint& operator[](int i) const {\n            ensure(i);\n \
    \           return invs[i];\n        }\n        static void ensure(int n) {\n\
    \            int sz = invs.size();\n            if (sz < 2) invs = { 0, 1 }, sz\
    \ = 2;\n            if (sz < n + 1) {\n                invs.resize(n + 1);\n \
    \               for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) *\
    \ invs[mod % i];\n            }\n        }\n    private:\n        static std::vector<mint>\
    \ invs;\n        static constexpr int mod = mint::mod();\n    };\n    template\
    \ <typename mint>\n    std::vector<mint> inv_mods<mint>::invs{};\n\n    template\
    \ <typename mint>\n    std::vector<mint> get_invs(const std::vector<mint>& vs)\
    \ {\n        const int n = vs.size();\n\n        mint p = 1;\n        for (auto&\
    \ e : vs) {\n            p *= e;\n            assert(e != 0);\n        }\n   \
    \     mint ip = p.inv();\n\n        std::vector<mint> rp(n + 1);\n        rp[n]\
    \ = 1;\n        for (int i = n - 1; i >= 0; --i) {\n            rp[i] = rp[i +\
    \ 1] * vs[i];\n        }\n        std::vector<mint> res(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            res[i] = ip * rp[i + 1];\n            ip *=\
    \ vs[i];\n        }\n        return res;\n    }\n}\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, typename U = T>\n    struct factorial {\n\
    \        factorial() = default;\n        factorial(int n) { ensure(n); }\n\n \
    \       static void ensure(const int n) {\n            int sz = _fac.size();\n\
    \            if (n + 1 <= sz) return;\n            int new_size = std::max(n +\
    \ 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 7 \"library/sequence/stirling_number1.hpp\"\n\nnamespace suisen\
    \ {\n    /**\n     * return:\n     *   vector<mint> v s.t. v[i] = S1[n,n-i] for\
    \ i=0,...,k (unsigned)\n     * constraints:\n     *   0 <= n <= 10^6\n     */\n\
    \    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ stirling_number1_reversed(int n) {\n        using mint = typename FPSType::value_type;\n\
    \        factorial<mint> fac(n);\n        int l = 0;\n        while ((n >> l)\
    \ != 0) ++l;\n        FPSType a{ 1 };\n        int m = 0;\n        while (l--\
    \ > 0) {\n            FPSType f(m + 1), g(m + 1);\n            mint powm = 1;\n\
    \            for (int i = 0; i <= m; ++i, powm *= m) {\n                f[i] =\
    \ powm * fac.fac_inv(i);\n                g[i] = a[i] * fac.fac(m - i);\n    \
    \        }\n            f *= g, f.cut(m + 1);\n            for (int i = 0; i <=\
    \ m; ++i) f[i] *= fac.fac_inv(m - i);\n            a *= f, m *= 2, a.cut(m + 1);\n\
    \            if ((n >> l) & 1) {\n                a.push_back(0);\n          \
    \      for (int i = m; i > 0; --i) a[i] += m * a[i - 1];\n                ++m;\n\
    \            }\n        }\n        return a;\n    }\n    template <typename FPSType>\n\
    \    std::vector<typename FPSType::value_type> stirling_number1(int n) {\n   \
    \     std::vector<typename FPSType::value_type> a(stirling_number1_reversed<FPSType>(n));\n\
    \        std::reverse(a.begin(), a.end());\n        return a;\n    }\n    /**\n\
    \     * return:\n     *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k,\
    \ where S1 is the stirling number of the first kind (unsigned).\n     * constraints:\n\
    \     * - 0 <= n <= 10^18\n     * - 0 <= k <= 5000\n     * - k < mod\n     */\n\
    \    template <typename mint>\n    std::vector<mint> stirling_number1_reversed(const\
    \ long long n, const int k) {\n        inv_mods<mint> invs(k + 1);\n        std::vector<mint>\
    \ a(k + 1, 0);\n        a[0] = 1;\n        int l = 0;\n        while (n >> l)\
    \ ++l;\n        mint m = 0;\n        while (l-- > 0) {\n            std::vector<mint>\
    \ b(k + 1, 0);\n            for (int j = 0; j <= k; ++j) {\n                mint\
    \ tmp = 1;\n                for (int i = j; i <= k; ++i) {\n                 \
    \   b[i] += a[j] * tmp;\n                    tmp *= (m - i) * invs[i - j + 1]\
    \ * m;\n                }\n            }\n            for (int i = k + 1; i--\
    \ > 0;) {\n                mint sum = 0;\n                for (int j = 0; j <=\
    \ i; ++j) sum += a[j] * b[i - j];\n                a[i] = sum;\n            }\n\
    \            m *= 2;\n            if ((n >> l) & 1) {\n                for (int\
    \ i = k; i > 0; --i) a[i] += m * a[i - 1];\n                ++m;\n           \
    \ }\n        }\n        return a;\n    }\n    template <typename mint>\n    std::vector<std::vector<mint>>\
    \ stirling_number1_table(int n) {\n        std::vector dp(n + 1, std::vector<mint>{});\n\
    \        for (int i = 0; i <= n; ++i) {\n            dp[i].resize(i + 1);\n  \
    \          dp[i][0] = 0, dp[i][i] = 1;\n            for (int j = 1; j < i; ++j)\
    \ dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j];\n        }\n        return\
    \ dp;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_STIRLING_NUMBER_1\n#define SUISEN_STIRLING_NUMBER_1\n\n#include\
    \ <algorithm>\n#include \"library/math/inv_mods.hpp\"\n#include \"library/math/factorial.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * return:\n     *   vector<mint> v s.t.\
    \ v[i] = S1[n,n-i] for i=0,...,k (unsigned)\n     * constraints:\n     *   0 <=\
    \ n <= 10^6\n     */\n    template <typename FPSType>\n    std::vector<typename\
    \ FPSType::value_type> stirling_number1_reversed(int n) {\n        using mint\
    \ = typename FPSType::value_type;\n        factorial<mint> fac(n);\n        int\
    \ l = 0;\n        while ((n >> l) != 0) ++l;\n        FPSType a{ 1 };\n      \
    \  int m = 0;\n        while (l-- > 0) {\n            FPSType f(m + 1), g(m +\
    \ 1);\n            mint powm = 1;\n            for (int i = 0; i <= m; ++i, powm\
    \ *= m) {\n                f[i] = powm * fac.fac_inv(i);\n                g[i]\
    \ = a[i] * fac.fac(m - i);\n            }\n            f *= g, f.cut(m + 1);\n\
    \            for (int i = 0; i <= m; ++i) f[i] *= fac.fac_inv(m - i);\n      \
    \      a *= f, m *= 2, a.cut(m + 1);\n            if ((n >> l) & 1) {\n      \
    \          a.push_back(0);\n                for (int i = m; i > 0; --i) a[i] +=\
    \ m * a[i - 1];\n                ++m;\n            }\n        }\n        return\
    \ a;\n    }\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ stirling_number1(int n) {\n        std::vector<typename FPSType::value_type>\
    \ a(stirling_number1_reversed<FPSType>(n));\n        std::reverse(a.begin(), a.end());\n\
    \        return a;\n    }\n    /**\n     * return:\n     *   vector<mint> v s.t.\
    \ v[i] = S1[n,n-i] for i=0,...,k, where S1 is the stirling number of the first\
    \ kind (unsigned).\n     * constraints:\n     * - 0 <= n <= 10^18\n     * - 0\
    \ <= k <= 5000\n     * - k < mod\n     */\n    template <typename mint>\n    std::vector<mint>\
    \ stirling_number1_reversed(const long long n, const int k) {\n        inv_mods<mint>\
    \ invs(k + 1);\n        std::vector<mint> a(k + 1, 0);\n        a[0] = 1;\n  \
    \      int l = 0;\n        while (n >> l) ++l;\n        mint m = 0;\n        while\
    \ (l-- > 0) {\n            std::vector<mint> b(k + 1, 0);\n            for (int\
    \ j = 0; j <= k; ++j) {\n                mint tmp = 1;\n                for (int\
    \ i = j; i <= k; ++i) {\n                    b[i] += a[j] * tmp;\n           \
    \         tmp *= (m - i) * invs[i - j + 1] * m;\n                }\n         \
    \   }\n            for (int i = k + 1; i-- > 0;) {\n                mint sum =\
    \ 0;\n                for (int j = 0; j <= i; ++j) sum += a[j] * b[i - j];\n \
    \               a[i] = sum;\n            }\n            m *= 2;\n            if\
    \ ((n >> l) & 1) {\n                for (int i = k; i > 0; --i) a[i] += m * a[i\
    \ - 1];\n                ++m;\n            }\n        }\n        return a;\n \
    \   }\n    template <typename mint>\n    std::vector<std::vector<mint>> stirling_number1_table(int\
    \ n) {\n        std::vector dp(n + 1, std::vector<mint>{});\n        for (int\
    \ i = 0; i <= n; ++i) {\n            dp[i].resize(i + 1);\n            dp[i][0]\
    \ = 0, dp[i][i] = 1;\n            for (int j = 1; j < i; ++j) dp[i][j] = dp[i\
    \ - 1][j - 1] + (i - 1) * dp[i - 1][j];\n        }\n        return dp;\n    }\n\
    } // namespace suisen\n\n#endif // SUISEN_STIRLING_NUMBER_1\n"
  dependsOn:
  - library/math/inv_mods.hpp
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/sequence/stirling_number1.hpp
  requiredBy:
  - library/math/factorial_large.hpp
  - library/sequence/stirling_number1_small_prime_mod.hpp
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/sequence/stirling_number1/stirling_number1.test.cpp
  - test/src/sequence/stirling_number1/stirling_number1_2.test.cpp
  - test/src/sequence/stirling_number1/abc247_h.test.cpp
  - test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
documentation_of: library/sequence/stirling_number1.hpp
layout: document
title: Stirling Number1
---
## Stirling Number1

### stirling_number1_reversed

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> stirling_number1_reversed(int n) // (1)
  template <typename mint>
  std::vector<mint> stirling_number1_reversed(const long long n, const int k) // (2)
  ```

- 概要
  
  (符号なし) 第一種スターリング数 $\mathrm{S1}(n,\cdot)$ を逆順に並べた列 $A=(\mathrm{S1}(n,n),\mathrm{S1}(n,n-1),\ldots)$ を計算します．つまり，$A_i$ は集合 $\\\{0,\ldots,n-1\\\}$ から $i$ 個の要素を選んで積を取ったものの総和となります．形式的には，以下が成り立ちます．

  $$A_i=\sum_{\overset{\scriptstyle S\subset\{0,\ldots,n-1\},}{|S|=i}}\prod_{j\in S} j$$

  組合せ的には，$\mathrm{S1}(n,i)$ はラベル付けされた $n$ 個の玉を $i$ 個の円環 (巡回列) に分割する方法の個数と一致します．

- テンプレート引数

  - `mint`: modint 型を想定

- 返り値

  1. $\\\{A_i\\\} _ {i=0} ^ n=\\\{\mathrm{S1}(n,n-i)\\\} _ {i=0} ^ {n}$
  2. $\\\{A_i\\\} _ {i=0} ^ k=\\\{\mathrm{S1}(n,n-i)\\\} _ {i=0} ^ {k}$

      Note. $k>n$ の場合は $A_{n+1}=\cdots=A_{k}=0$ が保証される．

- 制約

  1. - $0\leq n\leq 10 ^ 6$
  2. - $0\leq n\leq 10 ^ {18}$
     - $0\leq k\leq 5000$
     - $k\lt \mathrm{mod}$

- 時間計算量

  1. $O(n\log n)$
  2. $O(k ^ 2\log n)$

- 参考

  - [スターリング数 - Wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%AA%E3%83%B3%E3%82%B0%E6%95%B0)
  - [第一種スターリング数の末尾項を計算する](https://suisen-kyopro.hatenablog.com/entry/2021/06/02/225932)

### stirling_number1

- シグネチャ
  
  ```cpp
  template <typename mint>
  std::vector<mint> stirling_number1(int n)
  ```

- 概要
  
  [stirling number1 reversed](#stirling_number1_reversed) (1) の列を逆順にしたもの，つまり (符号なし) 第一種スターリング数の列 $\\\{\mathrm{S1}(n,i)\\\} _ {i=0} ^ n$ を計算します．