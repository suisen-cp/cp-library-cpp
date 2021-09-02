#ifndef SUISEN_MONOTONIC_CHT
#define SUISEN_MONOTONIC_CHT

#include <cassert>
#include <limits>
#include <queue>

#include "library/type_traits/type_traits.hpp"

namespace suisen {

template <typename T, bool is_min_query = true>
class MonotonicCHT {
    using MultT = safely_multipliable_t<T>;

    public:
        MonotonicCHT() {}
    
        void add_line(T slope, T intercept) {
            if constexpr (not is_min_query) {
                slope = -slope;
                intercept = -intercept;
            }
            if (slope <= min_slope) {
                min_slope = slope;
                max_slope = std::max(max_slope, slope);
                add_right(slope, intercept);
            } else if (slope >= max_slope) {
                max_slope = slope;
                min_slope = std::min(min_slope, slope);
                add_left(slope, intercept);
            } else assert(false);
        }

        MultT query(T x) const {
            assert(not (called_ascending_query or called_descending_query));
            called_general_query = true;
            assert(lines.size() > 0);
            int l = -1, r = lines.size();
            while (r - l >= 3) {
                int ml = l + (r - l) / 3;
                int mr = r - (r - l) / 3;
                if (eval(x, ml) < eval(x, mr)) {
                    r = mr;
                } else {
                    l = ml;
                }
            }
            assert(r - l == 2);
            MultT res = eval(l + 1);
            return is_min_query ? res : -res;
        }

        MultT ascending_query(T x) {
            assert(not (called_general_query or called_descending_query));
            if (not called_ascending_query) {
                prev_query = x;
                called_ascending_query = true;
            }
            assert(x >= prev_query);
            prev_query = x;
            assert(lines.size() > 0);
            MultT res = eval(x, 0);
            while (lines.size() >= 2) {
                MultT nxt_res = eval(x, 1);
                if (res < nxt_res) break;
                lines.pop_front();
                std::swap(res, nxt_res);
            }
            return is_min_query ? res : -res;
        }

        MultT descending_query(T x) {
            assert(not (called_general_query or called_ascending_query));
            if (not called_descending_query) {
                prev_query = x;
                called_descending_query = true;
            }
            assert(x <= prev_query);
            prev_query = x;
            assert(lines.size() > 0);
            MultT res = eval(x, lines.size() - 1);
            while (lines.size() >= 2) {
                MultT nxt_res = eval(x, lines.size() - 2);
                if (res < nxt_res) break;
                lines.pop_back();
                std::swap(res, nxt_res);
            }
            return is_min_query ? res : -res;
        }

    private:
        std::deque<std::pair<T, T>> lines;
        T max_slope = std::numeric_limits<T>::min();
        T min_slope = std::numeric_limits<T>::max();

        bool called_general_query = false;
        bool called_ascending_query = false;
        bool called_descending_query = false;

        T prev_query = 0;

        // check if ma * x + mb is necessary.
        bool is_necessary(T la, T lb, T ma, T mb, T ra, T rb) {
            return (MultT) (lb - mb) * (ra - ma) > (MultT) (mb - rb) * (ma - la);
        }

        void add_left(T slope, T intercept) {
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

        void add_right(T slope, T intercept) {
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

        MultT eval(T x, int i) {
            const auto &[a, b] = lines[i];
            return (MultT) a * x + b;
        }
};

} // namespace suisen

#endif // SUISEN_MONOTONIC_CHT
