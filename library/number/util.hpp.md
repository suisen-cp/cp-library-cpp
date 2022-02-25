---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/util/abc222_g.test.cpp
    title: test/src/number/util/abc222_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/util/divide_both.test.cpp
    title: test/src/number/util/divide_both.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/util/same_div_dens.test.cpp
    title: test/src/number/util/same_div_dens.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/util.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <optional>\n#include <tuple>\n\
    #include <vector>\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate\
    \ <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 11 \"library/number/util.hpp\"\n\nnamespace suisen {\n\n    // // Returns pow(-1,\
    \ n)\n    // template <typename T>\n    // constexpr inline int pow_m1(T n) {\n\
    \    //     return -(n & 1) | 1;\n    // }\n    // // Returns pow(-1, n)\n   \
    \ // template <>\n    // constexpr inline int pow_m1<bool>(bool n) {\n    // \
    \    return -int(n) | 1;\n    // }\n\n    // // Returns floor(x / y)\n    // template\
    \ <typename T>\n    // constexpr inline T fld(const T x, const T y) {\n    //\
    \     return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) / y;\n    // }\n\
    \    // // Returns ceil(x / y)\n    // template <typename T>\n    // constexpr\
    \ inline T cld(const T x, const T y) {\n    //     return (x ^ y) <= 0 ? x / y\
    \ : (x + (y + pow_m1(y >= 0))) / y;\n    // }\n\n    /**\n     * O(sqrt(n))\n\
    \     * Returns a vector of { prime, index }.\n     * It is guaranteed that `prime`\
    \ is ascending.\n     */\n    template <typename T>\n    std::vector<std::pair<T,\
    \ int>> factorize(T n) {\n        static constexpr std::array primes{ 2, 3, 5,\
    \ 7, 11, 13 };\n        static constexpr int next_prime = 17;\n        static\
    \ constexpr int siz = std::array{ 1, 2, 8, 48, 480, 5760, 92160 } [primes.size()\
    \ - 1] ;\n        static constexpr int period = [] {\n            int res = 1;\n\
    \            for (auto e : primes) res *= e;\n            return res;\n      \
    \  }();\n        static constexpr struct S : public std::array<int, siz> {\n \
    \           constexpr S() {\n                for (int i = next_prime, j = 0; i\
    \ < period + next_prime; i += 2) {\n                    bool ok = true;\n    \
    \                for (int p : primes) ok &= i % p > 0;\n                    if\
    \ (ok) (*this)[j++] = i - next_prime;\n                }\n            }\n    \
    \    } s{};\n\n        assert(n > 0);\n        std::vector<std::pair<T, int>>\
    \ res;\n        auto f = [&res, &n](int p) {\n            if (n % p) return;\n\
    \            int cnt = 0;\n            do n /= p, ++cnt; while (n % p == 0);\n\
    \            res.emplace_back(p, cnt);\n        };\n        for (int p : primes)\
    \ f(p);\n        for (T b = next_prime; b * b <= n; b += period) {\n         \
    \   for (int offset : s) f(b + offset);\n        }\n        if (n != 1) res.emplace_back(n,\
    \ 1);\n        return res;\n    }\n\n    /**\n     * O(sigma(n))\n     * Returns\
    \ a vector that contains all divisors of `n`.\n     * It is NOT guaranteed that\
    \ the vector is sorted.\n     */\n    template <typename T>\n    std::vector<T>\
    \ divisors(const std::vector<std::pair<T, int>>& factorized) {\n        std::vector<T>\
    \ res{ 1 };\n        for (auto [p, c] : factorized) {\n            for (int i\
    \ = 0, sz = res.size(); i < sz; ++i) {\n                T d = res[i];\n      \
    \          for (int j = 0; j < c; ++j) res.push_back(d *= p);\n            }\n\
    \        }\n        return res;\n    }\n\n    /**\n     * O(sqrt(n))\n     * Returns\
    \ a vector that contains all divisors of `n`.\n     * It is NOT guaranteed that\
    \ the vector is sorted.\n     */\n    template <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\n    std::vector<T> divisors(T n) {\n        return divisors(factorize(n));\n\
    \    }\n\n    template <typename T>\n    T totient(T n) {\n        for (const\
    \ auto& [p, _] : factorize(n)) n /= p, n *= p - 1;\n        return n;\n    }\n\
    \n    // Returns { l, r } := min_max { x>0 | fld(n,x)=q }.\n    template <typename\
    \ T, constraints_t<std::is_integral<T>> = nullptr>\n    std::optional<std::pair<T,\
    \ T>> same_fld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max())\
    \ {\n        T l, r;\n        if (q >= 0) {\n            if (n < 0) return std::nullopt;\n\
    \            // cld(n + 1, q + 1) <= x <= fld(n, q)\n            l = (n + 1 +\
    \ q) / (q + 1), r = q == 0 ? max_val : std::min(max_val, n / q);\n        } else\
    \ {\n            if (n >= 0) return std::nullopt;\n            // cld(n, q) <=\
    \ x <= fld(n + 1, q + 1)\n            l = (n + q + 1) / q, r = q == -1 ? max_val\
    \ : std::min(max_val, (n + 1) / (q + 1));\n        }\n        if (l <= r) return\
    \ std::make_pair(l, r);\n        else        return std::nullopt;\n    }\n   \
    \ // Returns { l, r } := min_max { x<0 | fld(n,x)=q }.\n    template <typename\
    \ T, constraints_t<std::is_integral<T>> = nullptr>\n    std::optional<std::pair<T,\
    \ T>> same_fld_denominators_negative(T n, T q, T min_val = std::numeric_limits<T>::min())\
    \ {\n        T l, r;\n        if (q >= 0) {\n            if (n > 0) return std::nullopt;\n\
    \            // cld(n, q) <= x <= fld(n - 1, q + 1)\n            l = q == 0 ?\
    \ min_val : std::max(min_val, n / q), r = (n - 1 - q) / (q + 1);\n        } else\
    \ {\n            if (n <= 0) return std::nullopt;\n            // cld(n - 1, q\
    \ + 1) <= x <= fld(n, q)\n            l = q == -1 ? min_val : std::max(min_val,\
    \ (n - 1) / (q + 1)), r = (n - q - 1) / q;\n        }\n        if (l <= r) return\
    \ std::make_pair(l, r);\n        else        return std::nullopt;\n    }\n   \
    \ // Returns { l, r } := min_max { x>0 | cld(n,x)=q }.\n    template <typename\
    \ T, constraints_t<std::is_integral<T>> = nullptr>\n    std::optional<std::pair<T,\
    \ T>> same_cld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max())\
    \ {\n        T l, r;\n        if (q > 0) {\n            if (n <= 0) return std::nullopt;\n\
    \            l = (n + q - 1) / q, r = q == 1 ? max_val : std::min(max_val, (n\
    \ - 1) / (q - 1));\n        } else {\n            if (n > 0) return std::nullopt;\n\
    \            l = (n - 1 + q) / (q - 1), r = q == 0 ? max_val : std::min(max_val,\
    \ n / q);\n        }\n        if (l <= r) return std::make_pair(l, r);\n     \
    \   else        return std::nullopt;\n    }\n    // Returns { l, r } := min_max\
    \ { x<0 | cld(n,x)=q }.\n    template <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\n    std::optional<std::pair<T, T>> same_cld_denominators_negative(T\
    \ n, T q, T min_val = std::numeric_limits<T>::min()) {\n        T l, r;\n    \
    \    if (q > 0) {\n            if (n >= 0) return std::nullopt;\n            l\
    \ = q == 1 ? min_val : std::max(min_val, (n + 1) / (q - 1)), r = (n - q + 1) /\
    \ q;\n        } else {\n            if (n < 0) return std::nullopt;\n        \
    \    l = q == 0 ? min_val : std::max(min_val, n / q), r = (n + 1 - q) / (q - 1);\n\
    \        }\n        if (l <= r) return std::make_pair(l, r);\n        else   \
    \     return std::nullopt;\n    }\n\n    /**\n     * O(sqrt(n)).\n     * Returns\
    \ vector of { l : T, r : T, q : T } s.t. let S be { d | n / d = q }, l = min S\
    \ and r = max S.\n     * It is guaranteed that `l`, `r` is ascending (i.e. `q`\
    \ is descending).\n     */\n    template <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\n    auto enumerate_quotients(T n) {\n        assert(0 <= n);\n \
    \       std::vector<std::tuple<T, T, T>> res;\n        for (T l = 1, r = 1; l\
    \ <= n; l = r + 1) {\n            T q = n / l;\n            res.emplace_back(l,\
    \ r = n / q, q);\n        }\n        return res;\n    }\n\n    /**\n     * Template\
    \ Parameter:\n     *  - vector<T> or array<T, N>\n     *\n     * Time Complexity:\
    \ O(|vs| * Sum_{v in vs} sqrt(v))\n     *\n     * Returns vector of { l : T, r\
    \ : T, qs : Container } s.t. let S be { d | vs[i] / d = qs[i] (for all i) }, l\
    \ = min S and r = max S\n     * It is guaranteed that `l`, `r` is ascending (i.e.\
    \ for all `i`, `q[i]` is descending).\n     */\n    template <typename Container>\n\
    \    std::vector<std::tuple<typename Container::value_type, typename Container::value_type,\
    \ Container>>\n        enumerate_multiple_quotients(const Container& vs) {\n \
    \       using T = typename Container::value_type;\n        static_assert(std::is_integral_v<T>);\n\
    \        int n = vs.size();\n        T max_val = *std::max_element(vs.begin(),\
    \ vs.end());\n        assert(*std::min_element(vs.begin(), vs.end()) >= 0);\n\
    \        std::vector<std::tuple<T, T, Container>> res;\n        for (T l = 1,\
    \ r = 1; l <= max_val; l = r + 1) {\n            Container qs;\n            if\
    \ constexpr (std::is_same_v<Container, std::vector<T>>) qs.resize(n);\n      \
    \      r = std::numeric_limits<T>::max();\n            for (int i = 0; i < n;\
    \ ++i) {\n                qs[i] = vs[i] / l;\n                r = std::min(r,\
    \ qs[i] == 0 ? std::numeric_limits<T>::max() : vs[i] / qs[i]);\n            }\n\
    \            res.emplace_back(l, r, std::move(qs));\n        }\n        return\
    \ res;\n    }\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_NUMBER_UTIL\n#define SUISEN_NUMBER_UTIL\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <optional>\n#include <tuple>\n\
    #include <vector>\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace\
    \ suisen {\n\n    // // Returns pow(-1, n)\n    // template <typename T>\n   \
    \ // constexpr inline int pow_m1(T n) {\n    //     return -(n & 1) | 1;\n   \
    \ // }\n    // // Returns pow(-1, n)\n    // template <>\n    // constexpr inline\
    \ int pow_m1<bool>(bool n) {\n    //     return -int(n) | 1;\n    // }\n\n   \
    \ // // Returns floor(x / y)\n    // template <typename T>\n    // constexpr inline\
    \ T fld(const T x, const T y) {\n    //     return (x ^ y) >= 0 ? x / y : (x -\
    \ (y + pow_m1(y >= 0))) / y;\n    // }\n    // // Returns ceil(x / y)\n    //\
    \ template <typename T>\n    // constexpr inline T cld(const T x, const T y) {\n\
    \    //     return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n  \
    \  // }\n\n    /**\n     * O(sqrt(n))\n     * Returns a vector of { prime, index\
    \ }.\n     * It is guaranteed that `prime` is ascending.\n     */\n    template\
    \ <typename T>\n    std::vector<std::pair<T, int>> factorize(T n) {\n        static\
    \ constexpr std::array primes{ 2, 3, 5, 7, 11, 13 };\n        static constexpr\
    \ int next_prime = 17;\n        static constexpr int siz = std::array{ 1, 2, 8,\
    \ 48, 480, 5760, 92160 } [primes.size() - 1] ;\n        static constexpr int period\
    \ = [] {\n            int res = 1;\n            for (auto e : primes) res *= e;\n\
    \            return res;\n        }();\n        static constexpr struct S : public\
    \ std::array<int, siz> {\n            constexpr S() {\n                for (int\
    \ i = next_prime, j = 0; i < period + next_prime; i += 2) {\n                \
    \    bool ok = true;\n                    for (int p : primes) ok &= i % p > 0;\n\
    \                    if (ok) (*this)[j++] = i - next_prime;\n                }\n\
    \            }\n        } s{};\n\n        assert(n > 0);\n        std::vector<std::pair<T,\
    \ int>> res;\n        auto f = [&res, &n](int p) {\n            if (n % p) return;\n\
    \            int cnt = 0;\n            do n /= p, ++cnt; while (n % p == 0);\n\
    \            res.emplace_back(p, cnt);\n        };\n        for (int p : primes)\
    \ f(p);\n        for (T b = next_prime; b * b <= n; b += period) {\n         \
    \   for (int offset : s) f(b + offset);\n        }\n        if (n != 1) res.emplace_back(n,\
    \ 1);\n        return res;\n    }\n\n    /**\n     * O(sigma(n))\n     * Returns\
    \ a vector that contains all divisors of `n`.\n     * It is NOT guaranteed that\
    \ the vector is sorted.\n     */\n    template <typename T>\n    std::vector<T>\
    \ divisors(const std::vector<std::pair<T, int>>& factorized) {\n        std::vector<T>\
    \ res{ 1 };\n        for (auto [p, c] : factorized) {\n            for (int i\
    \ = 0, sz = res.size(); i < sz; ++i) {\n                T d = res[i];\n      \
    \          for (int j = 0; j < c; ++j) res.push_back(d *= p);\n            }\n\
    \        }\n        return res;\n    }\n\n    /**\n     * O(sqrt(n))\n     * Returns\
    \ a vector that contains all divisors of `n`.\n     * It is NOT guaranteed that\
    \ the vector is sorted.\n     */\n    template <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\n    std::vector<T> divisors(T n) {\n        return divisors(factorize(n));\n\
    \    }\n\n    template <typename T>\n    T totient(T n) {\n        for (const\
    \ auto& [p, _] : factorize(n)) n /= p, n *= p - 1;\n        return n;\n    }\n\
    \n    // Returns { l, r } := min_max { x>0 | fld(n,x)=q }.\n    template <typename\
    \ T, constraints_t<std::is_integral<T>> = nullptr>\n    std::optional<std::pair<T,\
    \ T>> same_fld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max())\
    \ {\n        T l, r;\n        if (q >= 0) {\n            if (n < 0) return std::nullopt;\n\
    \            // cld(n + 1, q + 1) <= x <= fld(n, q)\n            l = (n + 1 +\
    \ q) / (q + 1), r = q == 0 ? max_val : std::min(max_val, n / q);\n        } else\
    \ {\n            if (n >= 0) return std::nullopt;\n            // cld(n, q) <=\
    \ x <= fld(n + 1, q + 1)\n            l = (n + q + 1) / q, r = q == -1 ? max_val\
    \ : std::min(max_val, (n + 1) / (q + 1));\n        }\n        if (l <= r) return\
    \ std::make_pair(l, r);\n        else        return std::nullopt;\n    }\n   \
    \ // Returns { l, r } := min_max { x<0 | fld(n,x)=q }.\n    template <typename\
    \ T, constraints_t<std::is_integral<T>> = nullptr>\n    std::optional<std::pair<T,\
    \ T>> same_fld_denominators_negative(T n, T q, T min_val = std::numeric_limits<T>::min())\
    \ {\n        T l, r;\n        if (q >= 0) {\n            if (n > 0) return std::nullopt;\n\
    \            // cld(n, q) <= x <= fld(n - 1, q + 1)\n            l = q == 0 ?\
    \ min_val : std::max(min_val, n / q), r = (n - 1 - q) / (q + 1);\n        } else\
    \ {\n            if (n <= 0) return std::nullopt;\n            // cld(n - 1, q\
    \ + 1) <= x <= fld(n, q)\n            l = q == -1 ? min_val : std::max(min_val,\
    \ (n - 1) / (q + 1)), r = (n - q - 1) / q;\n        }\n        if (l <= r) return\
    \ std::make_pair(l, r);\n        else        return std::nullopt;\n    }\n   \
    \ // Returns { l, r } := min_max { x>0 | cld(n,x)=q }.\n    template <typename\
    \ T, constraints_t<std::is_integral<T>> = nullptr>\n    std::optional<std::pair<T,\
    \ T>> same_cld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max())\
    \ {\n        T l, r;\n        if (q > 0) {\n            if (n <= 0) return std::nullopt;\n\
    \            l = (n + q - 1) / q, r = q == 1 ? max_val : std::min(max_val, (n\
    \ - 1) / (q - 1));\n        } else {\n            if (n > 0) return std::nullopt;\n\
    \            l = (n - 1 + q) / (q - 1), r = q == 0 ? max_val : std::min(max_val,\
    \ n / q);\n        }\n        if (l <= r) return std::make_pair(l, r);\n     \
    \   else        return std::nullopt;\n    }\n    // Returns { l, r } := min_max\
    \ { x<0 | cld(n,x)=q }.\n    template <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\n    std::optional<std::pair<T, T>> same_cld_denominators_negative(T\
    \ n, T q, T min_val = std::numeric_limits<T>::min()) {\n        T l, r;\n    \
    \    if (q > 0) {\n            if (n >= 0) return std::nullopt;\n            l\
    \ = q == 1 ? min_val : std::max(min_val, (n + 1) / (q - 1)), r = (n - q + 1) /\
    \ q;\n        } else {\n            if (n < 0) return std::nullopt;\n        \
    \    l = q == 0 ? min_val : std::max(min_val, n / q), r = (n + 1 - q) / (q - 1);\n\
    \        }\n        if (l <= r) return std::make_pair(l, r);\n        else   \
    \     return std::nullopt;\n    }\n\n    /**\n     * O(sqrt(n)).\n     * Returns\
    \ vector of { l : T, r : T, q : T } s.t. let S be { d | n / d = q }, l = min S\
    \ and r = max S.\n     * It is guaranteed that `l`, `r` is ascending (i.e. `q`\
    \ is descending).\n     */\n    template <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\n    auto enumerate_quotients(T n) {\n        assert(0 <= n);\n \
    \       std::vector<std::tuple<T, T, T>> res;\n        for (T l = 1, r = 1; l\
    \ <= n; l = r + 1) {\n            T q = n / l;\n            res.emplace_back(l,\
    \ r = n / q, q);\n        }\n        return res;\n    }\n\n    /**\n     * Template\
    \ Parameter:\n     *  - vector<T> or array<T, N>\n     *\n     * Time Complexity:\
    \ O(|vs| * Sum_{v in vs} sqrt(v))\n     *\n     * Returns vector of { l : T, r\
    \ : T, qs : Container } s.t. let S be { d | vs[i] / d = qs[i] (for all i) }, l\
    \ = min S and r = max S\n     * It is guaranteed that `l`, `r` is ascending (i.e.\
    \ for all `i`, `q[i]` is descending).\n     */\n    template <typename Container>\n\
    \    std::vector<std::tuple<typename Container::value_type, typename Container::value_type,\
    \ Container>>\n        enumerate_multiple_quotients(const Container& vs) {\n \
    \       using T = typename Container::value_type;\n        static_assert(std::is_integral_v<T>);\n\
    \        int n = vs.size();\n        T max_val = *std::max_element(vs.begin(),\
    \ vs.end());\n        assert(*std::min_element(vs.begin(), vs.end()) >= 0);\n\
    \        std::vector<std::tuple<T, T, Container>> res;\n        for (T l = 1,\
    \ r = 1; l <= max_val; l = r + 1) {\n            Container qs;\n            if\
    \ constexpr (std::is_same_v<Container, std::vector<T>>) qs.resize(n);\n      \
    \      r = std::numeric_limits<T>::max();\n            for (int i = 0; i < n;\
    \ ++i) {\n                qs[i] = vs[i] / l;\n                r = std::min(r,\
    \ qs[i] == 0 ? std::numeric_limits<T>::max() : vs[i] / qs[i]);\n            }\n\
    \            res.emplace_back(l, r, std::move(qs));\n        }\n        return\
    \ res;\n    }\n\n} // namespace suisen\n\n#endif // SUISEN_NUMBER_UTIL\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/number/util.hpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/util/divide_both.test.cpp
  - test/src/number/util/abc222_g.test.cpp
  - test/src/number/util/same_div_dens.test.cpp
documentation_of: library/number/util.hpp
layout: document
title: Util
---
## Util