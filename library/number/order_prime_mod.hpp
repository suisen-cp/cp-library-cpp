#ifndef SUISEN_ORDER_PRIME_MOD
#define SUISEN_ORDER_PRIME_MOD

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
    struct OrderFp {
        using U = std::make_unsigned_t<T>;
        OrderFp(T p) : _p(p) {
            assert(_p >= 1 and miller_rabin::is_prime(_p));
            for (auto [p, q] : fast_factorize::factorize(_p - 1)) {
                U r = 1;
                for (int i = 0; i < q; ++i) r *= p;
                _factorized.emplace_back(p, q, r);
            }
        }

        bool is_primitive_root(U a) const {
            if (_p < 1ULL << 32) {
                using mint = atcoder::dynamic_modint<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_p);
                bool res = is_primitive_root_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            } else {
                using mint = internal::order_prime_mod::mint64<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_p);
                bool res = is_primitive_root_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            }
        }

        T primitive_root() const {
            if (_p < 1ULL << 32) {
                return primitive_root_impl<std::mt19937>();
            } else {
                return primitive_root_impl<std::mt19937_64>();
            }
        }

        T operator()(U a) const {
            if (_p < 1ULL << 32) {
                using mint = atcoder::dynamic_modint<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_p);
                T res = order_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            } else {
                using mint = internal::order_prime_mod::mint64<1000000000>;
                U old_mod = mint::mod();
                mint::set_mod(_p);
                T res = order_impl<mint>(a);
                mint::set_mod(old_mod);
                return res;
            }
        }

        T mod() const {
            return _p;
        }

    private:
        U _p;
        std::vector<std::tuple<U, int, U>> _factorized;

        template <typename mint>
        bool is_primitive_root_impl(U a) const {
            if (_p == 2) return a % 2 == 1;

            const int k = _factorized.size();
            U x = _p - 1;
            for (const auto &[p, q, pq] : _factorized) x /= p;

            mint b = mint(a).pow(x);
            if (k == 1) return b.val() != 1;
    
            auto dfs = [&](auto dfs, const int l, const int r, const mint val) -> bool {
                const int m = (l + r) >> 1;

                U lp = 1;
                for (int i = m; i < r; ++i) lp *= std::get<0>(_factorized[i]);
                mint lval = val.pow(lp);
                if (m - l == 1) {
                    if (lval.val() == 1) return false;
                } else {
                    if (not dfs(dfs, l, m, lval)) return false;
                }

                U rp = 1;
                for (int i = l; i < m; ++i) rp *= std::get<0>(_factorized[i]);
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
        T primitive_root_impl() const {
            if (_p == 2) return 1;

            Rng rng{ std::random_device{}() };
            while (true) {
                if (U a = rng() % (_p - 2) + 2; is_primitive_root(a)) {
                    return a;
                }
            }
        }

        template <typename mint>
        U order_impl(U a) const {
            if (_p == 2) return a % 2 == 1;

            const int k = _factorized.size();

            U res = 1;

            auto update = [&](U p, mint val) {
                while (val.val() != 1) {
                    val = val.pow(p);
                    res *= p;
                }
            };
    
            if (k == 1) {
                update(std::get<0>(_factorized.front()), a);
                return res;
            }

            auto dfs = [&](auto dfs, const int l, const int r, const mint val) -> void {
                const int m = (l + r) >> 1;

                U lp = 1;
                for (int i = m; i < r; ++i) lp *= std::get<2>(_factorized[i]);
                mint lval = val.pow(lp);
                if (m - l == 1) {
                    update(std::get<0>(_factorized[l]), lval);
                } else {
                    dfs(dfs, l, m, lval);
                }

                U rp = 1;
                for (int i = l; i < m; ++i) rp *= std::get<2>(_factorized[i]);
                mint rval = val.pow(rp);
                if (r - m == 1) {
                    update(std::get<0>(_factorized[m]), rval);
                } else {
                    dfs(dfs, m, r, rval);
                }
            };
            dfs(dfs, 0, k, a);

            return res;
        }
    };
} // namespace suisen

#endif // SUISEN_ORDER_PRIME_MOD
