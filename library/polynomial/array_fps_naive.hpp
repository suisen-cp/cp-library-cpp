#ifndef SUISEN_ARRAY_FPS_NAIVE
#define SUISEN_ARRAY_FPS_NAIVE

#include <cassert>
#include <cmath>
#include <limits>
#include <type_traits>
#include <array>

#include "library/type_traits/type_traits.hpp"

#include "library/math/modint_extension.hpp"
#include "library/math/inv_mods.hpp"

namespace suisen {
    template <typename T, std::size_t N>
    struct ArrayFPSNaive : std::array<T, N> {
        static constexpr int SIZE = N;
        static constexpr int DEG = SIZE - 1;

        using value_type = T;
        using element_type = rec_value_type_t<T>;

        ArrayFPSNaive() {
            this->fill(value_type{ 0 });
        }
        ArrayFPSNaive(const std::initializer_list<value_type> l) : ArrayFPSNaive() {
            std::copy(l.begin(), l.end(), this->begin());
        }

        ArrayFPSNaive operator+() const {
            return ArrayFPSNaive(*this);
        }
        ArrayFPSNaive operator-() const {
            ArrayFPSNaive f(*this);
            for (auto& e : f) e = -e;
            return f;
        }
        ArrayFPSNaive& operator++() { return ++(*this)[0], * this; }
        ArrayFPSNaive& operator--() { return --(*this)[0], * this; }
        ArrayFPSNaive& operator+=(const value_type x) { return (*this)[0] += x, *this; }
        ArrayFPSNaive& operator-=(const value_type x) { return (*this)[0] -= x, *this; }
        ArrayFPSNaive& operator+=(const ArrayFPSNaive& g) {
            for (int i = 0; i < SIZE; ++i) (*this)[i] += g[i];
            return *this;
        }
        ArrayFPSNaive& operator-=(const ArrayFPSNaive& g) {
            for (int i = 0; i < SIZE; ++i) (*this)[i] -= g[i];
            return *this;
        }
        ArrayFPSNaive& operator*=(const ArrayFPSNaive& g) { return *this = *this * g; }
        ArrayFPSNaive& operator*=(const value_type x) {
            for (auto& e : *this) e *= x;
            return *this;
        }
        ArrayFPSNaive& operator/=(const ArrayFPSNaive& g) { return *this = *this / g; }
        ArrayFPSNaive& operator%=(const ArrayFPSNaive& g) { return *this = *this % g; }
        ArrayFPSNaive& operator<<=(int shamt) {
            shamt = std::min(shamt, SIZE);
            for (int i = SIZE - 1; i >= shamt; --i) std::swap((*this)[i], (*this)[i - shamt]);
            std::fill(this->begin(), this->begin() + shamt, value_type{ 0 });
            return *this;
        }
        ArrayFPSNaive& operator>>=(int shamt) {
            shamt = std::min(shamt, SIZE);
            for (int i = 0; i < SIZE - shamt; ++i) std::swap((*this)[i], (*this)[i + shamt]);
            std::fill(this->begin() + (SIZE - shamt), this->end(), value_type{ 0 });
            return *this;
        }

        friend ArrayFPSNaive operator+(ArrayFPSNaive f, const ArrayFPSNaive& g) { f += g; return f; }
        friend ArrayFPSNaive operator+(ArrayFPSNaive f, const value_type& x) { f += x; return f; }
        friend ArrayFPSNaive operator-(ArrayFPSNaive f, const ArrayFPSNaive& g) { f -= g; return f; }
        friend ArrayFPSNaive operator-(ArrayFPSNaive f, const value_type& x) { f -= x; return f; }
        friend ArrayFPSNaive operator*(const ArrayFPSNaive& f, const ArrayFPSNaive& g) {
            ArrayFPSNaive h;
            for (int i = 0; i < SIZE; ++i) for (int j = 0; i + j < SIZE; ++j) h[i + j] += f[i] * g[j];
            return h;
        }
        friend ArrayFPSNaive operator*(ArrayFPSNaive f, const value_type& x) { f *= x; return f; }
        friend ArrayFPSNaive operator/(ArrayFPSNaive f, ArrayFPSNaive g) { return std::move(div_mod(std::move(f), std::move(g)).first); }
        friend ArrayFPSNaive operator%(ArrayFPSNaive f, ArrayFPSNaive g) { return std::move(div_mod(std::move(f), std::move(g)).second); }
        friend ArrayFPSNaive operator*(const value_type x, ArrayFPSNaive f) { f *= x; return f; }
        friend ArrayFPSNaive operator<<(ArrayFPSNaive f, const int shamt) { f <<= shamt; return f; }
        friend ArrayFPSNaive operator>>(ArrayFPSNaive f, const int shamt) { f >>= shamt; return f; }

