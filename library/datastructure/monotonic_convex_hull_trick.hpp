#ifndef SUISEN_MONOTONIC_CHT
#define SUISEN_MONOTONIC_CHT

#include <cassert>
#include <limits>
#include <queue>
#include <type_traits>

namespace suisen {
    namespace internal::monotonic_cht { struct query_tag_base {}; }
    struct inc_query_tag : internal::monotonic_cht::query_tag_base {};
    struct dec_query_tag : internal::monotonic_cht::query_tag_base {};
    struct non_monotonic_query_tag : internal::monotonic_cht::query_tag_base {};

    template <typename T, bool is_min_query, typename QueryTag,
        std::enable_if_t<std::is_base_of_v<internal::monotonic_cht::query_tag_base, QueryTag>, std::nullptr_t> = nullptr
    >
    struct MonotonicCHT {
        using value_type = T;
        using query_tag = QueryTag;

        MonotonicCHT() = default;
    private:
        template <typename, typename = void>
        struct query_impl {};
        template <typename Dummy>
        struct query_impl<inc_query_tag, Dummy> {
            value_type prev_x = std::numeric_limits<value_type>::min();
            value_type operator()(MonotonicCHT* ptr, value_type x) {
                assert(x >= prev_x);
                prev_x = x;
                assert(ptr->lines.size());
                value_type res = ptr->eval(x, 0);
                while (ptr->lines.size() >= 2) {
                    value_type nxt_res = ptr->eval(x, 1);
                    if (res < nxt_res) break;
                    ptr->lines.pop_front();
                    std::swap(res, nxt_res);
                }
                return res;
            }
        };
        template <typename Dummy>
        struct query_impl<dec_query_tag, Dummy> {
            value_type prev_x = std::numeric_limits<value_type>::max();
            value_type operator()(MonotonicCHT* ptr, value_type x) {
                assert(x <= prev_x);
                prev_x = x;
                assert(ptr->lines.size());
                value_type res = ptr->eval(x, ptr->lines.size() - 1);
                while (ptr->lines.size() >= 2) {
                    value_type nxt_res = ptr->eval(x, ptr->lines.size() - 2);
                    if (res < nxt_res) break;
                    ptr->lines.pop_back();
                    std::swap(res, nxt_res);
                }
                return res;
            }
        };
        template <typename Dummy>
        struct query_impl<non_monotonic_query_tag, Dummy> {
            value_type operator()(MonotonicCHT* ptr, value_type x) {
                assert(ptr->lines.size());
                int l = -1, r = ptr->lines.size();
                while (r - l >= 3) {
                    int ml = l + (r - l) / 3;
                    int mr = r - (r - l) / 3;
                    if (ptr->eval(x, ml) < ptr->eval(x, mr)) {
                        r = mr;
                    } else {
                        l = ml;
                    }
                }
                assert(r - l == 2);
                return ptr->eval(x, l + 1);
            }
        };
    public:
        void add_line(value_type slope, value_type intercept) {
            if constexpr (not is_min_query) slope = -slope, intercept = -intercept;
            if (slope <= min_slope) {
                min_slope = slope, max_slope = std::max(max_slope, slope);
                add_right(slope, intercept);
            } else if (slope >= max_slope) {
                max_slope = slope, min_slope = std::min(min_slope, slope);
                add_left(slope, intercept);
            } else assert(false);
        }

        value_type query(value_type x) {
            return (is_min_query ? 1 : -1) * _query(this, x);
        }
    private:
        std::deque<std::pair<value_type, value_type>> lines;
        value_type max_slope = std::numeric_limits<value_type>::min();
        value_type min_slope = std::numeric_limits<value_type>::max();
        query_impl<query_tag> _query{};

        // check if ma * x + mb is necessary.
        bool is_necessary(value_type la, value_type lb, value_type ma, value_type mb, value_type ra, value_type rb) {
            using MultT = std::conditional_t<std::is_integral_v<value_type>, __int128_t, value_type>;
            return MultT(lb - mb) * (ra - ma) > MultT(mb - rb) * (ma - la);
        }

        void add_left(value_type slope, value_type intercept) {
            while (lines.size()) {
                auto it = lines.begin();
                const auto [a, b] = *it;
                if (a == slope) {
                    if (intercept >= b) return;
                } else {
                    if (++it == lines.end() or is_necessary(it->first, it->second, a, b, slope, intercept)) break;
                }
                lines.pop_front();
            }
            lines.emplace_front(slope, intercept);
        }

        void add_right(value_type slope, value_type intercept) {
            while (lines.size()) {
                auto it = lines.rbegin();
                const auto [a, b] = *it;
                if (a == slope) {
                    if (intercept >= b) return;
                } else {
                    if (++it == lines.rend() or is_necessary(slope, intercept, a, b, it->first, it->second)) break;
                }
                lines.pop_back();
            }
            lines.emplace_back(slope, intercept);
        }

        value_type eval(value_type x, int i) {
            const auto& [a, b] = lines[i];
            return a * x + b;
        }
    };

    template <typename T, typename QueryTag>
    using MinMonotonicCHT = MonotonicCHT<T, true, QueryTag>;
    template <typename T, typename QueryTag>
    using MaxMonotonicCHT = MonotonicCHT<T, false, QueryTag>;
} // namespace suisen

#endif // SUISEN_MONOTONIC_CHT
