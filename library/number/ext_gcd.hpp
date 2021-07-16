#ifndef SUISEN_EXT_GCD
#define SUISEN_EXT_GCD

#include <cassert>
#include <tuple>
#include <utility>

namespace suisen {
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    return x < 0 ? x + m : x;
}

// returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. 
std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
    long long x = 1, y = 0;
    long long z = 0, w = 1;
    long long tmp;
    while (b) {
        long long p = a / b, q = a % b;
        tmp = x - y * p; x = y; y = tmp;
        tmp = z - w * p; z = w; w = tmp;
        a = b; b = q;
    }
    if (a >= 0) return {x, z, a};
    else return {-x, -z, -a};
}

// returns {x,g} s.t. a*x=g (mod m)
std::pair<long long, long long> gcd_inv(long long a, long long m) {
    auto [x, y, g] = ext_gcd(a, m);
    return {safe_mod(x, m), g};
}

// returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime error.
long long inv_mod(long long a, long long mod) {
    auto [inv, y, g] = ext_gcd(a, mod);
    assert(g == 1);
    return safe_mod(inv, mod);
}
} // namespace suisen

#endif // SUISEN_EXT_GCD
