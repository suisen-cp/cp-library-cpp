#ifndef SUISEN_WAVELET_MATRIX
#define SUISEN_WAVELET_MATRIX

#include <cassert>
#include <array>
#include <type_traits>
#include <limits>

#include "library/datastructure/bit_vector.hpp"

namespace suisen {
    template <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>
    struct WaveletMatrix {
        // default constructor
        WaveletMatrix() noexcept : n(0) {}
        // builds WaveletMatrix from generating function typed as (int) -> T
        template <typename Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>
        WaveletMatrix(int n, Gen generator) : n(n) {
            build(generator);
        }
        // builds WaveletMatrix from vector
        template <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>
        WaveletMatrix(const std::vector<U>& a) : WaveletMatrix(a.size(), [&a](int i) { return T(a[i]); }) {}

        // builds WaveletMatrix from generating function typed as (int) -> T
        template <typename Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>
        void build(Gen generator) {
            std::vector<T> a(n), l(n), r(n);
            for (int i = 0; i < n; ++i) a[i] = generator(i);
            for (int log = bit_num - 1; log >= 0; --log) {
                bv[log] = BitVector(n, [&a, log](int i) -> bool { return (a[i] >> log) & 1; });
                int li = 0, ri = 0;
                for (int i = 0; i < n; ++i) {
                    ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];
                }
                a.swap(l);
                std::copy(r.begin(), r.begin() + ri, a.begin() + li);
                mid[log] = li;
            }
        }

