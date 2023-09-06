#ifndef SUISEN_ITER_UTILS
#define SUISEN_ITER_UTILS

#include <algorithm>
#include <array>
#include <type_traits>

namespace suisen {
    template <typename, typename ...Ints>
    class product_range {
        static constexpr std::size_t D = sizeof...(Ints);
        struct iterator {
            std::array<int, D> ns, values;
            bool done;

            iterator(const std::array<int, D>& ns) : ns(ns), values{}, done(*std::min_element(ns.begin(), ns.end()) <= 0) {}

            const std::array<int, D>& operator*() const { return values; }
            bool operator!=(std::nullptr_t) const { return not done; }
            iterator& operator++() { return succ(), *this; }
            template <std::size_t I = D - 1>
            void succ() {
                if constexpr (I == ~std::size_t(0)) {
                    done = true;
                } else if (++values[I] == ns[I]) {
                    values[I] = 0;
                    succ<I - 1>();
                }
            }
        };
        std::array<int, D> ns;
    public:
        product_range(const Ints &...ns) : ns{ static_cast<int>(ns)... } {}
        auto begin() const { return iterator{ns}; }
        auto end() const { return nullptr; }
    };
    template <typename ...Ints>
    product_range(const Ints &...) -> product_range<std::enable_if_t<std::conjunction_v<std::bool_constant<(sizeof...(Ints) > 0)>, std::is_integral<Ints>...>>, Ints...>;
} // namespace suisen

#endif // SUISEN_ITER_UTILS
