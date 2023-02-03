#define PROBLEM "https://yukicoder.me/problems/no/649"

#include <iostream>

#include "library/datastructure/bbst/implicit_treap.hpp"

using Set = suisen::DynamicArray<long long>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, k;
    std::cin >> q >> k;

    Set a;

    while (q-- > 0) {
        int t;
        std::cin >> t;
        if (t == 1) {
            long long v;
            std::cin >> v;
            a.insert(a.lower_bound(v), v);
            // a.insert(a.binary_search([&](Set::iterator it) { return v <= *it; }), v); // ok
            // a.insert(a.binary_search([&](Set::const_iterator it) { return v <= *it; }), v); // ok
        } else {
            if (a.size() < k) {
                std::cout << -1 << '\n';
            } else {
                std::cout << a.erase(k - 1) << '\n';
            }
        }
    }
}