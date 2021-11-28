#ifndef SUISEN_WAVELET_MATRIX
#define SUISEN_WAVELET_MATRIX

#include <cassert>
#include <array>
#include <type_traits>
#include <limits>

#include "library/datastructure/bit_vector.hpp"

namespace suisen {
template <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>
class WaveletMatrix {
    public:
        // default constructor
        WaveletMatrix() noexcept : n(0) {}
        // builds WaveletMatrix from generating function typed as (int) -> T
        template <typename Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>> = nullptr>
        WaveletMatrix(int n, Gen generator) : n(n) {
            build(generator);
        }
        // builds WaveletMatrix from vector
        template <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>
        WaveletMatrix(const std::vector<U> &a) : WaveletMatrix(a.size(), [&a](int i) { return T(a[i]); }) {}

        // builds WaveletMatrix from generating function typed as (int) -> T
        template <typename Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>>  = nullptr>
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
        inline T access(int i) const {
            return (*this)[i];
        }
        // returns the number of `val` in WaveletMatrix[0, i).
        int rank(T val, int i) const {
            check_value_bounds(val);
            int l = 0, r = i;
            for (int log = bit_num - 1; log >= 0; --log) succ(l, r, (val >> log) & 1, log);
            return r - l;
        }
        // returns the k'th smallest value in WaveletMatrix[l, r) (k : 0-indexed)
        T range_kth_smallest(int l, int r, int k, T default_value = T(-1)) const {
            if (k < 0 or k >= r - l) return default_value;
            T res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                int cnt_0 = bv[log].rank(false, l, r);
                bool bit = k >= cnt_0;
                succ(l, r, bit, log);
                res |= T(bit) << log;
                k -= bit * cnt_0;
            }
            return res;
        }
        // returns the k'th largest value in WaveletMatrix[l, r) (k : 0-indexed)
        inline T range_kth_largest(int l, int r, int k, T default_value = T(-1)) const {
            return range_kth_smallest(l, r, r - l - 1 - k, default_value);
        }
        // returns the minimum value in WaveletMatrix[l, r)
        inline T range_min(int l, int r) const {
            assert(l < r);
            return range_kth_smallest(l, r, 0);
        }
        // returns the maximum value in WaveletMatrix[l, r)
        inline T range_max(int l, int r) const {
            assert(l < r);
            return range_kth_largest(l, r, 0);
        }
        // returns the number of v in WaveletMatrix[l, r) s.t. v < upper
        int range_freq(int l, int r, T upper) const {
            if (r <= l) return 0;
            check_value_bounds(upper);
            int res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                bool b = (upper >> log) & 1;
                if (b) res += bv[log].rank(false, l, r);
                succ(l, r, b, log);
            }
            return res;
        }
        // returns the number of v in WaveletMatrix[l, r) s.t. lower <= v < upper
        inline int range_freq(int l, int r, T lower, T upper) const {
            if (lower >= upper) return 0;
            return range_freq(l, r, upper) - range_freq(l, r, lower);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower <= v
        inline T range_min_geq(int l, int r, T lower, T default_value = T(-1)) const {
            int cnt = range_freq(l, r, lower);
            return cnt >= r - l ? default_value : range_kth_smallest(l, r, cnt);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower < v
        inline T range_min_gt(int l, int r, T lower, T default_value = T(-1)) const {
            return lower == MAX ? default_value : range_min_geq(l, r, lower + 1);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper
        inline T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const {
            int cnt = range_freq(l, r, upper);
            return cnt == 0 ? default_value : range_kth_smallest(l, r, cnt - 1);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v <= upper
        inline T range_max_leq(int l, int r, T upper, T default_value = T(-1)) const {
            if (r >= l) return default_value;
            return upper == MAX ? range_max(l, r) : range_max_lt(l, r, upper + 1);
        }
    protected:
        WaveletMatrix(int n) noexcept : n(n) {}
    private:
        static_assert(bit_num > 0);
        static constexpr T MAX = bit_num == std::numeric_limits<T>::digits ? std::numeric_limits<T>::max() : (T(1) << bit_num) - 1;

        int n;
        std::array<BitVector, bit_num> bv;
        std::array<int, bit_num> mid;

        inline void succ(int &l, int &r, const bool b, const int log) const {
            l = b * mid[log] + bv[log].rank(b, l);
            r = b * mid[log] + bv[log].rank(b, r);
        }

        static constexpr void check_value_bounds(T val) {
            assert((val >> bit_num) == 0);
        }
};


} // namespace suisen

#endif // SUISEN_WAVELET_MATRIX
