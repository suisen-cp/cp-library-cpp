#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "library/number/count_square_free.hpp"

#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    std::cout << suisen::count_square_free(n) << std::endl;
}