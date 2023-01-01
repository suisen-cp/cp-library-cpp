#define PROBLEM "https://atcoder.jp/contests/abc268/tasks/abc268_Ex"

#include <iostream>

#include "library/string/aho_corasick.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    int n;
    std::cin >> n;

    suisen::AhoCorasick ac;
    for (int i = 0; i < n; ++i) {
        std::string t;
        std::cin >> t;
        ac.add(t);
    }
    ac.build();
 
    int ans = 0;
    int state = ac.init_state();
    for (char c : s) {
        if (int next_state = ac.next_state(state, c); ac.count_suffix_matching(next_state)) {
            ++ans;
            state = ac.init_state();
        } else {
            state = next_state;
        }
    }
    std::cout << ans << std::endl;

    return 0;
}