#ifndef SUISEN_FPS
#define SUISEN_FPS

#include <algorithm>
#include <cassert>
#include <iostream>

#include "library/math/inv_mods.hpp"

namespace suisen {

template <typename mint>
using convolution_t = std::vector<mint> (*)(const std::vector<mint> &, const std::vector<mint> &);

template <typename mint>
class FPS : public std::vector<mint> {
    public:
        using std::vector<mint>::vector;

        FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l) {}
        FPS(const std::vector<mint> &v) : std::vector<mint>::vector(v) {}
        FPS(std::vector<mint> &&v) : std::vector<mint>::vector(std::move(v)) {}

        static void set_multiplication(convolution_t<mint> multiplication) {
            FPS<mint>::mult = multiplication;
        }

        inline const mint  operator[](int n) const noexcept { return n <= deg() ? unsafe_get(n) : 0; }
        inline       mint& operator[](int n)       noexcept { ensure_deg(n); return unsafe_get(n); }

        inline int size() const noexcept { return std::vector<mint>::size(); }
        inline int deg()  const noexcept { return size() - 1; }
        inline int normalize() {
            while (this->size() and this->back() == 0) this->pop_back();
            return deg();
        }
        inline FPS& pre_inplace(int max_deg) noexcept {
            if (deg() > max_deg) this->resize(std::max(0, max_deg + 1));
            return *this;
        }
        inline FPS pre(int max_deg) const noexcept { return FPS(*this).pre_inplace(max_deg); }

