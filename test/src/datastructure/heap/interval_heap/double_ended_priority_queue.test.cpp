#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include <iostream>

#include "library/datastructure/heap/interval_heap.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    suisen::IntervalHeap<int> pq;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        pq.push(v);
    }

    for (int i = 0; i < q; ++i) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int x;
            std::cin >> x;
            pq.push(x);
        } else if (query_type == 1) {
            std::cout << pq.pop_min() << '\n';
        } else {
            std::cout << pq.pop_max() << '\n';
        }
    }
    return 0;
}