        friend std::pair<ArrayFPSNaive, ArrayFPSNaive> div_mod(ArrayFPSNaive f, const ArrayFPSNaive& g) {
            int fd = DEG, gd = DEG;
            while (fd >= 0 and f[fd] == value_type{ 0 }) --fd;
            while (gd >= 0 and g[gd] == value_type{ 0 }) --gd;
            assert(gd >= 0);
            if (fd < gd) return { ArrayFPSNaive{}, f };
            if (gd == 0) return { f *= g[0].inv(), ArrayFPSNaive{} };
            const int k = fd - gd;
            value_type head_inv = g[gd].inv();
            ArrayFPSNaive q;
            for (int i = k; i >= 0; --i) {
                value_type div = f[i + gd] * head_inv;
                q[i] = div;
                for (int j = 0; j <= gd; ++j) f[i + j] -= div * g[j];
            }
            std::fill(f.begin() + gd, f.end(), value_type{ 0 });
            return { std::move(q), std::move(f) };
        }

        ArrayFPSNaive mul(const ArrayFPSNaive& g) const {
            return (*this) * g;
        }
        ArrayFPSNaive diff() const {
            ArrayFPSNaive g;
            for (int i = 1; i <= DEG; ++i) g[i - 1] = (*this)[i] * i;
            g[DEG] = 0;
            return g;
        }
        ArrayFPSNaive intg() const {
            ArrayFPSNaive g;
            for (int i = 0; i < DEG; ++i) g[i + 1] = (*this)[i] * invs[i + 1];
            return g;
        }
        ArrayFPSNaive inv() const {
            ArrayFPSNaive g;
            const value_type inv_f0 = ::inv((*this)[0]);
            g[0] = inv_f0;
            for (int i = 1; i <= DEG; ++i) {
                for (int j = 1; j <= i; ++j) g[i] -= g[i - j] * (*this)[j];
                g[i] *= inv_f0;
            }
            return g;
        }
        ArrayFPSNaive exp() const {
            assert((*this)[0] == value_type{ 0 });
            ArrayFPSNaive g;
            g[0] = value_type{ 1 };
            for (int i = 1; i <= DEG; ++i) {
                for (int j = 1; j <= i; ++j) g[i] += j * g[i - j] * (*this)[j];
                g[i] *= invs[i];
            }
            return g;
        }
        ArrayFPSNaive log() const {
            assert((*this)[0] == value_type{ 1 });
            ArrayFPSNaive g;
            g[0] = value_type{ 0 };
            for (int i = 1; i <= DEG; ++i) {
                g[i] = i * (*this)[i];
                for (int j = 1; j < i; ++j) g[i] -= (i - j) * g[i - j] * (*this)[j];
                g[i] *= invs[i];
            }
            return g;
        }
        ArrayFPSNaive pow(const long long k) const {
            if (k == 0) {
                ArrayFPSNaive g;
                g[0] = 1;
                return g;
            }
            int z = 0;
            while (z < SIZE and (*this)[z] == value_type{ 0 }) ++z;
            if (z >= DEG / k + 1) return ArrayFPSNaive{};
            const int d = DEG - z * k;
            const int bf = z, bg = z * k;

            ArrayFPSNaive g;
            const value_type inv_f0 = ::inv((*this)[bf]);
            g[bg] = (*this)[bf].pow(k);
            for (int i = 1; i <= d; ++i) {
                for (int j = 1; j <= i; ++j) g[bg + i] += (element_type{ k } * j - (i - j)) * g[bg + i - j] * (*this)[bf + j];
                g[bg + i] *= inv_f0 * invs[i];
            }
            return g;
        }

        ArrayFPSNaive sqrt() const {
            int dl = 0;
            while (dl < SIZE and (*this)[dl] == value_type{ 0 }) ++dl;
            if (dl == SIZE) return ArrayFPSNaive{};
            if (dl & 1) assert(false);

            const int d = DEG - dl / 2;
            const int bf = dl, bg = bf / 2;

            ArrayFPSNaive g;
            g[bg] = ::sqrt((*this)[bf]);
            value_type inv_2g0 = ::inv(2 * g[bg]);
            for (int i = 1; i <= d; ++i) {
                g[bg + i] = (*this)[bf + i];
                for (int j = 1; j < i; ++j) g[bg + i] -= g[bg + j] * g[bg + i - j];
                g[bg + i] *= inv_2g0;
            }
            return g;
        }

        value_type eval(value_type x) const {
            value_type y = 0;
            for (int i = DEG; i >= 0; --i) y = y * x + (*this)[i];
            return y;
        }

    private:
        static inline inv_mods<element_type> invs;
    };
} // namespace suisen

template <typename mint, std::size_t N>
auto sqrt(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint, N>{}) {
    return a.sqrt();
}
template <typename mint, std::size_t N>
auto log(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint, N>{}) {
    return a.log();
}
template <typename mint, std::size_t N>
auto exp(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint, N>{}) {
    return a.exp();
}
template <typename mint, std::size_t N, typename T>
auto pow(suisen::ArrayFPSNaive<mint, N> a, const T& b) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint, N>{}) {
    return a.pow(b);
}
template <typename mint, std::size_t N>
auto inv(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint, N>{}) {
    return a.inv();
}

#endif // SUISEN_ARRAY_FPS_NAIVE