        inline FPS operator+() const { return FPS(*this); }
        FPS operator-() const {
            FPS f(*this);
            for (auto &e : f) e = mint::mod() - e;
            return f;
        }
        inline FPS& operator++() { ++(*this)[0]; return *this; }
        inline FPS& operator--() { --(*this)[0]; return *this; }
        inline FPS& operator+=(const mint x) { (*this)[0] += x; return *this; }
        inline FPS& operator-=(const mint x) { (*this)[0] -= x; return *this; }
        FPS& operator+=(const FPS &g) {
            ensure_deg(g.deg());
            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);
            return *this;
        }
        FPS& operator-=(const FPS &g) {
            ensure_deg(g.deg());
            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);
            return *this;
        }
        inline FPS& operator*=(const FPS  &g) { return *this = FPS<mint>::mult(*this, g); }
        inline FPS& operator*=(      FPS &&g) { return *this = FPS<mint>::mult(*this, g); }
        inline FPS& operator*=(const mint x) {
            for (auto &e : *this) e *= x;
            return *this;
        }
        FPS& operator/=(FPS &&g) {
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
        FPS& operator%=(FPS &&g) {
            int fd = normalize(), gd = g.normalize();
            assert(gd >= 0);
            if (fd < gd) return *this;
            if (gd == 0) { this->clear(); return *this; }
            static constexpr int THRESHOLD_NAIVE_REMAINDER = 256;
            if (gd <= THRESHOLD_NAIVE_REMAINDER) return naive_div_inplace(std::move(g), gd).second;
            *this -= g * (*this / g);
            return pre_inplace(gd - 1);
        }
        inline FPS& operator/=(const FPS &g) { return *this /= FPS(g); }
        inline FPS& operator%=(const FPS &g) { return *this %= FPS(g); }
        FPS& operator<<=(const int shamt) {
            this->insert(this->begin(), shamt, 0);
            return *this;
        }
        FPS& operator>>=(const int shamt) {
            if (shamt > size()) this->clear();
            else this->erase(this->begin(), this->begin() + shamt);
            return *this;
        }

        inline FPS operator+(FPS &&g) const { return FPS(*this) += std::move(g); }
        inline FPS operator-(FPS &&g) const { return FPS(*this) -= std::move(g); }
        inline FPS operator*(FPS &&g) const { return FPS(*this) *= std::move(g); }
        inline FPS operator/(FPS &&g) const { return FPS(*this) /= std::move(g); }
        inline FPS operator%(FPS &&g) const { return FPS(*this) %= std::move(g); }
        inline FPS operator+(const FPS &g) const { return FPS(*this) += g; }
        inline FPS operator+(const mint x) const { return FPS(*this) += x; }
        inline FPS operator-(const FPS &g) const { return FPS(*this) -= g; }
        inline FPS operator-(const mint x) const { return FPS(*this) -= x; }
        inline FPS operator*(const FPS &g) const { return FPS(*this) *= g; }
        inline FPS operator*(const mint x) const { return FPS(*this) *= x; }
        inline FPS operator/(const FPS &g) const { return FPS(*this) /= g; }
        inline FPS operator%(const FPS &g) const { return FPS(*this) %= g; }
        inline friend FPS operator*(const mint x, const FPS  &f) { return f * x; }
        inline friend FPS operator*(const mint x,       FPS &&f) { return f *= x; }
        inline FPS operator<<(const int shamt) { return FPS(*this) <<= shamt; }
        inline FPS operator>>(const int shamt) { return FPS(*this) >>= shamt; }

        friend bool operator==(const FPS &f, const FPS &g) {
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
            FPS res { unsafe_get(0).inv() };
            for (int k = 1; k <= max_deg; k *= 2) {
                FPS tmp(this->pre(k * 2) * (res * res));
                res *= 2, res -= tmp.pre_inplace(2 * k);
            }
            return *this = std::move(res), pre_inplace(max_deg);
        }
        FPS& log_inplace(const int max_deg) {
            FPS f_inv = inv(max_deg);
            diff_inplace(), *this *= f_inv, pre_inplace(max_deg - 1), intg_inplace();
            return *this;
        }
        FPS& exp_inplace(const int max_deg) {
            if (max_deg <= 60) return *this = naive_exp(max_deg);
            FPS res {1};
            for (int k = 1; k <= max_deg; k *= 2) res *= ++(pre(k * 2) - res.log(k * 2)), res.pre_inplace(k * 2);
            return *this = std::move(res), pre_inplace(max_deg);
        }
        FPS& pow_inplace(const long long k, const int max_deg) {
            int tlz = 0;
            while (tlz <= deg() and unsafe_get(tlz) == 0) ++tlz;
            if (tlz * k > max_deg) { this->clear(); return *this; }
            *this >>= tlz;
            mint base = (*this)[0];
            *this *= base.inv(), log_inplace(max_deg), *this *= k, exp_inplace(max_deg), *this *= base.pow(k);
            return *this <<= tlz * k, pre_inplace(max_deg);
        }
        inline FPS diff() const { return FPS(*this).diff_inplace(); }
        inline FPS intg() const { return FPS(*this).intg_inplace(); }
        inline FPS inv(const int max_deg) const { return FPS(*this).inv_inplace(max_deg); }
        inline FPS log(const int max_deg) const { return FPS(*this).log_inplace(max_deg); }
        inline FPS exp(const int max_deg) const { return FPS(*this).exp_inplace(max_deg); }
        inline FPS pow(const long long k, const int max_deg) const { return FPS(*this).pow_inplace(k, max_deg); }

        mint eval(mint x) const {
            mint y = 0;
            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);
            return y;
        }

    private:
        static inline inv_mods<mint> invs;
        static convolution_t<mint> mult;
        inline void ensure_deg(int d) { if (deg() < d) this->resize(d + 1, 0); }
        inline const mint& unsafe_get(int i) const { return std::vector<mint>::operator[](i); }
        inline       mint& unsafe_get(int i)       { return std::vector<mint>::operator[](i); }

        std::pair<FPS, FPS&> naive_div_inplace(FPS &&g, const int gd) {
            const int k = deg() - gd;
            mint head_inv = g.unsafe_get(gd).inv();
            FPS q(k + 1);
            for (int i = k; i >= 0; --i) {
                mint div = this->unsafe_get(i + gd) * head_inv;
                q.unsafe_get(i) = div;
                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j) -= div * g.unsafe_get(j);
            }
            return {q, pre_inplace(gd - 1)};
        }

        FPS<mint> naive_exp(const int max_deg) const {
            FPS<mint> g(max_deg + 1);
            g[0] = 1;
            for (int i = 1; i <= max_deg; ++i) {
                for (int j = 0; j < i; ++j) g[i] += g[j] * (i - j) * (*this)[i - j];
                g[i] *= invs[i];
            }
            return g;
        }
};

template <typename mint>
convolution_t<mint> FPS<mint>::mult = [](const auto &, const auto &) {
    std::cerr << "convolution function is not available." << std::endl;
    assert(false);
    return std::vector<mint>{};
};

} // namespace suisen

template <typename mint>
auto sqrt(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{})  {
    assert(false);
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
auto inv(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{})  {
    return a.inv(a.deg());
}

#endif // SUISEN_FPS
