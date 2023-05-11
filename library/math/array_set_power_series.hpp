#ifndef SUISEN_ARRAY_SPS
#define SUISEN_ARRAY_SPS

#include "library/convolution/array_subset_convolution.hpp"

namespace suisen {
    template <typename T, std::size_t N>
    struct ArraySetPowerSeries: public std::vector<T> {
        using base_type = std::vector<T>;
        using value_type = typename base_type::value_type;
        using size_type = typename base_type::size_type;

        using polynomial_type = array_ranked_subset_transform::polynomial_t<value_type, N>;

        using base_type::vector;

        ArraySetPowerSeries(): ArraySetPowerSeries(0) {}
        ArraySetPowerSeries(size_type n): ArraySetPowerSeries(n, value_type{ 0 }) {}
        ArraySetPowerSeries(size_type n, const value_type& val): ArraySetPowerSeries(std::vector<value_type>(1 << n, val)) {}
        ArraySetPowerSeries(const base_type& a): ArraySetPowerSeries(base_type(a)) {}
        ArraySetPowerSeries(base_type&& a): base_type(std::move(a)) {
            const int n = this->size();
            assert(n == (-n & n));
        }
        ArraySetPowerSeries(std::initializer_list<value_type> l): ArraySetPowerSeries(base_type(l)) {}

        static ArraySetPowerSeries one(int n) {
            ArraySetPowerSeries f(n, value_type{ 0 });
            f[0] = value_type{ 1 };
            return f;
        }

        void set_cardinality(int n) {
            this->resize(1 << n, value_type{ 0 });
        }
        int cardinality() const {
            return __builtin_ctz(this->size());
        }

        ArraySetPowerSeries cut_lower(size_type p) const {
            return ArraySetPowerSeries(this->begin(), this->begin() + p);
        }
        ArraySetPowerSeries cut_upper(size_type p) const {
            return ArraySetPowerSeries(this->begin() + p, this->begin() + p + p);
        }

        void concat(const ArraySetPowerSeries& upper) {
            assert(this->size() == upper.size());
            this->insert(this->end(), upper.begin(), upper.end());
        }

        ArraySetPowerSeries operator+() const {
            return *this;
        }
        ArraySetPowerSeries operator-() const {
            ArraySetPowerSeries res(*this);
            for (auto& e : res) e = -e;
            return res;
        }
        ArraySetPowerSeries& operator+=(const ArraySetPowerSeries& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] += g[i];
            return *this;
        }
        ArraySetPowerSeries& operator-=(const ArraySetPowerSeries& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
            return *this;
        }
        ArraySetPowerSeries& operator*=(const ArraySetPowerSeries& g) {
            return *this = (zeta() *= g).mobius_inplace();
        }
        ArraySetPowerSeries& operator*=(const value_type& c) {
            for (auto& e : *this) e *= c;
            return *this;
        }
        ArraySetPowerSeries& operator/=(const value_type& c) {
            value_type inv_c = ::inv(c);
            for (auto& e : *this) e *= inv_c;
            return *this;
        }
        friend ArraySetPowerSeries operator+(ArraySetPowerSeries f, const ArraySetPowerSeries& g) { f += g; return f; }
        friend ArraySetPowerSeries operator-(ArraySetPowerSeries f, const ArraySetPowerSeries& g) { f -= g; return f; }
        friend ArraySetPowerSeries operator*(ArraySetPowerSeries f, const ArraySetPowerSeries& g) { f *= g; return f; }
        friend ArraySetPowerSeries operator*(ArraySetPowerSeries f, const value_type& c) { f *= c; return f; }
        friend ArraySetPowerSeries operator*(const value_type& c, ArraySetPowerSeries f) { f *= c; return f; }
        friend ArraySetPowerSeries operator/(ArraySetPowerSeries f, const value_type& c) { f /= c; return f; }

        ArraySetPowerSeries inv() {
            return zeta().inv_inplace().mobius_inplace();
        }
        ArraySetPowerSeries sqrt() {
            return zeta().sqrt_inplace().mobius_inplace();
        }
        ArraySetPowerSeries exp() {
            return zeta().exp_inplace().mobius_inplace();
        }
        ArraySetPowerSeries log() {
            return zeta().log_inplace().mobius_inplace();
        }
        ArraySetPowerSeries pow(long long k) {
            return zeta().pow_inplace(k).mobius_inplace();
        }

        struct ZetaSPS: public std::vector<polynomial_type> {
            using base_type = std::vector<polynomial_type>;
            ZetaSPS() = default;
            ZetaSPS(const ArraySetPowerSeries<value_type, N>& f): base_type::vector(array_ranked_subset_transform::ranked_zeta<T, N>(f)), _d(f.cardinality()) {}

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
            friend ZetaSPS operator*(ZetaSPS f, const value_type& c) { f *= c; return f; }
            friend ZetaSPS operator*(const value_type& c, ZetaSPS f) { f *= c; return f; }
            friend ZetaSPS operator/(ZetaSPS f, const value_type& c) { f /= c; return f; }

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
                for (size_type i = 0; i < size_type(1) << _d; ++i) (*this)[i] = (*this)[i].mul(rhs[i]);
                return *this;
            }
            ZetaSPS inv()  const { auto f = ZetaSPS(*this).inv_inplace();  return f; }
            ZetaSPS sqrt() const { auto f = ZetaSPS(*this).sqrt_inplace(); return f; }
            ZetaSPS exp()  const { auto f = ZetaSPS(*this).exp_inplace();  return f; }
            ZetaSPS log()  const { auto f = ZetaSPS(*this).log_inplace();  return f; }
            ZetaSPS pow(long long k) const { auto f = ZetaSPS(*this).pow_inplace(k); return f; }
            ZetaSPS& inv_inplace() {
                for (auto& f : *this) f = f.inv();
                return *this;
            }
            ZetaSPS& sqrt_inplace() {
                for (auto& f : *this) f = f.sqrt();
                return *this;
            }
            ZetaSPS& exp_inplace() {
                for (auto& f : *this) f = f.exp();
                return *this;
            }
            ZetaSPS& log_inplace() {
                for (auto& f : *this) f = f.log();
                return *this;
            }
            ZetaSPS& pow_inplace(long long k) {
                for (auto& f : *this) f = f.pow(k);
                return *this;
            }
            ArraySetPowerSeries<value_type, N> mobius_inplace() {
                return array_ranked_subset_transform::deranked_mobius<value_type, N>(*this);
            }
            ArraySetPowerSeries<value_type, N> mobius() const {
                auto rf = ZetaSPS(*this);
                return array_ranked_subset_transform::deranked_mobius<value_type, N>(rf);
            }
        private:
            int _d;
        };

        ZetaSPS zeta() const {
            return ZetaSPS(*this);
        }
    };
} // namespace suisen

#endif // SUISEN_ARRAY_SPS
