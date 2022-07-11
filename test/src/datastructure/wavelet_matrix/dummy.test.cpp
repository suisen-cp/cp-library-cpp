#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <iostream>
#include <random>

#include "library/datastructure/wavelet_matrix.hpp"

template <typename T>
struct NaiveSolution {
    NaiveSolution() = default;
    NaiveSolution(std::vector<T> dat) : n(dat.size()), dat(dat) {}

    T operator[](int i) const { return dat[i]; }
    T access(int i) const { return (*this)[i]; }

    int rank(T val, int i) const {
        int res = 0;
        for (int j = 0; j < i; ++j) res += dat[j] == val;
        return res;
    }

    // returns the k'th smallest value in the multiset {| x ^ A[i] : i in [l, r) |} (k : 0-indexed)
    T range_xor_kth_smallest(int l, int r, int k, T x, T default_value = T(-1)) const {
        if (k < 0 or k >= r - l) return default_value;
        std::vector<T> sorted;
        for (int i = l; i < r; ++i) sorted.push_back(dat[i] ^ x);
        std::sort(sorted.begin(), sorted.end());
        return sorted[k] ^ x;
    }
    // returns the k'th largest value in the multiset {| x ^ A[i] : i in [l, r) |} (k : 0-indexed)
    T range_xor_kth_largest(int l, int r, int k, T x, T default_value = T(-1)) const {
        if (k < 0 or k >= r - l) return default_value;
        std::vector<T> sorted;
        for (int i = l; i < r; ++i) sorted.push_back(dat[i] ^ x);
        std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        return sorted[k] ^ x;
    }
    // returns the minimum value in the set { x ^ A[i] : i in [l, r) }
    T range_xor_min(int l, int r, T x) const {
        assert(l < r);
        T min_val = std::numeric_limits<T>::max();
        for (int i = l; i < r; ++i) min_val = std::min(min_val, dat[i] ^ x);
        return min_val ^ x;
    }
    // returns the maximum value in the set { x ^ A[i] : i in [l, r) }
    T range_xor_max(int l, int r, T x) const {
        assert(l < r);
        T max_val = std::numeric_limits<T>::min();
        for (int i = l; i < r; ++i) max_val = std::max(max_val, dat[i] ^ x);
        return max_val ^ x;
    }

    // returns the number of v in A[l, r) s.t. v ^ x < upper
    int range_xor_freq(int l, int r, T x, T upper) const {
        int res = 0;
        for (int i = l; i < r; ++i) res += (dat[i] ^ x) < upper;
        return res;
    }
    // returns the number of v in A[l, r) s.t. lower <= x ^ v < upper
    int range_xor_freq(int l, int r, T x, T lower, T upper) const {
        int res = 0;
        for (int i = l; i < r; ++i) res += lower <= (dat[i] ^ x) and (dat[i] ^ x) < upper;
        return res;
    }

    // returns the minimum value v in A[l, r) s.t. lower <= x ^ v
    T range_xor_min_geq(int l, int r, T x, T lower, T default_value = T(-1)) const {
        bool upd = false;
        T min_val = std::numeric_limits<T>::max();
        for (int i = l; i < r; ++i) if (T v = dat[i] ^ x; lower <= v and v <= min_val) min_val = v, upd = true;
        return upd ? min_val ^ x : default_value;
    }
    // returns the minimum value v in A[l, r) s.t. lower < x ^ v
    T range_xor_min_gt(int l, int r, T x, T lower, T default_value = T(-1)) const {
        bool upd = false;
        T min_val = std::numeric_limits<T>::max();
        for (int i = l; i < r; ++i) if (T v = dat[i] ^ x; lower < v and v <= min_val) min_val = v, upd = true;
        return upd ? min_val ^ x : default_value;
    }
    // returns the maximum value v in A[l, r) s.t. x ^ v < upper
    T range_xor_max_lt(int l, int r, T x, T upper, T default_value = T(-1)) const {
        bool upd = false;
        T max_val = std::numeric_limits<T>::min();
        for (int i = l; i < r; ++i) if (T v = dat[i] ^ x; v < upper and max_val <= v) max_val = v, upd = true;
        return upd ? max_val ^ x : default_value;
    }
    // returns the maximum value v in A[l, r) s.t. x ^ v <= upper
    T range_xor_max_leq(int l, int r, T x, T upper, T default_value = T(-1)) const {
        bool upd = false;
        T max_val = std::numeric_limits<T>::min();
        for (int i = l; i < r; ++i) if (T v = dat[i] ^ x; v <= upper and max_val <= v) max_val = v, upd = true;
        return upd ? max_val ^ x : default_value;
    }

