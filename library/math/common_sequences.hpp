#ifndef SUISEN_COMMON_SEQ
#define SUISEN_COMMON_SEQ

#include "library/math/fps.hpp"
#include "library/math/factorial.hpp"

namespace suisen {
/**
 * return:
 *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k (unsigned)
 * constraints:
 *   0 <= n <= 10^6
 */
template <typename mint>
std::vector<mint> stirling_number1_reversed(int n) {
    factorial<mint> fac(n);
    int l = 0;
    while ((n >> l) != 0) ++l;
    FPS<mint> a {1};
    int m = 0;
    while (l --> 0) {
        FPS<mint> f(m + 1), g(m + 1);
        mint powm = 1;
        for (int i = 0; i <= m; ++i, powm *= m) {
            f[i] = powm * fac.fac_inv(i);
            g[i] = a[i] * fac.fac(m - i);
        }
        f *= g, f.pre_inplace(m);
        for (int i = 0; i <= m; ++i) f[i] *= fac.fac_inv(m - i);
        a *= f, m *= 2, a.pre_inplace(m);
        if ((n >> l) & 1) {
            a.push_back(0);
            for (int i = m; i > 0; --i) a[i] += m * a[i - 1];
            ++m;
        }
    }
    return a;
}
template <typename mint>
std::vector<mint> stirling_number1(int n) {
    auto a(stirling_number1_reversed<mint>(n));
    std::reverse(a.begin(), a.end());
    return a;
}
/**
 * return:
 *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k, where S1 is the stirling number of the first kind (unsigned).
 * constraints:
 * - 0 <= n <= 10^18
 * - 0 <= k <= 5000
 * - k < mod
 */
template <typename mint>
std::vector<mint> stirling_number1_reversed(const long long n, const int k) {
    inv_mods<mint> invs(k + 1);
    std::vector<mint> a(k + 1, 0);
    a[0] = 1;
    int l = 0;
    while (n >> l) ++l;
    mint m = 0;
    while (l --> 0) {
        std::vector<mint> b(k + 1, 0);
        for (int j = 0; j <= k; ++j) {
            mint tmp = 1;
            for (int i = j; i <= k; ++i) {
                b[i] += a[j] * tmp;
                tmp *= (m - i) * invs[i - j + 1] * m;
            }
        }
        for (int i = k + 1; i --> 0;) {
            mint sum = 0;
            for (int j = 0; j <= i; ++j) sum += a[j] * b[i - j];
            a[i] = sum;
        }
        m *= 2;
        if ((n >> l) & 1) {
            for (int i = k; i > 0; --i) a[i] += m * a[i - 1];
            ++m;
        }
    }
    return a;
}

/**
 * return:
 *   vector<mint> v s.t. v[i] = S2[n,i] for i=0,...,k
 * constraints:
 *   0 <= n <= 10^6
 */
template <typename mint>
std::vector<mint> stirling_number2(int n) {
    factorial<mint> fac(n);
    FPS<mint> a(n + 1), b(n + 1);
    for (int i = 0; i <= n; ++i) {
        a[i] = mint(i).pow(n) * fac.fac_inv(i);
        b[i] = i & 1 ? -fac.fac_inv(i) : fac.fac_inv(i);
    }
    a *= b, a.pre_inplace(n);
    return a;
}

template <typename mint>
std::vector<mint> bernoulli_number(int n) {
    factorial<mint> fac(n);
    FPS<mint> a(n + 1);
    for (int i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);
    a.inv_inplace(n), a.resize(n + 1);
    for (int i = 2; i <= n; ++i) a[i] *= fac.fac(i);
    return a;
}

template <typename mint>
std::vector<mint> partition_number(int n) {
    FPS<mint> inv(n + 1);
    inv[0] = 1;
    for (int i = 1, k = 1; k <= n; k += 3 * i + 1, i++) {
        if (i & 1) --inv[k];
        else ++inv[k];
    }
    for (int i = 1, k = 2; k <= n; k += 3 * i + 2, i++) {
        if (i & 1) --inv[k];
        else ++inv[k];
    }
    inv.inv_inplace(n), inv.resize(n + 1);
    return inv;
}
} // namespace suisen

#endif // SUISEN_COMMON_SEQ
