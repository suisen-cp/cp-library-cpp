#ifndef SUISEN_HAS_OPERATOR
#define SUISEN_HAS_OPERATOR

#include <type_traits>

namespace suisen {
#define HAS_BINARY_OPERATOR(op, op_name) \
    namespace internal::type_traits { \
        template <typename LHS, typename RHS> \
        struct impl_has_operator_##op_name { \
            template <typename LHS2, typename RHS2> \
            static auto test(LHS2*) -> decltype(std::declval<LHS2>() op std::declval<RHS2>()); \
            template <typename, typename> \
            static auto test(...) -> std::false_type; \
            using type = typename std::negation<std::is_same<std::false_type, decltype(test<LHS, RHS>(nullptr))>>::type; \
        }; \
    } \
    template <typename LHS, typename RHS = LHS> \
    struct has_operator_##op_name: internal::type_traits::impl_has_operator_##op_name<LHS, RHS>::type {}; \
    template <typename LHS, typename RHS = LHS> \
    constexpr bool has_operator_##op_name##_v = has_operator_##op_name<LHS, RHS>::value;

#define HAS_UNARY_OPERATOR(op, op_name) \
    namespace internal::type_traits { \
        template <typename T> \
        struct impl_has_operator_##op_name { \
            template <typename U> \
            static auto test(U*) -> decltype(op std::declval<U>()); \
            template <typename> \
            static auto test(...) -> std::false_type; \
            using type = typename std::negation<std::is_same<std::false_type, decltype(test<T>(nullptr))>>::type; \
        }; \
    } \
    template <typename T> \
    struct has_operator_##op_name: internal::type_traits::impl_has_operator_##op_name<T>::type {}; \
    template <typename T> \
    constexpr bool has_operator_##op_name##_v = has_operator_##op_name<T>::value;

    HAS_UNARY_OPERATOR(-, negate)
    HAS_BINARY_OPERATOR(+, plus)
    HAS_BINARY_OPERATOR(-, minus)
    HAS_BINARY_OPERATOR(*, multiplies)
    HAS_BINARY_OPERATOR(/ , divides)
    HAS_BINARY_OPERATOR(%, modulus)

    HAS_UNARY_OPERATOR(~, bit_not)
    HAS_BINARY_OPERATOR(&, bit_and)
    HAS_BINARY_OPERATOR(| , bit_or)
    HAS_BINARY_OPERATOR(^, bit_xor)

    HAS_UNARY_OPERATOR(!, logical_not)
    HAS_BINARY_OPERATOR(&&, logical_and)
    HAS_BINARY_OPERATOR(|| , logical_or)

    HAS_BINARY_OPERATOR(==, equal_to)
    HAS_BINARY_OPERATOR(!=, not_equal_to)
    HAS_BINARY_OPERATOR(<, less)
    HAS_BINARY_OPERATOR(<=, less_equal)
    HAS_BINARY_OPERATOR(>, greater)
    HAS_BINARY_OPERATOR(>=, greater_equal)

#undef HAS_UNARY_OPERATOR
#undef HAS_BINARY_OPERATOR
} // namespace suisen

#endif // SUISEN_HAS_OPERATOR
