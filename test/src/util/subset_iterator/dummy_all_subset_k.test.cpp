#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <cassert>
#include <chrono>
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

void perf_test() {
    const uint32_t s = 0b0111'1111'1111'1111'1111'1111'1111'1111;
    const uint32_t k = 15;

    std::cerr << "|S| = " << __builtin_popcount(s) << ", k = " << k << std::endl;

    auto start = std::chrono::system_clock::now();

    uint64_t cnt = 0;
    for (uint32_t t : suisen::all_subset_k(s, k)) ++cnt;

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

    std::cerr << "Elapsed Time : " << elapsed << " ms" << std::endl;
    std::cerr << "Number of subsets of S with k elements : " << cnt << std::endl;
}

int main() {
    run_test();
    perf_test();
    std::cout << "Hello World" << std::endl;
    return 0;
}