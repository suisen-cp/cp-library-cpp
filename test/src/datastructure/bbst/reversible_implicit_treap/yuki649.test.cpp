#define PROBLEM "https://yukicoder.me/problems/no/649"

#include <iostream>

#include "library/datastructure/bbst/reversible_implicit_treap.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, k;
    std::cin >> q >> k;

    using suisen::ReversibleDynamicArray;

    ReversibleDynamicArray<long long> a;
    while (q-- > 0) {
        int t;
        std::cin >> t;
        if (t == 1) {
            long long v;
            std::cin >> v;
            a.insert_lower_bound(v);
        } else {
            if (a.size() < k) {
                std::cout << -1 << '\n';
            } else {
                std::cout << a.erase(k - 1) << '\n';
            }
        }
    }
}