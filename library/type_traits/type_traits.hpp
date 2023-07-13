#ifndef SUISEN_TYPE_TRITS
#define SUISEN_TYPE_TRITS

#include <limits>
#include <type_traits>

namespace suisen {
template <typename ...Types>
using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;
template <bool cond_v, typename Then, typename OrElse>
constexpr decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {
    if constexpr (cond_v) return std::forward<Then>(then);
    else return std::forward<OrElse>(or_else);
}

// ! function
template <typename ReturnType, typename Callable, typename ...Args>
using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;
template <typename F, typename T>
using is_uni_op = is_same_as_invoke_result<T, F, T>;
template <typename F, typename T>
using is_bin_op = is_same_as_invoke_result<T, F, T, T>;

template <typename Comparator, typename T>
using is_comparator = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;

// ! integral
template <typename T, typename = constraints_t<std::is_integral<T>>>
constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;
template <typename T, size_t n> struct is_nbit { static constexpr bool value = bit_num<T> == n; };
template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T, n>::value;

// ?
template <typename T> struct safely_multipliable {};
template <> struct safely_multipliable<int> { using type = long long; };
template <> struct safely_multipliable<long long> { using type = __int128_t; };
template <> struct safely_multipliable<unsigned int> { using type = unsigned long long; };
template <> struct safely_multipliable<unsigned long int> { using type = __uint128_t; };
template <> struct safely_multipliable<unsigned long long> { using type = __uint128_t; };
template <> struct safely_multipliable<float> { using type = float; };
template <> struct safely_multipliable<double> { using type = double; };
template <> struct safely_multipliable<long double> { using type = long double; };
template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;

template <typename T, typename = void> struct rec_value_type { using type = T; };
template <typename T> struct rec_value_type<T, std::void_t<typename T::value_type>> {
    using type = typename rec_value_type<typename T::value_type>::type;
};
template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;

template <typename T> class is_iterable {
    template <typename T_>
    static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});
    static std::false_type test(...);
public:
    static constexpr bool value = decltype(test(std::declval<T>()))::value;
};
template <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;

template <typename T> class is_writable {
    template <typename T_>
    static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});
    static std::false_type test(...);
public:
    static constexpr bool value = decltype(test(std::declval<T>()))::value;
};
template <typename T> static constexpr bool is_writable_v = is_writable<T>::value;

template <typename T> class is_readable {
    template <typename T_>
    static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});
    static std::false_type test(...);
public:
    static constexpr bool value = decltype(test(std::declval<T>()))::value;
};
template <typename T> static constexpr bool is_readable_v = is_readable<T>::value;
} // namespace suisen

#endif // SUISEN_TYPE_TRITS