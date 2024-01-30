#ifndef SUISEN_ORDER_Z_mZ
#define SUISEN_ORDER_Z_mZ

#include <map>
#include <tuple>

#include <atcoder/modint>
#include "library/number/fast_factorize.hpp"

namespace suisen {
    namespace internal::order_prime_mod {
        template <int id>
        struct mint64 {
            static uint64_t mod() { return _mod; }
            static void set_mod(uint64_t new_mod) { mint64<id>::_mod = new_mod; }

            mint64() : _val(0) {}
            mint64(long long val) : _val(safe_mod(val)) {}

            uint64_t val() { return _val; }

            friend mint64& operator*=(mint64& x, const mint64& y) {
                x._val = __uint128_t(x._val) * y._val % _mod;
                return x;
            }
            friend mint64 operator*(mint64 x, const mint64& y) {
                x *= y;
                return x;
            }
            mint64 pow(long long b) const {
                assert(b >= 0);
                mint64 p = *this, res = 1;
                for (; b; b >>= 1) {
                    if (b & 1) res *= p;
                    p *= p;
                }
                return res;
            }
        private:
            static inline uint64_t _mod;
            uint64_t _val;

            static uint64_t safe_mod(long long val) { return (val %= _mod) < 0 ? val + _mod : val; }
        };
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    struct OrderMod {
        using U = std::make_unsigned_t<T>;
        OrderMod() = default;
        OrderMod(T m) : _mod(m) {
            auto factorized = fast_factorize::factorize<T>(_mod);
            _is_prime = factorized.size() == 1;
            _lambda = _carmichael(factorized);
            _phi = _totient(factorized);
            for (auto [p, q] : fast_factorize::factorize<T>(_lambda)) {
                U r = 1;
                for (int i = 0; i < q; ++i) r *= p;
                _fac_lambda.emplace_back(p, q, r);
            }
        }

        bool is_primitive_root(U a) const {
            if (_mod < 1ULL << 32) {
                using mint = atcoder::dynamic_modint<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_mod);
                bool res = _is_primitive_root_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            } else {
                using mint = internal::order_prime_mod::mint64<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_mod);
                bool res = _is_primitive_root_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            }
        }

        T primitive_root() const {
            assert(_lambda == _phi);
            if (_mod < 1ULL << 32) {
                return _primitive_root_impl<std::mt19937>();
            } else {
                return _primitive_root_impl<std::mt19937_64>();
            }
        }

        T operator()(U a) const {
            if (_mod < 1ULL << 31) {
                using mint = atcoder::dynamic_modint<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_mod);
                T res = _order_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            } else {
                using mint = internal::order_prime_mod::mint64<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_mod);
                T res = _order_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            }
        }

        T mod() const {
            return _mod;
        }
        T totient() const {
            return _phi;
        }
        T carmichael() const {
            return _lambda;
        }
        bool is_prime() const {
            return _is_prime;
        }
        std::vector<T> carmichael_prime_factors() const {
            std::vector<T> res;
            for (const auto &e : _fac_lambda) res.push_back(std::get<0>(e));
            return res;
        }

    private:
        U _mod;
        U _phi;
        U _lambda;
        bool _is_prime;

        std::vector<std::tuple<U, int, U>> _fac_lambda;

        static T _carmichael(const std::vector<std::pair<T, int>>& factorized) {
            T lambda = 1;
            for (auto [p, ep] : factorized) {
                T phi = p - 1;
                int exponent = ep - (1 + (p == 2 and ep >= 3));
                for (int i = 0; i < exponent; ++i) phi *= p;
                lambda = std::lcm(lambda, phi);
            }
            return lambda;
        }
        static T _totient(const std::vector<std::pair<T, int>>& factorized) {
            T t = 1;
            for (const auto& [p, ep] : factorized) {
                t *= p - 1;
                for (int i = 0; i < ep - 1; ++i) t *= p;
            }
            return t;
        }

        template <typename mint>
        bool _is_primitive_root_impl(U a) const {
            if (_lambda != _phi) return false;
            if (_mod == 2) return a % 2 == 1;

            const int k = _fac_lambda.size();
            U x = _lambda;
            for (const auto& [p, q, pq] : _fac_lambda) x /= p;

            mint b = mint(a).pow(x);
            if (k == 1) return b.val() != 1;

            auto dfs = [&](auto dfs, const int l, const int r, const mint val) -> bool {
                const int m = (l + r) >> 1;

                U lp = 1;
                for (int i = m; i < r; ++i) lp *= std::get<0>(_fac_lambda[i]);
                mint lval = val.pow(lp);
                if (m - l == 1) {
                    if (lval.val() == 1) return false;
                } else {
                    if (not dfs(dfs, l, m, lval)) return false;
                }

                U rp = 1;
                for (int i = l; i < m; ++i) rp *= std::get<0>(_fac_lambda[i]);
                mint rval = val.pow(rp);
                if (r - m == 1) {
                    if (rval.val() == 1) return false;
                } else {
                    if (not dfs(dfs, m, r, rval)) return false;
                }

                return true;
            };
            return dfs(dfs, 0, k, b);
        }

        template <typename Rng>
        T _primitive_root_impl() const {
            if (_mod == 2) return 1;

            Rng rng{ std::random_device{}() };
            while (true) {
                U a = rng() % (_mod - 2) + 2;
                while (not _is_prime and std::gcd(a, _mod) != 1) {
                    a = rng() % (_mod - 2) + 2;
                }
                if (is_primitive_root(a)) return a;
            }
        }

        template <typename mint>
        U _order_impl(U a) const {
            if (_mod == 2) return a % 2 == 1;

            const int k = _fac_lambda.size();

            U res = 1;

            auto update = [&](U p, mint val) {
                while (val.val() != 1) {
                    val = val.pow(p);
                    res *= p;
                }
            };

            if (k == 1) {
                update(std::get<0>(_fac_lambda.front()), a);
                return res;
            }

            auto dfs = [&](auto dfs, const int l, const int r, const mint val) -> void {
                const int m = (l + r) >> 1;

                U lp = 1;
                for (int i = m; i < r; ++i) lp *= std::get<2>(_fac_lambda[i]);
                mint lval = val.pow(lp);
                if (m - l == 1) {
                    update(std::get<0>(_fac_lambda[l]), lval);
                } else {
                    dfs(dfs, l, m, lval);
                }

                U rp = 1;
                for (int i = l; i < m; ++i) rp *= std::get<2>(_fac_lambda[i]);
                mint rval = val.pow(rp);
                if (r - m == 1) {
                    update(std::get<0>(_fac_lambda[m]), rval);
                } else {
                    dfs(dfs, m, r, rval);
                }
            };
            dfs(dfs, 0, k, a);

            return res;
        }
    };
} // namespace suisen

#endif // SUISEN_ORDER_Z_mZ
