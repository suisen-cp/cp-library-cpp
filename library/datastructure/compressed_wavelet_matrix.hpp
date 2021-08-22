#ifndef SUISEN_COMP_WAVELET_MATRIX
#define SUISEN_COMP_WAVELET_MATRIX

#include <cassert>
#include <array>
#include <type_traits>
#include <limits>

#include "library/datastructure/wavelet_matrix.hpp"
#include "library/util/coordinate_compressor.hpp"

namespace suisen {
template <typename T, int log_max_len = std::numeric_limits<std::make_unsigned_t<T>>::digits>
class CompressedWaveletMatrix : public WaveletMatrix<int, log_max_len> {
    public:
        // default constructor
        CompressedWaveletMatrix() noexcept : WaveletMatrix<int, log_max_len>(0) {}
        // builds WaveletMatrix from generating function typed as (int) -> T
        template <typename Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>> = nullptr>
        CompressedWaveletMatrix(int n, Gen generator) : WaveletMatrix<int, log_max_len>(n), comp(CoordinateCompressorBuilder<T>::build(n, generator)) {
            this->build([this, &generator](int i) { return comp[generator(i)]; });
        }
        // builds WaveletMatrix from vector
        template <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>
        CompressedWaveletMatrix(const std::vector<U> &a) : CompressedWaveletMatrix(a.size(), [&a](int i) { return T(a[i]); }) {}

        // returns WaveletMatrix[i]
        inline T operator[](int i) const {
            return comp.decomp(WaveletMatrix<int, log_max_len>::operator[](i));
        }
        // returns WaveletMatrix[i]
        inline T access(int i) const {
            return (*this)[i];
        }
        // returns the number of `val` in WaveletMatrix[0, i).
        inline int rank(T val, int i) const {
            int x = comp.comp(val, -1);
            if (x == -1) return 0; 
            return WaveletMatrix<int, log_max_len>::rank(x, i);
        }
        // returns the k'th smallest value in WaveletMatrix[l, r) (k : 0-indexed)
        inline T range_kth_smallest(int l, int r, int k, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_kth_smallest(l, r, k, -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        // returns the k'th largest value in WaveletMatrix[l, r) (k : 0-indexed)
        inline T range_kth_largest(int l, int r, int k, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_kth_largest(l, r, k, -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        // returns the minimum value in WaveletMatrix[l, r)
        inline T range_min(int l, int r) const {
            return comp.decomp(WaveletMatrix<int, log_max_len>::range_min(l, r));
        }
        // returns the maximum value in WaveletMatrix[l, r)
        inline T range_max(int l, int r) const {
            return comp.decomp(WaveletMatrix<int, log_max_len>::range_max(l, r));
        }
        // returns the number of v in WaveletMatrix[l, r) s.t. v < upper
        inline int range_freq(int l, int r, T upper) const {
            return WaveletMatrix<int, log_max_len>::range_freq(l, r, comp.min_geq_index(upper));
        }
        // returns the number of v in WaveletMatrix[l, r) s.t. lower <= v < upper
        inline int range_freq(int l, int r, T lower, T upper) const {
            if (lower >= upper) return 0;
            return range_freq(l, r, upper) - range_freq(l, r, lower);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower <= v
        inline T range_min_geq(int l, int r, T lower, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_min_geq(l, r, comp.min_geq_index(lower), -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower < v
        inline T range_min_gt(int l, int r, T lower, T default_value = T(-1)) const {
            return lower == std::numeric_limits<T>::max() ? default_value : range_min_geq(l, r, lower + 1, default_value);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper
        inline T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_max_lt(l, r, comp.min_geq_index(upper), -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v <= upper
        inline T range_max_leq(int l, int r, T upper, T default_value = T(-1)) const {
            if (r >= l) return default_value;
            return upper == std::numeric_limits<T>::max() ? range_max(l, r) : range_max_lt(l, r, upper + 1, default_value);
        }
    private:
        typename CoordinateCompressorBuilder<T>::Compressor comp;
};
} // namespace suisen


#endif // SUISEN_COMP_WAVELET_MATRIX
