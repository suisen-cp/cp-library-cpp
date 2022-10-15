---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/deterministic_miller_rabin.hpp
    title: Deterministic Miller Rabin
  - icon: ':heavy_check_mark:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':heavy_check_mark:'
    path: library/number/order_prime_mod.hpp
    title: Order Prime Mod
  - icon: ':heavy_check_mark:'
    path: library/number/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/number/primitive_root/dummy.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\n#line 1 \"library/number/primitive_root.hpp\"\
    \n\n\n\n#line 1 \"library/number/order_prime_mod.hpp\"\n\n\n\n#include <tuple>\n\
    \n#line 1 \"library/number/fast_factorize.hpp\"\n\n\n\n#include <cmath>\n#line\
    \ 6 \"library/number/fast_factorize.hpp\"\n#include <random>\n#include <numeric>\n\
    \n#line 1 \"library/number/deterministic_miller_rabin.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iterator>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 9 \"library/number/deterministic_miller_rabin.hpp\"\
    \n\nnamespace suisen::miller_rabin {\n    namespace internal {\n        constexpr\
    \ uint32_t THRESHOLD_1 = 341531U;\n        constexpr uint64_t BASE_1[] { 9345883071009581737ULL\
    \ };\n\n        constexpr uint32_t THRESHOLD_2 = 1050535501U;\n        constexpr\
    \ uint64_t BASE_2[] { 336781006125ULL, 9639812373923155ULL };\n\n        constexpr\
    \ uint64_t THRESHOLD_3 = 350269456337ULL;\n        constexpr uint64_t BASE_3[]\
    \ { 4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL };\n\
    \n        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;\n        constexpr\
    \ uint64_t BASE_4[] { 2ULL, 141889084524735ULL, 1199124725622454117ULL, 11096072698276303650ULL\
    \ };\n\n        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;\n      \
    \  constexpr uint64_t BASE_5[] { 2ULL, 4130806001517ULL, 149795463772692060ULL,\
    \ 186635894390467037ULL, 3967304179347715805ULL };\n\n        constexpr uint64_t\
    \ THRESHOLD_6 = 585226005592931977ULL;\n        constexpr uint64_t BASE_6[] {\
    \ 2ULL, 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL,\
    \ 1263739024124850375ULL };\n\n        constexpr uint32_t BASE_7[] { 2U, 325U,\
    \ 9375U, 28178U, 450775U, 9780504U, 1795265022U };\n\n        template <auto BASE,\
    \ std::size_t SIZE, typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        constexpr bool miller_rabin(T _n) {\n            using U\
    \ = std::make_unsigned_t<T>;\n            using M = safely_multipliable_t<U>;\n\
    \n            U n = _n, d = (n - 1) >> __builtin_ctzll(n - 1);\n\n           \
    \ if (n == 2 or n == 3 or n == 5 or n == 7) return true;\n            if (n %\
    \ 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;\n\n        \
    \    for (std::size_t i = 0; i < SIZE; ++i) {\n                M y = 1, p = BASE[i]\
    \ % n;\n                if (p == 0) continue;\n                for (U d2 = d;\
    \ d2; d2 >>= 1) {\n                    if (d2 & 1) y = y * p % n;\n          \
    \          p = p * p % n;\n                }\n                if (y == 1) continue;\n\
    \                for (U t = d; y != n - 1; t <<= 1) {\n                    y =\
    \ y * y % n;\n                    if (y == 1 or t == n - 1) return false;\n  \
    \              }\n            }\n            return true;\n        }\n    }\n\n\
    \    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    constexpr bool is_prime(T n) {\n        if (n <= 1) return false;\n\
    \        using U = std::make_unsigned_t<T>;\n        U n2 = n;\n        using\
    \ namespace internal;\n        if (n2 < THRESHOLD_1) {\n            return miller_rabin<BASE_1,\
    \ 1>(n2);\n        } else if (n2 < THRESHOLD_2) {\n            return miller_rabin<BASE_2,\
    \ 2>(n2);\n        } else if (n2 < THRESHOLD_3) {\n            return miller_rabin<BASE_3,\
    \ 3>(n2);\n        } else if (n2 < THRESHOLD_4) {\n            return miller_rabin<BASE_4,\
    \ 4>(n2);\n        } else if (n2 < THRESHOLD_5) {\n            return miller_rabin<BASE_5,\
    \ 5>(n2);\n        } else if (n2 < THRESHOLD_6) {\n            return miller_rabin<BASE_6,\
    \ 6>(n2);\n        } else {\n            return miller_rabin<BASE_7, 7>(n2);\n\
    \        }\n    }\n} // namespace suisen::miller_rabin\n\n\n#line 10 \"library/number/fast_factorize.hpp\"\
    \n\nnamespace suisen::fast_factorize {\n    namespace internal {\n        template\
    \ <typename T>\n        constexpr int floor_log2(T n) {\n            int i = 0;\n\
    \            while (n) n >>= 1, ++i;\n            return i - 1;\n        }\n \
    \       template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        T pollard_rho(T n) {\n            using M = safely_multipliable_t<T>;\n\
    \            const T m = T(1) << (floor_log2(n) / 5);\n\n            static std::mt19937_64\
    \ rng{std::random_device{}()};\n            std::uniform_int_distribution<T> dist(0,\
    \ n - 1);\n\n            while (true) {\n                T c = dist(rng);\n  \
    \              auto f = [&](T x) -> T { return (M(x) * x + c) % n; };\n      \
    \          T x, y = 2, ys, q = 1, g = 1;\n                for (T r = 1; g == 1;\
    \ r <<= 1) {\n                    x = y;\n                    for (T i = 0; i\
    \ < r; ++i) y = f(y);\n                    for (T k = 0; k < r and g == 1; k +=\
    \ m) {\n                        ys = y;\n                        for (T i = 0;\
    \ i < std::min(m, r - k); ++i) y = f(y), q = M(q) * (x > y ? x - y : y - x) %\
    \ n;\n                        g = std::gcd(q, n);\n                    }\n   \
    \             }\n                if (g == n) {\n                    g = 1;\n \
    \                   while (g == 1) ys = f(ys), g = std::gcd(x > ys ? x - ys :\
    \ ys - x, n);\n                }\n                if (g < n) {\n             \
    \       if (miller_rabin::is_prime(g)) return g;\n                    if (T d\
    \ = n / g; miller_rabin::is_prime(d)) return d;\n                    return pollard_rho(g);\n\
    \                }\n            }\n        }\n    }\n\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    std::vector<std::pair<T,\
    \ int>> factorize(T n) {\n        std::vector<std::pair<T, int>> res;\n      \
    \  if ((n & 1) == 0) {\n            int q = 0;\n            do ++q, n >>= 1; while\
    \ ((n & 1) == 0);\n            res.emplace_back(2, q);\n        }\n        for\
    \ (T p = 3; p * p <= n; p += 2) {\n            if (p >= 101 and n >= 1 << 20)\
    \ {\n                while (n > 1) {\n                    if (miller_rabin::is_prime(n))\
    \ {\n                        res.emplace_back(std::exchange(n, 1), 1);\n     \
    \               } else {\n                        p = internal::pollard_rho(n);\n\
    \                        int q = 0;\n                        do ++q, n /= p; while\
    \ (n % p == 0);\n                        res.emplace_back(p, q);\n           \
    \         }\n                }\n                break;\n            }\n      \
    \      if (n % p == 0) {\n                int q = 0;\n                do ++q,\
    \ n /= p; while (n % p == 0);\n                res.emplace_back(p, q);\n     \
    \       }\n        }\n        if (n > 1) res.emplace_back(n, 1);\n        return\
    \ res;\n    }\n} // namespace suisen::fast_factorize\n\n\n#line 8 \"library/number/order_prime_mod.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::order_prime_mod {\n        template\
    \ <int id>\n        struct mint64 {\n            static uint64_t mod() { return\
    \ _mod; }\n            static void set_mod(uint64_t new_mod) { mint64<id>::_mod\
    \ = new_mod; }\n\n            mint64() : _val(0) {}\n            mint64(long long\
    \ val) : _val(safe_mod(val)) {}\n\n            uint64_t val() { return _val; }\n\
    \n            friend mint64& operator*=(mint64& x, const mint64& y) {\n      \
    \          x._val = __uint128_t(x._val) * y._val % _mod;\n                return\
    \ x;\n            }\n            friend mint64 operator*(mint64 x, const mint64&\
    \ y) {\n                x *= y;\n                return x;\n            }\n  \
    \          mint64 pow(long long b) const {\n                assert(b >= 0);\n\
    \                mint64 p = *this, res = 1;\n                for (; b; b >>= 1)\
    \ {\n                    if (b & 1) res *= p;\n                    p *= p;\n \
    \               }\n                return res;\n            }\n        private:\n\
    \            static inline uint64_t _mod;\n            uint64_t _val;\n\n    \
    \        static uint64_t safe_mod(long long val) { return (val %= _mod) < 0 ?\
    \ val + _mod : val; }\n        };\n    }\n\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    struct OrderFp {\n        using U = std::make_unsigned_t<T>;\n\
    \        OrderFp(T p) : _p(p) {\n            assert(_p >= 1 and miller_rabin::is_prime(_p));\n\
    \            for (auto [p, q] : fast_factorize::factorize(_p - 1)) {\n       \
    \         U r = 1;\n                for (int i = 0; i < q; ++i) r *= p;\n    \
    \            _factorized.emplace_back(p, q, r);\n            }\n        }\n\n\
    \        bool is_primitive_root(U a) const {\n            if (_p < 1ULL << 32)\
    \ {\n                using mint = atcoder::dynamic_modint<1000000000>;\n     \
    \           U old_mod = mint::mod();\n                mint::set_mod(_p);\n   \
    \             bool res = is_primitive_root_impl<mint>(a);\n                mint::set_mod(old_mod);\n\
    \                return res;\n            } else {\n                using mint\
    \ = internal::order_prime_mod::mint64<1000000000>;\n                U old_mod\
    \ = mint::mod();\n                mint::set_mod(_p);\n                bool res\
    \ = is_primitive_root_impl<mint>(a);\n                mint::set_mod(old_mod);\n\
    \                return res;\n            }\n        }\n\n        T primitive_root()\
    \ const {\n            if (_p < 1ULL << 32) {\n                return primitive_root_impl<std::mt19937>();\n\
    \            } else {\n                return primitive_root_impl<std::mt19937_64>();\n\
    \            }\n        }\n\n        T operator()(U a) const {\n            if\
    \ (_p < 1ULL << 32) {\n                using mint = atcoder::dynamic_modint<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_p);\n\
    \                T res = order_impl<mint>(a);\n                mint::set_mod(old_mod);\n\
    \                return res;\n            } else {\n                using mint\
    \ = internal::order_prime_mod::mint64<1000000000>;\n                U old_mod\
    \ = mint::mod();\n                mint::set_mod(_p);\n                T res =\
    \ order_impl<mint>(a);\n                mint::set_mod(old_mod);\n            \
    \    return res;\n            }\n        }\n\n        T mod() const {\n      \
    \      return _p;\n        }\n\n    private:\n        U _p;\n        std::vector<std::tuple<U,\
    \ int, U>> _factorized;\n\n        template <typename mint>\n        bool is_primitive_root_impl(U\
    \ a) const {\n            if (_p == 2) return a % 2 == 1;\n\n            const\
    \ int k = _factorized.size();\n            U x = _p - 1;\n            for (const\
    \ auto &[p, q, pq] : _factorized) x /= p;\n\n            mint b = mint(a).pow(x);\n\
    \            if (k == 1) return b.val() != 1;\n    \n            auto dfs = [&](auto\
    \ dfs, const int l, const int r, const mint val) -> bool {\n                const\
    \ int m = (l + r) >> 1;\n\n                U lp = 1;\n                for (int\
    \ i = m; i < r; ++i) lp *= std::get<0>(_factorized[i]);\n                mint\
    \ lval = val.pow(lp);\n                if (m - l == 1) {\n                   \
    \ if (lval.val() == 1) return false;\n                } else {\n             \
    \       if (not dfs(dfs, l, m, lval)) return false;\n                }\n\n   \
    \             U rp = 1;\n                for (int i = l; i < m; ++i) rp *= std::get<0>(_factorized[i]);\n\
    \                mint rval = val.pow(rp);\n                if (r - m == 1) {\n\
    \                    if (rval.val() == 1) return false;\n                } else\
    \ {\n                    if (not dfs(dfs, m, r, rval)) return false;\n       \
    \         }\n\n                return true;\n            };\n            return\
    \ dfs(dfs, 0, k, b);\n        }\n\n        template <typename Rng>\n        T\
    \ primitive_root_impl() const {\n            if (_p == 2) return 1;\n\n      \
    \      Rng rng{ std::random_device{}() };\n            while (true) {\n      \
    \          if (U a = rng() % (_p - 2) + 2; is_primitive_root(a)) {\n         \
    \           return a;\n                }\n            }\n        }\n\n       \
    \ template <typename mint>\n        U order_impl(U a) const {\n            if\
    \ (_p == 2) return a % 2 == 1;\n\n            const int k = _factorized.size();\n\
    \n            U res = 1;\n\n            auto update = [&](U p, mint val) {\n \
    \               while (val.val() != 1) {\n                    val = val.pow(p);\n\
    \                    res *= p;\n                }\n            };\n    \n    \
    \        if (k == 1) {\n                update(std::get<0>(_factorized.front()),\
    \ a);\n                return res;\n            }\n\n            auto dfs = [&](auto\
    \ dfs, const int l, const int r, const mint val) -> void {\n                const\
    \ int m = (l + r) >> 1;\n\n                U lp = 1;\n                for (int\
    \ i = m; i < r; ++i) lp *= std::get<2>(_factorized[i]);\n                mint\
    \ lval = val.pow(lp);\n                if (m - l == 1) {\n                   \
    \ update(std::get<0>(_factorized[l]), lval);\n                } else {\n     \
    \               dfs(dfs, l, m, lval);\n                }\n\n                U\
    \ rp = 1;\n                for (int i = l; i < m; ++i) rp *= std::get<2>(_factorized[i]);\n\
    \                mint rval = val.pow(rp);\n                if (r - m == 1) {\n\
    \                    update(std::get<0>(_factorized[m]), rval);\n            \
    \    } else {\n                    dfs(dfs, m, r, rval);\n                }\n\
    \            };\n            dfs(dfs, 0, k, a);\n\n            return res;\n \
    \       }\n    };\n} // namespace suisen\n\n\n#line 5 \"library/number/primitive_root.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T primitive_root(T p) {\n        return OrderFp<T>{p}.primitive_root();\n\
    \    }\n} // namespace suisen\n\n\n#line 1 \"library/number/sieve_of_eratosthenes.hpp\"\
    \n\n\n\n#line 6 \"library/number/sieve_of_eratosthenes.hpp\"\n#include <vector>\n\
    \n#line 1 \"library/number/internal_eratosthenes.hpp\"\n\n\n\n#line 6 \"library/number/internal_eratosthenes.hpp\"\
    \n\nnamespace suisen::internal::sieve {\n\nconstexpr std::uint8_t K = 8;\nconstexpr\
    \ std::uint8_t PROD = 2 * 3 * 5;\nconstexpr std::uint8_t RM[K] = { 1,  7, 11,\
    \ 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t DR[K] = { 6,  4,  2,  4,  2, \
    \ 4,  6,  2 };\nconstexpr std::uint8_t DF[K][K] = {\n    { 0, 0, 0, 0, 0, 0, 0,\
    \ 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2, 0, 2, 0, 2, 2, 1 }, { 3, 1, 1,\
    \ 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n\
    \    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t\
    \ DRP[K] = { 48, 32, 16, 32, 16, 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K]\
    \ = {\n    {  0,  0,  0,  0,  0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8, \
    \ 8 },\n    { 16, 16,  0, 16,  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,\
    \  8 },\n    { 24, 24,  8, 16,  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,\
    \  8 },\n    { 40, 24,  8, 32,  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,\
    \  8 },\n};\n\nconstexpr std::uint8_t MASK[K][K] = {\n    { 0x01, 0x02, 0x04,\
    \ 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01, 0x80, 0x08, 0x04,\
    \ 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20 }, { 0x08, 0x01,\
    \ 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40,\
    \ 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10, 0x04 },\n    { 0x40,\
    \ 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40, 0x20, 0x10, 0x08,\
    \ 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K] = {\n    { 0, 1,\
    \ 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3, 2, 6, },\n    { 2, 4, 0, 6, 1,\
    \ 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n    { 4, 7, 1, 2, 5, 6, 0, 3,\
    \ },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6, 2, 3, 7, 0, 4, 5, 1, },\n   \
    \ { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t mask_to_index(const\
    \ std::uint8_t bits) {\n    switch (bits) {\n        case 1 << 0: return 0;\n\
    \        case 1 << 1: return 1;\n        case 1 << 2: return 2;\n        case\
    \ 1 << 3: return 3;\n        case 1 << 4: return 4;\n        case 1 << 5: return\
    \ 5;\n        case 1 << 6: return 6;\n        case 1 << 7: return 7;\n       \
    \ default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\n\
    \n#line 9 \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
    \ntemplate <unsigned int N>\nclass SimpleSieve {\n    private:\n        static\
    \ constexpr unsigned int siz = N / internal::sieve::PROD + 1;\n        static\
    \ std::uint8_t flag[siz];\n    public:\n        SimpleSieve() {\n            using\
    \ namespace internal::sieve;\n            flag[0] |= 1;\n            unsigned\
    \ int k_max = (unsigned int) std::sqrt(N + 2) / PROD;\n            for (unsigned\
    \ int kp = 0; kp <= k_max; ++kp) {\n                for (std::uint8_t bits = ~flag[kp];\
    \ bits; bits &= bits - 1) {\n                    const std::uint8_t mp = mask_to_index(bits\
    \ & -bits), m = RM[mp];\n                    unsigned int kr = kp * (PROD * kp\
    \ + 2 * m) + m * m / PROD;\n                    for (std::uint8_t mq = mp; kr\
    \ < siz; kr += kp * DR[mq] + DF[mp][mq], ++mq &= 7) {\n                      \
    \  flag[kr] |= MASK[mp][mq];\n                    }\n                }\n     \
    \       }\n        }\n        std::vector<int> prime_list(unsigned int max_val\
    \ = N) const {\n            using namespace internal::sieve;\n            std::vector<int>\
    \ res { 2, 3, 5 };\n            res.reserve(max_val / 25);\n            for (unsigned\
    \ int i = 0, offset = 0; i < siz and offset < max_val; ++i, offset += PROD) {\n\
    \                for (uint8_t f = ~flag[i]; f;) {\n                    uint8_t\
    \ g = f & -f;\n                    res.push_back(offset + RM[mask_to_index(g)]);\n\
    \                    f ^= g;\n                }\n            }\n            while\
    \ (res.size() and (unsigned int) res.back() > max_val) res.pop_back();\n     \
    \       return res;\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]:\
    \ return ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]:\
    \ return ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]:\
    \ return ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]:\
    \ return ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]:\
    \ return ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]:\
    \ return ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]:\
    \ return ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return\
    \ false;\n                    }\n            }\n        }\n};\ntemplate <unsigned\
    \ int N>\nstd::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];\n\ntemplate\
    \ <unsigned int N>\nclass Sieve {\n    private:\n        static constexpr unsigned\
    \ int base_max = (N + 1) * internal::sieve::K / internal::sieve::PROD;\n     \
    \   static unsigned int pf[base_max + internal::sieve::K];\n\n    public:\n  \
    \      Sieve() {\n            using namespace internal::sieve;\n            pf[0]\
    \ = 1;\n            unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1)\
    \ / PROD;\n            for (unsigned int kp = 0; kp <= k_max; ++kp) {\n      \
    \          const int base_i = kp * K, base_act_i = kp * PROD;\n              \
    \  for (int mp = 0; mp < K; ++mp) {\n                    const int m = RM[mp],\
    \ i = base_i + mp;\n                    if (pf[i] == 0) {\n                  \
    \      unsigned int act_i = base_act_i + m;\n                        unsigned\
    \ int base_k = (kp * (PROD * kp + 2 * m) + m * m / PROD) * K;\n              \
    \          for (std::uint8_t mq = mp; base_k <= base_max; base_k += kp * DRP[mq]\
    \ + DFP[mp][mq], ++mq &= 7) {\n                            pf[base_k + OFFSET[mp][mq]]\
    \ = act_i;\n                        }\n                    }\n               \
    \ }\n            }\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return pf[p / PROD * K + 0] == 0;\n                        case RM[1]: return\
    \ pf[p / PROD * K + 1] == 0;\n                        case RM[2]: return pf[p\
    \ / PROD * K + 2] == 0;\n                        case RM[3]: return pf[p / PROD\
    \ * K + 3] == 0;\n                        case RM[4]: return pf[p / PROD * K +\
    \ 4] == 0;\n                        case RM[5]: return pf[p / PROD * K + 5] ==\
    \ 0;\n                        case RM[6]: return pf[p / PROD * K + 6] == 0;\n\
    \                        case RM[7]: return pf[p / PROD * K + 7] == 0;\n     \
    \                   default: return false;\n                    }\n          \
    \  }\n        }\n        int prime_factor(const unsigned int p) const {\n    \
    \        using namespace internal::sieve;\n            switch (p % PROD) {\n \
    \               case  0: case  2: case  4: case  6: case  8:\n               \
    \ case 10: case 12: case 14: case 16: case 18:\n                case 20: case\
    \ 22: case 24: case 26: case 28: return 2;\n                case  3: case  9:\
    \ case 15: case 21: case 27: return 3;\n                case  5: case 25: return\
    \ 5;\n                case RM[0]: return pf[p / PROD * K + 0] ? pf[p / PROD *\
    \ K + 0] : p;\n                case RM[1]: return pf[p / PROD * K + 1] ? pf[p\
    \ / PROD * K + 1] : p;\n                case RM[2]: return pf[p / PROD * K + 2]\
    \ ? pf[p / PROD * K + 2] : p;\n                case RM[3]: return pf[p / PROD\
    \ * K + 3] ? pf[p / PROD * K + 3] : p;\n                case RM[4]: return pf[p\
    \ / PROD * K + 4] ? pf[p / PROD * K + 4] : p;\n                case RM[5]: return\
    \ pf[p / PROD * K + 5] ? pf[p / PROD * K + 5] : p;\n                case RM[6]:\
    \ return pf[p / PROD * K + 6] ? pf[p / PROD * K + 6] : p;\n                case\
    \ RM[7]: return pf[p / PROD * K + 7] ? pf[p / PROD * K + 7] : p;\n           \
    \     default: assert(false);\n            }\n        }\n        /**\n       \
    \  * Returns a vector of `{ prime, index }`.\n         */\n        std::vector<std::pair<int,\
    \ int>> factorize(unsigned int n) const {\n            assert(0 < n and n <= N);\n\
    \            std::vector<std::pair<int, int>> prime_powers;\n            while\
    \ (n > 1) {\n                int p = prime_factor(n), c = 0;\n               \
    \ do { n /= p, ++c; } while (n % p == 0);\n                prime_powers.emplace_back(p,\
    \ c);\n            }\n            return prime_powers;\n        }\n        /**\n\
    \         * Returns the divisors of `n`.\n         * It is NOT guaranteed that\
    \ the returned vector is sorted.\n         */\n        std::vector<int> divisors(unsigned\
    \ int n) const {\n            assert(0 < n and n <= N);\n            std::vector<int>\
    \ divs { 1 };\n            for (auto [prime, index] : factorize(n)) {\n      \
    \          int sz = divs.size();\n                for (int i = 0; i < sz; ++i)\
    \ {\n                    int d = divs[i];\n                    for (int j = 0;\
    \ j < index; ++j) {\n                        divs.push_back(d *= prime);\n   \
    \                 }\n                }\n            }\n            return divs;\n\
    \        }\n};\ntemplate <unsigned int N>\nunsigned int Sieve<N>::pf[Sieve<N>::base_max\
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 9 \"test/src/number/primitive_root/dummy.test.cpp\"\
    \n\nusing mint = atcoder::modint;\n\nvoid test() {\n    suisen::Sieve<100000>\
    \ sieve;\n\n    for (int i = 2; i < 100000; ++i) if (sieve.is_prime(i)) {\n  \
    \      int g = suisen::primitive_root(i);\n\n        mint::set_mod(i);\n     \
    \   for (int d : sieve.divisors(i - 1)) if (d != i - 1) {\n            if (mint(g).pow(d).val()\
    \ == 1) {\n                std::cout << \"p = \" << i << \", g = \" << g << \"\
    , d = \" << d << std::endl;\n            }\n        }\n    }\n}\n\nint main()\
    \ {\n    test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\n#include \"library/number/primitive_root.hpp\"\
    \n#include \"library/number/sieve_of_eratosthenes.hpp\"\n\nusing mint = atcoder::modint;\n\
    \nvoid test() {\n    suisen::Sieve<100000> sieve;\n\n    for (int i = 2; i < 100000;\
    \ ++i) if (sieve.is_prime(i)) {\n        int g = suisen::primitive_root(i);\n\n\
    \        mint::set_mod(i);\n        for (int d : sieve.divisors(i - 1)) if (d\
    \ != i - 1) {\n            if (mint(g).pow(d).val() == 1) {\n                std::cout\
    \ << \"p = \" << i << \", g = \" << g << \", d = \" << d << std::endl;\n     \
    \       }\n        }\n    }\n}\n\nint main() {\n    test();\n    std::cout <<\
    \ \"Hello World\" << std::endl;\n    return 0;\n}\n"
  dependsOn:
  - library/number/primitive_root.hpp
  - library/number/order_prime_mod.hpp
  - library/number/fast_factorize.hpp
  - library/number/deterministic_miller_rabin.hpp
  - library/type_traits/type_traits.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  isVerificationFile: true
  path: test/src/number/primitive_root/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-10-15 19:12:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/primitive_root/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/primitive_root/dummy.test.cpp
- /verify/test/src/number/primitive_root/dummy.test.cpp.html
title: test/src/number/primitive_root/dummy.test.cpp
---
