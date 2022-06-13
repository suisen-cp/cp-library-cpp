#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <random>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp"
using namespace suisen;

template <typename T, int H, int W>
std::vector<T> static_rectangle_add_rectangle_sum_naive(const std::vector<AddQuery<T>>& add_queries, const std::vector<SumQuery>& sum_queries) {
    std::array<std::array<T, H>, W> dat;
    for (auto& row : dat) row.fill(T{ 0 });
    for (const auto& q : add_queries) {
        for (int x = q.l; x < q.r; ++x) for (int y = q.d; y < q.u; ++y) {
            dat[x][y] += q.val;
        }
    }
    std::vector<T> res(sum_queries.size(), T{ 0 });
    for (std::size_t query_id = 0; query_id < sum_queries.size(); ++query_id) {
        const auto& q = sum_queries[query_id];
        mint& ans = res[query_id];
        for (int x = q.l; x < q.r; ++x) for (int y = q.d; y < q.u; ++y) {
            ans += dat[x][y];
        }
    }
    return res;
}

template <int H, int W, int AddQ, int SumQ>
void random_test(uint32_t seed = ~uint32_t(0)) {
    std::mt19937 rng{ seed != ~uint32_t(0) ? seed : std::random_device{}() };

    std::vector<AddQuery<mint>> add_queries(AddQ);
    std::vector<SumQuery> sum_queries(SumQ);

    std::uniform_int_distribution<int> dist_x(0, H - 1), dist_y(0, W - 1), dist_val(0, mint::mod() - 1);

    for (int i = 0; i < AddQ; ++i) {
        int l = dist_x(rng), r = dist_x(rng);
        if (l > r) std::swap(l, r);
        int d = dist_y(rng), u = dist_y(rng);
        if (d > u) std::swap(d, u);
        int val = dist_val(rng);
        add_queries[i] = { l, r, d, u, val };
    }
    for (int i = 0; i < SumQ; ++i) {
        int l = dist_x(rng), r = dist_x(rng);
        if (l > r) std::swap(l, r);
        int d = dist_y(rng), u = dist_y(rng);
        if (d > u) std::swap(d, u);
        sum_queries[i] = { l, r, d, u };
    }

    auto actual = static_rectangle_add_rectangle_sum(add_queries, sum_queries);
    auto expected = static_rectangle_add_rectangle_sum_naive<mint, H, W>(add_queries, sum_queries);
    assert(actual == expected);
}

int main() {
    random_test<1000, 1000, 1000, 1000>();
    std::cout << "Hello World" << std::endl;
    return 0;
}