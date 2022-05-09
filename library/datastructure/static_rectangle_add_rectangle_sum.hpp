#ifndef SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM
#define SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM

#include <atcoder/lazysegtree>

#include "library/util/coordinate_compressor.hpp"

namespace suisen {
    template <typename T>
    struct AddQuery {
        int l, r, d, u;
        T val;
    };
    struct SumQuery {
        int l, r, d, u;
    };

    namespace internal::static_rectangle_add_rectangle_sum {
        template <typename T>
        struct LinearFunction { T a, b; };

        template <typename T>
        struct Data {
            LinearFunction<T> f;
            int len;
        };
        template <typename T>
        Data<T> op(Data<T> x, Data<T> y) {
            return Data<T>{ LinearFunction<T> { x.f.a + y.f.a, x.f.b + y.f.b }, x.len + y.len };
        }
        template <typename T>
        Data<T> e() {
            return Data<T>{ LinearFunction<T> { T{ 0 }, T{ 0 } }, 0 };
        }
        template <typename T>
        Data<T> mapping(LinearFunction<T> f, Data<T> x) {
            return Data<T>{ LinearFunction<T> { x.f.a + x.len * f.a, x.f.b + x.len * f.b }, x.len };
        }
        template <typename T>
        LinearFunction<T> composition(LinearFunction<T> f, LinearFunction<T> g) {
            return LinearFunction<T>{ f.a + g.a, f.b + g.b };
        }
        template <typename T>
        LinearFunction<T> id() {
            return LinearFunction<T>{ T{ 0 }, T{ 0 } };
        };
    }

    template <typename T>
    std::vector<T> static_rectangle_add_rectangle_sum(std::vector<AddQuery<T>> add_queries, std::vector<SumQuery> sum_queries) {
        using namespace internal::static_rectangle_add_rectangle_sum;

        const int add_query_num = add_queries.size(), sum_query_num = sum_queries.size();

        CoordinateCompressorBuilder<int> bx, by;
        for (const auto& add_query : add_queries) {
            bx.push(add_query.l), bx.push(add_query.r);
            by.push(add_query.d), by.push(add_query.u);
        }
        for (const auto& sum_query : sum_queries) {
            bx.push(sum_query.l), bx.push(sum_query.r);
            by.push(sum_query.d), by.push(sum_query.u);
        }
        const auto cmp_x = bx.build(), cmp_y = by.build();

        const int siz_x = cmp_x.size(), siz_y = cmp_y.size();

        std::vector<std::vector<std::tuple<int, int, LinearFunction<T>>>> add_query_bucket(siz_x);
        std::vector<std::vector<std::tuple<int, int, bool, int>>> sum_query_bucket(siz_x);
        for (int i = 0; i < add_query_num; ++i) {
            auto& add_query = add_queries[i];
            add_query.l = cmp_x[add_query.l], add_query.r = cmp_x[add_query.r];
            add_query.d = cmp_y[add_query.d], add_query.u = cmp_y[add_query.u];
            add_query_bucket[add_query.l].emplace_back(
                add_query.d, add_query.u,
                LinearFunction<T>{ add_query.val, add_query.val * -cmp_x.decomp(add_query.l) }
            );
            add_query_bucket[add_query.r].emplace_back(
                add_query.d, add_query.u,
                LinearFunction<T>{ -add_query.val, add_query.val * cmp_x.decomp(add_query.r) }
            );
        }
        for (int i = 0; i < sum_query_num; ++i) {
            auto& sum_query = sum_queries[i];
            sum_query.l = cmp_x[sum_query.l], sum_query.r = cmp_x[sum_query.r];
            sum_query.d = cmp_y[sum_query.d], sum_query.u = cmp_y[sum_query.u];
            sum_query_bucket[sum_query.l].emplace_back(sum_query.d, sum_query.u, /* is_add = */false, i);
            sum_query_bucket[sum_query.r].emplace_back(sum_query.d, sum_query.u, /* is_add = */true, i);
        }

        std::vector<Data<T>> init(siz_y - 1, Data<T>{ id<T>(), 0 });
        for (int i = 0; i < siz_y - 1; ++i) init[i].len = cmp_y.decomp(i + 1) - cmp_y.decomp(i);

        atcoder::lazy_segtree<Data<T>, op<T>, e<T>, LinearFunction<T>, mapping<T>, composition<T>, id<T>> seg(init);

        std::vector<T> res(sum_query_num, T{ 0 });
        for (int i = 0; i < siz_x; ++i) {
            for (const auto& [l, r, is_add, id] : sum_query_bucket[i]) {
                Data<T> dat = seg.prod(l, r);
                T val = dat.f.a * cmp_x.decomp(i) + dat.f.b;
                if (is_add) {
                    res[id] += val;
                } else {
                    res[id] -= val;
                }
            }
            for (const auto& [l, r, f] : add_query_bucket[i]) {
                seg.apply(l, r, f);
            }
        }

        return res;
    }
} // namespace suisen


#endif // SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM
