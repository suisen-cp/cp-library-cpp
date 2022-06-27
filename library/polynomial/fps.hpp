#ifndef SUISEN_FPS
#define SUISEN_FPS

#include <algorithm>
#include <cassert>
#include <iostream>

#include "library/polynomial/fps_naive.hpp"
#include "library/math/inv_mods.hpp"
#include "library/math/modint_extension.hpp"

namespace suisen {
    template <typename mint>
    using convolution_t = std::vector<mint>(*)(const std::vector<mint>&, const std::vector<mint>&);

    template <typename mint>
    struct FPS : public std::vector<mint> {
        using std::vector<mint>::vector;

        FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l) {}
        FPS(const std::vector<mint>& v) : std::vector<mint>::vector(v) {}
        FPS(std::vector<mint>&& v) : std::vector<mint>::vector(std::move(v)) {}

        static void set_multiplication(convolution_t<mint> multiplication) {
            FPS<mint>::mult = multiplication;
        }

        const mint operator[](int n) const noexcept { return n <= deg() ? unsafe_get(n) : 0; }
        mint& operator[](int n) noexcept { ensure_deg(n); return unsafe_get(n); }

        int size() const noexcept { return std::vector<mint>::size(); }
        int deg()  const noexcept { return size() - 1; }
        int normalize() {
            while (this->size() and this->back() == 0) this->pop_back();
            return deg();
        }
        FPS& pre_inplace(int max_deg) noexcept {
            if (deg() > max_deg) this->resize(std::max(0, max_deg + 1));
            return *this;
        }
        FPS pre(int max_deg) const noexcept { return FPS(*this).pre_inplace(max_deg); }

