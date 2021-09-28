#ifndef SUISEN_KRONECKER_POWER
#define SUISEN_KRONECKER_POWER

#include <cassert>
#include <vector>

#include "library/util/default_operator.hpp"

namespace suisen {
    namespace kronecker_power_transform {
        namespace internal {
            template <typename UnitTransform, typename ReferenceGetter, std::size_t... Seq>
            void unit_transform(UnitTransform transform, ReferenceGetter ref_getter, std::index_sequence<Seq...>) {
                transform(ref_getter(Seq)...);
            }
        }

        template <typename T, std::size_t D, auto unit_transform>
        void kronecker_power_transform(std::vector<T> &x) {
            const std::size_t n = x.size();
            for (std::size_t block = 1; block < n; block *= D) {
                for (std::size_t l = 0; l < n; l += D * block) {
                    for (std::size_t offset = l; offset < l + block; ++offset) {
                        const auto ref_getter = [&](std::size_t i) -> T& { return x[offset + i * block]; };
                        internal::unit_transform(unit_transform, ref_getter, std::make_index_sequence<D>());
                    }
                }
            }
        }

        template <typename T, typename UnitTransform>
        void kronecker_power_transform(std::vector<T> &x, const std::size_t D, UnitTransform unit_transform) {
            const std::size_t n = x.size();
            std::vector<T> work(D);
            for (std::size_t block = 1; block < n; block *= D) {
                for (std::size_t l = 0; l < n; l += D * block) {
                    for (std::size_t offset = l; offset < l + block; ++offset) {
                        for (std::size_t i = 0; i < D; ++i) work[i] = x[offset + i * block];
                        unit_transform(work);
                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block] = work[i];
                    }
                }
            }
        }

        template <typename T, auto e = default_operator::zero<T>, auto add = default_operator::add<T>, auto mul = default_operator::mul<T>>
        auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>> &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(), std::declval<T>()), void()) {
            const std::size_t D = A.size();
            assert(D == A[0].size());
            auto unit_transform = [&](std::vector<T> &x) {
                std::vector<T> y(D, e());
                for (std::size_t i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {
                    y[i] = add(y[i], mul(A[i][j], x[j]));
                }
                x.swap(y);
            };
            kronecker_power_transform<T>(x, D, unit_transform);
        }
    }
} // namespace suisen


#endif // SUISEN_KRONECKER_POWER
