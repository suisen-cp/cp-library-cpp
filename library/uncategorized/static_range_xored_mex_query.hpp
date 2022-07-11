#ifndef SUISEN_RANGE_XORED_MEX_QUERY
#define SUISEN_RANGE_XORED_MEX_QUERY

#include <cassert>
#include <array>
#include <type_traits>
#include <limits>

#include "library/datastructure/bit_vector.hpp"

namespace suisen {
    template <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>
    struct RangeXoredMexQuery {
        // default constructor
        RangeXoredMexQuery() noexcept : n(0) {}
        // builds WaveletMatrix from vector
        template <typename U, std::enable_if_t<std::is_constructible_v<T, U>, std::nullptr_t> = nullptr>
        RangeXoredMexQuery(const std::vector<U>& a) { build(a); }

        // builds WaveletMatrix from generating function typed as (int) -> T
        template <typename U, std::enable_if_t<std::is_constructible_v<T, U>, std::nullptr_t> = nullptr>
        void build(const std::vector<U> &dat) {
            n = dat.size();
            std::vector<T> a(n), l(n), r(n);
            for (int i = 0; i < n; ++i) a[i] = dat[i];

            int floor_log2 = 0;
            while (1 << (floor_log2 + 1) <= n) ++floor_log2;
            std::vector<int> cnt(1 << floor_log2, 0);
            int dcnt = 0;

            auto calc_min_r = [&, this](int log) {
                min_r[log].assign(n + 1, n + 1);
                if (log > floor_log2) return;
                const int mask = (1 << log) - 1;
                for (int l = 0, r = 0; l < n;) {
                    while (r < n and dcnt != 1 << log) dcnt += ++cnt[a[r++] & mask] == 1;
                    if (dcnt == 1 << log) min_r[log][l] = r;
                    dcnt -= --cnt[a[l++] & mask] == 0;
                }
            };

            calc_min_r(bit_num);
            for (int log = bit_num - 1; log >= 0; --log) {
                bv[log] = BitVector(n, [&a, log](int i) -> bool { return (a[i] >> log) & 1; });
                int li = 0, ri = 0;
                for (int i = 0; i < n; ++i) {
                    ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];
                }
                a.swap(l);
                std::copy(r.begin(), r.begin() + ri, a.begin() + li);
                mid[log] = li;
                calc_min_r(log);
            }
        }

        // returns mex { A_i ^ x | l <= i < r }
        T minimum_excluded(int l, int r, T x) const {
            if (x >> bit_num) return 0;
            if (min_r[bit_num][l] <= r) return T(1) << bit_num;
            T res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                bool z = (x >> log) & 1;
                auto [zl, zr] = succ(l, r, z, log);
                if (min_r[log][zl] <= zr) {
                    std::tie(l, r) = succ(l, r, not z, log);
                    res |= T(1) << log;
                } else {
                    l = zl, r = zr;
                }
            }
            return res;
        }

    private:
        static_assert(bit_num > 0);

        int n;
        std::array<BitVector, bit_num> bv;
        std::array<int, bit_num> mid;
        std::array<std::vector<int>, bit_num + 1> min_r;

        std::pair<int, int> succ(int l, int r, const bool b, const int log) const {
            return std::make_pair(b * mid[log] + bv[log].rank(b, l), b * mid[log] + bv[log].rank(b, r));
        }
    };
} // namespace suisen

#endif // SUISEN_RANGE_XORED_MEX_QUERY