    // returns the k'th smallest value in A[l, r) (k : 0-indexed)
    T range_kth_smallest(int l, int r, int k, T default_value = T(-1)) const {
        if (k < 0 or k >= r - l) return default_value;
        std::vector<T> sorted;
        for (int i = l; i < r; ++i) sorted.push_back(dat[i]);
        std::sort(sorted.begin(), sorted.end());
        return sorted[k];
    }
    // returns the k'th largest value in A[l, r) (k : 0-indexed)
    T range_kth_largest(int l, int r, int k, T default_value = T(-1)) const {
        if (k < 0 or k >= r - l) return default_value;
        std::vector<T> sorted;
        for (int i = l; i < r; ++i) sorted.push_back(dat[i]);
        std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        return sorted[k];
    }
    // returns the minimum value in A[l, r)
    T range_min(int l, int r) const {
        assert(l < r);
        T min_val = std::numeric_limits<T>::max();
        for (int i = l; i < r; ++i) min_val = std::min(min_val, dat[i]);
        return min_val;
    }
    // returns the maximum value in A[l, r)
    T range_max(int l, int r) const {
        assert(l < r);
        T max_val = std::numeric_limits<T>::min();
        for (int i = l; i < r; ++i) max_val = std::max(max_val, dat[i]);
        return max_val;
    }

    // returns the number of v in A[l, r) s.t. v < upper
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (int i = l; i < r; ++i) res += (dat[i]) < upper;
        return res;
    }
    // returns the number of v in A[l, r) s.t. lower <= v < upper
    int range_freq(int l, int r, T lower, T upper) const {
        int res = 0;
        for (int i = l; i < r; ++i) res += lower <= (dat[i]) and (dat[i]) < upper;
        return res;
    }
    // returns the minimum value v in A[l, r) s.t. lower <= v
    T range_min_geq(int l, int r, T lower, T default_value = T(-1)) const {
        bool upd = false;
        T min_val = std::numeric_limits<T>::max();
        for (int i = l; i < r; ++i) if (T v = dat[i]; lower <= v and v <= min_val) min_val = v, upd = true;
        return upd ? min_val : default_value;
    }
    // returns the minimum value v in A[l, r) s.t. lower < v
    T range_min_gt(int l, int r, T lower, T default_value = T(-1)) const {
        bool upd = false;
        T min_val = std::numeric_limits<T>::max();
        for (int i = l; i < r; ++i) if (T v = dat[i]; lower < v and v <= min_val) min_val = v, upd = true;
        return upd ? min_val : default_value;
    }
    // returns the maximum value v in A[l, r) s.t. v < upper
    T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const {
        bool upd = false;
        T max_val = std::numeric_limits<T>::min();
        for (int i = l; i < r; ++i) if (T v = dat[i]; v < upper and max_val <= v) max_val = v, upd = true;
        return upd ? max_val : default_value;
    }
    // returns the maximum value v in A[l, r) s.t. v <= upper
    T range_max_leq(int l, int r, T upper, T default_value = T(-1)) const {
        bool upd = false;
        T max_val = std::numeric_limits<T>::min();
        for (int i = l; i < r; ++i) if (T v = dat[i]; v <= upper and max_val <= v) max_val = v, upd = true;
        return upd ? max_val : default_value;
    }
private:
    int n;
    std::vector<T> dat;
};

using suisen::WaveletMatrix;

// std::mt19937 rng{std::random_device{}()};
std::mt19937 rng{0};

