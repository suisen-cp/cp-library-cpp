---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':x:'
    path: library/number/order_prime_mod.hpp
    title: Order Prime Mod
  - icon: ':x:'
    path: library/number/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: library/number/tetration_mod.hpp
    title: $a\uparrow\uparrow b \bmod m$
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/number/fast_factorize/factorize.test.cpp
    title: test/src/number/fast_factorize/factorize.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/dummy.test.cpp
    title: test/src/number/primitive_root/dummy.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/primitive_root.test.cpp
    title: test/src/number/primitive_root/primitive_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/tetration_mod/tetration_mod.test.cpp
    title: test/src/number/tetration_mod/tetration_mod.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/deterministic_miller_rabin.hpp\"\n\n\n\n\
    #include <cassert>\n#include <cstdint>\n#include <iterator>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    \        }\n    }\n} // namespace suisen::miller_rabin\n\n\n"
  code: "#ifndef SUISEN_DETERMINISTIC_MILLER_RABIN\n#define SUISEN_DETERMINISTIC_MILLER_RABIN\n\
    \n#include <cassert>\n#include <cstdint>\n#include <iterator>\n\n#include \"library/type_traits/type_traits.hpp\"\
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
    \        }\n    }\n} // namespace suisen::miller_rabin\n\n#endif // SUISEN_DETERMINISTIC_MILLER_RABIN\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/number/deterministic_miller_rabin.hpp
  requiredBy:
  - library/number/primitive_root.hpp
  - library/number/tetration_mod.hpp
  - library/number/fast_factorize.hpp
  - library/number/order_prime_mod.hpp
  timestamp: '2022-09-28 21:34:37+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/number/tetration_mod/tetration_mod.test.cpp
  - test/src/number/fast_factorize/factorize.test.cpp
  - test/src/number/primitive_root/dummy.test.cpp
  - test/src/number/primitive_root/primitive_root.test.cpp
documentation_of: library/number/deterministic_miller_rabin.hpp
layout: document
title: Deterministic Miller Rabin
---
## Deterministic Miller Rabin