#ifndef SUISEN_SPS
#define SUISEN_SPS

#include <cmath>
#include <initializer_list>
#include <type_traits>
#include "library/math/modint_extension.hpp"
#include "library/convolution/subset_convolution.hpp"

namespace suisen {

template <typename T>
class SPS : private std::vector<T> {
    public:
        using base_type = std::vector<T>;
        using value_type             = typename base_type::value_type;
        using reference              = typename base_type::reference;
        using const_reference        = typename base_type::const_reference;
        using pointer                = typename base_type::pointer;
        using const_pointer          = typename base_type::const_pointer;
        using allocator_type         = typename base_type::allocator_type;
        using size_type              = typename base_type::size_type;
        using difference_type        = typename base_type::difference_type;
        using iterator               = typename base_type::iterator;
        using const_iterator         = typename base_type::const_iterator;
        using reverse_iterator       = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;

        using base_type::vector;

        SPS() : SPS(0) {}
        SPS(int n) : SPS(n, 0) {}
        SPS(int n, T val) : SPS(std::vector<T>(1 << n, val)) {}
        SPS(const std::vector<T> &a) : SPS(std::vector<T>(a)) {}
        SPS(std::vector<T> &&a) : std::vector<T>(std::move(a)) {
            resize(ceil_pow2(size()), 0);
        }
        SPS(std::initializer_list<T> l) : SPS(std::vector<T>(l)) {}

        using base_type::operator=;

        using base_type::size;
        using base_type::max_size;
        using base_type::capacity;
        using base_type::empty;
        using base_type::reserve;
        using base_type::shrink_to_fit;

        using base_type::begin;
        using base_type::end;
        using base_type::cbegin;
        using base_type::cend;
        using base_type::rbegin;
        using base_type::rend;
        using base_type::crbegin;
        using base_type::crend;
        
        using base_type::operator[];
        using base_type::at;
        using base_type::data;
        using base_type::front;
        using base_type::back;

        using base_type::swap;

        static SPS one(int n) {
            SPS f(n, 0);
            f[0] = 1;
            return f;
        }

        friend bool operator==(const SPS &lhs, const SPS &rhs) {
            return std::operator==(lhs, rhs);
        }

        void set_cardinality(int n) {
            resize(1 << n, 0);
        }
        int cardinality() {
            return __builtin_ctz(size());
        }

        SPS cut_lower(unsigned int p) const {
            return SPS(begin(), begin() + p);
        }
        SPS cut_upper(unsigned int p) const {
            return SPS(begin() + p, begin() + p + p);
        }

        void concat(const SPS &upper) {
            assert(size() == upper.size());
            insert(end(), upper.begin(), upper.end());
        }

        SPS operator+() const {
            return *this;
        }
        SPS operator-() const {
            SPS res(*this);
            for (auto &e : res) e = -e;
            return res;
        }
        SPS& operator+=(const SPS &g) {
            ensure(g.size());
            for (unsigned int i = 0; i < g.size(); ++i) (*this)[i] += g[i];
            return *this;
        }
        SPS& operator-=(const SPS &g) {
            ensure(g.size());
            for (unsigned int i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
            return *this;
        }
        SPS& operator*=(const SPS &g) {
            SPS g_(g);
            ensure(g_.size()), g_.ensure(size());
            *this = subset_convolution<T>(*this, g_);
            return *this;
        }
        SPS& operator*=(T c) {
            for (auto &e : *this) e *= c;
            return *this;
        }
        SPS& operator/=(T c) {
            T inv_c = ::inv(c);
            for (auto &e : *this) e *= inv_c;
            return *this;
        }
        friend SPS operator+(const SPS &f, const SPS &g) { return SPS(f) += g; }
        friend SPS operator-(const SPS &f, const SPS &g) { return SPS(f) -= g; }
        friend SPS operator*(const SPS &f, const SPS &g) { return SPS(f) *= g; }
        friend SPS operator*(const SPS &f, T c) { return SPS(f) *= c; }
        friend SPS operator*(T c, const SPS &f) { return SPS(f) *= c; }
        friend SPS operator/(const SPS &f, T c) { return SPS(f) /= c; }

        SPS inv() {
            using namespace internal::subset_convolution;

            SPS res { ::inv(front()) };
            res.reserve(size());
            for (unsigned int p = 1; p < size(); p <<= 1) {
                auto res_poly = ranked_zeta<T>(res);
                auto poly = ranked_zeta<T>(cut_upper(p));
                for (unsigned int i = 0; i < p; ++i) {
                    muleq(muleq(poly[i], res_poly[i]), res_poly[i]);
                    for (auto &e : poly[i]) e *= -1;
                }
                res.concat(deranked_mobius<T>(poly));
            }
            return res;
        }
        SPS sqrt() {
            using namespace internal::subset_convolution;

            SPS res { ::sqrt(front()) };
            assert(res[0] * res[0] == front());
            res.reserve(size());
            for (unsigned int p = 1; p < size(); p <<= 1) {
                auto res_poly = ranked_zeta<T>(res);
                auto poly = ranked_zeta<T>(cut_upper(p));
                for (unsigned int i = 0; i < p; ++i) {
                    for (auto &e : res_poly[i]) e *= 2;
                    muleq(poly[i], naive_poly_inv(res_poly[i]));
                }
                res.concat(deranked_mobius<T>(poly));
            }
            return res;
        }
        SPS exp() {
            SPS res { ::exp(front()) };
            res.reserve(size());
            for (unsigned int p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * res);
            return res;
        }
        SPS log() {
            SPS res { ::log(front()) };
            res.reserve(size());
            SPS inv_ = cut_lower(size() >> 1).inv();
            for (unsigned int p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * inv_.cut_lower(p));
            return res;
        }
        SPS pow(long long k) {
            const T c = (*this)[0];

            if (c != 0) {
                T pow_c = ::pow(c, k);
                SPS f = *this / c;
                f = (T(k) * f.log()).exp();
                for (auto &e : f) e *= pow_c;
                return f;
            }

            using namespace internal::subset_convolution;

            int n = cardinality();
            if (n < k) return SPS(n, 0);
            auto res_poly = ranked<T>(one(n));
            auto cur_poly = ranked<T>(*this);
            for (; k; k >>= 1) {
                for (unsigned int i = 0; i < size(); ++i) {
                    if (k & 1) muleq(res_poly[i], cur_poly[i]);
                    muleq(cur_poly[i], std::vector<T>(cur_poly[i]));
                }
            }
            return SPS(deranked<T>(res_poly));
        }

    private:
        using base_type::assign;
        using base_type::push_back;
        using base_type::emplace_back;
        using base_type::pop_back;
        using base_type::insert;
        using base_type::emplace;
        using base_type::erase;
        using base_type::clear;
        using base_type::resize;

        static constexpr int ceil_pow2(unsigned int n) {
            unsigned int res = 1;
            while (res < n) res <<= 1;
            return res;
        }

        void ensure(unsigned int n) {
            if (size() < n) resize(n, 0);
        }

        static std::vector<T> naive_poly_inv(std::vector<T> &a) {
            const unsigned int n = a.size();
            std::vector<T> res(n, T(0));
            T v = ::inv(a[0]);
            for (unsigned int j = 0; j < n; ++j) {
                res[j] = j == 0;
                for (unsigned int k = 0; k < j; ++k) res[j] -= a[j - k] * res[k];
                res[j] *= v;
            }
            return res;
        }
};

} // namespace suisen

#endif // SUISEN_SPS
