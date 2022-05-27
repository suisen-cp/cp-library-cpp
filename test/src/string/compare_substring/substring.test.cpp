#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444"

#include <iostream>

#include "library/string/compare_substring.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;

    suisen::CompareSubstring cmp(s);
    using Substring = decltype(cmp.substr(0, 0));

    std::vector<Substring> sub(q);

    for (int qi = 0, l = 0, r = 1; qi < q; ++qi) {
        std::string query;
        std::cin >> query;
        (query[0] == 'R' ? r : l) += (query[1] == '+' ? 1 : -1);
        sub[qi] = cmp.substr(l, r);
    }

    std::sort(sub.begin(), sub.end());
    sub.erase(std::unique(sub.begin(), sub.end()), sub.end());

    std::cout << sub.size() << std::endl;

    return 0;
}