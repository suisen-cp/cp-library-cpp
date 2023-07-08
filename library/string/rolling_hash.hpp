#ifndef SUISEN_ROLLING_HASH
#define SUISEN_ROLLING_HASH

#include <array>
#include <cstdint>
#include <string>
#include <random>
#include <vector>

#include "library/math/pow_mods.hpp"
#include "library/number/modint_2^61m1.hpp"

namespace suisen {
    namespace internal::rolling_hash {
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

    template <int base_num = 1, typename mint = modint2p61m1>
    struct RollingHash {
    public:
        using modint_type = mint;
        using hash_type = decltype(mint::mod());

        RollingHash() = default;
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
