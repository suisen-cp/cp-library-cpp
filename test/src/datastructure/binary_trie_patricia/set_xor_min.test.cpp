#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <iostream>

#include "library/datastructure/binary_trie_patricia.hpp"
using suisen::BinaryTriePatricia;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    BinaryTriePatricia<uint32_t, 30> bt;
    while (q --> 0) {
        uint32_t query_type, x;
        std::cin >> query_type >> x;

        if (query_type == 0) {
            bt.insert_if_absent(x);
        } else if (query_type == 1) {
            bt.erase(x);
        } else {
            std::cout << bt.xor_min(x) << '\n';
        }
    }

    return 0;
}
