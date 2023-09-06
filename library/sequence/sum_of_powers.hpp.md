---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/pow_mods.hpp
    title: "\u51AA\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':x:'
    path: library/sequence/bernoulli_number.hpp
    title: Bernoulli Number
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/sum_of_powers.hpp\"\n\n\n\n#line 1 \"library/math/pow_mods.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <int base_as_int,\
    \ typename mint>\n    struct static_pow_mods {\n        static_pow_mods() = default;\n\
    \        static_pow_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return pows[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = pows.size();\n    \
    \        if (sz > n) return;\n            pows.resize(n + 1);\n            for\
    \ (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];\n        }\n    private:\n\
    \        static inline std::vector<mint> pows { 1 };\n        static inline mint\
    \ base = base_as_int;\n        static constexpr int mod = mint::mod();\n    };\n\
    \n    template <typename mint>\n    struct pow_mods {\n        pow_mods() = default;\n\
    \        pow_mods(mint base, int n) : base(base) { ensure(n); }\n        const\
    \ mint& operator[](int i) const {\n            ensure(i);\n            return\
    \ pows[i];\n        }\n        void ensure(int n) const {\n            int sz\
    \ = pows.size();\n            if (sz > n) return;\n            pows.resize(n +\
    \ 1);\n            for (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];\n\
    \        }\n    private:\n        mutable std::vector<mint> pows { 1 };\n    \
    \    mint base;\n        static constexpr int mod = mint::mod();\n    };\n}\n\n\
    \n#line 1 \"library/sequence/bernoulli_number.hpp\"\n\n\n\n#line 1 \"library/math/factorial.hpp\"\
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
    \ suisen\n\n\n#line 5 \"library/sequence/bernoulli_number.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ bernoulli_number(int n) {\n        using mint = typename FPSType::value_type;\n\
    \        factorial<mint> fac(n);\n        FPSType a(n + 1);\n        for (int\
    \ i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);\n        a.inv_inplace(n + 1),\
    \ a.resize(n + 1);\n        for (int i = 2; i <= n; ++i) a[i] *= fac(i);\n   \
    \     return a;\n    }\n} // namespace suisen\n\n\n#line 6 \"library/sequence/sum_of_powers.hpp\"\
    \n\nnamespace suisen {\n    // res[p] = 1^p + 2^p + ... + n^p for p=0, ..., max_exponent\
    \ (O(k log k), where k=max_exponent)\n    template <typename FPSType>\n    auto\
    \ sum_of_powers(int n, int max_exponent, const std::vector<typename FPSType::value_type>\
    \ &bernoulli_table) {\n        const int k = max_exponent;\n        assert(bernoulli_table.size()\
    \ >= size_t(k + 2));\n        using fps = FPSType;\n        using mint = typename\
    \ FPSType::value_type;\n\n        factorial<mint> fac(k + 1);\n        pow_mods<mint>\
    \ pow_n(n, k + 1);\n\n        fps f(k + 2);\n        for (int j = 0; j <= k +\
    \ 1; ++j) {\n            f[j] = pow_n[j] * fac.fac_inv(j);\n        }\n      \
    \  std::vector<mint> b(bernoulli_table.begin(), bernoulli_table.begin() + (k +\
    \ 2));\n        b[1] *= -1; // b[1] = +1/2\n        for (int j = 0; j <= k + 1;\
    \ ++j) {\n            b[j] *= fac.fac_inv(j);\n        }\n        f *= b;\n\n\
    \        std::vector<mint> res(k + 1);\n        for (int p = 0; p <= k; ++p) {\n\
    \            res[p] = fac.fac(p) * (f[p + 1] - b[p + 1]);\n        }\n       \
    \ return res;\n    }\n\n    // res[p] = 1^p + 2^p + ... + n^p for p=0, ..., max_exponent\
    \ (O(k log k), where k=max_exponent)\n    template <typename FPSType>\n    auto\
    \ sum_of_powers(int n, int max_exponent) {\n        return sum_of_powers<FPSType>(n,\
    \ max_exponent, bernoulli_number<FPSType>(max_exponent + 1));\n    }\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_SUM_POWERS\n#define SUISEN_SUM_POWERS\n\n#include \"library/math/pow_mods.hpp\"\
    \n#include \"library/sequence/bernoulli_number.hpp\"\n\nnamespace suisen {\n \
    \   // res[p] = 1^p + 2^p + ... + n^p for p=0, ..., max_exponent (O(k log k),\
    \ where k=max_exponent)\n    template <typename FPSType>\n    auto sum_of_powers(int\
    \ n, int max_exponent, const std::vector<typename FPSType::value_type> &bernoulli_table)\
    \ {\n        const int k = max_exponent;\n        assert(bernoulli_table.size()\
    \ >= size_t(k + 2));\n        using fps = FPSType;\n        using mint = typename\
    \ FPSType::value_type;\n\n        factorial<mint> fac(k + 1);\n        pow_mods<mint>\
    \ pow_n(n, k + 1);\n\n        fps f(k + 2);\n        for (int j = 0; j <= k +\
    \ 1; ++j) {\n            f[j] = pow_n[j] * fac.fac_inv(j);\n        }\n      \
    \  std::vector<mint> b(bernoulli_table.begin(), bernoulli_table.begin() + (k +\
    \ 2));\n        b[1] *= -1; // b[1] = +1/2\n        for (int j = 0; j <= k + 1;\
    \ ++j) {\n            b[j] *= fac.fac_inv(j);\n        }\n        f *= b;\n\n\
    \        std::vector<mint> res(k + 1);\n        for (int p = 0; p <= k; ++p) {\n\
    \            res[p] = fac.fac(p) * (f[p + 1] - b[p + 1]);\n        }\n       \
    \ return res;\n    }\n\n    // res[p] = 1^p + 2^p + ... + n^p for p=0, ..., max_exponent\
    \ (O(k log k), where k=max_exponent)\n    template <typename FPSType>\n    auto\
    \ sum_of_powers(int n, int max_exponent) {\n        return sum_of_powers<FPSType>(n,\
    \ max_exponent, bernoulli_number<FPSType>(max_exponent + 1));\n    }\n} // namespace\
    \ suisen\n\n#endif // SUISEN_SUM_POWERS\n"
  dependsOn:
  - library/math/pow_mods.hpp
  - library/sequence/bernoulli_number.hpp
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/sequence/sum_of_powers.hpp
  requiredBy: []
  timestamp: '2023-09-06 20:34:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/sequence/sum_of_powers.hpp
layout: document
redirect_from:
- /library/library/sequence/sum_of_powers.hpp
- /library/library/sequence/sum_of_powers.hpp.html
title: library/sequence/sum_of_powers.hpp
---
