#ifndef SUISEN_CONVOLUTION
#define SUISEN_CONVOLUTION

#include <cassert>
#include <vector>

#include "library/util/default_operator.hpp"

namespace suisen {
    namespace convolution {
        template <typename T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>
        std::vector<T> transform_convolution(std::vector<T> a, std::vector<T> b) {
            const std::size_t n = a.size(), m = b.size();
            assert(n == m);
            transform(a), transform(b);
            for (std::size_t i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);
            inv_transform(a);
            return a;
        }
        template <typename T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>
        std::vector<T> transform_convolution(std::vector<std::vector<T>> a) {
            const std::size_t num = a.size();
            assert(num);
            const std::size_t n = a[0].size();
            for (auto &v : a) {
                assert(n == int(v.size()));
                transform(v);
            }
            auto &res = a[0];
            for (int i = 1; i < num; ++i) {
                for (int j = 0; j < n; ++j) res[j] = mul(res[j], a[i][j]);
            }
            inv_transform(res);
            return res;
        }
    }
} // namespace suisen


#endif // SUISEN_CONVOLUTION
