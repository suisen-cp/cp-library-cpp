#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <random>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp"
using suisen::RectangleAddRectangleSum;

template <typename T, int H, int W>
struct RectangleAddRectangleSumNaive {
    using value_type = T;
    RectangleAddRectangleSumNaive() {
        for (auto& row : _dat) row.fill(T{ 0 });
    }

    void add(int l, int r, int d, int u, const value_type& val) {
        for (int x = l; x < r; ++x) for (int y = d; y < u; ++y) _dat[x][y] += val;
    }

    value_type sum(int l, int r, int d, int u) const {
        value_type res{ 0 };
        for (int x = l; x < r; ++x) for (int y = d; y < u; ++y) res += _dat[x][y];
        return res;
    }
private:
    std::array<std::array<value_type, H>, W> _dat;
};


template <int H, int W, int Q>
void random_test(uint32_t seed = ~uint32_t(0)) {
    std::mt19937 rng{ seed != ~uint32_t(0) ? seed : std::random_device{}() };

    RectangleAddRectangleSumNaive<mint, H, W> sol1;
    RectangleAddRectangleSum<mint> sol2(H);

    using query_t = std::tuple<int, int, int, int, int>;

    std::vector<query_t> queries(Q);
    std::uniform_int_distribution<int> dist_x(0, H - 1), dist_y(0, W - 1), dist_val(0, mint::mod() - 1);

    for (int i = 0; i < Q; ++i) {
        int l = dist_x(rng), r = dist_x(rng);
        if (l > r) std::swap(l, r);
        int d = dist_y(rng), u = dist_y(rng);
        if (d > u) std::swap(d, u);
        if (rng() & 1) {
            int val = dist_val(rng);
            queries[i] = { l, r, d, u, val };
            sol2.register_add_query_rectangle(l, r, d, u);
        } else {
            queries[i] = { l, r, d, u, -1 };
        }
    }
    sol2.build();

    for (const auto& [l, r, d, u, v] : queries) {
        if (v >= 0) {
            sol1.add(l, r, d, u, v), sol2.add(l, r, d, u, v);
        } else {
            assert(sol1.sum(l, r, d, u) == sol2.sum(l, r, d, u));
        }
    }
}

int main() {
    random_test<1000, 1000, 2000>();
    std::cout << "Hello World" << std::endl;
    return 0;
}