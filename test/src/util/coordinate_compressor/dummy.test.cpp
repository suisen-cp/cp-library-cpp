#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/util/coordinate_compressor.hpp"

template <typename T>
struct NaiveCompressor {
    static constexpr int absent = suisen::CoordinateCompressorBuilder<T>::Compressor::absent;

    NaiveCompressor(const std::vector<T>& a) : _sorted(a) {
        std::sort(_sorted.begin(), _sorted.end());
        _sorted.erase(std::unique(_sorted.begin(), _sorted.end()), _sorted.end());
        // check if strictly increasing
        assert(std::adjacent_find(_sorted.begin(), _sorted.end(), std::greater_equal<T>()) == _sorted.end());
    }

    // Return the minimum registered value greater than `e`. if not exists, return `default_value`.
    T min_gt(const T& e, const T& default_value) const {
        auto it = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x > e; });
        if (it != _sorted.begin()) assert(*std::prev(it) <= e);
        if (it != _sorted.end()) assert(*it > e);
        return it == _sorted.end() ? default_value : *it;
    }
    // Return the minimum registered value greater than or equal to `e`. if not exists, return `default_value`.
    T min_geq(const T& e, const T& default_value) const {
        auto it = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x >= e; });
        if (it != _sorted.begin()) assert(*std::prev(it) < e);
        if (it != _sorted.end()) assert(*it >= e);
        return it == _sorted.end() ? default_value : *it;
    }
    // Return the maximum registered value less than `e`. if not exists, return `default_value`
    T max_lt(const T& e, const T& default_value) const {
        auto it = std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const T& x) { return x < e; });
        if (it != _sorted.rbegin()) assert(*std::prev(it) >= e);
        if (it != _sorted.rend()) assert(*it < e);
        return it == _sorted.rend() ? default_value : *it;
    }
    // Return the maximum registered value less than or equal to `e`. if not exists, return `default_value`
    T max_leq(const T& e, const T& default_value) const {
        auto it = std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const T& x) { return x <= e; });
        if (it != _sorted.rbegin()) assert(*std::prev(it) > e);
        if (it != _sorted.rend()) assert(*it <= e);
        return it == _sorted.rend() ? default_value : *it;
    }
    // Return the compressed index of the minimum registered value greater than `e`. if not exists, return `compressor.size()`.
    int min_gt_index(const T& e) const {
        int i = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x > e; }) - _sorted.begin();
        if (i > 0) assert(_sorted[i - 1] <= e);
        if (i < int(_sorted.size())) assert(_sorted[i] > e);
        else assert(i == int(_sorted.size()));
        return i;
    }
    // Return the compressed index of the minimum registered value greater than or equal to `e`. if not exists, return `compressor.size()`.
    int min_geq_index(const T& e) const {
        int i = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x >= e; }) - _sorted.begin();
        if (i > 0) assert(_sorted[i - 1] < e);
        if (i < int(_sorted.size())) assert(_sorted[i] >= e);
        else assert(i == int(_sorted.size()));
        return i;
    }
    // Return the compressed index of the maximum registered value less than `e`. if not exists, return -1.
    int max_lt_index(const T& e) const {
        int i = _sorted.rend() - std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const T& x) { return x < e; }) - 1;
        if (i + 1 < int(_sorted.size())) assert(_sorted[i + 1] >= e);
        if (i >= 0) assert(_sorted[i] < e);
        else assert(i == -1);
        return i;
    }
    // Return the compressed index of the maximum registered value less than or equal to `e`. if not exists, return -1.
    int max_leq_index(const T& e) const {
        int i = _sorted.rend() - std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const T& x) { return x <= e; }) - 1;
        if (i + 1 < int(_sorted.size())) assert(_sorted[i + 1] > e);
        if (i >= 0) assert(_sorted[i] <= e);
        else assert(i == -1);
        return i;
    }
private:
    std::vector<T> _sorted;
};

void test(std::vector<int> a, int l, int r, int default_value) {
    NaiveCompressor<int> comp_naive(a);
    auto comp = suisen::CoordinateCompressorBuilder<int>::build(a);

    for (int i = l; i <= r; ++i) {
        assert(comp_naive.max_leq(i, default_value) == comp.max_leq(i, default_value));
        assert(comp_naive.max_lt (i, default_value) == comp.max_lt (i, default_value));
        assert(comp_naive.min_geq(i, default_value) == comp.min_geq(i, default_value));
        assert(comp_naive.min_gt (i, default_value) == comp.min_gt (i, default_value));
        assert(comp_naive.max_leq_index(i) == comp.max_leq_index(i));
        assert(comp_naive.max_lt_index (i) == comp.max_lt_index (i));
        assert(comp_naive.min_geq_index(i) == comp.min_geq_index(i));
        assert(comp_naive.min_gt_index (i) == comp.min_gt_index (i));
    }
}

void tests() {
    test({ 1, 3, 6, 3, 10, 1 }, 0, 11, -1);
    test({ -5, -4, 1, 4, -4, -6, 10, 12, 14, 14 }, -7, 15, 7);
    test({ }, -10, +10, 0);
    test({ 1, 1, 1, 1, 1, 1 }, 0, 2, 0);
}

int main() {
    tests();
    std::cout << "Hello World" << std::endl;
    return 0;
}