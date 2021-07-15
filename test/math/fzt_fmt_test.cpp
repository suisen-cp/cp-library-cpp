#include "../../library/math/fmt.hpp"
#include "../../library/math/fzt.hpp"

template <typename T>
std::vector<T> naive_fzt_subset(const int n, std::vector<T> f) {
    int sz = f.size();
    assert(sz == 1 << n);
    std::vector<T> g(sz, 0);
    for (int s = 0; s < 1 << n; ++s) {
        for (int t = s;; t = (t - 1) & s) {
            g[s] += f[t];
            if (t == 0) break;
        }
    }
    return g;
}

template <typename T>
std::vector<T> naive_fzt_supset(const int n, std::vector<T> f) {
    int sz = f.size();
    assert(sz == 1 << n);
    std::vector<T> g(sz, 0);
    for (int s = 0; s < 1 << n; ++s) {
        for (int t = s;; t = (t - 1) & s) {
            g[t] += f[s];
            if (t == 0) break;
        }
    }
    return g;
}

int main() {
    []{
        int log = 3;
        std::vector<int> f = { 1, 1, 2, 3, 4, 5, 6, 7 };
        std::vector<int> fzt_subset_expected = naive_fzt_subset(log, f);
        fzt_subset(log, f);
        assert(f == fzt_subset_expected);
    }(), []{
        int log = 3;
        std::vector<int> f = { 1, 1, 2, 3, 4, 5, 6, 7 };
        std::vector<int> fzt_supset_expected = naive_fzt_supset(log, f);
        fzt_supset(log, f);
        assert(f == fzt_supset_expected);
    }();
}