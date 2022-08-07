#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <numeric>
#include <random>

#include "library/tree/point_set_range_contour_product.hpp"

int op(int x, int y) {
    return std::max(x, y);
}
int e() {
    return 0;
}

using Solution = suisen::PointSetRangeContourProduct<int, op, e>;

struct NaiveSolution {
    NaiveSolution(std::vector<std::vector<int>> g, std::vector<int> dat) : g(g), dat(dat) {}

    void set(int u, int val) {
        dat[u] = val;
    }
    int prod(int k, int dl, int dr) {
        int res = e();
        auto dfs = [&](auto dfs, int u, int p, int dep) -> void {
            if (dl <= dep and dep < dr) res = op(res, dat[u]);
            for (int v : g[u]) {
                if (v == p) continue;
                dfs(dfs, v, u, dep + 1);
            }
        };
        dfs(dfs, k, -1, 0);
        return res;
    }
private:
    std::vector<std::vector<int>> g;
    std::vector<int> dat;
};

void random_queries(int n, int q, Solution& t1, NaiveSolution& t2) {
    auto check = [&](int k, int dl, int dr) {
        int sum1 = t1.prod(k, dl, dr);
        int sum2 = t2.prod(k, dl, dr);
        assert(sum1 == sum2);
    };

    std::mt19937 rng{ std::random_device{}() };
    while (q-- > 0) {
        int qt = rng();
        if (qt == 1) {
            int i = rng() % n;
            int v = rng() % 10000;
            t1.set(i, v);
            t2.set(i, v);
        } else {
            int i = rng() % n;
            int l = rng() % n;
            int r = l + rng() % (n - l);
            check(i, l, r);
        }
    }
}

#include <atcoder/dsu>

std::vector<std::vector<int>> random_tree(int n) {
    std::mt19937 rng{ std::random_device{}() };

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) {
        edges.emplace_back(i, j);
    }
    std::shuffle(edges.begin(), edges.end(), rng);

    std::vector<std::vector<int>> g(n);

    atcoder::dsu uf(n);
    int con = n;
    while (con > 1) {
        auto [u, v] = edges.back();
        edges.pop_back();
        if (uf.same(u, v)) continue;
        uf.merge(u, v);
        --con;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

void test1(int q = 100000) {
    std::vector<std::vector<int>> g{
        { 1, 8, 16 },       // 0
        { 0, 2, 3 },        // 1
        { 1 },              // 2
        { 1, 4, 7 },        // 3
        { 3, 5, 6 },        // 4
        { 4 },              // 5
        { 4 },              // 6
        { 3 },              // 7
        { 0, 9, 10 },       // 8
        { 8 },              // 9
        { 8, 11, 15 },      // 10
        { 10, 12, 13, 14 }, // 11
        { 11 },             // 12
        { 11 },             // 13
        { 11 },             // 14
        { 10 },             // 15
        { 0, 17, 18, 20 },  // 16
        { 16 },             // 17
        { 16, 19 },         // 18
        { 18 },             // 19
        { 16, 21, 24 },     // 20
        { 20, 22, 23 },     // 21
        { 21 },             // 22
        { 21 },             // 23
        { 20 }              // 24
    };

    const int n = g.size();
    std::vector<int> dat(n);
    std::iota(dat.begin(), dat.end(), 1);

    suisen::PointSetRangeContourProduct<int, op, e> contour_aggregator(dat);
    for (int i = 0; i < n; ++i) for (int j : g[i]) if (i < j) {
        contour_aggregator.add_edge(i, j);
    }

    contour_aggregator.build();
    NaiveSolution naive(g, dat);

    random_queries(n, q, contour_aggregator, naive);
}

void test2(int n = 1000, int q = 10000) {
    auto g = random_tree(n);
    std::vector<int> dat(n);
    std::iota(dat.begin(), dat.end(), 1);

    suisen::PointSetRangeContourProduct<int, op, e> contour_aggregator(dat);
    for (int i = 0; i < n; ++i) for (int j : g[i]) if (i < j) {
        contour_aggregator.add_edge(i, j);
    }

    contour_aggregator.build();
    NaiveSolution naive(g, dat);

    random_queries(n, q, contour_aggregator, naive);
}

int main() {
    test1();
    test2();
    std::cout << "Hello World" << std::endl;
    return 0;
}