#ifndef SUISEN_FPS
#define SUISEN_FPS

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>

#include "library/polynomial/fps_naive.hpp"
#include "library/math/inv_mods.hpp"
#include "library/math/modint_extension.hpp"

namespace suisen {
    template <typename mint>
    using convolution_t = std::vector<mint>(*)(const std::vector<mint>&, const std::vector<mint>&);

    template <typename mint>
    struct FPS : public std::vector<mint> {
        using base_type = std::vector<mint>;
        using value_type = typename base_type::value_type;
        using base_type::vector;

        FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l) {}
        FPS(const std::vector<mint>& v) : std::vector<mint>::vector(v) {}
        FPS(std::vector<mint>&& v) : std::vector<mint>::vector(std::move(v)) {}

        static void set_multiplication(convolution_t<mint> multiplication) {
            FPS<mint>::mult = multiplication;
        }

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

        FPS& cut_trailing_zeros() {
            while (this->size() and this->back() == 0) this->pop_back();
            return *this;
        }
        FPS& cut(int n) {
            if (size() > n) this->resize(std::max(0, n));
            return *this;
        }
        FPS cut_copy(int n) const {
            FPS res(this->begin(), this->begin() + std::min(size(), n));
            res.ensure(n);
            return res;
        }
        FPS cut_copy(int l, int r) const {
            if (l >= size()) return FPS(r - l, 0);
            FPS res(this->begin() + l, this->begin() + std::min(size(), r));
            res.ensure(r - l);
            return res;
        }

        /* Unary Operations */

        FPS operator+() const { return *this; }
        FPS operator-() const {
            FPS res = *this;
            for (auto& e : res) e = -e;
            return res;
        }
        FPS& operator++() { return ++safe_get(0), * this; }
        FPS& operator--() { return --safe_get(0), * this; }
        FPS operator++(int) {
            FPS res = *this;
            ++(*this);
            return res;
        }
        FPS operator--(int) {
            FPS res = *this;
            --(*this);
            return res;
        }

        /* Binary Operations With Constant */

        FPS& operator+=(const value_type& x) { return safe_get(0) += x, *this; }
        FPS& operator-=(const value_type& x) { return safe_get(0) -= x, *this; }
        FPS& operator*=(const value_type& x) {
            for (auto& e : *this) e *= x;
            return *this;
        }
        FPS& operator/=(const value_type& x) { return *this *= x.inv(); }

        friend FPS operator+(FPS f, const value_type& x) { f += x; return f; }
        friend FPS operator+(const value_type& x, FPS f) { f += x; return f; }
        friend FPS operator-(FPS f, const value_type& x) { f -= x; return f; }
        friend FPS operator-(const value_type& x, FPS f) { f -= x; return -f; }
        friend FPS operator*(FPS f, const value_type& x) { f *= x; return f; }
        friend FPS operator*(const value_type& x, FPS f) { f *= x; return f; }
        friend FPS operator/(FPS f, const value_type& x) { f /= x; return f; }

        /* Binary Operations With Formal Power Series */

        FPS& operator+=(const FPS& g) {
            const int n = g.size();
            ensure(n);
            for (int i = 0; i < n; ++i) (*this)[i] += g[i];
            return *this;
        }
        FPS& operator-=(const FPS& g) {
            const int n = g.size();
            ensure(n);
            for (int i = 0; i < n; ++i) (*this)[i] -= g[i];
            return *this;
        }
        FPS& operator*=(const FPS& g) { return *this = *this * g; }
        FPS& operator/=(const FPS& g) { return *this = *this / g; }
        FPS& operator%=(const FPS& g) { return *this = *this % g; }

        friend FPS operator+(FPS f, const FPS& g) { f += g; return f; }
        friend FPS operator-(FPS f, const FPS& g) { f -= g; return f; }
        friend FPS operator*(const FPS& f, const FPS& g) { return mult(f, g); }
        friend FPS operator/(FPS f, FPS g) {
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
            FPS q = f * g.inv(qd + 1);
            q.cut(qd + 1);
            std::reverse(q.begin(), q.end());
            return q;
        }
        friend FPS operator%(const FPS& f, const FPS& g) { return f.div_mod(g).second; }
        std::pair<FPS, FPS> div_mod(const FPS& g) const {
            if (size() < 60) {
                auto [q, r] = FPSNaive<mint>(*this).div_mod(g);
                return { q, r };
            }
            FPS q = *this / g, r = *this - g * q;
            r.cut_trailing_zeros();
            return { q, r };
        }

