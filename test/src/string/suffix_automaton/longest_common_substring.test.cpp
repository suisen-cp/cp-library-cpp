#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "library/string/suffix_automaton.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;
    auto [i, j, l] = suisen::SuffixAutomaton<char>{s}.longest_common_substring(t);
    std::cout << i << ' ' << i + l << ' ' << j << ' ' << j + l << std::endl;
}