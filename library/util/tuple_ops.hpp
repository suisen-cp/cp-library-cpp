#ifndef SUISEN_TUPLE_OPS
#define SUISEN_TUPLE_OPS

#include <tuple>

namespace suisen {
    namespace internal::tuple_ops {
        template <std::size_t N, typename F, typename ...Args>
        std::tuple<Args...>& update(std::tuple<Args...> &lhs, F &&fun) {
            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>) return lhs;
            else return fun(std::get<N>(lhs)), update<N + 1>(lhs, std::forward<F>(fun));
        }
        template <std::size_t N, typename F, typename ...Args>
        std::tuple<Args...>& merge(std::tuple<Args...> &lhs, const std::tuple<Args...>& rhs, F &&fun) {
            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>) return lhs;
            else return fun(std::get<N>(lhs), std::get<N>(rhs)), merge<N + 1>(lhs, rhs, std::forward<F>(fun));
        }
    }
    template <typename ...Args>
    std::tuple<Args...>& operator+=(std::tuple<Args...>& t1, const std::tuple<Args...>& t2) {
        return internal::tuple_ops::merge<0>(t1, t2, [](auto &x, const auto &y) { x += y; });
    }
    template <typename ...Args>
    std::tuple<Args...>& operator-=(std::tuple<Args...>& t1, const std::tuple<Args...>& t2) {
        return internal::tuple_ops::merge<0>(t1, t2, [](auto &x, const auto &y) { x -= y; });
    }
    template <typename ...Args>
    std::tuple<Args...> operator+(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1 += t2); }
    template <typename ...Args>
    std::tuple<Args...> operator-(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1 -= t2); }
    
    template <typename V, typename ...Args>
    std::tuple<Args...>& operator*=(std::tuple<Args...>& t1, const V &v) { return internal::tuple_ops::update<0>(t1, [&v](auto &x) { x *= v; }); }
    template <typename V, typename ...Args>
    std::tuple<Args...>& operator/=(std::tuple<Args...>& t1, const V &v) { return internal::tuple_ops::update<0>(t1, [&v](auto &x) { x /= v; }); }

    template <typename V, typename ...Args>
    std::tuple<Args...> operator*(const V &v, std::tuple<Args...> t1) { return std::move(t1 *= v); }
    template <typename V, typename ...Args>
    std::tuple<Args...> operator*(std::tuple<Args...> t1, const V &v) { return std::move(t1 *= v); }
    template <typename V, typename ...Args>
    std::tuple<Args...> operator/(std::tuple<Args...> t1, const V &v) { return std::move(t1 /= v); }
} // namespace suisen

#endif // SUISEN_TUPLE_OPS
