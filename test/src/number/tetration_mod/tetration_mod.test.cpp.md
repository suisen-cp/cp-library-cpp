---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/number/deterministic_miller_rabin.hpp
    title: Deterministic Miller Rabin
  - icon: ':question:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':question:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':question:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/number/tetration_mod.hpp
    title: $a\uparrow\uparrow b \bmod m$
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tetration_mod
    links:
    - https://judge.yosupo.jp/problem/tetration_mod
  bundledCode: "#line 1 \"test/src/number/tetration_mod/tetration_mod.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/tetration_mod\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/number/tetration_mod.hpp\"\n\n\n\n#include <numeric>\n\
    #include <optional>\n\n#line 1 \"library/number/fast_factorize.hpp\"\n\n\n\n#include\
    \ <cmath>\n#line 6 \"library/number/fast_factorize.hpp\"\n#include <random>\n\
    #line 8 \"library/number/fast_factorize.hpp\"\n#include <utility>\n\n#line 1 \"\
    library/number/deterministic_miller_rabin.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iterator>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    \        }\n    }\n} // namespace suisen::miller_rabin\n\n\n#line 1 \"library/number/sieve_of_eratosthenes.hpp\"\
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
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 12 \"library/number/fast_factorize.hpp\"\
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
    \ int>> factorize(T n) {\n        static constexpr int threshold = 1000000;\n\
    \        static Sieve<threshold> sieve;\n\n        std::vector<std::pair<T, int>>\
    \ res;\n        if (n <= threshold) {\n            for (auto [p, q] : sieve.factorize(n))\
    \ res.emplace_back(p, q);\n            return res;\n        }\n\n        if ((n\
    \ & 1) == 0) {\n            int q = 0;\n            do ++q, n >>= 1; while ((n\
    \ & 1) == 0);\n            res.emplace_back(2, q);\n        }\n        for (T\
    \ p = 3; p * p <= n; p += 2) {\n            if (p >= 101 and n >= 1 << 20) {\n\
    \                while (n > 1) {\n                    if (miller_rabin::is_prime(n))\
    \ {\n                        res.emplace_back(std::exchange(n, 1), 1);\n     \
    \               } else {\n                        p = internal::pollard_rho(n);\n\
    \                        int q = 0;\n                        do ++q, n /= p; while\
    \ (n % p == 0);\n                        res.emplace_back(p, q);\n           \
    \         }\n                }\n                break;\n            }\n      \
    \      if (n % p == 0) {\n                int q = 0;\n                do ++q,\
    \ n /= p; while (n % p == 0);\n                res.emplace_back(p, q);\n     \
    \       }\n        }\n        if (n > 1) res.emplace_back(n, 1);\n        return\
    \ res;\n    }\n} // namespace suisen::fast_factorize\n\n\n#line 9 \"library/number/tetration_mod.hpp\"\
    \n\n/**\n * @brief $a \\uparrow \\uparrow b \\pmod{m}$\n*/\n\nnamespace suisen\
    \ {\n    namespace internal::tetration_mod {\n        constexpr int max_value\
    \ = std::numeric_limits<int>::max();\n        int saturation_pow(int a, int b)\
    \ {\n            if (b >= 32) return max_value;\n            long long res = 1,\
    \ pow_a = a;\n            for (; b; b >>= 1) {\n                if (b & 1) res\
    \ = std::min(res * pow_a, (long long) max_value);\n                pow_a = std::min(pow_a\
    \ * pow_a, (long long) max_value);\n            }\n            return res;\n \
    \       }\n        int saturation_tetration(int a, int b) {\n            assert(a\
    \ >= 2);\n            if (b == 0) return 1;\n            int exponent = 1;\n \
    \           for (int i = 0; i < b and exponent != max_value; ++i) exponent = saturation_pow(a,\
    \ exponent);\n            return exponent;\n        }\n        int pow_mod(int\
    \ a, int b, int m) {\n            long long res = 1, pow_a = a;\n            for\
    \ (; b; b >>= 1) {\n                if (b & 1) res = (res * pow_a) % m;\n    \
    \            pow_a = (pow_a * pow_a) % m;\n            }\n            return res;\n\
    \        }\n    }\n\n    /**\n     * @brief Calculates a\u2191\u2191b mod m (=\
    \ a^(a^(a^...(b times)...)) mod m)\n     * @param a base\n     * @param b number\
    \ of power operations\n     * @param m mod\n     * @return a\u2191\u2191b mod\
    \ m\n     */\n    int tetration_mod(int a, int b, int m) {\n        using namespace\
    \ internal::tetration_mod;\n        if (m == 1) return 0;\n        if (a == 0)\
    \ return 1 ^ (b & 1);\n        if (a == 1 or b == 0) return 1;\n        int i0\
    \ = 0, m0 = m;\n        for (int g = std::gcd(m0, a); g != 1; g = std::gcd(m0,\
    \ g)) {\n            m0 /= g, ++i0;\n        }\n        int phi = m0;\n      \
    \  for (auto [p, q] : fast_factorize::factorize(m0)) {\n            phi /= p,\
    \ phi *= p - 1;\n        }\n        int exponent = saturation_tetration(a, b -\
    \ 1);\n        if (exponent == max_value) {\n            exponent = tetration_mod(a,\
    \ b - 1, phi);\n            if (i0 > exponent) {\n                exponent +=\
    \ (((i0 - exponent) + phi - 1) / phi) * phi;\n            }\n        } else if\
    \ (i0 <= exponent) {\n            exponent -= ((exponent - i0) / phi) * phi;\n\
    \        }\n        return pow_mod(a, exponent, m);\n    }\n}\n\n\n#line 6 \"\
    test/src/number/tetration_mod/tetration_mod.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t;\n    std::cin >> t;\n\n    for (int\
    \ i = 0; i < t; ++i) {\n        int a, b, m;\n        std::cin >> a >> b >> m;\n\
    \        std::cout << suisen::tetration_mod(a, b, m) << '\\n';\n    }\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tetration_mod\"\n\n#include\
    \ <iostream>\n\n#include \"library/number/tetration_mod.hpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ t;\n    std::cin >> t;\n\n    for (int i = 0; i < t; ++i) {\n        int a,\
    \ b, m;\n        std::cin >> a >> b >> m;\n        std::cout << suisen::tetration_mod(a,\
    \ b, m) << '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/number/tetration_mod.hpp
  - library/number/fast_factorize.hpp
  - library/number/deterministic_miller_rabin.hpp
  - library/type_traits/type_traits.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  isVerificationFile: true
  path: test/src/number/tetration_mod/tetration_mod.test.cpp
  requiredBy: []
  timestamp: '2022-10-17 22:14:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/tetration_mod/tetration_mod.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/tetration_mod/tetration_mod.test.cpp
- /verify/test/src/number/tetration_mod/tetration_mod.test.cpp.html
title: test/src/number/tetration_mod/tetration_mod.test.cpp
---
