---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/string/rolling_hash.hpp
    title: Rolling Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/rolling_hash/abc141_e.test.cpp
    title: test/src/string/rolling_hash/abc141_e.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/pow_mods.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    template <int base_as_int, typename mint>\n    struct\
    \ static_pow_mods {\n        static_pow_mods() {}\n        static_pow_mods(int\
    \ n) { ensure(n); }\n        const mint& operator[](int i) const {\n         \
    \   ensure(i);\n            return pows[i];\n        }\n        static void ensure(int\
    \ n) {\n            int sz = pows.size();\n            if (sz > n) return;\n \
    \           pows.resize(n + 1);\n            for (int i = sz; i <= n; ++i) pows[i]\
    \ = base * pows[i - 1];\n        }\n    private:\n        static inline std::vector<mint>\
    \ pows { 1 };\n        static inline mint base = base_as_int;\n        static\
    \ constexpr int mod = mint::mod();\n    };\n\n    template <typename mint>\n \
    \   struct pow_mods {\n        pow_mods() {}\n        pow_mods(mint base, int\
    \ n) : base(base) { ensure(n); }\n        const mint& operator[](int i) const\
    \ {\n            ensure(i);\n            return pows[i];\n        }\n        void\
    \ ensure(int n) const {\n            int sz = pows.size();\n            if (sz\
    \ > n) return;\n            pows.resize(n + 1);\n            for (int i = sz;\
    \ i <= n; ++i) pows[i] = base * pows[i - 1];\n        }\n    private:\n      \
    \  mutable std::vector<mint> pows { 1 };\n        mint base;\n        static constexpr\
    \ int mod = mint::mod();\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_POW_MOD\n#define SUISEN_POW_MOD\n\n#include <vector>\n\nnamespace\
    \ suisen {\n    template <int base_as_int, typename mint>\n    struct static_pow_mods\
    \ {\n        static_pow_mods() {}\n        static_pow_mods(int n) { ensure(n);\
    \ }\n        const mint& operator[](int i) const {\n            ensure(i);\n \
    \           return pows[i];\n        }\n        static void ensure(int n) {\n\
    \            int sz = pows.size();\n            if (sz > n) return;\n        \
    \    pows.resize(n + 1);\n            for (int i = sz; i <= n; ++i) pows[i] =\
    \ base * pows[i - 1];\n        }\n    private:\n        static inline std::vector<mint>\
    \ pows { 1 };\n        static inline mint base = base_as_int;\n        static\
    \ constexpr int mod = mint::mod();\n    };\n\n    template <typename mint>\n \
    \   struct pow_mods {\n        pow_mods() {}\n        pow_mods(mint base, int\
    \ n) : base(base) { ensure(n); }\n        const mint& operator[](int i) const\
    \ {\n            ensure(i);\n            return pows[i];\n        }\n        void\
    \ ensure(int n) const {\n            int sz = pows.size();\n            if (sz\
    \ > n) return;\n            pows.resize(n + 1);\n            for (int i = sz;\
    \ i <= n; ++i) pows[i] = base * pows[i - 1];\n        }\n    private:\n      \
    \  mutable std::vector<mint> pows { 1 };\n        mint base;\n        static constexpr\
    \ int mod = mint::mod();\n    };\n}\n\n#endif // SUISEN_POW_MOD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/pow_mods.hpp
  requiredBy:
  - library/string/rolling_hash.hpp
  timestamp: '2021-11-28 20:19:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/rolling_hash/abc141_e.test.cpp
documentation_of: library/math/pow_mods.hpp
layout: document
title: Pow Mods
---
## Pow Mods