---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/arbitrary_mod_convolution.hpp
    title: "\u4EFB\u610F $\\mathrm{mod}$ \u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/factorial_large.hpp
    title: Factorial Large
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/shift_of_sampling_points.hpp
    title: Shift of Sampling Points of Polynomial
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/math/factorial_large/dummy.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#include <atcoder/modint>\n\n#line\
    \ 1 \"library/polynomial/fps.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #line 7 \"library/polynomial/fps.hpp\"\n#include <queue>\n\n#line 1 \"library/polynomial/fps_naive.hpp\"\
    \n\n\n\n#line 5 \"library/polynomial/fps_naive.hpp\"\n#include <cmath>\n#include\
    \ <limits>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    }\n\n\n#line 12 \"library/polynomial/fps.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    using convolution_t = std::vector<mint>(*)(const std::vector<mint>&,\
    \ const std::vector<mint>&);\n\n    template <typename mint>\n    struct FPS :\
    \ public std::vector<mint> {\n        using base_type = std::vector<mint>;\n \
    \       using value_type = typename base_type::value_type;\n        using base_type::vector;\n\
    \n        FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l)\
    \ {}\n        FPS(const std::vector<mint>& v) : std::vector<mint>::vector(v) {}\n\
    \        FPS(std::vector<mint>&& v) : std::vector<mint>::vector(std::move(v))\
    \ {}\n\n        static void set_multiplication(convolution_t<mint> multiplication)\
    \ {\n            FPS<mint>::mult = multiplication;\n        }\n\n        int size()\
    \ const noexcept {\n            return base_type::size();\n        }\n       \
    \ int deg() const noexcept {\n            return size() - 1;\n        }\n    \
    \    void ensure(int n) {\n            if (size() < n) this->resize(n);\n    \
    \    }\n\n        value_type safe_get(int d) const {\n            return d <=\
    \ deg() ? (*this)[d] : 0;\n        }\n        value_type& safe_get(int d) {\n\
    \            ensure(d + 1);\n            return (*this)[d];\n        }\n\n   \
    \     FPS& cut_trailing_zeros() {\n            while (this->size() and this->back()\
    \ == 0) this->pop_back();\n            return *this;\n        }\n        FPS&\
    \ cut(int n) {\n            if (size() > n) this->resize(std::max(0, n));\n  \
    \          return *this;\n        }\n        FPS cut_copy(int n) const {\n   \
    \         FPS res(this->begin(), this->begin() + std::min(size(), n));\n     \
    \       res.ensure(n);\n            return res;\n        }\n        FPS cut_copy(int\
    \ l, int r) const {\n            if (l >= size()) return FPS(r - l, 0);\n    \
    \        FPS res(this->begin() + l, this->begin() + std::min(size(), r));\n  \
    \          res.ensure(r - l);\n            return res;\n        }\n\n        /*\
    \ Unary Operations */\n\n        FPS operator+() const { return *this; }\n   \
    \     FPS operator-() const {\n            FPS res = *this;\n            for (auto&\
    \ e : res) e = -e;\n            return res;\n        }\n        FPS& operator++()\
    \ { return ++safe_get(0), * this; }\n        FPS& operator--() { return --safe_get(0),\
    \ * this; }\n        FPS operator++(int) {\n            FPS res = *this;\n   \
    \         ++(*this);\n            return res;\n        }\n        FPS operator--(int)\
    \ {\n            FPS res = *this;\n            --(*this);\n            return\
    \ res;\n        }\n\n        /* Binary Operations With Constant */\n\n       \
    \ FPS& operator+=(const value_type& x) { return safe_get(0) += x, *this; }\n \
    \       FPS& operator-=(const value_type& x) { return safe_get(0) -= x, *this;\
    \ }\n        FPS& operator*=(const value_type& x) {\n            for (auto& e\
    \ : *this) e *= x;\n            return *this;\n        }\n        FPS& operator/=(const\
    \ value_type& x) { return *this *= x.inv(); }\n\n        friend FPS operator+(FPS\
    \ f, const value_type& x) { f += x; return f; }\n        friend FPS operator+(const\
    \ value_type& x, FPS f) { f += x; return f; }\n        friend FPS operator-(FPS\
    \ f, const value_type& x) { f -= x; return f; }\n        friend FPS operator-(const\
    \ value_type& x, FPS f) { f -= x; return -f; }\n        friend FPS operator*(FPS\
    \ f, const value_type& x) { f *= x; return f; }\n        friend FPS operator*(const\
    \ value_type& x, FPS f) { f *= x; return f; }\n        friend FPS operator/(FPS\
    \ f, const value_type& x) { f /= x; return f; }\n\n        /* Binary Operations\
    \ With Formal Power Series */\n\n        FPS& operator+=(const FPS& g) {\n   \
    \         const int n = g.size();\n            ensure(n);\n            for (int\
    \ i = 0; i < n; ++i) (*this)[i] += g[i];\n            return *this;\n        }\n\
    \        FPS& operator-=(const FPS& g) {\n            const int n = g.size();\n\
    \            ensure(n);\n            for (int i = 0; i < n; ++i) (*this)[i] -=\
    \ g[i];\n            return *this;\n        }\n        FPS& operator*=(const FPS&\
    \ g) { return *this = *this * g; }\n        FPS& operator/=(const FPS& g) { return\
    \ *this = *this / g; }\n        FPS& operator%=(const FPS& g) { return *this =\
    \ *this % g; }\n\n        friend FPS operator+(FPS f, const FPS& g) { f += g;\
    \ return f; }\n        friend FPS operator-(FPS f, const FPS& g) { f -= g; return\
    \ f; }\n        friend FPS operator*(const FPS& f, const FPS& g) { return mult(f,\
    \ g); }\n        friend FPS operator/(FPS f, FPS g) {\n            if (f.size()\
    \ < 60) return FPSNaive<mint>(f).div_mod(g).first;\n            f.cut_trailing_zeros(),\
    \ g.cut_trailing_zeros();\n            const int fd = f.deg(), gd = g.deg();\n\
    \            assert(gd >= 0);\n            if (fd < gd) return {};\n         \
    \   if (gd == 0) {\n                f /= g[0];\n                return f;\n  \
    \          }\n            std::reverse(f.begin(), f.end()), std::reverse(g.begin(),\
    \ g.end());\n            const int qd = fd - gd;\n            FPS q = f * g.inv(qd\
    \ + 1);\n            q.cut(qd + 1);\n            std::reverse(q.begin(), q.end());\n\
    \            return q;\n        }\n        friend FPS operator%(const FPS& f,\
    \ const FPS& g) { return f.div_mod(g).second; }\n        std::pair<FPS, FPS> div_mod(const\
    \ FPS& g) const {\n            if (size() < 60) {\n                auto [q, r]\
    \ = FPSNaive<mint>(*this).div_mod(g);\n                return { q, r };\n    \
    \        }\n            FPS q = *this / g, r = *this - g * q;\n            r.cut_trailing_zeros();\n\
    \            return { q, r };\n        }\n\n        /* Shift Operations */\n\n\
    \        FPS& operator<<=(const int shamt) {\n            return this->insert(this->begin(),\
    \ shamt, 0), * this;\n        }\n        FPS& operator>>=(const int shamt) {\n\
    \            return this->erase(this->begin(), this->begin() + std::min(shamt,\
    \ size())), * this;\n        }\n        friend FPS operator<<(FPS f, const int\
    \ shamt) { f <<= shamt; return f; }\n        friend FPS operator>>(FPS f, const\
    \ int shamt) { f >>= shamt; return f; }\n\n        /* Compare */\n\n        friend\
    \ bool operator==(const FPS& f, const FPS& g) {\n            const int n = f.size(),\
    \ m = g.size();\n            if (n < m) return g == f;\n            for (int i\
    \ = 0; i < m; ++i) if (f[i] != g[i]) return false;\n            for (int i = m;\
    \ i < n; ++i) if (f[i] != 0) return false;\n            return true;\n       \
    \ }\n        friend bool operator!=(const FPS& f, const FPS& g) { return not (f\
    \ == g); }\n\n        /* Other Operations */\n\n        FPS& diff_inplace() {\n\
    \            const int n = size();\n            for (int i = 1; i < n; ++i) (*this)[i\
    \ - 1] = (*this)[i] * i;\n            return (*this)[n - 1] = 0, *this;\n    \
    \    }\n        FPS diff() const {\n            FPS res = *this;\n           \
    \ res.diff_inplace();\n            return res;\n        }\n        FPS& intg_inplace()\
    \ {\n            const int n = size();\n            inv_mods<value_type> invs(n);\n\
    \            this->resize(n + 1);\n            for (int i = n; i > 0; --i) (*this)[i]\
    \ = (*this)[i - 1] * invs[i];\n            return (*this)[0] = 0, *this;\n   \
    \     }\n        FPS intg() const {\n            FPS res = *this;\n          \
    \  res.intg_inplace();\n            return res;\n        }\n        \n       \
    \ FPS& inv_inplace(const int n = -1) { return *this = inv(n); } \n        FPS\
    \ inv(int n = -1) const {\n            if (n < 0) n = size();\n            if\
    \ (n < 60) return FPSNaive<mint>(*this).inv(n);\n            if (auto sp_f = sparse_fps_format(15);\
    \ sp_f.has_value()) return inv_sparse(std::move(*sp_f), n);\n            FPS g{\
    \ (*this)[0].inv() };\n            for (int k = 1; k < n; k *= 2) {\n        \
    \        FPS f_lo = cut_copy(k), f_hi = cut_copy(k, 2 * k);\n                FPS\
    \ h = (f_hi * g).cut(k) + ((f_lo * g) >>= k);\n                FPS g_hi = g *\
    \ h;\n                g.resize(2 * k);\n                for (int i = 0; i < k;\
    \ ++i) g[k + i] = -g_hi[i];\n            }\n            g.resize(n);\n       \
    \     return g;\n        }\n        FPS& log_inplace(int n = -1) { return *this\
    \ = log(n); }\n        FPS log(int n = -1) const {\n            assert(safe_get(0)\
    \ == 1);\n            if (n < 0) n = size();\n            if (n < 60) return FPSNaive<mint>(cut_copy(n)).log(n);\n\
    \            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return log_sparse(std::move(*sp_f),\
    \ n);\n            FPS res = inv(n) * diff();\n            res.resize(n - 1);\n\
    \            return res.intg();\n        }\n        FPS& exp_inplace(int n = -1)\
    \ { return *this = exp(n); }\n        FPS exp(int n = -1) {\n            assert(safe_get(0)\
    \ == 0);\n            if (n < 0) n = size();\n            if (n < 60) return FPSNaive<mint>(cut_copy(n)).exp(n);\n\
    \            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return exp_sparse(std::move(*sp_f),\
    \ n);\n            FPS res{ 1 };\n            for (int k = 1; k < n; k *= 2) res\
    \ *= ++(cut_copy(k * 2) - res.log(k * 2)), res.cut(k * 2);\n            res.resize(n);\n\
    \            return res;\n        }\n        FPS& pow_inplace(long long k, int\
    \ n = -1) { return *this = pow(k, n); }\n        FPS pow(const long long k, int\
    \ n = -1) const {\n            if (n < 0) n = size();\n            if (n < 60)\
    \ return FPSNaive<mint>(cut_copy(n)).pow(k, n);\n            if (auto sp_f = sparse_fps_format(15);\
    \ sp_f.has_value()) return pow_sparse(std::move(*sp_f), k, n);\n            if\
    \ (k == 0) {\n                FPS f{ 1 };\n                f.resize(n);\n    \
    \            return f;\n            }\n            int tlz = 0;\n            while\
    \ (tlz < size() and (*this)[tlz] == 0) ++tlz;\n            if (tlz == size() or\
    \ tlz > (n - 1) / k) return FPS(n, 0);\n            const int m = n - tlz * k;\n\
    \            FPS f = *this >> tlz;\n            value_type base = f[0];\n    \
    \        return ((((f /= base).log(m) *= k).exp(m) *= base.pow(k)) <<= (tlz *\
    \ k));\n        }\n        std::optional<FPS> safe_sqrt(int n = -1) const {\n\
    \            if (n < 0) n = size();\n            if (n < 60) return FPSNaive<mint>(cut_copy(n)).safe_sqrt(n);\n\
    \            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return safe_sqrt_sparse(std::move(*sp_f),\
    \ n);\n            int tlz = 0;\n            while (tlz < size() and (*this)[tlz]\
    \ == 0) ++tlz;\n            if (tlz == size()) return FPS(n, 0);\n           \
    \ if (tlz & 1) return std::nullopt;\n            const int m = n - tlz / 2;\n\n\
    \            FPS h(this->begin() + tlz, this->end());\n            auto q0 = ::safe_sqrt(h[0]);\n\
    \            if (not q0.has_value()) return std::nullopt;\n            FPS f{\
    \ *q0 }, g{ q0->inv() };\n            mint inv_2 = mint(2).inv();\n          \
    \  for (int k = 1; k < m; k *= 2) {\n                FPS tmp = h.cut_copy(2 *\
    \ k) * f.inv(2 * k);\n                tmp.cut(2 * k);\n                f += tmp,\
    \ f *= inv_2;\n            }\n            f.resize(m);\n            f <<= tlz\
    \ / 2;\n            return f;\n        }\n        FPS& sqrt_inplace(int n = -1)\
    \ { return *this = sqrt(n); }\n        FPS sqrt(int n = -1) const {\n        \
    \    return *safe_sqrt(n);\n        }\n\n        mint eval(mint x) const {\n \
    \           mint y = 0;\n            for (int i = size() - 1; i >= 0; --i) y =\
    \ y * x + (*this)[i];\n            return y;\n        }\n\n        static FPS\
    \ prod(const std::vector<FPS>& fs) {\n            auto comp = [](const FPS& f,\
    \ const FPS& g) { return f.size() > g.size(); };\n            std::priority_queue<FPS,\
    \ std::vector<FPS>, decltype(comp)> pq{ comp };\n            for (const auto&\
    \ f : fs) pq.push(f);\n            while (pq.size() > 1) {\n                auto\
    \ f = pq.top();\n                pq.pop();\n                auto g = pq.top();\n\
    \                pq.pop();\n                pq.push(f * g);\n            }\n \
    \           return pq.top();\n        }\n\n        std::optional<std::vector<std::pair<int,\
    \ value_type>>> sparse_fps_format(int max_size) const {\n            std::vector<std::pair<int,\
    \ value_type>> res;\n            for (int i = 0; i <= deg() and int(res.size())\
    \ <= max_size; ++i) if (value_type v = (*this)[i]; v != 0) res.emplace_back(i,\
    \ v);\n            if (int(res.size()) > max_size) return std::nullopt;\n    \
    \        return res;\n        }\n\n    protected:\n        static convolution_t<mint>\
    \ mult;\n\n        static FPS div_fps_sparse(const FPS& f, const std::vector<std::pair<int,\
    \ value_type>>& g, int n) {\n            const int siz = g.size();\n         \
    \   assert(siz and g[0].first == 0);\n            const value_type inv_g0 = g[0].second.inv();\n\
    \            FPS h(n);\n            for (int i = 0; i < n; ++i) {\n          \
    \      value_type v = f.safe_get(i);\n                for (int idx = 1; idx <\
    \ siz; ++idx) {\n                    const auto& [j, gj] = g[idx];\n         \
    \           if (j > i) break;\n                    v -= gj * h[i - j];\n     \
    \           }\n                h[i] = v * inv_g0;\n            }\n           \
    \ return h;\n        }\n        static FPS inv_sparse(const std::vector<std::pair<int,\
    \ value_type>>& g, const int n) {\n            return div_fps_sparse(FPS{ 1 },\
    \ g, n);\n        }\n        static FPS exp_sparse(const std::vector<std::pair<int,\
    \ value_type>>& f, const int n) {\n            const int siz = f.size();\n   \
    \         assert(not siz or f[0].first != 0);\n            FPS g(n);\n       \
    \     g[0] = 1;\n            inv_mods<value_type> invs(n);\n            for (int\
    \ i = 1; i < n; ++i) {\n                value_type v = 0;\n                for\
    \ (const auto& [j, fj] : f) {\n                    if (j > i) break;\n       \
    \             v += j * fj * g[i - j];\n                }\n                v *=\
    \ invs[i];\n                g[i] = v;\n            }\n            return g;\n\
    \        }\n        static FPS log_sparse(const std::vector<std::pair<int, value_type>>&\
    \ f, const int n) {\n            const int siz = f.size();\n            assert(siz\
    \ and f[0].first == 0 and f[0].second == 1);\n            FPS g(n);\n        \
    \    for (int idx = 1; idx < siz; ++idx) {\n                const auto& [j, fj]\
    \ = f[idx];\n                if (j >= n) break;\n                g[j] = j * fj;\n\
    \            }\n            inv_mods<value_type> invs(n);\n            for (int\
    \ i = 1; i < n; ++i) {\n                value_type v = g[i];\n               \
    \ for (int idx = 1; idx < siz; ++idx) {\n                    const auto& [j, fj]\
    \ = f[idx];\n                    if (j > i) break;\n                    v -= fj\
    \ * g[i - j] * (i - j);\n                }\n                v *= invs[i];\n  \
    \              g[i] = v;\n            }\n            return g;\n        }\n  \
    \      static FPS pow_sparse(const std::vector<std::pair<int, value_type>>& f,\
    \ const long long k, const int n) {\n            if (k == 0) {\n             \
    \   FPS res(n, 0);\n                res[0] = 1;\n                return res;\n\
    \            }\n            const int siz = f.size();\n            if (not siz)\
    \ return FPS(n, 0);\n            const int p = f[0].first;\n            if (p\
    \ > (n - 1) / k) return FPS(n, 0);\n            const value_type inv_f0 = f[0].second.inv();\n\
    \            const int lz = p * k;\n            FPS g(n);\n            g[lz] =\
    \ f[0].second.pow(k);\n            inv_mods<value_type> invs(n);\n           \
    \ for (int i = 1; lz + i < n; ++i) {\n                value_type v = 0;\n    \
    \            for (int idx = 1; idx < siz; ++idx) {\n                    auto [j,\
    \ fj] = f[idx];\n                    j -= p;\n                    if (j > i) break;\n\
    \                    v += fj * g[lz + i - j] * (value_type(k) * j - (i - j));\n\
    \                }\n                v *= invs[i] * inv_f0;\n                g[lz\
    \ + i] = v;\n            }\n            return g;\n        }\n        static std::optional<FPS>\
    \ safe_sqrt_sparse(const std::vector<std::pair<int, value_type>>& f, const int\
    \ n) {\n            const int siz = f.size();\n            if (not siz) return\
    \ FPS(n, 0);\n            const int p = f[0].first;\n            if (p % 2 ==\
    \ 1) return std::nullopt;\n            if (p / 2 >= n) return FPS(n, 0);\n   \
    \         const value_type inv_f0 = f[0].second.inv();\n            const int\
    \ lz = p / 2;\n            FPS g(n);\n            auto opt_g0 = ::safe_sqrt(f[0].second);\n\
    \            if (not opt_g0.has_value()) return std::nullopt;\n            g[lz]\
    \ = *opt_g0;\n            value_type k = mint(2).inv();\n            inv_mods<value_type>\
    \ invs(n);\n            for (int i = 1; lz + i < n; ++i) {\n                value_type\
    \ v = 0;\n                for (int idx = 1; idx < siz; ++idx) {\n            \
    \        auto [j, fj] = f[idx];\n                    j -= p;\n               \
    \     if (j > i) break;\n                    v += fj * g[lz + i - j] * (k * j\
    \ - (i - j));\n                }\n                v *= invs[i] * inv_f0;\n   \
    \             g[lz + i] = v;\n            }\n            return g;\n        }\n\
    \        static FPS sqrt_sparse(const std::vector<std::pair<int, value_type>>&\
    \ f, const int n) {\n            return *safe_sqrt(f, n);\n        }\n    };\n\
    \n    template <typename mint>\n    convolution_t<mint> FPS<mint>::mult = [](const\
    \ auto&, const auto&) {\n        std::cerr << \"convolution function is not available.\"\
    \ << std::endl;\n        assert(false);\n        return std::vector<mint>{};\n\
    \    };\n\n} // namespace suisen\n\ntemplate <typename mint>\nsuisen::FPS<mint>\
    \ sqrt(suisen::FPS<mint> a) {\n    return a.sqrt();\n}\ntemplate <typename mint>\n\
    suisen::FPS<mint> log(suisen::FPS<mint> a) {\n    return a.log();\n}\ntemplate\
    \ <typename mint>\nsuisen::FPS<mint> exp(suisen::FPS<mint> a) {\n    return a.exp();\n\
    }\ntemplate <typename mint, typename T>\nsuisen::FPS<mint> pow(suisen::FPS<mint>\
    \ a, T b) {\n    return a.pow(b);\n}\ntemplate <typename mint>\nsuisen::FPS<mint>\
    \ inv(suisen::FPS<mint> a) {\n    return a.inv();\n}\n\n\n#line 1 \"library/math/factorial_large.hpp\"\
    \n\n\n\n#include <utility>\n\n#line 1 \"library/polynomial/shift_of_sampling_points.hpp\"\
    \n\n\n\n#line 5 \"library/polynomial/shift_of_sampling_points.hpp\"\n#include\
    \ <atcoder/convolution>\n\n#line 1 \"library/math/factorial.hpp\"\n\n\n\n#line\
    \ 6 \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T, typename U = T>\n    struct factorial {\n        factorial() = default;\n\
    \        factorial(int n) { ensure(n); }\n\n        static void ensure(const int\
    \ n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n\n        T fac(const int i) {\n            ensure(i);\n\
    \            return _fac[i];\n        }\n        T operator()(int i) {\n     \
    \       return fac(i);\n        }\n        U fac_inv(const int i) {\n        \
    \    ensure(i);\n            return _fac_inv[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return _fac[n] * _fac_inv[r] * _fac_inv[n\
    \ - r];\n        }\n        template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        U polynom(const int n, const Ds& ...ds)\
    \ {\n            if (n < 0) return 0;\n            ensure(n);\n            int\
    \ sumd = 0;\n            U res = _fac[n];\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= _fac_inv[d];\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= _fac_inv[n - sumd];\n            return res;\n\
    \        }\n        U perm(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return _fac[n]\
    \ * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T> _fac;\n\
    \        static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 8 \"library/polynomial/shift_of_sampling_points.hpp\"\n\n\
    namespace suisen {\n    template <typename mint, typename Convolve,\n        std::enable_if_t<std::is_invocable_r_v<std::vector<mint>,\
    \ Convolve, std::vector<mint>, std::vector<mint>>, std::nullptr_t> = nullptr>\n\
    \    std::vector<mint> shift_of_sampling_points(const std::vector<mint>& ys, mint\
    \ t, int m, const Convolve &convolve) {\n        const int n = ys.size();\n  \
    \      factorial<mint> fac(std::max(n, m));\n\n        std::vector<mint> b = [&]\
    \ {\n            std::vector<mint> f(n), g(n);\n            for (int i = 0; i\
    \ < n; ++i) {\n                f[i] = ys[i] * fac.fac_inv(i);\n              \
    \  g[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);\n            }\n            std::vector<mint>\
    \ b = convolve(f, g);\n            b.resize(n);\n            return b;\n     \
    \   }();\n        std::vector<mint> e = [&] {\n            std::vector<mint> c(n);\n\
    \            mint prd = 1;\n            std::reverse(b.begin(), b.end());\n  \
    \          for (int i = 0; i < n; ++i) {\n                b[i] *= fac.fac(n -\
    \ i - 1);\n                c[i] = prd * fac.fac_inv(i);\n                prd *=\
    \ t - i;\n            }\n            std::vector<mint> e = convolve(b, c);\n \
    \           e.resize(n);\n            return e;\n        }();\n        std::reverse(e.begin(),\
    \ e.end());\n        for (int i = 0; i < n; ++i) {\n            e[i] *= fac.fac_inv(i);\n\
    \        }\n\n        std::vector<mint> f(m);\n        for (int i = 0; i < m;\
    \ ++i) f[i] = fac.fac_inv(i);\n        std::vector<mint> res = convolve(e, f);\n\
    \        res.resize(m);\n        for (int i = 0; i < m; ++i) res[i] *= fac.fac(i);\n\
    \        return res;\n    }\n\n    template <typename mint>\n    std::vector<mint>\
    \ shift_of_sampling_points(const std::vector<mint>& ys, mint t, int m) {\n   \
    \     auto convolve = [&](const std::vector<mint> &f, const std::vector<mint>\
    \ &g) { return atcoder::convolution(f, g); };\n        return shift_of_sampling_points(ys,\
    \ t, m, convolve);\n    }\n} // namespace suisen\n\n\n\n#line 1 \"library/convolution/arbitrary_mod_convolution.hpp\"\
    \n\n\n\n#line 6 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\n#line\
    \ 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution_naive.hpp\"\
    \n\nnamespace suisen::internal {\n    template <typename T, typename R = T>\n\
    \    std::vector<R> convolution_naive(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\n        const int n = a.size(), m = b.size();\n        std::vector<R>\
    \ c(n + m - 1);\n        if (n < m) {\n            for (int j = 0; j < m; j++)\
    \ for (int i = 0; i < n; i++) c[i + j] += R(a[i]) * b[j];\n        } else {\n\
    \            for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j]\
    \ += R(a[i]) * b[j];\n        }\n        return c;\n    }\n} // namespace suisen\n\
    \n\n\n#line 8 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename mint, atcoder::internal::is_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        int n = int(a.size()), m = int(b.size());\n\
    \n        if constexpr (atcoder::internal::is_static_modint<mint>::value) {\n\
    \            if constexpr (not (mint::mod() & 63)) {\n                int maxz\
    \ = 1;\n                while (not ((mint::mod() - 1) & maxz)) maxz <<= 1;\n \
    \               int z = 1;\n                while (z < n + m - 1) z <<= 1;\n \
    \               if (z <= maxz) return atcoder::convolution<mint>(a, b);\n    \
    \        }\n        }\n\n        if (n == 0 or m == 0) return {};\n        if\
    \ (std::min(n, m) <= 120) return internal::convolution_naive(a, b);\n\n      \
    \  static constexpr long long MOD1 = 754974721;  // 2^24\n        static constexpr\
    \ long long MOD2 = 167772161;  // 2^25\n        static constexpr long long MOD3\
    \ = 469762049;  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n\
    \        static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1,\
    \ MOD2).second;\n        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        std::vector<int> a2(n), b2(m);\n        for (int i\
    \ = 0; i < n; ++i) a2[i] = a[i].val();\n        for (int i = 0; i < m; ++i) b2[i]\
    \ = b[i].val();\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n   \
    \     auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n\n        const long long m1m2 = mint(M1M2).val();\n        std::vector<mint>\
    \ c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n            //\
    \ Garner's Algorithm\n            // X = x1 + x2 * m1 + x3 * m1 * m2\n       \
    \     // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 *\
    \ m1) / m2 (mod m3)\n            long long x1 = c1[i];\n            long long\
    \ x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n     \
    \       long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + x3 * m1m2;\n    \
    \    }\n        return c;\n    }\n\n    std::vector<__uint128_t> convolution_int(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n        int n = int(a.size()),\
    \ m = int(b.size());\n\n        auto check_nonnegative = [](int e) { return e\
    \ >= 0; };\n        assert(std::all_of(a.begin(), a.end(), check_nonnegative));\n\
    \        assert(std::all_of(b.begin(), b.end(), check_nonnegative));\n\n     \
    \   if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 120) return\
    \ internal::convolution_naive<int, __uint128_t>(a, b);\n\n        static constexpr\
    \ long long MOD1 = 754974721;  // 2^24\n        static constexpr long long MOD2\
    \ = 167772161;  // 2^25\n        static constexpr long long MOD3 = 469762049;\
    \  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n        static\
    \ constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;\n\
    \        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        auto c1 = atcoder::convolution<MOD1>(a, b);\n     \
    \   auto c2 = atcoder::convolution<MOD2>(a, b);\n        auto c3 = atcoder::convolution<MOD3>(a,\
    \ b);\n        std::vector<__uint128_t> c(n + m - 1);\n        for (int i = 0;\
    \ i < n + m - 1; ++i) {\n            // Garner's Algorithm\n            // X =\
    \ x1 + x2 * m1 + x3 * m1 * m2\n            // x1 = c1[i], x2 = (c2[i] - x1) /\
    \ m1 (mod m2), x3 = (c3[i] - x1 - x2 * m1) / m2 (mod m3)\n            int x1 =\
    \ c1[i];\n            int x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n\
    \            int x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + __uint128_t(x3) *\
    \ M1M2;\n        }\n        return c;\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 9 \"library/math/factorial_large.hpp\"\n\nnamespace suisen {\n    // mod must\
    \ be a prime number\n    template <typename mint,\n        std::enable_if_t<atcoder::internal::is_static_modint<mint>::value,\
    \ std::nullptr_t> = nullptr>\n    struct factorial_large {\n        using value_type\
    \ = mint;\n\n        static constexpr int LOG_BLOCK_SIZE = 9;\n        static\
    \ constexpr int BLOCK_SIZE = 1 << LOG_BLOCK_SIZE;\n        static constexpr int\
    \ BLOCK_NUM = value_type::mod() >> LOG_BLOCK_SIZE;\n\n        static inline int\
    \ threshold = 2000000;\n\n        static_assert(atcoder::internal::is_prime_constexpr(mint::mod()));\n\
    \n        static value_type fac(long long n) {\n            if (n >= mint::mod())\
    \ return 0;\n            return n <= threshold ? factorial<mint>{}.fac(n) : _large_fac(n);\n\
    \        }\n        static value_type fac_inv(long long n) {\n            assert(n\
    \ < (long long) mint::mod());\n            return n <= threshold ? factorial<mint>{}.fac_inv(n)\
    \ : _large_fac(n).inv();\n        }\n        static value_type binom(int n, int\
    \ r) {\n            if (r < 0 or r > n) return 0;\n            return fac(n) *\
    \ fac_inv(r) * fac_inv(n - r);\n        }\n        template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        static value_type polynom(const int n, const\
    \ Ds& ...ds) {\n            if (n < 0) return 0;\n            long long sumd =\
    \ 0;\n            value_type res = fac(n);\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= fac_inv(d);\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= fac_inv(n - sumd);\n            return res;\n\
    \        }\n        static value_type perm(int n, int r) {\n            if (r\
    \ < 0 or r > n) return 0;\n            return fac(n) * fac_inv(n - r);\n     \
    \   }\n    private:\n        static inline std::vector<value_type> _block_fac{};\n\
    \n        static void _build() {\n            if (_block_fac.size()) {\n     \
    \           return;\n            }\n            std::vector<value_type> f{ 1 };\n\
    \            f.reserve(BLOCK_SIZE);\n            for (int i = 0; i < LOG_BLOCK_SIZE;\
    \ ++i) {\n                std::vector<value_type> g = shift_of_sampling_points<value_type>(f,\
    \ 1 << i, 3 << i, arbitrary_mod_convolution<value_type>);\n                const\
    \ auto get = [&](int j) { return j < (1 << i) ? f[j] : g[j - (1 << i)]; };\n \
    \               f.resize(2 << i);\n                for (int j = 0; j < 2 << i;\
    \ ++j) {\n                    f[j] = get(2 * j) * get(2 * j + 1) * ((2 * j + 1)\
    \ << i);\n                }\n            }\n            // f_B(x) = (x+1) * ...\
    \ * (x+B-1)\n            if (BLOCK_NUM > BLOCK_SIZE) {\n                std::vector<value_type>\
    \ g = shift_of_sampling_points<value_type>(f, BLOCK_SIZE, BLOCK_NUM - BLOCK_SIZE,\
    \ arbitrary_mod_convolution<value_type>);\n                std::move(g.begin(),\
    \ g.end(), std::back_inserter(f));\n            } else {\n                f.resize(BLOCK_NUM);\n\
    \            }\n            for (int i = 0; i < BLOCK_NUM; ++i) {\n          \
    \      f[i] *= value_type(i + 1) * BLOCK_SIZE;\n            }\n            //\
    \ f[i] = (i*B + 1) * ... * (i*B + B)\n\n            f.insert(f.begin(), 1);\n\
    \            for (int i = 1; i <= BLOCK_NUM; ++i) {\n                f[i] *= f[i\
    \ - 1];\n            }\n            _block_fac = std::move(f);\n        }\n\n\
    \        static value_type _large_fac(int n) {\n            _build();\n      \
    \      value_type res;\n            int q = n / BLOCK_SIZE, r = n % BLOCK_SIZE;\n\
    \            if (2 * r <= BLOCK_SIZE) {\n                res = _block_fac[q];\n\
    \                for (int i = 0; i < r; ++i) {\n                    res *= value_type::raw(n\
    \ - i);\n                }\n            } else if (q != factorial_large::BLOCK_NUM)\
    \ {\n                res = _block_fac[q + 1];\n                value_type den\
    \ = 1;\n                for (int i = 1; i <= BLOCK_SIZE - r; ++i) {\n        \
    \            den *= value_type::raw(n + i);\n                }\n             \
    \   res /= den;\n            } else {\n                // Wilson's theorem\n \
    \               res = value_type::mod() - 1;\n                value_type den =\
    \ 1;\n                for (int i = value_type::mod() - 1; i > n; --i) {\n    \
    \                den *= value_type::raw(i);\n                }\n             \
    \   res /= den;\n            }\n            return res;\n        }\n    };\n}\
    \ // namespace suisen\n\n\n\n#line 10 \"test/src/math/factorial_large/dummy.test.cpp\"\
    \n\ntemplate <int MOD>\nvoid test() {\n    using mint = atcoder::static_modint<MOD>;\n\
    \n    std::mt19937 rng{};\n    constexpr int MAX_N = 10000000;\n    std::uniform_int_distribution<int>\
    \ dist(0, MAX_N);\n\n    const int q = 10000;\n    std::vector<int> ns(q);\n \
    \   for (int& e : ns) e = dist(rng);\n    // power of 2\n    for (int i = 0; 1\
    \ << i < MAX_N; ++i) ns[i] = 1 << i;\n\n    std::vector<mint> res1, res2;\n  \
    \  {\n        suisen::factorial_large<mint> fac{};\n        fac.threshold = -1;\n\
    \        res1.resize(q);\n        for (int i = 0; i < q; ++i) res1[i] = fac.fac(ns[i]);\n\
    \    }\n    {\n        suisen::factorial<mint> fac{};\n        res2.resize(q);\n\
    \        for (int i = 0; i < q; ++i) res2[i] = fac.fac(ns[i]);\n    }\n    assert(res1\
    \ == res2);\n\n}\n\nint main() {\n    test<998244353>();\n    test<1000000007>();\n\
    \    test<1000000009>();\n    std::cout << \"Hello World\" << std::endl;\n   \
    \ return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#include <atcoder/modint>\n\n#include\
    \ \"library/polynomial/fps.hpp\"\n#include \"library/math/factorial_large.hpp\"\
    \n\ntemplate <int MOD>\nvoid test() {\n    using mint = atcoder::static_modint<MOD>;\n\
    \n    std::mt19937 rng{};\n    constexpr int MAX_N = 10000000;\n    std::uniform_int_distribution<int>\
    \ dist(0, MAX_N);\n\n    const int q = 10000;\n    std::vector<int> ns(q);\n \
    \   for (int& e : ns) e = dist(rng);\n    // power of 2\n    for (int i = 0; 1\
    \ << i < MAX_N; ++i) ns[i] = 1 << i;\n\n    std::vector<mint> res1, res2;\n  \
    \  {\n        suisen::factorial_large<mint> fac{};\n        fac.threshold = -1;\n\
    \        res1.resize(q);\n        for (int i = 0; i < q; ++i) res1[i] = fac.fac(ns[i]);\n\
    \    }\n    {\n        suisen::factorial<mint> fac{};\n        res2.resize(q);\n\
    \        for (int i = 0; i < q; ++i) res2[i] = fac.fac(ns[i]);\n    }\n    assert(res1\
    \ == res2);\n\n}\n\nint main() {\n    test<998244353>();\n    test<1000000007>();\n\
    \    test<1000000009>();\n    std::cout << \"Hello World\" << std::endl;\n   \
    \ return 0;\n}\n"
  dependsOn:
  - library/polynomial/fps.hpp
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/math/factorial_large.hpp
  - library/polynomial/shift_of_sampling_points.hpp
  - library/math/factorial.hpp
  - library/convolution/arbitrary_mod_convolution.hpp
  - library/convolution/convolution_naive.hpp
  isVerificationFile: true
  path: test/src/math/factorial_large/dummy.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 21:01:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/factorial_large/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/factorial_large/dummy.test.cpp
- /verify/test/src/math/factorial_large/dummy.test.cpp.html
title: test/src/math/factorial_large/dummy.test.cpp
---