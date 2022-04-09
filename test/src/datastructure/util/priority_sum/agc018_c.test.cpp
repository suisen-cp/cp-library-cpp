#define PROBLEM "https://atcoder.jp/contests/agc018/tasks/agc018_c"

#include <iostream>
#include <vector>

#include "library/datastructure/util/priority_sum.hpp"
#include "library/util/permutation.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x, y, z;
    std::cin >> x >> y >> z;

    const int n = x + y + z;
    std::vector<long long> b(n), c(n), d(n);

    long long sum_a = 0;
    for (int i = 0; i < n; i++) {
        long long a, x, y;
        std::cin >> a >> x >> y;
        b[i] = a - x;
        c[i] = a - y;
        d[i] = x - y;
        sum_a += a;
    }

    auto p = suisen::Permutation::index_sort(b);
    b = p.permute(b);
    c = p.permute(c);
    d = p.permute(d);

    std::vector<long long> sum_t(n);
    suisen::MaximumPrioritySum<long long> topk_t;
    for (int i = n - 1; i >= y - 1; --i) {
        if (i <= y + z - 1) {
            sum_t[i] = topk_t.get_sum();
            topk_t.incr_k();
        }
        topk_t.insert(c[i]);
    }
    std::vector<long long> sum_h(n);
    suisen::MaximumPrioritySum<long long> topk_h;
    long long sum_b = 0;
    for (int i = 0; i <= y + z - 1; ++i) {
        sum_b += b[i];
        topk_h.insert(d[i]);
        if (i >= y - 1) {
            sum_h[i] = topk_h.get_sum() + sum_b;
            topk_h.incr_k();
        }
    }
    long long ans = 0;
    for (int i = y - 1; i < y + z; i++) {
        ans = std::max(ans, sum_a - (sum_h[i] + sum_t[i]));
    }
    std::cout << ans << std::endl;
    return 0;
}