#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include <iostream>

#include "library/datastructure/binary_trie_patricia.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::string t;
    std::cin >> t;

    suisen::BinaryTriePatricia<int, 24> bt;
    for (int i = 0; i < n; ++i) if (t[i] == '1') {
        bt.insert(i);
    }

    while (q --> 0) {
        int query_type, k;
        std::cin >> query_type >> k;
        if (query_type == 0) {
            bt.insert_if_absent(k);
        } else if (query_type == 1) {
            bt.erase(k);
        } else if (query_type == 2) {
            std::cout << bt.contains(k) << '\n';
        } else if (query_type == 3) {
            auto opt_v = bt.safe_min_geq(k);
            std::cout << (opt_v.has_value() ? *opt_v : -1) << '\n';
        } else {
            auto opt_v = bt.safe_max_leq(k);
            std::cout << (opt_v.has_value() ? *opt_v : -1) << '\n';
        }
    }

    return 0;
}