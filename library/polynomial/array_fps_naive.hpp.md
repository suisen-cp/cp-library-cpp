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
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/array_subset_convolution.hpp
    title: Array Subset Convolution
  - icon: ':heavy_check_mark:'
    path: library/math/array_sps.hpp
    title: Array Sps
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/array_sps/abc213_g.test.cpp
    title: test/src/math/array_sps/abc213_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/array_sps/abc236_h.test.cpp
    title: test/src/math/array_sps/abc236_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/array_sps/abc253_h.test.cpp
    title: test/src/math/array_sps/abc253_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/array_sps/abc253_h_2.test.cpp
    title: test/src/math/array_sps/abc253_h_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/array_sps/arc105_f.test.cpp
    title: test/src/math/array_sps/arc105_f.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/array_fps_naive.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cmath>\n#include <limits>\n#include <type_traits>\n#include\
    \ <array>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 6 \"\
    library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n// ! utility\ntemplate\
    \ <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
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
    } // namespace suisen\n\n\n#line 11 \"library/polynomial/array_fps_naive.hpp\"\
    \n\n#line 1 \"library/math/modint_extension.hpp\"\n\n\n\n#line 5 \"library/math/modint_extension.hpp\"\
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
    library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen {\ntemplate\
    \ <typename mint>\nclass inv_mods {\n    public:\n        inv_mods() {}\n    \
    \    inv_mods(int n) { ensure(n); }\n        const mint& operator[](int i) const\
    \ {\n            ensure(i);\n            return invs[i];\n        }\n        static\
    \ void ensure(int n) {\n            int sz = invs.size();\n            if (sz\
    \ < 2) invs = {0, 1}, sz = 2;\n            if (sz < n + 1) {\n               \
    \ invs.resize(n + 1);\n                for (int i = sz; i <= n; ++i) invs[i] =\
    \ mint(mod - mod / i) * invs[mod % i];\n            }\n        }\n    private:\n\
    \        static std::vector<mint> invs;\n        static constexpr int mod = mint::mod();\n\
    };\ntemplate <typename mint>\nstd::vector<mint> inv_mods<mint>::invs{};\n}\n\n\
    \n#line 14 \"library/polynomial/array_fps_naive.hpp\"\n\nnamespace suisen {\n\
    \    template <typename T, std::size_t N>\n    struct ArrayFPSNaive : std::array<T,\
    \ N> {\n        static constexpr int SIZE = N;\n        static constexpr int DEG\
    \ = SIZE - 1;\n\n        using value_type = T;\n        using element_type = rec_value_type_t<T>;\n\
    \n        ArrayFPSNaive() {\n            this->fill(value_type{ 0 });\n      \
    \  }\n        ArrayFPSNaive(const std::initializer_list<value_type> l) : ArrayFPSNaive()\
    \ {\n            std::copy(l.begin(), l.end(), this->begin());\n        }\n\n\
    \        ArrayFPSNaive operator+() const {\n            return ArrayFPSNaive(*this);\n\
    \        }\n        ArrayFPSNaive operator-() const {\n            ArrayFPSNaive\
    \ f(*this);\n            for (auto& e : f) e = -e;\n            return f;\n  \
    \      }\n        ArrayFPSNaive& operator++() { return ++(*this)[0], * this; }\n\
    \        ArrayFPSNaive& operator--() { return --(*this)[0], * this; }\n      \
    \  ArrayFPSNaive& operator+=(const value_type x) { return (*this)[0] += x, *this;\
    \ }\n        ArrayFPSNaive& operator-=(const value_type x) { return (*this)[0]\
    \ -= x, *this; }\n        ArrayFPSNaive& operator+=(const ArrayFPSNaive& g) {\n\
    \            for (int i = 0; i < SIZE; ++i) (*this)[i] += g[i];\n            return\
    \ *this;\n        }\n        ArrayFPSNaive& operator-=(const ArrayFPSNaive& g)\
    \ {\n            for (int i = 0; i < SIZE; ++i) (*this)[i] -= g[i];\n        \
    \    return *this;\n        }\n        ArrayFPSNaive& operator*=(const ArrayFPSNaive&\
    \ g) { return *this = *this * g; }\n        ArrayFPSNaive& operator*=(const value_type\
    \ x) {\n            for (auto& e : *this) e *= x;\n            return *this;\n\
    \        }\n        ArrayFPSNaive& operator/=(const ArrayFPSNaive& g) { return\
    \ *this = *this / g; }\n        ArrayFPSNaive& operator%=(const ArrayFPSNaive&\
    \ g) { return *this = *this % g; }\n        ArrayFPSNaive& operator<<=(int shamt)\
    \ {\n            shamt = std::min(shamt, SIZE);\n            for (int i = SIZE\
    \ - 1; i >= shamt; --i) std::swap((*this)[i], (*this)[i - shamt]);\n         \
    \   std::fill(this->begin(), this->begin() + shamt, value_type{ 0 });\n      \
    \      return *this;\n        }\n        ArrayFPSNaive& operator>>=(int shamt)\
    \ {\n            shamt = std::min(shamt, SIZE);\n            for (int i = 0; i\
    \ < SIZE - shamt; ++i) std::swap((*this)[i], (*this)[i + shamt]);\n          \
    \  std::fill(this->begin() + (SIZE - shamt), this->end(), value_type{ 0 });\n\
    \            return *this;\n        }\n\n        friend ArrayFPSNaive operator+(ArrayFPSNaive\
    \ f, const ArrayFPSNaive& g) { f += g; return f; }\n        friend ArrayFPSNaive\
    \ operator+(ArrayFPSNaive f, const value_type& x) { f += x; return f; }\n    \
    \    friend ArrayFPSNaive operator-(ArrayFPSNaive f, const ArrayFPSNaive& g) {\
    \ f -= g; return f; }\n        friend ArrayFPSNaive operator-(ArrayFPSNaive f,\
    \ const value_type& x) { f -= x; return f; }\n        friend ArrayFPSNaive operator*(const\
    \ ArrayFPSNaive& f, const ArrayFPSNaive& g) {\n            ArrayFPSNaive h;\n\
    \            for (int i = 0; i < SIZE; ++i) for (int j = 0; i + j < SIZE; ++j)\
    \ h[i + j] += f[i] * g[j];\n            return h;\n        }\n        friend ArrayFPSNaive\
    \ operator*(ArrayFPSNaive f, const value_type& x) { f *= x; return f; }\n    \
    \    friend ArrayFPSNaive operator/(ArrayFPSNaive f, ArrayFPSNaive g) { return\
    \ std::move(div_mod(std::move(f), std::move(g)).first); }\n        friend ArrayFPSNaive\
    \ operator%(ArrayFPSNaive f, ArrayFPSNaive g) { return std::move(div_mod(std::move(f),\
    \ std::move(g)).second); }\n        friend ArrayFPSNaive operator*(const value_type\
    \ x, ArrayFPSNaive f) { f *= x; return f; }\n        friend ArrayFPSNaive operator<<(ArrayFPSNaive\
    \ f, const int shamt) { f <<= shamt; return f; }\n        friend ArrayFPSNaive\
    \ operator>>(ArrayFPSNaive f, const int shamt) { f >>= shamt; return f; }\n\n\
    \        friend std::pair<ArrayFPSNaive, ArrayFPSNaive> div_mod(ArrayFPSNaive\
    \ f, const ArrayFPSNaive& g) {\n            int fd = DEG, gd = DEG;\n        \
    \    while (fd >= 0 and f[fd] == value_type{ 0 }) --fd;\n            while (gd\
    \ >= 0 and g[gd] == value_type{ 0 }) --gd;\n            assert(gd >= 0);\n   \
    \         if (fd < gd) return { ArrayFPSNaive{}, f };\n            if (gd == 0)\
    \ return { f *= g[0].inv(), ArrayFPSNaive{} };\n            const int k = fd -\
    \ gd;\n            value_type head_inv = g[gd].inv();\n            ArrayFPSNaive\
    \ q;\n            for (int i = k; i >= 0; --i) {\n                value_type div\
    \ = f[i + gd] * head_inv;\n                q[i] = div;\n                for (int\
    \ j = 0; j <= gd; ++j) f[i + j] -= div * g[j];\n            }\n            std::fill(f.begin()\
    \ + gd, f.end(), value_type{ 0 });\n            return { std::move(q), std::move(f)\
    \ };\n        }\n\n        ArrayFPSNaive mul(const ArrayFPSNaive& g) const {\n\
    \            return (*this) * g;\n        }\n        ArrayFPSNaive diff() const\
    \ {\n            ArrayFPSNaive g;\n            for (int i = 1; i <= DEG; ++i)\
    \ g[i - 1] = (*this)[i] * i;\n            g[DEG] = 0;\n            return g;\n\
    \        }\n        ArrayFPSNaive intg() const {\n            ArrayFPSNaive g;\n\
    \            for (int i = 0; i < DEG; ++i) g[i + 1] = (*this)[i] * invs[i + 1];\n\
    \            return g;\n        }\n        ArrayFPSNaive inv() const {\n     \
    \       ArrayFPSNaive g;\n            const value_type inv_f0 = ::inv((*this)[0]);\n\
    \            g[0] = inv_f0;\n            for (int i = 1; i <= DEG; ++i) {\n  \
    \              for (int j = 1; j <= i; ++j) g[i] -= g[i - j] * (*this)[j];\n \
    \               g[i] *= inv_f0;\n            }\n            return g;\n      \
    \  }\n        ArrayFPSNaive exp() const {\n            assert((*this)[0] == value_type{\
    \ 0 });\n            ArrayFPSNaive g;\n            g[0] = value_type{ 1 };\n \
    \           for (int i = 1; i <= DEG; ++i) {\n                for (int j = 1;\
    \ j <= i; ++j) g[i] += j * g[i - j] * (*this)[j];\n                g[i] *= invs[i];\n\
    \            }\n            return g;\n        }\n        ArrayFPSNaive log()\
    \ const {\n            assert((*this)[0] == value_type{ 1 });\n            ArrayFPSNaive\
    \ g;\n            g[0] = value_type{ 0 };\n            for (int i = 1; i <= DEG;\
    \ ++i) {\n                g[i] = i * (*this)[i];\n                for (int j =\
    \ 1; j < i; ++j) g[i] -= (i - j) * g[i - j] * (*this)[j];\n                g[i]\
    \ *= invs[i];\n            }\n            return g;\n        }\n        ArrayFPSNaive\
    \ pow(const long long k) const {\n            if (k == 0) {\n                ArrayFPSNaive\
    \ g;\n                g[0] = 1;\n                return g;\n            }\n  \
    \          int z = 0;\n            while (z < SIZE and (*this)[z] == value_type{\
    \ 0 }) ++z;\n            if (z >= DEG / k + 1) return ArrayFPSNaive{};\n     \
    \       const int d = DEG - z * k;\n            const int bf = z, bg = z * k;\n\
    \n            ArrayFPSNaive g;\n            const value_type inv_f0 = ::inv((*this)[bf]);\n\
    \            g[bg] = (*this)[bf].pow(k);\n            for (int i = 1; i <= d;\
    \ ++i) {\n                for (int j = 1; j <= i; ++j) g[bg + i] += (element_type{\
    \ k } * j - (i - j)) * g[bg + i - j] * (*this)[bf + j];\n                g[bg\
    \ + i] *= inv_f0 * invs[i];\n            }\n            return g;\n        }\n\
    \n        ArrayFPSNaive sqrt() const {\n            int dl = 0;\n            while\
    \ (dl < SIZE and (*this)[dl] == value_type{ 0 }) ++dl;\n            if (dl ==\
    \ SIZE) return ArrayFPSNaive{};\n            if (dl & 1) assert(false);\n\n  \
    \          const int d = DEG - dl / 2;\n            const int bf = dl, bg = bf\
    \ / 2;\n\n            ArrayFPSNaive g;\n            g[bg] = ::sqrt((*this)[bf]);\n\
    \            value_type inv_2g0 = ::inv(2 * g[bg]);\n            for (int i =\
    \ 1; i <= d; ++i) {\n                g[bg + i] = (*this)[bf + i];\n          \
    \      for (int j = 1; j < i; ++j) g[bg + i] -= g[bg + j] * g[bg + i - j];\n \
    \               g[bg + i] *= inv_2g0;\n            }\n            return g;\n\
    \        }\n\n        value_type eval(value_type x) const {\n            value_type\
    \ y = 0;\n            for (int i = DEG; i >= 0; --i) y = y * x + (*this)[i];\n\
    \            return y;\n        }\n\n    private:\n        static inline inv_mods<element_type>\
    \ invs;\n    };\n} // namespace suisen\n\ntemplate <typename mint, std::size_t\
    \ N>\nauto sqrt(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint,\
    \ N>{}) {\n    return a.sqrt();\n}\ntemplate <typename mint, std::size_t N>\n\
    auto log(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint,\
    \ N>{}) {\n    return a.log();\n}\ntemplate <typename mint, std::size_t N>\nauto\
    \ exp(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint,\
    \ N>{}) {\n    return a.exp();\n}\ntemplate <typename mint, std::size_t N, typename\
    \ T>\nauto pow(suisen::ArrayFPSNaive<mint, N> a, const T& b) -> decltype(mint::mod(),\
    \ suisen::ArrayFPSNaive<mint, N>{}) {\n    return a.pow(b);\n}\ntemplate <typename\
    \ mint, std::size_t N>\nauto inv(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(),\
    \ suisen::ArrayFPSNaive<mint, N>{}) {\n    return a.inv();\n}\n\n\n"
  code: "#ifndef SUISEN_ARRAY_FPS_NAIVE\n#define SUISEN_ARRAY_FPS_NAIVE\n\n#include\
    \ <cassert>\n#include <cmath>\n#include <limits>\n#include <type_traits>\n#include\
    \ <array>\n\n#include \"library/type_traits/type_traits.hpp\"\n\n#include \"library/math/modint_extension.hpp\"\
    \n#include \"library/math/inv_mods.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T, std::size_t N>\n    struct ArrayFPSNaive : std::array<T, N> {\n        static\
    \ constexpr int SIZE = N;\n        static constexpr int DEG = SIZE - 1;\n\n  \
    \      using value_type = T;\n        using element_type = rec_value_type_t<T>;\n\
    \n        ArrayFPSNaive() {\n            this->fill(value_type{ 0 });\n      \
    \  }\n        ArrayFPSNaive(const std::initializer_list<value_type> l) : ArrayFPSNaive()\
    \ {\n            std::copy(l.begin(), l.end(), this->begin());\n        }\n\n\
    \        ArrayFPSNaive operator+() const {\n            return ArrayFPSNaive(*this);\n\
    \        }\n        ArrayFPSNaive operator-() const {\n            ArrayFPSNaive\
    \ f(*this);\n            for (auto& e : f) e = -e;\n            return f;\n  \
    \      }\n        ArrayFPSNaive& operator++() { return ++(*this)[0], * this; }\n\
    \        ArrayFPSNaive& operator--() { return --(*this)[0], * this; }\n      \
    \  ArrayFPSNaive& operator+=(const value_type x) { return (*this)[0] += x, *this;\
    \ }\n        ArrayFPSNaive& operator-=(const value_type x) { return (*this)[0]\
    \ -= x, *this; }\n        ArrayFPSNaive& operator+=(const ArrayFPSNaive& g) {\n\
    \            for (int i = 0; i < SIZE; ++i) (*this)[i] += g[i];\n            return\
    \ *this;\n        }\n        ArrayFPSNaive& operator-=(const ArrayFPSNaive& g)\
    \ {\n            for (int i = 0; i < SIZE; ++i) (*this)[i] -= g[i];\n        \
    \    return *this;\n        }\n        ArrayFPSNaive& operator*=(const ArrayFPSNaive&\
    \ g) { return *this = *this * g; }\n        ArrayFPSNaive& operator*=(const value_type\
    \ x) {\n            for (auto& e : *this) e *= x;\n            return *this;\n\
    \        }\n        ArrayFPSNaive& operator/=(const ArrayFPSNaive& g) { return\
    \ *this = *this / g; }\n        ArrayFPSNaive& operator%=(const ArrayFPSNaive&\
    \ g) { return *this = *this % g; }\n        ArrayFPSNaive& operator<<=(int shamt)\
    \ {\n            shamt = std::min(shamt, SIZE);\n            for (int i = SIZE\
    \ - 1; i >= shamt; --i) std::swap((*this)[i], (*this)[i - shamt]);\n         \
    \   std::fill(this->begin(), this->begin() + shamt, value_type{ 0 });\n      \
    \      return *this;\n        }\n        ArrayFPSNaive& operator>>=(int shamt)\
    \ {\n            shamt = std::min(shamt, SIZE);\n            for (int i = 0; i\
    \ < SIZE - shamt; ++i) std::swap((*this)[i], (*this)[i + shamt]);\n          \
    \  std::fill(this->begin() + (SIZE - shamt), this->end(), value_type{ 0 });\n\
    \            return *this;\n        }\n\n        friend ArrayFPSNaive operator+(ArrayFPSNaive\
    \ f, const ArrayFPSNaive& g) { f += g; return f; }\n        friend ArrayFPSNaive\
    \ operator+(ArrayFPSNaive f, const value_type& x) { f += x; return f; }\n    \
    \    friend ArrayFPSNaive operator-(ArrayFPSNaive f, const ArrayFPSNaive& g) {\
    \ f -= g; return f; }\n        friend ArrayFPSNaive operator-(ArrayFPSNaive f,\
    \ const value_type& x) { f -= x; return f; }\n        friend ArrayFPSNaive operator*(const\
    \ ArrayFPSNaive& f, const ArrayFPSNaive& g) {\n            ArrayFPSNaive h;\n\
    \            for (int i = 0; i < SIZE; ++i) for (int j = 0; i + j < SIZE; ++j)\
    \ h[i + j] += f[i] * g[j];\n            return h;\n        }\n        friend ArrayFPSNaive\
    \ operator*(ArrayFPSNaive f, const value_type& x) { f *= x; return f; }\n    \
    \    friend ArrayFPSNaive operator/(ArrayFPSNaive f, ArrayFPSNaive g) { return\
    \ std::move(div_mod(std::move(f), std::move(g)).first); }\n        friend ArrayFPSNaive\
    \ operator%(ArrayFPSNaive f, ArrayFPSNaive g) { return std::move(div_mod(std::move(f),\
    \ std::move(g)).second); }\n        friend ArrayFPSNaive operator*(const value_type\
    \ x, ArrayFPSNaive f) { f *= x; return f; }\n        friend ArrayFPSNaive operator<<(ArrayFPSNaive\
    \ f, const int shamt) { f <<= shamt; return f; }\n        friend ArrayFPSNaive\
    \ operator>>(ArrayFPSNaive f, const int shamt) { f >>= shamt; return f; }\n\n\
    \        friend std::pair<ArrayFPSNaive, ArrayFPSNaive> div_mod(ArrayFPSNaive\
    \ f, const ArrayFPSNaive& g) {\n            int fd = DEG, gd = DEG;\n        \
    \    while (fd >= 0 and f[fd] == value_type{ 0 }) --fd;\n            while (gd\
    \ >= 0 and g[gd] == value_type{ 0 }) --gd;\n            assert(gd >= 0);\n   \
    \         if (fd < gd) return { ArrayFPSNaive{}, f };\n            if (gd == 0)\
    \ return { f *= g[0].inv(), ArrayFPSNaive{} };\n            const int k = fd -\
    \ gd;\n            value_type head_inv = g[gd].inv();\n            ArrayFPSNaive\
    \ q;\n            for (int i = k; i >= 0; --i) {\n                value_type div\
    \ = f[i + gd] * head_inv;\n                q[i] = div;\n                for (int\
    \ j = 0; j <= gd; ++j) f[i + j] -= div * g[j];\n            }\n            std::fill(f.begin()\
    \ + gd, f.end(), value_type{ 0 });\n            return { std::move(q), std::move(f)\
    \ };\n        }\n\n        ArrayFPSNaive mul(const ArrayFPSNaive& g) const {\n\
    \            return (*this) * g;\n        }\n        ArrayFPSNaive diff() const\
    \ {\n            ArrayFPSNaive g;\n            for (int i = 1; i <= DEG; ++i)\
    \ g[i - 1] = (*this)[i] * i;\n            g[DEG] = 0;\n            return g;\n\
    \        }\n        ArrayFPSNaive intg() const {\n            ArrayFPSNaive g;\n\
    \            for (int i = 0; i < DEG; ++i) g[i + 1] = (*this)[i] * invs[i + 1];\n\
    \            return g;\n        }\n        ArrayFPSNaive inv() const {\n     \
    \       ArrayFPSNaive g;\n            const value_type inv_f0 = ::inv((*this)[0]);\n\
    \            g[0] = inv_f0;\n            for (int i = 1; i <= DEG; ++i) {\n  \
    \              for (int j = 1; j <= i; ++j) g[i] -= g[i - j] * (*this)[j];\n \
    \               g[i] *= inv_f0;\n            }\n            return g;\n      \
    \  }\n        ArrayFPSNaive exp() const {\n            assert((*this)[0] == value_type{\
    \ 0 });\n            ArrayFPSNaive g;\n            g[0] = value_type{ 1 };\n \
    \           for (int i = 1; i <= DEG; ++i) {\n                for (int j = 1;\
    \ j <= i; ++j) g[i] += j * g[i - j] * (*this)[j];\n                g[i] *= invs[i];\n\
    \            }\n            return g;\n        }\n        ArrayFPSNaive log()\
    \ const {\n            assert((*this)[0] == value_type{ 1 });\n            ArrayFPSNaive\
    \ g;\n            g[0] = value_type{ 0 };\n            for (int i = 1; i <= DEG;\
    \ ++i) {\n                g[i] = i * (*this)[i];\n                for (int j =\
    \ 1; j < i; ++j) g[i] -= (i - j) * g[i - j] * (*this)[j];\n                g[i]\
    \ *= invs[i];\n            }\n            return g;\n        }\n        ArrayFPSNaive\
    \ pow(const long long k) const {\n            if (k == 0) {\n                ArrayFPSNaive\
    \ g;\n                g[0] = 1;\n                return g;\n            }\n  \
    \          int z = 0;\n            while (z < SIZE and (*this)[z] == value_type{\
    \ 0 }) ++z;\n            if (z >= DEG / k + 1) return ArrayFPSNaive{};\n     \
    \       const int d = DEG - z * k;\n            const int bf = z, bg = z * k;\n\
    \n            ArrayFPSNaive g;\n            const value_type inv_f0 = ::inv((*this)[bf]);\n\
    \            g[bg] = (*this)[bf].pow(k);\n            for (int i = 1; i <= d;\
    \ ++i) {\n                for (int j = 1; j <= i; ++j) g[bg + i] += (element_type{\
    \ k } * j - (i - j)) * g[bg + i - j] * (*this)[bf + j];\n                g[bg\
    \ + i] *= inv_f0 * invs[i];\n            }\n            return g;\n        }\n\
    \n        ArrayFPSNaive sqrt() const {\n            int dl = 0;\n            while\
    \ (dl < SIZE and (*this)[dl] == value_type{ 0 }) ++dl;\n            if (dl ==\
    \ SIZE) return ArrayFPSNaive{};\n            if (dl & 1) assert(false);\n\n  \
    \          const int d = DEG - dl / 2;\n            const int bf = dl, bg = bf\
    \ / 2;\n\n            ArrayFPSNaive g;\n            g[bg] = ::sqrt((*this)[bf]);\n\
    \            value_type inv_2g0 = ::inv(2 * g[bg]);\n            for (int i =\
    \ 1; i <= d; ++i) {\n                g[bg + i] = (*this)[bf + i];\n          \
    \      for (int j = 1; j < i; ++j) g[bg + i] -= g[bg + j] * g[bg + i - j];\n \
    \               g[bg + i] *= inv_2g0;\n            }\n            return g;\n\
    \        }\n\n        value_type eval(value_type x) const {\n            value_type\
    \ y = 0;\n            for (int i = DEG; i >= 0; --i) y = y * x + (*this)[i];\n\
    \            return y;\n        }\n\n    private:\n        static inline inv_mods<element_type>\
    \ invs;\n    };\n} // namespace suisen\n\ntemplate <typename mint, std::size_t\
    \ N>\nauto sqrt(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint,\
    \ N>{}) {\n    return a.sqrt();\n}\ntemplate <typename mint, std::size_t N>\n\
    auto log(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint,\
    \ N>{}) {\n    return a.log();\n}\ntemplate <typename mint, std::size_t N>\nauto\
    \ exp(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(), suisen::ArrayFPSNaive<mint,\
    \ N>{}) {\n    return a.exp();\n}\ntemplate <typename mint, std::size_t N, typename\
    \ T>\nauto pow(suisen::ArrayFPSNaive<mint, N> a, const T& b) -> decltype(mint::mod(),\
    \ suisen::ArrayFPSNaive<mint, N>{}) {\n    return a.pow(b);\n}\ntemplate <typename\
    \ mint, std::size_t N>\nauto inv(suisen::ArrayFPSNaive<mint, N> a) -> decltype(mint::mod(),\
    \ suisen::ArrayFPSNaive<mint, N>{}) {\n    return a.inv();\n}\n\n#endif // SUISEN_ARRAY_FPS_NAIVE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/polynomial/array_fps_naive.hpp
  requiredBy:
  - library/convolution/array_subset_convolution.hpp
  - library/math/array_sps.hpp
  timestamp: '2022-07-21 04:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/array_sps/arc105_f.test.cpp
  - test/src/math/array_sps/abc253_h.test.cpp
  - test/src/math/array_sps/abc236_h.test.cpp
  - test/src/math/array_sps/abc213_g.test.cpp
  - test/src/math/array_sps/abc253_h_2.test.cpp
documentation_of: library/polynomial/array_fps_naive.hpp
layout: document
title: Array Fps Naive
---
## Array Fps Naive