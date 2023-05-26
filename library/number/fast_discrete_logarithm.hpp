#ifndef SUISEN_INDEX_CALCULUS
#define SUISEN_INDEX_CALCULUS

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <optional>
#include <map>

#include <atcoder/modint>
#include <atcoder/math>

#include "library/number/fast_factorize.hpp"
#include "library/number/order_Z_mZ.hpp"
#include "library/number/discrete_logarithm.hpp"

namespace suisen::fast_discrete_logarithm {
    namespace internal {
        template <typename mint>
        struct SystemOfLinearEquations {
            SystemOfLinearEquations() = default;
            SystemOfLinearEquations(int target_var_id) : target_var_id(target_var_id) {}

            void append(std::vector<mint> r, mint bi) {
                int ti = target_var_id + 1;
                for (int i = 0; i <= target_var_id; ++i) if (r[i] != 0) {
                    ti = i;
                    break;
                }
                if (ti > target_var_id) return;

                const int l = A.size();
                const int start = std::lower_bound(top_pos.begin(), top_pos.end(), ti) - top_pos.begin();
                for (int i = start; i < l; ++i) {
                    eliminate(top_pos[i], A[i], b[i], ti, r, bi);
                    if (ti > target_var_id) return;
                }
                A.push_back(std::move(r));
                top_pos.push_back(ti);
                b.push_back(bi);
            }
            void append(const std::vector<std::pair<int, mint>>& ri, mint bi) {
                std::vector<mint> r(target_var_id + 1);
                for (auto [j, v] : ri) r[j] = v;
                append(std::move(r), bi);
            }

            std::optional<mint> target() {
                if (top_pos.empty() or top_pos.back() != target_var_id) return std::nullopt;
                auto [g, inv_c] = atcoder::internal::inv_gcd(A.back().back().val(), mint::mod());
                return g == 1 ? std::make_optional(b.back() * inv_c) : std::nullopt;
            }

            void change_target() {
                const int l = A.size();

                int t = -1;
                for (int i = l - 1; i >= 0; --i) {
                    if (A[i][target_var_id] != 0) {
                        t = i;
                        break;
                    }
                }

                SystemOfLinearEquations<mint> nxt(target_var_id);
                for (int i = l - 1; i > t; --i) {
                    nxt.append(A[i], b[i]);
                }

                for (int i = t - 1; i >= 0; --i) {
                    if (A[i][target_var_id] != 0) {
                        const auto T = euclid(A[t][target_var_id].val(), A[i][target_var_id].val());
                        for (int col = top_pos[i]; col <= target_var_id; ++col) {
                            apply_euclid(T, A[t][col], A[i][col]);
                        }
                        apply_euclid(T, b[t], b[i]);
                    }
                    nxt.append(A[i], b[i]);
                }

                *this = std::move(nxt);
            }
        private:
            int target_var_id;
            std::vector<std::vector<mint>> A;
            std::vector<int> top_pos;
            std::vector<mint> b;

            // Euclidean Algorithm
            // A * [a, b] = [gcd(a,b), 0]
            static std::array<std::array<int, 2>, 2> euclid(int a, int b) {
                int x = 1, y = 0, z = 0, w = 1;
                while (b) {
                    int p = a / b, q = a % b;
                    x -= p * z, std::swap(x, z);
                    y -= p * w, std::swap(y, w);
                    a = b, b = q;
                }
                return { x, y, z, w };
            }
            static void apply_euclid(const std::array<std::array<int, 2>, 2>& A, mint& x, mint& y) {
                mint x2 = x, y2 = y;
                x = A[0][0] * x2 + A[0][1] * y2;
                y = A[1][0] * x2 + A[1][1] * y2;
            }

            static void eliminate(int& ti, std::vector<mint>& ri, mint& bi, int& tj, std::vector<mint>& rj, mint& bj) {
                if (ti != tj) {
                    if (ti > tj) std::swap(ti, tj), std::swap(ri, rj), std::swap(bi, bj);
                    return;
                }
                const int siz = ri.size();
                assert(int(rj.size()) == siz);

                const auto T = euclid(ri[ti].val(), rj[tj].val());
                for (int col = ti; col < siz; ++col) {
                    apply_euclid(T, ri[col], rj[col]);
                }
                apply_euclid(T, bi, bj);

                while (tj < siz and rj[tj] == 0) ++tj;
            }
        };
    }

    struct IndexCalculus {
    private:
        using mint = atcoder::dynamic_modint<73495793>;
        using mint2 = atcoder::dynamic_modint<73495794>;
    public:
        IndexCalculus() = default;
        IndexCalculus(const OrderMod<int>& ord) : _p(ord.mod()), _ord(ord) {
            assert(ord.is_prime());
        }

