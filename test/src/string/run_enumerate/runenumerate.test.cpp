#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"

#include <iostream>

#include "library/string/run_enumerate.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    auto runs = suisen::run_enumerate(s);
    std::sort(std::begin(runs), std::end(runs));

    std::cout << runs.size() << '\n';
    for (const auto &run : runs) {
        std::cout << run.period << ' ' << run.l << ' ' << run.r << '\n';
    }

    return 0;
}
