#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <iostream>

#include "library/string/substring_set.hpp"
using suisen::SubstringSet;

int main() {
    std::string s;
    std::cin >> s;
    std::cout << SubstringSet(s).size() - 1 << std::endl;
    return 0;
}