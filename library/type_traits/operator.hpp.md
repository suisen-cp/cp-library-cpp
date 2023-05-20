---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
    title: Reversible Implicit Treap Dual Segtree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
    title: Reversible Implicit Treap Lazy Segtree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/type_traits/operator.hpp\"\n\n\n\n#include <type_traits>\n\
    \nnamespace suisen {\n#define HAS_BINARY_OPERATOR(op, op_name) \\\n    namespace\
    \ internal::type_traits { \\\n        template <typename LHS, typename RHS> \\\
    \n        struct impl_has_operator_##op_name { \\\n            template <typename\
    \ LHS2, typename RHS2> \\\n            static auto test(LHS2*) -> decltype(std::declval<LHS2>()\
    \ op std::declval<RHS2>()); \\\n            template <typename, typename> \\\n\
    \            static auto test(...) -> std::false_type; \\\n            using type\
    \ = typename std::negation<std::is_same<std::false_type, decltype(test<LHS, RHS>(nullptr))>>::type;\
    \ \\\n        }; \\\n    } \\\n    template <typename LHS, typename RHS = LHS>\
    \ \\\n    struct has_operator_##op_name: internal::type_traits::impl_has_operator_##op_name<LHS,\
    \ RHS>::type {}; \\\n    template <typename LHS, typename RHS = LHS> \\\n    constexpr\
    \ bool has_operator_##op_name##_v = has_operator_##op_name<LHS, RHS>::value;\n\
    \n#define HAS_UNARY_OPERATOR(op, op_name) \\\n    namespace internal::type_traits\
    \ { \\\n        template <typename T> \\\n        struct impl_has_operator_##op_name\
    \ { \\\n            template <typename U> \\\n            static auto test(U*)\
    \ -> decltype(op std::declval<U>()); \\\n            template <typename> \\\n\
    \            static auto test(...) -> std::false_type; \\\n            using type\
    \ = typename std::negation<std::is_same<std::false_type, decltype(test<T>(nullptr))>>::type;\
    \ \\\n        }; \\\n    } \\\n    template <typename T> \\\n    struct has_operator_##op_name:\
    \ internal::type_traits::impl_has_operator_##op_name<T>::type {}; \\\n    template\
    \ <typename T> \\\n    constexpr bool has_operator_##op_name##_v = has_operator_##op_name<T>::value;\n\
    \n    HAS_UNARY_OPERATOR(-, negate)\n    HAS_BINARY_OPERATOR(+, plus)\n    HAS_BINARY_OPERATOR(-,\
    \ minus)\n    HAS_BINARY_OPERATOR(*, multiplies)\n    HAS_BINARY_OPERATOR(/ ,\
    \ divides)\n    HAS_BINARY_OPERATOR(%, modulus)\n\n    HAS_UNARY_OPERATOR(~, bit_not)\n\
    \    HAS_BINARY_OPERATOR(&, bit_and)\n    HAS_BINARY_OPERATOR(| , bit_or)\n  \
    \  HAS_BINARY_OPERATOR(^, bit_xor)\n\n    HAS_UNARY_OPERATOR(!, logical_not)\n\
    \    HAS_BINARY_OPERATOR(&&, logical_and)\n    HAS_BINARY_OPERATOR(|| , logical_or)\n\
    \n    HAS_BINARY_OPERATOR(==, equal_to)\n    HAS_BINARY_OPERATOR(!=, not_equal_to)\n\
    \    HAS_BINARY_OPERATOR(<, less)\n    HAS_BINARY_OPERATOR(<=, less_equal)\n \
    \   HAS_BINARY_OPERATOR(>, greater)\n    HAS_BINARY_OPERATOR(>=, greater_equal)\n\
    \n#undef HAS_UNARY_OPERATOR\n#undef HAS_BINARY_OPERATOR\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_HAS_OPERATOR\n#define SUISEN_HAS_OPERATOR\n\n#include <type_traits>\n\
    \nnamespace suisen {\n#define HAS_BINARY_OPERATOR(op, op_name) \\\n    namespace\
    \ internal::type_traits { \\\n        template <typename LHS, typename RHS> \\\
    \n        struct impl_has_operator_##op_name { \\\n            template <typename\
    \ LHS2, typename RHS2> \\\n            static auto test(LHS2*) -> decltype(std::declval<LHS2>()\
    \ op std::declval<RHS2>()); \\\n            template <typename, typename> \\\n\
    \            static auto test(...) -> std::false_type; \\\n            using type\
    \ = typename std::negation<std::is_same<std::false_type, decltype(test<LHS, RHS>(nullptr))>>::type;\
    \ \\\n        }; \\\n    } \\\n    template <typename LHS, typename RHS = LHS>\
    \ \\\n    struct has_operator_##op_name: internal::type_traits::impl_has_operator_##op_name<LHS,\
    \ RHS>::type {}; \\\n    template <typename LHS, typename RHS = LHS> \\\n    constexpr\
    \ bool has_operator_##op_name##_v = has_operator_##op_name<LHS, RHS>::value;\n\
    \n#define HAS_UNARY_OPERATOR(op, op_name) \\\n    namespace internal::type_traits\
    \ { \\\n        template <typename T> \\\n        struct impl_has_operator_##op_name\
    \ { \\\n            template <typename U> \\\n            static auto test(U*)\
    \ -> decltype(op std::declval<U>()); \\\n            template <typename> \\\n\
    \            static auto test(...) -> std::false_type; \\\n            using type\
    \ = typename std::negation<std::is_same<std::false_type, decltype(test<T>(nullptr))>>::type;\
    \ \\\n        }; \\\n    } \\\n    template <typename T> \\\n    struct has_operator_##op_name:\
    \ internal::type_traits::impl_has_operator_##op_name<T>::type {}; \\\n    template\
    \ <typename T> \\\n    constexpr bool has_operator_##op_name##_v = has_operator_##op_name<T>::value;\n\
    \n    HAS_UNARY_OPERATOR(-, negate)\n    HAS_BINARY_OPERATOR(+, plus)\n    HAS_BINARY_OPERATOR(-,\
    \ minus)\n    HAS_BINARY_OPERATOR(*, multiplies)\n    HAS_BINARY_OPERATOR(/ ,\
    \ divides)\n    HAS_BINARY_OPERATOR(%, modulus)\n\n    HAS_UNARY_OPERATOR(~, bit_not)\n\
    \    HAS_BINARY_OPERATOR(&, bit_and)\n    HAS_BINARY_OPERATOR(| , bit_or)\n  \
    \  HAS_BINARY_OPERATOR(^, bit_xor)\n\n    HAS_UNARY_OPERATOR(!, logical_not)\n\
    \    HAS_BINARY_OPERATOR(&&, logical_and)\n    HAS_BINARY_OPERATOR(|| , logical_or)\n\
    \n    HAS_BINARY_OPERATOR(==, equal_to)\n    HAS_BINARY_OPERATOR(!=, not_equal_to)\n\
    \    HAS_BINARY_OPERATOR(<, less)\n    HAS_BINARY_OPERATOR(<=, less_equal)\n \
    \   HAS_BINARY_OPERATOR(>, greater)\n    HAS_BINARY_OPERATOR(>=, greater_equal)\n\
    \n#undef HAS_UNARY_OPERATOR\n#undef HAS_BINARY_OPERATOR\n} // namespace suisen\n\
    \n#endif // SUISEN_HAS_OPERATOR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/type_traits/operator.hpp
  requiredBy:
  - library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  timestamp: '2023-02-16 15:43:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
documentation_of: library/type_traits/operator.hpp
layout: document
title: Operator
---
## Operator
