---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/pow_mods.hpp
    title: "\u51AA\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
    title: test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
    links: []
  bundledCode: "#line 1 \"library/polynomial/prod_f(r^k_x).hpp\"\n\n\n\n#line 1 \"\
    library/math/pow_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen {\n \
    \   template <int base_as_int, typename mint>\n    struct static_pow_mods {\n\
    \        static_pow_mods() {}\n        static_pow_mods(int n) { ensure(n); }\n\
    \        const mint& operator[](int i) const {\n            ensure(i);\n     \
    \       return pows[i];\n        }\n        static void ensure(int n) {\n    \
    \        int sz = pows.size();\n            if (sz > n) return;\n            pows.resize(n\
    \ + 1);\n            for (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];\n\
    \        }\n    private:\n        static inline std::vector<mint> pows { 1 };\n\
    \        static inline mint base = base_as_int;\n        static constexpr int\
    \ mod = mint::mod();\n    };\n\n    template <typename mint>\n    struct pow_mods\
    \ {\n        pow_mods() {}\n        pow_mods(mint base, int n) : base(base) {\
    \ ensure(n); }\n        const mint& operator[](int i) const {\n            ensure(i);\n\
    \            return pows[i];\n        }\n        void ensure(int n) const {\n\
    \            int sz = pows.size();\n            if (sz > n) return;\n        \
    \    pows.resize(n + 1);\n            for (int i = sz; i <= n; ++i) pows[i] =\
    \ base * pows[i - 1];\n        }\n    private:\n        mutable std::vector<mint>\
    \ pows { 1 };\n        mint base;\n        static constexpr int mod = mint::mod();\n\
    \    };\n}\n\n\n#line 5 \"library/polynomial/prod_f(r^k_x).hpp\"\n\n/**\n * @brief\
    \ $\\left(\\prod_{k=0}^{m-1} f(r^k x)\\right) \\bmod x^N$\n */\n\nnamespace suisen\
    \ {\n    namespace internal::prod_f_rk_x {\n        template <typename FPSType>\n\
    \        FPSType prod_f_rk_x(FPSType f, typename FPSType::value_type r, int m,\
    \ int result_size) {\n            using mint = typename FPSType::value_type;\n\
    \            pow_mods<mint> pow_r(r, result_size), pow_rm(r.pow(m), result_size);\n\
    \            if (auto opt_sp_f = f.sparse_fps_format(15); opt_sp_f.has_value())\
    \ {\n                bool all_invertible = true;\n                for (int i =\
    \ 1; i < result_size; ++i) {\n                    if (pow_r[i] == mint{ 1 }) {\n\
    \                        all_invertible = false;\n                        break;\n\
    \                    }\n                }\n                if (all_invertible)\
    \ {\n                    auto &sp_f = *opt_sp_f;\n                    sp_f.erase(sp_f.begin());\n\
    \                    FPSType g(result_size);\n                    g[0] = 1;\n\
    \                    for (int i = 1; i < result_size; ++i) {\n               \
    \         for (auto [j, fj] : sp_f) {\n                            if (j > i)\
    \ break;\n                            g[i] += g[i - j] * fj * (pow_r[i - j] -\
    \ pow_rm[j]);\n                        }\n                        g[i] /= 1 -\
    \ pow_r[i];\n                    }\n                    return g;\n          \
    \      }\n            }\n            f = f.log(result_size);\n            for\
    \ (int i = 1; i < result_size; ++i) f[i] *= pow_r[i] == mint{ 1 } ? mint{ m }\
    \ : (pow_rm[i] - 1) / (pow_r[i] - 1);\n            return f.exp(result_size);\n\
    \        }\n    }\n    /**\n     * \\brief Calculates \u03A0[k=0,m-1] f(r^k x)\
    \ mod x^N in O(NlogN) time.\n     * \\tparam FPSType type of formal power series\n\
    \     * \\param f formal power series\n     * \\param r ratio\n     * \\param\
    \ m the number of terms of the product\n     * \\param result_size N (default:\
    \ size of f)\n     * \\return \u03A0[k=0,m-1] f(r^k x) mod x^N \n     */\n   \
    \ template <typename FPSType>\n    FPSType prod_f_rk_x(FPSType f, const typename\
    \ FPSType::value_type r, const int m, int result_size = -1) {\n        using mint\
    \ = typename FPSType::value_type;\n        if (result_size < 0) result_size =\
    \ f.size();\n        if (r == mint{ 1 }) return f.pow(m, result_size);\n     \
    \   if (m == 0) { FPSType res{ 1 }; res.resize(result_size); return res; }\n \
    \       int z = 0;\n        while (z < int(f.size()) and f[z] == mint{ 0 }) ++z;\n\
    \        if (z == int(f.size()) or z >= (result_size + m - 1) / m) return FPSType(result_size,\
    \ mint{ 0 });\n        const mint c = f[z], d = c.pow(m) * r.pow((long long) m\
    \ * (m - 1) / 2 * z);\n        f >>= z, f /= c; // => f[0] = 1\n        f = internal::prod_f_rk_x::prod_f_rk_x(f,\
    \ r, m, result_size - z * m);\n        f *= d, f <<= z * m;\n        return f;\n\
    \    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_PROD_F_RK_X\n#define SUISEN_PROD_F_RK_X\n\n#include \"library/math/pow_mods.hpp\"\
    \n\n/**\n * @brief $\\left(\\prod_{k=0}^{m-1} f(r^k x)\\right) \\bmod x^N$\n */\n\
    \nnamespace suisen {\n    namespace internal::prod_f_rk_x {\n        template\
    \ <typename FPSType>\n        FPSType prod_f_rk_x(FPSType f, typename FPSType::value_type\
    \ r, int m, int result_size) {\n            using mint = typename FPSType::value_type;\n\
    \            pow_mods<mint> pow_r(r, result_size), pow_rm(r.pow(m), result_size);\n\
    \            if (auto opt_sp_f = f.sparse_fps_format(15); opt_sp_f.has_value())\
    \ {\n                bool all_invertible = true;\n                for (int i =\
    \ 1; i < result_size; ++i) {\n                    if (pow_r[i] == mint{ 1 }) {\n\
    \                        all_invertible = false;\n                        break;\n\
    \                    }\n                }\n                if (all_invertible)\
    \ {\n                    auto &sp_f = *opt_sp_f;\n                    sp_f.erase(sp_f.begin());\n\
    \                    FPSType g(result_size);\n                    g[0] = 1;\n\
    \                    for (int i = 1; i < result_size; ++i) {\n               \
    \         for (auto [j, fj] : sp_f) {\n                            if (j > i)\
    \ break;\n                            g[i] += g[i - j] * fj * (pow_r[i - j] -\
    \ pow_rm[j]);\n                        }\n                        g[i] /= 1 -\
    \ pow_r[i];\n                    }\n                    return g;\n          \
    \      }\n            }\n            f = f.log(result_size);\n            for\
    \ (int i = 1; i < result_size; ++i) f[i] *= pow_r[i] == mint{ 1 } ? mint{ m }\
    \ : (pow_rm[i] - 1) / (pow_r[i] - 1);\n            return f.exp(result_size);\n\
    \        }\n    }\n    /**\n     * \\brief Calculates \u03A0[k=0,m-1] f(r^k x)\
    \ mod x^N in O(NlogN) time.\n     * \\tparam FPSType type of formal power series\n\
    \     * \\param f formal power series\n     * \\param r ratio\n     * \\param\
    \ m the number of terms of the product\n     * \\param result_size N (default:\
    \ size of f)\n     * \\return \u03A0[k=0,m-1] f(r^k x) mod x^N \n     */\n   \
    \ template <typename FPSType>\n    FPSType prod_f_rk_x(FPSType f, const typename\
    \ FPSType::value_type r, const int m, int result_size = -1) {\n        using mint\
    \ = typename FPSType::value_type;\n        if (result_size < 0) result_size =\
    \ f.size();\n        if (r == mint{ 1 }) return f.pow(m, result_size);\n     \
    \   if (m == 0) { FPSType res{ 1 }; res.resize(result_size); return res; }\n \
    \       int z = 0;\n        while (z < int(f.size()) and f[z] == mint{ 0 }) ++z;\n\
    \        if (z == int(f.size()) or z >= (result_size + m - 1) / m) return FPSType(result_size,\
    \ mint{ 0 });\n        const mint c = f[z], d = c.pow(m) * r.pow((long long) m\
    \ * (m - 1) / 2 * z);\n        f >>= z, f /= c; // => f[0] = 1\n        f = internal::prod_f_rk_x::prod_f_rk_x(f,\
    \ r, m, result_size - z * m);\n        f *= d, f <<= z * m;\n        return f;\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_PROD_F_RK_X\n"
  dependsOn:
  - library/math/pow_mods.hpp
  isVerificationFile: false
  path: library/polynomial/prod_f(r^k_x).hpp
  requiredBy: []
  timestamp: '2022-10-08 20:12:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
documentation_of: library/polynomial/prod_f(r^k_x).hpp
layout: document
redirect_from:
- /library/library/polynomial/prod_f(r^k_x).hpp
- /library/library/polynomial/prod_f(r^k_x).hpp.html
title: $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
---
