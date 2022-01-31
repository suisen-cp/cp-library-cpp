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
        SPS(size_type n) : SPS(n, 0) {}
        SPS(size_type n, const value_type &val) : SPS(std::vector<value_type>(1 << n, val)) {}
        SPS(const base_type &a) : SPS(base_type(a)) {}
        SPS(base_type &&a) : base_type(std::move(a)) {
            resize(ceil_pow2(size()), 0);
        }
        SPS(std::initializer_list<value_type> l) : SPS(base_type(l)) {}

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
        int cardinality() const {
            return __builtin_ctz(size());
        }

        SPS cut_lower(size_type p) const {
            return SPS(begin(), begin() + p);
        }
        SPS cut_upper(size_type p) const {
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
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] += g[i];
            return *this;
        }
        SPS& operator-=(const SPS &g) {
            ensure(g.size());
            for (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
            return *this;
        }
        SPS& operator*=(const SPS &g) {
            SPS g_(g);
            ensure(g_.size()), g_.ensure(size());
            *this = subset_convolution<value_type>(*this, g_);
            return *this;
        }
        SPS& operator*=(value_type c) {
            for (auto &e : *this) e *= c;
            return *this;
        }
        SPS& operator/=(value_type c) {
            value_type inv_c = ::inv(c);
            for (auto &e : *this) e *= inv_c;
            return *this;
        }
        friend SPS operator+(const SPS &f, const SPS &g) { return SPS(f) += g; }
        friend SPS operator-(const SPS &f, const SPS &g) { return SPS(f) -= g; }
        friend SPS operator*(const SPS &f, const SPS &g) { return SPS(f) *= g; }
        friend SPS operator*(const SPS &f, value_type c) { return SPS(f) *= c; }
        friend SPS operator*(value_type c, const SPS &f) { return SPS(f) *= c; }
        friend SPS operator/(const SPS &f, value_type c) { return SPS(f) /= c; }

        SPS inv() {
            using namespace internal::subset_convolution;

            SPS res { ::inv(front()) };
            res.reserve(size());
            for (size_type p = 1; p < size(); p <<= 1) {
                auto res_poly = ranked_zeta<value_type>(res);
                auto poly = ranked_zeta<value_type>(cut_upper(p));
                for (size_type i = 0; i < p; ++i) {
                    muleq(muleq(poly[i], res_poly[i]), res_poly[i]);
                    for (auto &e : poly[i]) e *= -1;
                }
                res.concat(deranked_mobius<value_type>(poly));
            }
            return res;
        }
        // SPS inv() {
        //     using namespace internal::subset_convolution;
        //     const int n = size();
        //     auto rf = ranked(*this);
        //     rf[0][0] = ::inv(front());
        //     for (int i = 1; i < n; i <<= 1) {
        //         for (int k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l += 2 * k) for (int p = l; p < l + k; ++p) addeq(rf[p + k], rf[p]);
        //         for (int j = 0; j < i; ++j) {
        //             muleq(rf[i + j], rf[j]);
        //             muleq(rf[i + j], rf[j]);
        //             rf[i + j] = sub(rf[j], rf[i + j]);
        //         }
        //     }
        //     return deranked_mobius(rf);
        // }
        SPS sqrt() {
            using namespace internal::subset_convolution;

            SPS res { ::sqrt(front()) };
            assert(res[0] * res[0] == front());
            res.reserve(size());
            for (size_type p = 1; p < size(); p <<= 1) {
                auto res_poly = ranked_zeta<value_type>(res);
                auto poly = ranked_zeta<value_type>(cut_upper(p));
                for (size_type i = 0; i < p; ++i) {
                    for (auto &e : res_poly[i]) e *= 2;
                    muleq(poly[i], naive_poly_inv(res_poly[i]));
                }
                res.concat(deranked_mobius<value_type>(poly));
            }
            return res;
        }
        // SPS sqrt() {
        //     using namespace internal::subset_convolution;
        //     const int n = size();
        //     auto rf = ranked(*this);
        //     rf[0][0] = ::sqrt(front());
        //     assert(rf[0][0] * rf[0][0] == front());
        //     for (int i = 1; i < n; i <<= 1) {
        //         for (int k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l += 2 * k) for (int p = l; p < l + k; ++p) addeq(rf[p + k], rf[p]);
        //         for (int j = 0; j < i; ++j) {
        //             auto inv_2rg = rf[j];
        //             for (auto &e : inv_2rg) e *= 2;
        //             muleq(rf[i + j], naive_poly_inv(inv_2rg));
        //             addeq(rf[i + j], rf[j]);
        //         }
        //     }
        //     return deranked_mobius(rf);
        // }
        SPS exp() {
            SPS res { ::exp(front()) };
            res.reserve(size());
            for (size_type p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * res);
            return res;
        }
        // SPS exp() {
        //     using namespace internal::subset_convolution;
        //     const int n = size();
        //     auto rf = ranked(*this);
        //     rf[0][0] = ::exp(front());
        //     for (int i = 1; i < n; i <<= 1) {
        //         for (int k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l += 2 * k) for (int p = l; p < l + k; ++p) addeq(rf[p + k], rf[p]);
        //         for (int j = 0; j < i; ++j) {
        //             ++rf[i + j][0];
        //             muleq(rf[i + j], rf[j]);
        //         }
        //     }
        //     return deranked_mobius(rf);
        // }
        SPS log() {
            SPS res { ::log(front()) };
            res.reserve(size());
            SPS inv_ = cut_lower(size() >> 1).inv();
            for (size_type p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * inv_.cut_lower(p));
            return res;
        }
        // SPS log() {
        //     using namespace internal::subset_convolution;
        //     const int n = size();
        //     auto rg = ranked_zeta<value_type>(cut_lower(size() >> 1).inv());
        //     for (auto &v : rg) v.push_back(value_type(0));
        //     auto rf = ranked(*this);
        //     rf[0][0] = ::log(front());
        //     for (int i = 1; i < n; i <<= 1) {
        //         for (int k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l += 2 * k) for (int p = l; p < l + k; ++p) addeq(rf[p + k], rf[p]);
        //         for (int j = 0; j < i; ++j) {
        //             muleq(rf[i + j], rg[j]);
        //             addeq(rf[i + j], rf[j]);
        //         }
        //     }
        //     return deranked_mobius(rf);
        // }
        SPS pow(long long k) {
            const value_type c = (*this)[0];

            if (c != 0) {
                value_type pow_c = ::pow(c, k);
                SPS f = *this / c;
                f = (value_type(k) * f.log()).exp();
                for (auto &e : f) e *= pow_c;
                return f;
            }

            using namespace internal::subset_convolution;

            int n = cardinality();
            if (n < k) return SPS(n, 0);
            auto res_poly = ranked_zeta<value_type>(one(n));
            auto cur_poly = ranked_zeta<value_type>(*this);
            for (size_type i = 0; i < size(); ++i) {
                for (long long b = k; b; b >>= 1) {
                    if (b & 1) muleq(res_poly[i], cur_poly[i]);
                    muleq(cur_poly[i], std::vector<value_type>(cur_poly[i]));
                }
            }
            return SPS(deranked_mobius<value_type>(res_poly));
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

        static constexpr int ceil_pow2(size_type n) {
            size_type res = 1;
            while (res < n) res <<= 1;
            return res;
        }

        void ensure(size_type n) {
            if (size() < n) resize(n, 0);
        }

        static std::vector<value_type> naive_poly_inv(std::vector<value_type> &a) {
            const size_type n = a.size();
            std::vector<value_type> res(n, value_type(0));
            value_type v = ::inv(a[0]);
            for (size_type j = 0; j < n; ++j) {
                res[j] = j == 0;
                for (size_type k = 0; k < j; ++k) res[j] -= a[j - k] * res[k];
                res[j] *= v;
            }
            return res;
        }
};

} // namespace suisen

#endif // SUISEN_SPS
