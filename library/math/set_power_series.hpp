#ifndef SUISEN_SPS
#define SUISEN_SPS

#include "library/convolution/subset_convolution.hpp"

namespace suisen {
    template <typename T>
    struct SetPowerSeries: public std::vector<T> {
        using base_type = std::vector<T>;
        using value_type = typename base_type::value_type;
        using size_type = typename base_type::size_type;

        using polynomial_type = ranked_subset_transform::polynomial_t<value_type>;

        using base_type::vector;

        SetPowerSeries(): SetPowerSeries(0) {}
        SetPowerSeries(size_type n): SetPowerSeries(n, value_type{ 0 }) {}
        SetPowerSeries(size_type n, const value_type& val): SetPowerSeries(std::vector<value_type>(1 << n, val)) {}
        SetPowerSeries(const base_type& a): SetPowerSeries(base_type(a)) {}
        SetPowerSeries(base_type&& a): base_type(std::move(a)) {
            const int n = this->size();
            assert(n == (-n & n));
        }
        SetPowerSeries(std::initializer_list<value_type> l): SetPowerSeries(base_type(l)) {}

        static SetPowerSeries one(int n) {
            SetPowerSeries f(n, value_type{ 0 });
            f[0] = value_type{ 1 };
            return f;
        }

        void set_cardinality(int n) {
            this->resize(1 << n, value_type{ 0 });
        }
        int cardinality() const {
            return __builtin_ctz(this->size());
        }

        SetPowerSeries cut_lower(size_type p) const {
            return SetPowerSeries(this->begin(), this->begin() + p);
        }
        SetPowerSeries cut_upper(size_type p) const {
            return SetPowerSeries(this->begin() + p, this->begin() + p + p);
        }

        void concat(const SetPowerSeries& upper) {
            assert(this->size() == upper.size());
            this->insert(this->end(), upper.begin(), upper.end());
        }

        SetPowerSeries operator+() const {
            return *this;
        }
        SetPowerSeries operator-() const {
            SetPowerSeries res(*this);
            for (auto& e : res) e = -e;
            return res;
        }
        SetPowerSeries& operator+=(const SetPowerSeries& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] += g[i];
            return *this;
        }
        SetPowerSeries& operator-=(const SetPowerSeries& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
            return *this;
        }
        SetPowerSeries& operator*=(const SetPowerSeries& g) {
            return *this = (zeta() *= g).mobius_inplace();
        }
        SetPowerSeries& operator*=(const value_type& c) {
            for (auto& e : *this) e *= c;
            return *this;
        }
        SetPowerSeries& operator/=(const value_type& c) {
            value_type inv_c = ::inv(c);
            for (auto& e : *this) e *= inv_c;
            return *this;
        }
        friend SetPowerSeries operator+(SetPowerSeries f, const SetPowerSeries& g) { f += g; return f; }
        friend SetPowerSeries operator-(SetPowerSeries f, const SetPowerSeries& g) { f -= g; return f; }
        friend SetPowerSeries operator*(SetPowerSeries f, const SetPowerSeries& g) { f *= g; return f; }
        friend SetPowerSeries operator*(SetPowerSeries f, const value_type& c) { f *= c; return f; }
        friend SetPowerSeries operator*(const value_type& c, SetPowerSeries f) { f *= c; return f; }
        friend SetPowerSeries operator/(SetPowerSeries f, const value_type& c) { f /= c; return f; }

        SetPowerSeries inv() {
            return zeta().inv_inplace().mobius_inplace();
        }
        SetPowerSeries sqrt() {
            return zeta().sqrt_inplace().mobius_inplace();
        }
        SetPowerSeries exp() {
            return zeta().exp_inplace().mobius_inplace();
        }
        SetPowerSeries log() {
            return zeta().log_inplace().mobius_inplace();
        }
        SetPowerSeries pow(long long k) {
            return zeta().pow_inplace(k).mobius_inplace();
        }

        static SetPowerSeries polynomial_composite(std::vector<T> f, const SetPowerSeries& g) {
            const int n = g.cardinality();
            std::vector<ZetaSPS> dp(n + 1);
            for (int k = 0; k <= n; ++k) {
                T eval_g0 = 0;
                for (int j = f.size(); j-- > 0;) eval_g0 = eval_g0 * g[0] + f[j];
                dp[k] = ZetaSPS({ eval_g0 });

                if (const int l = f.size()) {
                    for (int j = 1; j < l; ++j) f[j - 1] = f[j] * j;
                    f.pop_back();
                }
            }
            for (int m = 1; m <= n; ++m) {
                ZetaSPS hi_g = g.cut_upper(1 << (m - 1)).zeta();
                for (int k = 0; k <= n - m; ++k) {
                    dp[k].concat(dp[k + 1] * hi_g);
                }
                dp.pop_back();
            }
            return dp[0].mobius_inplace();
        }

        struct ZetaSPS: public std::vector<polynomial_type> {
            using base_type = std::vector<polynomial_type>;
            using base_type::vector;
            ZetaSPS() = default;
            ZetaSPS(const SetPowerSeries<value_type>& f): base_type::vector(ranked_subset_transform::ranked_zeta(f)), _d(f.cardinality()) {}

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
                for (size_type i = 0; i < size_type(1) << _d; ++i) (*this)[i] = (*this)[i].mul(rhs[i], _d + 1);
                return *this;
            }
            ZetaSPS inv()  const { auto f = ZetaSPS(*this).inv_inplace();  return f; }
            ZetaSPS sqrt() const { auto f = ZetaSPS(*this).sqrt_inplace(); return f; }
            ZetaSPS exp()  const { auto f = ZetaSPS(*this).exp_inplace();  return f; }
            ZetaSPS log()  const { auto f = ZetaSPS(*this).log_inplace();  return f; }
            ZetaSPS pow(long long k) const { auto f = ZetaSPS(*this).pow_inplace(k); return f; }
            ZetaSPS& inv_inplace() {
                for (auto& f : *this) f = f.inv(_d + 1);
                return *this;
            }
            ZetaSPS& sqrt_inplace() {
                for (auto& f : *this) f = f.sqrt(_d + 1);
                return *this;
            }
            ZetaSPS& exp_inplace() {
                for (auto& f : *this) f = f.exp(_d + 1);
                return *this;
            }
            ZetaSPS& log_inplace() {
                for (auto& f : *this) f = f.log(_d + 1);
                return *this;
            }
            ZetaSPS& pow_inplace(long long k) {
                for (auto& f : *this) f = f.pow(k, _d + 1);
                return *this;
            }
            void concat(const ZetaSPS& rhs) {
                assert(_d == rhs._d);
                this->reserve(1 << (_d + 1));
                for (size_type i = 0; i < size_type(1) << _d; ++i) {
                    this->push_back((rhs[i] << 1) += (*this)[i]);
                }
                ++_d;
            }
            SetPowerSeries<value_type> mobius_inplace() {
                return ranked_subset_transform::deranked_mobius<value_type>(*this);
            }
            SetPowerSeries<value_type> mobius() const {
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
