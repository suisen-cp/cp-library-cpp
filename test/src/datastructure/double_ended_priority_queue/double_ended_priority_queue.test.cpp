#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include <iostream>

#include "library/datastructure/double_ended_priority_queue.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> init(n);
    for (auto &e : init) std::cin >> e;
    suisen::DoubleEndedPriorityQueue<int> pq(init.begin(), init.end());

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