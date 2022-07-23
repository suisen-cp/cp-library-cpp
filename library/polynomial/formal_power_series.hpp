#ifndef SUISEN_FORMAL_POWER_SERIES
#define SUISEN_FORMAL_POWER_SERIES

#include <limits>
#include <optional>
#include <queue>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/fps_naive.hpp"
#include "library/math/inv_mods.hpp"
#include "library/math/modint_extension.hpp"

namespace suisen {
    template <typename mint, atcoder::internal::is_static_modint_t<mint>* = nullptr>
    struct FormalPowerSeries : std::vector<mint> {
        using base_type = std::vector<mint>;
        using value_type = typename base_type::value_type;
        using base_type::vector;

        FormalPowerSeries(const std::initializer_list<value_type> l) : std::vector<value_type>::vector(l) {}
        FormalPowerSeries(const std::vector<value_type>& v) : std::vector<value_type>::vector(v) {}

        int size() const noexcept {
            return base_type::size();
        }
        int deg() const noexcept {
            return size() - 1;
        }
        void ensure(int n) {
            if (size() < n) this->resize(n);
        }

        value_type safe_get(int d) const {
            return d <= deg() ? (*this)[d] : 0;
        }
        value_type& safe_get(int d) {
            ensure(d + 1);
            return (*this)[d];
        }

        FormalPowerSeries& cut_trailing_zeros() {
            while (size() and this->back() == 0) this->pop_back();
            return *this;
        }
        FormalPowerSeries& cut(int n) {
            if (size() > n) this->resize(std::max(0, n));
            return *this;
        }
        FormalPowerSeries cut_copy(int n) const {
            FormalPowerSeries res(this->begin(), this->begin() + std::min(size(), n));
            res.ensure(n);
            return res;
        }
        FormalPowerSeries cut_copy(int l, int r) const {
            if (l >= size()) return FormalPowerSeries(r - l, 0);
            FormalPowerSeries res(this->begin() + l, this->begin() + std::min(size(), r));
            res.ensure(r - l);
            return res;
        }

        /* Unary Operations */

        FormalPowerSeries operator+() const { return *this; }
        FormalPowerSeries operator-() const {
            FormalPowerSeries res = *this;
            for (auto& e : res) e = -e;
            return res;
        }
        FormalPowerSeries& operator++() { return ++safe_get(0), * this; }
        FormalPowerSeries& operator--() { return --safe_get(0), * this; }
        FormalPowerSeries operator++(int) {
            FormalPowerSeries res = *this;
            ++(*this);
            return res;
        }
        FormalPowerSeries operator--(int) {
            FormalPowerSeries res = *this;
            --(*this);
            return res;
        }

        /* Binary Operations With Constant */

        FormalPowerSeries& operator+=(const value_type& x) { return safe_get(0) += x, *this; }
        FormalPowerSeries& operator-=(const value_type& x) { return safe_get(0) -= x, *this; }
        FormalPowerSeries& operator*=(const value_type& x) {
            for (auto& e : *this) e *= x;
            return *this;
        }
        FormalPowerSeries& operator/=(const value_type& x) { return *this *= x.inv(); }

        friend FormalPowerSeries operator+(FormalPowerSeries f, const value_type& x) { f += x; return f; }
        friend FormalPowerSeries operator+(const value_type& x, FormalPowerSeries f) { f += x; return f; }
        friend FormalPowerSeries operator-(FormalPowerSeries f, const value_type& x) { f -= x; return f; }
        friend FormalPowerSeries operator-(const value_type& x, FormalPowerSeries f) { f -= x; return -f; }
        friend FormalPowerSeries operator*(FormalPowerSeries f, const value_type& x) { f *= x; return f; }
        friend FormalPowerSeries operator*(const value_type& x, FormalPowerSeries f) { f *= x; return f; }
        friend FormalPowerSeries operator/(FormalPowerSeries f, const value_type& x) { f /= x; return f; }

        /* Binary Operations With Formal Power Series */

