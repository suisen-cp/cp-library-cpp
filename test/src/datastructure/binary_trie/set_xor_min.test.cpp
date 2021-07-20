#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <iostream>

#include "library/datastructure/binary_trie.hpp"
using suisen::BinaryTrie;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    BinaryTrie<int, 30> bt;
    int q;
    std::cin >> q;
    while (q --> 0) {
        int t, x;
        std::cin >> t >> x;
        switch (t) {
            case 0:
                if (not bt.contains(x)) bt.insert(x);
                break;
            case 1:
                bt.erase(x);
                break;
            case 2:
                std::cout << bt.xor_min(x) << '\n';
                break;
            default:
                assert(false);
        }
    }
}