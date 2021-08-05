#ifndef SUISEN_CONVOLUTION
#define SUISEN_CONVOLUTION

#include <vector>

namespace suisen {

template <typename T, template <typename> class Transform>
struct Convolution {
    static std::vector<T> convolution(std::vector<T> a, std::vector<T> b) {
        const int n = a.size();
        assert(n == int(b.size()));
        Transform<T>::transform(a);
        Transform<T>::transform(b);
        for (int i = 0; i < n; ++i) a[i] *= b[i];
        Transform<T>::inverse_transform(a);
        return a;
    }
    static std::vector<T> convolution(std::vector<std::vector<T>> a) {
        const int num = a.size();
        if (num == 0) return {};
        const int n = a[0].size();
        for (auto &v : a) {
            assert(n == int(v.size()));
            Transform<T>::transform(v);
        }
        auto &res = a[0];
        for (int i = 1; i < num; ++i) {
            for (int j = 0; j < n; ++j) res[j] *= a[i][j];
        }
        Transform<T>::inverse_transform(res);
        return res;
    }
};

} // namespace suisen


#endif // SUISEN_CONVOLUTION
