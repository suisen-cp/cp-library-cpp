---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc245/tasks/abc245_d
    links:
    - https://atcoder.jp/contests/abc245/tasks/abc245_d
  bundledCode: "#line 1 \"test/src/polynomial/fps_naive/abc245_d.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc245/tasks/abc245_d\"\n\n#include <iostream>\n\
    #include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\n#line 1 \"\
    library/polynomial/fps_naive.hpp\"\n\n\n\n#include <cassert>\n#include <cmath>\n\
    #include <limits>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 7 \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\
    \    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 11 \"library/polynomial/fps_naive.hpp\"\n\n#line\
    \ 1 \"library/math/modint_extension.hpp\"\n\n\n\n#line 5 \"library/math/modint_extension.hpp\"\
    \n#include <optional>\n\n/**\n * refernce: https://37zigen.com/tonelli-shanks-algorithm/\n\
    \ * calculates x s.t. x^2 = a mod p in O((log p)^2).\n */\ntemplate <typename\
    \ mint>\nstd::optional<mint> safe_sqrt(mint a) {\n    static int p = mint::mod();\n\
    \    if (a == 0) return std::make_optional(0);\n    if (p == 2) return std::make_optional(a);\n\
    \    if (a.pow((p - 1) / 2) != 1) return std::nullopt;\n    mint b = 1;\n    while\
    \ (b.pow((p - 1) / 2) == 1) ++b;\n    static int tlz = __builtin_ctz(p - 1), q\
    \ = (p - 1) >> tlz;\n    mint x = a.pow((q + 1) / 2);\n    b = b.pow(q);\n   \
    \ for (int shift = 2; x * x != a; ++shift) {\n        mint e = a.inv() * x * x;\n\
    \        if (e.pow(1 << (tlz - shift)) != 1) x *= b;\n        b *= b;\n    }\n\
    \    return std::make_optional(x);\n}\n\n/**\n * calculates x s.t. x^2 = a mod\
    \ p in O((log p)^2).\n * if not exists, raises runtime error.\n */\ntemplate <typename\
    \ mint>\nauto sqrt(mint a) -> decltype(mint::mod(), mint()) {\n    return *safe_sqrt(a);\n\
    }\ntemplate <typename mint>\nauto log(mint a) -> decltype(mint::mod(), mint())\
    \ {\n    assert(a == 1);\n    return 0;\n}\ntemplate <typename mint>\nauto exp(mint\
    \ a) -> decltype(mint::mod(), mint()) {\n    assert(a == 0);\n    return 1;\n\
    }\ntemplate <typename mint, typename T>\nauto pow(mint a, T b) -> decltype(mint::mod(),\
    \ mint()) {\n    return a.pow(b);\n}\ntemplate <typename mint>\nauto inv(mint\
    \ a) -> decltype(mint::mod(), mint()) {\n    return a.inv();\n}\n\n\n#line 1 \"\
    library/math/inv_mods.hpp\"\n\n\n\n#line 5 \"library/math/inv_mods.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename mint>\n    class inv_mods {\n    public:\n\
    \        inv_mods() = default;\n        inv_mods(int n) { ensure(n); }\n     \
    \   const mint& operator[](int i) const {\n            ensure(i);\n          \
    \  return invs[i];\n        }\n        static void ensure(int n) {\n         \
    \   int sz = invs.size();\n            if (sz < 2) invs = { 0, 1 }, sz = 2;\n\
    \            if (sz < n + 1) {\n                invs.resize(n + 1);\n        \
    \        for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) * invs[mod\
    \ % i];\n            }\n        }\n    private:\n        static std::vector<mint>\
    \ invs;\n        static constexpr int mod = mint::mod();\n    };\n    template\
    \ <typename mint>\n    std::vector<mint> inv_mods<mint>::invs{};\n\n    template\
    \ <typename mint>\n    std::vector<mint> get_invs(const std::vector<mint>& vs)\
    \ {\n        const int n = vs.size();\n\n        mint p = 1;\n        for (auto&\
    \ e : vs) {\n            p *= e;\n            assert(e != 0);\n        }\n   \
    \     mint ip = p.inv();\n\n        std::vector<mint> rp(n + 1);\n        rp[n]\
    \ = 1;\n        for (int i = n - 1; i >= 0; --i) {\n            rp[i] = rp[i +\
    \ 1] * vs[i];\n        }\n        std::vector<mint> res(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            res[i] = ip * rp[i + 1];\n            ip *=\
    \ vs[i];\n        }\n        return res;\n    }\n}\n\n\n#line 14 \"library/polynomial/fps_naive.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct FPSNaive : std::vector<T>\
    \ {\n        static inline int MAX_SIZE = std::numeric_limits<int>::max() / 2;\n\
    \n        using value_type = T;\n        using element_type = rec_value_type_t<T>;\n\
    \        using std::vector<value_type>::vector;\n\n        FPSNaive(const std::initializer_list<value_type>\
    \ l) : std::vector<value_type>::vector(l) {}\n        FPSNaive(const std::vector<value_type>&\
    \ v) : std::vector<value_type>::vector(v) {}\n\n        static void set_max_size(int\
    \ n) {\n            FPSNaive<T>::MAX_SIZE = n;\n        }\n\n        const value_type\
    \ operator[](int n) const {\n            return n <= deg() ? unsafe_get(n) : value_type{\
    \ 0 };\n        }\n        value_type& operator[](int n) {\n            return\
    \ ensure_deg(n), unsafe_get(n);\n        }\n\n        int size() const {\n   \
    \         return std::vector<value_type>::size();\n        }\n        int deg()\
    \ const {\n            return size() - 1;\n        }\n        int normalize()\
    \ {\n            while (size() and this->back() == value_type{ 0 }) this->pop_back();\n\
    \            return deg();\n        }\n        FPSNaive& cut_inplace(int n) {\n\
    \            if (size() > n) this->resize(std::max(0, n));\n            return\
    \ *this;\n        }\n        FPSNaive cut(int n) const {\n            FPSNaive\
    \ f = FPSNaive(*this).cut_inplace(n);\n            return f;\n        }\n\n  \
    \      FPSNaive operator+() const {\n            return FPSNaive(*this);\n   \
    \     }\n        FPSNaive operator-() const {\n            FPSNaive f(*this);\n\
    \            for (auto& e : f) e = -e;\n            return f;\n        }\n   \
    \     FPSNaive& operator++() { return ++(*this)[0], * this; }\n        FPSNaive&\
    \ operator--() { return --(*this)[0], * this; }\n        FPSNaive& operator+=(const\
    \ value_type x) { return (*this)[0] += x, *this; }\n        FPSNaive& operator-=(const\
    \ value_type x) { return (*this)[0] -= x, *this; }\n        FPSNaive& operator+=(const\
    \ FPSNaive& g) {\n            ensure_deg(g.deg());\n            for (int i = 0;\
    \ i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);\n            return *this;\n\
    \        }\n        FPSNaive& operator-=(const FPSNaive& g) {\n            ensure_deg(g.deg());\n\
    \            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);\n\
    \            return *this;\n        }\n        FPSNaive& operator*=(const FPSNaive&\
    \ g) { return *this = *this * g; }\n        FPSNaive& operator*=(const value_type\
    \ x) {\n            for (auto& e : *this) e *= x;\n            return *this;\n\
    \        }\n        FPSNaive& operator/=(const FPSNaive& g) { return *this = *this\
    \ / g; }\n        FPSNaive& operator%=(const FPSNaive& g) { return *this = *this\
    \ % g; }\n        FPSNaive& operator<<=(const int shamt) {\n            this->insert(this->begin(),\
    \ shamt, value_type{ 0 });\n            return *this;\n        }\n        FPSNaive&\
    \ operator>>=(const int shamt) {\n            if (shamt > size()) this->clear();\n\
    \            else this->erase(this->begin(), this->begin() + shamt);\n       \
    \     return *this;\n        }\n\n        friend FPSNaive operator+(FPSNaive f,\
    \ const FPSNaive& g) { f += g; return f; }\n        friend FPSNaive operator+(FPSNaive\
    \ f, const value_type& x) { f += x; return f; }\n        friend FPSNaive operator-(FPSNaive\
    \ f, const FPSNaive& g) { f -= g; return f; }\n        friend FPSNaive operator-(FPSNaive\
    \ f, const value_type& x) { f -= x; return f; }\n        friend FPSNaive operator*(const\
    \ FPSNaive& f, const FPSNaive& g) {\n            if (f.empty() or g.empty()) return\
    \ FPSNaive{};\n            const int n = f.size(), m = g.size();\n           \
    \ FPSNaive h(std::min(MAX_SIZE, n + m - 1));\n            for (int i = 0; i <\
    \ n; ++i) for (int j = 0; j < m; ++j) {\n                if (i + j >= MAX_SIZE)\
    \ break;\n                h.unsafe_get(i + j) += f.unsafe_get(i) * g.unsafe_get(j);\n\
    \            }\n            return h;\n        }\n        friend FPSNaive operator*(FPSNaive\
    \ f, const value_type& x) { f *= x; return f; }\n        friend FPSNaive operator/(FPSNaive\
    \ f, const FPSNaive& g) { return std::move(f.div_mod(g).first); }\n        friend\
    \ FPSNaive operator%(FPSNaive f, const FPSNaive& g) { return std::move(f.div_mod(g).second);\
    \ }\n        friend FPSNaive operator*(const value_type x, FPSNaive f) { f *=\
    \ x; return f; }\n        friend FPSNaive operator<<(FPSNaive f, const int shamt)\
    \ { f <<= shamt; return f; }\n        friend FPSNaive operator>>(FPSNaive f, const\
    \ int shamt) { f >>= shamt; return f; }\n\n        std::pair<FPSNaive, FPSNaive>\
    \ div_mod(FPSNaive g) const {\n            FPSNaive f = *this;\n            const\
    \ int fd = f.normalize(), gd = g.normalize();\n            assert(gd >= 0);\n\
    \            if (fd < gd) return { FPSNaive{}, f };\n            if (gd == 0)\
    \ return { f *= g.unsafe_get(0).inv(), FPSNaive{} };\n            const int k\
    \ = f.deg() - gd;\n            value_type head_inv = g.unsafe_get(gd).inv();\n\
    \            FPSNaive q(k + 1);\n            for (int i = k; i >= 0; --i) {\n\
    \                value_type div = f.unsafe_get(i + gd) * head_inv;\n         \
    \       q.unsafe_get(i) = div;\n                for (int j = 0; j <= gd; ++j)\
    \ f.unsafe_get(i + j) -= div * g.unsafe_get(j);\n            }\n            f.cut_inplace(gd);\n\
    \            f.normalize();\n            return { q, f };\n        }\n\n     \
    \   friend bool operator==(const FPSNaive& f, const FPSNaive& g) {\n         \
    \   const int n = f.size(), m = g.size();\n            if (n < m) return g ==\
    \ f;\n            for (int i = 0; i < m; ++i) if (f.unsafe_get(i) != g.unsafe_get(i))\
    \ return false;\n            for (int i = m; i < n; ++i) if (f.unsafe_get(i) !=\
    \ 0) return false;\n            return true;\n        }\n        friend bool operator!=(const\
    \ FPSNaive& f, const FPSNaive& g) {\n            return not (f == g);\n      \
    \  }\n\n        FPSNaive mul(const FPSNaive& g, int n = -1) const {\n        \
    \    if (n < 0) n = size();\n            if (this->empty() or g.empty()) return\
    \ FPSNaive{};\n            const int m = size(), k = g.size();\n            FPSNaive\
    \ h(std::min(n, m + k - 1));\n            for (int i = 0; i < m; ++i) {\n    \
    \            for (int j = 0, jr = std::min(k, n - i); j < jr; ++j) {\n       \
    \             h.unsafe_get(i + j) += unsafe_get(i) * g.unsafe_get(j);\n      \
    \          }\n            }\n            return h;\n        }\n        FPSNaive\
    \ diff() const {\n            if (this->empty()) return {};\n            FPSNaive\
    \ g(size() - 1);\n            for (int i = 1; i <= deg(); ++i) g.unsafe_get(i\
    \ - 1) = unsafe_get(i) * i;\n            return g;\n        }\n        FPSNaive\
    \ intg() const {\n            const int n = size();\n            FPSNaive g(n\
    \ + 1);\n            for (int i = 0; i < n; ++i) g.unsafe_get(i + 1) = unsafe_get(i)\
    \ * invs[i + 1];\n            if (g.deg() > MAX_SIZE) g.cut_inplace(MAX_SIZE);\n\
    \            return g;\n        }\n        FPSNaive inv(int n = -1) const {\n\
    \            if (n < 0) n = size();\n            FPSNaive g(n);\n            const\
    \ value_type inv_f0 = ::inv(unsafe_get(0));\n            g.unsafe_get(0) = inv_f0;\n\
    \            for (int i = 1; i < n; ++i) {\n                for (int j = 1; j\
    \ <= i; ++j) g.unsafe_get(i) -= g.unsafe_get(i - j) * (*this)[j];\n          \
    \      g.unsafe_get(i) *= inv_f0;\n            }\n            return g;\n    \
    \    }\n        FPSNaive exp(int n = -1) const {\n            if (n < 0) n = size();\n\
    \            assert(unsafe_get(0) == value_type{ 0 });\n            FPSNaive g(n);\n\
    \            g.unsafe_get(0) = value_type{ 1 };\n            for (int i = 1; i\
    \ < n; ++i) {\n                for (int j = 1; j <= i; ++j) g.unsafe_get(i) +=\
    \ j * g.unsafe_get(i - j) * (*this)[j];\n                g.unsafe_get(i) *= invs[i];\n\
    \            }\n            return g;\n        }\n        FPSNaive log(int n =\
    \ -1) const {\n            if (n < 0) n = size();\n            assert(unsafe_get(0)\
    \ == value_type{ 1 });\n            FPSNaive g(n);\n            g.unsafe_get(0)\
    \ = value_type{ 0 };\n            for (int i = 1; i < n; ++i) {\n            \
    \    g.unsafe_get(i) = i * (*this)[i];\n                for (int j = 1; j < i;\
    \ ++j) g.unsafe_get(i) -= (i - j) * g.unsafe_get(i - j) * (*this)[j];\n      \
    \          g.unsafe_get(i) *= invs[i];\n            }\n            return g;\n\
    \        }\n        FPSNaive pow(const long long k, int n = -1) const {\n    \
    \        if (n < 0) n = size();\n            if (k == 0) {\n                FPSNaive\
    \ res(n);\n                res[0] = 1;\n                return res;\n        \
    \    }\n            int z = 0;\n            while (z < size() and unsafe_get(z)\
    \ == value_type{ 0 }) ++z;\n            if (z == size() or z > (n - 1) / k) return\
    \ FPSNaive(n, 0);\n            const int m = n - z * k;\n\n            FPSNaive\
    \ g(m);\n            const value_type inv_f0 = ::inv(unsafe_get(z));\n       \
    \     g.unsafe_get(0) = unsafe_get(z).pow(k);\n            for (int i = 1; i <\
    \ m; ++i) {\n                for (int j = 1; j <= i; ++j) g.unsafe_get(i) += (element_type{\
    \ k } *j - (i - j)) * g.unsafe_get(i - j) * (*this)[z + j];\n                g.unsafe_get(i)\
    \ *= inv_f0 * invs[i];\n            }\n            g <<= z * k;\n            return\
    \ g;\n        }\n\n        std::optional<FPSNaive> safe_sqrt(int n = -1) const\
    \ {\n            if (n < 0) n = size();\n            int dl = 0;\n           \
    \ while (dl < size() and unsafe_get(dl) == value_type{ 0 }) ++dl;\n          \
    \  if (dl == size()) return FPSNaive(n, 0);\n            if (dl & 1) return std::nullopt;\n\
    \n            const int m = n - dl / 2;\n\n            FPSNaive g(m);\n      \
    \      auto opt_g0 = ::safe_sqrt((*this)[dl]);\n            if (not opt_g0.has_value())\
    \ return std::nullopt;\n            g.unsafe_get(0) = *opt_g0;\n            value_type\
    \ inv_2g0 = ::inv(2 * g.unsafe_get(0));\n            for (int i = 1; i < m; ++i)\
    \ {\n                g.unsafe_get(i) = (*this)[dl + i];\n                for (int\
    \ j = 1; j < i; ++j) g.unsafe_get(i) -= g.unsafe_get(j) * g.unsafe_get(i - j);\n\
    \                g.unsafe_get(i) *= inv_2g0;\n            }\n            g <<=\
    \ dl / 2;\n            return g;\n        }\n        FPSNaive sqrt(int n = -1)\
    \ const {\n            if (n < 0) n = size();\n            return *safe_sqrt(n);\n\
    \        }\n\n        value_type eval(value_type x) const {\n            value_type\
    \ y = 0;\n            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);\n\
    \            return y;\n        }\n\n    private:\n        static inline inv_mods<element_type>\
    \ invs;\n\n        void ensure_deg(int d) {\n            if (deg() < d) this->resize(d\
    \ + 1, value_type{ 0 });\n        }\n        const value_type& unsafe_get(int\
    \ i) const {\n            return std::vector<value_type>::operator[](i);\n   \
    \     }\n        value_type& unsafe_get(int i) {\n            return std::vector<value_type>::operator[](i);\n\
    \        }\n    };\n} // namespace suisen\n\ntemplate <typename mint>\nsuisen::FPSNaive<mint>\
    \ sqrt(suisen::FPSNaive<mint> a) {\n    return a.sqrt();\n}\ntemplate <typename\
    \ mint>\nsuisen::FPSNaive<mint> log(suisen::FPSNaive<mint> a) {\n    return a.log();\n\
    }\ntemplate <typename mint>\nsuisen::FPSNaive<mint> exp(suisen::FPSNaive<mint>\
    \ a) {\n    return a.exp();\n}\ntemplate <typename mint, typename T>\nsuisen::FPSNaive<mint>\
    \ pow(suisen::FPSNaive<mint> a, T b) {\n    return a.pow(b);\n}\ntemplate <typename\
    \ mint>\nsuisen::FPSNaive<mint> inv(suisen::FPSNaive<mint> a) {\n    return a.inv();\n\
    }\n\n\n#line 8 \"test/src/polynomial/fps_naive/abc245_d.test.cpp\"\n\nint main()\
    \ {\n    int n, m;\n    std::cin >> n >> m;\n\n    suisen::FPSNaive<mint> a(n\
    \ + 1), c(n + m + 1);\n\n    for (auto &e : a) {\n        int v;\n        std::cin\
    \ >> v;\n        e = v;\n    }\n    for (auto &e : c) {\n        int v;\n    \
    \    std::cin >> v;\n        e = v;\n    }\n\n    auto [b, r] = c.div_mod(a);\n\
    \    assert(r == suisen::FPSNaive<mint>{});\n\n    for (int i = 0; i <= m; ++i)\
    \ {\n        int v = b[i].val();\n        std::cout << (v > 100 ? v - mint::mod()\
    \ : v) << \" \\n\"[i == m];\n    }\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc245/tasks/abc245_d\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/polynomial/fps_naive.hpp\"\n\nint main() {\n    int n, m;\n\
    \    std::cin >> n >> m;\n\n    suisen::FPSNaive<mint> a(n + 1), c(n + m + 1);\n\
    \n    for (auto &e : a) {\n        int v;\n        std::cin >> v;\n        e =\
    \ v;\n    }\n    for (auto &e : c) {\n        int v;\n        std::cin >> v;\n\
    \        e = v;\n    }\n\n    auto [b, r] = c.div_mod(a);\n    assert(r == suisen::FPSNaive<mint>{});\n\
    \n    for (int i = 0; i <= m; ++i) {\n        int v = b[i].val();\n        std::cout\
    \ << (v > 100 ? v - mint::mod() : v) << \" \\n\"[i == m];\n    }\n}"
  dependsOn:
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: true
  path: test/src/polynomial/fps_naive/abc245_d.test.cpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/polynomial/fps_naive/abc245_d.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/fps_naive/abc245_d.test.cpp
- /verify/test/src/polynomial/fps_naive/abc245_d.test.cpp.html
title: test/src/polynomial/fps_naive/abc245_d.test.cpp
---
