#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <iostream>

#include "library/string/suffix_automaton.hpp"
using suisen::SuffixAutomaton;

int main() {
    std::string s;
    std::cin >> s;
    std::cout << SuffixAutomaton(s).number_of_substrings() - 1 << std::endl;
    return 0;
}