        // returns WaveletMatrix[i]
        T operator[](int i) const {
            T res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                bool b = bv[log][i];
                res |= T(b) << log;
                i = b * mid[log] + bv[log].rank(b, i);
            }
            return res;
        }
        // returns WaveletMatrix[i]
        T access(int i) const {
            return (*this)[i];
        }

        // returns the number of `val` in WaveletMatrix[0, i).
        int rank(T val, int i) const {
            check_value_bounds(val);
            int l = 0, r = i;
            for (int log = bit_num - 1; log >= 0; --log) succ(l, r, (val >> log) & 1, log);
            return r - l;
        }

        // returns the k'th smallest value in the multiset {| x ^ WaveletMatrix[i] : i in [l, r) |} (k : 0-indexed)
        T range_xor_kth_smallest(int l, int r, int k, T x, T default_value = T(-1)) const {
            if (k < 0 or k >= r - l) return default_value;
            T res = 0;
            check_value_bounds(x);
            for (int log = bit_num - 1; log >= 0; --log) {
                bool z = (x >> log) & 1;
                int cnt_z = bv[log].rank(z, l, r);
                bool skip_z = k >= cnt_z, bit = z ^ skip_z;
                succ(l, r, bit, log);
                res |= T(bit) << log;
                k -= skip_z * cnt_z;
            }
            return res;
        }
        // returns the k'th largest value in the multiset {| x ^ WaveletMatrix[i] : i in [l, r) |} (k : 0-indexed)
        T range_xor_kth_largest(int l, int r, int k, T x, T default_value = T(-1)) const {
            return range_xor_kth_smallest(l, r, r - l - 1 - k, x, default_value);
        }
        // returns the minimum value in the set { x ^ WaveletMatrix[i] : i in [l, r) }
        T range_xor_min(int l, int r, T x) const {
            assert(l < r);
            return range_xor_kth_smallest(l, r, 0, x);
        }
        // returns the maximum value in the set { x ^ WaveletMatrix[i] : i in [l, r) }
        T range_xor_max(int l, int r, T x) const {
            assert(l < r);
            return range_xor_kth_largest(l, r, 0, x);
        }

        // returns the number of v in WaveletMatrix[l, r) s.t. v ^ x < upper
        int range_xor_freq(int l, int r, T x, T upper) const {
            if (r <= l) return 0;
            if (upper > MAX) return r - l;
            check_value_bounds(x);
            int res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                bool z = (x >> log) & 1, u = (upper >> log) & 1;
                if (u) res += bv[log].rank(z, l, r);
                succ(l, r, z ^ u, log);
            }
            return res;
        }
        // returns the number of v in WaveletMatrix[l, r) s.t. lower <= x ^ v < upper
        int range_xor_freq(int l, int r, T x, T lower, T upper) const {
            if (lower >= upper) return 0;
            return range_xor_freq(l, r, x, upper) - range_xor_freq(l, r, x, lower);
        }

        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower <= x ^ v
        T range_xor_min_geq(int l, int r, T x, T lower, T default_value = T(-1)) const {
            int cnt = range_xor_freq(l, r, x, lower);
            return cnt >= r - l ? default_value : range_xor_kth_smallest(l, r, cnt, x);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower < x ^ v
        T range_xor_min_gt(int l, int r, T x, T lower, T default_value = T(-1)) const {
            return lower == MAX ? default_value : range_xor_min_geq(l, r, x, lower + 1, default_value);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. x ^ v < upper
        T range_xor_max_lt(int l, int r, T x, T upper, T default_value = T(-1)) const {
            int cnt = range_xor_freq(l, r, x, upper);
            return cnt == 0 ? default_value : range_xor_kth_smallest(l, r, cnt - 1, x, default_value);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. x ^ v <= upper
        T range_xor_max_leq(int l, int r, T x, T upper, T default_value = T(-1)) const {
            if (l >= r) return default_value;
            return upper == MAX ? range_xor_max(l, r, x) : range_xor_max_lt(l, r, x, upper + 1, default_value);
        }

        // returns the k'th smallest value in WaveletMatrix[l, r) (k : 0-indexed)
        T range_kth_smallest(int l, int r, int k, T default_value = T(-1)) const { return range_xor_kth_smallest(l, r, k, 0, default_value); }
        // returns the k'th largest value in WaveletMatrix[l, r) (k : 0-indexed)
        T range_kth_largest(int l, int r, int k, T default_value = T(-1)) const { return range_xor_kth_largest(l, r, k, 0, default_value); }
        // returns the minimum value in WaveletMatrix[l, r)
        T range_min(int l, int r) const { return range_xor_min(l, r, 0); }
        // returns the maximum value in WaveletMatrix[l, r)
        T range_max(int l, int r) const { return range_xor_max(l, r, 0); }

        // returns the number of v in WaveletMatrix[l, r) s.t. v < upper
        int range_freq(int l, int r, T upper) const { return range_xor_freq(l, r, 0, upper); }
        // returns the number of v in WaveletMatrix[l, r) s.t. lower <= v < upper
        int range_freq(int l, int r, T lower, T upper) const { return range_xor_freq(l, r, 0, lower, upper); }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower <= v
        T range_min_geq(int l, int r, T lower, T default_value = T(-1)) const { return range_xor_min_geq(l, r, 0, lower, default_value); }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower < v
        T range_min_gt(int l, int r, T lower, T default_value = T(-1)) const { return range_xor_min_gt(l, r, 0, lower, default_value); }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper
        T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const { return range_xor_max_lt(l, r, 0, upper, default_value); }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v <= upper
        T range_max_leq(int l, int r, T upper, T default_value = T(-1)) const { return range_xor_max_leq(l, r, 0, upper, default_value); }
    protected:
        WaveletMatrix(int n) noexcept : n(n) {}
    private:
        static_assert(bit_num > 0);
        static constexpr T MAX = bit_num == std::numeric_limits<T>::digits ? std::numeric_limits<T>::max() : (T(1) << bit_num) - 1;

        int n;
        std::array<BitVector, bit_num> bv;
        std::array<int, bit_num> mid;

        void succ(int& l, int& r, const bool b, const int log) const {
            l = b * mid[log] + bv[log].rank(b, l);
            r = b * mid[log] + bv[log].rank(b, r);
        }

        static void check_value_bounds(T val) {
            assert((val >> bit_num) == 0);
        }
    };
} // namespace suisen

#endif // SUISEN_WAVELET_MATRIX