        int operator()(int a, int b, int p) {
            int old_mod = mint::mod(), old_mod2 = mint2::mod();
            mint::set_mod(p), mint2::set_mod(p - 1);
            int res = discrete_log_impl(a, b, p);
            mint::set_mod(old_mod), mint2::set_mod(old_mod2);
            return res;
        }
        static int discrete_logarithm(int a, int b, int p) {
            return IndexCalculus{}(a, b, p);
        }
    private:
        static constexpr int MAX_B = 80;
        static constexpr uint32_t primes[MAX_B]{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
            31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
            127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
            179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
            233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
            283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
            353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        };
        // inv_primes[i] = ceil(2^32 / primes[i])
        static constexpr uint32_t inv_primes[MAX_B]{
            2147483648,1431655766, 858993460, 613566757, 390451573, 330382100, 252645136, 226050911, 186737709, 148102321,
            138547333, 116080198, 104755300, 99882961, 91382283, 81037119, 72796056, 70409300, 64103990, 60492498,
            58835169, 54366675, 51746594, 48258060, 44278014, 42524429, 41698712, 40139882, 39403370, 38008561,
            33818641, 32786010, 31350127, 30899046, 28825284, 28443493, 27356480, 26349493, 25718368, 24826401,
            23994231, 23729102, 22486740, 22253717, 21801865, 21582751, 20355296, 19259944, 18920561, 18755316,
            18433337, 17970575, 17821442, 17111424, 16711936, 16330675, 15966422, 15848588, 15505298, 15284582,
            15176563, 14658592, 13990122, 13810185, 13721941, 13548793, 12975733, 12744711, 12377428, 12306497,
            12167047, 11963698, 11702909, 11514658, 11332368, 11214014, 11041048, 10818558, 10710642, 10501143,
        };

        int _p = -1;
        OrderMod<int> _ord;
        int _a = -1;
        internal::SystemOfLinearEquations<mint2> _eq;

        static int safe_mod(int a, int p) { return ((a %= p) < 0) ? a + p : a; }

        static int discrete_log_naive(mint a, mint b, int ord_a) {
            mint pow_a = 1;
            for (int res = 0; res < ord_a; ++res) {
                if (pow_a == b) return res;
                pow_a *= a;
            }
            return -1;
        }

        static bool is_smooth(const int B, uint32_t v) {
            assert(B <= MAX_B);
            for (int i = 0; i < B; ++i) {
                const uint32_t m = primes[B - i - 1], im = inv_primes[B - i - 1];
                if (uint32_t q = (uint64_t(v) * im) >> 32; v == q * m) {
                    // q = floor(v/m)
                    do v = q, q = (uint64_t(v) * im) >> 32; while (v == q * m);
                }
            }
            return v == 1;
        }

        static std::optional<std::vector<mint2>> try_factorize(const int B, uint32_t v) {
            assert(B <= MAX_B);
            if (not is_smooth(B, v)) return std::nullopt;
            std::vector<mint2> res(B + 1);
            for (int i = 0; i < B; ++i) {
                const uint32_t m = primes[B - i - 1], im = inv_primes[B - i - 1];
                int c = 0;
                uint32_t q = (uint64_t(v) * im) >> 32;
                while (v == q * m) {
                    v = q, q = (uint64_t(v) * im) >> 32;
                    ++c;
                }
                res[i] = c;
            }
            res[B] = -1;
            return res;
        }

        int discrete_log_impl(int a, int b, int p) {
            a = safe_mod(a, p), b = safe_mod(b, p);

            if (b == 0) return a == 0 ? 1 : -1;
            if (b == 1) return 0;
            if (a == 0) return -1;
            if (a == 1) return -1;

            if (p <= 64) return discrete_log_naive(a, b, p - 1);

            const int B = ::pow(p - 1, 1 / (2 * ::sqrt(::log(p - 1) / ::log(::log(p - 1))))) + 5;
            assert(B <= MAX_B);

            if (p != _p) {
                _p = p, _ord = OrderMod<int>(p);
                _a = a, _eq = internal::SystemOfLinearEquations<mint2>(B);
            } else if (a != _a) {
                _a = a, _eq = internal::SystemOfLinearEquations<mint2>(B);
            } else {
                _eq.change_target();
            }

            assert(_ord.is_prime());

            const int ord_a = _ord(a), ord_b = _ord(b);
            if (ord_a % ord_b) return -1;
            if (ord_a <= 64) return discrete_log_naive(a, b, ord_a);

            static std::mt19937 rng{};
            while (true) {
                const int k = rng() % ord_a;
                auto opt_fac = try_factorize(B, (mint(a).pow(k) * b).val());
                if (not opt_fac) continue;
                auto& fac = *opt_fac;
                _eq.append(std::move(fac), k);
                if (auto res = _eq.target()) return res->val() % ord_a;
            }
        }
    };

