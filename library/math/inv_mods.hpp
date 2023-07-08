#ifndef SUISEN_INV_MOD
#define SUISEN_INV_MOD

#include <vector>

namespace suisen {
    template <typename mint>
    class inv_mods {
    public:
        inv_mods() = default;
        inv_mods(int n) { ensure(n); }
        const mint& operator[](int i) const {
            ensure(i);
            return invs[i];
        }
        static void ensure(int n) {
            int sz = invs.size();
            if (sz < 2) invs = { 0, 1 }, sz = 2;
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

    template <typename mint>
    std::vector<mint> get_invs(const std::vector<mint>& vs) {
        const int n = vs.size();

        mint p = 1;
        for (auto& e : vs) {
            p *= e;
            assert(e != 0);
        }
        mint ip = p.inv();

        std::vector<mint> rp(n + 1);
        rp[n] = 1;
        for (int i = n - 1; i >= 0; --i) {
            rp[i] = rp[i + 1] * vs[i];
        }
        std::vector<mint> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = ip * rp[i + 1];
            ip *= vs[i];
        }
        return res;
    }
}

#endif // SUISEN_INV_MOD
