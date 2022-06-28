#ifndef SUISEN_FPS_NAIVE_OPS
#define SUISEN_FPS_NAIVE_OPS

#include <cassert>
#include <cmath>
#include <limits>
#include <type_traits>
#include <vector>

#include "library/type_traits/type_traits.hpp"

#include "library/math/modint_extension.hpp"
#include "library/math/inv_mods.hpp"

namespace suisen {
    template <typename T>
    struct FPSNaive : std::vector<T> {
        static inline int MAX_DEG = std::numeric_limits<int>::max() / 2;

        using value_type = T;
        using element_type = rec_value_type_t<T>;
        using std::vector<value_type>::vector;

        FPSNaive(const std::initializer_list<value_type> l) : std::vector<value_type>::vector(l) {}

        static void set_max_deg(int max_deg) {
            FPSNaive<T>::MAX_DEG = max_deg;
        }

        const value_type operator[](int n) const {
            return n <= deg() ? unsafe_get(n) : value_type{ 0 };
        }
        value_type& operator[](int n) {
            return ensure_deg(n), unsafe_get(n);
        }

        int size() const {
            return std::vector<value_type>::size();
        }
        int deg() const {
            return size() - 1;
        }
        int normalize() {
            while (size() and this->back() == value_type{ 0 }) this->pop_back();
            return deg();
        }
        FPSNaive& cut_inplace(int max_deg) {
            if (deg() > max_deg) this->resize(std::max(0, max_deg + 1));
            return *this;
        }
        FPSNaive cut(int max_deg) const {
            return FPSNaive(*this).cut_inplace(max_deg);
        }