        FPS operator+() const { return FPS(*this); }
        FPS operator-() const {
            FPS f(*this);
            for (auto& e : f) e = mint::mod() - e;
            return f;
        }
        FPS& operator++() { ++(*this)[0]; return *this; }
        FPS& operator--() { --(*this)[0]; return *this; }
        FPS& operator+=(const mint x) { (*this)[0] += x; return *this; }
        FPS& operator-=(const mint x) { (*this)[0] -= x; return *this; }
        FPS& operator+=(const FPS& g) {
            ensure_deg(g.deg());
            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);
            return *this;
        }
        FPS& operator-=(const FPS& g) {
            ensure_deg(g.deg());
            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);
            return *this;
        }
        FPS& operator*=(const FPS& g) { return *this = FPS<mint>::mult(*this, g); }
        FPS& operator*=(const mint x) {
            for (auto& e : *this) e *= x;
            return *this;
        }
        FPS& operator/=(FPS g) {
            const int fd = normalize(), gd = g.normalize();
            assert(gd >= 0);
            if (fd < gd) { this->clear(); return *this; }
            if (gd == 0) return *this *= g.unsafe_get(0).inv();
            static constexpr int THRESHOLD_NAIVE_POLY_QUOTIENT = 256;
            if (gd <= THRESHOLD_NAIVE_POLY_QUOTIENT) {
                *this = std::move(naive_div_inplace(std::move(g), gd).first);
                return *this;
            }
            std::reverse(this->begin(), this->end()), std::reverse(g.begin(), g.end());
            const int k = fd - gd;
            *this *= g.inv_inplace(k), this->resize(k + 1);
            std::reverse(this->begin(), this->end());
            return *this;
        }
        FPS& operator%=(FPS g) {
            int fd = normalize(), gd = g.normalize();
            assert(gd >= 0);
            if (fd < gd) return *this;
            if (gd == 0) { this->clear(); return *this; }
            static constexpr int THRESHOLD_NAIVE_REMAINDER = 256;
            if (gd <= THRESHOLD_NAIVE_REMAINDER) return naive_div_inplace(std::move(g), gd).second;
            *this -= g * (*this / g);
            return pre_inplace(gd - 1);
        }
        FPS& operator<<=(const int shamt) {
            this->insert(this->begin(), shamt, 0);
            return *this;
        }
        FPS& operator>>=(const int shamt) {
            if (shamt > size()) this->clear();
            else this->erase(this->begin(), this->begin() + shamt);
            return *this;
        }

        friend FPS operator+(FPS f, const FPS& g) { f += g; return f; }
        friend FPS operator+(FPS f, const mint x) { f += x; return f; }
        friend FPS operator-(FPS f, const FPS& g) { f -= g; return f; }
        friend FPS operator-(FPS f, const mint x) { f -= x; return f; }
        friend FPS operator*(FPS f, const FPS& g) { f *= g; return f; }
        friend FPS operator*(FPS f, const mint x) { f *= x; return f; }
        friend FPS operator/(FPS f, const FPS& g) { f /= g; return f; }
        friend FPS operator%(FPS f, const FPS& g) { f %= g; return f; }
        friend FPS operator*(const mint x, FPS f) { f *= x; return f; }
        friend FPS operator<<(FPS f, const int shamt) { f <<= shamt; return f; }
        friend FPS operator>>(FPS f, const int shamt) { f >>= shamt; return f; }

        friend bool operator==(const FPS& f, const FPS& g) {
            int n = f.size(), m = g.size();
            if (n < m) return g == f;
            for (int i = 0; i < m; ++i) if (f.unsafe_get(i) != g.unsafe_get(i)) return false;
            for (int i = m; i < n; ++i) if (f.unsafe_get(i) != 0) return false;
            return true;
        }

        FPS& diff_inplace() {
            if (this->size() == 0) return *this;
            for (int i = 1; i <= deg(); ++i) unsafe_get(i - 1) = unsafe_get(i) * i;
            this->pop_back();
            return *this;
        }
        FPS& intg_inplace() {
            int d = deg();
            ensure_deg(d + 1);
            for (int i = d; i >= 0; --i) unsafe_get(i + 1) = unsafe_get(i) * invs[i + 1];
            unsafe_get(0) = 0;
            return *this;
        }
        FPS& inv_inplace(const int max_deg) {
            if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(), this->end()).inv(max_deg);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return *this = inv_sparse(std::move(*sp_f), max_deg);
            FPS res{ unsafe_get(0).inv() };
            for (int k = 1; k <= max_deg; k *= 2) {
                FPS tmp(this->pre(k * 2) * (res * res));
                res *= 2, res -= tmp.pre_inplace(2 * k);
            }
            return *this = std::move(res), pre_inplace(max_deg);
        }
        FPS& log_inplace(const int max_deg) {
            if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(), this->end()).log(max_deg);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return *this = log_sparse(std::move(*sp_f), max_deg);
            FPS f_inv = inv(max_deg);
            diff_inplace(), *this *= f_inv, pre_inplace(max_deg - 1), intg_inplace();
            return *this;
        }
        FPS& exp_inplace(const int max_deg) {
            if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(), this->end()).exp(max_deg);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return *this = exp_sparse(std::move(*sp_f), max_deg);
            FPS res{ 1 };
            for (int k = 1; k <= max_deg; k *= 2) res *= ++(pre(k * 2) - res.log(k * 2)), res.pre_inplace(k * 2);
            return *this = std::move(res), pre_inplace(max_deg);
        }
        FPS& sqrt_inplace(const int max_deg) {
            return *this = sqrt(max_deg);
        }
        FPS& pow_inplace(const long long k, const int max_deg) {
            if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(), this->end()).pow(k, max_deg);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return *this = pow_sparse(std::move(*sp_f), k, max_deg);
            int tlz = 0;
            while (tlz <= deg() and unsafe_get(tlz) == 0) ++tlz;
            if (tlz * k > max_deg) { this->clear(); return *this; }
            *this >>= tlz;
            mint base = (*this)[0];
            *this *= base.inv(), log_inplace(max_deg), *this *= k, exp_inplace(max_deg), *this *= base.pow(k);
            return *this <<= tlz * k, pre_inplace(max_deg);
        }
        FPS diff() const { FPS f{ *this }; f.diff_inplace(); return f; }
        FPS intg() const { FPS f{ *this }; f.intg_inplace(); return f; }
        FPS inv(const int max_deg) const { FPS f{ *this }; f.inv_inplace(max_deg); return f; }
        FPS log(const int max_deg) const { FPS f{ *this }; f.log_inplace(max_deg); return f; }
        FPS exp(const int max_deg) const { FPS f{ *this }; f.exp_inplace(max_deg); return f; }
        std::optional<FPS> optional_sqrt(const int max_deg) {
            if (max_deg <= 60) return FPSNaive<mint>(this->begin(), this->end()).optional_sqrt(max_deg);
            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return optional_sqrt_sparse(std::move(*sp_f), max_deg);

            int tlz = 0;
            while (tlz <= deg() and unsafe_get(tlz) == 0) ++tlz;
            if (tlz > deg()) return FPS{};
            if (tlz % 2 == 1) return std::nullopt;
            int max_deg2 = max_deg - tlz / 2;
            FPS f(this->begin() + tlz, this->end());

            auto opt_res0 = ::optional_sqrt(f[0]);
            if (not opt_res0.has_value()) return std::nullopt;
            FPS res{ *opt_res0 };
            mint inv_2 = mint(2).inv();
            for (int k = 1; k <= max_deg2; k *= 2) {
                res = ((f.pre(k * 2) * res.inv(2 * k)).pre_inplace(2 * k) += res) *= inv_2;
            }
            return *this = std::move(res <<= tlz / 2), pre_inplace(max_deg);
        }
        FPS sqrt(const int max_deg) const { return *optional_sqrt(max_deg); }
        FPS pow(const long long k, const int max_deg) const { FPS f{ *this }; f.pow_inplace(k, max_deg); return f; }

        mint eval(mint x) const {
            mint y = 0;
            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);
            return y;
        }

    private:
        static inline inv_mods<mint> invs;
        static convolution_t<mint> mult;
        void ensure_deg(int d) { if (deg() < d) this->resize(d + 1, 0); }
        const mint& unsafe_get(int i) const { return std::vector<mint>::operator[](i); }
        mint& unsafe_get(int i) { return std::vector<mint>::operator[](i); }

        std::optional<std::vector<std::pair<int, mint>>> sparse_fps_format(int max_size) const {
            std::vector<std::pair<int, mint>> res;
            for (int i = 0; i <= deg() and int(res.size()) <= max_size; ++i) if (mint v = unsafe_get(i); v != 0) res.emplace_back(i, v);
            if (int(res.size()) > max_size) return std::nullopt;
            return res;
        }

        std::pair<FPS, FPS&> naive_div_inplace(FPS&& g, const int gd) {
            const int k = deg() - gd;
            mint head_inv = g.unsafe_get(gd).inv();
            FPS q(k + 1);
            for (int i = k; i >= 0; --i) {
                mint div = this->unsafe_get(i + gd) * head_inv;
                q.unsafe_get(i) = div;
                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j) -= div * g.unsafe_get(j);
            }
            return { q, pre_inplace(gd - 1) };
        }

        static FPS div_fps_sparse(const FPS &f, const std::vector<std::pair<int, mint>> &g, const int max_deg) {
            const int siz = g.size();
            assert(siz and g[0].first == 0);
            const mint inv_g0 = g[0].second.inv();
            FPS h(max_deg + 1);
            for (int i = 0; i <= max_deg; ++i) {
                mint v = f[i];
                for (int idx = 1; idx < siz; ++idx) {
                    const auto &[j, gj] = g[idx];
                    if (j > i) break;
                    v -= gj * h.unsafe_get(i - j);
                }
                h.unsafe_get(i) = v * inv_g0;
            }
            return h;
        }
        static FPS inv_sparse(const std::vector<std::pair<int, mint>> &g, const int max_deg) {
            return div_fps_sparse(FPS { mint{1} }, g, max_deg);
        }
        static FPS exp_sparse(const std::vector<std::pair<int, mint>> &f, const int max_deg) {
            const int siz = f.size();
            assert(not siz or f[0].first != 0);
            FPS g(max_deg + 1);
            g[0] = 1;
            for (int i = 1; i <= max_deg; ++i) {
                mint v = 0;
                for (const auto &[j, fj] : f) {
                    if (j > i) break;
                    v += j * fj * g.unsafe_get(i - j);
                }
                v *= invs[i];
                g.unsafe_get(i) = v;
            }
            return g;
        }
        static FPS log_sparse(const std::vector<std::pair<int, mint>> &f, const int max_deg) {
            const int siz = f.size();
            assert(siz and f[0].first == 0 and f[0].second == 1);
            FPS g(max_deg + 1);
            for (int idx = 1; idx < siz; ++idx) {
                const auto &[j, fj] = f[idx];
                if (j > max_deg) break;
                g.unsafe_get(j) = j * fj;
            }
            for (int i = 1; i <= max_deg; ++i) {
                mint v = g.unsafe_get(i);
                for (int idx = 1; idx < siz; ++idx) {
                    const auto &[j, fj] = f[idx];
                    if (j > i) break;
                    v -= fj * g.unsafe_get(i - j) * (i - j);
                }
                v *= invs[i];
                g.unsafe_get(i) = v;
            }
            return g;
        }
        static FPS pow_sparse(const std::vector<std::pair<int, mint>> &f, const long long k, const int max_deg) {
            if (k == 0) return FPS { mint{1} };
            const int siz = f.size();
            if (not siz) return FPS{};
            const int p = f[0].first;
            if (p >= max_deg / k + 1) return FPS{};
            const mint inv_f0 = f[0].second.inv();
            const int lz = p * k;
            FPS g(max_deg + 1);
            g[lz] = f[0].second.pow(k);
            for (int i = 1; lz + i <= max_deg; ++i) {
                mint v = 0;
                for (int idx = 1; idx < siz; ++idx) {
                    auto [j, fj] = f[idx];
                    j -= p;
                    if (j > i) break;
                    v += fj * g.unsafe_get(lz + i - j) * (mint(k) * j - (i - j));
                }
                v *= invs[i] * inv_f0;
                g.unsafe_get(lz + i) = v;
            }
            return g;
        }
        static std::optional<FPS> optional_sqrt_sparse(const std::vector<std::pair<int, mint>> &f, const int max_deg) {
            const int siz = f.size();
            if (not siz) return FPS{};
            const int p = f[0].first;
            if (p % 2 == 1) return std::nullopt;
            if (p / 2 > max_deg) return FPS{};
            const mint inv_f0 = f[0].second.inv();
            const int lz = p / 2;
            FPS g(max_deg + 1);
            auto opt_g0 = ::optional_sqrt(f[0].second);
            if (not opt_g0.has_value()) return std::nullopt;
            g[lz] = *opt_g0;
            mint k = mint(2).inv();
            for (int i = 1; lz + i <= max_deg; ++i) {
                mint v = 0;
                for (int idx = 1; idx < siz; ++idx) {
                    auto [j, fj] = f[idx];
                    j -= p;
                    if (j > i) break;
                    v += fj * g.unsafe_get(lz + i - j) * (k * j - (i - j));
                }
                v *= invs[i] * inv_f0;
                g.unsafe_get(lz + i) = v;
            }
            return g;
        }
        static FPS sqrt_sparse(const std::vector<std::pair<int, mint>> &f, const int max_deg) {
            return *optional_sqrt(f, max_deg);
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
auto sqrt(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {
    return a.sqrt(a.deg());
}
template <typename mint>
auto log(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {
    return a.log(a.deg());
}
template <typename mint>
auto exp(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {
    return a.exp(a.deg());
}
template <typename mint, typename T>
auto pow(suisen::FPS<mint> a, T b) -> decltype(mint::mod(), suisen::FPS<mint>{}) {
    return a.pow(b, a.deg());
}
template <typename mint>
auto inv(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {
    return a.inv(a.deg());
}

#endif // SUISEN_FPS
