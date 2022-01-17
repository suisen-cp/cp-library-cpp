---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/pow_mods.hpp
    title: Pow Mods
  - icon: ':heavy_check_mark:'
    path: library/string/rolling_hash.hpp
    title: Rolling Hash
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc141/tasks/abc141_e
    links:
    - https://atcoder.jp/contests/abc141/tasks/abc141_e
  bundledCode: "#line 1 \"test/src/string/rolling_hash/abc141_e.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc141/tasks/abc141_e\"\n\n#include <iostream>\n\
    #include <set>\n\n#line 1 \"library/string/rolling_hash.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cstdint>\n#include <string>\n#include <random>\n#include\
    \ <vector>\n\n#line 1 \"library/math/pow_mods.hpp\"\n\n\n\n#line 5 \"library/math/pow_mods.hpp\"\
    \n\nnamespace suisen {\n    template <int base_as_int, typename mint>\n    struct\
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
    \ int mod = mint::mod();\n    };\n}\n\n\n#line 11 \"library/string/rolling_hash.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::rolling_hash {\n        // reference:\
    \ https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n        struct Modint2305843009213693951\
    \ {\n            using self = Modint2305843009213693951;\n\n            Modint2305843009213693951()\
    \ {}\n            Modint2305843009213693951(uint64_t v) : v(fast_mod(v)) {}\n\n\
    \            static constexpr uint64_t mod() {\n                return _mod;\n\
    \            }\n\n            static constexpr uint64_t fast_mod(uint64_t v) {\n\
    \                constexpr uint32_t mid = 61;\n                constexpr uint64_t\
    \ mask = (uint64_t(1) << mid) - 1;\n                uint64_t u = v >> mid;\n \
    \               uint64_t d = v & mask;\n                uint64_t res = u + d;\n\
    \                if (res >= _mod) res -= _mod;\n                return res;\n\
    \            }\n\n            uint64_t val() const {\n                return v;\n\
    \            }\n\n            self& operator+=(const self &rhs) {\n          \
    \      v += rhs.v;\n                if (v >= _mod) v -= _mod;\n              \
    \  return *this;\n            }\n            self& operator-=(const self &rhs)\
    \ {\n                if (v < rhs.v) v += _mod;\n                v -= rhs.v;\n\
    \                return *this;\n            }\n            self& operator*=(const\
    \ self &rhs) {\n                static constexpr uint32_t mid31 = 31;\n      \
    \          static constexpr uint64_t mask31 = (uint64_t(1) << mid31) - 1;\n\n\
    \                uint64_t au = v >> mid31;     // < 2^30\n                uint64_t\
    \ ad = v & mask31;     // < 2^31\n                uint64_t bu = rhs.v >> mid31;\
    \ // < 2^30\n                uint64_t bd = rhs.v & mask31; // < 2^31\n       \
    \         \n                //   a * b\n                // = (au * 2^31 + ad)\
    \ * (bu * 2^31 + bd)\n                // = au * bu * 2^62             # au * bu\
    \ * 2^62 \u2261 au * bu * 2 < 2^61\n                // + (au * bd + ad * bu) *\
    \ 2^31 # m := au * bd + ad * bu\n                //                          \
    \    # m <= 2 * (2^31 - 1) * (2^30 - 1) = 2^62 - 6 * 2^30 + 2\n              \
    \  //                              # m = mu * 2^30 + md (0 <= mu < 2^32, 0 <=\
    \ md < 2^30)\n                //                              # m * 2^31 \u2261\
    \ mu + md * 2^31 < 2^61 + 2^31\n                // + ad * bd                 \
    \   # ad * bd <= (2^31 - 1) ** 2 = 2^62 - 2^32 + 1 < 2^62 - 2^31\n           \
    \     // \u2261 au * bu * 2 + mu + md * 2^31 + ad * bd < 2^63\n\n            \
    \    static constexpr uint32_t mid30 = 30;\n                static constexpr uint64_t\
    \ mask30 = (uint64_t(1) << mid30) - 1;\n\n                uint64_t m = au * bd\
    \ + ad * bu;\n                uint64_t mu = m >> mid30;\n                uint64_t\
    \ md = m & mask30;\n\n                v = fast_mod((au * bu << 1) + mu + (md <<\
    \ 31) + ad * bd);\n                return *this;\n            }\n\n          \
    \  friend self operator+(const self &l, const self &r) { return self(l) += r;\
    \ }\n            friend self operator-(const self &l, const self &r) { return\
    \ self(l) -= r; }\n            friend self operator*(const self &l, const self\
    \ &r) { return self(l) *= r; }\n            friend bool operator==(const self\
    \ &l, const self &r) { return l.v == r.v; }\n        private:\n            static\
    \ constexpr uint64_t _mod = (uint64_t(1) << 61) - 1; // 2305843009213693951UL\
    \ : prime\n            uint64_t v;\n        };\n\n        template <int base_num,\
    \ typename mint>\n        std::array<mint, base_num> gen_bases() {\n         \
    \   static std::mt19937_64 rng(std::random_device{}());\n            std::array<mint,\
    \ base_num> res;\n            for (int i = 0; i < base_num; ++i) {\n         \
    \       res[i] = rng();\n                while (res[i].val() < 128) res[i] = rng();\n\
    \            }\n            return res;\n        }\n        template <int base_num,\
    \ typename mint>\n        std::array<pow_mods<mint>, base_num> init_pows(const\
    \ std::array<mint, base_num>& bases) {\n            std::array<pow_mods<mint>,\
    \ base_num> res;\n            for (int i = 0; i < base_num; ++i) {\n         \
    \       res[i] = pow_mods<mint>(bases[i], 0);\n            }\n            return\
    \ res;\n        }\n    }\n\n    template <int base_num = 1, typename mint = internal::rolling_hash::Modint2305843009213693951>\n\
    \    struct RollingHash {\n    private:\n        using default_mint = internal::rolling_hash::Modint2305843009213693951;\n\
    \    public:\n        using modint_type = mint;\n        using hash_type = decltype(mint::mod());\n\
    \n        RollingHash() {}\n        RollingHash(const std::vector<int> &a) : n(a.size())\
    \ {\n            for (int base_id = 0; base_id < base_num; ++base_id) {\n    \
    \            hash[base_id].resize(n + 1);\n                hash[base_id][0] =\
    \ 0;\n                for (int i = 0; i < n; ++i) hash[base_id][i + 1] = hash[base_id][i]\
    \ * bases[base_id] + a[i];\n            }\n        }\n\n        auto operator()(int\
    \ l, int r) {\n            std::array<mint, base_num> res;\n            for (int\
    \ base_id = 0; base_id < base_num; ++base_id) res[base_id] = hash[base_id][r]\
    \ - hash[base_id][l] * pows[base_id][r - l];\n            return res;\n      \
    \  }\n\n        static auto mod() {\n            return mint::mod();\n       \
    \ }\n\n        static void set_bases(const std::array<mint, base_num> &new_bases)\
    \ {\n            bases = new_bases;\n            pows = internal::rolling_hash::init_pows<base_num,\
    \ mint>(bases);\n        }\n\n        template <typename Iterable, typename ToIntFunction>\n\
    \        static RollingHash from(const Iterable &s, ToIntFunction f) {\n     \
    \       std::vector<int> a;\n            for (auto &&e : s) a.push_back(f(e));\n\
    \            return RollingHash(a);\n        }\n        static RollingHash from_lowercase_alphabet(const\
    \ std::string &s) {\n            return from(s, [](const auto &e) { return e -\
    \ 'a' + 1; });\n        }\n        static RollingHash from_uppercase_alphabet(const\
    \ std::string &s) {\n            return from(s, [](const auto &e) { return e -\
    \ 'A' + 1; });\n        }\n        static RollingHash from_alphabet(const std::string\
    \ &s) {\n            return from(s, [](const auto &e) { return std::islower(e)\
    \ ? e - 'a' + 27 : e - 'A' + 1; });\n        }\n        static RollingHash from_digit(const\
    \ std::string &s) {\n            return from(s, [](const auto &e) { return e -\
    \ '0' + 1; });\n        }\n\n    private:\n        static inline std::array<mint,\
    \ base_num> bases = internal::rolling_hash::gen_bases<base_num, mint>();\n   \
    \     static inline std::array<pow_mods<mint>, base_num> pows = internal::rolling_hash::init_pows<base_num,\
    \ mint>(bases);\n\n        int n;\n        std::array<std::vector<mint>, base_num>\
    \ hash;\n    };\n} // namespace suisen\n\n\n#line 7 \"test/src/string/rolling_hash/abc141_e.test.cpp\"\
    \nusing suisen::RollingHash;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::string s;\n    std::cin >>\
    \ n >> s;\n\n    auto rh = RollingHash<>::from_lowercase_alphabet(s);\n\n    auto\
    \ f = [&](int l) -> bool {\n        std::vector<RollingHash<>::hash_type> hashes(n);\n\
    \        std::set<RollingHash<>::hash_type> s;\n        for (int i = 0; i + l\
    \ <= n; ++i) {\n            if (i >= l) s.insert(hashes[i - l]);\n           \
    \ auto h = rh(i, i + l)[0].val();\n            hashes[i] = h;\n            if\
    \ (s.count(h)) return true;\n        }\n        return false;\n    };\n\n    int\
    \ ok = 0, ng = n + 1;\n    while (ng - ok > 1) {\n        int l = (ok + ng) /\
    \ 2;\n        if (f(l)) {\n            ok = l;\n        } else {\n           \
    \ ng = l;\n        }\n    }\n    std::cout << ok << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc141/tasks/abc141_e\"\n\n\
    #include <iostream>\n#include <set>\n\n#include \"library/string/rolling_hash.hpp\"\
    \nusing suisen::RollingHash;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::string s;\n    std::cin >>\
    \ n >> s;\n\n    auto rh = RollingHash<>::from_lowercase_alphabet(s);\n\n    auto\
    \ f = [&](int l) -> bool {\n        std::vector<RollingHash<>::hash_type> hashes(n);\n\
    \        std::set<RollingHash<>::hash_type> s;\n        for (int i = 0; i + l\
    \ <= n; ++i) {\n            if (i >= l) s.insert(hashes[i - l]);\n           \
    \ auto h = rh(i, i + l)[0].val();\n            hashes[i] = h;\n            if\
    \ (s.count(h)) return true;\n        }\n        return false;\n    };\n\n    int\
    \ ok = 0, ng = n + 1;\n    while (ng - ok > 1) {\n        int l = (ok + ng) /\
    \ 2;\n        if (f(l)) {\n            ok = l;\n        } else {\n           \
    \ ng = l;\n        }\n    }\n    std::cout << ok << std::endl;\n    return 0;\n\
    }"
  dependsOn:
  - library/string/rolling_hash.hpp
  - library/math/pow_mods.hpp
  isVerificationFile: true
  path: test/src/string/rolling_hash/abc141_e.test.cpp
  requiredBy: []
  timestamp: '2021-11-28 20:19:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/string/rolling_hash/abc141_e.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/rolling_hash/abc141_e.test.cpp
- /verify/test/src/string/rolling_hash/abc141_e.test.cpp.html
title: test/src/string/rolling_hash/abc141_e.test.cpp
---
