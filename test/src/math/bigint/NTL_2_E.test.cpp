#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_E"

#include <iostream>

#include "library/math/bigint.hpp"
using suisen::bigint;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    bigint a, b;
    std::cin >> a >> b;
    std::cout << a % b << std::endl;
    return 0;
}