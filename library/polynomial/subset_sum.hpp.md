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
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
    title: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/subset_sum.hpp\"\n\n\n\n#line 1 \"library/polynomial/fps.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n\n#line\
    \ 1 \"library/polynomial/fps_naive.hpp\"\n\n\n\n#line 5 \"library/polynomial/fps_naive.hpp\"\
    \n#include <cmath>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
    \n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 6 \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 11 \"library/polynomial/fps_naive.hpp\"\n\n#line\
    \ 1 \"library/math/modint_extension.hpp\"\n\n\n\n#line 5 \"library/math/modint_extension.hpp\"\
    \n#include <optional>\n\nnamespace suisen {\n/**\n * refernce: https://37zigen.com/tonelli-shanks-algorithm/\n\
    \ * calculates x s.t. x^2 = a mod p in O((log p)^2).\n */\ntemplate <typename\
    \ mint>\nstd::optional<mint> optional_sqrt(mint a) {\n    static int p = mint::mod();\n\
    \    if (a == 0) return std::make_optional(0);\n    if (p == 2) return std::make_optional(a);\n\
    \    if (a.pow((p - 1) / 2) != 1) return std::nullopt;\n    mint b = 1;\n    while\
    \ (b.pow((p - 1) / 2) == 1) ++b;\n    static int tlz = __builtin_ctz(p - 1), q\
    \ = (p - 1) >> tlz;\n    mint x = a.pow((q + 1) / 2);\n    b = b.pow(q);\n   \
    \ for (int shift = 2; x * x != a; ++shift) {\n        mint e = a.inv() * x * x;\n\
    \        if (e.pow(1 << (tlz - shift)) != 1) x *= b;\n        b *= b;\n    }\n\
    \    return std::make_optional(x);\n}\n\n};\n\n/**\n * calculates x s.t. x^2 =\
    \ a mod p in O((log p)^2).\n * if not exists, raises runtime error.\n */\ntemplate\
    \ <typename mint>\nauto sqrt(mint a) -> decltype(mint::mod(), mint()) {\n    return\
    \ *suisen::optional_sqrt(a);\n}\ntemplate <typename mint>\nauto log(mint a) ->\
    \ decltype(mint::mod(), mint())  {\n    assert(a == 1);\n    return 0;\n}\ntemplate\
    \ <typename mint>\nauto exp(mint a) -> decltype(mint::mod(), mint())  {\n    assert(a\
    \ == 0);\n    return 1;\n}\ntemplate <typename mint, typename T>\nauto pow(mint\
    \ a, T b) -> decltype(mint::mod(), mint())  {\n    return a.pow(b);\n}\ntemplate\
    \ <typename mint>\nauto inv(mint a) -> decltype(mint::mod(), mint()) {\n    return\
    \ a.inv();\n}\n\n\n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#line 5 \"library/math/inv_mods.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n\
    \        inv_mods() {}\n        inv_mods(int n) { ensure(n); }\n        const\
    \ mint& operator[](int i) const {\n            ensure(i);\n            return\
    \ invs[i];\n        }\n        static void ensure(int n) {\n            int sz\
    \ = invs.size();\n            if (sz < 2) invs = {0, 1}, sz = 2;\n           \
    \ if (sz < n + 1) {\n                invs.resize(n + 1);\n                for\
    \ (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n \
    \           }\n        }\n    private:\n        static std::vector<mint> invs;\n\
    \        static constexpr int mod = mint::mod();\n};\ntemplate <typename mint>\n\
    std::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n#line 14 \"library/polynomial/fps_naive.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct FPSNaive : std::vector<T>\
    \ {\n        static inline int MAX_DEG = std::numeric_limits<int>::max() / 2;\n\
    \n        using value_type = T;\n        using element_type = rec_value_type_t<T>;\n\
    \        using std::vector<value_type>::vector;\n\n        FPSNaive(const std::initializer_list<value_type>\
    \ l) : std::vector<value_type>::vector(l) {}\n\n        static void set_max_deg(int\
    \ max_deg) {\n            FPSNaive<T>::MAX_DEG = max_deg;\n        }\n\n     \
    \   const value_type operator[](int n) const {\n            return n <= deg()\
    \ ? unsafe_get(n) : value_type{ 0 };\n        }\n        value_type& operator[](int\
    \ n) {\n            return ensure_deg(n), unsafe_get(n);\n        }\n\n      \
    \  int size() const {\n            return std::vector<value_type>::size();\n \
    \       }\n        int deg() const {\n            return size() - 1;\n       \
    \ }\n        int normalize() {\n            while (size() and this->back() ==\
    \ value_type{ 0 }) this->pop_back();\n            return deg();\n        }\n \
    \       FPSNaive& cut_inplace(int max_deg) {\n            if (deg() > max_deg)\
    \ this->resize(std::max(0, max_deg + 1));\n            return *this;\n       \
    \ }\n        FPSNaive cut(int max_deg) const {\n            return FPSNaive(*this).cut_inplace(max_deg);\n\
    \        }\n\n        FPSNaive operator+() const {\n            return FPSNaive(*this);\n\
    \        }\n        FPSNaive operator-() const {\n            FPSNaive f(*this);\n\
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
    \ shamt, value_type { 0 });\n            return *this;\n        }\n        FPSNaive&\
    \ operator>>=(const int shamt) {\n            if (shamt > size()) this->clear();\n\
    \            else this->erase(this->begin(), this->begin() + shamt);\n       \
    \     return *this;\n        }\n\n        friend FPSNaive operator+(FPSNaive f,\
    \ const FPSNaive& g)   { f += g; return f; }\n        friend FPSNaive operator+(FPSNaive\
    \ f, const value_type &x) { f += x; return f; }\n        friend FPSNaive operator-(FPSNaive\
    \ f, const FPSNaive& g)   { f -= g; return f; }\n        friend FPSNaive operator-(FPSNaive\
    \ f, const value_type &x) { f -= x; return f; }\n        friend FPSNaive operator*(const\
    \ FPSNaive &f, const FPSNaive& g) {\n            if (f.empty() or g.empty()) return\
    \ FPSNaive{};\n            const int n = f.size(), m = g.size();\n           \
    \ FPSNaive h(std::min(MAX_DEG + 1, n + m - 1));\n            for (int i = 0; i\
    \ < n; ++i) for (int j = 0; j < m; ++j) {\n                if (i + j > MAX_DEG)\
    \ break;\n                h.unsafe_get(i + j) += f.unsafe_get(i) * g.unsafe_get(j);\n\
    \            }\n            return h;\n        }\n        friend FPSNaive operator*(FPSNaive\
    \ f, const value_type &x) { f *= x; return f; }\n        friend FPSNaive operator/(FPSNaive\
    \ f, FPSNaive g) { return std::move(div_mod(std::move(f), std::move(g)).first);\
    \ }\n        friend FPSNaive operator%(FPSNaive f, FPSNaive g) { return std::move(div_mod(std::move(f),\
    \ std::move(g)).second); }\n        friend FPSNaive operator*(const value_type\
    \ x, FPSNaive f) { f *= x; return f; }\n        friend FPSNaive operator<<(FPSNaive\
    \ f, const int shamt)   { f <<= shamt; return f; }\n        friend FPSNaive operator>>(FPSNaive\
    \ f, const int shamt)   { f >>= shamt; return f; }\n\n        friend std::pair<FPSNaive,\
    \ FPSNaive> div_mod(FPSNaive f, FPSNaive g) {\n            const int fd = f.normalize(),\
    \ gd = g.normalize();\n            assert(gd >= 0);\n            if (fd < gd)\
    \ return { FPSNaive{}, f };\n            if (gd == 0) return { f *= g.unsafe_get(0).inv(),\
    \ FPSNaive{} };\n            const int k = f.deg() - gd;\n            value_type\
    \ head_inv = g.unsafe_get(gd).inv();\n            FPSNaive q(k + 1);\n       \
    \     for (int i = k; i >= 0; --i) {\n                value_type div = f.unsafe_get(i\
    \ + gd) * head_inv;\n                q.unsafe_get(i) = div;\n                for\
    \ (int j = 0; j <= gd; ++j) f.unsafe_get(i + j) -= div * g.unsafe_get(j);\n  \
    \          }\n            return { q, f.cut_inplace(gd - 1) };\n        }\n\n\
    \        friend bool operator==(const FPSNaive& f, const FPSNaive& g) {\n    \
    \        const int n = f.size(), m = g.size();\n            if (n < m) return\
    \ g == f;\n            for (int i = 0; i < m; ++i) if (f.unsafe_get(i) != g.unsafe_get(i))\
    \ return false;\n            for (int i = m; i < n; ++i) if (f.unsafe_get(i) !=\
    \ 0) return false;\n            return true;\n        }\n        friend bool operator!=(const\
    \ FPSNaive& f, const FPSNaive& g) {\n            return not (f == g);\n      \
    \  }\n\n        FPSNaive mul(const FPSNaive& g, int max_deg) const {\n       \
    \     if (this->empty() or g.empty()) return FPSNaive{};\n            const int\
    \ n = size(), m = g.size();\n            FPSNaive h(std::min(max_deg + 1, n +\
    \ m - 1));\n            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)\
    \ {\n                if (i + j > max_deg) break;\n                h.unsafe_get(i\
    \ + j) += unsafe_get(i) * g.unsafe_get(j);\n            }\n            return\
    \ h;\n        }\n        FPSNaive diff() const {\n            if (this->empty())\
    \ return {};\n            FPSNaive g(size() - 1);\n            for (int i = 1;\
    \ i <= deg(); ++i) g.unsafe_get(i - 1) = unsafe_get(i) * i;\n            return\
    \ g;\n        }\n        FPSNaive intg() const {\n            const int n = size();\n\
    \            FPSNaive g(n + 1);\n            for (int i = 0; i < n; ++i) g.unsafe_get(i\
    \ + 1) = unsafe_get(i) * invs[i + 1];\n            if (g.deg() > MAX_DEG) g.cut_inplace(MAX_DEG);\n\
    \            return g;\n        }\n        FPSNaive inv(int max_deg) const {\n\
    \            FPSNaive g(max_deg + 1);\n            const value_type inv_f0 = ::inv(unsafe_get(0));\n\
    \            g.unsafe_get(0) = inv_f0;\n            for (int i = 1; i <= max_deg;\
    \ ++i) {\n                for (int j = 1; j <= i; ++j) g.unsafe_get(i) -= g.unsafe_get(i\
    \ - j) * (*this)[j];\n                g.unsafe_get(i) *= inv_f0;\n           \
    \ }\n            return g;\n        }\n        FPSNaive exp(int max_deg) const\
    \ {\n            assert(unsafe_get(0) == value_type{ 0 });\n            FPSNaive\
    \ g(max_deg + 1);\n            g.unsafe_get(0) = value_type{ 1 };\n          \
    \  for (int i = 1; i <= max_deg; ++i) {\n                for (int j = 1; j <=\
    \ i; ++j) g.unsafe_get(i) += j * g.unsafe_get(i - j) * (*this)[j];\n         \
    \       g.unsafe_get(i) *= invs[i];\n            }\n            return g;\n  \
    \      }\n        FPSNaive log(int max_deg) const {\n            assert(unsafe_get(0)\
    \ == value_type{ 1 });\n            FPSNaive g(max_deg + 1);\n            g.unsafe_get(0)\
    \ = value_type{ 0 };\n            for (int i = 1; i <= max_deg; ++i) {\n     \
    \           g.unsafe_get(i) = i * (*this)[i];\n                for (int j = 1;\
    \ j < i; ++j) g.unsafe_get(i) -= (i - j) * g.unsafe_get(i - j) * (*this)[j];\n\
    \                g.unsafe_get(i) *= invs[i];\n            }\n            return\
    \ g;\n        }\n        FPSNaive pow(const long long k, int max_deg) const {\n\
    \            if (k == 0) return { value_type{ 1 } };\n            int z = 0;\n\
    \            while (z < size() and unsafe_get(z) == value_type{ 0 }) ++z;\n  \
    \          if (z >= max_deg / k + 1) return FPSNaive{};\n            const int\
    \ d = max_deg - z * k;\n\n            FPSNaive g(d + 1);\n            const value_type\
    \ inv_f0 = ::inv(unsafe_get(z));\n            g.unsafe_get(0) = unsafe_get(z).pow(k);\n\
    \            for (int i = 1; i <= d; ++i) {\n                for (int j = 1; j\
    \ <= i; ++j) g.unsafe_get(i) += (element_type{ k } * j - (i - j)) * g.unsafe_get(i\
    \ - j) * (*this)[z + j];\n                g.unsafe_get(i) *= inv_f0 * invs[i];\n\
    \            }\n            g <<= z * k;\n            return g;\n        }\n\n\
    \        FPSNaive sqrt(int max_deg) const {\n            int dl = 0;\n       \
    \     while (dl < size() and unsafe_get(dl) == value_type{ 0 }) ++dl;\n      \
    \      if (dl == size()) return FPSNaive{};\n            if (dl & 1) assert(false);\n\
    \n            const int d = max_deg - dl / 2;\n\n            FPSNaive g(d + 1);\n\
    \            g.unsafe_get(0) = ::sqrt((*this)[dl]);\n            value_type inv_2g0\
    \ = ::inv(2 * g.unsafe_get(0));\n            for (int i = 1; i <= d; ++i) {\n\
    \                g.unsafe_get(i) = unsafe_get(dl + i);\n                for (int\
    \ j = 1; j < i; ++j) g.unsafe_get(i) -= g.unsafe_get(j) * g.unsafe_get(i - j);\n\
    \                g.unsafe_get(i) *= inv_2g0;\n            }\n            g <<=\
    \ dl / 2;\n            return g;\n        }\n\n        value_type eval(value_type\
    \ x) const {\n            value_type y = 0;\n            for (int i = size() -\
    \ 1; i >= 0; --i) y = y * x + unsafe_get(i);\n            return y;\n        }\n\
    \n    private:\n        static inline inv_mods<element_type> invs;\n\n       \
    \ void ensure_deg(int d) {\n            if (deg() < d) this->resize(d + 1, value_type{\
    \ 0 });\n        }\n        const value_type& unsafe_get(int i) const {\n    \
    \        return std::vector<value_type>::operator[](i);\n        }\n        value_type&\
    \ unsafe_get(int i) {\n            return std::vector<value_type>::operator[](i);\n\
    \        }\n    };\n} // namespace suisen\n\ntemplate <typename mint>\nauto sqrt(suisen::FPSNaive<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {\n    return a.sqrt(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\ntemplate <typename mint>\nauto log(suisen::FPSNaive<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPSNaive<mint>{}) {\n    return a.log(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\ntemplate <typename mint>\nauto exp(suisen::FPSNaive<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPSNaive<mint>{}) {\n    return a.exp(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\ntemplate <typename mint, typename T>\nauto pow(suisen::FPSNaive<mint> a, T\
    \ b) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {\n    return a.pow(b,\
    \ suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG\
    \ : a.deg());\n}\ntemplate <typename mint>\nauto inv(suisen::FPSNaive<mint> a)\
    \ -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {\n    return a.inv(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\n\n\n\n#line 10 \"library/polynomial/fps.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    using convolution_t = std::vector<mint>(*)(const std::vector<mint>&,\
    \ const std::vector<mint>&);\n\n    template <typename mint>\n    struct FPS :\
    \ public std::vector<mint> {\n        using std::vector<mint>::vector;\n\n   \
    \     FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l)\
    \ {}\n        FPS(const std::vector<mint>& v) : std::vector<mint>::vector(v) {}\n\
    \        FPS(std::vector<mint>&& v) : std::vector<mint>::vector(std::move(v))\
    \ {}\n\n        static void set_multiplication(convolution_t<mint> multiplication)\
    \ {\n            FPS<mint>::mult = multiplication;\n        }\n\n        const\
    \ mint operator[](int n) const noexcept { return n <= deg() ? unsafe_get(n) :\
    \ 0; }\n        mint& operator[](int n) noexcept { ensure_deg(n); return unsafe_get(n);\
    \ }\n\n        int size() const noexcept { return std::vector<mint>::size(); }\n\
    \        int deg()  const noexcept { return size() - 1; }\n        int normalize()\
    \ {\n            while (this->size() and this->back() == 0) this->pop_back();\n\
    \            return deg();\n        }\n        FPS& pre_inplace(int max_deg) noexcept\
    \ {\n            if (deg() > max_deg) this->resize(std::max(0, max_deg + 1));\n\
    \            return *this;\n        }\n        FPS pre(int max_deg) const noexcept\
    \ { return FPS(*this).pre_inplace(max_deg); }\n\n        FPS operator+() const\
    \ { return FPS(*this); }\n        FPS operator-() const {\n            FPS f(*this);\n\
    \            for (auto& e : f) e = mint::mod() - e;\n            return f;\n \
    \       }\n        FPS& operator++() { ++(*this)[0]; return *this; }\n       \
    \ FPS& operator--() { --(*this)[0]; return *this; }\n        FPS& operator+=(const\
    \ mint x) { (*this)[0] += x; return *this; }\n        FPS& operator-=(const mint\
    \ x) { (*this)[0] -= x; return *this; }\n        FPS& operator+=(const FPS& g)\
    \ {\n            ensure_deg(g.deg());\n            for (int i = 0; i <= g.deg();\
    \ ++i) unsafe_get(i) += g.unsafe_get(i);\n            return *this;\n        }\n\
    \        FPS& operator-=(const FPS& g) {\n            ensure_deg(g.deg());\n \
    \           for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);\n\
    \            return *this;\n        }\n        FPS& operator*=(const FPS& g) {\
    \ return *this = FPS<mint>::mult(*this, g); }\n        FPS& operator*=(const mint\
    \ x) {\n            for (auto& e : *this) e *= x;\n            return *this;\n\
    \        }\n        FPS& operator/=(FPS g) {\n            const int fd = normalize(),\
    \ gd = g.normalize();\n            assert(gd >= 0);\n            if (fd < gd)\
    \ { this->clear(); return *this; }\n            if (gd == 0) return *this *= g.unsafe_get(0).inv();\n\
    \            static constexpr int THRESHOLD_NAIVE_POLY_QUOTIENT = 256;\n     \
    \       if (gd <= THRESHOLD_NAIVE_POLY_QUOTIENT) {\n                *this = std::move(naive_div_inplace(std::move(g),\
    \ gd).first);\n                return *this;\n            }\n            std::reverse(this->begin(),\
    \ this->end()), std::reverse(g.begin(), g.end());\n            const int k = fd\
    \ - gd;\n            *this *= g.inv_inplace(k), this->resize(k + 1);\n       \
    \     std::reverse(this->begin(), this->end());\n            return *this;\n \
    \       }\n        FPS& operator%=(FPS g) {\n            int fd = normalize(),\
    \ gd = g.normalize();\n            assert(gd >= 0);\n            if (fd < gd)\
    \ return *this;\n            if (gd == 0) { this->clear(); return *this; }\n \
    \           static constexpr int THRESHOLD_NAIVE_REMAINDER = 256;\n          \
    \  if (gd <= THRESHOLD_NAIVE_REMAINDER) return naive_div_inplace(std::move(g),\
    \ gd).second;\n            *this -= g * (*this / g);\n            return pre_inplace(gd\
    \ - 1);\n        }\n        FPS& operator<<=(const int shamt) {\n            this->insert(this->begin(),\
    \ shamt, 0);\n            return *this;\n        }\n        FPS& operator>>=(const\
    \ int shamt) {\n            if (shamt > size()) this->clear();\n            else\
    \ this->erase(this->begin(), this->begin() + shamt);\n            return *this;\n\
    \        }\n\n        friend FPS operator+(FPS f, const FPS& g) { f += g; return\
    \ f; }\n        friend FPS operator+(FPS f, const mint x) { f += x; return f;\
    \ }\n        friend FPS operator-(FPS f, const FPS& g) { f -= g; return f; }\n\
    \        friend FPS operator-(FPS f, const mint x) { f -= x; return f; }\n   \
    \     friend FPS operator*(FPS f, const FPS& g) { f *= g; return f; }\n      \
    \  friend FPS operator*(FPS f, const mint x) { f *= x; return f; }\n        friend\
    \ FPS operator/(FPS f, const FPS& g) { f /= g; return f; }\n        friend FPS\
    \ operator%(FPS f, const FPS& g) { f %= g; return f; }\n        friend FPS operator*(const\
    \ mint x, FPS f) { f *= x; return f; }\n        friend FPS operator<<(FPS f, const\
    \ int shamt) { f <<= shamt; return f; }\n        friend FPS operator>>(FPS f,\
    \ const int shamt) { f >>= shamt; return f; }\n\n        friend bool operator==(const\
    \ FPS& f, const FPS& g) {\n            int n = f.size(), m = g.size();\n     \
    \       if (n < m) return g == f;\n            for (int i = 0; i < m; ++i) if\
    \ (f.unsafe_get(i) != g.unsafe_get(i)) return false;\n            for (int i =\
    \ m; i < n; ++i) if (f.unsafe_get(i) != 0) return false;\n            return true;\n\
    \        }\n\n        FPS& diff_inplace() {\n            if (this->size() == 0)\
    \ return *this;\n            for (int i = 1; i <= deg(); ++i) unsafe_get(i - 1)\
    \ = unsafe_get(i) * i;\n            this->pop_back();\n            return *this;\n\
    \        }\n        FPS& intg_inplace() {\n            int d = deg();\n      \
    \      ensure_deg(d + 1);\n            for (int i = d; i >= 0; --i) unsafe_get(i\
    \ + 1) = unsafe_get(i) * invs[i + 1];\n            unsafe_get(0) = 0;\n      \
    \      return *this;\n        }\n        FPS& inv_inplace(const int max_deg) {\n\
    \            if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(), this->end()).inv(max_deg);\n\
    \            FPS res{ unsafe_get(0).inv() };\n            for (int k = 1; k <=\
    \ max_deg; k *= 2) {\n                FPS tmp(this->pre(k * 2) * (res * res));\n\
    \                res *= 2, res -= tmp.pre_inplace(2 * k);\n            }\n   \
    \         return *this = std::move(res), pre_inplace(max_deg);\n        }\n  \
    \      FPS& log_inplace(const int max_deg) {\n            if (max_deg <= 60) return\
    \ *this = FPSNaive<mint>(this->begin(), this->end()).log(max_deg);\n         \
    \   FPS f_inv = inv(max_deg);\n            diff_inplace(), *this *= f_inv, pre_inplace(max_deg\
    \ - 1), intg_inplace();\n            return *this;\n        }\n        FPS& exp_inplace(const\
    \ int max_deg) {\n            if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(),\
    \ this->end()).exp(max_deg);\n            FPS res{ 1 };\n            for (int\
    \ k = 1; k <= max_deg; k *= 2) res *= ++(pre(k * 2) - res.log(k * 2)), res.pre_inplace(k\
    \ * 2);\n            return *this = std::move(res), pre_inplace(max_deg);\n  \
    \      }\n        FPS& pow_inplace(const long long k, const int max_deg) {\n \
    \           if (max_deg <= 60) return *this = FPSNaive<mint>(this->begin(), this->end()).pow(k,\
    \ max_deg);\n            int tlz = 0;\n            while (tlz <= deg() and unsafe_get(tlz)\
    \ == 0) ++tlz;\n            if (tlz * k > max_deg) { this->clear(); return *this;\
    \ }\n            *this >>= tlz;\n            mint base = (*this)[0];\n       \
    \     *this *= base.inv(), log_inplace(max_deg), *this *= k, exp_inplace(max_deg),\
    \ *this *= base.pow(k);\n            return *this <<= tlz * k, pre_inplace(max_deg);\n\
    \        }\n        FPS diff() const { FPS f{ *this }; f.diff_inplace(); return\
    \ f; }\n        FPS intg() const { FPS f{ *this }; f.intg_inplace(); return f;\
    \ }\n        FPS inv(const int max_deg) const { FPS f{ *this }; f.inv_inplace(max_deg);\
    \ return f; }\n        FPS log(const int max_deg) const { FPS f{ *this }; f.log_inplace(max_deg);\
    \ return f; }\n        FPS exp(const int max_deg) const { FPS f{ *this }; f.exp_inplace(max_deg);\
    \ return f; }\n        FPS pow(const long long k, const int max_deg) const { FPS\
    \ f{ *this }; f.pow_inplace(k, max_deg); return f; }\n\n        mint eval(mint\
    \ x) const {\n            mint y = 0;\n            for (int i = size() - 1; i\
    \ >= 0; --i) y = y * x + unsafe_get(i);\n            return y;\n        }\n\n\
    \    private:\n        static inline inv_mods<mint> invs;\n        static convolution_t<mint>\
    \ mult;\n        void ensure_deg(int d) { if (deg() < d) this->resize(d + 1, 0);\
    \ }\n        const mint& unsafe_get(int i) const { return std::vector<mint>::operator[](i);\
    \ }\n        mint& unsafe_get(int i) { return std::vector<mint>::operator[](i);\
    \ }\n\n        std::pair<FPS, FPS&> naive_div_inplace(FPS&& g, const int gd) {\n\
    \            const int k = deg() - gd;\n            mint head_inv = g.unsafe_get(gd).inv();\n\
    \            FPS q(k + 1);\n            for (int i = k; i >= 0; --i) {\n     \
    \           mint div = this->unsafe_get(i + gd) * head_inv;\n                q.unsafe_get(i)\
    \ = div;\n                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j)\
    \ -= div * g.unsafe_get(j);\n            }\n            return { q, pre_inplace(gd\
    \ - 1) };\n        }\n    };\n\n    template <typename mint>\n    convolution_t<mint>\
    \ FPS<mint>::mult = [](const auto&, const auto&) {\n        std::cerr << \"convolution\
    \ function is not available.\" << std::endl;\n        assert(false);\n       \
    \ return std::vector<mint>{};\n    };\n\n} // namespace suisen\n\ntemplate <typename\
    \ mint>\nauto sqrt(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{})\
    \ {\n    assert(false);\n}\ntemplate <typename mint>\nauto log(suisen::FPS<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {\n    return a.log(a.deg());\n\
    }\ntemplate <typename mint>\nauto exp(suisen::FPS<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPS<mint>{}) {\n    return a.exp(a.deg());\n}\ntemplate <typename mint,\
    \ typename T>\nauto pow(suisen::FPS<mint> a, T b) -> decltype(mint::mod(), suisen::FPS<mint>{})\
    \ {\n    return a.pow(b, a.deg());\n}\ntemplate <typename mint>\nauto inv(suisen::FPS<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {\n    return a.inv(a.deg());\n\
    }\n\n\n#line 5 \"library/polynomial/subset_sum.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <typename mint>\nstd::vector<mint> subset_sum(const int n, const std::vector<int>\
    \ &items) {\n    std::vector<int> a(n + 1, 0);\n    for (int e : items) {\n  \
    \      assert(e >= 0);\n        if (e <= n) ++a[e];\n    }\n    inv_mods<mint>\
    \ invs(n);\n    FPS<mint> log(n + 1);\n    for (int i = 1; i <= n; ++i) {\n  \
    \      if (a[i] == 0) continue;\n        for (int j = 1; i * j <= n; ++j) {\n\
    \            if (j & 1) log[i * j] += invs[j] * a[i];\n            else      \
    \ log[i * j] -= invs[j] * a[i];\n        }\n    }\n    log.exp_inplace(n), log.resize(n\
    \ + 1);\n    mint p = mint(2).pow(a[0]);\n    for (mint &e : log) e *= p;\n  \
    \  return log;\n}\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SUBSET_SUM\n#define SUISEN_SUBSET_SUM\n\n#include \"library/polynomial/fps.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename mint>\nstd::vector<mint> subset_sum(const\
    \ int n, const std::vector<int> &items) {\n    std::vector<int> a(n + 1, 0);\n\
    \    for (int e : items) {\n        assert(e >= 0);\n        if (e <= n) ++a[e];\n\
    \    }\n    inv_mods<mint> invs(n);\n    FPS<mint> log(n + 1);\n    for (int i\
    \ = 1; i <= n; ++i) {\n        if (a[i] == 0) continue;\n        for (int j =\
    \ 1; i * j <= n; ++j) {\n            if (j & 1) log[i * j] += invs[j] * a[i];\n\
    \            else       log[i * j] -= invs[j] * a[i];\n        }\n    }\n    log.exp_inplace(n),\
    \ log.resize(n + 1);\n    mint p = mint(2).pow(a[0]);\n    for (mint &e : log)\
    \ e *= p;\n    return log;\n}\n} // namespace suisen\n\n#endif // SUISEN_SUBSET_SUM\n"
  dependsOn:
  - library/polynomial/fps.hpp
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/polynomial/subset_sum.hpp
  requiredBy: []
  timestamp: '2022-06-04 19:41:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/subset_sum/p_subset_sum.test.cpp
documentation_of: library/polynomial/subset_sum.hpp
layout: document
title: Subset Sum
---
## Subset Sum