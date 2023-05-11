#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/util/step_sum.hpp"

template <typename T>
struct StepSumNaive {
    template <typename Sequence>
    StepSumNaive(const Sequence& a, int step): _dat(a.begin(), a.end()), _step(step), _n(_dat.size()) {}
    T sum(int k, int l, int r) const {
        T ans = 0;
        for (int i = k; i < std::min(r, _n); i += _step) {
            if (i >= l) {
                ans += _dat[i];
            }
        }
        return ans;
    }
    T operator()(int k, int l, int r) const { return sum(k, l, r); }
private:
    std::vector<T> _dat;
    int _step, _n;
};
template <typename Sequence>
StepSumNaive(Sequence, int) -> StepSumNaive<typename Sequence::value_type>;

#include <cassert>
#include <random>

void test() {
    std::mt19937 rng{0};

    int n = 100, v = 10000000;
    std::vector<int> a(n);
    for (auto& e : a) e = rng() % v - v / 2;

    for (int step = 1; step <= n; ++step) {
        suisen::StepSum sum1(a, step);
        StepSumNaive sum2(a, step);
        for (int k = 0; k < step; ++k) {
            for (int l = -10; l <= n + 10; ++l) {
                for (int r = -10; r <= n + 10; ++r) {
                    if (sum1(k, l, r) != sum2(k, l, r)) {
                        for (int e : a) std::cerr << e << ",";
                        std::cerr << std::endl;
                        std::cerr << "step = " << step << std::endl;
                        std::cerr << "(k, l, r) = (" << k << ", " << l << ", " << r << ")" << std::endl;

                        std::cerr << "Actual  :" << sum1(k, l, r) << std::endl;
                        std::cerr << "Expected:" << sum2(k, l, r) << std::endl;
                        assert(false);
                    }
                }
            }
        }
    }
}

struct S {
    using value_type = int;
    std::vector<int> a;
    auto begin() const { return a.begin(); }
    auto end() const { return a.end(); }
};

int main() {
    suisen::StepSum sum(S{std::vector<int>{1}}, 2);
    suisen::StepSum sum2(std::vector<long long>{1}, 2);
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
