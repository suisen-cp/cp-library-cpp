---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/deterministic_miller_rabin.hpp
    title: Deterministic Miller Rabin
  - icon: ':heavy_check_mark:'
    path: library/number/discrete_logarithm.hpp
    title: Discrete Logarithm
  - icon: ':heavy_check_mark:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':heavy_check_mark:'
    path: library/number/montogomery.hpp
    title: Montogomery
  - icon: ':heavy_check_mark:'
    path: library/number/order_Z_mZ.hpp
    title: Order of $x \in (\mathbb{Z}/m\mathbb{Z}) ^ \ast$
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/fast_discrete_logarithm.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n#include\
    \ <optional>\n#include <map>\n\n#include <atcoder/modint>\n#include <atcoder/math>\n\
    \n#line 1 \"library/number/fast_factorize.hpp\"\n\n\n\n#line 5 \"library/number/fast_factorize.hpp\"\
    \n#include <iostream>\n#include <random>\n#include <numeric>\n#include <utility>\n\
    \n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\n\
    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\n\
    template <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto)\
    \ constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n\
    \        return std::forward<Then>(then);\n    } else {\n        return std::forward<OrElse>(or_else);\n\
    \    }\n}\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
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
    } // namespace suisen\n\n\n#line 11 \"library/number/fast_factorize.hpp\"\n\n\
    #line 1 \"library/number/deterministic_miller_rabin.hpp\"\n\n\n\n#line 6 \"library/number/deterministic_miller_rabin.hpp\"\
    \n#include <cstdint>\n#include <iterator>\n#include <tuple>\n#line 10 \"library/number/deterministic_miller_rabin.hpp\"\
    \n\n#line 1 \"library/number/montogomery.hpp\"\n\n\n\n#line 7 \"library/number/montogomery.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::montgomery {\n        template\
    \ <typename Int, typename DInt>\n        struct Montgomery {\n        private:\n\
    \            static constexpr uint32_t bits = std::numeric_limits<Int>::digits;\n\
    \            static constexpr Int mask = ~Int(0);\n            // R = 2**32 or\
    \ 2**64\n\n            // 1. N is an odd number\n            // 2. N < R\n   \
    \         // 3. gcd(N, R) = 1\n            // 4. R * R2 - N * N2 = 1\n       \
    \     // 5. 0 < R2 < N\n            // 6. 0 < N2 < R\n            Int N, N2, R2;\n\
    \n            // RR = R * R (mod N)\n            Int RR;\n        public:\n  \
    \          constexpr Montgomery() = default;\n            explicit constexpr Montgomery(Int\
    \ N) : N(N), N2(calcN2(N)), R2(calcR2(N, N2)), RR(calcRR(N)) {\n             \
    \   assert(N & 1);\n            }\n\n            // @returns t * R (mod N)\n \
    \           constexpr Int make(Int t) const {\n                return reduce(static_cast<DInt>(t)\
    \ * RR);\n            }\n            // @returns T * R^(-1) (mod N)\n        \
    \    constexpr Int reduce(DInt T) const {\n                // 0 <= T < RN\n\n\
    \                // Note:\n                //  1. m = T * N2 (mod R)\n       \
    \         //  2. 0 <= m < R\n                DInt m = modR(static_cast<DInt>(modR(T))\
    \ * N2);\n\n                // Note:\n                //  T + m * N = T + T *\
    \ N * N2 = T + T * (R * R2 - 1) = 0 (mod R)\n                //  => (T + m * N)\
    \ / R is an integer.\n                //  => t * R = T + m * N = T (mod N)\n \
    \               //  => t = T R^(-1) (mod N)\n                DInt t = divR(T +\
    \ m * N);\n\n                // Note:\n                //  1. 0 <= T < RN\n  \
    \              //  2. 0 <= mN < RN (because 0 <= m < R)\n                //  =>\
    \ 0 <= T + mN < 2RN\n                //  => 0 <= t < 2N\n                return\
    \ t >= N ? t - N : t;\n            }\n\n            constexpr Int add(Int A, Int\
    \ B) const {\n                return (A += B) >= N ? A - N : A;\n            }\n\
    \            constexpr Int sub(Int A, Int B) const {\n                return (A\
    \ -= B) < 0 ? A + N : A;\n            }\n            constexpr Int mul(Int A,\
    \ Int B) const {\n                return reduce(static_cast<DInt>(A) * B);\n \
    \           }\n            constexpr Int div(Int A, Int B) const {\n         \
    \       return reduce(static_cast<DInt>(A) * inv(B));\n            }\n       \
    \     constexpr Int inv(Int A) const; // TODO: Implement\n\n            constexpr\
    \ Int pow(Int A, long long b) const {\n                Int P = make(1);\n    \
    \            for (; b; b >>= 1) {\n                    if (b & 1) P = mul(P, A);\n\
    \                    A = mul(A, A);\n                }\n                return\
    \ P;\n            }\n\n        private:\n            static constexpr Int divR(DInt\
    \ t) { return t >> bits; }\n            static constexpr Int modR(DInt t) { return\
    \ t & mask; }\n\n            static constexpr Int calcN2(Int N) {\n          \
    \      // - N * N2 = 1 (mod R)\n                // N2 = -N^{-1} (mod R)\n\n  \
    \              // calculates N^{-1} (mod R) by Newton's method\n             \
    \   DInt invN = N; // = N^{-1} (mod 2^2)\n                for (uint32_t cur_bits\
    \ = 2; cur_bits < bits; cur_bits *= 2) {\n                    // loop invariant:\
    \ invN = N^{-1} (mod 2^cur_bits)\n\n                    // x = a^{-1} mod m =>\
    \ x(2-ax) = a^{-1} mod m^2 because:\n                    //  ax = 1 (mod m)\n\
    \                    //  => (ax-1)^2 = 0 (mod m^2)\n                    //  =>\
    \ 2ax - a^2x^2 = 1 (mod m^2)\n                    //  => a(x(2-ax)) = 1 (mod m^2)\n\
    \                    invN = modR(invN * modR(2 - N * invN));\n               \
    \ }\n                assert(modR(N * invN) == 1);\n\n                return modR(-invN);\n\
    \            }\n            static constexpr Int calcR2(Int N, Int N2) {\n   \
    \             // R * R2 - N * N2 = 1\n                // => R2 = (1 + N * N2)\
    \ / R\n                return divR(1 + static_cast<DInt>(N) * N2);\n         \
    \   }\n            static constexpr Int calcRR(Int N) {\n                return\
    \ -DInt(N) % N;\n            }\n        };\n    } // namespace internal::montgomery\n\
    \    using Montgomery32 = internal::montgomery::Montgomery<uint32_t, uint64_t>;\n\
    \    using Montgomery64 = internal::montgomery::Montgomery<uint64_t, __uint128_t>;\n\
    } // namespace suisen\n\n\n\n#line 12 \"library/number/deterministic_miller_rabin.hpp\"\
    \n\nnamespace suisen::miller_rabin {\n    namespace internal {\n        constexpr\
    \ uint64_t THRESHOLD_1 = 341531ULL;\n        constexpr uint64_t BASE_1[]{ 9345883071009581737ULL\
    \ };\n\n        constexpr uint64_t THRESHOLD_2 = 1050535501ULL;\n        constexpr\
    \ uint64_t BASE_2[]{ 336781006125ULL, 9639812373923155ULL };\n\n        constexpr\
    \ uint64_t THRESHOLD_3 = 350269456337ULL;\n        constexpr uint64_t BASE_3[]{\
    \ 4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL };\n\
    \n        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;\n        constexpr\
    \ uint64_t BASE_4[]{ 2ULL, 141889084524735ULL, 1199124725622454117ULL, 11096072698276303650ULL\
    \ };\n\n        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;\n      \
    \  constexpr uint64_t BASE_5[]{ 2ULL, 4130806001517ULL, 149795463772692060ULL,\
    \ 186635894390467037ULL, 3967304179347715805ULL };\n\n        constexpr uint64_t\
    \ THRESHOLD_6 = 585226005592931977ULL;\n        constexpr uint64_t BASE_6[]{ 2ULL,\
    \ 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL,\
    \ 1263739024124850375ULL };\n\n        constexpr uint64_t BASE_7[]{ 2U, 325U,\
    \ 9375U, 28178U, 450775U, 9780504U, 1795265022U };\n\n        template <auto BASE,\
    \ std::size_t SIZE>\n        constexpr bool miller_rabin(uint64_t n) {\n     \
    \       if (n == 2 or n == 3 or n == 5 or n == 7) return true;\n            if\
    \ (n <= 1 or n % 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;\n\
    \            if (n < 121) return true;\n\n            const uint32_t s = __builtin_ctzll(n\
    \ - 1); // >= 1\n            const uint64_t d = (n - 1) >> s;\n\n            const\
    \ Montgomery64 mg{ n };\n\n            const uint64_t one = mg.make(1), minus_one\
    \ = mg.make(n - 1);\n\n            for (std::size_t i = 0; i < SIZE; ++i) {\n\
    \                uint64_t a = BASE[i] % n;\n                if (a == 0) continue;\n\
    \                uint64_t Y = mg.pow(mg.make(a), d);\n                if (Y ==\
    \ one) continue;\n                for (uint32_t r = 0;; ++r, Y = mg.mul(Y, Y))\
    \ {\n                    // Y = a^(d 2^r)\n                    if (Y == minus_one)\
    \ break;\n                    if (r == s - 1) return false;\n                }\n\
    \            }\n            return true;\n        }\n    }\n\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    constexpr\
    \ bool is_prime(T n) {\n        if constexpr (std::is_signed_v<T>) {\n       \
    \     assert(n >= 0);\n        }\n        const std::make_unsigned_t<T> n_unsigned\
    \ = n;\n        assert(n_unsigned <= std::numeric_limits<uint64_t>::max()); //\
    \ n < 2^64\n        using namespace internal;\n        if (n_unsigned < THRESHOLD_1)\
    \ return miller_rabin<BASE_1, 1>(n_unsigned);\n        if (n_unsigned < THRESHOLD_2)\
    \ return miller_rabin<BASE_2, 2>(n_unsigned);\n        if (n_unsigned < THRESHOLD_3)\
    \ return miller_rabin<BASE_3, 3>(n_unsigned);\n        if (n_unsigned < THRESHOLD_4)\
    \ return miller_rabin<BASE_4, 4>(n_unsigned);\n        if (n_unsigned < THRESHOLD_5)\
    \ return miller_rabin<BASE_5, 5>(n_unsigned);\n        if (n_unsigned < THRESHOLD_6)\
    \ return miller_rabin<BASE_6, 6>(n_unsigned);\n        return miller_rabin<BASE_7,\
    \ 7>(n_unsigned);\n    }\n} // namespace suisen::miller_rabin\n\n\n#line 1 \"\
    library/number/sieve_of_eratosthenes.hpp\"\n\n\n\n#line 6 \"library/number/sieve_of_eratosthenes.hpp\"\
    \n#include <vector>\n\n#line 1 \"library/number/internal_eratosthenes.hpp\"\n\n\
    \n\n#line 6 \"library/number/internal_eratosthenes.hpp\"\n\nnamespace suisen::internal::sieve\
    \ {\n\nconstexpr std::uint8_t K = 8;\nconstexpr std::uint8_t PROD = 2 * 3 * 5;\n\
    constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t\
    \ DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };\nconstexpr std::uint8_t DF[K][K]\
    \ = {\n    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2,\
    \ 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3,\
    \ 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2,\
    \ 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 48, 32, 16, 32, 16,\
    \ 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K] = {\n    {  0,  0,  0,  0, \
    \ 0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8,  8 },\n    { 16, 16,  0, 16,\
    \  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,  8 },\n    { 24, 24,  8, 16,\
    \  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,  8 },\n    { 40, 24,  8, 32,\
    \  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,  8 },\n};\n\nconstexpr std::uint8_t\
    \ MASK[K][K] = {\n    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02,\
    \ 0x20, 0x10, 0x01, 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02,\
    \ 0x80, 0x08, 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n  \
    \  { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02,\
    \ 0x40, 0x01, 0x10, 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02\
    \ }, { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t\
    \ OFFSET[K][K] = {\n    { 0, 1, 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3,\
    \ 2, 6, },\n    { 2, 4, 0, 6, 1, 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n\
    \    { 4, 7, 1, 2, 5, 6, 0, 3, },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6,\
    \ 2, 3, 7, 0, 4, 5, 1, },\n    { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t\
    \ mask_to_index(const std::uint8_t bits) {\n    switch (bits) {\n        case\
    \ 1 << 0: return 0;\n        case 1 << 1: return 1;\n        case 1 << 2: return\
    \ 2;\n        case 1 << 3: return 3;\n        case 1 << 4: return 4;\n       \
    \ case 1 << 5: return 5;\n        case 1 << 6: return 6;\n        case 1 << 7:\
    \ return 7;\n        default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\
    \n\n#line 9 \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
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
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 14 \"library/number/fast_factorize.hpp\"\
    \n\nnamespace suisen::fast_factorize {\n    namespace internal {\n        template\
    \ <typename T>\n        constexpr int floor_log2(T n) {\n            int i = 0;\n\
    \            while (n) n >>= 1, ++i;\n            return i - 1;\n        }\n \
    \       template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        T pollard_rho(const T n) {\n            using M = safely_multipliable_t<T>;\n\
    \            const T m = T(1) << (floor_log2(n) / 5);\n\n            static std::mt19937_64\
    \ rng{std::random_device{}()};\n            std::uniform_int_distribution<T> dist(0,\
    \ n - 1);\n\n            // const Montgomery64 mg{n};\n\n            while (true)\
    \ {\n                T c = dist(rng);\n                auto f = [&](T x) -> T\
    \ { return (M(x) * x + c) % n; };\n                T x, y = 2, ys, q = 1, g =\
    \ 1;\n                for (T r = 1; g == 1; r <<= 1) {\n                    x\
    \ = y;\n                    for (T i = 0; i < r; ++i) y = f(y);\n            \
    \        for (T k = 0; k < r and g == 1; k += m) {\n                        ys\
    \ = y;\n                        for (T i = 0; i < std::min(m, r - k); ++i) y =\
    \ f(y), q = M(q) * (x > y ? x - y : y - x) % n;\n                        g = std::gcd(q,\
    \ n);\n                    }\n                }\n                if (g == n) {\n\
    \                    g = 1;\n                    while (g == 1) ys = f(ys), g\
    \ = std::gcd(x > ys ? x - ys : ys - x, n);\n                }\n              \
    \  if (g < n) {\n                    if (miller_rabin::is_prime(g)) return g;\n\
    \                    if (T d = n / g; miller_rabin::is_prime(d)) return d;\n \
    \                   return pollard_rho(g);\n                }\n            }\n\
    \        }\n    }\n\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<std::pair<T, int>> factorize(T n)\
    \ {\n        static constexpr int threshold = 1000000;\n        static Sieve<threshold>\
    \ sieve;\n\n        std::vector<std::pair<T, int>> res;\n        if (n <= threshold)\
    \ {\n            for (auto [p, q] : sieve.factorize(n)) res.emplace_back(p, q);\n\
    \            return res;\n        }\n\n        if ((n & 1) == 0) {\n         \
    \   int q = 0;\n            do ++q, n >>= 1; while ((n & 1) == 0);\n         \
    \   res.emplace_back(2, q);\n        }\n        for (T p = 3; p * p <= n; p +=\
    \ 2) {\n            if (p >= 101 and n >= 1 << 20) {\n                while (n\
    \ > 1) {\n                    if (miller_rabin::is_prime(n)) {\n             \
    \           res.emplace_back(std::exchange(n, 1), 1);\n                    } else\
    \ {\n                        p = internal::pollard_rho(n);\n                 \
    \       int q = 0;\n                        do ++q, n /= p; while (n % p == 0);\n\
    \                        res.emplace_back(p, q);\n                    }\n    \
    \            }\n                break;\n            }\n            if (n % p ==\
    \ 0) {\n                int q = 0;\n                do ++q, n /= p; while (n %\
    \ p == 0);\n                res.emplace_back(p, q);\n            }\n        }\n\
    \        if (n > 1) res.emplace_back(n, 1);\n        return res;\n    }\n} //\
    \ namespace suisen::fast_factorize\n\n\n#line 1 \"library/number/order_Z_mZ.hpp\"\
    \n\n\n\n#line 6 \"library/number/order_Z_mZ.hpp\"\n\n#line 9 \"library/number/order_Z_mZ.hpp\"\
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
    \ std::nullptr_t> = nullptr>\n    struct OrderMod {\n        using U = std::make_unsigned_t<T>;\n\
    \        OrderMod() = default;\n        OrderMod(T m) : _mod(m) {\n          \
    \  auto factorized = fast_factorize::factorize<T>(_mod);\n            _is_prime\
    \ = factorized.size() == 1;\n            _lambda = _carmichael(factorized);\n\
    \            _phi = _totient(factorized);\n            for (auto [p, q] : fast_factorize::factorize<T>(_lambda))\
    \ {\n                U r = 1;\n                for (int i = 0; i < q; ++i) r *=\
    \ p;\n                _fac_lambda.emplace_back(p, q, r);\n            }\n    \
    \    }\n\n        bool is_primitive_root(U a) const {\n            if (_mod <\
    \ 1ULL << 32) {\n                using mint = atcoder::dynamic_modint<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_mod);\n\
    \                bool res = _is_primitive_root_impl<mint>(a);\n              \
    \  mint::set_mod(old_mod);\n                return res;\n            } else {\n\
    \                using mint = internal::order_prime_mod::mint64<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_mod);\n\
    \                bool res = _is_primitive_root_impl<mint>(a);\n              \
    \  mint::set_mod(old_mod);\n                return res;\n            }\n     \
    \   }\n\n        T primitive_root() const {\n            assert(_lambda == _phi);\n\
    \            if (_mod < 1ULL << 32) {\n                return _primitive_root_impl<std::mt19937>();\n\
    \            } else {\n                return _primitive_root_impl<std::mt19937_64>();\n\
    \            }\n        }\n\n        T operator()(U a) const {\n            if\
    \ (_mod < 1ULL << 32) {\n                using mint = atcoder::dynamic_modint<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_mod);\n\
    \                T res = _order_impl<mint>(a);\n                mint::set_mod(old_mod);\n\
    \                return res;\n            } else {\n                using mint\
    \ = internal::order_prime_mod::mint64<1000000000>;\n                U old_mod\
    \ = mint::mod();\n                mint::set_mod(_mod);\n                T res\
    \ = _order_impl<mint>(a);\n                mint::set_mod(old_mod);\n         \
    \       return res;\n            }\n        }\n\n        T mod() const {\n   \
    \         return _mod;\n        }\n        T totient() const {\n            return\
    \ _phi;\n        }\n        T carmichael() const {\n            return _lambda;\n\
    \        }\n        bool is_prime() const {\n            return _is_prime;\n \
    \       }\n        std::vector<T> carmichael_prime_factors() const {\n       \
    \     std::vector<T> res;\n            for (const auto &e : _fac_lambda) res.push_back(std::get<0>(e));\n\
    \            return res;\n        }\n\n    private:\n        U _mod;\n       \
    \ U _phi;\n        U _lambda;\n        bool _is_prime;\n\n        std::vector<std::tuple<U,\
    \ int, U>> _fac_lambda;\n\n        static T _carmichael(const std::vector<std::pair<T,\
    \ int>>& factorized) {\n            T lambda = 1;\n            for (auto [p, ep]\
    \ : factorized) {\n                T phi = p - 1;\n                int exponent\
    \ = ep - (1 + (p == 2 and ep >= 3));\n                for (int i = 0; i < exponent;\
    \ ++i) phi *= p;\n                lambda = std::lcm(lambda, phi);\n          \
    \  }\n            return lambda;\n        }\n        static T _totient(const std::vector<std::pair<T,\
    \ int>>& factorized) {\n            T t = 1;\n            for (const auto& [p,\
    \ ep] : factorized) {\n                t *= p - 1;\n                for (int i\
    \ = 0; i < ep - 1; ++i) t *= p;\n            }\n            return t;\n      \
    \  }\n\n        template <typename mint>\n        bool _is_primitive_root_impl(U\
    \ a) const {\n            if (_lambda != _phi) return false;\n            if (_mod\
    \ == 2) return a % 2 == 1;\n\n            const int k = _fac_lambda.size();\n\
    \            U x = _lambda;\n            for (const auto& [p, q, pq] : _fac_lambda)\
    \ x /= p;\n\n            mint b = mint(a).pow(x);\n            if (k == 1) return\
    \ b.val() != 1;\n\n            auto dfs = [&](auto dfs, const int l, const int\
    \ r, const mint val) -> bool {\n                const int m = (l + r) >> 1;\n\n\
    \                U lp = 1;\n                for (int i = m; i < r; ++i) lp *=\
    \ std::get<0>(_fac_lambda[i]);\n                mint lval = val.pow(lp);\n   \
    \             if (m - l == 1) {\n                    if (lval.val() == 1) return\
    \ false;\n                } else {\n                    if (not dfs(dfs, l, m,\
    \ lval)) return false;\n                }\n\n                U rp = 1;\n     \
    \           for (int i = l; i < m; ++i) rp *= std::get<0>(_fac_lambda[i]);\n \
    \               mint rval = val.pow(rp);\n                if (r - m == 1) {\n\
    \                    if (rval.val() == 1) return false;\n                } else\
    \ {\n                    if (not dfs(dfs, m, r, rval)) return false;\n       \
    \         }\n\n                return true;\n            };\n            return\
    \ dfs(dfs, 0, k, b);\n        }\n\n        template <typename Rng>\n        T\
    \ _primitive_root_impl() const {\n            if (_mod == 2) return 1;\n\n   \
    \         Rng rng{ std::random_device{}() };\n            while (true) {\n   \
    \             U a = rng() % (_mod - 2) + 2;\n                while (not _is_prime\
    \ and std::gcd(a, _mod) != 1) {\n                    a = rng() % (_mod - 2) +\
    \ 2;\n                }\n                if (is_primitive_root(a)) return a;\n\
    \            }\n        }\n\n        template <typename mint>\n        U _order_impl(U\
    \ a) const {\n            if (_mod == 2) return a % 2 == 1;\n\n            const\
    \ int k = _fac_lambda.size();\n\n            U res = 1;\n\n            auto update\
    \ = [&](U p, mint val) {\n                while (val.val() != 1) {\n         \
    \           val = val.pow(p);\n                    res *= p;\n               \
    \ }\n            };\n\n            if (k == 1) {\n                update(std::get<0>(_fac_lambda.front()),\
    \ a);\n                return res;\n            }\n\n            auto dfs = [&](auto\
    \ dfs, const int l, const int r, const mint val) -> void {\n                const\
    \ int m = (l + r) >> 1;\n\n                U lp = 1;\n                for (int\
    \ i = m; i < r; ++i) lp *= std::get<2>(_fac_lambda[i]);\n                mint\
    \ lval = val.pow(lp);\n                if (m - l == 1) {\n                   \
    \ update(std::get<0>(_fac_lambda[l]), lval);\n                } else {\n     \
    \               dfs(dfs, l, m, lval);\n                }\n\n                U\
    \ rp = 1;\n                for (int i = l; i < m; ++i) rp *= std::get<2>(_fac_lambda[i]);\n\
    \                mint rval = val.pow(rp);\n                if (r - m == 1) {\n\
    \                    update(std::get<0>(_fac_lambda[m]), rval);\n            \
    \    } else {\n                    dfs(dfs, m, r, rval);\n                }\n\
    \            };\n            dfs(dfs, 0, k, a);\n\n            return res;\n \
    \       }\n    };\n} // namespace suisen\n\n\n#line 1 \"library/number/discrete_logarithm.hpp\"\
    \n\n\n\n#line 5 \"library/number/discrete_logarithm.hpp\"\n#include <unordered_map>\n\
    #line 7 \"library/number/discrete_logarithm.hpp\"\n\nnamespace suisen {\n    namespace\
    \ internal::discrete_logarithm {\n        int floor_log2(int m) {\n          \
    \  int res = 0;\n            while (1 << (res + 1) <= m) ++res;\n            return\
    \ res;\n        }\n    }\n\n    template <typename mint>\n    int discrete_logarithm_coprime(mint\
    \ x, mint y) {\n        const int m = mint::mod();\n        if (y == 1 or m ==\
    \ 1) return 0;\n        if (x == 0) return y == 0 ? 1 : -1;\n        const int\
    \ p = ::sqrt(m) + 1;\n        mint a = mint(x).inv().pow(p);\n        std::unordered_map<int,\
    \ int> mp;\n        mint pow_x = 1;\n        for (int j = 0; j < p; ++j, pow_x\
    \ *= x) mp.try_emplace(pow_x.val(), j);\n        mint ya = y;\n        for (int\
    \ i = 0; i < p; ++i, ya *= a) {\n            if (auto it = mp.find(ya.val());\
    \ it != mp.end()) return p * i + it->second;\n        }\n        return -1;\n\
    \    }\n\n    template <typename mint>\n    int discrete_logarithm(mint x, mint\
    \ y) {\n        using namespace internal::discrete_logarithm;\n        const int\
    \ m = mint::mod();\n        if (m == 1) return 0;\n        const int d = floor_log2(m);\n\
    \        mint pow_x = 1;\n        for (int i = 0; i < d; ++i, pow_x *= x) if (pow_x\
    \ == y) return i;\n        const int g = std::gcd(pow_x.val(), m);\n        if\
    \ (y.val() % g) return -1;\n        mint::set_mod(m / g);\n        const int t\
    \ = discrete_logarithm_coprime(mint(x.val()), mint(y.val()) * mint(pow_x.val()).inv());\n\
    \        mint::set_mod(m);\n        return t != -1 ? d + t : -1;\n    }\n} //\
    \ namespace suisen\n\n\n\n#line 17 \"library/number/fast_discrete_logarithm.hpp\"\
    \n\nnamespace suisen::fast_discrete_logarithm {\n    namespace internal {\n  \
    \      template <typename mint>\n        struct SystemOfLinearEquations {\n  \
    \          SystemOfLinearEquations() = default;\n            SystemOfLinearEquations(int\
    \ target_var_id) : target_var_id(target_var_id) {}\n\n            void append(std::vector<mint>\
    \ r, mint bi) {\n                int ti = target_var_id + 1;\n               \
    \ for (int i = 0; i <= target_var_id; ++i) if (r[i] != 0) {\n                \
    \    ti = i;\n                    break;\n                }\n                if\
    \ (ti > target_var_id) return;\n\n                const int l = A.size();\n  \
    \              const int start = std::lower_bound(top_pos.begin(), top_pos.end(),\
    \ ti) - top_pos.begin();\n                for (int i = start; i < l; ++i) {\n\
    \                    eliminate(top_pos[i], A[i], b[i], ti, r, bi);\n         \
    \           if (ti > target_var_id) return;\n                }\n             \
    \   A.push_back(std::move(r));\n                top_pos.push_back(ti);\n     \
    \           b.push_back(bi);\n            }\n            void append(const std::vector<std::pair<int,\
    \ mint>>& ri, mint bi) {\n                std::vector<mint> r(target_var_id +\
    \ 1);\n                for (auto [j, v] : ri) r[j] = v;\n                append(std::move(r),\
    \ bi);\n            }\n\n            std::optional<mint> target() {\n        \
    \        if (top_pos.empty() or top_pos.back() != target_var_id) return std::nullopt;\n\
    \                auto [g, inv_c] = atcoder::internal::inv_gcd(A.back().back().val(),\
    \ mint::mod());\n                return g == 1 ? std::make_optional(b.back() *\
    \ inv_c) : std::nullopt;\n            }\n\n            void change_target() {\n\
    \                const int l = A.size();\n\n                int t = -1;\n    \
    \            for (int i = l - 1; i >= 0; --i) {\n                    if (A[i][target_var_id]\
    \ != 0) {\n                        t = i;\n                        break;\n  \
    \                  }\n                }\n\n                SystemOfLinearEquations<mint>\
    \ nxt(target_var_id);\n                for (int i = l - 1; i > t; --i) {\n   \
    \                 nxt.append(A[i], b[i]);\n                }\n\n             \
    \   for (int i = t - 1; i >= 0; --i) {\n                    if (A[i][target_var_id]\
    \ != 0) {\n                        const auto T = euclid(A[t][target_var_id].val(),\
    \ A[i][target_var_id].val());\n                        for (int col = top_pos[i];\
    \ col <= target_var_id; ++col) {\n                            apply_euclid(T,\
    \ A[t][col], A[i][col]);\n                        }\n                        apply_euclid(T,\
    \ b[t], b[i]);\n                    }\n                    nxt.append(A[i], b[i]);\n\
    \                }\n\n                *this = std::move(nxt);\n            }\n\
    \        private:\n            int target_var_id;\n            std::vector<std::vector<mint>>\
    \ A;\n            std::vector<int> top_pos;\n            std::vector<mint> b;\n\
    \n            // Euclidean Algorithm\n            // A * [a, b] = [gcd(a,b), 0]\n\
    \            static std::array<std::array<int, 2>, 2> euclid(int a, int b) {\n\
    \                int x = 1, y = 0, z = 0, w = 1;\n                while (b) {\n\
    \                    int p = a / b, q = a % b;\n                    x -= p * z,\
    \ std::swap(x, z);\n                    y -= p * w, std::swap(y, w);\n       \
    \             a = b, b = q;\n                }\n                return { x, y,\
    \ z, w };\n            }\n            static void apply_euclid(const std::array<std::array<int,\
    \ 2>, 2>& A, mint& x, mint& y) {\n                mint x2 = x, y2 = y;\n     \
    \           x = A[0][0] * x2 + A[0][1] * y2;\n                y = A[1][0] * x2\
    \ + A[1][1] * y2;\n            }\n\n            static void eliminate(int& ti,\
    \ std::vector<mint>& ri, mint& bi, int& tj, std::vector<mint>& rj, mint& bj) {\n\
    \                if (ti != tj) {\n                    if (ti > tj) std::swap(ti,\
    \ tj), std::swap(ri, rj), std::swap(bi, bj);\n                    return;\n  \
    \              }\n                const int siz = ri.size();\n               \
    \ assert(int(rj.size()) == siz);\n\n                const auto T = euclid(ri[ti].val(),\
    \ rj[tj].val());\n                for (int col = ti; col < siz; ++col) {\n   \
    \                 apply_euclid(T, ri[col], rj[col]);\n                }\n    \
    \            apply_euclid(T, bi, bj);\n\n                while (tj < siz and rj[tj]\
    \ == 0) ++tj;\n            }\n        };\n    }\n\n    struct IndexCalculus {\n\
    \    private:\n        using mint = atcoder::dynamic_modint<73495793>;\n     \
    \   using mint2 = atcoder::dynamic_modint<73495794>;\n    public:\n        IndexCalculus()\
    \ = default;\n        IndexCalculus(const OrderMod<int>& ord) : _p(ord.mod()),\
    \ _ord(ord) {\n            assert(ord.is_prime());\n        }\n\n        int operator()(int\
    \ a, int b, int p) {\n            int old_mod = mint::mod(), old_mod2 = mint2::mod();\n\
    \            mint::set_mod(p), mint2::set_mod(p - 1);\n            int res = discrete_log_impl(a,\
    \ b, p);\n            mint::set_mod(old_mod), mint2::set_mod(old_mod2);\n    \
    \        return res;\n        }\n        static int discrete_logarithm(int a,\
    \ int b, int p) {\n            return IndexCalculus{}(a, b, p);\n        }\n \
    \   private:\n        static constexpr int MAX_B = 80;\n        static constexpr\
    \ uint32_t primes[MAX_B]{\n            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,\n \
    \           31, 37, 41, 43, 47, 53, 59, 61, 67, 71,\n            73, 79, 83, 89,\
    \ 97, 101, 103, 107, 109, 113,\n            127, 131, 137, 139, 149, 151, 157,\
    \ 163, 167, 173,\n            179, 181, 191, 193, 197, 199, 211, 223, 227, 229,\n\
    \            233, 239, 241, 251, 257, 263, 269, 271, 277, 281,\n            283,\
    \ 293, 307, 311, 313, 317, 331, 337, 347, 349,\n            353, 359, 367, 373,\
    \ 379, 383, 389, 397, 401, 409,\n        };\n        // inv_primes[i] = ceil(2^32\
    \ / primes[i])\n        static constexpr uint32_t inv_primes[MAX_B]{\n       \
    \     2147483648,1431655766, 858993460, 613566757, 390451573, 330382100, 252645136,\
    \ 226050911, 186737709, 148102321,\n            138547333, 116080198, 104755300,\
    \ 99882961, 91382283, 81037119, 72796056, 70409300, 64103990, 60492498,\n    \
    \        58835169, 54366675, 51746594, 48258060, 44278014, 42524429, 41698712,\
    \ 40139882, 39403370, 38008561,\n            33818641, 32786010, 31350127, 30899046,\
    \ 28825284, 28443493, 27356480, 26349493, 25718368, 24826401,\n            23994231,\
    \ 23729102, 22486740, 22253717, 21801865, 21582751, 20355296, 19259944, 18920561,\
    \ 18755316,\n            18433337, 17970575, 17821442, 17111424, 16711936, 16330675,\
    \ 15966422, 15848588, 15505298, 15284582,\n            15176563, 14658592, 13990122,\
    \ 13810185, 13721941, 13548793, 12975733, 12744711, 12377428, 12306497,\n    \
    \        12167047, 11963698, 11702909, 11514658, 11332368, 11214014, 11041048,\
    \ 10818558, 10710642, 10501143,\n        };\n\n        int _p = -1;\n        OrderMod<int>\
    \ _ord;\n        int _a = -1;\n        internal::SystemOfLinearEquations<mint2>\
    \ _eq;\n\n        static int safe_mod(int a, int p) { return ((a %= p) < 0) ?\
    \ a + p : a; }\n\n        static int discrete_log_naive(mint a, mint b, int ord_a)\
    \ {\n            mint pow_a = 1;\n            for (int res = 0; res < ord_a; ++res)\
    \ {\n                if (pow_a == b) return res;\n                pow_a *= a;\n\
    \            }\n            return -1;\n        }\n\n        static bool is_smooth(const\
    \ int B, uint32_t v) {\n            assert(B <= MAX_B);\n            for (int\
    \ i = 0; i < B; ++i) {\n                const uint32_t m = primes[B - i - 1],\
    \ im = inv_primes[B - i - 1];\n                if (uint32_t q = (uint64_t(v) *\
    \ im) >> 32; v == q * m) {\n                    // q = floor(v/m)\n          \
    \          do v = q, q = (uint64_t(v) * im) >> 32; while (v == q * m);\n     \
    \           }\n            }\n            return v == 1;\n        }\n\n      \
    \  static std::optional<std::vector<mint2>> try_factorize(const int B, uint32_t\
    \ v) {\n            assert(B <= MAX_B);\n            if (not is_smooth(B, v))\
    \ return std::nullopt;\n            std::vector<mint2> res(B + 1);\n         \
    \   for (int i = 0; i < B; ++i) {\n                const uint32_t m = primes[B\
    \ - i - 1], im = inv_primes[B - i - 1];\n                int c = 0;\n        \
    \        uint32_t q = (uint64_t(v) * im) >> 32;\n                while (v == q\
    \ * m) {\n                    v = q, q = (uint64_t(v) * im) >> 32;\n         \
    \           ++c;\n                }\n                res[i] = c;\n           \
    \ }\n            res[B] = -1;\n            return res;\n        }\n\n        int\
    \ discrete_log_impl(int a, int b, int p) {\n            a = safe_mod(a, p), b\
    \ = safe_mod(b, p);\n\n            if (b == 0) return a == 0 ? 1 : -1;\n     \
    \       if (b == 1) return 0;\n            if (a == 0) return -1;\n          \
    \  if (a == 1) return -1;\n\n            if (p <= 64) return discrete_log_naive(a,\
    \ b, p - 1);\n\n            const int B = ::pow(p - 1, 1 / (2 * ::sqrt(::log(p\
    \ - 1) / ::log(::log(p - 1))))) + 5;\n            assert(B <= MAX_B);\n\n    \
    \        if (p != _p) {\n                _p = p, _ord = OrderMod<int>(p);\n  \
    \              _a = a, _eq = internal::SystemOfLinearEquations<mint2>(B);\n  \
    \          } else if (a != _a) {\n                _a = a, _eq = internal::SystemOfLinearEquations<mint2>(B);\n\
    \            } else {\n                _eq.change_target();\n            }\n\n\
    \            assert(_ord.is_prime());\n\n            const int ord_a = _ord(a),\
    \ ord_b = _ord(b);\n            if (ord_a % ord_b) return -1;\n            if\
    \ (ord_a <= 64) return discrete_log_naive(a, b, ord_a);\n\n            static\
    \ std::mt19937 rng{};\n            while (true) {\n                const int k\
    \ = rng() % ord_a;\n                auto opt_fac = try_factorize(B, (mint(a).pow(k)\
    \ * b).val());\n                if (not opt_fac) continue;\n                auto&\
    \ fac = *opt_fac;\n                _eq.append(std::move(fac), k);\n          \
    \      if (auto res = _eq.target()) return res->val() % ord_a;\n            }\n\
    \        }\n    };\n\n    namespace internal {\n        using mint = atcoder::dynamic_modint<73495793>;\n\
    \n        // min{ i | 0 <= i < r and a^i = b } or -1\n        int naive(int a,\
    \ int b, int r) {\n            mint pow_a = 1;\n            for (int res = 0;\
    \ res < r; ++res) {\n                if (pow_a == b) return res;\n           \
    \     pow_a *= a;\n            }\n            return -1;\n        }\n\n      \
    \  int pohlig_hellman_prime_power_bsgs(int a, int b, int ord_a, int p, int q)\
    \ {\n            // ord_a = p ^ q\n            if (ord_a <= 64) return naive(a,\
    \ b, ord_a);\n            const mint gamma = mint(a).pow(ord_a / p);\n       \
    \     const mint inv_a = mint(a).inv();\n\n            int x = 0;\n          \
    \  for (int k = 0, pl = 1, pr = ord_a; k < q; ++k) {\n                pr /= p;\n\
    \                int d = suisen::discrete_logarithm_coprime(gamma, (inv_a.pow(x)\
    \ * b).pow(pr));\n                if (d == -1) return -1;\n                x +=\
    \ pl * d;\n                pl *= p;\n            }\n            return x;\n  \
    \      }\n\n        int pohlig_hellman(int a, int b, int p, int q, const OrderMod<int>&\
    \ ord) {\n            // gcd(a, p) = 1\n\n            if (b == 1) return 0;\n\
    \            if (a == 1) return b == 1 ? 0 : -1;\n            if (b % p == 0)\
    \ return -1;\n\n            if (q == 1) {\n                \n                return\
    \ IndexCalculus{ ord }(a, b, p);\n            }\n\n            const int ord_a\
    \ = ord(a);\n            if (ord_a <= 64) return naive(a, b, ord_a);\n       \
    \     if (ord_a % ord(b)) return -1;\n\n            const std::vector<std::pair<int,\
    \ int>> ord_factorized = [&] {\n                std::vector<std::pair<int, int>>\
    \ res;\n                int v = ord_a;\n                for (int p : ord.carmichael_prime_factors())\
    \ if (v % p == 0) {\n                    int& c = res.emplace_back(p, 0).second;\n\
    \                    do v /= p, ++c; while (v % p == 0);\n                }\n\
    \                return res;\n            }();\n\n            std::vector<long\
    \ long> rs, ms;\n            for (auto [p, q] : ord_factorized) {\n          \
    \      int pq = 1;\n                for (int i = 0; i < q; ++i) pq *= p;\n\n \
    \               const int na = mint(a).pow(ord_a / pq).val(), nb = mint(b).pow(ord_a\
    \ / pq).val();\n                const int x = pohlig_hellman_prime_power_bsgs(na,\
    \ nb, pq, p, q);\n                if (x == -1) return -1;\n                rs.push_back(x),\
    \ ms.push_back(pq);\n            }\n            return atcoder::crt(rs, ms).first;\n\
    \        }\n    }\n\n    namespace internal {\n        int discrete_logarithm_coprime(int\
    \ a, int b) {\n            const int m = mint::mod();\n            assert(std::gcd(a,\
    \ m) == 1);\n\n            long long r = 0, md = 1;\n            for (auto [p,\
    \ q] : fast_factorize::factorize(m)) { // CRT\n                int pq = 1;\n \
    \               for (int i = 0; i < q; ++i) pq *= p;\n\n                mint::set_mod(pq);\n\
    \                OrderMod ord(pq);\n                const long long r2 = pohlig_hellman(mint(a).val(),\
    \ mint(b).val(), p, q, ord);\n                if (r2 == -1) return -1;\n\n   \
    \             const long long md2 = ord(a);\n                std::tie(r, md) =\
    \ atcoder::crt({ r, r2 }, { md, md2 });\n                if (md == 0) return -1;\n\
    \            }\n            return r;\n        }\n\n        int discrete_logarithm_arbitrary_mod(int\
    \ a, int b) {\n            const int m = mint::mod();\n\n            if (m ==\
    \ 1 or b == 1) return 0;\n            if (a == 0) return b == 0 ? 1 : b == 1 ?\
    \ 0 : -1;\n            if (a == 1) return b == 1 ? 0 : -1;\n\n            const\
    \ int floor_log2_m = [m] {\n                int res = 0;\n                while\
    \ (1 << (res + 1) <= m) ++res;\n                return res;\n            }();\n\
    \n            if (int i = naive(a, b, floor_log2_m); i != -1) return i;\n\n  \
    \          const int pow_a = mint(a).pow(floor_log2_m).val();\n            const\
    \ int g = std::gcd(pow_a, m);\n            if (b % g) return -1;\n\n         \
    \   mint::set_mod(m / g);\n            const int t = discrete_logarithm_coprime(mint(a).val(),\
    \ (mint(b) / pow_a).val());\n\n            return t != -1 ? floor_log2_m + t :\
    \ -1;\n        }\n    }\n\n    int discrete_logarithm(int a, int b, int m) {\n\
    \        using internal::mint;\n        const int old_mod = mint::mod();\n   \
    \     mint::set_mod(m);\n        const int res = internal::discrete_logarithm_arbitrary_mod(mint(a).val(),\
    \ mint(b).val());\n        mint::set_mod(old_mod);\n        return res;\n    }\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_INDEX_CALCULUS\n#define SUISEN_INDEX_CALCULUS\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n#include\
    \ <optional>\n#include <map>\n\n#include <atcoder/modint>\n#include <atcoder/math>\n\
    \n#include \"library/number/fast_factorize.hpp\"\n#include \"library/number/order_Z_mZ.hpp\"\
    \n#include \"library/number/discrete_logarithm.hpp\"\n\nnamespace suisen::fast_discrete_logarithm\
    \ {\n    namespace internal {\n        template <typename mint>\n        struct\
    \ SystemOfLinearEquations {\n            SystemOfLinearEquations() = default;\n\
    \            SystemOfLinearEquations(int target_var_id) : target_var_id(target_var_id)\
    \ {}\n\n            void append(std::vector<mint> r, mint bi) {\n            \
    \    int ti = target_var_id + 1;\n                for (int i = 0; i <= target_var_id;\
    \ ++i) if (r[i] != 0) {\n                    ti = i;\n                    break;\n\
    \                }\n                if (ti > target_var_id) return;\n\n      \
    \          const int l = A.size();\n                const int start = std::lower_bound(top_pos.begin(),\
    \ top_pos.end(), ti) - top_pos.begin();\n                for (int i = start; i\
    \ < l; ++i) {\n                    eliminate(top_pos[i], A[i], b[i], ti, r, bi);\n\
    \                    if (ti > target_var_id) return;\n                }\n    \
    \            A.push_back(std::move(r));\n                top_pos.push_back(ti);\n\
    \                b.push_back(bi);\n            }\n            void append(const\
    \ std::vector<std::pair<int, mint>>& ri, mint bi) {\n                std::vector<mint>\
    \ r(target_var_id + 1);\n                for (auto [j, v] : ri) r[j] = v;\n  \
    \              append(std::move(r), bi);\n            }\n\n            std::optional<mint>\
    \ target() {\n                if (top_pos.empty() or top_pos.back() != target_var_id)\
    \ return std::nullopt;\n                auto [g, inv_c] = atcoder::internal::inv_gcd(A.back().back().val(),\
    \ mint::mod());\n                return g == 1 ? std::make_optional(b.back() *\
    \ inv_c) : std::nullopt;\n            }\n\n            void change_target() {\n\
    \                const int l = A.size();\n\n                int t = -1;\n    \
    \            for (int i = l - 1; i >= 0; --i) {\n                    if (A[i][target_var_id]\
    \ != 0) {\n                        t = i;\n                        break;\n  \
    \                  }\n                }\n\n                SystemOfLinearEquations<mint>\
    \ nxt(target_var_id);\n                for (int i = l - 1; i > t; --i) {\n   \
    \                 nxt.append(A[i], b[i]);\n                }\n\n             \
    \   for (int i = t - 1; i >= 0; --i) {\n                    if (A[i][target_var_id]\
    \ != 0) {\n                        const auto T = euclid(A[t][target_var_id].val(),\
    \ A[i][target_var_id].val());\n                        for (int col = top_pos[i];\
    \ col <= target_var_id; ++col) {\n                            apply_euclid(T,\
    \ A[t][col], A[i][col]);\n                        }\n                        apply_euclid(T,\
    \ b[t], b[i]);\n                    }\n                    nxt.append(A[i], b[i]);\n\
    \                }\n\n                *this = std::move(nxt);\n            }\n\
    \        private:\n            int target_var_id;\n            std::vector<std::vector<mint>>\
    \ A;\n            std::vector<int> top_pos;\n            std::vector<mint> b;\n\
    \n            // Euclidean Algorithm\n            // A * [a, b] = [gcd(a,b), 0]\n\
    \            static std::array<std::array<int, 2>, 2> euclid(int a, int b) {\n\
    \                int x = 1, y = 0, z = 0, w = 1;\n                while (b) {\n\
    \                    int p = a / b, q = a % b;\n                    x -= p * z,\
    \ std::swap(x, z);\n                    y -= p * w, std::swap(y, w);\n       \
    \             a = b, b = q;\n                }\n                return { x, y,\
    \ z, w };\n            }\n            static void apply_euclid(const std::array<std::array<int,\
    \ 2>, 2>& A, mint& x, mint& y) {\n                mint x2 = x, y2 = y;\n     \
    \           x = A[0][0] * x2 + A[0][1] * y2;\n                y = A[1][0] * x2\
    \ + A[1][1] * y2;\n            }\n\n            static void eliminate(int& ti,\
    \ std::vector<mint>& ri, mint& bi, int& tj, std::vector<mint>& rj, mint& bj) {\n\
    \                if (ti != tj) {\n                    if (ti > tj) std::swap(ti,\
    \ tj), std::swap(ri, rj), std::swap(bi, bj);\n                    return;\n  \
    \              }\n                const int siz = ri.size();\n               \
    \ assert(int(rj.size()) == siz);\n\n                const auto T = euclid(ri[ti].val(),\
    \ rj[tj].val());\n                for (int col = ti; col < siz; ++col) {\n   \
    \                 apply_euclid(T, ri[col], rj[col]);\n                }\n    \
    \            apply_euclid(T, bi, bj);\n\n                while (tj < siz and rj[tj]\
    \ == 0) ++tj;\n            }\n        };\n    }\n\n    struct IndexCalculus {\n\
    \    private:\n        using mint = atcoder::dynamic_modint<73495793>;\n     \
    \   using mint2 = atcoder::dynamic_modint<73495794>;\n    public:\n        IndexCalculus()\
    \ = default;\n        IndexCalculus(const OrderMod<int>& ord) : _p(ord.mod()),\
    \ _ord(ord) {\n            assert(ord.is_prime());\n        }\n\n        int operator()(int\
    \ a, int b, int p) {\n            int old_mod = mint::mod(), old_mod2 = mint2::mod();\n\
    \            mint::set_mod(p), mint2::set_mod(p - 1);\n            int res = discrete_log_impl(a,\
    \ b, p);\n            mint::set_mod(old_mod), mint2::set_mod(old_mod2);\n    \
    \        return res;\n        }\n        static int discrete_logarithm(int a,\
    \ int b, int p) {\n            return IndexCalculus{}(a, b, p);\n        }\n \
    \   private:\n        static constexpr int MAX_B = 80;\n        static constexpr\
    \ uint32_t primes[MAX_B]{\n            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,\n \
    \           31, 37, 41, 43, 47, 53, 59, 61, 67, 71,\n            73, 79, 83, 89,\
    \ 97, 101, 103, 107, 109, 113,\n            127, 131, 137, 139, 149, 151, 157,\
    \ 163, 167, 173,\n            179, 181, 191, 193, 197, 199, 211, 223, 227, 229,\n\
    \            233, 239, 241, 251, 257, 263, 269, 271, 277, 281,\n            283,\
    \ 293, 307, 311, 313, 317, 331, 337, 347, 349,\n            353, 359, 367, 373,\
    \ 379, 383, 389, 397, 401, 409,\n        };\n        // inv_primes[i] = ceil(2^32\
    \ / primes[i])\n        static constexpr uint32_t inv_primes[MAX_B]{\n       \
    \     2147483648,1431655766, 858993460, 613566757, 390451573, 330382100, 252645136,\
    \ 226050911, 186737709, 148102321,\n            138547333, 116080198, 104755300,\
    \ 99882961, 91382283, 81037119, 72796056, 70409300, 64103990, 60492498,\n    \
    \        58835169, 54366675, 51746594, 48258060, 44278014, 42524429, 41698712,\
    \ 40139882, 39403370, 38008561,\n            33818641, 32786010, 31350127, 30899046,\
    \ 28825284, 28443493, 27356480, 26349493, 25718368, 24826401,\n            23994231,\
    \ 23729102, 22486740, 22253717, 21801865, 21582751, 20355296, 19259944, 18920561,\
    \ 18755316,\n            18433337, 17970575, 17821442, 17111424, 16711936, 16330675,\
    \ 15966422, 15848588, 15505298, 15284582,\n            15176563, 14658592, 13990122,\
    \ 13810185, 13721941, 13548793, 12975733, 12744711, 12377428, 12306497,\n    \
    \        12167047, 11963698, 11702909, 11514658, 11332368, 11214014, 11041048,\
    \ 10818558, 10710642, 10501143,\n        };\n\n        int _p = -1;\n        OrderMod<int>\
    \ _ord;\n        int _a = -1;\n        internal::SystemOfLinearEquations<mint2>\
    \ _eq;\n\n        static int safe_mod(int a, int p) { return ((a %= p) < 0) ?\
    \ a + p : a; }\n\n        static int discrete_log_naive(mint a, mint b, int ord_a)\
    \ {\n            mint pow_a = 1;\n            for (int res = 0; res < ord_a; ++res)\
    \ {\n                if (pow_a == b) return res;\n                pow_a *= a;\n\
    \            }\n            return -1;\n        }\n\n        static bool is_smooth(const\
    \ int B, uint32_t v) {\n            assert(B <= MAX_B);\n            for (int\
    \ i = 0; i < B; ++i) {\n                const uint32_t m = primes[B - i - 1],\
    \ im = inv_primes[B - i - 1];\n                if (uint32_t q = (uint64_t(v) *\
    \ im) >> 32; v == q * m) {\n                    // q = floor(v/m)\n          \
    \          do v = q, q = (uint64_t(v) * im) >> 32; while (v == q * m);\n     \
    \           }\n            }\n            return v == 1;\n        }\n\n      \
    \  static std::optional<std::vector<mint2>> try_factorize(const int B, uint32_t\
    \ v) {\n            assert(B <= MAX_B);\n            if (not is_smooth(B, v))\
    \ return std::nullopt;\n            std::vector<mint2> res(B + 1);\n         \
    \   for (int i = 0; i < B; ++i) {\n                const uint32_t m = primes[B\
    \ - i - 1], im = inv_primes[B - i - 1];\n                int c = 0;\n        \
    \        uint32_t q = (uint64_t(v) * im) >> 32;\n                while (v == q\
    \ * m) {\n                    v = q, q = (uint64_t(v) * im) >> 32;\n         \
    \           ++c;\n                }\n                res[i] = c;\n           \
    \ }\n            res[B] = -1;\n            return res;\n        }\n\n        int\
    \ discrete_log_impl(int a, int b, int p) {\n            a = safe_mod(a, p), b\
    \ = safe_mod(b, p);\n\n            if (b == 0) return a == 0 ? 1 : -1;\n     \
    \       if (b == 1) return 0;\n            if (a == 0) return -1;\n          \
    \  if (a == 1) return -1;\n\n            if (p <= 64) return discrete_log_naive(a,\
    \ b, p - 1);\n\n            const int B = ::pow(p - 1, 1 / (2 * ::sqrt(::log(p\
    \ - 1) / ::log(::log(p - 1))))) + 5;\n            assert(B <= MAX_B);\n\n    \
    \        if (p != _p) {\n                _p = p, _ord = OrderMod<int>(p);\n  \
    \              _a = a, _eq = internal::SystemOfLinearEquations<mint2>(B);\n  \
    \          } else if (a != _a) {\n                _a = a, _eq = internal::SystemOfLinearEquations<mint2>(B);\n\
    \            } else {\n                _eq.change_target();\n            }\n\n\
    \            assert(_ord.is_prime());\n\n            const int ord_a = _ord(a),\
    \ ord_b = _ord(b);\n            if (ord_a % ord_b) return -1;\n            if\
    \ (ord_a <= 64) return discrete_log_naive(a, b, ord_a);\n\n            static\
    \ std::mt19937 rng{};\n            while (true) {\n                const int k\
    \ = rng() % ord_a;\n                auto opt_fac = try_factorize(B, (mint(a).pow(k)\
    \ * b).val());\n                if (not opt_fac) continue;\n                auto&\
    \ fac = *opt_fac;\n                _eq.append(std::move(fac), k);\n          \
    \      if (auto res = _eq.target()) return res->val() % ord_a;\n            }\n\
    \        }\n    };\n\n    namespace internal {\n        using mint = atcoder::dynamic_modint<73495793>;\n\
    \n        // min{ i | 0 <= i < r and a^i = b } or -1\n        int naive(int a,\
    \ int b, int r) {\n            mint pow_a = 1;\n            for (int res = 0;\
    \ res < r; ++res) {\n                if (pow_a == b) return res;\n           \
    \     pow_a *= a;\n            }\n            return -1;\n        }\n\n      \
    \  int pohlig_hellman_prime_power_bsgs(int a, int b, int ord_a, int p, int q)\
    \ {\n            // ord_a = p ^ q\n            if (ord_a <= 64) return naive(a,\
    \ b, ord_a);\n            const mint gamma = mint(a).pow(ord_a / p);\n       \
    \     const mint inv_a = mint(a).inv();\n\n            int x = 0;\n          \
    \  for (int k = 0, pl = 1, pr = ord_a; k < q; ++k) {\n                pr /= p;\n\
    \                int d = suisen::discrete_logarithm_coprime(gamma, (inv_a.pow(x)\
    \ * b).pow(pr));\n                if (d == -1) return -1;\n                x +=\
    \ pl * d;\n                pl *= p;\n            }\n            return x;\n  \
    \      }\n\n        int pohlig_hellman(int a, int b, int p, int q, const OrderMod<int>&\
    \ ord) {\n            // gcd(a, p) = 1\n\n            if (b == 1) return 0;\n\
    \            if (a == 1) return b == 1 ? 0 : -1;\n            if (b % p == 0)\
    \ return -1;\n\n            if (q == 1) {\n                \n                return\
    \ IndexCalculus{ ord }(a, b, p);\n            }\n\n            const int ord_a\
    \ = ord(a);\n            if (ord_a <= 64) return naive(a, b, ord_a);\n       \
    \     if (ord_a % ord(b)) return -1;\n\n            const std::vector<std::pair<int,\
    \ int>> ord_factorized = [&] {\n                std::vector<std::pair<int, int>>\
    \ res;\n                int v = ord_a;\n                for (int p : ord.carmichael_prime_factors())\
    \ if (v % p == 0) {\n                    int& c = res.emplace_back(p, 0).second;\n\
    \                    do v /= p, ++c; while (v % p == 0);\n                }\n\
    \                return res;\n            }();\n\n            std::vector<long\
    \ long> rs, ms;\n            for (auto [p, q] : ord_factorized) {\n          \
    \      int pq = 1;\n                for (int i = 0; i < q; ++i) pq *= p;\n\n \
    \               const int na = mint(a).pow(ord_a / pq).val(), nb = mint(b).pow(ord_a\
    \ / pq).val();\n                const int x = pohlig_hellman_prime_power_bsgs(na,\
    \ nb, pq, p, q);\n                if (x == -1) return -1;\n                rs.push_back(x),\
    \ ms.push_back(pq);\n            }\n            return atcoder::crt(rs, ms).first;\n\
    \        }\n    }\n\n    namespace internal {\n        int discrete_logarithm_coprime(int\
    \ a, int b) {\n            const int m = mint::mod();\n            assert(std::gcd(a,\
    \ m) == 1);\n\n            long long r = 0, md = 1;\n            for (auto [p,\
    \ q] : fast_factorize::factorize(m)) { // CRT\n                int pq = 1;\n \
    \               for (int i = 0; i < q; ++i) pq *= p;\n\n                mint::set_mod(pq);\n\
    \                OrderMod ord(pq);\n                const long long r2 = pohlig_hellman(mint(a).val(),\
    \ mint(b).val(), p, q, ord);\n                if (r2 == -1) return -1;\n\n   \
    \             const long long md2 = ord(a);\n                std::tie(r, md) =\
    \ atcoder::crt({ r, r2 }, { md, md2 });\n                if (md == 0) return -1;\n\
    \            }\n            return r;\n        }\n\n        int discrete_logarithm_arbitrary_mod(int\
    \ a, int b) {\n            const int m = mint::mod();\n\n            if (m ==\
    \ 1 or b == 1) return 0;\n            if (a == 0) return b == 0 ? 1 : b == 1 ?\
    \ 0 : -1;\n            if (a == 1) return b == 1 ? 0 : -1;\n\n            const\
    \ int floor_log2_m = [m] {\n                int res = 0;\n                while\
    \ (1 << (res + 1) <= m) ++res;\n                return res;\n            }();\n\
    \n            if (int i = naive(a, b, floor_log2_m); i != -1) return i;\n\n  \
    \          const int pow_a = mint(a).pow(floor_log2_m).val();\n            const\
    \ int g = std::gcd(pow_a, m);\n            if (b % g) return -1;\n\n         \
    \   mint::set_mod(m / g);\n            const int t = discrete_logarithm_coprime(mint(a).val(),\
    \ (mint(b) / pow_a).val());\n\n            return t != -1 ? floor_log2_m + t :\
    \ -1;\n        }\n    }\n\n    int discrete_logarithm(int a, int b, int m) {\n\
    \        using internal::mint;\n        const int old_mod = mint::mod();\n   \
    \     mint::set_mod(m);\n        const int res = internal::discrete_logarithm_arbitrary_mod(mint(a).val(),\
    \ mint(b).val());\n        mint::set_mod(old_mod);\n        return res;\n    }\n\
    } // namespace suisen\n\n\n#endif // SUISEN_INDEX_CALCULUS\n"
  dependsOn:
  - library/number/fast_factorize.hpp
  - library/type_traits/type_traits.hpp
  - library/number/deterministic_miller_rabin.hpp
  - library/number/montogomery.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  - library/number/order_Z_mZ.hpp
  - library/number/discrete_logarithm.hpp
  isVerificationFile: false
  path: library/number/fast_discrete_logarithm.hpp
  requiredBy: []
  timestamp: '2023-05-27 03:50:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/fast_discrete_logarithm.hpp
layout: document
redirect_from:
- /library/library/number/fast_discrete_logarithm.hpp
- /library/library/number/fast_discrete_logarithm.hpp.html
title: library/number/fast_discrete_logarithm.hpp
---
