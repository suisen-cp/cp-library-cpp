#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <iostream>
#include "library/string/manacher.hpp"

int main() {
    std::string s;
    std::cin >> s;
    suisen::Manacher manacher(s, '$');
    for (int i = 1; i < 2 * int(s.size()); ++i) std::cout << manacher[i] << '\n';
    return 0;
}