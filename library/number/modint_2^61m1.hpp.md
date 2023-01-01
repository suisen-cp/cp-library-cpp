---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/string/rolling_hash.hpp
    title: Rolling Hash
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/string/rolling_hash/abc141_e.test.cpp
    title: test/src/string/rolling_hash/abc141_e.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
  bundledCode: "#line 1 \"library/number/modint_2^61m1.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n\nnamespace suisen {\n    // reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    \    struct modint2p61m1 {\n        using self = modint2p61m1;\n\n        constexpr\
    \ modint2p61m1(): v(0) {}\n        constexpr modint2p61m1(uint64_t v): v(fast_mod(v))\
    \ {}\n\n        static constexpr uint64_t mod() {\n            return _mod;\n\
    \        }\n\n        static constexpr uint64_t fast_mod(uint64_t v) {\n     \
    \       constexpr uint32_t mid = 61;\n            constexpr uint64_t mask = (uint64_t(1)\
    \ << mid) - 1;\n            uint64_t u = v >> mid;\n            uint64_t d = v\
    \ & mask;\n            uint64_t res = u + d;\n            if (res >= _mod) res\
    \ -= _mod;\n            return res;\n        }\n\n        constexpr uint64_t val()\
    \ const {\n            return v;\n        }\n\n        constexpr self& operator+=(const\
    \ self& rhs) {\n            v += rhs.v;\n            if (v >= _mod) v -= _mod;\n\
    \            return *this;\n        }\n        constexpr self& operator-=(const\
    \ self& rhs) {\n            if (v < rhs.v) v += _mod;\n            v -= rhs.v;\n\
    \            return *this;\n        }\n        constexpr self& operator*=(const\
    \ self& rhs) {\n            uint64_t au = v >> mid31;     // < 2^30\n        \
    \    uint64_t ad = v & mask31;     // < 2^31\n            uint64_t bu = rhs.v\
    \ >> mid31; // < 2^30\n            uint64_t bd = rhs.v & mask31; // < 2^31\n\n\
    \            //   a * b\n            // = (au * 2^31 + ad) * (bu * 2^31 + bd)\n\
    \            // = au * bu * 2^62             # au * bu * 2^62 \u2261 au * bu *\
    \ 2 < 2^61\n            // + (au * bd + ad * bu) * 2^31 # m := au * bd + ad *\
    \ bu\n            //                              # m <= 2 * (2^31 - 1) * (2^30\
    \ - 1) = 2^62 - 6 * 2^30 + 2\n            //                              # m\
    \ = mu * 2^30 + md (0 <= mu < 2^32, 0 <= md < 2^30)\n            //          \
    \                    # m * 2^31 \u2261 mu + md * 2^31 < 2^61 + 2^31\n        \
    \    // + ad * bd                    # ad * bd <= (2^31 - 1) ** 2 = 2^62 - 2^32\
    \ + 1 < 2^62 - 2^31\n            // \u2261 au * bu * 2 + mu + md * 2^31 + ad *\
    \ bd < 2^63\n\n            uint64_t m = au * bd + ad * bu;\n            uint64_t\
    \ mu = m >> mid30;\n            uint64_t md = m & mask30;\n\n            v = fast_mod((au\
    \ * bu << 1) + mu + (md << 31) + ad * bd);\n            return *this;\n      \
    \  }\n\n        constexpr friend self operator+(const self& l, const self& r)\
    \ { return self(l) += r; }\n        constexpr friend self operator-(const self&\
    \ l, const self& r) { return self(l) -= r; }\n        constexpr friend self operator*(const\
    \ self& l, const self& r) { return self(l) *= r; }\n        constexpr friend bool\
    \ operator==(const self& l, const self& r) { return l.v == r.v; }\n\n        constexpr\
    \ self pow(long long b) const {\n            assert(b >= 0);\n            self\
    \ x = 1, p = *this;\n            for (; b; b >>= 1) {\n                if (b &\
    \ 1) x *= p;\n                p *= p;\n            }\n            return x;\n\
    \        }\n        constexpr self inv() const {\n            // a ** (p - 2)\
    \ = a ** (2**61 - 3)\n            // 2**61 - 3 = 0001_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1101\n\
    \            self x = *this, p = *this * *this;\n            for (int i = 2; i\
    \ <= 60; ++i) {\n                x *= (p *= p);\n            }\n            return\
    \ x;\n        }\n    private:\n        static constexpr uint64_t _mod = (uint64_t(1)\
    \ << 61) - 1; // 2**61-1 : prime\n\n        static constexpr uint32_t mid31 =\
    \ 31;\n        static constexpr uint64_t mask31 = (uint64_t(1) << 31) - 1;\n \
    \       static constexpr uint32_t mid30 = 30;\n        static constexpr uint64_t\
    \ mask30 = (uint64_t(1) << mid30) - 1;\n\n        uint64_t v;\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_MODINT_2p61m1\n#define SUISEN_MODINT_2p61m1\n\n#include <cassert>\n\
    #include <cstdint>\n\nnamespace suisen {\n    // reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    \    struct modint2p61m1 {\n        using self = modint2p61m1;\n\n        constexpr\
    \ modint2p61m1(): v(0) {}\n        constexpr modint2p61m1(uint64_t v): v(fast_mod(v))\
    \ {}\n\n        static constexpr uint64_t mod() {\n            return _mod;\n\
    \        }\n\n        static constexpr uint64_t fast_mod(uint64_t v) {\n     \
    \       constexpr uint32_t mid = 61;\n            constexpr uint64_t mask = (uint64_t(1)\
    \ << mid) - 1;\n            uint64_t u = v >> mid;\n            uint64_t d = v\
    \ & mask;\n            uint64_t res = u + d;\n            if (res >= _mod) res\
    \ -= _mod;\n            return res;\n        }\n\n        constexpr uint64_t val()\
    \ const {\n            return v;\n        }\n\n        constexpr self& operator+=(const\
    \ self& rhs) {\n            v += rhs.v;\n            if (v >= _mod) v -= _mod;\n\
    \            return *this;\n        }\n        constexpr self& operator-=(const\
    \ self& rhs) {\n            if (v < rhs.v) v += _mod;\n            v -= rhs.v;\n\
    \            return *this;\n        }\n        constexpr self& operator*=(const\
    \ self& rhs) {\n            uint64_t au = v >> mid31;     // < 2^30\n        \
    \    uint64_t ad = v & mask31;     // < 2^31\n            uint64_t bu = rhs.v\
    \ >> mid31; // < 2^30\n            uint64_t bd = rhs.v & mask31; // < 2^31\n\n\
    \            //   a * b\n            // = (au * 2^31 + ad) * (bu * 2^31 + bd)\n\
    \            // = au * bu * 2^62             # au * bu * 2^62 \u2261 au * bu *\
    \ 2 < 2^61\n            // + (au * bd + ad * bu) * 2^31 # m := au * bd + ad *\
    \ bu\n            //                              # m <= 2 * (2^31 - 1) * (2^30\
    \ - 1) = 2^62 - 6 * 2^30 + 2\n            //                              # m\
    \ = mu * 2^30 + md (0 <= mu < 2^32, 0 <= md < 2^30)\n            //          \
    \                    # m * 2^31 \u2261 mu + md * 2^31 < 2^61 + 2^31\n        \
    \    // + ad * bd                    # ad * bd <= (2^31 - 1) ** 2 = 2^62 - 2^32\
    \ + 1 < 2^62 - 2^31\n            // \u2261 au * bu * 2 + mu + md * 2^31 + ad *\
    \ bd < 2^63\n\n            uint64_t m = au * bd + ad * bu;\n            uint64_t\
    \ mu = m >> mid30;\n            uint64_t md = m & mask30;\n\n            v = fast_mod((au\
    \ * bu << 1) + mu + (md << 31) + ad * bd);\n            return *this;\n      \
    \  }\n\n        constexpr friend self operator+(const self& l, const self& r)\
    \ { return self(l) += r; }\n        constexpr friend self operator-(const self&\
    \ l, const self& r) { return self(l) -= r; }\n        constexpr friend self operator*(const\
    \ self& l, const self& r) { return self(l) *= r; }\n        constexpr friend bool\
    \ operator==(const self& l, const self& r) { return l.v == r.v; }\n\n        constexpr\
    \ self pow(long long b) const {\n            assert(b >= 0);\n            self\
    \ x = 1, p = *this;\n            for (; b; b >>= 1) {\n                if (b &\
    \ 1) x *= p;\n                p *= p;\n            }\n            return x;\n\
    \        }\n        constexpr self inv() const {\n            // a ** (p - 2)\
    \ = a ** (2**61 - 3)\n            // 2**61 - 3 = 0001_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1101\n\
    \            self x = *this, p = *this * *this;\n            for (int i = 2; i\
    \ <= 60; ++i) {\n                x *= (p *= p);\n            }\n            return\
    \ x;\n        }\n    private:\n        static constexpr uint64_t _mod = (uint64_t(1)\
    \ << 61) - 1; // 2**61-1 : prime\n\n        static constexpr uint32_t mid31 =\
    \ 31;\n        static constexpr uint64_t mask31 = (uint64_t(1) << 31) - 1;\n \
    \       static constexpr uint32_t mid30 = 30;\n        static constexpr uint64_t\
    \ mask30 = (uint64_t(1) << mid30) - 1;\n\n        uint64_t v;\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_MODINT_2p61m1\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/modint_2^61m1.hpp
  requiredBy:
  - library/string/rolling_hash.hpp
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/string/rolling_hash/abc141_e.test.cpp
documentation_of: library/number/modint_2^61m1.hpp
layout: document
redirect_from:
- /library/library/number/modint_2^61m1.hpp
- /library/library/number/modint_2^61m1.hpp.html
title: library/number/modint_2^61m1.hpp
---
