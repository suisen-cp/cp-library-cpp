#ifndef SUISEN_MODINT_EXTENSION
#define SUISEN_MODINT_EXTENSION

#include <cassert>
#include <optional>

namespace suisen {
/**
 * refernce: https://37zigen.com/tonelli-shanks-algorithm/
 * calculates x s.t. x^2 = a mod p in O((log p)^2).
 */
template <typename mint>
std::optional<mint> optional_sqrt(mint a) {
    static int p = mint::mod();
    if (a == 0) return std::make_optional(0);
    if (p == 2) return std::make_optional(a);
    if (a.pow((p - 1) / 2) != 1) return std::nullopt;
    mint b = 1;
    while (b.pow((p - 1) / 2) == 1) ++b;
    static int tlz = __builtin_ctz(p - 1), q = (p - 1) >> tlz;
    mint x = a.pow((q + 1) / 2);
    b = b.pow(q);
    for (int shift = 2; x * x != a; ++shift) {
        mint e = a.inv() * x * x;
        if (e.pow(1 << (tlz - shift)) != 1) x *= b;
        b *= b;
    }
    return std::make_optional(x);
}

};

/**
 * calculates x s.t. x^2 = a mod p in O((log p)^2).
 * if not exists, raises runtime error.
 */
template <typename mint>
auto sqrt(mint a) -> decltype(mint::mod(), mint()) {
    return *suisen::optional_sqrt(a);
}
template <typename mint>
auto log(mint a) -> decltype(mint::mod(), mint())  {
    assert(a == 1);
    return 0;
}
template <typename mint>
auto exp(mint a) -> decltype(mint::mod(), mint())  {
    assert(a == 0);
    return 1;
}
template <typename mint, typename T>
auto pow(mint a, T b) -> decltype(mint::mod(), mint())  {
    return a.pow(b);
}
template <typename mint>
auto inv(mint a) -> decltype(mint::mod(), mint()) {
    return a.inv();
}

#endif // SUISEN_MODINT_EXTENSION
