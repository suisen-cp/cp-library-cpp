---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp
    title: Rectangle Add Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp
    title: Static Rectangle Add Rectangle Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
    title: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
    title: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/dummy.test.cpp
    title: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
    title: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/tuple_ops.hpp\"\n\n\n\n#include <tuple>\n\n\
    namespace suisen {\n    namespace internal::tuple_ops {\n        template <std::size_t\
    \ N, typename F, typename ...Args>\n        std::tuple<Args...>& update(std::tuple<Args...>\
    \ &lhs, F &&fun) {\n            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>)\
    \ return lhs;\n            else return fun(std::get<N>(lhs)), update<N + 1>(lhs,\
    \ std::forward<F>(fun));\n        }\n        template <std::size_t N, typename\
    \ F, typename ...Args>\n        std::tuple<Args...>& merge(std::tuple<Args...>\
    \ &lhs, const std::tuple<Args...>& rhs, F &&fun) {\n            if constexpr (N\
    \ == std::tuple_size_v<std::tuple<Args...>>) return lhs;\n            else return\
    \ fun(std::get<N>(lhs), std::get<N>(rhs)), merge<N + 1>(lhs, rhs, std::forward<F>(fun));\n\
    \        }\n    }\n    template <typename ...Args>\n    std::tuple<Args...>& operator+=(std::tuple<Args...>&\
    \ t1, const std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
    \ t2, [](auto &x, const auto &y) { x += y; });\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...>& operator-=(std::tuple<Args...>& t1, const\
    \ std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
    \ t2, [](auto &x, const auto &y) { x -= y; });\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...> operator+(std::tuple<Args...> t1, const std::tuple<Args...>&\
    \ t2) { return std::move(t1 += t2); }\n    template <typename ...Args>\n    std::tuple<Args...>\
    \ operator-(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1\
    \ -= t2); }\n    \n    template <typename V, typename ...Args>\n    std::tuple<Args...>&\
    \ operator*=(std::tuple<Args...>& t1, const V &v) { return internal::tuple_ops::update<0>(t1,\
    \ [&v](auto &x) { x *= v; }); }\n    template <typename V, typename ...Args>\n\
    \    std::tuple<Args...>& operator/=(std::tuple<Args...>& t1, const V &v) { return\
    \ internal::tuple_ops::update<0>(t1, [&v](auto &x) { x /= v; }); }\n\n    template\
    \ <typename V, typename ...Args>\n    std::tuple<Args...> operator*(const V &v,\
    \ std::tuple<Args...> t1) { return std::move(t1 *= v); }\n    template <typename\
    \ V, typename ...Args>\n    std::tuple<Args...> operator*(std::tuple<Args...>\
    \ t1, const V &v) { return std::move(t1 *= v); }\n    template <typename V, typename\
    \ ...Args>\n    std::tuple<Args...> operator/(std::tuple<Args...> t1, const V\
    \ &v) { return std::move(t1 /= v); }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_TUPLE_OPS\n#define SUISEN_TUPLE_OPS\n\n#include <tuple>\n\n\
    namespace suisen {\n    namespace internal::tuple_ops {\n        template <std::size_t\
    \ N, typename F, typename ...Args>\n        std::tuple<Args...>& update(std::tuple<Args...>\
    \ &lhs, F &&fun) {\n            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>)\
    \ return lhs;\n            else return fun(std::get<N>(lhs)), update<N + 1>(lhs,\
    \ std::forward<F>(fun));\n        }\n        template <std::size_t N, typename\
    \ F, typename ...Args>\n        std::tuple<Args...>& merge(std::tuple<Args...>\
    \ &lhs, const std::tuple<Args...>& rhs, F &&fun) {\n            if constexpr (N\
    \ == std::tuple_size_v<std::tuple<Args...>>) return lhs;\n            else return\
    \ fun(std::get<N>(lhs), std::get<N>(rhs)), merge<N + 1>(lhs, rhs, std::forward<F>(fun));\n\
    \        }\n    }\n    template <typename ...Args>\n    std::tuple<Args...>& operator+=(std::tuple<Args...>&\
    \ t1, const std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
    \ t2, [](auto &x, const auto &y) { x += y; });\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...>& operator-=(std::tuple<Args...>& t1, const\
    \ std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
    \ t2, [](auto &x, const auto &y) { x -= y; });\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...> operator+(std::tuple<Args...> t1, const std::tuple<Args...>&\
    \ t2) { return std::move(t1 += t2); }\n    template <typename ...Args>\n    std::tuple<Args...>\
    \ operator-(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1\
    \ -= t2); }\n    \n    template <typename V, typename ...Args>\n    std::tuple<Args...>&\
    \ operator*=(std::tuple<Args...>& t1, const V &v) { return internal::tuple_ops::update<0>(t1,\
    \ [&v](auto &x) { x *= v; }); }\n    template <typename V, typename ...Args>\n\
    \    std::tuple<Args...>& operator/=(std::tuple<Args...>& t1, const V &v) { return\
    \ internal::tuple_ops::update<0>(t1, [&v](auto &x) { x /= v; }); }\n\n    template\
    \ <typename V, typename ...Args>\n    std::tuple<Args...> operator*(const V &v,\
    \ std::tuple<Args...> t1) { return std::move(t1 *= v); }\n    template <typename\
    \ V, typename ...Args>\n    std::tuple<Args...> operator*(std::tuple<Args...>\
    \ t1, const V &v) { return std::move(t1 *= v); }\n    template <typename V, typename\
    \ ...Args>\n    std::tuple<Args...> operator/(std::tuple<Args...> t1, const V\
    \ &v) { return std::move(t1 /= v); }\n} // namespace suisen\n\n#endif // SUISEN_TUPLE_OPS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/tuple_ops.hpp
  requiredBy:
  - library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp
  - library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp
  timestamp: '2022-05-07 15:41:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
  - test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/dummy.test.cpp
  - test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
  - test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
documentation_of: library/util/tuple_ops.hpp
layout: document
title: Tuple Ops
---
## Tuple Ops