        /* Shift Operations */

        FPS& operator<<=(const int shamt) {
            return this->insert(this->begin(), shamt, 0), * this;
        }
        FPS& operator>>=(const int shamt) {
            return this->erase(this->begin(), this->begin() + std::min(shamt, size())), * this;
        }
        friend FPS operator<<(FPS f, const int shamt) { f <<= shamt; return f; }
        friend FPS operator>>(FPS f, const int shamt) { f >>= shamt; return f; }

        /* Compare */

        friend bool operator==(const FPS& f, const FPS& g) {
            const int n = f.size(), m = g.size();
            if (n < m) return g == f;
            for (int i = 0; i < m; ++i) if (f[i] != g[i]) return false;
            for (int i = m; i < n; ++i) if (f[i] != 0) return false;
            return true;
        }
        friend bool operator!=(const FPS& f, const FPS& g) { return not (f == g); }

        /* Other Operations */

        FPS& diff_inplace() {
            const int n = size();
            for (int i = 1; i < n; ++i) (*this)[i - 1] = (*this)[i] * i;
            return (*this)[n - 1] = 0, *this;
        }
        FPS diff() const {
            FPS res = *this;
            res.diff_inplace();
            return res;
        }
        FPS& intg_inplace() {
            const int n = size();
            inv_mods<value_type> invs(n);
            this->resize(n + 1);
            for (int i = n; i > 0; --i) (*this)[i] = (*this)[i - 1] * invs[i];
            return (*this)[0] = 0, *this;
        }
        FPS intg() const {
            FPS res = *this;
            res.intg_inplace();
            return res;
        }
        
