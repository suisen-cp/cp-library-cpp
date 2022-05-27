#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja"

#include <iostream>

#include "library/string/compare_substring.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;
    std::string st = s + '$' + t;

    suisen::CompareSubstring cmp(st);

    int n = s.size(), m = t.size();
    for (int i = 0; i + m <= n; ++i) {
        if (cmp.substr(i, i + m) == cmp.substr(n + 1, n + 1 + m)) {
            std::cout << i << '\n';
        }
    }

    return 0;
}