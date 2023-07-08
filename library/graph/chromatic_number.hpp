#ifndef SUISEN_CHROMATIC_NUMBER
#define SUISEN_CHROMATIC_NUMBER

#include <vector>

#include <atcoder/modint>

namespace suisen {
    namespace detail {
        template <int mod>
        int chromatic_number(const int n, const std::vector<int> &I) {
            std::vector<int> f(1 << n);
            for (int s = 0; s < 1 << n; ++s) {
                f[s] = (n - __builtin_popcount(s)) & 1 ? mod - 1 : 1;
            }
            for (int k = 1; k < n; ++k) {
                long long sum = 0;
                for (int s = 0; s < 1 << n; ++s) {
                    f[s] = static_cast<long long>(f[s]) * I[s] % mod;
                    sum += f[s];
                }
                if (sum % mod) return k;
            }
            return n;
        }

    } // namespace detail::chromatic_number
    
    int chromatic_number(const int n, const std::vector<std::pair<int, int>>& edges) {
        if (n == 0) return 0;

        const int m = edges.size();
        std::vector<int> g(n);
        for (const auto& [u, v] : edges) {
            g[u] |= 1 << v;
            g[v] |= 1 << u;
        }

        std::vector<int> I(1 << n); // I[S] := # of independent sets T \subseteq S
        I[0] = 1;
        for (int s = 1; s < 1 << n; ++s) {
            const int v = __builtin_ctz(s), t = s ^ (1 << v);
            I[s] = I[t] + I[t & ~g[v]];
        }

        return std::min(detail::chromatic_number<998244353>(n, I), detail::chromatic_number<1000000007>(n, I));
    }
} // namespace suisen

#endif // SUISEN_CHROMATIC_NUMBER
