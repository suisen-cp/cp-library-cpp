---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_large.hpp
    title: Convolution Large
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_large
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_large
    - https://judge.yosupo.jp/submission/21623
  bundledCode: "#line 1 \"test/src/convolution/convolution_large/convolution_large.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_large\"\n\n\
    #include <iostream>\n#include <cstring>\n\n#line 1 \"library/convolution/convolution_large.hpp\"\
    \n\n\n\n#include <atcoder/convolution>\n\nnamespace suisen {\n    template <typename\
    \ mint, atcoder::internal::is_static_modint_t<mint>* = nullptr>\n    std::vector<mint>\
    \ convolution_large(const std::vector<mint>& a, const std::vector<mint>& b) {\n\
    \        static constexpr int max_size = (mint::mod() - 1) & -(mint::mod() - 1);\n\
    \        static constexpr int half_size = max_size >> 1;\n        static constexpr\
    \ int inv_max_size = atcoder::internal::inv_gcd(max_size, mint::mod()).second;\n\
    \n        const int n = int(a.size()), m = int(b.size());\n        if (n + m -\
    \ 1 <= max_size) return atcoder::convolution(a, b);\n        if (n == 0 or m ==\
    \ 0) return {};\n\n        const int dn = (n + half_size - 1) / half_size;\n \
    \       const int dm = (m + half_size - 1) / half_size;\n\n        std::vector<std::vector<mint>>\
    \ as(dn), bs(dm);\n        for (int i = 0; i < dn; ++i) {\n            const int\
    \ offset = half_size * i;\n            as[i] = std::vector<mint>(a.begin() + offset,\
    \ a.begin() + std::min(n, offset + half_size));\n            as[i].resize(max_size);\n\
    \            atcoder::internal::butterfly(as[i]);\n        }\n        for (int\
    \ j = 0; j < dm; ++j) {\n            const int offset = half_size * j;\n     \
    \       bs[j] = std::vector<mint>(b.begin() + offset, b.begin() + std::min(m,\
    \ offset + half_size));\n            bs[j].resize(max_size);\n            atcoder::internal::butterfly(bs[j]);\n\
    \        }\n        std::vector<std::vector<mint>> cs(dn + dm - 1, std::vector<mint>(max_size));\n\
    \        for (int i = 0; i < dn; ++i) for (int j = 0; j < dm; ++j) {\n       \
    \     for (int k = 0; k < max_size; ++k) cs[i + j][k] += as[i][k] * bs[j][k];\n\
    \        }\n        std::vector<mint> res(n + m - 1);\n        for (int i = 0;\
    \ i < dn + dm - 1; ++i) {\n            atcoder::internal::butterfly_inv(cs[i]);\n\
    \            const int offset = half_size * i;\n            const int jmax = std::min(n\
    \ + m - 1 - offset, max_size);\n            for (int j = 0; j < jmax; ++j) {\n\
    \                res[offset + j] += cs[i][j] * mint::raw(inv_max_size);\n    \
    \        }\n        }\n        return res;\n    }\n} // namespace suisen\n\n\n\
    \n#line 7 \"test/src/convolution/convolution_large/convolution_large.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\n// from\
    \ https://judge.yosupo.jp/submission/21623\nnamespace nyaan {\n    namespace fastio\
    \ {\n        static constexpr uint32_t SZ = 1 << 17;\n        char ibuf[SZ];\n\
    \        char obuf[SZ];\n        uint32_t pil = 0, pir = 0, por = 0;\n\n     \
    \   struct Pre {\n            char num[40000];\n            constexpr Pre() :\
    \ num() {\n                for (int i = 0; i < 10000; i++) {\n               \
    \     int n = i;\n                    for (int j = 3; j >= 0; j--) {\n       \
    \                 num[i * 4 + j] = n % 10 + '0';\n                        n /=\
    \ 10;\n                    }\n                }\n            }\n        } constexpr\
    \ pre;\n\n        __attribute__((target(\"avx2\"), optimize(\"O3\"))) inline void\
    \ load() {\n            memcpy(ibuf, ibuf + pil, pir - pil);\n            pir\
    \ = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);\n         \
    \   pil = 0;\n        }\n\n        __attribute__((target(\"avx2\"), optimize(\"\
    O3\"))) inline void flush() {\n            fwrite(obuf, 1, por, stdout);\n   \
    \         por = 0;\n        }\n\n        inline void rd(char& c) { c = ibuf[pil++];\
    \ }\n\n        template <typename T>\n        __attribute__((target(\"avx2\"),\
    \ optimize(\"O3\"))) inline void rd(T& x) {\n            if (pil + 32 > pir) load();\n\
    \            char c;\n            do\n                rd(c);\n            while\
    \ (c < '-');\n            bool minus = 0;\n            if constexpr (std::is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    minus = 1;\n       \
    \             rd(c);\n                }\n            }\n            x = 0;\n \
    \           while (c >= '0') {\n                x = x * 10 + (c & 15);\n     \
    \           rd(c);\n            }\n            if constexpr (std::is_signed<T>::value)\
    \ {\n                if (minus) x = -x;\n            }\n        }\n\n        inline\
    \ void wt(char c) { obuf[por++] = c; }\n        template <typename T>\n      \
    \  __attribute__((target(\"avx2\"), optimize(\"O3\"))) inline void wt(T x) {\n\
    \            if (por + 32 > SZ) flush();\n            if (!x) {\n            \
    \    wt('0');\n                return;\n            }\n            if constexpr\
    \ (std::is_signed<T>::value) {\n                if (x < 0) {\n               \
    \     wt('-');\n                    x = -x;\n                }\n            }\n\
    \            if (x >= 10000000000000000) {\n                uint32_t r1 = x %\
    \ 100000000;\n                uint64_t q1 = x / 100000000;\n                uint32_t\
    \ r2 = q1 % 100000000;\n                uint32_t q2 = q1 / 100000000;\n      \
    \          uint32_t n1 = r1 % 10000;\n                uint32_t n2 = r1 / 10000;\n\
    \                uint32_t n3 = r2 % 10000;\n                uint32_t n4 = r2 /\
    \ 10000;\n                if (x >= 1000000000000000000) {\n                  \
    \  memcpy(obuf + por, pre.num + (q2 << 2) + 1, 3);\n                    memcpy(obuf\
    \ + por + 3, pre.num + (n4 << 2), 4);\n                    memcpy(obuf + por +\
    \ 7, pre.num + (n3 << 2), 4);\n                    memcpy(obuf + por + 11, pre.num\
    \ + (n2 << 2), 4);\n                    memcpy(obuf + por + 15, pre.num + (n1\
    \ << 2), 4);\n                    por += 19;\n                } else if (x >=\
    \ 100000000000000000) {\n                    uint32_t q3 = (q2 * 205) >> 11;\n\
    \                    uint32_t r3 = q2 - q3 * 10;\n                    obuf[por\
    \ + 0] = '0' + q3;\n                    obuf[por + 1] = '0' + r3;\n          \
    \          memcpy(obuf + por + 2, pre.num + (n4 << 2), 4);\n                 \
    \   memcpy(obuf + por + 6, pre.num + (n3 << 2), 4);\n                    memcpy(obuf\
    \ + por + 10, pre.num + (n2 << 2), 4);\n                    memcpy(obuf + por\
    \ + 14, pre.num + (n1 << 2), 4);\n                    por += 18;\n           \
    \     } else {\n                    obuf[por + 0] = '0' + q2;\n              \
    \      memcpy(obuf + por + 1, pre.num + (n4 << 2), 4);\n                    memcpy(obuf\
    \ + por + 5, pre.num + (n3 << 2), 4);\n                    memcpy(obuf + por +\
    \ 9, pre.num + (n2 << 2), 4);\n                    memcpy(obuf + por + 13, pre.num\
    \ + (n1 << 2), 4);\n                    por += 17;\n                }\n      \
    \      } else {\n                int i = 8;\n                char buf[12];\n \
    \               while (x >= 10000) {\n                    memcpy(buf + i, pre.num\
    \ + (x % 10000) * 4, 4);\n                    x /= 10000;\n                  \
    \  i -= 4;\n                }\n                if (x < 100) {\n              \
    \      if (x < 10) {\n                        wt(char('0' + x));\n           \
    \         } else {\n                        obuf[por + 0] = '0' + x / 10;\n  \
    \                      obuf[por + 1] = '0' + x % 10;\n                       \
    \ por += 2;\n                    }\n                } else {\n               \
    \     if (x < 1000) {\n                        memcpy(obuf + por, pre.num + (x\
    \ << 2) + 1, 3);\n                        por += 3;\n                    } else\
    \ {\n                        memcpy(obuf + por, pre.num + (x << 2), 4);\n    \
    \                    por += 4;\n                    }\n                }\n   \
    \             memcpy(obuf + por, buf + i + 4, 8 - i);\n                por +=\
    \ 8 - i;\n            }\n        }\n\n        struct Dummy {\n            Dummy()\
    \ { atexit(flush); }\n        } dummy;\n    }  // namespace fastio\n}\n\nint main()\
    \ {\n    std::size_t n, m;\n    nyaan::fastio::rd(n);\n    nyaan::fastio::rd(m);\n\
    \n    std::vector<mint> a(n), b(m);\n    for (auto& e : a) {\n        int v;\n\
    \        nyaan::fastio::rd(v);\n        e = v;\n    }\n    for (auto& e : b) {\n\
    \        int v;\n        nyaan::fastio::rd(v);\n        e = v;\n    }\n\n    std::vector<mint>\
    \ c = suisen::convolution_large(a, b);\n    for (std::size_t i = 0; i < n + m\
    \ - 1; ++i) {\n        nyaan::fastio::wt(c[i].val());\n        nyaan::fastio::wt('\\\
    n');\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_large\"\
    \n\n#include <iostream>\n#include <cstring>\n\n#include \"library/convolution/convolution_large.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint& a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\n// from\
    \ https://judge.yosupo.jp/submission/21623\nnamespace nyaan {\n    namespace fastio\
    \ {\n        static constexpr uint32_t SZ = 1 << 17;\n        char ibuf[SZ];\n\
    \        char obuf[SZ];\n        uint32_t pil = 0, pir = 0, por = 0;\n\n     \
    \   struct Pre {\n            char num[40000];\n            constexpr Pre() :\
    \ num() {\n                for (int i = 0; i < 10000; i++) {\n               \
    \     int n = i;\n                    for (int j = 3; j >= 0; j--) {\n       \
    \                 num[i * 4 + j] = n % 10 + '0';\n                        n /=\
    \ 10;\n                    }\n                }\n            }\n        } constexpr\
    \ pre;\n\n        __attribute__((target(\"avx2\"), optimize(\"O3\"))) inline void\
    \ load() {\n            memcpy(ibuf, ibuf + pil, pir - pil);\n            pir\
    \ = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);\n         \
    \   pil = 0;\n        }\n\n        __attribute__((target(\"avx2\"), optimize(\"\
    O3\"))) inline void flush() {\n            fwrite(obuf, 1, por, stdout);\n   \
    \         por = 0;\n        }\n\n        inline void rd(char& c) { c = ibuf[pil++];\
    \ }\n\n        template <typename T>\n        __attribute__((target(\"avx2\"),\
    \ optimize(\"O3\"))) inline void rd(T& x) {\n            if (pil + 32 > pir) load();\n\
    \            char c;\n            do\n                rd(c);\n            while\
    \ (c < '-');\n            bool minus = 0;\n            if constexpr (std::is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    minus = 1;\n       \
    \             rd(c);\n                }\n            }\n            x = 0;\n \
    \           while (c >= '0') {\n                x = x * 10 + (c & 15);\n     \
    \           rd(c);\n            }\n            if constexpr (std::is_signed<T>::value)\
    \ {\n                if (minus) x = -x;\n            }\n        }\n\n        inline\
    \ void wt(char c) { obuf[por++] = c; }\n        template <typename T>\n      \
    \  __attribute__((target(\"avx2\"), optimize(\"O3\"))) inline void wt(T x) {\n\
    \            if (por + 32 > SZ) flush();\n            if (!x) {\n            \
    \    wt('0');\n                return;\n            }\n            if constexpr\
    \ (std::is_signed<T>::value) {\n                if (x < 0) {\n               \
    \     wt('-');\n                    x = -x;\n                }\n            }\n\
    \            if (x >= 10000000000000000) {\n                uint32_t r1 = x %\
    \ 100000000;\n                uint64_t q1 = x / 100000000;\n                uint32_t\
    \ r2 = q1 % 100000000;\n                uint32_t q2 = q1 / 100000000;\n      \
    \          uint32_t n1 = r1 % 10000;\n                uint32_t n2 = r1 / 10000;\n\
    \                uint32_t n3 = r2 % 10000;\n                uint32_t n4 = r2 /\
    \ 10000;\n                if (x >= 1000000000000000000) {\n                  \
    \  memcpy(obuf + por, pre.num + (q2 << 2) + 1, 3);\n                    memcpy(obuf\
    \ + por + 3, pre.num + (n4 << 2), 4);\n                    memcpy(obuf + por +\
    \ 7, pre.num + (n3 << 2), 4);\n                    memcpy(obuf + por + 11, pre.num\
    \ + (n2 << 2), 4);\n                    memcpy(obuf + por + 15, pre.num + (n1\
    \ << 2), 4);\n                    por += 19;\n                } else if (x >=\
    \ 100000000000000000) {\n                    uint32_t q3 = (q2 * 205) >> 11;\n\
    \                    uint32_t r3 = q2 - q3 * 10;\n                    obuf[por\
    \ + 0] = '0' + q3;\n                    obuf[por + 1] = '0' + r3;\n          \
    \          memcpy(obuf + por + 2, pre.num + (n4 << 2), 4);\n                 \
    \   memcpy(obuf + por + 6, pre.num + (n3 << 2), 4);\n                    memcpy(obuf\
    \ + por + 10, pre.num + (n2 << 2), 4);\n                    memcpy(obuf + por\
    \ + 14, pre.num + (n1 << 2), 4);\n                    por += 18;\n           \
    \     } else {\n                    obuf[por + 0] = '0' + q2;\n              \
    \      memcpy(obuf + por + 1, pre.num + (n4 << 2), 4);\n                    memcpy(obuf\
    \ + por + 5, pre.num + (n3 << 2), 4);\n                    memcpy(obuf + por +\
    \ 9, pre.num + (n2 << 2), 4);\n                    memcpy(obuf + por + 13, pre.num\
    \ + (n1 << 2), 4);\n                    por += 17;\n                }\n      \
    \      } else {\n                int i = 8;\n                char buf[12];\n \
    \               while (x >= 10000) {\n                    memcpy(buf + i, pre.num\
    \ + (x % 10000) * 4, 4);\n                    x /= 10000;\n                  \
    \  i -= 4;\n                }\n                if (x < 100) {\n              \
    \      if (x < 10) {\n                        wt(char('0' + x));\n           \
    \         } else {\n                        obuf[por + 0] = '0' + x / 10;\n  \
    \                      obuf[por + 1] = '0' + x % 10;\n                       \
    \ por += 2;\n                    }\n                } else {\n               \
    \     if (x < 1000) {\n                        memcpy(obuf + por, pre.num + (x\
    \ << 2) + 1, 3);\n                        por += 3;\n                    } else\
    \ {\n                        memcpy(obuf + por, pre.num + (x << 2), 4);\n    \
    \                    por += 4;\n                    }\n                }\n   \
    \             memcpy(obuf + por, buf + i + 4, 8 - i);\n                por +=\
    \ 8 - i;\n            }\n        }\n\n        struct Dummy {\n            Dummy()\
    \ { atexit(flush); }\n        } dummy;\n    }  // namespace fastio\n}\n\nint main()\
    \ {\n    std::size_t n, m;\n    nyaan::fastio::rd(n);\n    nyaan::fastio::rd(m);\n\
    \n    std::vector<mint> a(n), b(m);\n    for (auto& e : a) {\n        int v;\n\
    \        nyaan::fastio::rd(v);\n        e = v;\n    }\n    for (auto& e : b) {\n\
    \        int v;\n        nyaan::fastio::rd(v);\n        e = v;\n    }\n\n    std::vector<mint>\
    \ c = suisen::convolution_large(a, b);\n    for (std::size_t i = 0; i < n + m\
    \ - 1; ++i) {\n        nyaan::fastio::wt(c[i].val());\n        nyaan::fastio::wt('\\\
    n');\n    }\n    return 0;\n}"
  dependsOn:
  - library/convolution/convolution_large.hpp
  isVerificationFile: true
  path: test/src/convolution/convolution_large/convolution_large.test.cpp
  requiredBy: []
  timestamp: '2022-04-30 04:33:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/convolution_large/convolution_large.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/convolution_large/convolution_large.test.cpp
- /verify/test/src/convolution/convolution_large/convolution_large.test.cpp.html
title: test/src/convolution/convolution_large/convolution_large.test.cpp
---
