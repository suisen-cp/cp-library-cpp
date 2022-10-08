#ifndef SUISEN_MUL_MOD_2_N_CONVOLUTION
#define SUISEN_MUL_MOD_2_N_CONVOLUTION

#include <array>
#include <cassert>
#include <vector>

#include <atcoder/convolution>

namespace suisen {
    namespace internal::mul_mod_2_n_convolution {
        template <typename T, int n>
        std::vector<T> multiplicative_convolution_mod_2_n_naive(const std::vector<T>& a, const std::vector<T>& b) {
            static constexpr int mask = (1 << n) - 1;
            std::vector<T> c(1 << n);
            for (int i = 0; i < 1 << n; ++i) for (int j = 0; j < 1 << n; ++j) c[(i * j) & mask] += a[i] * b[j];
            return c;
        }

        constexpr int pow_m1(int x) {
            return x & 1 ? -1 : +1;
        }
    }
    template <typename T>
    std::vector<T> multiplicative_convolution_mod_2_n(const std::vector<T>& a, const std::vector<T>& b) {
        using namespace internal::mul_mod_2_n_convolution;
        const int n = [&a] {
            int n = 0;
            while (1 << n < int(a.size())) ++n;
            return n;
        }();
        assert(1 << n == int(a.size()));
        assert(1 << n == int(b.size()));
        const int mask = (1 << n) - 1;
        if (n <= 6) {
            if (n == 0) return multiplicative_convolution_mod_2_n_naive<T, 0>(a, b);
            if (n == 1) return multiplicative_convolution_mod_2_n_naive<T, 1>(a, b);
            if (n == 2) return multiplicative_convolution_mod_2_n_naive<T, 2>(a, b);
            if (n == 3) return multiplicative_convolution_mod_2_n_naive<T, 3>(a, b);
            if (n == 4) return multiplicative_convolution_mod_2_n_naive<T, 4>(a, b);
            if (n == 5) return multiplicative_convolution_mod_2_n_naive<T, 5>(a, b);
            if (n == 6) return multiplicative_convolution_mod_2_n_naive<T, 6>(a, b);
        }
        static constexpr int g = 5;
        std::vector<int> pows(1 << (n - 2));
        std::vector<int> p(1 << n), q(1 << n), r(1 << n);
        for (int i = 0, pow_g = 1; i < 1 << (n - 2); ++i) {
            pows[i] = pow_g;
            q[pow_g] = i;
            r[pow_g] = 0;
            q[-pow_g & mask] = i;
            r[-pow_g & mask] = 1;
            pow_g = (pow_g * g) & mask;
        }
        p[0] = n;
        for (int i = 2; i < 1 << n; i += 2) {
            p[i] = __builtin_ctz(i);
            const int len = 1 << std::max(n - p[i] - 2, 0);
            q[i] = q[i >> p[i]] & (len - 1);
            r[i] = r[i >> p[i]];
        }

        std::array<std::vector<std::vector<T>>, 2> a2{}, b2{}, c2{};
        a2[0].resize(n + 1), a2[1].resize(n + 1);
        b2[0].resize(n + 1), b2[1].resize(n + 1);
        c2[0].resize(n + 1), c2[1].resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            const int len = 1 << std::max(n - i - 2, 0);
            a2[0][i].resize(len), a2[1][i].resize(len);
            b2[0][i].resize(len), b2[1][i].resize(len);
            c2[0][i].resize(len), c2[1][i].resize(len);
        }
        for (int i = 0; i < 1 << n; ++i) {
            a2[r[i]][p[i]][q[i]] += a[i];
            b2[r[i]][p[i]][q[i]] += b[i];
        }
        auto adjust_size = [](std::vector<T>& v, int len) {
            for (int i = len; i < int(v.size()); ++i) v[i & (len - 1)] += v[i];
            v.resize(len);
        };
        
        std::vector<T> c(1 << n);
        constexpr int naive_threshold_log = 4;
        for (int pi = 0; pi <= n; ++pi) for (int pj = 0; pj <= n; ++pj) {
            const int k = pi + pj;
            const int len = 1 << std::max(n - k - 2, 0);
            if (len <= 1 << naive_threshold_log) {
                for (int f = 0; f < 2; ++f) {
                    adjust_size(a2[f][pi], len);
                    adjust_size(b2[f][pj], len);
                }
                for (int af = 0; af < 2; ++af) for (int bf = 0; bf < 2; ++bf) {
                    for (int ai = 0; ai < len; ++ai) for (int bi = 0; bi < len; ++bi) {
                        int j = (pow_m1(af ^ bf) * ((long long) pows[(ai + bi) & (len - 1)] << k)) & mask;
                        c[j] += a2[af][pi][ai] * b2[bf][pj][bi];
                    }
                }
                continue;
            }
            for (int f = 0; f < 2; ++f) {
                adjust_size(a2[f][pi], len);
                adjust_size(b2[f][pj], len);
                atcoder::internal::butterfly(a2[f][pi]);
                atcoder::internal::butterfly(b2[f][pj]);
            }
            const T z = T{ len }.inv();
            for (int i = 0; i < len; ++i) {
                T &au = a2[0][pi][i], &av = a2[1][pi][i];
                T &bu = b2[0][pj][i], &bv = b2[1][pj][i];
                c2[0][k][i] += (au * bu + av * bv) * z;
                c2[1][k][i] += (au * bv + av * bu) * z;
                au *= z, av *= z, bu *= z, bv *= z;
            }
            for (int f = 0; f < 2; ++f) {
                atcoder::internal::butterfly_inv(a2[f][pi]);
                atcoder::internal::butterfly_inv(b2[f][pj]);
            }
        }
        for (int f = 0; f < 2; ++f) for (int k = 0; k < n - 2 - naive_threshold_log; ++k) {
            const int len = 1 << (n - k - 2);
            atcoder::internal::butterfly_inv(c2[f][k]);
            for (int i = 0; i < len; ++i) {
                int j = (pow_m1(f) * ((long long) pows[i] << k)) & mask;
                c[j] += c2[f][k][i];
            }
        }
        return c;
    }
} // namespace suisen


#endif // SUISEN_MUL_MOD_2_N_CONVOLUTION
