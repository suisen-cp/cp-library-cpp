---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/util/divide_both.test.cpp
    title: test/src/number/util/divide_both.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/util.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <tuple>\n#include <vector>\n#line\
    \ 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 10\
    \ \"library/number/util.hpp\"\n\nnamespace suisen {\n\n// Returns pow(-1, n)\n\
    template <typename T>\nconstexpr inline int pow_m1(T n) {\n    return -(n & 1)\
    \ | 1;\n}\n// Returns pow(-1, n)\ntemplate <>\nconstexpr inline int pow_m1<bool>(bool\
    \ n) {\n    return -int(n) | 1;\n}\n\n// Returns floor(x / y)\ntemplate <typename\
    \ T>\nconstexpr inline T fld(const T x, const T y) {\n    return (x ^ y) >= 0\
    \ ? x / y : (x - (y + pow_m1(y >= 0))) / y;\n}\n// Returns ceil(x / y)\ntemplate\
    \ <typename T>\nconstexpr inline T cld(const T x, const T y) {\n    return (x\
    \ ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n}\n\n/**\n * O(sqrt(n))\n\
    \ * Returns a vector of { prime, index }. \n * It is guaranteed that `prime` is\
    \ ascending.\n */\ntemplate <typename T>\nstd::vector<std::pair<T, int>> factorize(T\
    \ n) {\n    assert(0 < n);\n    std::vector<std::pair<T, int>> prime_powers;\n\
    \    int c2 = 0;\n    while ((n & 1) == 0) ++c2, n >>= 1;\n    if (c2) prime_powers.emplace_back(2,\
    \ c2);\n    for (T p = 3; p * p <= n; p += 2) {\n        int cp = 0;\n       \
    \ while (n % p == 0) n /= p, ++cp;\n        if (cp) prime_powers.emplace_back(p,\
    \ cp);\n    }\n    if (n > 1) prime_powers.emplace_back(n, 1);\n    return prime_powers;\n\
    }\n\n/**\n * O(sqrt(n))\n * Returns a vector that contains all divisors of `n`\
    \ in ascending order.\n */\ntemplate <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\nstd::vector<T> divisors(T n) {\n    assert(0 < n);\n    std::vector<T>\
    \ l, r;\n    for (T p = 1; p * p <= n; ++p) {\n        if (n % p) continue;\n\
    \        l.push_back(p);\n        if (T q = n / p; p != q) r.push_back(q);\n \
    \   }\n    for (auto it = r.rbegin(); it != r.rend(); ++it) l.push_back(*it);\n\
    \    return l;\n}\n\n/**\n * O(sigma(n))\n * Returns a vector that contains all\
    \ divisors of `n`.\n * It is NOT guaranteed that the vector is sorted.\n */\n\
    template <typename T>\nstd::vector<T> divisors(const std::vector<std::pair<T,\
    \ int>> &factorized) {\n    std::vector<T> res { 1 };\n    for (auto [p, c] :\
    \ factorized) {\n        for (int i = 0, sz = res.size(); i < sz; ++i) {\n   \
    \         T d = res[i];\n            for (int j = 0; j < c; ++j) res.push_back(d\
    \ *= p);\n        }\n    }\n    return res;\n}\n\n/**\n * O(sqrt(n)).\n * Returns\
    \ vector of { l : T, r : T, q : T } s.t. let S be { d | n / d = q }, l = min S\
    \ and r = max S.\n * It is guaranteed that `l`, `r` is ascending (i.e. `q` is\
    \ descending).\n */\ntemplate <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\nauto enumerate_quotients(T n) {\n    assert(0 <= n);\n    std::vector<std::tuple<T,\
    \ T, T>> res;\n    for (T l = 1, r = 1; l <= n; l = r + 1) {\n        T q = n\
    \ / l;\n        res.emplace_back(l, r = n / q, q);\n    }\n    return res;\n}\n\
    \n/**\n * Template Parameter:\n *  - vector<T> or array<T, N>\n * \n * Time Complexity:\
    \ O(|vs| * Sum_{v in vs} sqrt(v))\n * \n * Returns vector of { l : T, r : T, qs\
    \ : Container } s.t. let S be { d | vs[i] / d = qs[i] (for all i) }, l = min S\
    \ and r = max S\n * It is guaranteed that `l`, `r` is ascending (i.e. for all\
    \ `i`, `q[i]` is descending).\n */\ntemplate <typename Container>\nstd::vector<std::tuple<typename\
    \ Container::value_type, typename Container::value_type, Container>>\nenumerate_multiple_quotients(const\
    \ Container &vs) {\n    using T = typename Container::value_type;\n    static_assert(std::is_integral_v<T>);\n\
    \    int n = vs.size();\n    T max_val = *std::max_element(vs.begin(), vs.end());\n\
    \    assert(*std::min_element(vs.begin(), vs.end()) >= 0);\n    std::vector<std::tuple<T,\
    \ T, Container>> res;\n    for (T l = 1, r = 1; l <= max_val; l = r + 1) {\n \
    \       Container qs;\n        if constexpr (std::is_same_v<Container, std::vector<T>>)\
    \ qs.resize(n);\n        r = std::numeric_limits<T>::max();\n        for (int\
    \ i = 0; i < n; ++i) {\n            qs[i] = vs[i] / l;\n            r = std::min(r,\
    \ qs[i] == 0 ? std::numeric_limits<T>::max() : vs[i] / qs[i]);\n        }\n  \
    \      res.emplace_back(l, r, std::move(qs));\n    }\n    return res;\n}\n\n}\
    \ // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_NUMBER_UTIL\n#define SUISEN_NUMBER_UTIL\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <tuple>\n#include <vector>\n#include\
    \ \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\n// Returns\
    \ pow(-1, n)\ntemplate <typename T>\nconstexpr inline int pow_m1(T n) {\n    return\
    \ -(n & 1) | 1;\n}\n// Returns pow(-1, n)\ntemplate <>\nconstexpr inline int pow_m1<bool>(bool\
    \ n) {\n    return -int(n) | 1;\n}\n\n// Returns floor(x / y)\ntemplate <typename\
    \ T>\nconstexpr inline T fld(const T x, const T y) {\n    return (x ^ y) >= 0\
    \ ? x / y : (x - (y + pow_m1(y >= 0))) / y;\n}\n// Returns ceil(x / y)\ntemplate\
    \ <typename T>\nconstexpr inline T cld(const T x, const T y) {\n    return (x\
    \ ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n}\n\n/**\n * O(sqrt(n))\n\
    \ * Returns a vector of { prime, index }. \n * It is guaranteed that `prime` is\
    \ ascending.\n */\ntemplate <typename T>\nstd::vector<std::pair<T, int>> factorize(T\
    \ n) {\n    assert(0 < n);\n    std::vector<std::pair<T, int>> prime_powers;\n\
    \    int c2 = 0;\n    while ((n & 1) == 0) ++c2, n >>= 1;\n    if (c2) prime_powers.emplace_back(2,\
    \ c2);\n    for (T p = 3; p * p <= n; p += 2) {\n        int cp = 0;\n       \
    \ while (n % p == 0) n /= p, ++cp;\n        if (cp) prime_powers.emplace_back(p,\
    \ cp);\n    }\n    if (n > 1) prime_powers.emplace_back(n, 1);\n    return prime_powers;\n\
    }\n\n/**\n * O(sqrt(n))\n * Returns a vector that contains all divisors of `n`\
    \ in ascending order.\n */\ntemplate <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\nstd::vector<T> divisors(T n) {\n    assert(0 < n);\n    std::vector<T>\
    \ l, r;\n    for (T p = 1; p * p <= n; ++p) {\n        if (n % p) continue;\n\
    \        l.push_back(p);\n        if (T q = n / p; p != q) r.push_back(q);\n \
    \   }\n    for (auto it = r.rbegin(); it != r.rend(); ++it) l.push_back(*it);\n\
    \    return l;\n}\n\n/**\n * O(sigma(n))\n * Returns a vector that contains all\
    \ divisors of `n`.\n * It is NOT guaranteed that the vector is sorted.\n */\n\
    template <typename T>\nstd::vector<T> divisors(const std::vector<std::pair<T,\
    \ int>> &factorized) {\n    std::vector<T> res { 1 };\n    for (auto [p, c] :\
    \ factorized) {\n        for (int i = 0, sz = res.size(); i < sz; ++i) {\n   \
    \         T d = res[i];\n            for (int j = 0; j < c; ++j) res.push_back(d\
    \ *= p);\n        }\n    }\n    return res;\n}\n\n/**\n * O(sqrt(n)).\n * Returns\
    \ vector of { l : T, r : T, q : T } s.t. let S be { d | n / d = q }, l = min S\
    \ and r = max S.\n * It is guaranteed that `l`, `r` is ascending (i.e. `q` is\
    \ descending).\n */\ntemplate <typename T, constraints_t<std::is_integral<T>>\
    \ = nullptr>\nauto enumerate_quotients(T n) {\n    assert(0 <= n);\n    std::vector<std::tuple<T,\
    \ T, T>> res;\n    for (T l = 1, r = 1; l <= n; l = r + 1) {\n        T q = n\
    \ / l;\n        res.emplace_back(l, r = n / q, q);\n    }\n    return res;\n}\n\
    \n/**\n * Template Parameter:\n *  - vector<T> or array<T, N>\n * \n * Time Complexity:\
    \ O(|vs| * Sum_{v in vs} sqrt(v))\n * \n * Returns vector of { l : T, r : T, qs\
    \ : Container } s.t. let S be { d | vs[i] / d = qs[i] (for all i) }, l = min S\
    \ and r = max S\n * It is guaranteed that `l`, `r` is ascending (i.e. for all\
    \ `i`, `q[i]` is descending).\n */\ntemplate <typename Container>\nstd::vector<std::tuple<typename\
    \ Container::value_type, typename Container::value_type, Container>>\nenumerate_multiple_quotients(const\
    \ Container &vs) {\n    using T = typename Container::value_type;\n    static_assert(std::is_integral_v<T>);\n\
    \    int n = vs.size();\n    T max_val = *std::max_element(vs.begin(), vs.end());\n\
    \    assert(*std::min_element(vs.begin(), vs.end()) >= 0);\n    std::vector<std::tuple<T,\
    \ T, Container>> res;\n    for (T l = 1, r = 1; l <= max_val; l = r + 1) {\n \
    \       Container qs;\n        if constexpr (std::is_same_v<Container, std::vector<T>>)\
    \ qs.resize(n);\n        r = std::numeric_limits<T>::max();\n        for (int\
    \ i = 0; i < n; ++i) {\n            qs[i] = vs[i] / l;\n            r = std::min(r,\
    \ qs[i] == 0 ? std::numeric_limits<T>::max() : vs[i] / qs[i]);\n        }\n  \
    \      res.emplace_back(l, r, std::move(qs));\n    }\n    return res;\n}\n\n}\
    \ // namespace suisen\n\n#endif // SUISEN_NUMBER_UTIL\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/number/util.hpp
  requiredBy: []
  timestamp: '2021-08-04 18:37:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/util/divide_both.test.cpp
documentation_of: library/number/util.hpp
layout: document
redirect_from:
- /library/library/number/util.hpp
- /library/library/number/util.hpp.html
title: library/number/util.hpp
---
