#ifndef SUISEN_SUPSET_TRANSFORM
#define SUISEN_SUPSET_TRANSFORM

#include <cassert>
#include <vector>

namespace suisen {

namespace supset_transform {

namespace internal {

template <typename T, typename AssignOp>
void transform(std::vector<T> &f, AssignOp assign_op) {
    const int n = f.size();
    assert((-n & n) == n);
    for (int k = 1; k < n; k <<= 1) {
        for (int l = 0; l < n; l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) assign_op(f[l + p], f[m + p]);
        }
    }
}

} // namespace internal

template <typename T, typename AddAssign>
void zeta(std::vector<T> &f, AddAssign add_assign) {
    internal::transform(f, add_assign);
}
template <typename T, typename SubAssign>
void mobius(std::vector<T> &f, SubAssign sub_assign) {
    internal::transform(f, sub_assign);
}
template <typename T>
void zeta(std::vector<T> &f) {
    internal::transform(f, [](T &a, const T &b) { a += b; });
}
template <typename T>
void mobius(std::vector<T> &f) {
    internal::transform(f, [](T &a, const T &b) { a -= b; });
}

} // namespace supset_transform

template <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>
struct SupsetTransformGeneral {
    static void transform(std::vector<T> &a) {
        supset_transform::zeta(a, add_assign);
    }
    static void inverse_transform(std::vector<T> &a) {
        supset_transform::mobius(a, sub_assign);
    }
};

template <typename T>
struct SupsetTransform {
    static void transform(std::vector<T> &a) {
        supset_transform::zeta(a);
    }
    static void inverse_transform(std::vector<T> &a) {
        supset_transform::mobius(a);
    }
};

} // namespace suisen


#endif // SUISEN_SUPSET_TRANSFORM