template <typename T, int bit_num>
void test(int n, int q) {
    std::uniform_int_distribution<T> value_dist(0, (T(1) << bit_num) - 1);
    std::vector<T> dat(n);
    for (auto &e : dat) e = value_dist(rng);
    
    WaveletMatrix<T, bit_num> wm(dat);
    NaiveSolution<T> naive(dat);

    std::uniform_int_distribution<int> query_dist(0, 21);

    std::uniform_int_distribution<int> index_dist(0, n - 1);
    std::uniform_int_distribution<int> range_dist(0, n);

    auto query = [&]{
        return query_dist(rng);
    };
    auto index = [&]{
        return index_dist(rng);
    };
    auto index_n = [&] {
        return range_dist(rng);
    };
    auto range = [&]{
        int l = index_n();
        int r = index_n();
        if (l > r) std::swap(l, r);
        return std::make_pair(l, r);
    };
    auto nonempty_range = [&] {
        int l, r;
        do {
            std::tie(l, r) = range();
        } while (l >= r);
        return std::make_pair(l, r);
    };
    auto value = [&] {
        return value_dist(rng);
    };
    auto value_range = [&]{
        T l = value();
        T r = value();
        if (l > r) std::swap(l, r);
        return std::make_pair(l, r);
    };

    while (q --> 0) {
        int qt = query();
        if (qt == 0) {
            int i = index();
            assert(naive.access(i) == wm.access(i));
        } else if (qt == 1) {
            T v = value();
            int i = index_n();
            assert(naive.rank(v, i) == wm.rank(v, i));
        } else if (qt == 2) {
            auto [l, r] = range();
            int k = rng() % (r - l + 1) + l;
            T x = value();
            assert(naive.range_xor_kth_smallest(l, r, k, x) == wm.range_xor_kth_smallest(l, r, k, x));
        } else if (qt == 3) {
            auto [l, r] = range();
            int k = rng() % (r - l + 1) + l;
            T x = value();
            assert(naive.range_xor_kth_largest(l, r, k, x) == wm.range_xor_kth_largest(l, r, k, x));
        } else if (qt == 4) {
            auto [l, r] = nonempty_range();
            T x = value();
            assert(naive.range_xor_min(l, r, x) == wm.range_xor_min(l, r, x));
        } else if (qt == 5) {
            auto [l, r] = nonempty_range();
            T x = value();
            assert(naive.range_xor_max(l, r, x) == wm.range_xor_max(l, r, x));
        } else if (qt == 6) {
            auto [l, r] = range();
            T x = value();
            T upper = value();
            assert(naive.range_xor_freq(l, r, x, upper) == wm.range_xor_freq(l, r, x, upper));
        } else if (qt == 7) {
            auto [l, r] = range();
            T x = value();
            auto [lower, upper] = value_range();
            assert(naive.range_xor_freq(l, r, x, lower, upper) == wm.range_xor_freq(l, r, x, lower, upper));
        } else if (qt == 8) {
            auto [l, r] = range();
            T x = value();
            T v = value();
            assert(naive.range_xor_min_geq(l, r, x, v) == wm.range_xor_min_geq(l, r, x, v));
        } else if (qt == 9) {
            auto [l, r] = range();
            T x = value();
            T v = value();
            assert(naive.range_xor_min_gt(l, r, x, v) == wm.range_xor_min_gt(l, r, x, v));
        } else if (qt == 10) {
            auto [l, r] = range();
            T x = value();
            T v = value();
            assert(naive.range_xor_max_lt(l, r, x, v) == wm.range_xor_max_lt(l, r, x, v));
        } else if (qt == 11) {
            auto [l, r] = range();
            T x = value();
            T v = value();
            assert(naive.range_xor_max_leq(l, r, x, v) == wm.range_xor_max_leq(l, r, x, v));
        } else if (qt == 12) {
            auto [l, r] = range();
            int k = rng() % (r - l + 1) + l;
            assert(naive.range_kth_smallest(l, r, k) == wm.range_kth_smallest(l, r, k));
        } else if (qt == 13) {
            auto [l, r] = range();
            int k = rng() % (r - l + 1) + l;
            assert(naive.range_kth_largest(l, r, k) == wm.range_kth_largest(l, r, k));
        } else if (qt == 14) {
            auto [l, r] = nonempty_range();
            assert(naive.range_min(l, r) == wm.range_min(l, r));
        } else if (qt == 15) {
            auto [l, r] = nonempty_range();
            assert(naive.range_max(l, r) == wm.range_max(l, r));
        } else if (qt == 16) {
            auto [l, r] = range();
            T upper = value();
            assert(naive.range_freq(l, r, upper) == wm.range_freq(l, r, upper));
        } else if (qt == 17) {
            auto [l, r] = range();
            auto [lower, upper] = value_range();
            assert(naive.range_freq(l, r, lower, upper) == wm.range_freq(l, r, lower, upper));
        } else if (qt == 18) {
            auto [l, r] = range();
            T v = value();
            assert(naive.range_min_geq(l, r, v) == wm.range_min_geq(l, r, v));
        } else if (qt == 19) {
            auto [l, r] = range();
            T v = value();
            assert(naive.range_min_gt(l, r, v) == wm.range_min_gt(l, r, v));
        } else if (qt == 20) {
            auto [l, r] = range();
            T v = value();
            assert(naive.range_max_lt(l, r, v) == wm.range_max_lt(l, r, v));
        } else if (qt == 21) {
            auto [l, r] = range();
            T v = value();
            assert(naive.range_max_leq(l, r, v) == wm.range_max_leq(l, r, v));
        }
    }
    std::cerr << "done" << std::endl;
}

void tests() {
    test<int, 1>(100, 1000);
    test<int, 2>(100, 1000);
    test<int, 5>(100, 1000);
    test<int, 7>(100, 100000);
    test<int, 16>(100, 100000);
    test<int, 30>(100, 100000);
    test<long long, 16>(100, 100000);
    test<long long, 62>(100, 100000);

    test<int, 16>(1, 100);
    test<long long, 16>(1, 100);
}

int main() {
    tests();
    std::cout << "Hello World" << std::endl;
    return 0;
}