#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <bitset>
#include <iostream>

#include "library/datastructure/util/dynamic_bitset.hpp"

using suisen::DynamicBitSet;

template <std::size_t n>
bool operator==(const DynamicBitSet& dbs, const std::bitset<n>& bs) {
    if (dbs.size() != int(n)) return false;
    for (std::size_t i = 0; i < n; ++i) if (dbs[i] != bs[i]) return false;
    return true;
}
template <std::size_t n>
bool operator==(const std::bitset<n>& bs, const DynamicBitSet& dbs) {
    return dbs == bs;
}
template <std::size_t n>
bool operator!=(const DynamicBitSet& dbs, const std::bitset<n>& bs) {
    return not (dbs == bs);
}
template <std::size_t n>
bool operator!=(const std::bitset<n>& bs, const DynamicBitSet& dbs) {
    return dbs != bs;
}

void test_empty() {
    assert(DynamicBitSet(0).empty());
    assert(not DynamicBitSet(1).empty());
}

void test_size() {
    assert(DynamicBitSet(0).size() == 0);
    assert(DynamicBitSet(1).size() == 1);
    assert(DynamicBitSet(64).size() == 64);
}

void test_resize() {
    DynamicBitSet bs;
    bs.resize(35, true);
    assert(bs.size() == 35);
    for (int i = 0; i < 35; ++i) assert(bs[i]);
    bs.resize(1026, false);
    assert(bs.size() == 1026);
    for (int i = 0; i < 35; ++i) assert(bs[i]);
    for (int i = 35; i < 1026; ++i) assert(not bs[i]);
    bs.resize(78);
    assert(bs.size() == 78);
    for (int i = 0; i < 35; ++i) assert(bs[i]);
    for (int i = 35; i < 78; ++i) assert(not bs[i]);
    bs.resize(512, true);
    assert(bs.size() == 512);
    for (int i = 0; i < 35; ++i) assert(bs[i]);
    for (int i = 35; i < 78; ++i) assert(not bs[i]);
    for (int i = 78; i < 512; ++i) assert(bs[i]);
    bs.resize(128, false);
    assert(bs.size() == 128);
    for (int i = 0; i < 35; ++i) assert(bs[i]);
    for (int i = 35; i < 78; ++i) assert(not bs[i]);
    for (int i = 78; i < 128; ++i) assert(bs[i]);
}

void test_push_back() {
    DynamicBitSet bs;
    for (int i = 0; i < 1000; ++i) {
        bs.push_back(i & 1);
        assert(bs.size() == i + 1);
        for (int j = 0; j <= i; ++j) assert(bs[j] == (j & 1));
    }
}

void test_pop_back() {
    DynamicBitSet bs;
    for (int i = 0; i < 1000; ++i) {
        bs.push_back(i & 1);
    }
    for (int i = 0; i < 1000; ++i) {
        bs.pop_back();
        assert(bs.size() == 999 - i);
        for (int j = 0; j < 999 - i; ++j) assert(bs[j] == (j & 1));
    }
}

void test_eq() {
    DynamicBitSet x(10, true);
    DynamicBitSet y(10);
    for (int i = 0; i < 10; ++i) y[i] = true;
    assert(x == y);
    x.resize(516, false);
    y.resize(516, false);
    assert(x == y);
    x.resize(100);
    y.resize(200);
    x.resize(300, true);
    y.resize(300, true);
    for (int i = 100; i < 200; ++i) y[i] = true;
    assert(x == y);
}

void test_neq() {
    DynamicBitSet x(10);
    DynamicBitSet y;
    assert(x != y);
    y.resize(5);
    assert(x != y);
    y.resize(64, true);
    assert(x != y);
    y.resize(10);
    assert(x != y);
    x.resize(500);
    y.resize(500);
    for (int i = 5; i < 10; ++i) x[i] = true;
    assert(x == y);
    y[499] = true;
    assert(x != y);
    y[499] = false;
    assert(x == y);
    y[256] = true;
    assert(x != y);
    y[256] = false;
    assert(x == y);
    y[255] = true;
    assert(x != y);
}

void test_lt() {
    DynamicBitSet x(100), y(100);
    assert(not (x < y));
    x[56] = true;
    assert(not (x < y));
    y[56] = true;
    assert(not (x < y));
    y[99] = true;
    assert(x < y);
    x.resize(200), y.resize(200);
    x[100] = true;
    assert(not (x < y));
    y[100] = true;
    assert(x < y);
    x[99] = true;
    assert(not (x < y));
    y[199] = true;
    assert(x < y);
    y[199] = false;
    y[128] = true;
    assert(x < y);
    y[128] = false;
    y[127] = true;
    assert(x < y);
}

