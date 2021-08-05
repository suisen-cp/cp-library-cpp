#ifndef SUISEN_COPRIME_CONVOLUTION
#define SUISEN_COPRIME_CONVOLUTION

#include "library/math/fps.hpp"
#include "library/convolution/dirichlet_convolution.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {

namespace internal {

std::vector<int> count_prime_factor(int n) {
    std::vector<int> res(n, 0);
    auto update = [&res, n](int p) {
        if (res[p] != 0) return;
        for (int q = p; q < n; q += p) ++res[q];
    };
    if (2 < n) update(2);
    for (int p = 3; p < n; p += 2) update(p);
    return res;
}

template <typename mint>
auto to_polynomial(const std::vector<mint> &a, const std::vector<int> &pf_num) {
    int n = a.size();
    std::vector<FPS<mint>> fs(n);
    for (int i = 1; i < n; ++i) {
        fs[i][pf_num[i]] = a[i];
    }
    return fs;
}

} // namespace internal

template <typename mint>
std::vector<mint> coprime_convolution(const std::vector<mint> &a, const std::vector<mint> &b, int n) {
    using namespace internal;
    const int max_size = std::max(int(std::max(a.size(), b.size())), n);
    auto pf_num = count_prime_factor(max_size);
    auto fs = dirichlet_convolution(to_polynomial(a, pf_num), to_polynomial(b, pf_num), n);
    std::vector<mint> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = fs[i][pf_num[i]];
    }
    return res;
}

} // namespace suisen

#endif // SUISEN_COPRIME_CONVOLUTION
