#define PROBLEM "https://atcoder.jp/contests/arc097/tasks/arc097_c"

#include <iostream>

#include "library/string/substring_set.hpp"
using suisen::SubstringSet;

int main() {
    std::string s;
    int k;
    std::cin >> s >> k;
    std::cout << SubstringSet(s)[k] << std::endl;
    return 0;
}