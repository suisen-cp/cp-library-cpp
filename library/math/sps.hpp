#ifndef SUISEN_SPS
#define SUISEN_SPS

#include "library/convolution/subset_convolution.hpp"

namespace suisen {
    template <typename T>
    struct SPS : public std::vector<T> {
        using base_type = std::vector<T>;
        using value_type = typename base_type::value_type;
        using size_type = typename base_type::size_type;

        using polynomial_type = ranked_subset_transform::polynomial_t<value_type>;

        using base_type::vector;

        SPS() : SPS(0) {}
        SPS(size_type n) : SPS(n, value_type{ 0 }) {}
        SPS(size_type n, const value_type& val) : SPS(std::vector<value_type>(1 << n, val)) {}
        SPS(const base_type& a) : SPS(base_type(a)) {}
        SPS(base_type&& a) : base_type(std::move(a)) {
            const int n = this->size();
            assert(n == (-n & n));
        }
        SPS(std::initializer_list<value_type> l) : SPS(base_type(l)) {}

        static SPS one(int n) {
            SPS f(n, value_type{ 0 });
            f[0] = value_type{ 1 };
            return f;
        }

        void set_cardinality(int n) {
            this->resize(1 << n, value_type{ 0 });
        }
        int cardinality() const {
            return __builtin_ctz(this->size());
        }

        SPS cut_lower(size_type p) const {
            return SPS(this->begin(), this->begin() + p);
        }
        SPS cut_upper(size_type p) const {
            return SPS(this->begin() + p, this->begin() + p + p);
        }

        void concat(const SPS& upper) {
            assert(this->size() == upper.size());
            this->insert(this->end(), upper.begin(), upper.end());
        }

        SPS operator+() const {
            return *this;
        }
        SPS operator-() const {
            SPS res(*this);
            for (auto& e : res) e = -e;
            return res;
        }
        SPS& operator+=(const SPS& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] += g[i];
            return *this;
        }
        SPS& operator-=(const SPS& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
            return *this;
        }
        SPS& operator*=(const SPS& g) {
            return *this = (zeta() *= g).mobius_inplace();
        }
        SPS& operator*=(const value_type &c) {
            for (auto& e : *this) e *= c;
            return *this;
        }
        SPS& operator/=(const value_type &c) {
            value_type inv_c = ::inv(c);
            for (auto& e : *this) e *= inv_c;
            return *this;
        }
        friend SPS operator+(SPS f, const SPS& g) { f += g; return f; }
        friend SPS operator-(SPS f, const SPS& g) { f -= g; return f; }
        friend SPS operator*(SPS f, const SPS& g) { f *= g; return f; }
        friend SPS operator*(SPS f, const value_type &c) { f *= c; return f; }
        friend SPS operator*(const value_type &c, SPS f) { f *= c; return f; }
        friend SPS operator/(SPS f, const value_type &c) { f /= c; return f; }

        SPS inv() {
            return zeta().inv_inplace().mobius_inplace();
        }
        SPS sqrt() {
            return zeta().sqrt_inplace().mobius_inplace();
        }
        SPS exp() {
            return zeta().exp_inplace().mobius_inplace();
        }
        SPS log() {
            return zeta().log_inplace().mobius_inplace();
        }
        SPS pow(long long k) {
            return zeta().pow_inplace(k).mobius_inplace();
        }

        struct ZetaSPS : public std::vector<polynomial_type> {
            using base_type = std::vector<polynomial_type>;
            ZetaSPS() = default;
            ZetaSPS(const SPS<value_type>& f) : base_type::vector(ranked_subset_transform::ranked_zeta(f)), _d(f.cardinality() + 1) {}

            ZetaSPS operator+() const {
                return *this;
            }
            ZetaSPS operator-() const {
                ZetaSPS res(*this);
                for (auto& f : res) f = -f;
                return res;
            }
            friend ZetaSPS operator+(ZetaSPS f, const ZetaSPS& g) { f += g; return f; }
            friend ZetaSPS operator-(ZetaSPS f, const ZetaSPS& g) { f -= g; return f; }
            friend ZetaSPS operator*(ZetaSPS f, const ZetaSPS& g) { f *= g; return f; }
            friend ZetaSPS operator*(ZetaSPS f, const value_type &c) { f *= c; return f; }
            friend ZetaSPS operator*(const value_type &c, ZetaSPS f) { f *= c; return f; }
            friend ZetaSPS operator/(ZetaSPS f, const value_type &c) { f /= c; return f; }

            ZetaSPS& operator+=(const ZetaSPS& rhs) {
                assert(_d == rhs._d);
                for (int i = 0; i < 1 << _d; ++i) (*this)[i] += rhs[i];
                return *this;
            }
            ZetaSPS& operator-=(const ZetaSPS& rhs) {
                assert(_d == rhs._d);
                for (int i = 0; i < 1 << _d; ++i) (*this)[i] -= rhs[i];
                return *this;
            }
            ZetaSPS& operator*=(value_type c) {
                for (auto& f : *this) f *= c;
                return *this;
            }
            ZetaSPS& operator/=(value_type c) {
                value_type inv_c = ::inv(c);
                for (auto& f : *this) f *= inv_c;
                return *this;
            }
            ZetaSPS& operator*=(const ZetaSPS& rhs) {
                assert(_d == rhs._d);
                for (size_type i = 0; i < size_type(1) << _d; ++i) (*this)[i] = (*this)[i].mul(rhs[i], _d);
                return *this;
            }
            ZetaSPS inv()  const { auto f = ZetaSPS(*this).inv_inplace();  return f; }
            ZetaSPS sqrt() const { auto f = ZetaSPS(*this).sqrt_inplace(); return f; }
            ZetaSPS exp()  const { auto f = ZetaSPS(*this).exp_inplace();  return f; }
            ZetaSPS log()  const { auto f = ZetaSPS(*this).log_inplace();  return f; }
            ZetaSPS pow(long long k) const { auto f = ZetaSPS(*this).pow_inplace(k); return f; }
            ZetaSPS& inv_inplace() {
                for (auto& f : *this) f = f.inv(_d);
                return *this;
            }
            ZetaSPS& sqrt_inplace() {
                for (auto& f : *this) f = f.sqrt(_d);
                return *this;
            }
            ZetaSPS& exp_inplace() {
                for (auto& f : *this) f = f.exp(_d);
                return *this;
            }
            ZetaSPS& log_inplace() {
                for (auto& f : *this) f = f.log(_d);
                return *this;
            }
            ZetaSPS& pow_inplace(long long k) {
                for (auto& f : *this) f = f.pow(k, _d);
                return *this;
            }
            SPS<value_type> mobius_inplace() {
                return ranked_subset_transform::deranked_mobius<value_type>(*this);
            }
            SPS<value_type> mobius() const {
                auto rf = ZetaSPS(*this);
                return ranked_subset_transform::deranked_mobius<value_type>(rf);
            }
        private:
            int _d;
        };

        ZetaSPS zeta() const {
            return ZetaSPS(*this);
        }
    };
} // namespace suisen

#endif // SUISEN_SPS
