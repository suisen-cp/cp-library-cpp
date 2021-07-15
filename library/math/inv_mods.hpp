#ifndef SUISEN_INV_MOD
#define SUISEN_INV_MOD

#include <vector>

namespace suisen {
template <typename mint>
class inv_mods {
    public:
        inv_mods() {}
        inv_mods(int n) { ensure(n); }
        const mint& operator[](int i) const {
            ensure(i);
            return invs[i];
        }
        static void ensure(int n) {
            int sz = invs.size();
            if (sz < 2) invs = {0, 1}, sz = 2;
            if (sz < n + 1) {
                invs.resize(n + 1);
                for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];
            }
        }
    private:
        static std::vector<mint> invs;
        static constexpr int mod = mint::mod();
};
template <typename mint>
std::vector<mint> inv_mods<mint>::invs{};
}

#endif
