#ifndef SUISEN_DISCRETE_LOGARITHM
#define SUISEN_DISCRETE_LOGARITHM

#include <cmath>
#include <unordered_map>
#include <numeric>

namespace suisen {
    namespace internal::discrete_logarithm {
        int floor_log2(int m) {
            int res = 0;
            while (1 << (res + 1) <= m) ++res;
            return res;
        }
    }

    template <typename mint>
    int discrete_logarithm_coprime(mint x, mint y) {
        const int m = mint::mod();
        if (y == 1 or m == 1) return 0;
        if (x == 0) return y == 0 ? 1 : -1;
        const int p = ::sqrt(m) + 1;
        mint a = mint(x).inv().pow(p);
        std::unordered_map<int, int> mp;
        mint pow_x = 1;
        for (int j = 0; j < p; ++j, pow_x *= x) mp.try_emplace(pow_x.val(), j);
        mint ya = y;
        for (int i = 0; i < p; ++i, ya *= a) {
            if (auto it = mp.find(ya.val()); it != mp.end()) return p * i + it->second;
        }
        return -1;
    }

    template <typename mint>
    int discrete_logarithm(mint x, mint y) {
        using namespace internal::discrete_logarithm;
        const int m = mint::mod();
        if (m == 1) return 0;
        const int d = floor_log2(m);
        mint pow_x = 1;
        for (int i = 0; i < d; ++i, pow_x *= x) if (pow_x == y) return i;
        const int g = std::gcd(pow_x.val(), m);
        if (y.val() % g) return -1;
        mint::set_mod(m / g);
        const int t = discrete_logarithm_coprime(mint(x.val()), mint(y.val()) * mint(pow_x.val()).inv());
        mint::set_mod(m);
        return t != -1 ? d + t : -1;
    }
} // namespace suisen


#endif // SUISEN_DISCRETE_LOGARITHM
