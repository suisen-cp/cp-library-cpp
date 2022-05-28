#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "library/util/subset_iterator.hpp"

void test_all_subset_k(uint32_t s, uint32_t k) {
    std::vector<uint32_t> expected;
    if (__builtin_popcount(s) >= k) {
        for (uint32_t i = 0; i <= s; ++i) if ((i & s) == i and __builtin_popcount(i) == k) {
            expected.push_back(i);
        }
    }

    std::vector<uint32_t> actual;
    for (uint32_t t : suisen::all_subset_k(s, k)) {
        actual.push_back(t);
    }

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(expected == actual);
}

void run_test() {
    for (uint32_t s = 0; s < 10000; ++s) for (uint32_t k = 0; k <= 15; ++k) {
        test_all_subset_k(s, k);
    }
}

int main() {
    run_test();
    std::cout << "Hello World" << std::endl;
    return 0;
}