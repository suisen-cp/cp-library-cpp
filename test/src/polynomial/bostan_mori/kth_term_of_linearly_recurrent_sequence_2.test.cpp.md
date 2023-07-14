---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':x:'
    path: library/polynomial/bostan_mori.hpp
    title: Bostan Mori
  - icon: ':x:'
    path: library/polynomial/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
  bundledCode: "#line 1 \"test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <iostream>\n\n#line 1 \"library/polynomial/formal_power_series.hpp\"\
    \n\n\n\n#include <limits>\n#include <optional>\n#include <queue>\n\n#include <atcoder/modint>\n\
    #include <atcoder/convolution>\n\n#line 1 \"library/polynomial/fps_naive.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cmath>\n#line 7 \"library/polynomial/fps_naive.hpp\"\
    \n#include <type_traits>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 6 \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\
    template <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) return std::forward<Then>(then);\n    else return std::forward<OrElse>(or_else);\n\
    }\n\n// ! function\ntemplate <typename ReturnType, typename Callable, typename\
    \ ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, size_t n> struct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, size_t n> static constexpr bool is_nbit_v\
    \ = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T> struct safely_multipliable\
    \ {};\ntemplate <> struct safely_multipliable<int> { using type = long long; };\n\
    template <> struct safely_multipliable<long long> { using type = __int128_t; };\n\
    template <> struct safely_multipliable<unsigned int> { using type = unsigned long\
    \ long; };\ntemplate <> struct safely_multipliable<unsigned long int> { using\
    \ type = __uint128_t; };\ntemplate <> struct safely_multipliable<unsigned long\
    \ long> { using type = __uint128_t; };\ntemplate <> struct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <> struct safely_multipliable<double> { using\
    \ type = double; };\ntemplate <> struct safely_multipliable<long double> { using\
    \ type = long double; };\ntemplate <typename T> using safely_multipliable_t =\
    \ typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename = void>\
    \ struct rec_value_type { using type = T; };\ntemplate <typename T> struct rec_value_type<T,\
    \ std::void_t<typename T::value_type>> {\n    using type = typename rec_value_type<typename\
    \ T::value_type>::type;\n};\ntemplate <typename T> using rec_value_type_t = typename\
    \ rec_value_type<T>::type;\n\ntemplate <typename T> class is_iterable {\n    template\
    \ <typename T_>\n    static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \    static std::false_type test(...);\npublic:\n    static constexpr bool value\
    \ = decltype(test(std::declval<T>()))::value;\n};\ntemplate <typename T> static\
    \ constexpr bool is_iterable_v = is_iterable<T>::value;\n\ntemplate <typename\
    \ T> class is_writable {\n    template <typename T_>\n    static auto test(T_\
    \ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n    static\
    \ std::false_type test(...);\npublic:\n    static constexpr bool value = decltype(test(std::declval<T>()))::value;\n\
    };\ntemplate <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \ntemplate <typename T> class is_readable {\n    template <typename T_>\n    static\
    \ auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \    static std::false_type test(...);\npublic:\n    static constexpr bool value\
    \ = decltype(test(std::declval<T>()))::value;\n};\ntemplate <typename T> static\
    \ constexpr bool is_readable_v = is_readable<T>::value;\n} // namespace suisen\n\
    \n\n#line 11 \"library/polynomial/fps_naive.hpp\"\n\n#line 1 \"library/math/modint_extension.hpp\"\
    \n\n\n\n#line 6 \"library/math/modint_extension.hpp\"\n\n/**\n * refernce: https://37zigen.com/tonelli-shanks-algorithm/\n\
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
    }\n\n\n#line 14 \"library/polynomial/formal_power_series.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename mint, atcoder::internal::is_static_modint_t<mint>*\
    \ = nullptr>\n    struct FormalPowerSeries : std::vector<mint> {\n        using\
    \ base_type = std::vector<mint>;\n        using value_type = typename base_type::value_type;\n\
    \        using base_type::vector;\n\n        FormalPowerSeries(const std::initializer_list<value_type>\
    \ l) : std::vector<value_type>::vector(l) {}\n        FormalPowerSeries(const\
    \ std::vector<value_type>& v) : std::vector<value_type>::vector(v) {}\n\n    \
    \    int size() const noexcept {\n            return base_type::size();\n    \
    \    }\n        int deg() const noexcept {\n            return size() - 1;\n \
    \       }\n        void ensure(int n) {\n            if (size() < n) this->resize(n);\n\
    \        }\n\n        value_type safe_get(int d) const {\n            return d\
    \ <= deg() ? (*this)[d] : 0;\n        }\n        value_type& safe_get(int d) {\n\
    \            ensure(d + 1);\n            return (*this)[d];\n        }\n\n   \
    \     FormalPowerSeries& cut_trailing_zeros() {\n            while (size() and\
    \ this->back() == 0) this->pop_back();\n            return *this;\n        }\n\
    \        FormalPowerSeries& cut(int n) {\n            if (size() > n) this->resize(std::max(0,\
    \ n));\n            return *this;\n        }\n        FormalPowerSeries cut_copy(int\
    \ n) const {\n            FormalPowerSeries res(this->begin(), this->begin() +\
    \ std::min(size(), n));\n            res.ensure(n);\n            return res;\n\
    \        }\n        FormalPowerSeries cut_copy(int l, int r) const {\n       \
    \     if (l >= size()) return FormalPowerSeries(r - l, 0);\n            FormalPowerSeries\
    \ res(this->begin() + l, this->begin() + std::min(size(), r));\n            res.ensure(r\
    \ - l);\n            return res;\n        }\n\n        /* Unary Operations */\n\
    \n        FormalPowerSeries operator+() const { return *this; }\n        FormalPowerSeries\
    \ operator-() const {\n            FormalPowerSeries res = *this;\n          \
    \  for (auto& e : res) e = -e;\n            return res;\n        }\n        FormalPowerSeries&\
    \ operator++() { return ++safe_get(0), * this; }\n        FormalPowerSeries& operator--()\
    \ { return --safe_get(0), * this; }\n        FormalPowerSeries operator++(int)\
    \ {\n            FormalPowerSeries res = *this;\n            ++(*this);\n    \
    \        return res;\n        }\n        FormalPowerSeries operator--(int) {\n\
    \            FormalPowerSeries res = *this;\n            --(*this);\n        \
    \    return res;\n        }\n\n        /* Binary Operations With Constant */\n\
    \n        FormalPowerSeries& operator+=(const value_type& x) { return safe_get(0)\
    \ += x, *this; }\n        FormalPowerSeries& operator-=(const value_type& x) {\
    \ return safe_get(0) -= x, *this; }\n        FormalPowerSeries& operator*=(const\
    \ value_type& x) {\n            for (auto& e : *this) e *= x;\n            return\
    \ *this;\n        }\n        FormalPowerSeries& operator/=(const value_type& x)\
    \ { return *this *= x.inv(); }\n\n        friend FormalPowerSeries operator+(FormalPowerSeries\
    \ f, const value_type& x) { f += x; return f; }\n        friend FormalPowerSeries\
    \ operator+(const value_type& x, FormalPowerSeries f) { f += x; return f; }\n\
    \        friend FormalPowerSeries operator-(FormalPowerSeries f, const value_type&\
    \ x) { f -= x; return f; }\n        friend FormalPowerSeries operator-(const value_type&\
    \ x, FormalPowerSeries f) { f -= x; return -f; }\n        friend FormalPowerSeries\
    \ operator*(FormalPowerSeries f, const value_type& x) { f *= x; return f; }\n\
    \        friend FormalPowerSeries operator*(const value_type& x, FormalPowerSeries\
    \ f) { f *= x; return f; }\n        friend FormalPowerSeries operator/(FormalPowerSeries\
    \ f, const value_type& x) { f /= x; return f; }\n\n        /* Binary Operations\
    \ With Formal Power Series */\n\n        FormalPowerSeries& operator+=(const FormalPowerSeries&\
    \ g) {\n            const int n = g.size();\n            ensure(n);\n        \
    \    for (int i = 0; i < n; ++i) (*this)[i] += g[i];\n            return *this;\n\
    \        }\n        FormalPowerSeries& operator-=(const FormalPowerSeries& g)\
    \ {\n            const int n = g.size();\n            ensure(n);\n           \
    \ for (int i = 0; i < n; ++i) (*this)[i] -= g[i];\n            return *this;\n\
    \        }\n        FormalPowerSeries& operator*=(const FormalPowerSeries& g)\
    \ { return *this = *this * g; }\n        FormalPowerSeries& operator/=(const FormalPowerSeries&\
    \ g) { return *this = *this / g; }\n        FormalPowerSeries& operator%=(const\
    \ FormalPowerSeries& g) { return *this = *this % g; }\n\n        friend FormalPowerSeries\
    \ operator+(FormalPowerSeries f, const FormalPowerSeries& g) { f += g; return\
    \ f; }\n        friend FormalPowerSeries operator-(FormalPowerSeries f, const\
    \ FormalPowerSeries& g) { f -= g; return f; }\n        friend FormalPowerSeries\
    \ operator*(const FormalPowerSeries& f, const FormalPowerSeries& g) {\n      \
    \      const int siz_f = f.size(), siz_g = g.size();\n            if (siz_f <\
    \ siz_g) return g * f;\n            if (std::min(siz_f, siz_g) <= 60) return atcoder::convolution(f,\
    \ g);\n            const int deg = siz_f + siz_g - 2;\n            int fpow2 =\
    \ 1;\n            while ((fpow2 << 1) <= deg) fpow2 <<= 1;\n            if (const\
    \ int dif = deg - fpow2 + 1; dif <= 10) {\n                FormalPowerSeries h\
    \ = atcoder::convolution(std::vector<mint>(f.begin(), f.end() - dif), g);\n  \
    \              h.resize(h.size() + dif);\n                for (int i = siz_f -\
    \ dif; i < siz_f; ++i) for (int j = 0; j < siz_g; ++j) {\n                   \
    \ h[i + j] += f[i] * g[j];\n                }\n                return h;\n   \
    \         }\n            return atcoder::convolution(f, g);\n        }\n     \
    \   friend FormalPowerSeries operator/(FormalPowerSeries f, FormalPowerSeries\
    \ g) {\n            if (f.size() < 60) return FPSNaive<mint>(f).div_mod(g).first;\n\
    \            f.cut_trailing_zeros(), g.cut_trailing_zeros();\n            const\
    \ int fd = f.deg(), gd = g.deg();\n            assert(gd >= 0);\n            if\
    \ (fd < gd) return {};\n            if (gd == 0) {\n                f /= g[0];\n\
    \                return f;\n            }\n            std::reverse(f.begin(),\
    \ f.end()), std::reverse(g.begin(), g.end());\n            const int qd = fd -\
    \ gd;\n            f.cut(qd + 1);\n            FormalPowerSeries q = f * g.inv(qd\
    \ + 1);\n            q.cut(qd + 1);\n            std::reverse(q.begin(), q.end());\n\
    \            return q;\n        }\n        friend FormalPowerSeries operator%(const\
    \ FormalPowerSeries& f, const FormalPowerSeries& g) { return f.div_mod(g).second;\
    \ }\n        std::pair<FormalPowerSeries, FormalPowerSeries> div_mod(const FormalPowerSeries&\
    \ g) const {\n            if (size() < 60) {\n                auto [q, r] = FPSNaive<mint>(*this).div_mod(g);\n\
    \                return { q, r };\n            }\n            FormalPowerSeries\
    \ q = *this / g, r = *this - g * q;\n            r.cut_trailing_zeros();\n   \
    \         return { q, r };\n        }\n\n        /* Shift Operations */\n\n  \
    \      FormalPowerSeries& operator<<=(const int shamt) {\n            return this->insert(this->begin(),\
    \ shamt, 0), * this;\n        }\n        FormalPowerSeries& operator>>=(const\
    \ int shamt) {\n            return this->erase(this->begin(), this->begin() +\
    \ std::min(shamt, size())), * this;\n        }\n        friend FormalPowerSeries\
    \ operator<<(FormalPowerSeries f, const int shamt) { f <<= shamt; return f; }\n\
    \        friend FormalPowerSeries operator>>(FormalPowerSeries f, const int shamt)\
    \ { f >>= shamt; return f; }\n\n        /* Compare */\n\n        friend bool operator==(const\
    \ FormalPowerSeries& f, const FormalPowerSeries& g) {\n            const int n\
    \ = f.size(), m = g.size();\n            if (n < m) return g == f;\n         \
    \   for (int i = 0; i < m; ++i) if (f[i] != g[i]) return false;\n            for\
    \ (int i = m; i < n; ++i) if (f[i] != 0) return false;\n            return true;\n\
    \        }\n        friend bool operator!=(const FormalPowerSeries& f, const FormalPowerSeries&\
    \ g) { return not (f == g); }\n\n        /* Other Operations */\n\n        FormalPowerSeries&\
    \ diff_inplace() {\n            const int n = size();\n            for (int i\
    \ = 1; i < n; ++i) (*this)[i - 1] = (*this)[i] * i;\n            return (*this)[n\
    \ - 1] = 0, *this;\n        }\n        FormalPowerSeries diff() const {\n    \
    \        FormalPowerSeries res = *this;\n            res.diff_inplace();\n   \
    \         return res;\n        }\n        FormalPowerSeries& intg_inplace() {\n\
    \            const int n = size();\n            inv_mods<value_type> invs(n);\n\
    \            this->resize(n + 1);\n            for (int i = n; i > 0; --i) (*this)[i]\
    \ = (*this)[i - 1] * invs[i];\n            return (*this)[0] = 0, *this;\n   \
    \     }\n        FormalPowerSeries intg() const {\n            FormalPowerSeries\
    \ res = *this;\n            res.intg_inplace();\n            return res;\n   \
    \     }\n\n        FormalPowerSeries& inv_inplace(int n = -1) { return *this =\
    \ inv(n); }\n        // reference: https://opt-cp.com/fps-fast-algorithms/\n \
    \       FormalPowerSeries inv(int n = -1) const {\n            if (n < 0) n =\
    \ size();\n            if (n < 60) return FPSNaive<mint>(cut_copy(n)).inv();\n\
    \            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return inv_sparse(std::move(*sp_f),\
    \ n);\n            FormalPowerSeries f_fft, g_fft;\n            FormalPowerSeries\
    \ g{ (*this)[0].inv() };\n            for (int k = 1; k < n; k *= 2) {\n     \
    \           f_fft = cut_copy(2 * k), g_fft = g.cut_copy(2 * k);\n            \
    \    atcoder::internal::butterfly(f_fft);\n                atcoder::internal::butterfly(g_fft);\n\
    \                update_inv(k, f_fft, g_fft, g);\n            }\n            g.resize(n);\n\
    \            return g;\n        }\n        FormalPowerSeries& log_inplace(int\
    \ n = -1) { return *this = log(n); }\n        FormalPowerSeries log(int n = -1)\
    \ const {\n            assert(safe_get(0) == 1);\n            if (n < 0) n = size();\n\
    \            if (n < 60) return FPSNaive<mint>(cut_copy(n)).log();\n         \
    \   if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return log_sparse(std::move(*sp_f),\
    \ n);\n            FormalPowerSeries res = inv(n) * diff();\n            res.resize(n\
    \ - 1);\n            return res.intg();\n        }\n        FormalPowerSeries&\
    \ exp_inplace(int n = -1) { return *this = exp(n); }\n        // https://arxiv.org/pdf/1301.5804.pdf\n\
    \        FormalPowerSeries exp(int n = -1) const {\n            assert(safe_get(0)\
    \ == 0);\n            if (n < 0) n = size();\n            if (n < 60) return FPSNaive<mint>(cut_copy(n)).exp();\n\
    \            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return exp_sparse(std::move(*sp_f),\
    \ n);\n            // h = *this\n            // f = exp(h) mod x ^ k\n       \
    \     // g = f^{-1} mod x ^ k\n            FormalPowerSeries dh = diff();\n  \
    \          FormalPowerSeries f{ 1 }, f_fft;\n            FormalPowerSeries g{\
    \ 1 }, g_fft;\n            for (int k = 1; k < n; k *= 2) {\n                f_fft\
    \ = f.cut_copy(2 * k), atcoder::internal::butterfly(f_fft);\n\n              \
    \  if (k > 1) update_inv(k / 2, f_fft, g_fft, g);\n\n                FormalPowerSeries\
    \ t = f.cut_copy(k);\n                t.diff_inplace();\n                {\n \
    \                   FormalPowerSeries r = dh.cut_copy(k);\n                  \
    \  r.back() = 0;\n                    atcoder::internal::butterfly(r);\n     \
    \               for (int i = 0; i < k; ++i) r[i] *= f_fft[i];\n              \
    \      atcoder::internal::butterfly_inv(r);\n                    r /= -k;\n  \
    \                  t += r;\n                    t <<= 1, t[0] = t[k], t.pop_back();\n\
    \                }\n                t.resize(2 * k);\n                atcoder::internal::butterfly(t);\n\
    \                g_fft = g.cut_copy(2 * k);\n                atcoder::internal::butterfly(g_fft);\n\
    \                for (int i = 0; i < 2 * k; ++i) t[i] *= g_fft[i];\n         \
    \       atcoder::internal::butterfly_inv(t);\n                t.resize(k);\n \
    \               t /= 2 * k;\n\n                FormalPowerSeries v = cut_copy(2\
    \ * k) >>= k;\n                t <<= k - 1;\n                t.intg_inplace();\n\
    \                for (int i = 0; i < k; ++i) v[i] -= t[k + i];\n\n           \
    \     v.resize(2 * k);\n                atcoder::internal::butterfly(v);\n   \
    \             for (int i = 0; i < 2 * k; ++i) v[i] *= f_fft[i];\n            \
    \    atcoder::internal::butterfly_inv(v);\n                v.resize(k);\n    \
    \            v /= 2 * k;\n\n                f.resize(2 * k);\n               \
    \ for (int i = 0; i < k; ++i) f[k + i] = v[i];\n            }\n            f.cut(n);\n\
    \            return f;\n        }\n\n        FormalPowerSeries& pow_inplace(long\
    \ long k, int n = -1) { return *this = pow(k, n); }\n        FormalPowerSeries\
    \ pow(const long long k, int n = -1) const {\n            if (n < 0) n = size();\n\
    \            if (n < 60) return FPSNaive<mint>(cut_copy(n)).pow(k);\n        \
    \    if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return pow_sparse(std::move(*sp_f),\
    \ k, n);\n            if (k == 0) {\n                FormalPowerSeries f{ 1 };\n\
    \                f.resize(n);\n                return f;\n            }\n    \
    \        int tlz = 0;\n            while (tlz < size() and (*this)[tlz] == 0)\
    \ ++tlz;\n            if (tlz == size() or tlz > (n - 1) / k) return FormalPowerSeries(n,\
    \ 0);\n            const int m = n - tlz * k;\n            FormalPowerSeries f\
    \ = *this >> tlz;\n            value_type base = f[0];\n            return ((((f\
    \ /= base).log(m) *= k).exp(m) *= base.pow(k)) <<= (tlz * k));\n        }\n\n\
    \        std::optional<FormalPowerSeries> safe_sqrt(int n = -1) const {\n    \
    \        if (n < 0) n = size();\n            if (n < 60) return FPSNaive<mint>(cut_copy(n)).safe_sqrt();\n\
    \            if (auto sp_f = sparse_fps_format(15); sp_f.has_value()) return safe_sqrt_sparse(std::move(*sp_f),\
    \ n);\n            int tlz = 0;\n            while (tlz < size() and (*this)[tlz]\
    \ == 0) ++tlz;\n            if (tlz == size()) return FormalPowerSeries(n, 0);\n\
    \            if (tlz & 1) return std::nullopt;\n            const int m = n -\
    \ tlz / 2;\n\n            FormalPowerSeries h(this->begin() + tlz, this->end());\n\
    \            auto q0 = ::safe_sqrt(h[0]);\n            if (not q0.has_value())\
    \ return std::nullopt;\n\n            FormalPowerSeries f{ *q0 }, f_fft, g{ q0->inv()\
    \ }, g_fft;\n            for (int k = 1; k < m; k *= 2) {\n                f_fft\
    \ = f.cut_copy(2 * k), atcoder::internal::butterfly(f_fft);\n\n              \
    \  if (k > 1) update_inv(k / 2, f_fft, g_fft, g);\n\n                g_fft = g.cut_copy(2\
    \ * k);\n                atcoder::internal::butterfly(g_fft);\n              \
    \  FormalPowerSeries h_fft = h.cut_copy(2 * k);\n                atcoder::internal::butterfly(h_fft);\n\
    \                for (int i = 0; i < 2 * k; ++i) h_fft[i] = (h_fft[i] - f_fft[i]\
    \ * f_fft[i]) * g_fft[i];\n                atcoder::internal::butterfly_inv(h_fft);\n\
    \                f.resize(2 * k);\n                const value_type iz = value_type(4\
    \ * k).inv();\n                for (int i = 0; i < k; ++i) f[k + i] = h_fft[k\
    \ + i] * iz;\n            }\n            f.resize(m), f <<= (tlz / 2);\n     \
    \       return f;\n        }\n        FormalPowerSeries& sqrt_inplace(int n =\
    \ -1) { return *this = sqrt(n); }\n        FormalPowerSeries sqrt(int n = -1)\
    \ const {\n            return *safe_sqrt(n);\n        }\n\n        value_type\
    \ eval(value_type x) const {\n            value_type y = 0;\n            for (int\
    \ i = size() - 1; i >= 0; --i) y = y * x + (*this)[i];\n            return y;\n\
    \        }\n\n        static FormalPowerSeries prod(const std::vector<FormalPowerSeries>&\
    \ fs) {\n            if (fs.empty()) return { 1 };\n            std::deque<FormalPowerSeries>\
    \ dq(fs.begin(), fs.end());\n            std::sort(dq.begin(), dq.end(), [](auto&\
    \ f, auto& g) { return f.size() < g.size(); });\n            while (dq.size()\
    \ >= 2) {\n                dq.push_back(dq[0] * dq[1]);\n                dq.pop_front();\n\
    \                dq.pop_front();\n            }\n            return dq.front();\n\
    \        }\n\n        std::optional<std::vector<std::pair<int, value_type>>> sparse_fps_format(int\
    \ max_size) const {\n            std::vector<std::pair<int, value_type>> res;\n\
    \            for (int i = 0; i <= deg() and int(res.size()) <= max_size; ++i)\
    \ if (value_type v = (*this)[i]; v != 0) res.emplace_back(i, v);\n           \
    \ if (int(res.size()) > max_size) return std::nullopt;\n            return res;\n\
    \        }\n\n    private:\n        static void update_inv(const int k, FormalPowerSeries&\
    \ f_fft, FormalPowerSeries& g_fft, FormalPowerSeries& g) {\n            FormalPowerSeries\
    \ fg(2 * k);\n            for (int i = 0; i < 2 * k; ++i) fg[i] = f_fft[i] * g_fft[i];\n\
    \            atcoder::internal::butterfly_inv(fg);\n            fg >>= k, fg.resize(2\
    \ * k);\n            atcoder::internal::butterfly(fg);\n            for (int i\
    \ = 0; i < 2 * k; ++i) fg[i] *= g_fft[i];\n            atcoder::internal::butterfly_inv(fg);\n\
    \            const value_type iz = value_type(2 * k).inv(), c = -iz * iz;\n  \
    \          g.resize(2 * k);\n            for (int i = 0; i < k; ++i) g[k + i]\
    \ = fg[i] * c;\n        }\n\n        static FormalPowerSeries div_fps_sparse(const\
    \ FormalPowerSeries& f, const std::vector<std::pair<int, value_type>>& g, int\
    \ n) {\n            const int siz = g.size();\n            assert(siz and g[0].first\
    \ == 0);\n            const value_type inv_g0 = g[0].second.inv();\n         \
    \   FormalPowerSeries h(n);\n            for (int i = 0; i < n; ++i) {\n     \
    \           value_type v = f.safe_get(i);\n                for (int idx = 1; idx\
    \ < siz; ++idx) {\n                    const auto& [j, gj] = g[idx];\n       \
    \             if (j > i) break;\n                    v -= gj * h[i - j];\n   \
    \             }\n                h[i] = v * inv_g0;\n            }\n         \
    \   return h;\n        }\n        static FormalPowerSeries inv_sparse(const std::vector<std::pair<int,\
    \ value_type>>& g, const int n) {\n            return div_fps_sparse(FormalPowerSeries{\
    \ 1 }, g, n);\n        }\n        static FormalPowerSeries exp_sparse(const std::vector<std::pair<int,\
    \ value_type>>& f, const int n) {\n            const int siz = f.size();\n   \
    \         assert(not siz or f[0].first != 0);\n            FormalPowerSeries g(n);\n\
    \            g[0] = 1;\n            inv_mods<value_type> invs(n);\n          \
    \  for (int i = 1; i < n; ++i) {\n                value_type v = 0;\n        \
    \        for (const auto& [j, fj] : f) {\n                    if (j > i) break;\n\
    \                    v += j * fj * g[i - j];\n                }\n            \
    \    v *= invs[i];\n                g[i] = v;\n            }\n            return\
    \ g;\n        }\n        static FormalPowerSeries log_sparse(const std::vector<std::pair<int,\
    \ value_type>>& f, const int n) {\n            const int siz = f.size();\n   \
    \         assert(siz and f[0].first == 0 and f[0].second == 1);\n            FormalPowerSeries\
    \ g(n);\n            for (int idx = 1; idx < siz; ++idx) {\n                const\
    \ auto& [j, fj] = f[idx];\n                if (j >= n) break;\n              \
    \  g[j] = j * fj;\n            }\n            inv_mods<value_type> invs(n);\n\
    \            for (int i = 1; i < n; ++i) {\n                value_type v = g[i];\n\
    \                for (int idx = 1; idx < siz; ++idx) {\n                    const\
    \ auto& [j, fj] = f[idx];\n                    if (j > i) break;\n           \
    \         v -= fj * g[i - j] * (i - j);\n                }\n                v\
    \ *= invs[i];\n                g[i] = v;\n            }\n            return g;\n\
    \        }\n        static FormalPowerSeries pow_sparse(const std::vector<std::pair<int,\
    \ value_type>>& f, const long long k, const int n) {\n            if (k == 0)\
    \ {\n                FormalPowerSeries res(n, 0);\n                res[0] = 1;\n\
    \                return res;\n            }\n            const int siz = f.size();\n\
    \            if (not siz) return FormalPowerSeries(n, 0);\n            const int\
    \ p = f[0].first;\n            if (p > (n - 1) / k) return FormalPowerSeries(n,\
    \ 0);\n            const value_type inv_f0 = f[0].second.inv();\n            const\
    \ int lz = p * k;\n            FormalPowerSeries g(n);\n            g[lz] = f[0].second.pow(k);\n\
    \            inv_mods<value_type> invs(n);\n            for (int i = 1; lz + i\
    \ < n; ++i) {\n                value_type v = 0;\n                for (int idx\
    \ = 1; idx < siz; ++idx) {\n                    auto [j, fj] = f[idx];\n     \
    \               j -= p;\n                    if (j > i) break;\n             \
    \       v += fj * g[lz + i - j] * (value_type(k) * j - (i - j));\n           \
    \     }\n                v *= invs[i] * inv_f0;\n                g[lz + i] = v;\n\
    \            }\n            return g;\n        }\n        static std::optional<FormalPowerSeries>\
    \ safe_sqrt_sparse(const std::vector<std::pair<int, value_type>>& f, const int\
    \ n) {\n            const int siz = f.size();\n            if (not siz) return\
    \ FormalPowerSeries(n, 0);\n            const int p = f[0].first;\n          \
    \  if (p % 2 == 1) return std::nullopt;\n            if (p / 2 >= n) return FormalPowerSeries(n,\
    \ 0);\n            const value_type inv_f0 = f[0].second.inv();\n            const\
    \ int lz = p / 2;\n            FormalPowerSeries g(n);\n            auto opt_g0\
    \ = ::safe_sqrt(f[0].second);\n            if (not opt_g0.has_value()) return\
    \ std::nullopt;\n            g[lz] = *opt_g0;\n            value_type k = mint(2).inv();\n\
    \            inv_mods<value_type> invs(n);\n            for (int i = 1; lz + i\
    \ < n; ++i) {\n                value_type v = 0;\n                for (int idx\
    \ = 1; idx < siz; ++idx) {\n                    auto [j, fj] = f[idx];\n     \
    \               j -= p;\n                    if (j > i) break;\n             \
    \       v += fj * g[lz + i - j] * (k * j - (i - j));\n                }\n    \
    \            v *= invs[i] * inv_f0;\n                g[lz + i] = v;\n        \
    \    }\n            return g;\n        }\n        static FormalPowerSeries sqrt_sparse(const\
    \ std::vector<std::pair<int, value_type>>& f, const int n) {\n            return\
    \ *safe_sqrt(f, n);\n        }\n    };\n} // namespace suisen\n\ntemplate <typename\
    \ mint>\nsuisen::FormalPowerSeries<mint> sqrt(suisen::FormalPowerSeries<mint>\
    \ a) {\n    return a.sqrt();\n}\ntemplate <typename mint>\nsuisen::FormalPowerSeries<mint>\
    \ log(suisen::FormalPowerSeries<mint> a) {\n    return a.log();\n}\ntemplate <typename\
    \ mint>\nsuisen::FormalPowerSeries<mint> exp(suisen::FormalPowerSeries<mint> a)\
    \ {\n    return a.exp();\n}\ntemplate <typename mint, typename T>\nsuisen::FormalPowerSeries<mint>\
    \ pow(suisen::FormalPowerSeries<mint> a, T b) {\n    return a.pow(b);\n}\ntemplate\
    \ <typename mint>\nsuisen::FormalPowerSeries<mint> inv(suisen::FormalPowerSeries<mint>\
    \ a) {\n    return a.inv();\n}\n\n\n#line 1 \"library/polynomial/bostan_mori.hpp\"\
    \n\n\n\nnamespace suisen {\n    template <typename FPSType>\n    typename FPSType::value_type\
    \ bostan_mori(FPSType P, FPSType Q, unsigned long long n) {\n        auto alternate\
    \ = [](FPSType&& a, bool odd) -> FPSType&& {\n            int i = 0;\n       \
    \     for (int j = odd; j < a.size(); j += 2) a[i++] = a[j];\n            a.erase(a.begin()\
    \ + i, a.end());\n            return std::move(a);\n        };\n        for (;\
    \ n; n >>= 1) {\n            if (n < int(P.size())) P.resize(n + 1);\n       \
    \     if (n < int(Q.size())) Q.resize(n + 1);\n            FPSType mQ = Q;\n \
    \           for (int i = 1; i < Q.size(); i += 2) mQ[i] = -mQ[i];\n          \
    \  P = alternate(P * mQ, n & 1);\n            Q = alternate(Q * mQ, 0);\n    \
    \    }\n        return P[0];\n    }\n\n    template <typename FPSType>\n    typename\
    \ FPSType::value_type nth_term_of_linearly_recurrent_sequence(const FPSType& a,\
    \ const FPSType& c, const unsigned long long n) {\n        const int K = c.size();\n\
    \        assert(K <= a.size());\n        FPSType Q(K + 1);\n        Q[0] = 1;\n\
    \        for (int i = 0; i < K; ++i) {\n            Q[i + 1] = -c[i];\n      \
    \  }\n        FPSType P = a * Q;\n        P.cut(K);\n        return bostan_mori(P,\
    \ Q, n);\n    }\n\n} // namespace suisen\n\n\n#line 7 \"test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp\"\
    \nusing suisen::FormalPowerSeries;\n\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::size_t d;\n    unsigned long long k;\n    std::cin >> d >> k;\n\n \
    \   FormalPowerSeries<mint> a(d), c(d);\n    for (std::size_t i = 0; i < d; ++i)\
    \ {\n        unsigned int v;\n        std::cin >> v;\n        a[i] = v;\n    }\n\
    \    for (std::size_t i = 0; i < d; ++i) {\n        unsigned int v;\n        std::cin\
    \ >> v;\n        c[i] = v;\n    }\n    \n    std::cout << suisen::nth_term_of_linearly_recurrent_sequence(a,\
    \ c, k).val() << std::endl;\n    \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <iostream>\n\n#include \"library/polynomial/formal_power_series.hpp\"\
    \n#include \"library/polynomial/bostan_mori.hpp\"\nusing suisen::FormalPowerSeries;\n\
    \nusing mint = atcoder::modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::size_t d;\n    unsigned long long k;\n\
    \    std::cin >> d >> k;\n\n    FormalPowerSeries<mint> a(d), c(d);\n    for (std::size_t\
    \ i = 0; i < d; ++i) {\n        unsigned int v;\n        std::cin >> v;\n    \
    \    a[i] = v;\n    }\n    for (std::size_t i = 0; i < d; ++i) {\n        unsigned\
    \ int v;\n        std::cin >> v;\n        c[i] = v;\n    }\n    \n    std::cout\
    \ << suisen::nth_term_of_linearly_recurrent_sequence(a, c, k).val() << std::endl;\n\
    \    \n    return 0;\n}"
  dependsOn:
  - library/polynomial/formal_power_series.hpp
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/polynomial/bostan_mori.hpp
  isVerificationFile: true
  path: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
  requiredBy: []
  timestamp: '2023-07-13 15:42:30+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
- /verify/test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp.html
title: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence_2.test.cpp
---
