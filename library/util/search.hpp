#include <cassert>
#include <cstdint>
#include <functional>
#include <type_traits>

namespace suisen {
    enum class ternary_search_tag { Convex, Concave };

    /**
     * @brief 
     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave if f is concave
     * @param l min argument
     * @param r max argument
     * @param num number of loops determined by the required accuracy.
     * @param f convex/concave function
     * @return argmin_{l<=x<=r} f(x) if f is convex, argmax_{l<=x<=r} f(x) if f is concave
     */
    template <ternary_search_tag tag, typename Arg, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>, std::is_floating_point<Arg>>, std::nullptr_t> = nullptr>
    Arg ternary_search_key(Arg l, Arg r, std::size_t num, const Fun &f) {
        assert(l <= r);
        const auto compare = std::conditional_t<tag == ternary_search_tag::Convex, std::greater<>, std::less<>>{};
        while (num--) {
            const Arg ml = l + (r - l) / 3, mr = r - (r - l) / 3;
            if (compare(f(ml), f(mr))) l = ml;
            else r = mr;
        }
        return l;
    }

    /**
     * @brief 
     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave if f is concave
     * @param l min argument
     * @param r max argument
     * @param f convex/concave function
     * @return argmin_{l<=x<=r} f(x) if f is convex, argmax_{l<=x<=r} f(x) if f is concave
     */
    template <ternary_search_tag tag, typename Arg, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>
    Arg ternary_search_key(Arg l, Arg r, const Fun &f) {
        assert(l <= r);
        const auto compare = std::conditional_t<tag == ternary_search_tag::Convex, std::greater<>, std::less<>>{};
        while (r - l >= 3) {
            const Arg ml = l + (r - l) / 3, mr = r - (r - l) / 3;
            if (compare(f(ml), f(mr))) l = ml;
            else r = mr;
        }
        Arg x = l;
        auto fx = f(x);
        for (Arg y = l + 1; y <= r; ++y) {
            if (auto fy = f(y); compare(fx, fy)) x = y, fx = fy;
        }
        return x;
    }

    /**
     * @brief 
     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave if f is concave
     * @param l min argument
     * @param r max argument
     * @param num number of loops determined by the required accuracy.
     * @param f convex/concave function
     * @return min_{l<=x<=r} f(x) if f is convex, max_{l<=x<=r} f(x) if f is concave
     */
    template <ternary_search_tag tag, typename Arg, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>, std::is_floating_point<Arg>>, std::nullptr_t> = nullptr>
    std::invoke_result_t<Fun, Arg> ternary_search_value(const Arg &l, const Arg &r, const std::size_t &num, const Fun &f) {
        return f(ternary_search_key<tag>(l, r, num, f));
    }

    /**
     * @brief 
     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave if f is concave
     * @param l min argument
     * @param r max argument
     * @param f convex/concave function
     * @return min_{l<=x<=r} f(x) if f is convex, max_{l<=x<=r} f(x) if f is concave
     */
    template <ternary_search_tag tag, typename Arg, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>
    Arg ternary_search_value(Arg l, Arg r, const Fun &f) {
        return f(ternary_search_key<tag>(l, r, f));
    }

    /**
     * @brief 
     * @param l_ng f(l_ng) must be false
     * @param r_ok f(r_ok) must be true
     * @param f non-decreasing predicate function
     * @return min x s.t. f(x) is true
     */
    template <typename Arg, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool, Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>
    Arg binary_search(Arg l_ng, Arg r_ok, const Fun &f) {
        assert(l_ng <= r_ok);
        assert(not f(l_ng));
        assert(f(r_ok));
        while ((r_ok - l_ng) > 1) {
            Arg m = l_ng + ((r_ok - l_ng) >> 1);
            (f(m) ? r_ok : l_ng) = m;
        }
        return r_ok;
    }

    /**
     * @brief 
     * @param l_ng f(l_ng) must be false
     * @param f non-decreasing predicate function
     * @return min x s.t. f(x) is true
     */
    template <typename Arg, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool, Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>
    Arg binary_search_exponential(Arg l_ng, const Fun &f) {
        assert(not f(l_ng));
        Arg w = 1;
        while (not f(l_ng + w)) w <<= 1;
        Arg r_ok = l_ng + w;
        while ((r_ok - l_ng) > 1) {
            Arg m = l_ng + ((r_ok - l_ng) >> 1);
            (f(m) ? r_ok : l_ng) = m;
        }
        return r_ok;
    }
} // namespace suisen