void test_leq() {
    DynamicBitSet x(100), y(100);
    assert(x <= y);
    x[56] = true;
    assert(not (x <= y));
    y[56] = true;
    assert(x <= y);
    y[99] = true;
    assert(x <= y);
    x.resize(200), y.resize(200);
    x[100] = true;
    assert(not (x <= y));
    y[100] = true;
    assert(x <= y);
    x[99] = true;
    assert(x <= y);
    y[199] = true;
    assert(x <= y);
    y[199] = false;
    y[128] = true;
    assert(x <= y);
    y[128] = false;
    y[127] = true;
    assert(x <= y);
}
void test_gt() {
    DynamicBitSet x(100), y(100);
    assert(not (x > y));
    x[56] = true;
    assert(x > y);
    y[56] = true;
    assert(not (x > y));
    y[99] = true;
    assert(not (x > y));
    x.resize(200), y.resize(200);
    x[100] = true;
    assert(x > y);
    y[100] = true;
    assert(not (x > y));
    x[99] = true;
    assert(not (x > y));
    y[199] = true;
    assert(not (x > y));
    y[199] = false;
    y[128] = true;
    assert(not (x > y));
    y[128] = false;
    y[127] = true;
    assert(not (x > y));
}
void test_geq() {
    DynamicBitSet x(100), y(100);
    assert(x >= y);
    x[56] = true;
    assert(x >= y);
    y[56] = true;
    assert(x >= y);
    y[99] = true;
    assert(not (x >= y));
    x.resize(200), y.resize(200);
    x[100] = true;
    assert(x >= y);
    y[100] = true;
    assert(not (x >= y));
    x[99] = true;
    assert(x >= y);
    y[199] = true;
    assert(not (x >= y));
    y[199] = false;
    y[128] = true;
    assert(not (x >= y));
    y[128] = false;
    y[127] = true;
    assert(not (x >= y));
}

void test_cast_bool() {
    DynamicBitSet x;
    assert(not x);
    x.resize(100);
    assert(not x);
    x[99] = true;
    assert(x);
}

void test_and() {
    constexpr int n = 353;
    std::bitset<n> bs1, bs2;
    DynamicBitSet dbs1(n), dbs2(n);
    for (int i = 0; i < n; ++i) {
        bs1[i] = i % 3 == 0;
        dbs1[i] = i % 3 == 0;
    }
    for (int i = 0; i < n; ++i) {
        bs2[i] = i % 5 == 0;
        dbs2[i] = i % 5 == 0;
    }
    auto bs = bs1 & bs2;
    auto dbs = dbs1 & dbs2;
    assert(bs == dbs);
}
void test_or() {
    constexpr int n = 353;
    std::bitset<n> bs1, bs2;
    DynamicBitSet dbs1(n), dbs2(n);
    for (int i = 0; i < n; ++i) {
        bs1[i] = i % 3 == 0;
        dbs1[i] = i % 3 == 0;
    }
    for (int i = 0; i < n; ++i) {
        bs2[i] = i % 5 == 0;
        dbs2[i] = i % 5 == 0;
    }
    auto bs = bs1 | bs2;
    auto dbs = dbs1 | dbs2;
    assert(bs == dbs);
}
void test_xor() {
    constexpr int n = 353;
    std::bitset<n> bs1, bs2;
    DynamicBitSet dbs1(n), dbs2(n);
    for (int i = 0; i < n; ++i) {
        bs1[i] = i % 3 == 0;
        dbs1[i] = i % 3 == 0;
    }
    for (int i = 0; i < n; ++i) {
        bs2[i] = i % 5 == 0;
        dbs2[i] = i % 5 == 0;
    }
    auto bs = bs1 ^ bs2;
    auto dbs = dbs1 ^ dbs2;
    assert(bs == dbs);
}
void test_shift_r() {
    constexpr int n = 353;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    for (std::size_t i = 0; i < n; ++i) {
        assert((bs >> i) == (dbs >> i));
    }
}
void test_shift_l() {
    constexpr int n = 353;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    for (std::size_t i = 0; i < n; ++i) {
        assert((bs << i) == (dbs << i));
    }
}
void test_neg() {
    constexpr int n = 353;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    assert(~bs == ~dbs);
}

void test_get_set() {
    constexpr int n = 2349;
    DynamicBitSet bs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 != 0;
    }
    for (int i = 0; i < n; ++i) {
        assert(bs[i] == (i % 3 != 0));
    }
}

void test_range_set() {
    constexpr int n = 513;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    auto range_set_dbs = [&](int l, int r) {
        auto dbs2 = dbs;
        dbs2.range_set(l, r);
        return dbs2;
    };
    auto range_set_bs = [&](int l, int r) {
        auto bs2 = bs;
        for (int i = l; i < r; ++i) bs2[i] = true;
        return bs2;
    };

    for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
        assert(range_set_bs(l, r) == range_set_dbs(l, r));
    }
}
void test_range_reset() {
    constexpr int n = 513;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    auto range_reset_dbs = [&](int l, int r) {
        auto dbs2 = dbs;
        dbs2.range_reset(l, r);
        return dbs2;
    };
    auto range_reset_bs = [&](int l, int r) {
        auto bs2 = bs;
        for (int i = l; i < r; ++i) bs2[i] = false;
        return bs2;
    };

    for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
        assert(range_reset_bs(l, r) == range_reset_dbs(l, r));
    }
}
void test_range_flip() {
    constexpr int n = 513;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    auto range_flip_dbs = [&](int l, int r) {
        auto dbs2 = dbs;
        dbs2.range_flip(l, r);
        return dbs2;
    };
    auto range_flip_bs = [&](int l, int r) {
        auto bs2 = bs;
        for (int i = l; i < r; ++i) bs2[i].flip();
        return bs2;
    };

    for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
        assert(range_flip_bs(l, r) == range_flip_dbs(l, r));
    }
}

