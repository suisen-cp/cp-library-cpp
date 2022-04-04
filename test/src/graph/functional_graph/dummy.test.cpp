#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <cassert>
#include <iostream>
#include <random>

#include "library/graph/functional_graph.hpp"

void kth_iterate_test(const int n = 500, const int m = 1000) {
    std::mt19937 rng{std::random_device{}()};

    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = rng() % n;

    std::vector<int> q(n);
    std::iota(q.begin(), q.end(), 0);

    auto succ = [&]{
        std::vector<int> r(n);
        for (int i = 0; i < n; ++i) r[i] = p[q[i]];
        q = std::move(r);
    };
    
    suisen::FunctionalGraph g(p);
    for (int k = 0; k < m; ++k) {
        std::vector<int> r = g.kth_iterate(k);
        assert(r == q);
        succ();
    }
}

int main() {
    for (int i = 0; i < 10; ++i) kth_iterate_test();
    std::cout << "Hello World" << std::endl;
    return 0;
}