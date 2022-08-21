#ifndef SUISEN_CHT
#define SUISEN_CHT

#include <cassert>
#include <limits>
#include <set>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
    namespace internal::convex_hull_trick {
        template <typename T>
        struct Line {
            // f(x)=ax+b,m=max{x|f=argmin_{f' in S}{f'(x)}}
            mutable T a, b, m;
            Line(const T& a, const T& b, const T& m) : a(a), b(b), m(m) {}
            bool operator<(const Line<T>& rhs) const { return a < rhs.a; }
            bool operator<(const T& x) const { return not (m < x); }
        };

        template <typename T, std::enable_if_t<std::is_integral<T>::value, std::nullptr_t> = nullptr>
        inline T div(const T& num, const T& den) {
            return num / den - ((num ^ den) < 0 and num % den);
        }
        template <typename T, std::enable_if_t<std::negation<std::is_integral<T>>::value, std::nullptr_t> = nullptr>
        inline T div(const T& num, const T& den) {
            return num / den;
        }
    }

    template <typename T, bool is_min_query = true>
    class ConvexHullTrick : std::multiset<internal::convex_hull_trick::Line<T>, std::less<>> {
        using iterator = typename std::multiset<internal::convex_hull_trick::Line<T>>::iterator;
        using MultT = safely_multipliable_t<T>;
        using Line = internal::convex_hull_trick::Line<T>;

        static constexpr T inf = std::numeric_limits<T>::max();
    public:
        void add_line(T slope, T intercept) {
            if constexpr (not is_min_query) slope = -slope, intercept = -intercept;
            auto it = this->emplace(slope, intercept, inf);
            auto itl = it;
            for (; itl != this->begin();) {
                if (update_intersec_right(--itl, it)) {
                    ++itl;
                    break;
                }
            }
            auto itm = this->erase(itl, it), itr = std::next(itm);
            if (not update_intersec_right(itm, itr)) {
                update_intersec_right(--itm, itr);
            }
            for (it = itm; itr != this->end();) {
                itm = itr++;
                if (itr != this->end() and itm->m <= itr->m) {
                    update_intersec_right(it, itr);
                } else {
                    break;
                }
            }
            if (it != itm) this->erase(std::next(it), itm);
        }

        MultT query(T x) {
            assert(not this->empty());
            const iterator l = --(this-> template lower_bound<T>(x));
            auto res = (MultT) l->a * x + l->b;
            if constexpr (is_min_query) {
                return res;
            } else {
                return -res;
            }
        }
    private:
        // updates r->m and returns whether l is necessary or not.
        bool update_intersec_right(iterator l, iterator r) {
            if (r == this->end()) return true;
            if (l->a == r->a) {
                r->m = r->b <= l->b ? inf : -inf;
            } else {
                r->m = internal::convex_hull_trick::div(r->b - l->b, l->a - r->a);
            }
            return l->m > r->m;
        }
    };
    template <typename T>
    using MinCHT = ConvexHullTrick<T, /* is_min_query = */ true>;
    template <typename T>
    using MaxCHT = ConvexHullTrick<T, /* is_min_query = */ false>;
} // namespace suisen

#endif // SUISEN_CHT