void test_range_update() {
    constexpr int n = 513;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    auto range_update_dbs = [&](int l, int r, bool val) {
        auto dbs2 = dbs;
        dbs2.range_update(l, r, val);
        return dbs2;
    };
    auto range_update_bs = [&](int l, int r, bool val) {
        auto bs2 = bs;
        for (int i = l; i < r; ++i) bs2[i] = val;
        return bs2;
    };

    for (bool b : { false, true }) {
        for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
            assert(range_update_bs(l, r, b) == range_update_dbs(l, r, b));
        }
    }
}
void test_range_count() {
    constexpr int n = 513;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    auto range_count_dbs = [&](int l, int r) {
        return dbs.range_count(l, r);
    };
    auto range_count_bs = [&](int l, int r) {
        int res = 0;
        for (int i = l; i < r; ++i) res += bs[i];
        return res;
    };

    for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
        assert(range_count_bs(l, r) == range_count_dbs(l, r));
    }
}

void test_all() {
    DynamicBitSet x;
    assert(x.all());
    x.push_back(true);
    assert(x.all());
    x[0] = false;
    assert(not x.all());
    x.resize(129, true);
    assert(not x.all());
    x[0] = true;
    assert(x.all());
    x[128] = false;
    assert(not x.all());
}
void test_none() {
    DynamicBitSet x;
    assert(x.none());
    x.push_back(true);
    assert(not x.none());
    x[0] = false;
    assert(x.none());
    x.resize(129, false);
    assert(x.none());
    x[0] = true;
    assert(not x.none());
    x[0] = false;
    assert(x.none());
    x[128] = true;
    assert(not x.none());
}
void test_any() {
    DynamicBitSet x;
    assert(not x.any());
    x.push_back(true);
    assert(x.any());
    x[0] = false;
    assert(not x.any());
    x.resize(129, false);
    assert(not x.any());
    x[0] = true;
    assert(x.any());
    x[0] = false;
    assert(not x.any());
    x[128] = true;
    assert(x.any());
}

void test_count() {
    DynamicBitSet x;
    assert(x.count() == 0);
    x.resize(10);
    assert(x.count() == 0);
    x[3] = true;
    assert(x.count() == 1);
    x.resize(176, true);
    assert(x.count() == 167);
}

void test_set() {
    DynamicBitSet x;
    x.set();
    assert(x.count() == 0);
    x.resize(20, false);
    x.set();
    assert(x.count() == 20);
    x.resize(1238);
    x.set();
    assert(x.count() == 1238);
}
void test_reset() {
    DynamicBitSet x;
    x.reset();
    assert(x.count() == 0);
    x.resize(20, true);
    x.reset();
    assert(x.count() == 0);
    x.resize(1238);
    x.reset();
    assert(x.count() == 0);
}

void test_find() {
    constexpr int n = 513;
    std::bitset<n> bs;
    DynamicBitSet dbs(n);
    for (int i = 0; i < n; ++i) {
        bs[i] = i % 3 == 0;
        dbs[i] = i % 3 == 0;
    }

    int i = bs._Find_first(), j = dbs.find_first();
    for (; i < n and j < n; i = bs._Find_next(i), j = dbs.find_next(j)) {
        assert(i == j);
    }
    assert(i == n and j == n);
}

void test_has_intersectoin() {
    DynamicBitSet x(10, true), y;
    assert(not x.has_intersection(y));
    y.resize(10);
    y[9] = true;
    assert(x.has_intersection(y));
    y[9] = false;
    y.resize(123);
    y[122] = true;
    assert(not x.has_intersection(y));
    x.resize(1230);
    x[122] = true;
    assert(x.has_intersection(y));
}
void test_is_disjoint() {
    DynamicBitSet x(10, true), y;
    assert(x.is_disjoint(y));
    y.resize(10);
    y[9] = true;
    assert(not x.is_disjoint(y));
    y[9] = false;
    y.resize(123);
    y[122] = true;
    assert(x.is_disjoint(y));
    x.resize(1230);
    x[122] = true;
    assert(not x.is_disjoint(y));
}

void test() {
    test_empty();
    test_size();
    test_resize();
    test_push_back();
    test_pop_back();
    test_eq();
    test_neq();
    test_lt();
    test_leq();
    test_gt();
    test_geq();
    test_cast_bool();
    test_and();
    test_or();
    test_xor();
    test_shift_r();
    test_shift_l();
    test_neg();
    test_get_set();
    test_range_set();
    test_range_reset();
    test_range_flip();
    test_range_update();
    test_range_count();
    test_all();
    test_none();
    test_any();
    test_count();
    test_set();
    test_reset();
    test_find();
    test_has_intersectoin();
    test_is_disjoint();
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
