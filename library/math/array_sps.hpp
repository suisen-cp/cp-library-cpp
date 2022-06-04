#ifndef SUISEN_ARRAY_SPS
#define SUISEN_ARRAY_SPS

#include "library/convolution/array_subset_convolution.hpp"

namespace suisen {
    template <typename T, std::size_t N>
    struct ArraySPS : public std::vector<T> {
        using base_type = std::vector<T>;
        using value_type = typename base_type::value_type;
        using size_type = typename base_type::size_type;

        using polynomial_type = array_ranked_subset_transform::polynomial_t<value_type, N>;

        using base_type::vector;

        ArraySPS() : ArraySPS(0) {}
        ArraySPS(size_type n) : ArraySPS(n, value_type{ 0 }) {}
        ArraySPS(size_type n, const value_type& val) : ArraySPS(std::vector<value_type>(1 << n, val)) {}
        ArraySPS(const base_type& a) : ArraySPS(base_type(a)) {}
        ArraySPS(base_type&& a) : base_type(std::move(a)) {
            const int n = this->size();
            assert(n == (-n & n));
        }
        ArraySPS(std::initializer_list<value_type> l) : ArraySPS(base_type(l)) {}

        static ArraySPS one(int n) {
            ArraySPS f(n, value_type{ 0 });
            f[0] = value_type{ 1 };
            return f;
        }

        void set_cardinality(int n) {
            this->resize(1 << n, value_type{ 0 });
        }
        int cardinality() const {
            return __builtin_ctz(this->size());
        }

        ArraySPS cut_lower(size_type p) const {
            return ArraySPS(this->begin(), this->begin() + p);
        }
        ArraySPS cut_upper(size_type p) const {
            return ArraySPS(this->begin() + p, this->begin() + p + p);
        }

        void concat(const ArraySPS& upper) {
            assert(this->size() == upper.size());
            this->insert(this->end(), upper.begin(), upper.end());
        }

        ArraySPS operator+() const {
            return *this;
        }
        ArraySPS operator-() const {
            ArraySPS res(*this);
            for (auto& e : res) e = -e;
            return res;
        }
        ArraySPS& operator+=(const ArraySPS& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] += g[i];
            return *this;
        }
        ArraySPS& operator-=(const ArraySPS& g) {
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
            return *this;
        }
        ArraySPS& operator*=(const ArraySPS& g) {
            return *this = (zeta() *= g).mobius_inplace();
        }
        ArraySPS& operator*=(const value_type &c) {
            for (auto& e : *this) e *= c;
            return *this;
        }
        ArraySPS& operator/=(const value_type &c) {
            value_type inv_c = ::inv(c);
            for (auto& e : *this) e *= inv_c;
            return *this;
        }
        friend ArraySPS operator+(ArraySPS f, const ArraySPS& g) { f += g; return f; }
        friend ArraySPS operator-(ArraySPS f, const ArraySPS& g) { f -= g; return f; }
        friend ArraySPS operator*(ArraySPS f, const ArraySPS& g) { f *= g; return f; }
        friend ArraySPS operator*(ArraySPS f, const value_type &c) { f *= c; return f; }
        friend ArraySPS operator*(const value_type &c, ArraySPS f) { f *= c; return f; }
        friend ArraySPS operator/(ArraySPS f, const value_type &c) { f /= c; return f; }

        ArraySPS inv() {
            return zeta().inv_inplace().mobius_inplace();
        }
        ArraySPS sqrt() {
            return zeta().sqrt_inplace().mobius_inplace();
        }
        ArraySPS exp() {
            return zeta().exp_inplace().mobius_inplace();
        }
        ArraySPS log() {
            return zeta().log_inplace().mobius_inplace();
        }
        ArraySPS pow(long long k) {
            return zeta().pow_inplace(k).mobius_inplace();
        }

        struct ZetaSPS : public std::vector<polynomial_type> {
            using base_type = std::vector<polynomial_type>;
            ZetaSPS() = default;
            ZetaSPS(const ArraySPS<value_type, N>& f) : base_type::vector(array_ranked_subset_transform::ranked_zeta<T, N>(f)), _d(f.cardinality()) {}

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
            ArraySPS<value_type, N> mobius_inplace() {
                return array_ranked_subset_transform::deranked_mobius<value_type, N>(*this);
            }
            ArraySPS<value_type, N> mobius() const {
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