        FPSNaive operator+() const {
            return FPSNaive(*this);
        }
        FPSNaive operator-() const {
            FPSNaive f(*this);
            for (auto& e : f) e = -e;
            return f;
        }
        FPSNaive& operator++() { return ++(*this)[0], * this; }
        FPSNaive& operator--() { return --(*this)[0], * this; }
        FPSNaive& operator+=(const value_type x) { return (*this)[0] += x, *this; }
        FPSNaive& operator-=(const value_type x) { return (*this)[0] -= x, *this; }
        FPSNaive& operator+=(const FPSNaive& g) {
            ensure_deg(g.deg());
            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);
            return *this;
        }
        FPSNaive& operator-=(const FPSNaive& g) {
            ensure_deg(g.deg());
            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);
            return *this;
        }
        FPSNaive& operator*=(const FPSNaive& g) { return *this = *this * g; }
        FPSNaive& operator*=(const value_type x) {
            for (auto& e : *this) e *= x;
            return *this;
        }
        FPSNaive& operator/=(const FPSNaive& g) { return *this = *this / g; }
        FPSNaive& operator%=(const FPSNaive& g) { return *this = *this % g; }
        FPSNaive& operator<<=(const int shamt) {
            this->insert(this->begin(), shamt, value_type { 0 });
            return *this;
        }
        FPSNaive& operator>>=(const int shamt) {
            if (shamt > size()) this->clear();
            else this->erase(this->begin(), this->begin() + shamt);
            return *this;
        }

        friend FPSNaive operator+(FPSNaive f, const FPSNaive& g)   { f += g; return f; }
        friend FPSNaive operator+(FPSNaive f, const value_type &x) { f += x; return f; }
        friend FPSNaive operator-(FPSNaive f, const FPSNaive& g)   { f -= g; return f; }
        friend FPSNaive operator-(FPSNaive f, const value_type &x) { f -= x; return f; }
        friend FPSNaive operator*(const FPSNaive &f, const FPSNaive& g) {
            if (f.empty() or g.empty()) return FPSNaive{};
            const int n = f.size(), m = g.size();
            FPSNaive h(std::min(MAX_DEG + 1, n + m - 1));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                if (i + j > MAX_DEG) break;
                h.unsafe_get(i + j) += f.unsafe_get(i) * g.unsafe_get(j);
            }
            return h;
        }
        friend FPSNaive operator*(FPSNaive f, const value_type &x) { f *= x; return f; }
        friend FPSNaive operator/(FPSNaive f, FPSNaive g) { return std::move(div_mod(std::move(f), std::move(g)).first); }
        friend FPSNaive operator%(FPSNaive f, FPSNaive g) { return std::move(div_mod(std::move(f), std::move(g)).second); }
        friend FPSNaive operator*(const value_type x, FPSNaive f) { f *= x; return f; }
        friend FPSNaive operator<<(FPSNaive f, const int shamt)   { f <<= shamt; return f; }
        friend FPSNaive operator>>(FPSNaive f, const int shamt)   { f >>= shamt; return f; }

        friend std::pair<FPSNaive, FPSNaive> div_mod(FPSNaive f, FPSNaive g) {
            const int fd = f.normalize(), gd = g.normalize();
            assert(gd >= 0);
            if (fd < gd) return { FPSNaive{}, f };
            if (gd == 0) return { f *= g.unsafe_get(0).inv(), FPSNaive{} };
            const int k = f.deg() - gd;
            value_type head_inv = g.unsafe_get(gd).inv();
            FPSNaive q(k + 1);
            for (int i = k; i >= 0; --i) {
                value_type div = f.unsafe_get(i + gd) * head_inv;
                q.unsafe_get(i) = div;
                for (int j = 0; j <= gd; ++j) f.unsafe_get(i + j) -= div * g.unsafe_get(j);
            }
            return { q, f.cut_inplace(gd - 1) };
        }

        friend bool operator==(const FPSNaive& f, const FPSNaive& g) {
            const int n = f.size(), m = g.size();
            if (n < m) return g == f;
            for (int i = 0; i < m; ++i) if (f.unsafe_get(i) != g.unsafe_get(i)) return false;
            for (int i = m; i < n; ++i) if (f.unsafe_get(i) != 0) return false;
            return true;
        }
        friend bool operator!=(const FPSNaive& f, const FPSNaive& g) {
            return not (f == g);
        }

        FPSNaive mul(const FPSNaive& g, int max_deg) const {
            if (this->empty() or g.empty()) return FPSNaive{};
            const int n = size(), m = g.size();
            FPSNaive h(std::min(max_deg + 1, n + m - 1));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                if (i + j > max_deg) break;
                h.unsafe_get(i + j) += unsafe_get(i) * g.unsafe_get(j);
            }
            return h;
        }
        FPSNaive diff() const {
            if (this->empty()) return {};
            FPSNaive g(size() - 1);
            for (int i = 1; i <= deg(); ++i) g.unsafe_get(i - 1) = unsafe_get(i) * i;
            return g;
        }
        FPSNaive intg() const {
            const int n = size();
            FPSNaive g(n + 1);
            for (int i = 0; i < n; ++i) g.unsafe_get(i + 1) = unsafe_get(i) * invs[i + 1];
            if (g.deg() > MAX_DEG) g.cut_inplace(MAX_DEG);
            return g;
        }
        FPSNaive inv(int max_deg) const {
            FPSNaive g(max_deg + 1);
            const value_type inv_f0 = ::inv(unsafe_get(0));
            g.unsafe_get(0) = inv_f0;
            for (int i = 1; i <= max_deg; ++i) {
                for (int j = 1; j <= i; ++j) g.unsafe_get(i) -= g.unsafe_get(i - j) * (*this)[j];
                g.unsafe_get(i) *= inv_f0;
            }
            return g;
        }
        FPSNaive exp(int max_deg) const {
            assert(unsafe_get(0) == value_type{ 0 });
            FPSNaive g(max_deg + 1);
            g.unsafe_get(0) = value_type{ 1 };
            for (int i = 1; i <= max_deg; ++i) {
                for (int j = 1; j <= i; ++j) g.unsafe_get(i) += j * g.unsafe_get(i - j) * (*this)[j];
                g.unsafe_get(i) *= invs[i];
            }
            return g;
        }
        FPSNaive log(int max_deg) const {
            assert(unsafe_get(0) == value_type{ 1 });
            FPSNaive g(max_deg + 1);
            g.unsafe_get(0) = value_type{ 0 };
            for (int i = 1; i <= max_deg; ++i) {
                g.unsafe_get(i) = i * (*this)[i];
                for (int j = 1; j < i; ++j) g.unsafe_get(i) -= (i - j) * g.unsafe_get(i - j) * (*this)[j];
                g.unsafe_get(i) *= invs[i];
            }
            return g;
        }
        FPSNaive pow(const long long k, int max_deg) const {
            if (k == 0) return { value_type{ 1 } };
            int z = 0;
            while (z < size() and unsafe_get(z) == value_type{ 0 }) ++z;
            if (z == size() or z > max_deg / k) return FPSNaive{};
            const int d = max_deg - z * k;

            FPSNaive g(d + 1);
            const value_type inv_f0 = ::inv(unsafe_get(z));
            g.unsafe_get(0) = unsafe_get(z).pow(k);
            for (int i = 1; i <= d; ++i) {
                for (int j = 1; j <= i; ++j) g.unsafe_get(i) += (element_type{ k } * j - (i - j)) * g.unsafe_get(i - j) * (*this)[z + j];
                g.unsafe_get(i) *= inv_f0 * invs[i];
            }
            g <<= z * k;
            return g;
        }

        std::optional<FPSNaive> optional_sqrt(int max_deg) const {
            int dl = 0;
            while (dl < size() and unsafe_get(dl) == value_type{ 0 }) ++dl;
            if (dl == size()) return FPSNaive{};
            if (dl & 1) return std::nullopt;

            const int d = max_deg - dl / 2;

            FPSNaive g(d + 1);
            auto opt_g0 = ::optional_sqrt((*this)[dl]);
            if (not opt_g0.has_value()) return std::nullopt;
            g.unsafe_get(0) = *opt_g0;
            value_type inv_2g0 = ::inv(2 * g.unsafe_get(0));
            for (int i = 1; i <= d; ++i) {
                g.unsafe_get(i) = (*this)[dl + i];
                for (int j = 1; j < i; ++j) g.unsafe_get(i) -= g.unsafe_get(j) * g.unsafe_get(i - j);
                g.unsafe_get(i) *= inv_2g0;
            }
            g <<= dl / 2;
            return g;
        }
        FPSNaive sqrt(int max_deg) const {
            return *optional_sqrt(max_deg);
        }

        value_type eval(value_type x) const {
            value_type y = 0;
            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);
            return y;
        }

    private:
        static inline inv_mods<element_type> invs;

        void ensure_deg(int d) {
            if (deg() < d) this->resize(d + 1, value_type{ 0 });
        }
        const value_type& unsafe_get(int i) const {
            return std::vector<value_type>::operator[](i);
        }
        value_type& unsafe_get(int i) {
            return std::vector<value_type>::operator[](i);
        }
    };
} // namespace suisen

template <typename mint>
auto sqrt(suisen::FPSNaive<mint> a) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {
    return a.sqrt(suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());
}
template <typename mint>
auto log(suisen::FPSNaive<mint> a) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {
    return a.log(suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());
}
template <typename mint>
auto exp(suisen::FPSNaive<mint> a) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {
    return a.exp(suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());
}
template <typename mint, typename T>
auto pow(suisen::FPSNaive<mint> a, T b) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {
    return a.pow(b, suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());
}
template <typename mint>
auto inv(suisen::FPSNaive<mint> a) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {
    return a.inv(suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());
}


#endif // SUISEN_FPS_NAIVE_OPS
