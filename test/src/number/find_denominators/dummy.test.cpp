#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <cassert>
#include <iostream>

#include "library/number/find_denominators.hpp"

using suisen::fld_denominators_positive;
using suisen::fld_denominators_negative;
using suisen::cld_denominators_positive;
using suisen::cld_denominators_negative;

template <typename T>
constexpr inline int pow_m1(T n) {
    return -(n & 1) | 1;
}
template <>
constexpr inline int pow_m1<bool>(bool n) {
    return -int(n) | 1;
}

template <typename T>
constexpr inline T fld(const T x, const T y) {
    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) / y;
}
template <typename T>
constexpr inline T cld(const T x, const T y) {
    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;
}

bool in(const std::optional<std::pair<int, int>> &r, int x) {
    return r.has_value() and r->first <= x and x <= r->second;
}
bool out(const std::optional<std::pair<int, int>> &r, int x) {
    return not r.has_value() or x < r->first or x > r->second;
}

void cld_test(int n, int q) {
    auto res_pos = cld_denominators_positive(n, q, 100);
    if (res_pos.has_value()) {
        auto [l, r] = *res_pos;
        assert(1 <= l and r <= 100);
    }
    for (int x = 1; x <= 100; ++x) {
        if (not (cld(n, x) == q ? in : out)(res_pos, x)) {
            assert(false);
        }
    }

    auto res_neg = cld_denominators_negative(n, q, -100);
    if (res_neg.has_value()) {
        auto [l, r] = *res_neg;
        assert(-100 <= l and r <= -1);
    }
    for (int x = -100; x <= -1; ++x) {
        if (not (cld(n, x) == q ? in : out)(res_neg, x)) {
            assert(false);
        }
    }
}

void fld_test(int n, int q) {
    auto res_pos = fld_denominators_positive(n, q, 100);
    if (res_pos.has_value()) {
        auto [l, r] = *res_pos;
        assert(1 <= l and r <= 100);
    }
    for (int x = 1; x <= 100; ++x) {
        if (not (fld(n, x) == q ? in : out)(res_pos, x)) {
            assert(false);
        }
    }

    auto res_neg = fld_denominators_negative(n, q, -100);
    if (res_neg.has_value()) {
        auto [l, r] = *res_neg;
        assert(-100 <= l and r <= -1);
    }
    for (int x = -100; x <= -1; ++x) {
        if (not (fld(n, x) == q ? in : out)(res_neg, x)) {
            assert(false);
        }
    }
}

int main() {
    for (int n = -100; n <= 100; ++n) {
        for (int q = -101; q <= 101; ++q) {
            cld_test(n, q);
            fld_test(n, q);
        }
    }

    std::cout << "Hello World" << std::endl;
    return 0;
}