#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <iostream>
#include <random>

#include "library/uncategorized/static_range_xored_mex_query.hpp"

template <typename T>
struct NaiveSolution {
    NaiveSolution() = default;
    NaiveSolution(const std::vector<T> &dat) : dat(dat) {}

    T minimum_excluded(int l, int r, T x) {
        std::vector<T> st;
        for (int i = l; i < r; ++i) st.push_back(dat[i] ^ x);
        std::sort(st.begin(), st.end());
        st.erase(std::unique(st.begin(), st.end()), st.end());
        st.push_back(std::numeric_limits<int>::max());
        for (int i = 0;; ++i) {
            if (st[i] != i) return i;
        }
    }
private:
    std::vector<T> dat;
};

std::mt19937 rng{0};

template <typename T, int bit_num>
void test(int n, int q) {
    std::uniform_int_distribution<T> value_dist(0, (T(1) << bit_num) - 1);
    std::vector<T> dat(n);
    for (auto &e : dat) e = value_dist(rng);
    
    suisen::RangeXoredMexQuery<T, bit_num> wm(dat);
    NaiveSolution<T> naive(dat);

    for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
        for (int t = 0; t < q; ++t) {
            int x = value_dist(rng);
            assert(wm.minimum_excluded(l, r, x) == naive.minimum_excluded(l, r, x));
        }
    }
    std::cerr << "done" << std::endl;
}

void tests() {
    // std::vector<int> dat { 0, 1, 2, 3, 4 };
    // suisen::RangeXoredMexQuery<int, 3> wm(dat);
    // NaiveSolution<int> naive(dat);
    // for (int l = 0; l <= 5; ++l) for (int r = l; r <= 5; ++r) {
    //     for (int x = 0; x <= 5; ++x) {
    //         std::cerr << "sub array : [";
    //         for (int i = l; i < r; ++i) {
    //             std::cerr << (dat[i] ^ x);
    //             if (i < r - 1) std::cerr << ",";
    //         }
    //         std::cerr << "]" << std::endl;
    //         int mex1 = wm.minimum_excluded(l, r, x);
    //         std::cerr << "actual   : " << mex1 << std::endl;
    //         int mex2 = naive.minimum_excluded(l, r, x);
    //         std::cerr << "expected : " << mex2 << std::endl;
    //     }
    // }


    test<int, 1>(100, 100);
    test<int, 2>(100, 100);
    test<int, 3>(100, 100);
    test<int, 4>(100, 100);
    test<int, 5>(100, 100);
    test<int, 6>(100, 100);
}

int main() {
    tests();
    std::cout << "Hello World" << std::endl;
    return 0;
}