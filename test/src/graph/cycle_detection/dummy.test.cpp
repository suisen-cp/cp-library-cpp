#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <set>

#include "library/graph/cycle_detection.hpp"

using namespace suisen;

void test_undirected_unweighted1() {
    const int n = 4;
    std::vector<std::pair<int, int>> edges {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 },
        { 3, 2 }
    };
    Graph g = UndirectedGraphBuilder<void>::build(n, edges);
    auto c = *get_cycle_undirected(g);

    std::set<std::pair<int, int>> edge_set;
    for (auto [u, v] : edges) edge_set.insert(std::minmax(u, v));

    const int siz = c.size();
    for (int i = 0; i < siz; ++i) {
        int u = c[i], v = c[(i + 1) % siz];
        assert(edge_set.count(std::minmax(u, v)));
    }
}
void test_undirected_unweighted2() {
    const int n = 4;
    std::vector<std::pair<int, int>> edges {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 }
    };
    Graph g = UndirectedGraphBuilder<void>::build(n, edges);
    assert(not get_cycle_undirected(g).has_value());
}

void test_directed_unweighted1() {
    const int n = 4;
    std::vector<std::pair<int, int>> edges {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 },
        { 3, 2 }
    };
    Graph g = DirectedGraphBuilder<void>::build(n, edges);
    auto c = *get_cycle_directed(g);

    std::set<std::pair<int, int>> edge_set;
    for (auto [u, v] : edges) edge_set.insert({ u, v });

    const int siz = c.size();
    for (int i = 0; i < siz; ++i) {
        int u = c[i], v = c[(i + 1) % siz];
        assert(edge_set.count({ u, v }));
    }
}
void test_directed_unweighted2() {
    const int n = 4;
    std::vector<std::pair<int, int>> edges {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 }
    };
    Graph g = DirectedGraphBuilder<void>::build(n, edges);
    assert(not get_cycle_directed(g).has_value());
}

void test() {
    test_undirected_unweighted1();
    test_undirected_unweighted2();
    test_directed_unweighted1();
    test_directed_unweighted2();
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
