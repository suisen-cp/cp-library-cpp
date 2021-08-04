#ifndef SUISEN_MULTIPLE_TRANSFORM
#define SUISEN_MULTIPLE_TRANSFORM

#include <vector>

namespace suisen::multiple_transform {

// Calculates `g` s.t. g(n) = Sum_{n | m} f(m) inplace.
template <typename T>
void zeta(std::vector<T> &f) {
    const int n = f.size();
    std::vector<char> is_prime(n, true);
    auto cum = [&](const int p) {
        const int qmax = (n - 1) / p, rmax = qmax * p;
        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {
            f[q] += f[pq];
            is_prime[pq] = false;
        }
    };
    cum(2);
    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);
}

// Calculates `f` s.t. g(n) = Sum_{n | m} f(m) inplace.
template <typename T>
void mobius(std::vector<T> &f) {
    const int n = f.size();
    std::vector<char> is_prime(n, true);
    auto diff = [&](const int p) {
        for (int q = 1, pq = p; pq < n; ++q, pq += p) {
            f[q] -= f[pq];
            is_prime[pq] = false;
        }
    };
    diff(2);
    for (int p = 3; p < n; p += 2) if (is_prime[p]) diff(p);
}

} // namespace suisen:: multiple_transform


#endif // SUISEN_MULTIPLE_TRANSFORM
