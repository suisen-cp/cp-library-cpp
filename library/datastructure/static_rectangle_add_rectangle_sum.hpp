#ifndef SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM
#define SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM

#include "library/datastructure/fenwick_tree.hpp"
#include "library/util/tuple_ops.hpp"

namespace suisen {
    template <typename T>
    struct AddQuery {
        int l, r, d, u;
        T val;
        AddQuery() = default;
        AddQuery(int l, int r, int d, int u, const T &val) : l(l), r(r), d(d), u(u), val(val) {}
    };
    struct SumQuery {
        int l, r, d, u;
        SumQuery() = default;
        SumQuery(int l, int r, int d, int u) : l(l), r(r), d(d), u(u) {}
    };

    template <typename T>
    std::vector<T> static_rectangle_add_rectangle_sum(const std::vector<AddQuery<T>>& add_queries, const std::vector<SumQuery>& sum_queries) {
        using suffix_add_query_type = std::tuple<int, int, T>;         // l, d, val
        using prefix_sum_query_type = std::tuple<int, int, int, bool>; // r, u, query_id, sign

        std::vector<int> ys;
        std::vector<suffix_add_query_type> suf_add_queries;
        for (const auto& q : add_queries) {
            ys.push_back(q.d), ys.push_back(q.u);
            suf_add_queries.emplace_back(q.l, q.d, q.val), suf_add_queries.emplace_back(q.r, q.d, -q.val);
            suf_add_queries.emplace_back(q.l, q.u, -q.val), suf_add_queries.emplace_back(q.r, q.u, q.val);
        }

        std::sort(ys.begin(), ys.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
        auto compress = [&ys](int y) -> int { return std::lower_bound(ys.begin(), ys.end(), y) - ys.begin(); };

        std::vector<prefix_sum_query_type> pre_sum_queries;
        for (std::size_t i = 0; i < sum_queries.size(); ++i) {
            const auto& q = sum_queries[i];
            pre_sum_queries.emplace_back(q.l, q.d, i, true), pre_sum_queries.emplace_back(q.r, q.d, i, false);
            pre_sum_queries.emplace_back(q.l, q.u, i, false), pre_sum_queries.emplace_back(q.r, q.u, i, true);
        }

        static constexpr auto x_comparator = [](const auto& q1, const auto& q2) { return std::get<0>(q1) < std::get<0>(q2); };
        std::sort(suf_add_queries.begin(), suf_add_queries.end(), x_comparator);
        std::sort(pre_sum_queries.begin(), pre_sum_queries.end(), x_comparator);

        using data_type = std::tuple<T, T, T, T>;
        FenwickTree<data_type> ft(ys.size());

        std::vector<T> res(sum_queries.size(), T{ 0 });
        const int n = suf_add_queries.size(), m = pre_sum_queries.size();
        for (int i = 0, j = 0; i < n or j < m;) {
            if (j == m or (i < n and std::get<0>(suf_add_queries[i]) < std::get<0>(pre_sum_queries[j]))) {
                const auto& [l, d, v] = suf_add_queries[i++];
                // v * (x - l) * (y - d) = v * xy - vd * x - vl * y + vld
                ft.add(compress(d), data_type{ v, -v * d, -v * l, v * l * d });
            } else {
                const auto& [x, y, qid, is_add] = pre_sum_queries[j++];
                auto [a, b, c, d] = ft.sum(0, compress(y));
                const T sum = a * x * y + b * x + c * y + d;
                if (is_add) res[qid] += sum;
                else        res[qid] -= sum;
            }
        }
        return res;
    }
} // namespace suisen


#endif // SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM
