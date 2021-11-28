#ifndef SUISEN_POW_MOD
#define SUISEN_POW_MOD

#include <vector>

namespace suisen {
    template <int base_as_int, typename mint>
    struct static_pow_mods {
        static_pow_mods() {}
        static_pow_mods(int n) { ensure(n); }
        const mint& operator[](int i) const {
            ensure(i);
            return pows[i];
        }
        static void ensure(int n) {
            int sz = pows.size();
            if (sz > n) return;
            pows.resize(n + 1);
            for (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];
        }
    private:
        static inline std::vector<mint> pows { 1 };
        static inline mint base = base_as_int;
        static constexpr int mod = mint::mod();
    };

    template <typename mint>
    struct pow_mods {
        pow_mods() {}
        pow_mods(mint base, int n) : base(base) { ensure(n); }
        const mint& operator[](int i) const {
            ensure(i);
            return pows[i];
        }
        void ensure(int n) const {
            int sz = pows.size();
            if (sz > n) return;
            pows.resize(n + 1);
            for (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];
        }
    private:
        mutable std::vector<mint> pows { 1 };
        mint base;
        static constexpr int mod = mint::mod();
    };
}

#endif // SUISEN_POW_MOD