        FormalPowerSeries& operator+=(const FormalPowerSeries& g) {
            const int n = g.size();
            ensure(n);
            for (int i = 0; i < n; ++i) (*this)[i] += g[i];
            return *this;
        }
        FormalPowerSeries& operator-=(const FormalPowerSeries& g) {
            const int n = g.size();
            ensure(n);
            for (int i = 0; i < n; ++i) (*this)[i] -= g[i];
            return *this;
        }
        FormalPowerSeries& operator*=(const FormalPowerSeries& g) { return *this = *this * g; }
        FormalPowerSeries& operator/=(const FormalPowerSeries& g) { return *this = *this / g; }
        FormalPowerSeries& operator%=(const FormalPowerSeries& g) { return *this = *this % g; }

        friend FormalPowerSeries operator+(FormalPowerSeries f, const FormalPowerSeries& g) { f += g; return f; }
        friend FormalPowerSeries operator-(FormalPowerSeries f, const FormalPowerSeries& g) { f -= g; return f; }
        friend FormalPowerSeries operator*(const FormalPowerSeries& f, const FormalPowerSeries& g) { return atcoder::convolution(f, g); }
        friend FormalPowerSeries operator/(FormalPowerSeries f, FormalPowerSeries g) {
            if (f.size() < 60) return FPSNaive<mint>(f).div_mod(g).first;
            f.cut_trailing_zeros(), g.cut_trailing_zeros();
            const int fd = f.deg(), gd = g.deg();
            assert(gd >= 0);
            if (fd < gd) return {};
            if (gd == 0) {
                f /= g[0];
                return f;
            }
            std::reverse(f.begin(), f.end()), std::reverse(g.begin(), g.end());
            const int qd = fd - gd;
            FormalPowerSeries q = f * g.inv(qd + 1);
            q.cut(qd + 1);
            std::reverse(q.begin(), q.end());
            return q;
        }
        friend FormalPowerSeries operator%(const FormalPowerSeries& f, const FormalPowerSeries& g) { return f.div_mod(g).second; }
        std::pair<FormalPowerSeries, FormalPowerSeries> div_mod(const FormalPowerSeries& g) const {
            if (size() < 60) {
                auto [q, r] = FPSNaive<mint>(*this).div_mod(g);
                return { q, r };
            }
            FormalPowerSeries q = *this / g, r = *this - g * q;
            r.cut_trailing_zeros();
            return { q, r };
        }

        /* Shift Operations */

        FormalPowerSeries& operator<<=(const int shamt) {
            return this->insert(this->begin(), shamt, 0), * this;
        }
        FormalPowerSeries& operator>>=(const int shamt) {
            return this->erase(this->begin(), this->begin() + std::min(shamt, size())), * this;
        }
        friend FormalPowerSeries operator<<(FormalPowerSeries f, const int shamt) { f <<= shamt; return f; }
        friend FormalPowerSeries operator>>(FormalPowerSeries f, const int shamt) { f >>= shamt; return f; }

        /* Compare */

        friend bool operator==(const FormalPowerSeries& f, const FormalPowerSeries& g) {
            const int n = f.size(), m = g.size();
            if (n < m) return g == f;
            for (int i = 0; i < m; ++i) if (f[i] != g[i]) return false;
            for (int i = m; i < n; ++i) if (f[i] != 0) return false;
            return true;
        }
        friend bool operator!=(const FormalPowerSeries& f, const FormalPowerSeries& g) { return not (f == g); }

        /* Other Operations */

        FormalPowerSeries& diff_inplace() {
            const int n = size();
            for (int i = 1; i < n; ++i) (*this)[i - 1] = (*this)[i] * i;
            return (*this)[n - 1] = 0, *this;
        }
        FormalPowerSeries diff() const {
            FormalPowerSeries res = *this;
            res.diff_inplace();
            return res;
        }
        FormalPowerSeries& intg_inplace() {
            const int n = size();
            inv_mods<value_type> invs(n);
            this->resize(n + 1);
            for (int i = n; i > 0; --i) (*this)[i] = (*this)[i - 1] * invs[i];
            return (*this)[0] = 0, *this;
        }
        FormalPowerSeries intg() const {
            FormalPowerSeries res = *this;
            res.intg_inplace();
            return res;
        }

