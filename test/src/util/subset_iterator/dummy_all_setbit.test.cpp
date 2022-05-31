#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

#include "library/util/subset_iterator.hpp"

void test_all_setbit(uint32_t s) {
    std::vector<uint8_t> expected;
    for (uint8_t i = 0; i < 32; ++i) if ((s >> i) & 1) {
        expected.push_back(i);
    }

    std::vector<uint8_t> actual;
    for (uint8_t t : suisen::all_setbit(s)) {
        actual.push_back(t);
    }

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(expected == actual);
}

void test_all_setbit_64(uint64_t s) {
    std::vector<uint8_t> expected;
    for (uint8_t i = 0; i < 64; ++i) if ((s >> i) & 1) {
        expected.push_back(i);
    }

    std::vector<uint8_t> actual;
    for (uint8_t t : suisen::all_setbit_64(s)) {
        actual.push_back(t);
    }

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(expected == actual);
}

void run_test() {
    for (uint32_t s = 0; s < 1000000; ++s) {
        test_all_setbit(s);
    }

    std::mt19937_64 rng{std::random_device{}()};
    for (uint32_t i = 0; i < 1000000; ++i) {
        uint64_t s = rng();
        test_all_setbit_64(s);
    }
}

int main() {
    run_test();
    std::cout << "Hello World" << std::endl;
    return 0;
}