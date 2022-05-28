#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "library/util/subset_iterator.hpp"

void test_all_subset(uint32_t s) {
    std::vector<uint32_t> expected;
    for (uint32_t i = 0; i <= s; ++i) if ((i & s) == i) {
        expected.push_back(i);
    }

    std::vector<uint32_t> actual;
    for (uint32_t t : suisen::all_subset(s)) {
        actual.push_back(t);
    }

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(expected == actual);
}

void run_test() {
    for (uint32_t s = 0; s < 10000; ++s) {
        test_all_subset(s);
    }
}

int main() {
    run_test();
    std::cout << "Hello World" << std::endl;
    return 0;
}