    namespace internal {
        using mint = atcoder::dynamic_modint<73495793>;

        // min{ i | 0 <= i < r and a^i = b } or -1
        int naive(int a, int b, int r) {
            mint pow_a = 1;
            for (int res = 0; res < r; ++res) {
                if (pow_a == b) return res;
                pow_a *= a;
            }
            return -1;
        }

        int pohlig_hellman_prime_power_bsgs(int a, int b, int ord_a, int p, int q) {
            // ord_a = p ^ q
            if (ord_a <= 64) return naive(a, b, ord_a);
            const mint gamma = mint(a).pow(ord_a / p);
            const mint inv_a = mint(a).inv();

            int x = 0;
            for (int k = 0, pl = 1, pr = ord_a; k < q; ++k) {
                pr /= p;
                int d = suisen::discrete_logarithm_coprime(gamma, (inv_a.pow(x) * b).pow(pr));
                if (d == -1) return -1;
                x += pl * d;
                pl *= p;
            }
            return x;
        }

        int pohlig_hellman(int a, int b, int p, int q, const OrderMod<int>& ord) {
            // gcd(a, p) = 1

            if (b == 1) return 0;
            if (a == 1) return b == 1 ? 0 : -1;
            if (b % p == 0) return -1;

            if (q == 1) {
                
                return IndexCalculus{ ord }(a, b, p);
            }

            const int ord_a = ord(a);
            if (ord_a <= 64) return naive(a, b, ord_a);
            if (ord_a % ord(b)) return -1;

            const std::vector<std::pair<int, int>> ord_factorized = [&] {
                std::vector<std::pair<int, int>> res;
                int v = ord_a;
                for (int p : ord.carmichael_prime_factors()) if (v % p == 0) {
                    int& c = res.emplace_back(p, 0).second;
                    do v /= p, ++c; while (v % p == 0);
                }
                return res;
            }();

            std::vector<long long> rs, ms;
            for (auto [p, q] : ord_factorized) {
                int pq = 1;
                for (int i = 0; i < q; ++i) pq *= p;

                const int na = mint(a).pow(ord_a / pq).val(), nb = mint(b).pow(ord_a / pq).val();
                const int x = pohlig_hellman_prime_power_bsgs(na, nb, pq, p, q);
                if (x == -1) return -1;
                rs.push_back(x), ms.push_back(pq);
            }
            return atcoder::crt(rs, ms).first;
        }
    }

    namespace internal {
        int discrete_logarithm_coprime(int a, int b) {
            const int m = mint::mod();
            assert(std::gcd(a, m) == 1);

            long long r = 0, md = 1;
            for (auto [p, q] : fast_factorize::factorize(m)) { // CRT
                int pq = 1;
                for (int i = 0; i < q; ++i) pq *= p;

                mint::set_mod(pq);
                OrderMod ord(pq);
                const long long r2 = pohlig_hellman(mint(a).val(), mint(b).val(), p, q, ord);
                if (r2 == -1) return -1;

                const long long md2 = ord(a);
                std::tie(r, md) = atcoder::crt({ r, r2 }, { md, md2 });
                if (md == 0) return -1;
            }
            return r;
        }

        int discrete_logarithm_arbitrary_mod(int a, int b) {
            const int m = mint::mod();

            if (m == 1 or b == 1) return 0;
            if (a == 0) return b == 0 ? 1 : b == 1 ? 0 : -1;
            if (a == 1) return b == 1 ? 0 : -1;

            const int floor_log2_m = [m] {
                int res = 0;
                while (1 << (res + 1) <= m) ++res;
                return res;
            }();

            if (int i = naive(a, b, floor_log2_m); i != -1) return i;

            const int pow_a = mint(a).pow(floor_log2_m).val();
            const int g = std::gcd(pow_a, m);
            if (b % g) return -1;

            mint::set_mod(m / g);
            const int t = discrete_logarithm_coprime(mint(a).val(), (mint(b) / pow_a).val());

            return t != -1 ? floor_log2_m + t : -1;
        }
    }

    int discrete_logarithm(int a, int b, int m) {
        using internal::mint;
        const int old_mod = mint::mod();
        mint::set_mod(m);
        const int res = internal::discrete_logarithm_arbitrary_mod(mint(a).val(), mint(b).val());
        mint::set_mod(old_mod);
        return res;
    }
} // namespace suisen


#endif // SUISEN_INDEX_CALCULUS
