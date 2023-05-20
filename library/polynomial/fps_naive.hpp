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
        static inline int MAX_SIZE = std::numeric_limits<int>::max() / 2;

        using value_type = T;
        using element_type = rec_value_type_t<T>;
        using std::vector<value_type>::vector;

        FPSNaive(const std::initializer_list<value_type> l) : std::vector<value_type>::vector(l) {}
        FPSNaive(const std::vector<value_type>& v) : std::vector<value_type>::vector(v) {}

        static void set_max_size(int n) {
            FPSNaive<T>::MAX_SIZE = n;
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
        FPSNaive& cut_inplace(int n) {
            if (size() > n) this->resize(std::max(0, n));
            return *this;
        }
        FPSNaive cut(int n) const {
            FPSNaive f = FPSNaive(*this).cut_inplace(n);
            return f;
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
            this->insert(this->begin(), shamt, value_type{ 0 });
            return *this;
        }
        FPSNaive& operator>>=(const int shamt) {
            if (shamt > size()) this->clear();
            else this->erase(this->begin(), this->begin() + shamt);
            return *this;
        }

        friend FPSNaive operator+(FPSNaive f, const FPSNaive& g) { f += g; return f; }
        friend FPSNaive operator+(FPSNaive f, const value_type& x) { f += x; return f; }
        friend FPSNaive operator-(FPSNaive f, const FPSNaive& g) { f -= g; return f; }
        friend FPSNaive operator-(FPSNaive f, const value_type& x) { f -= x; return f; }
        friend FPSNaive operator*(const FPSNaive& f, const FPSNaive& g) {
            if (f.empty() or g.empty()) return FPSNaive{};
            const int n = f.size(), m = g.size();
            FPSNaive h(std::min(MAX_SIZE, n + m - 1));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                if (i + j >= MAX_SIZE) break;
                h.unsafe_get(i + j) += f.unsafe_get(i) * g.unsafe_get(j);
            }
            return h;
        }
        friend FPSNaive operator*(FPSNaive f, const value_type& x) { f *= x; return f; }
        friend FPSNaive operator/(FPSNaive f, const FPSNaive& g) { return std::move(f.div_mod(g).first); }
        friend FPSNaive operator%(FPSNaive f, const FPSNaive& g) { return std::move(f.div_mod(g).second); }
        friend FPSNaive operator*(const value_type x, FPSNaive f) { f *= x; return f; }
        friend FPSNaive operator<<(FPSNaive f, const int shamt) { f <<= shamt; return f; }
        friend FPSNaive operator>>(FPSNaive f, const int shamt) { f >>= shamt; return f; }

        std::pair<FPSNaive, FPSNaive> div_mod(FPSNaive g) const {
            FPSNaive f = *this;
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
            f.cut_inplace(gd);
            f.normalize();
            return { q, f };
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

        FPSNaive mul(const FPSNaive& g, int n = -1) const {
            if (n < 0) n = size();
            if (this->empty() or g.empty()) return FPSNaive{};
            const int m = size(), k = g.size();
            FPSNaive h(std::min(n, m + k - 1));
            for (int i = 0; i < m; ++i) {
                for (int j = 0, jr = std::min(k, n - i); j < jr; ++j) {
                    h.unsafe_get(i + j) += unsafe_get(i) * g.unsafe_get(j);
                }
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
            if (g.deg() > MAX_SIZE) g.cut_inplace(MAX_SIZE);
            return g;
        }
        FPSNaive inv(int n = -1) const {
            if (n < 0) n = size();
            FPSNaive g(n);
            const value_type inv_f0 = ::inv(unsafe_get(0));
            g.unsafe_get(0) = inv_f0;
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j <= i; ++j) g.unsafe_get(i) -= g.unsafe_get(i - j) * (*this)[j];
                g.unsafe_get(i) *= inv_f0;
            }
            return g;
        }
        FPSNaive exp(int n = -1) const {
            if (n < 0) n = size();
            assert(unsafe_get(0) == value_type{ 0 });
            FPSNaive g(n);
            g.unsafe_get(0) = value_type{ 1 };
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j <= i; ++j) g.unsafe_get(i) += j * g.unsafe_get(i - j) * (*this)[j];
                g.unsafe_get(i) *= invs[i];
            }
            return g;
        }
        FPSNaive log(int n = -1) const {
            if (n < 0) n = size();
            assert(unsafe_get(0) == value_type{ 1 });
            FPSNaive g(n);
            g.unsafe_get(0) = value_type{ 0 };
            for (int i = 1; i < n; ++i) {
                g.unsafe_get(i) = i * (*this)[i];
                for (int j = 1; j < i; ++j) g.unsafe_get(i) -= (i - j) * g.unsafe_get(i - j) * (*this)[j];
                g.unsafe_get(i) *= invs[i];
            }
            return g;
        }
        FPSNaive pow(const long long k, int n = -1) const {
            if (n < 0) n = size();
            if (k == 0) {
                FPSNaive res(n);
                res[0] = 1;
                return res;
            }
            int z = 0;
            while (z < size() and unsafe_get(z) == value_type{ 0 }) ++z;
            if (z == size() or z > (n - 1) / k) return FPSNaive(n, 0);
            const int m = n - z * k;

            FPSNaive g(m);
            const value_type inv_f0 = ::inv(unsafe_get(z));
            g.unsafe_get(0) = unsafe_get(z).pow(k);
            for (int i = 1; i < m; ++i) {
                for (int j = 1; j <= i; ++j) g.unsafe_get(i) += (element_type{ k } *j - (i - j)) * g.unsafe_get(i - j) * (*this)[z + j];
                g.unsafe_get(i) *= inv_f0 * invs[i];
            }
            g <<= z * k;
            return g;
        }

        std::optional<FPSNaive> safe_sqrt(int n = -1) const {
            if (n < 0) n = size();
            int dl = 0;
            while (dl < size() and unsafe_get(dl) == value_type{ 0 }) ++dl;
            if (dl == size()) return FPSNaive(n, 0);
            if (dl & 1) return std::nullopt;

            const int m = n - dl / 2;

            FPSNaive g(m);
            auto opt_g0 = ::safe_sqrt((*this)[dl]);
            if (not opt_g0.has_value()) return std::nullopt;
            g.unsafe_get(0) = *opt_g0;
            value_type inv_2g0 = ::inv(2 * g.unsafe_get(0));
            for (int i = 1; i < m; ++i) {
                g.unsafe_get(i) = (*this)[dl + i];
                for (int j = 1; j < i; ++j) g.unsafe_get(i) -= g.unsafe_get(j) * g.unsafe_get(i - j);
                g.unsafe_get(i) *= inv_2g0;
            }
            g <<= dl / 2;
            return g;
        }
        FPSNaive sqrt(int n = -1) const {
            if (n < 0) n = size();
            return *safe_sqrt(n);
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
suisen::FPSNaive<mint> sqrt(suisen::FPSNaive<mint> a) {
    return a.sqrt();
}
template <typename mint>
suisen::FPSNaive<mint> log(suisen::FPSNaive<mint> a) {
    return a.log();
}
template <typename mint>
suisen::FPSNaive<mint> exp(suisen::FPSNaive<mint> a) {
    return a.exp();
}
template <typename mint, typename T>
suisen::FPSNaive<mint> pow(suisen::FPSNaive<mint> a, T b) {
    return a.pow(b);
}
template <typename mint>
suisen::FPSNaive<mint> inv(suisen::FPSNaive<mint> a) {
    return a.inv();
}

#endif // SUISEN_FPS_NAIVE_OPS
