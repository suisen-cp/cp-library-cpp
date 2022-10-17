#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <numeric>
#include <random>

#include "library/graph/csr_graph.hpp"
#include "library/util/timer.hpp"

using namespace suisen;

void test1() {
    const int n = 5;
    GraphBuilder<undirected_graph_tag> builder(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        builder.emplace_edge(i, j);
    }
    Graph g = builder.build();
    for (int i = 0; i < n; ++i) {
        std::sort(g[i].begin(), g[i].end());
        g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());
    }

    for (int i = 0; i < n; ++i) {
        std::vector<int> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<int> expected(n);
        std::iota(expected.begin(), expected.end(), 0);
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        std::vector<int> actual;
        std::copy(g[i].rbegin(), g[i].rend(), std::back_inserter(actual));
        std::vector<int> expected(n);
        std::iota(expected.rbegin(), expected.rend(), 0);
        assert(actual == expected);
    }

    g.shrink_to_fit();

    for (int i = 0; i < n; ++i) {
        std::vector<int> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<int> expected(n);
        std::iota(expected.begin(), expected.end(), 0);
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        g[i].erase(std::remove_if(g[i].begin(), g[i].end(), [i](int j) { return j == i + 1; }), g[i].end());
        std::vector<int> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<int> expected(n);
        std::iota(expected.begin(), expected.end(), 0);
        if (i != n - 1) {
            expected.erase(std::find(expected.begin(), expected.end(), i + 1));
        }
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        if (i != n - 1) {
            g[i].insert(std::lower_bound(g[i].begin(), g[i].end(), i + 1), i + 1);
        }
        std::vector<int> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<int> expected(n);
        std::iota(expected.begin(), expected.end(), 0);
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        for (auto& e : g[i]) {
            assert(g.get_weight(e) == 1);
        }
    }
}

void test2() {
    const int n = 5;
    GraphBuilder<undirected_graph_tag, long long> builder(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        builder.emplace_edge(i, j, std::max(i, j));
    }
    Graph g = builder.build();
    for (int i = 0; i < n; ++i) {
        std::sort(g[i].begin(), g[i].end());
        g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());
    }

    for (int i = 0; i < n; ++i) {
        std::vector<std::pair<int, long long>> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<std::pair<int, long long>> expected(n);
        for (int j = 0; j < n; ++j) expected[j] = { j, std::max(i, j) };
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        std::vector<std::pair<int, long long>> actual;
        std::copy(g[i].rbegin(), g[i].rend(), std::back_inserter(actual));
        std::vector<std::pair<int, long long>> expected(n);
        for (int j = 0; j < n; ++j) expected[n - j - 1] = { j, std::max(i, j) };
        assert(actual == expected);
    }

    g.shrink_to_fit();

    for (int i = 0; i < n; ++i) {
        std::vector<std::pair<int, long long>> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<std::pair<int, long long>> expected(n);
        for (int j = 0; j < n; ++j) expected[j] = { j, std::max(i, j) };
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        g[i].erase(std::remove_if(g[i].begin(), g[i].end(), [i](const std::pair<int, long long>& e) { return e.first == i + 1; }), g[i].end());
        std::vector<std::pair<int, long long>> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<std::pair<int, long long>> expected;
        for (int j = 0; j < n; ++j) if (j != i + 1) expected.emplace_back(j, std::max(i, j));
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        if (i != n - 1) g[i].insert(std::lower_bound(g[i].begin(), g[i].end(), std::pair{ i + 1, 0LL }), { i + 1, i + 1 });
        std::vector<std::pair<int, long long>> actual;
        std::copy(g[i].begin(), g[i].end(), std::back_inserter(actual));
        std::vector<std::pair<int, long long>> expected(n);
        for (int j = 0; j < n; ++j) expected[j] = { j, std::max(i, j) };
        assert(actual == expected);
    }

    for (int i = 0; i < n; ++i) {
        for (auto& e : g[i]) {
            assert(g.get_weight(e) == std::max<int>(i, e));
        }
    }
}

void test3() {
    auto g = Graph<void>::create_undirected_graph(3, { { 0, 1 }, { 1, 2 }, { 2, 0 } });
    auto h = g;
    for (int i = 0; i < 3; ++i) {
        std::sort(h[i].begin(), h[i].end());
    }
    if (std::vector(h[0].begin(), h[0].end()) != std::vector<int> { 1, 2 }) assert(false);
    if (std::vector(h[1].begin(), h[1].end()) != std::vector<int> { 0, 2 }) assert(false);
    if (std::vector(h[2].begin(), h[2].end()) != std::vector<int> { 0, 1 }) assert(false);
}

void test4() {
    const int n = 500000, m = 500000;

    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist_v(0, n - 1);
    std::uniform_int_distribution<long long> dist_w(std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());

    std::vector<std::tuple<int, int, long long>> edges;
    for (int i = 0; i < m; ++i) {
        int u = dist_v(rng);
        int v = dist_v(rng);
        long long w = dist_w(rng);
        edges.emplace_back(u, v, w);
    }

    Timer t;

    Graph g = Graph<long long>::create_directed_graph(n, edges);
    Graph h = Graph<long long>::create_undirected_graph(n, edges);
    
    const int swap_num = 500000;
    for (int i = 0; i < swap_num; ++i) {
        std::swap(g, h);
        Graph tmp = std::move(g);
        g = std::move(h);
        h = std::move(tmp);
    }

    assert(t.elapsed() <= 1000);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    std::cout << "Hello World" << std::endl;
    return 0;
}