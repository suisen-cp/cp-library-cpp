#define PROBLEM "https://atcoder.jp/contests/abc237/tasks/abc237_d"

#include <iostream>
#include "library/datastructure/bbst/implicit_treap.hpp"

using Sequence = suisen::DynamicArray<int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string s;
    std::cin >> n >> s;

    Sequence t;
    t.push_back(0);

    int pos = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'L') {
            t.insert(pos, i + 1);
        } else {
            t.insert(++pos, i + 1);
        }
    }
    std::vector<int> res = t.dump();

    for (int i = 0; i <= n; ++i) {
        std::cout << res[i] << " \n"[i == n];
    }

    return 0;
}