        FPS& inv_inplace(const int n = -1) { return *this = inv(n); } 
        FPS inv(int n = -1) const {
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(*this).inv(n);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return inv_sparse(std::move(*sp_f), n);
            FPS g{ (*this)[0].inv() };
            for (int k = 1; k < n; k *= 2) {
                FPS f_lo = cut_copy(k), f_hi = cut_copy(k, 2 * k);
                FPS h = (f_hi * g).cut(k) + ((f_lo * g) >>= k);
                FPS g_hi = g * h;
                g.resize(2 * k);
                for (int i = 0; i < k; ++i) g[k + i] = -g_hi[i];
            }
            g.resize(n);
            return g;
        }
        FPS& log_inplace(int n = -1) { return *this = log(n); }
        FPS log(int n = -1) const {
            assert(safe_get(0) == 1);
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).log(n);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return log_sparse(std::move(*sp_f), n);
            FPS res = inv(n) * diff();
            res.resize(n - 1);
            return res.intg();
        }
        FPS& exp_inplace(int n = -1) { return *this = exp(n); }
        FPS exp(int n = -1) {
            assert(safe_get(0) == 0);
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).exp(n);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return exp_sparse(std::move(*sp_f), n);
            FPS res{ 1 };
            for (int k = 1; k < n; k *= 2) res *= ++(cut_copy(k * 2) - res.log(k * 2)), res.cut(k * 2);
            res.resize(n);
            return res;
        }
        FPS& pow_inplace(long long k, int n = -1) { return *this = pow(k, n); }
        FPS pow(const long long k, int n = -1) const {
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).pow(k, n);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return pow_sparse(std::move(*sp_f), k, n);
            if (k == 0) {
                FPS f{ 1 };
                f.resize(n);
                return f;
            }
            int tlz = 0;
            while (tlz < size() and (*this)[tlz] == 0) ++tlz;
            if (tlz == size() or tlz > (n - 1) / k) return FPS(n, 0);
            const int m = n - tlz * k;
            FPS f = *this >> tlz;
            value_type base = f[0];
            return ((((f /= base).log(m) *= k).exp(m) *= base.pow(k)) <<= (tlz * k));
        }
        std::optional<FPS> safe_sqrt(int n = -1) const {
            if (n < 0) n = size();
            if (n < 60) return FPSNaive<mint>(cut_copy(n)).safe_sqrt(n);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return safe_sqrt_sparse(std::move(*sp_f), n);
            int tlz = 0;
            while (tlz < size() and (*this)[tlz] == 0) ++tlz;
            if (tlz == size()) return FPS(n, 0);
            if (tlz & 1) return std::nullopt;
            const int m = n - tlz / 2;

            FPS h(this->begin() + tlz, this->end());
            auto q0 = ::safe_sqrt(h[0]);
            if (not q0.has_value()) return std::nullopt;
            FPS f{ *q0 }, g{ q0->inv() };
            mint inv_2 = mint(2).inv();
            for (int k = 1; k < m; k *= 2) {
                FPS tmp = h.cut_copy(2 * k) * f.inv(2 * k);
                tmp.cut(2 * k);
                f += tmp, f *= inv_2;
            }
            f.fize(m);
            f <<= tlz / 2;
            return f;
        }
        FPS& sqrt_inplace(int n = -1) { return *this = sqrt(n); }
        FPS sqrt(int n = -1) const {
            return *safe_sqrt(n);
        }

        mint eval(mint x) const {
            mint y = 0;
            for (int i = size() - 1; i >= 0; --i) y = y * x + (*this)[i];
            return y;
        }

        static FPS prod(const std::vector<FPS>& fs) {
            auto comp = [](const FPS& f, const FPS& g) { return f.size() > g.size(); };
            std::priority_queue<FPS, std::vector<FPS>, decltype(comp)> pq{ comp };
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

    protected:
        static convolution_t<mint> mult;

        std::optional<std::vector<std::pair<int, value_type>>> sparse_fps_format(int max_size) const {
            std::vector<std::pair<int, value_type>> res;
            for (int i = 0; i <= deg() and int(res.size()) <= max_size; ++i) if (value_type v = (*this)[i]; v != 0) res.emplace_back(i, v);
            if (int(res.size()) > max_size) return std::nullopt;
            return res;
        }

        static FPS div_fps_sparse(const FPS& f, const std::vector<std::pair<int, value_type>>& g, int n) {
            const int siz = g.size();
            assert(siz and g[0].first == 0);
            const value_type inv_g0 = g[0].second.inv();
            FPS h(n);
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
        static FPS inv_sparse(const std::vector<std::pair<int, value_type>>& g, const int n) {
            return div_fps_sparse(FPS{ 1 }, g, n);
        }
        static FPS exp_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            const int siz = f.size();
            assert(not siz or f[0].first != 0);
            FPS g(n);
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
        static FPS log_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            const int siz = f.size();
            assert(siz and f[0].first == 0 and f[0].second == 1);
            FPS g(n);
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
        static FPS pow_sparse(const std::vector<std::pair<int, value_type>>& f, const long long k, const int n) {
            if (k == 0) {
                FPS res(n, 0);
                res[0] = 1;
                return res;
            }
            const int siz = f.size();
            if (not siz) return FPS(n, 0);
            const int p = f[0].first;
            if (p > (n - 1) / k) return FPS(n, 0);
            const value_type inv_f0 = f[0].second.inv();
            const int lz = p * k;
            FPS g(n);
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
        static std::optional<FPS> safe_sqrt_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            const int siz = f.size();
            if (not siz) return FPS(n, 0);
            const int p = f[0].first;
            if (p % 2 == 1) return std::nullopt;
            if (p / 2 >= n) return FPS(n, 0);
            const value_type inv_f0 = f[0].second.inv();
            const int lz = p / 2;
            FPS g(n);
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
        static FPS sqrt_sparse(const std::vector<std::pair<int, value_type>>& f, const int n) {
            return *safe_sqrt(f, n);
        }
    };

    template <typename mint>
    convolution_t<mint> FPS<mint>::mult = [](const auto&, const auto&) {
        std::cerr << "convolution function is not available." << std::endl;
        assert(false);
        return std::vector<mint>{};
    };

} // namespace suisen

template <typename mint>
suisen::FPS<mint> sqrt(suisen::FPS<mint> a) {
    return a.sqrt();
}
template <typename mint>
suisen::FPS<mint> log(suisen::FPS<mint> a) {
    return a.log();
}
template <typename mint>
suisen::FPS<mint> exp(suisen::FPS<mint> a) {
    return a.exp();
}
template <typename mint, typename T>
suisen::FPS<mint> pow(suisen::FPS<mint> a, T b) {
    return a.pow(b);
}
template <typename mint>
suisen::FPS<mint> inv(suisen::FPS<mint> a) {
    return a.inv();
}

#endif // SUISEN_FPS
