#ifndef SUISEN_DIVISOR_TRANSFORM
#define SUISEN_DIVISOR_TRANSFORM

#include <vector>

namespace suisen::internal::arithmetic_operator {}

namespace suisen {
namespace divisor_transform {

using namespace suisen::internal::arithmetic_operator;

// Calculates `g` s.t. g(n) = Sum_{d | n} f(d) inplace.
template <typename T, typename AddAssign>
void zeta(std::vector<T> &f, AddAssign add_assign) {
    const int n = f.size();
    std::vector<char> is_prime(n, true);
    auto cum = [&](const int p) {
        for (int q = 1, pq = p; pq < n; ++q, pq += p) {
            add_assign(f[pq], f[q]);
            is_prime[pq] = false;
        }
    };
    cum(2);
    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);
}

// Calculates `f` s.t. g(n) = Sum_{d | n} f(d) inplace.
template <typename T, typename SubAssign>
void mobius(std::vector<T> &f, SubAssign sub_assign) {
    const int n = f.size();
    std::vector<char> is_prime(n, true);
    auto diff = [&](const int p) {
        const int qmax = (n - 1) / p, rmax = qmax * p;
        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {
            sub_assign(f[pq], f[q]);
            is_prime[pq] = false;
        }
    };
    diff(2);
    for (int p = 3; p < n; p += 2) if (is_prime[p]) diff(p);
}

// Calculates `g` s.t. g(n) = Sum_{d | n} f(d) inplace.
template <typename T>
void zeta(std::vector<T> &f) {
    zeta(f, [](T &a, const T &b) { a += b; });
}

// Calculates `f` s.t. g(n) = Sum_{d | n} f(d) inplace.
template <typename T>
void mobius(std::vector<T> &f) {
    mobius(f, [](T &a, const T &b) { a -= b; });
}

} // namespace divisor_transform

template <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>
struct DivisorTransformGeneral {
    static void transform(std::vector<T> &a) {
        divisor_transform::zeta(a, add_assign);
    }
    static void inverse_transform(std::vector<T> &a) {
        divisor_transform::mobius(a, sub_assign);
    }
};

template <typename T>
struct DivisorTransform {
    static void transform(std::vector<T> &a) {
        divisor_transform::zeta(a);
    }
    static void inverse_transform(std::vector<T> &a) {
        divisor_transform::mobius(a);
    }
};

} // namespace suisen


#endif // SUISEN_DIVISOR_TRANSFORM
