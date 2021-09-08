#define PROBLEM "https://yukicoder.me/problems/no/430"

#include <iostream>

#include "library/string/suffix_automaton.hpp"
using suisen::SuffixAutomaton;

int main() {
    std::string s;
    std::cin >> s;
    SuffixAutomaton sa(s);
    auto counter = sa.substring_counter();
    int m;
    std::cin >> m;
    long long ans = 0;
    while (m --> 0) {
        std::string c;
        std::cin >> c;
        ans += counter.count(c);
    }
    std::cout << ans << '\n';
    return 0;
}