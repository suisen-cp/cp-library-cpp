---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/binomial_coefficient_small_r_offline.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include\
    \ <vector>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\nnamespace\
    \ suisen {\n    namespace internal::binom_small_r_offline {\n        template\
    \ <typename mint>\n        using Polynomial = std::vector<mint>;\n\n        //\
    \ g s.t. fg=1 mod x^n\n        // O(nlog n)\n        template <typename mint>\n\
    \        Polynomial<mint> inv(Polynomial<mint> f, int n) {\n            const\
    \ int siz_f = f.size();\n\n            Polynomial<mint> f_fft, g_fft;\n      \
    \      Polynomial<mint> g{ f[0].inv() };\n            for (int k = 1; k < n; k\
    \ *= 2) {\n                f_fft = Polynomial<mint>(f.begin(), f.begin() + std::min(siz_f,\
    \ 2 * k));\n                g_fft = g;\n                f_fft.resize(2 * k);\n\
    \                g_fft.resize(2 * k);\n                atcoder::internal::butterfly(f_fft);\n\
    \                atcoder::internal::butterfly(g_fft);\n\n                Polynomial<mint>\
    \ fg(2 * k);\n                for (int i = 0; i < 2 * k; ++i) {\n            \
    \        fg[i] = f_fft[i] * g_fft[i];\n                }\n                atcoder::internal::butterfly_inv(fg);\n\
    \                for (int i = 0; i < k; ++i) {\n                    fg[i] = std::exchange(fg[k\
    \ + i], 0);\n                }\n                atcoder::internal::butterfly(fg);\n\
    \                for (int i = 0; i < 2 * k; ++i) {\n                    fg[i]\
    \ *= g_fft[i];\n                }\n                atcoder::internal::butterfly_inv(fg);\n\
    \                const mint iz = mint(2 * k).inv(), c = -iz * iz;\n          \
    \      g.resize(2 * k);\n                for (int i = 0; i < k; ++i) {\n     \
    \               g[k + i] = fg[i] * c;\n                }\n            }\n    \
    \        g.resize(n);\n            return g;\n        }\n\n        // q s.t. qg=f-(f\
    \ mod g)\n        // O(k log k) where k:=|f|+|g|\n        template <typename mint>\n\
    \        Polynomial<mint> poly_div(Polynomial<mint> f, Polynomial<mint> g) {\n\
    \            while (not f.empty() and f.back() == 0) {\n                f.pop_back();\n\
    \            }\n            while (not g.empty() and g.back() == 0) {\n      \
    \          g.pop_back();\n            }\n\n            const int deg_f = static_cast<int>(f.size())\
    \ - 1, deg_g = static_cast<int>(g.size()) - 1;\n            assert(deg_g >= 0);\n\
    \            if (deg_f < deg_g) {\n                return {};\n            }\n\
    \n            std::reverse(f.begin(), f.end());\n            std::reverse(g.begin(),\
    \ g.end());\n            const int deg_q = deg_f - deg_g;\n            Polynomial<mint>\
    \ q = atcoder::convolution(f, inv(g, deg_q + 1));\n            q.resize(deg_q\
    \ + 1);\n            std::reverse(q.begin(), q.end());\n            return q;\n\
    \        }\n\n        // f mod g\n        // O(k log k) where k:=|f|+|g|\n   \
    \     template <typename mint>\n        Polynomial<mint> poly_mod(Polynomial<mint>\
    \ f, const Polynomial<mint>& g) {\n            Polynomial<mint> q = poly_div(f,\
    \ g);\n            Polynomial<mint> qg = atcoder::convolution(q, g);\n       \
    \     for (std::size_t i = 0; i < std::min(f.size(), qg.size()); ++i) {\n    \
    \            f[i] -= qg[i];\n            }\n            while (not f.empty() and\
    \ f.back() == 0) {\n                f.pop_back();\n            }\n           \
    \ return f;\n        }\n\n        // result[i][j] = S1[2^i,j] * (is_signed ? (-1)^(2^i+j)\
    \ : +1) for 0<=i<t, 0<=j<=2^i\n        // O(t*2^t)\n        template <bool is_signed,\
    \ typename mint>\n        std::vector<Polynomial<mint>> stirling_number1_doubling(int\
    \ t) {\n            const int n = 1 << t;\n\n            std::vector<mint> fac(n\
    \ + 1), fac_inv(n + 1);\n            fac[0] = 1;\n            for (int i = 1;\
    \ i <= n; ++i) {\n                fac[i] = fac[i - 1] * i;\n            }\n  \
    \          fac_inv[n] = fac[n].inv();\n            for (int i = n; i >= 1; --i)\
    \ {\n                fac_inv[i - 1] = fac_inv[i] * i;\n            }\n\n     \
    \       // S1[i][j] = S1[2^i,j] for 0<=i<t, 0<=j<=2^i\n            std::vector<Polynomial<mint>>\
    \ S1(t);\n            S1[0] = { 1, 0 };\n\n            for (int l = 0; l < t -\
    \ 1; ++l) {\n                const int m = 1 << l;\n                Polynomial<mint>\
    \ f(m + 1), g(m + 1);\n                mint pow_m = 1;\n                for (int\
    \ i = 0; i <= m; ++i) {\n                    f[i] = pow_m * fac_inv[i];\n    \
    \                g[i] = S1[l][i] * fac[m - i];\n                    pow_m *= (is_signed\
    \ ? -m : +m);\n                }\n                f = atcoder::convolution(f,\
    \ g);\n                f.resize(m + 1);\n                for (int i = 0; i <=\
    \ m; ++i) {\n                    f[i] *= fac_inv[m - i];\n                }\n\
    \                S1[l + 1] = atcoder::convolution(S1[l], f);\n            }\n\
    \            for (auto& S1_i : S1) {\n                std::reverse(S1_i.begin(),\
    \ S1_i.end());\n            }\n            return S1;\n        }\n\n        //\
    \ O(|xs|*log(t)^2) where t:=min(|f|,|xs|)\n        template <typename mint>\n\
    \        std::vector<mint> multipoint_evaluation(const Polynomial<mint>& f, const\
    \ std::vector<mint>& xs) {\n            const int n = f.size();\n            const\
    \ int m = xs.size();\n            if (n == 0) {\n                return std::vector<mint>(m,\
    \ 0);\n            }\n\n            auto impl = [&f](const std::vector<mint>&\
    \ xs) {\n                const int n = xs.size();\n                std::vector<Polynomial<mint>>\
    \ seg(2 * n);\n                for (int i = 0; i < n; ++i) {\n               \
    \     seg[n + i] = Polynomial<mint>{ -xs[i], 1 };\n                }\n       \
    \         for (int i = n - 1; i > 0; --i) {\n                    seg[i] = atcoder::convolution(seg[i\
    \ * 2], seg[i * 2 + 1]);\n                }\n                seg[1] = poly_mod(f,\
    \ seg[1]);\n                for (int i = 2; i < 2 * n; ++i) {\n              \
    \      seg[i] = poly_mod(seg[i / 2], seg[i]);\n                }\n           \
    \     std::vector<mint> ys(n);\n                for (int i = 0; i < n; ++i) {\n\
    \                    ys[i] = seg[n + i].size() ? seg[n + i][0] : 0;\n        \
    \        }\n                return ys;\n            };\n\n            std::vector<mint>\
    \ ys(m);\n            for (int l = 0; l < m; l += n) {\n                int r\
    \ = std::min(m, l + n);\n                std::vector<mint> ys_lr = impl(std::vector<mint>(xs.begin()\
    \ + l, xs.begin() + r));\n                std::move(ys_lr.begin(), ys_lr.end(),\
    \ ys.begin() + l);\n            }\n            return ys;\n        }\n    }\n\n\
    \    // O(QlogR(log min(Q,R))^2 + RlogR)\n    template <typename mint>\n    std::vector<mint>\
    \ binomial_coefficient_small_r_offline(std::vector<std::pair<long long, int>>\
    \ queries) {\n        using namespace internal::binom_small_r_offline;\n\n   \
    \     const int q = queries.size();\n        const int max_r = [&] {\n       \
    \     int max_r = 0;\n            for (auto [n, r] : queries) {\n            \
    \    max_r = std::max(max_r, r);\n            }\n            return max_r;\n \
    \       }(); // r <= max_r\n        const int log_r = [&] {\n            int log_r\
    \ = 0;\n            while (1 << log_r <= max_r) {\n                ++log_r;\n\
    \            }\n            return log_r;\n        }(); // r < 2^(log_r)\n\n \
    \       const std::vector<mint> fac_inv = [&] {\n            mint fac_max_r =\
    \ 1;\n            for (int i = 1; i <= max_r; ++i) {\n                fac_max_r\
    \ = fac_max_r * i;\n            }\n            std::vector<mint> fac_inv(max_r\
    \ + 1);\n            fac_inv[max_r] = fac_max_r.inv();\n            for (int i\
    \ = max_r; i >= 1; --i) {\n                fac_inv[i - 1] = fac_inv[i] * i;\n\
    \            }\n            return fac_inv;\n        }();\n\n        std::vector<mint>\
    \ ans(q);\n        for (int i = 0; i < q; ++i) {\n            ans[i] = fac_inv[queries[i].second];\n\
    \        }\n\n        // O(R log R)\n        auto S1 = stirling_number1_doubling<true,\
    \ mint>(log_r);\n\n        // sum[bit=0,log R] O(Q*bit^2) = O(Q(log R)^3)\n  \
    \      for (int bit = 0; bit < log_r; ++bit) {\n            // x (x - 1) (x -\
    \ 2) ... (x - 2^bit + 1)\n            std::vector<mint> xs;\n            std::vector<int>\
    \ ids;\n\n            // O(Q)\n            for (int i = 0; i < q; ++i) {\n   \
    \             auto& [n, r] = queries[i];\n                if ((r >> bit) & 1)\
    \ {\n                    xs.push_back(n);\n                    ids.push_back(i);\n\
    \                    n -= 1 << bit;\n                    r -= 1 << bit;\n    \
    \            }\n            }\n            const int siz = xs.size();\n\n    \
    \        // O(min(Q*bit^2, Q(logQ)^2 + bit 2^bit))\n            std::vector<mint>\
    \ ys = multipoint_evaluation<mint>(S1[bit], xs);\n            for (int i = 0;\
    \ i < siz; ++i) {\n                ans[ids[i]] *= ys[i];\n            }\n    \
    \    }\n\n        return ans;\n    }\n}\n\n\n"
  code: "#ifndef SUISEN_BINOMIAL_COEFFICIENT_SMALL_R_OFFLINE\n#define SUISEN_BINOMIAL_COEFFICIENT_SMALL_R_OFFLINE\n\
    \n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\
    \n#include <atcoder/modint>\n#include <atcoder/convolution>\n\nnamespace suisen\
    \ {\n    namespace internal::binom_small_r_offline {\n        template <typename\
    \ mint>\n        using Polynomial = std::vector<mint>;\n\n        // g s.t. fg=1\
    \ mod x^n\n        // O(nlog n)\n        template <typename mint>\n        Polynomial<mint>\
    \ inv(Polynomial<mint> f, int n) {\n            const int siz_f = f.size();\n\n\
    \            Polynomial<mint> f_fft, g_fft;\n            Polynomial<mint> g{ f[0].inv()\
    \ };\n            for (int k = 1; k < n; k *= 2) {\n                f_fft = Polynomial<mint>(f.begin(),\
    \ f.begin() + std::min(siz_f, 2 * k));\n                g_fft = g;\n         \
    \       f_fft.resize(2 * k);\n                g_fft.resize(2 * k);\n         \
    \       atcoder::internal::butterfly(f_fft);\n                atcoder::internal::butterfly(g_fft);\n\
    \n                Polynomial<mint> fg(2 * k);\n                for (int i = 0;\
    \ i < 2 * k; ++i) {\n                    fg[i] = f_fft[i] * g_fft[i];\n      \
    \          }\n                atcoder::internal::butterfly_inv(fg);\n        \
    \        for (int i = 0; i < k; ++i) {\n                    fg[i] = std::exchange(fg[k\
    \ + i], 0);\n                }\n                atcoder::internal::butterfly(fg);\n\
    \                for (int i = 0; i < 2 * k; ++i) {\n                    fg[i]\
    \ *= g_fft[i];\n                }\n                atcoder::internal::butterfly_inv(fg);\n\
    \                const mint iz = mint(2 * k).inv(), c = -iz * iz;\n          \
    \      g.resize(2 * k);\n                for (int i = 0; i < k; ++i) {\n     \
    \               g[k + i] = fg[i] * c;\n                }\n            }\n    \
    \        g.resize(n);\n            return g;\n        }\n\n        // q s.t. qg=f-(f\
    \ mod g)\n        // O(k log k) where k:=|f|+|g|\n        template <typename mint>\n\
    \        Polynomial<mint> poly_div(Polynomial<mint> f, Polynomial<mint> g) {\n\
    \            while (not f.empty() and f.back() == 0) {\n                f.pop_back();\n\
    \            }\n            while (not g.empty() and g.back() == 0) {\n      \
    \          g.pop_back();\n            }\n\n            const int deg_f = static_cast<int>(f.size())\
    \ - 1, deg_g = static_cast<int>(g.size()) - 1;\n            assert(deg_g >= 0);\n\
    \            if (deg_f < deg_g) {\n                return {};\n            }\n\
    \n            std::reverse(f.begin(), f.end());\n            std::reverse(g.begin(),\
    \ g.end());\n            const int deg_q = deg_f - deg_g;\n            Polynomial<mint>\
    \ q = atcoder::convolution(f, inv(g, deg_q + 1));\n            q.resize(deg_q\
    \ + 1);\n            std::reverse(q.begin(), q.end());\n            return q;\n\
    \        }\n\n        // f mod g\n        // O(k log k) where k:=|f|+|g|\n   \
    \     template <typename mint>\n        Polynomial<mint> poly_mod(Polynomial<mint>\
    \ f, const Polynomial<mint>& g) {\n            Polynomial<mint> q = poly_div(f,\
    \ g);\n            Polynomial<mint> qg = atcoder::convolution(q, g);\n       \
    \     for (std::size_t i = 0; i < std::min(f.size(), qg.size()); ++i) {\n    \
    \            f[i] -= qg[i];\n            }\n            while (not f.empty() and\
    \ f.back() == 0) {\n                f.pop_back();\n            }\n           \
    \ return f;\n        }\n\n        // result[i][j] = S1[2^i,j] * (is_signed ? (-1)^(2^i+j)\
    \ : +1) for 0<=i<t, 0<=j<=2^i\n        // O(t*2^t)\n        template <bool is_signed,\
    \ typename mint>\n        std::vector<Polynomial<mint>> stirling_number1_doubling(int\
    \ t) {\n            const int n = 1 << t;\n\n            std::vector<mint> fac(n\
    \ + 1), fac_inv(n + 1);\n            fac[0] = 1;\n            for (int i = 1;\
    \ i <= n; ++i) {\n                fac[i] = fac[i - 1] * i;\n            }\n  \
    \          fac_inv[n] = fac[n].inv();\n            for (int i = n; i >= 1; --i)\
    \ {\n                fac_inv[i - 1] = fac_inv[i] * i;\n            }\n\n     \
    \       // S1[i][j] = S1[2^i,j] for 0<=i<t, 0<=j<=2^i\n            std::vector<Polynomial<mint>>\
    \ S1(t);\n            S1[0] = { 1, 0 };\n\n            for (int l = 0; l < t -\
    \ 1; ++l) {\n                const int m = 1 << l;\n                Polynomial<mint>\
    \ f(m + 1), g(m + 1);\n                mint pow_m = 1;\n                for (int\
    \ i = 0; i <= m; ++i) {\n                    f[i] = pow_m * fac_inv[i];\n    \
    \                g[i] = S1[l][i] * fac[m - i];\n                    pow_m *= (is_signed\
    \ ? -m : +m);\n                }\n                f = atcoder::convolution(f,\
    \ g);\n                f.resize(m + 1);\n                for (int i = 0; i <=\
    \ m; ++i) {\n                    f[i] *= fac_inv[m - i];\n                }\n\
    \                S1[l + 1] = atcoder::convolution(S1[l], f);\n            }\n\
    \            for (auto& S1_i : S1) {\n                std::reverse(S1_i.begin(),\
    \ S1_i.end());\n            }\n            return S1;\n        }\n\n        //\
    \ O(|xs|*log(t)^2) where t:=min(|f|,|xs|)\n        template <typename mint>\n\
    \        std::vector<mint> multipoint_evaluation(const Polynomial<mint>& f, const\
    \ std::vector<mint>& xs) {\n            const int n = f.size();\n            const\
    \ int m = xs.size();\n            if (n == 0) {\n                return std::vector<mint>(m,\
    \ 0);\n            }\n\n            auto impl = [&f](const std::vector<mint>&\
    \ xs) {\n                const int n = xs.size();\n                std::vector<Polynomial<mint>>\
    \ seg(2 * n);\n                for (int i = 0; i < n; ++i) {\n               \
    \     seg[n + i] = Polynomial<mint>{ -xs[i], 1 };\n                }\n       \
    \         for (int i = n - 1; i > 0; --i) {\n                    seg[i] = atcoder::convolution(seg[i\
    \ * 2], seg[i * 2 + 1]);\n                }\n                seg[1] = poly_mod(f,\
    \ seg[1]);\n                for (int i = 2; i < 2 * n; ++i) {\n              \
    \      seg[i] = poly_mod(seg[i / 2], seg[i]);\n                }\n           \
    \     std::vector<mint> ys(n);\n                for (int i = 0; i < n; ++i) {\n\
    \                    ys[i] = seg[n + i].size() ? seg[n + i][0] : 0;\n        \
    \        }\n                return ys;\n            };\n\n            std::vector<mint>\
    \ ys(m);\n            for (int l = 0; l < m; l += n) {\n                int r\
    \ = std::min(m, l + n);\n                std::vector<mint> ys_lr = impl(std::vector<mint>(xs.begin()\
    \ + l, xs.begin() + r));\n                std::move(ys_lr.begin(), ys_lr.end(),\
    \ ys.begin() + l);\n            }\n            return ys;\n        }\n    }\n\n\
    \    // O(QlogR(log min(Q,R))^2 + RlogR)\n    template <typename mint>\n    std::vector<mint>\
    \ binomial_coefficient_small_r_offline(std::vector<std::pair<long long, int>>\
    \ queries) {\n        using namespace internal::binom_small_r_offline;\n\n   \
    \     const int q = queries.size();\n        const int max_r = [&] {\n       \
    \     int max_r = 0;\n            for (auto [n, r] : queries) {\n            \
    \    max_r = std::max(max_r, r);\n            }\n            return max_r;\n \
    \       }(); // r <= max_r\n        const int log_r = [&] {\n            int log_r\
    \ = 0;\n            while (1 << log_r <= max_r) {\n                ++log_r;\n\
    \            }\n            return log_r;\n        }(); // r < 2^(log_r)\n\n \
    \       const std::vector<mint> fac_inv = [&] {\n            mint fac_max_r =\
    \ 1;\n            for (int i = 1; i <= max_r; ++i) {\n                fac_max_r\
    \ = fac_max_r * i;\n            }\n            std::vector<mint> fac_inv(max_r\
    \ + 1);\n            fac_inv[max_r] = fac_max_r.inv();\n            for (int i\
    \ = max_r; i >= 1; --i) {\n                fac_inv[i - 1] = fac_inv[i] * i;\n\
    \            }\n            return fac_inv;\n        }();\n\n        std::vector<mint>\
    \ ans(q);\n        for (int i = 0; i < q; ++i) {\n            ans[i] = fac_inv[queries[i].second];\n\
    \        }\n\n        // O(R log R)\n        auto S1 = stirling_number1_doubling<true,\
    \ mint>(log_r);\n\n        // sum[bit=0,log R] O(Q*bit^2) = O(Q(log R)^3)\n  \
    \      for (int bit = 0; bit < log_r; ++bit) {\n            // x (x - 1) (x -\
    \ 2) ... (x - 2^bit + 1)\n            std::vector<mint> xs;\n            std::vector<int>\
    \ ids;\n\n            // O(Q)\n            for (int i = 0; i < q; ++i) {\n   \
    \             auto& [n, r] = queries[i];\n                if ((r >> bit) & 1)\
    \ {\n                    xs.push_back(n);\n                    ids.push_back(i);\n\
    \                    n -= 1 << bit;\n                    r -= 1 << bit;\n    \
    \            }\n            }\n            const int siz = xs.size();\n\n    \
    \        // O(min(Q*bit^2, Q(logQ)^2 + bit 2^bit))\n            std::vector<mint>\
    \ ys = multipoint_evaluation<mint>(S1[bit], xs);\n            for (int i = 0;\
    \ i < siz; ++i) {\n                ans[ids[i]] *= ys[i];\n            }\n    \
    \    }\n\n        return ans;\n    }\n}\n\n#endif // SUISEN_BINOMIAL_COEFFICIENT_SMALL_R_OFFLINE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/sequence/binomial_coefficient_small_r_offline.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:37:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/sequence/binomial_coefficient_small_r_offline.hpp
layout: document
redirect_from:
- /library/library/sequence/binomial_coefficient_small_r_offline.hpp
- /library/library/sequence/binomial_coefficient_small_r_offline.hpp.html
title: library/sequence/binomial_coefficient_small_r_offline.hpp
---
