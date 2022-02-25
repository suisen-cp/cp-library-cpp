---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/number/deterministic_miller_rabin.hpp
    title: Deterministic Miller Rabin
  - icon: ':x:'
    path: library/number/fast_factorize.hpp
    title: Fast Factorize
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "#line 1 \"test/src/number/fast_factorize/factorize.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include <algorithm>\n\
    #include <iostream>\n\n#line 1 \"library/number/fast_factorize.hpp\"\n\n\n\n#include\
    \ <cmath>\n#line 6 \"library/number/fast_factorize.hpp\"\n#include <random>\n\
    #include <numeric>\n\n#line 1 \"library/number/deterministic_miller_rabin.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <iterator>\n\n#line 1\
    \ \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include <type_traits>\n\
    \nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
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
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 9 \"library/number/deterministic_miller_rabin.hpp\"\n\nnamespace suisen::miller_rabin\
    \ {\n    namespace internal {\n        constexpr uint32_t THRESHOLD_1 = 341531U;\n\
    \        constexpr uint64_t BASE_1[] { 9345883071009581737ULL };\n\n        constexpr\
    \ uint32_t THRESHOLD_2 = 1050535501U;\n        constexpr uint64_t BASE_2[] { 336781006125ULL,\
    \ 9639812373923155ULL };\n\n        constexpr uint64_t THRESHOLD_3 = 350269456337ULL;\n\
    \        constexpr uint64_t BASE_3[] { 4230279247111683200ULL, 14694767155120705706ULL,\
    \ 16641139526367750375ULL };\n\n        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;\n\
    \        constexpr uint64_t BASE_4[] { 2ULL, 141889084524735ULL, 1199124725622454117ULL,\
    \ 11096072698276303650ULL };\n\n        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;\n\
    \        constexpr uint64_t BASE_5[] { 2ULL, 4130806001517ULL, 149795463772692060ULL,\
    \ 186635894390467037ULL, 3967304179347715805ULL };\n\n        constexpr uint64_t\
    \ THRESHOLD_6 = 585226005592931977ULL;\n        constexpr uint64_t BASE_6[] {\
    \ 2ULL, 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL,\
    \ 1263739024124850375ULL };\n\n        constexpr uint32_t BASE_7[] { 2U, 325U,\
    \ 9375U, 28178U, 450775U, 9780504U, 1795265022U };\n\n        template <auto BASE,\
    \ std::size_t SIZE, typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        bool miller_rabin(T _n) {\n            using U = std::make_unsigned_t<T>;\n\
    \            using M = safely_multipliable_t<U>;\n\n            U n = _n, d =\
    \ (n - 1) >> __builtin_ctzll(n - 1);\n\n            if (n == 2 or n == 3 or n\
    \ == 5 or n == 7) return true;\n            if (n % 2 == 0 or n % 3 == 0 or n\
    \ % 5 == 0 or n % 7 == 0) return false;\n\n            for (std::size_t i = 0;\
    \ i < SIZE; ++i) {\n                M y = 1, p = BASE[i] % n;\n              \
    \  if (p == 0) continue;\n                for (U d2 = d; d2; d2 >>= 1) {\n   \
    \                 if (d2 & 1) y = y * p % n;\n                    p = p * p %\
    \ n;\n                }\n                if (y == 1) continue;\n             \
    \   for (U t = d; y != n - 1; t <<= 1) {\n                    y = y * y % n;\n\
    \                    if (y == 1 or t == n - 1) return false;\n               \
    \ }\n            }\n            return true;\n        }\n    }\n\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    bool is_prime(T n) {\n        if (n <= 1) return false;\n        using namespace\
    \ internal;\n        if (n < THRESHOLD_1) {\n            return miller_rabin<BASE_1,\
    \ 1>(n);\n        } else if (n < THRESHOLD_2) {\n            return miller_rabin<BASE_2,\
    \ 2>(n);\n        } else if (n < THRESHOLD_3) {\n            return miller_rabin<BASE_3,\
    \ 3>(n);\n        } else if (n < THRESHOLD_4) {\n            return miller_rabin<BASE_4,\
    \ 4>(n);\n        } else if (n < THRESHOLD_5) {\n            return miller_rabin<BASE_5,\
    \ 5>(n);\n        } else if (n < THRESHOLD_6) {\n            return miller_rabin<BASE_6,\
    \ 6>(n);\n        } else {\n            return miller_rabin<BASE_7, 7>(n);\n \
    \       }\n    }\n} // namespace suisen::miller_rabin\n\n\n#line 10 \"library/number/fast_factorize.hpp\"\
    \n\nnamespace suisen::fast_factorize {\n    namespace internal {\n        template\
    \ <typename T>\n        int floor_log2(T n) {\n            int i = 0;\n      \
    \      while (n) n >>= 1, ++i;\n            return i - 1;\n        }\n       \
    \ template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
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
    \ res;\n    }\n} // namespace suisen::fast_factorize\n\n\n#line 7 \"test/src/number/fast_factorize/factorize.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int q;\n    std::cin >> q;\n    while (q --> 0) {\n        long long a;\n\
    \        std::cin >> a;\n        auto fac = suisen::fast_factorize::factorize(a);\n\
    \        std::sort(fac.begin(), fac.end());\n        int pf_num = 0;\n       \
    \ for (const auto &pq : fac) pf_num += pq.second;\n        std::cout << pf_num;\n\
    \        for (const auto &[p, q] : fac) for (int i = 0; i < q; ++i) std::cout\
    \ << ' ' << p;\n        std::cout << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n\n#include \"library/number/fast_factorize.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int q;\n    std::cin >> q;\n    while (q --> 0) {\n        long long a;\n\
    \        std::cin >> a;\n        auto fac = suisen::fast_factorize::factorize(a);\n\
    \        std::sort(fac.begin(), fac.end());\n        int pf_num = 0;\n       \
    \ for (const auto &pq : fac) pf_num += pq.second;\n        std::cout << pf_num;\n\
    \        for (const auto &[p, q] : fac) for (int i = 0; i < q; ++i) std::cout\
    \ << ' ' << p;\n        std::cout << '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/number/fast_factorize.hpp
  - library/number/deterministic_miller_rabin.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/number/fast_factorize/factorize.test.cpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/number/fast_factorize/factorize.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/fast_factorize/factorize.test.cpp
- /verify/test/src/number/fast_factorize/factorize.test.cpp.html
title: test/src/number/fast_factorize/factorize.test.cpp
---
