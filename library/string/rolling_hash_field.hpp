#ifndef SUISEN_ROLLING_HASH_FIELD
#define SUISEN_ROLLING_HASH_FIELD

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <random>
#include <vector>

#include "library/util/default_operator.hpp"

namespace suisen {
    template <
        typename T,
        size_t base_num,
        auto add = default_operator::add<T>,
        auto zero = default_operator::zero<T>,
        auto neg = default_operator::neg<T>,
        auto mul = default_operator::mul<T>,
        auto one = default_operator::one<T>
    >
    struct RollingHashField {
        using hash_type = std::array<T, base_num>;

        RollingHashField() = default;

        hash_type operator()(int l, int r) {
            ensure_pows(r - l);
            hash_type res;
            for (size_t base_id = 0; base_id < base_num; ++base_id) {
                res[base_id] = add(hash[base_id][r], neg(mul(hash[base_id][l], pows[base_id][r - l])));
            }
            return res;
        }

        static hash_type concat(hash_type h1, hash_type h2, int length_h2) {
            ensure_pows(length_h2);
            hash_type res;
            for (int base_id = 0; base_id < base_num; ++base_id) {
                res[base_id] = add(mul(h1[base_id], pows[base_id][length_h2]), h2[base_id]);
            }
            return res;
        }
        static hash_type pointwise_add(hash_type h1, hash_type h2) {
            hash_type h3;
            for (size_t i = 0; i < base_num; ++i) h3[i] = add(h1[i], h2[i]);
            return h3;
        }

        static void set_bases(const std::array<T, base_num>& new_bases) {
            bases = new_bases;
            already_set_bases = true;
        }

        template <typename Iterable>
        static RollingHashField create(const Iterable& s, const std::array<std::function<T(typename Iterable::value_type)>, base_num> &hasher) {
            std::vector<std::array<T, base_num>> a;
            for (const auto& e : s) {
                auto &h = a.emplace_back();
                for (size_t i = 0; i < base_num; ++i) {
                    h[i] = hasher[i](e);
                }
            }
            return RollingHashField(a);
        }

        int lcp(int pos1, int pos2) {
            if (pos1 > pos2) std::swap(pos1, pos2);
            int l = 0, r = n - pos2 + 1;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                ((*this)(pos1, pos1 + m) == (*this)(pos2, pos2 + m) ? l : r) = m;
            }
            return l;
        }

    private:
        static inline std::array<T, base_num> bases;
        static inline std::array<std::vector<T>, base_num> pows;
        static inline bool already_set_bases = false;

        int n;
        std::array<std::vector<T>, base_num> hash;

        RollingHashField(const std::vector<std::array<T, base_num>>& a) : n(a.size()) {
            assert(already_set_bases);
            for (size_t base_id = 0; base_id < base_num; ++base_id) {
                hash[base_id].resize(n + 1);
                hash[base_id][0] = zero();
                for (int i = 0; i < n; ++i) hash[base_id][i + 1] = add(mul(hash[base_id][i], bases[base_id]), a[i][base_id]);
            }
        }

        static void ensure_pows(int n) {
            if (int(pows[0].size()) > n) return;
            for (size_t base_id = 0; base_id < base_num; ++base_id) {
                const int old_size = std::max(size_t(1), pows[base_id].size());
                pows[base_id].resize(n + 1);
                pows[base_id][0] = one();
                for (int i = old_size; i <= n; ++i) pows[base_id][i] = mul(pows[base_id][i - 1], bases[base_id]);
            }
        }
    };
} // namespace suisen

#endif // SUISEN_ROLLING_HASH_FIELD
