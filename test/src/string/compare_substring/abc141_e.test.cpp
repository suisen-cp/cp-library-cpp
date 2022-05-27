#define PROBLEM "https://atcoder.jp/contests/abc141/tasks/abc141_e"

#include <iostream>
#include <map>

#include "library/string/compare_substring.hpp"

int main() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    suisen::CompareSubstring cmp(s);
    using Substring = decltype(cmp.substr(0, 0));
    
    auto is_ok = [&](int w) {
        std::map<Substring, int> st;
        for (int i = 0; i + w <= n; ++i) {
            Substring sub = cmp.substr(i, i + w);
            if (auto it = st.find(sub); it != st.end()) {
                if (it->second + w <= i) return true;
            } else {
                st[sub] = i;
            }
        }
        return false;
    };

    int l = 0, r = n / 2 + 1;
    while (r - l > 1) {
        int w = (l + r) >> 1;
        (is_ok(w) ? l : r) = w;
    }
    std::cout << l << std::endl;
    
    return 0;
}