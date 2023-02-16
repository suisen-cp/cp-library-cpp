#ifndef SUISEN_KRONECKER_TRANSFORM
#define SUISEN_KRONECKER_TRANSFORM

#include <cassert>
#include <type_traits>
#include <vector>

#include "library/util/step_view.hpp"
#include "library/util/default_operator.hpp"

namespace suisen::kronecker_transform {
    namespace internal {
        int log(int d, int n) {
            int l = 0, p = 1;
            while (p < n) p *= d, ++l;
            assert(p == n);
            return l;
        }
    }
    // trans: (dimension id, std::vector<T>&) -> void
    template <typename T, typename Transform, std::enable_if_t<std::is_invocable_v<Transform, int, StepView<std::vector<T>>>, std::nullptr_t> = nullptr>
    void transform(std::vector<T>& f, const std::vector<int>& dims, const Transform& trans) {
        const int n = f.size(), m = dims.size();
        {
            int p = 1;
            for (int d : dims) p *= d;
            assert(p == n);
        }
        for (int i = 0, block = 1; i < m; ++i) {
            const int next_block = block * dims[i];
            for (int l = 0; l < n; l += next_block) {
                for (int offset = l; offset < l + block; ++offset) {
                    trans(i, StepView{ f, offset, block, dims[i] });
                }
            }
            block = next_block;
        }
    }
    // trans: (std::vector<T>&) -> void
    template <typename T, typename Transform, std::enable_if_t<std::is_invocable_v<Transform, StepView<std::vector<T>>>, std::nullptr_t> = nullptr>
    void transform(std::vector<T>& f, int d, const Transform& trans) {
        transform(f, std::vector<int>(internal::log(d, f.size()), d), [&trans](int, StepView<std::vector<T>> view) { trans(view); });
    }

    template <typename T, auto add = default_operator::add<T>>
    void sub_zeta(std::vector<T>& f, const std::vector<int>& dims) {
        transform(
            f, dims, [&](int, const StepView<std::vector<T>>& f) {
                for (size_t i = 1; i < f.size(); ++i) f[i] = add(f[i], f[i - 1]);
            }
        );
    }
    template <typename T, auto add = default_operator::add<T>>
    void sub_zeta(std::vector<T>& f, int d) {
        sub_zeta<T, add>(f, std::vector<int>(internal::log(d, f.size()), d));
    }
    template <typename T, auto sub = default_operator::sub<T>>
    void sub_mobius(std::vector<T>& f, const std::vector<int>& dims) {
        transform(
            f, dims,
            [&](int, const StepView<std::vector<T>>& f) {
                for (size_t i = f.size() - 1; i > 0; --i) f[i] = sub(f[i], f[i - 1]);
            }
        );
    }
    template <typename T, auto sub = default_operator::sub<T>>
    void sub_mobius(std::vector<T>& f, int d) {
        sub_mobius<T, sub>(f, std::vector<int>(internal::log(d, f.size()), d));
    }

    template <typename T, auto add = default_operator::add<T>>
    void sup_zeta(std::vector<T>& f, const std::vector<int>& dims) {
        transform(
            f, dims,
            [&](int, const StepView<std::vector<T>>& f) {
                for (size_t i = f.size() - 1; i > 0; --i) f[i - 1] = add(f[i - 1], f[i]);
            }
        );
    }
    template <typename T, auto add = default_operator::add<T>>
    void sup_zeta(std::vector<T>& f, int d) {
        sup_zeta<T, add>(f, std::vector<int>(internal::log(d, f.size()), d));
    }
    template <typename T, auto sub = default_operator::sub<T>>
    void sup_mobius(std::vector<T>& f, const std::vector<int>& dims) {
        transform(
            f, dims,
            [&](int, const StepView<std::vector<T>>& f) {
                for (size_t i = 1; i < f.size(); ++i) f[i - 1] = sub(f[i - 1], f[i]);
            }
        );
    }
    template <typename T, auto sub = default_operator::sub<T>>
    void sup_mobius(std::vector<T>& f, int d) {
        sup_mobius<T, sub>(f, std::vector<int>(internal::log(d, f.size()), d));
    }
} // namespace suisen::kronecker_transform


#endif // SUISEN_KRONECKER_TRANSFORM
