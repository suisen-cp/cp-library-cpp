#ifndef SUISEN_DEFAULT_OPERATOR
#define SUISEN_DEFAULT_OPERATOR

namespace suisen {
    namespace default_operator {
        template <typename T>
        auto zero() -> decltype(T { 0 }) { return T { 0 }; }
        template <typename T>
        auto one()  -> decltype(T { 1 }) { return T { 1 }; }
        template <typename T>
        auto add(const T &x, const T &y) -> decltype(x + y) { return x + y; }
        template <typename T>
        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }
        template <typename T>
        auto mul(const T &x, const T &y) -> decltype(x * y) { return x * y; }
        template <typename T>
        auto div(const T &x, const T &y) -> decltype(x / y) { return x / y; }
        template <typename T>
        auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }
        template <typename T>
        auto neg(const T &x) -> decltype(-x) { return -x; }
        template <typename T>
        auto inv(const T &x) -> decltype(one<T>() / x)  { return one<T>() / x; }
    } // default_operator
} // namespace suisen

#endif // SUISEN_DEFAULT_OPERATOR
