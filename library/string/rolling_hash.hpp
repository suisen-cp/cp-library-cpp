#ifndef SUISEN_ROLLING_HASH
#define SUISEN_ROLLING_HASH

#include <array>
#include <cstdint>
#include <string>
#include <random>
#include <vector>

#include "library/math/pow_mods.hpp"

namespace suisen {
    namespace internal::rolling_hash {
        // reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
        struct Modint2305843009213693951 {
            using self = Modint2305843009213693951;

            Modint2305843009213693951() = default;
            Modint2305843009213693951(uint64_t v) : v(fast_mod(v)) {}

            static constexpr uint64_t mod() {
                return _mod;
            }

            static constexpr uint64_t fast_mod(uint64_t v) {
                constexpr uint32_t mid = 61;
                constexpr uint64_t mask = (uint64_t(1) << mid) - 1;
                uint64_t u = v >> mid;
                uint64_t d = v & mask;
                uint64_t res = u + d;
                if (res >= _mod) res -= _mod;
                return res;
            }

            uint64_t val() const {
                return v;
            }

            self& operator+=(const self &rhs) {
                v += rhs.v;
                if (v >= _mod) v -= _mod;
                return *this;
            }
            self& operator-=(const self &rhs) {
                if (v < rhs.v) v += _mod;
                v -= rhs.v;
                return *this;
            }
            self& operator*=(const self &rhs) {
                static constexpr uint32_t mid31 = 31;
                static constexpr uint64_t mask31 = (uint64_t(1) << mid31) - 1;

                uint64_t au = v >> mid31;     // < 2^30
                uint64_t ad = v & mask31;     // < 2^31
                uint64_t bu = rhs.v >> mid31; // < 2^30
                uint64_t bd = rhs.v & mask31; // < 2^31
                
                //   a * b
                // = (au * 2^31 + ad) * (bu * 2^31 + bd)
                // = au * bu * 2^62             # au * bu * 2^62 ≡ au * bu * 2 < 2^61
                // + (au * bd + ad * bu) * 2^31 # m := au * bd + ad * bu
                //                              # m <= 2 * (2^31 - 1) * (2^30 - 1) = 2^62 - 6 * 2^30 + 2
                //                              # m = mu * 2^30 + md (0 <= mu < 2^32, 0 <= md < 2^30)
                //                              # m * 2^31 ≡ mu + md * 2^31 < 2^61 + 2^31
                // + ad * bd                    # ad * bd <= (2^31 - 1) ** 2 = 2^62 - 2^32 + 1 < 2^62 - 2^31
                // ≡ au * bu * 2 + mu + md * 2^31 + ad * bd < 2^63

                static constexpr uint32_t mid30 = 30;
                static constexpr uint64_t mask30 = (uint64_t(1) << mid30) - 1;

                uint64_t m = au * bd + ad * bu;
                uint64_t mu = m >> mid30;
                uint64_t md = m & mask30;

                v = fast_mod((au * bu << 1) + mu + (md << 31) + ad * bd);
                return *this;
            }

            friend self operator+(const self &l, const self &r) { return self(l) += r; }
            friend self operator-(const self &l, const self &r) { return self(l) -= r; }
            friend self operator*(const self &l, const self &r) { return self(l) *= r; }
            friend bool operator==(const self &l, const self &r) { return l.v == r.v; }
        private:
            static constexpr uint64_t _mod = (uint64_t(1) << 61) - 1; // 2305843009213693951UL : prime
            uint64_t v;
        };

        template <int base_num, typename mint>
        std::array<mint, base_num> gen_bases() {
            static std::mt19937_64 rng(std::random_device{}());
            std::array<mint, base_num> res;
            for (int i = 0; i < base_num; ++i) {
                res[i] = rng();
                while (res[i].val() < 128) res[i] = rng();
            }
            return res;
        }
        template <int base_num, typename mint>
        std::array<pow_mods<mint>, base_num> init_pows(const std::array<mint, base_num>& bases) {
            std::array<pow_mods<mint>, base_num> res;
            for (int i = 0; i < base_num; ++i) {
                res[i] = pow_mods<mint>(bases[i], 0);
            }
            return res;
        }
    }

    template <int base_num = 1, typename mint = internal::rolling_hash::Modint2305843009213693951>
    struct RollingHash {
    private:
        using default_mint = internal::rolling_hash::Modint2305843009213693951;
    public:
        using modint_type = mint;
        using hash_type = decltype(mint::mod());

        RollingHash() {}
        RollingHash(const std::vector<int> &a) : n(a.size()) {
            for (int base_id = 0; base_id < base_num; ++base_id) {
                hash[base_id].resize(n + 1);
                hash[base_id][0] = 0;
                for (int i = 0; i < n; ++i) hash[base_id][i + 1] = hash[base_id][i] * bases[base_id] + a[i];
            }
        }

        std::array<uint64_t, base_num> operator()(int l, int r) {
            std::array<uint64_t, base_num> res;
            for (int base_id = 0; base_id < base_num; ++base_id) {
                res[base_id] = (hash[base_id][r] - hash[base_id][l] * pows[base_id][r - l]).val();
            }
            return res;
        }

        std::array<uint64_t, base_num> concat(std::array<uint64_t, base_num> h, int l, int r) {
            for (int base_id = 0; base_id < base_num; ++base_id) {
                h[base_id] = (h[base_id] * pows[base_id][r - l] + hash[base_id][r] - hash[base_id][l] * pows[base_id][r - l]).val();
            }
            return h;
        }

        static auto mod() {
            return mint::mod();
        }

        static void set_bases(const std::array<mint, base_num> &new_bases) {
            bases = new_bases;
            pows = internal::rolling_hash::init_pows<base_num, mint>(bases);
        }

        template <typename Iterable, typename ToIntFunction>
        static RollingHash from(const Iterable &s, ToIntFunction f) {
            std::vector<int> a;
            for (auto &&e : s) a.push_back(f(e));
            return RollingHash(a);
        }
        static RollingHash from_lowercase_alphabet(const std::string &s) {
            return from(s, [](const auto &e) { return e - 'a' + 1; });
        }
        static RollingHash from_uppercase_alphabet(const std::string &s) {
            return from(s, [](const auto &e) { return e - 'A' + 1; });
        }
        static RollingHash from_alphabet(const std::string &s) {
            return from(s, [](const auto &e) { return std::islower(e) ? e - 'a' + 27 : e - 'A' + 1; });
        }
        static RollingHash from_digit(const std::string &s) {
            return from(s, [](const auto &e) { return e - '0' + 1; });
        }

    private:
        static inline std::array<mint, base_num> bases = internal::rolling_hash::gen_bases<base_num, mint>();
        static inline std::array<pow_mods<mint>, base_num> pows = internal::rolling_hash::init_pows<base_num, mint>(bases);

        int n;
        std::array<std::vector<mint>, base_num> hash;
    };
} // namespace suisen

#endif // SUISEN_ROLLING_HASH