        FormalPowerSeries& inv_inplace(int n = -1) { return *this = inv(n); }
        // reference: https://opt-cp.com/fps-fast-algorithms/
        FormalPowerSeries inv(int n = -1) const {
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).inv();
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return inv_sparse(std::move(*sp_f), n);
            FormalPowerSeries f_fft, g_fft;
            FormalPowerSeries g{ (*this)[0].inv() };
            for (int k = 1; k < n; k *= 2) {
                f_fft = cut_copy(2 * k), g_fft = g.cut_copy(2 * k);
                atcoder::internal::butterfly(f_fft);
                atcoder::internal::butterfly(g_fft);
                update_inv(k, f_fft, g_fft, g);
            }
            g.resize(n);
            return g;
        }
        FormalPowerSeries& log_inplace(int n = -1) { return *this = log(n); }
        FormalPowerSeries log(int n = -1) const {
            assert(safe_get(0) == 1);
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).log();
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return log_sparse(std::move(*sp_f), n);
            FormalPowerSeries res = inv(n) * diff();
            res.resize(n - 1);
            return res.intg();
        }
        FormalPowerSeries& exp_inplace(int n = -1) { return *this = exp(n); }
        // https://arxiv.org/pdf/1301.5804.pdf
        FormalPowerSeries exp(int n = -1) const {
            assert(safe_get(0) == 0);
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).exp();
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return exp_sparse(std::move(*sp_f), n);
            // h = *this
            // f = exp(h) mod x ^ k
            // g = f^{-1} mod x ^ k
            FormalPowerSeries dh = diff();
            FormalPowerSeries f{ 1 }, f_fft;
            FormalPowerSeries g{ 1 }, g_fft;
            for (int k = 1; k < n; k *= 2) {
                f_fft = f.cut_copy(2 * k), atcoder::internal::butterfly(f_fft);

                if (k > 1) update_inv(k / 2, f_fft, g_fft, g);

                FormalPowerSeries t = f.cut_copy(k);
                t.diff_inplace();
                {
                    FormalPowerSeries r = dh.cut_copy(k);
                    r.back() = 0;
                    atcoder::internal::butterfly(r);
                    for (int i = 0; i < k; ++i) r[i] *= f_fft[i];
                    atcoder::internal::butterfly_inv(r);
                    r /= -k;
                    t += r;
                    t <<= 1, t[0] = t[k], t.pop_back();
                }
                t.resize(2 * k);
                atcoder::internal::butterfly(t);
                g_fft = g.cut_copy(2 * k);
                atcoder::internal::butterfly(g_fft);
                for (int i = 0; i < 2 * k; ++i) t[i] *= g_fft[i];
                atcoder::internal::butterfly_inv(t);
                t.resize(k);
                t /= 2 * k;

                FormalPowerSeries v = cut_copy(2 * k) >>= k;
                t <<= k - 1;
                t.intg_inplace();
                for (int i = 0; i < k; ++i) v[i] -= t[k + i];

                v.resize(2 * k);
                atcoder::internal::butterfly(v);
                for (int i = 0; i < 2 * k; ++i) v[i] *= f_fft[i];
                atcoder::internal::butterfly_inv(v);
                v.resize(k);
                v /= 2 * k;

                f.resize(2 * k);
                for (int i = 0; i < k; ++i) f[k + i] = v[i];
            }
            f.cut(n);
            return f;
        }

        FormalPowerSeries& pow_inplace(long long k, int n = -1) { return *this = pow(k, n); }
        FormalPowerSeries pow(const long long k, int n = -1) const {
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).pow(k);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return pow_sparse(std::move(*sp_f), k, n);
            if (k == 0) {
                FormalPowerSeries f{ 1 };
                f.resize(n);
                return f;
            }
            int tlz = 0;
            while (tlz < size() and (*this)[tlz] == 0) ++tlz;
            if (tlz == size() or tlz > (n - 1) / k) return FormalPowerSeries(n, 0);
            const int m = n - tlz * k;
            FormalPowerSeries f = *this >> tlz;
            value_type base = f[0];
            return ((((f /= base).log(m) *= k).exp(m) *= base.pow(k)) <<= (tlz * k));
        }

        std::optional<FormalPowerSeries> safe_sqrt(int n = -1) const {
            if (n < 0) n = size();
            // if (n < 60) return FPSNaive<mint>(cut_copy(n)).safe_sqrt();
            // if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return safe_sqrt_sparse(std::move(*sp_f), n);
            int tlz = 0;
            while (tlz < size() and (*this)[tlz] == 0) ++tlz;
            if (tlz == size()) return FormalPowerSeries(n, 0);
            if (tlz & 1) return std::nullopt;
            const int m = n - tlz / 2;

            FormalPowerSeries h(this->begin() + tlz, this->end());
            auto q0 = ::safe_sqrt(h[0]);
            if (not q0.has_value()) return std::nullopt;

            FormalPowerSeries f{ *q0 }, f_fft, g{ q0->inv() }, g_fft;
            for (int k = 1; k < m; k *= 2) {
                f_fft = f.cut_copy(2 * k), atcoder::internal::butterfly(f_fft);

                if (k > 1) update_inv(k / 2, f_fft, g_fft, g);

                g_fft = g.cut_copy(2 * k);
                atcoder::internal::butterfly(g_fft);
                FormalPowerSeries h_fft = h.cut_copy(2 * k);
                atcoder::internal::butterfly(h_fft);
                for (int i = 0; i < 2 * k; ++i) h_fft[i] = (h_fft[i] - f_fft[i] * f_fft[i]) * g_fft[i];
                atcoder::internal::butterfly_inv(h_fft);
                f.resize(2 * k);
                const value_type iz = value_type(4 * k).inv();
                for (int i = 0; i < k; ++i) f[k + i] = h_fft[k + i] * iz;
            }
            f.resize(m), f <<= (tlz / 2);
            return f;
        }
        FormalPowerSeries& sqrt_inplace(int n = -1) { return *this = sqrt(n); }
        FormalPowerSeries sqrt(int n = -1) const {
            return *safe_sqrt(n);
        }

        value_type eval(value_type x) const {
            value_type y = 0;
            for (int i = size() - 1; i >= 0; --i) y = y * x + (*this)[i];
            return y;
        }

        static FormalPowerSeries prod(const std::vector<FormalPowerSeries>& fs) {
            auto comp = [](const FormalPowerSeries& f, const FormalPowerSeries& g) { return f.size() > g.size(); };
            std::priority_queue<FormalPowerSeries, std::vector<FormalPowerSeries>, decltype(comp)> pq{ comp };
            for (const auto& f : fs) pq.push(f);
            while (pq.size() > 1) {
                auto f = pq.top();
                pq.pop();
                auto g = pq.top();
                pq.pop();
                pq.push(f * g);
            }
            return pq.top();
        }

    private:
        static void update_inv(const int k, FormalPowerSeries& f_fft, FormalPowerSeries& g_fft, FormalPowerSeries& g) {
            FormalPowerSeries fg(2 * k);
            for (int i = 0; i < 2 * k; ++i) fg[i] = f_fft[i] * g_fft[i];
            atcoder::internal::butterfly_inv(fg);
            fg >>= k, fg.resize(2 * k);
            atcoder::internal::butterfly(fg);
            for (int i = 0; i < 2 * k; ++i) fg[i] *= g_fft[i];
            atcoder::internal::butterfly_inv(fg);
            const value_type iz = value_type(2 * k).inv(), c = -iz * iz;
            g.resize(2 * k);
            for (int i = 0; i < k; ++i) g[k + i] = fg[i] * c;
        }

        std::optional<std::vector<std::pair<int, value_type>>> sparse_fps_format(int max_size) const {
            std::vector<std::pair<int, value_type>> res;
            for (int i = 0; i <= deg() and int(res.size()) <= max_size; ++i) if (value_type v = (*this)[i]; v != 0) res.emplace_back(i, v);
            if (int(res.size()) > max_size) return std::nullopt;
            return res;
        }

        static FormalPowerSeries div_fps_sparse(const FormalPowerSeries& f, const std::vector<std::pair<int, value_type>>& g, int n) {
            const int siz = g.size();
            assert(siz and g[0].first == 0);
            const value_type inv_g0 = g[0].second.inv();
            FormalPowerSeries h(n);
            for (int i = 0; i < n; ++i) {
                value_type v = f.safe_get(i);
                for (int idx = 1; idx < siz; ++idx) {
                    const auto& [j, gj] = g[idx];
                    if (j > i) break;
                    v -= gj * h[i - j];
                }
                h[i] = v * inv_g0;
            }
            return h;
        }
        static FormalPowerSeries inv_sparse(const std::vector<std::pair<int, value_type>>& g, const int n) {
            return div_fps_sparse(FormalPowerSeries{ 1 }, g, n);
        }
        static FormalPowerSeries exp_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            const int siz = f.size();
            assert(not siz or f[0].first != 0);
            FormalPowerSeries g(n);
            g[0] = 1;
            inv_mods<value_type> invs(n);
            for (int i = 1; i < n; ++i) {
                value_type v = 0;
                for (const auto& [j, fj] : f) {
                    if (j > i) break;
                    v += j * fj * g[i - j];
                }
                v *= invs[i];
                g[i] = v;
            }
            return g;
        }
        static FormalPowerSeries log_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            const int siz = f.size();
            assert(siz and f[0].first == 0 and f[0].second == 1);
            FormalPowerSeries g(n);
            for (int idx = 1; idx < siz; ++idx) {
                const auto& [j, fj] = f[idx];
                if (j >= n) break;
                g[j] = j * fj;
            }
            inv_mods<value_type> invs(n);
            for (int i = 1; i < n; ++i) {
                value_type v = g[i];
                for (int idx = 1; idx < siz; ++idx) {
                    const auto& [j, fj] = f[idx];
                    if (j > i) break;
                    v -= fj * g[i - j] * (i - j);
                }
                v *= invs[i];
                g[i] = v;
            }
            return g;
        }
        static FormalPowerSeries pow_sparse(const std::vector<std::pair<int, value_type>>& f, const long long k, const int n) {
            if (k == 0) {
                FormalPowerSeries res(n, 0);
                res[0] = 1;
                return res;
            }
            const int siz = f.size();
            if (not siz) return FormalPowerSeries(n, 0);
            const int p = f[0].first;
            if (p > (n - 1) / k) return FormalPowerSeries(n, 0);
            const value_type inv_f0 = f[0].second.inv();
            const int lz = p * k;
            FormalPowerSeries g(n);
            g[lz] = f[0].second.pow(k);
            inv_mods<value_type> invs(n);
            for (int i = 1; lz + i < n; ++i) {
                value_type v = 0;
                for (int idx = 1; idx < siz; ++idx) {
                    auto [j, fj] = f[idx];
                    j -= p;
                    if (j > i) break;
                    v += fj * g[lz + i - j] * (value_type(k) * j - (i - j));
                }
                v *= invs[i] * inv_f0;
                g[lz + i] = v;
            }
            return g;
        }
        static std::optional<FormalPowerSeries> safe_sqrt_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            const int siz = f.size();
            if (not siz) return FormalPowerSeries(n, 0);
            const int p = f[0].first;
            if (p % 2 == 1) return std::nullopt;
            if (p / 2 >= n) return FormalPowerSeries(n, 0);
            const value_type inv_f0 = f[0].second.inv();
            const int lz = p / 2;
            FormalPowerSeries g(n);
            auto opt_g0 = ::safe_sqrt(f[0].second);
            if (not opt_g0.has_value()) return std::nullopt;
            g[lz] = *opt_g0;
            value_type k = mint(2).inv();
            inv_mods<value_type> invs(n);
            for (int i = 1; lz + i < n; ++i) {
                value_type v = 0;
                for (int idx = 1; idx < siz; ++idx) {
                    auto [j, fj] = f[idx];
                    j -= p;
                    if (j > i) break;
                    v += fj * g[lz + i - j] * (k * j - (i - j));
                }
                v *= invs[i] * inv_f0;
                g[lz + i] = v;
            }
            return g;
        }
        static FormalPowerSeries sqrt_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            return *safe_sqrt(f, n);
        }
    };
} // namespace suisen

template <typename mint>
suisen::FormalPowerSeries<mint> sqrt(suisen::FormalPowerSeries<mint> a) {
    return a.sqrt();
}
template <typename mint>
suisen::FormalPowerSeries<mint> log(suisen::FormalPowerSeries<mint> a) {
    return a.log();
}
template <typename mint>
suisen::FormalPowerSeries<mint> exp(suisen::FormalPowerSeries<mint> a) {
    return a.exp();
}
template <typename mint, typename T>
suisen::FormalPowerSeries<mint> pow(suisen::FormalPowerSeries<mint> a, T b) {
    return a.pow(b);
}
template <typename mint>
suisen::FormalPowerSeries<mint> inv(suisen::FormalPowerSeries<mint> a) {
    return a.inv();
}

#endif // SUISEN_FORMAL_POWER_SERIES
