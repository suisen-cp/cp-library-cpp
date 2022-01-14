#ifndef SUISEN_MULTIVARIATE_CONVOLUTION
#define SUISEN_MULTIVARIATE_CONVOLUTION

#include <numeric>
#include <atcoder/convolution>

#include "library/util/default_operator.hpp"

namespace suisen {
    struct multi_variate_convolution {
        multi_variate_convolution() : multi_variate_convolution(std::vector<int>{}) {}
        multi_variate_convolution(const std::vector<int> &dim) : _n(std::accumulate(dim.begin(), dim.end(), 1, std::multiplies<int>())), _k(dim.size()), _m(2 * ceil_pow2(_n)), _chi(_n, 0) {
            for (int i = 0; i < _n; ++i) {
                int den = 1;
                for (int e : dim) den *= e, _chi[i] += i / den;
                if (_k) _chi[i] %= _k;
            }
        }

        int size() const { return _n; }
        int dim_num() const { return _k; }

        template <typename T, typename Inverse = decltype(default_operator::inv<T>)>
        std::vector<T> convolution(std::vector<T> f, std::vector<T> g, Inverse inv = default_operator::inv<T>) const {
            assert(int(f.size()) == _n and int(g.size()) == _n);
            if (_k == 0) return { f[0] * g[0] };
            auto rf = ranked(f), rg = ranked(g);
            for (auto &v : rf) atcoder::internal::butterfly(v);
            for (auto &v : rg) atcoder::internal::butterfly(v);
            std::vector rh(_k, std::vector<T>(_m, T{}));
            for (int i = 0; i < _k; ++i) for (int j = 0; j < _k; ++j) {
                int r = i + j < _k ? i + j : i + j - _k;
                for (int p = 0; p < _m; ++p) rh[r][p] += rf[i][p] * rg[j][p];
            }
            for (auto &v : rh) atcoder::internal::butterfly_inv(v);
            const T isz = inv(T(_m));
            std::vector<T> h(_n);
            for (int i = 0; i < _n; ++i) h[i] = rh[_chi[i]][i] * isz;
            return h;
        }

        template <typename T>
        std::vector<T> operator()(std::vector<T> f, std::vector<T> g) const {
            return convolution(f, g);
        }

    private:
        int _n, _k, _m;
        std::vector<int> _chi;

        static constexpr int ceil_pow2(int m) {
            int res = 1;
            while (res < m) res *= 2;
            return res;
        }

        template <typename T>
        auto ranked(const std::vector<T> &f) const {
            std::vector rf(_k, std::vector<T>(_m, T{}));
            for (int i = 0; i < _n; ++i) rf[_chi[i]][i] = f[i];
            return rf;
        }
    };
} // namespace suisen


#endif // SUISEN_MULTIVARIATE_CONVOLUTION
