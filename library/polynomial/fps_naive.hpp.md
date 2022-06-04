---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/polynomial_eval_multipoint_eval.hpp
    title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\
      \u306E\u8A55\u4FA1 (\u591A\u70B9\u8A55\u4FA1\u7248)"
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':question:'
    path: library/math/product_of_differences.hpp
    title: Product Of Differences
  - icon: ':heavy_check_mark:'
    path: library/math/sps.hpp
    title: Set Power Series
  - icon: ':heavy_check_mark:'
    path: library/polynomial/bostan_mori.hpp
    title: Bostan Mori
  - icon: ':question:'
    path: library/polynomial/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':question:'
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  - icon: ':x:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
  - icon: ':question:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
  - icon: ':x:'
    path: library/polynomial/polynomial_interpolation.hpp
    title: "\u88DC\u9593\u591A\u9805\u5F0F"
  - icon: ':x:'
    path: library/polynomial/polynomial_taylor_shift.hpp
    title: Polynomial Taylor Shift
  - icon: ':x:'
    path: library/polynomial/subset_sum.hpp
    title: Subset Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/product_of_differences/yuki1938.test.cpp
    title: test/src/math/product_of_differences/yuki1938.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc213_g.test.cpp
    title: test/src/math/sps/abc213_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc236_h.test.cpp
    title: test/src/math/sps/abc236_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc253_h.test.cpp
    title: test/src/math/sps/abc253_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc253_h_2.test.cpp
    title: test/src/math/sps/abc253_h_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/arc105_f.test.cpp
    title: test/src/math/sps/arc105_f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/bernoulli_number.test.cpp
    title: test/src/polynomial/common_sequences/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
    title: test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/partition_function.test.cpp
    title: test/src/polynomial/common_sequences/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/stirling_number1.test.cpp
    title: test/src/polynomial/common_sequences/stirling_number1.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/stirling_number2.test.cpp
    title: test/src/polynomial/common_sequences/stirling_number2.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/fps/division_of_polynomials.test.cpp
    title: test/src/polynomial/fps/division_of_polynomials.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/fps/exp_of_fps.test.cpp
    title: test/src/polynomial/fps/exp_of_fps.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/fps/inv_of_fps.test.cpp
    title: test/src/polynomial/fps/inv_of_fps.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/fps/log_of_fps.test.cpp
    title: test/src/polynomial/fps/log_of_fps.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/fps/pow_of_fps.test.cpp
    title: test/src/polynomial/fps/pow_of_fps.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/fps_naive/abc245_d.test.cpp
    title: test/src/polynomial/fps_naive/abc245_d.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
    title: test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
    title: test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
    title: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/fps_naive.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cmath>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
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
    }\n\n\n\n"
  code: "#ifndef SUISEN_FPS_NAIVE_OPS\n#define SUISEN_FPS_NAIVE_OPS\n\n#include <cassert>\n\
    #include <cmath>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
    \n#include \"library/type_traits/type_traits.hpp\"\n\n#include \"library/math/modint_extension.hpp\"\
    \n#include \"library/math/inv_mods.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T>\n    struct FPSNaive : std::vector<T> {\n        static inline int MAX_DEG\
    \ = std::numeric_limits<int>::max() / 2;\n\n        using value_type = T;\n  \
    \      using element_type = rec_value_type_t<T>;\n        using std::vector<value_type>::vector;\n\
    \n        FPSNaive(const std::initializer_list<value_type> l) : std::vector<value_type>::vector(l)\
    \ {}\n\n        static void set_max_deg(int max_deg) {\n            FPSNaive<T>::MAX_DEG\
    \ = max_deg;\n        }\n\n        const value_type operator[](int n) const {\n\
    \            return n <= deg() ? unsafe_get(n) : value_type{ 0 };\n        }\n\
    \        value_type& operator[](int n) {\n            return ensure_deg(n), unsafe_get(n);\n\
    \        }\n\n        int size() const {\n            return std::vector<value_type>::size();\n\
    \        }\n        int deg() const {\n            return size() - 1;\n      \
    \  }\n        int normalize() {\n            while (size() and this->back() ==\
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
    }\n\n\n#endif // SUISEN_FPS_NAIVE_OPS\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/polynomial/fps_naive.hpp
  requiredBy:
  - library/convolution/subset_convolution.hpp
  - library/convolution/polynomial_eval_multipoint_eval.hpp
  - library/math/sps.hpp
  - library/math/product_of_differences.hpp
  - library/polynomial/fps.hpp
  - library/polynomial/multi_point_eval.hpp
  - library/polynomial/common_sequences.hpp
  - library/polynomial/polynomial_interpolation.hpp
  - library/polynomial/polynomial_taylor_shift.hpp
  - library/polynomial/lagrange_interpolation.hpp
  - library/polynomial/bostan_mori.hpp
  - library/polynomial/subset_sum.hpp
  timestamp: '2022-06-04 18:33:47+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/math/product_of_differences/yuki1938.test.cpp
  - test/src/math/sps/abc236_h.test.cpp
  - test/src/math/sps/arc105_f.test.cpp
  - test/src/math/sps/abc253_h_2.test.cpp
  - test/src/math/sps/abc253_h.test.cpp
  - test/src/math/sps/abc213_g.test.cpp
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - test/src/polynomial/fps_naive/abc245_d.test.cpp
  - test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/polynomial/subset_sum/p_subset_sum.test.cpp
  - test/src/polynomial/fps/exp_of_fps.test.cpp
  - test/src/polynomial/fps/log_of_fps.test.cpp
  - test/src/polynomial/fps/division_of_polynomials.test.cpp
  - test/src/polynomial/fps/inv_of_fps.test.cpp
  - test/src/polynomial/fps/pow_of_fps.test.cpp
  - test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
  - test/src/polynomial/common_sequences/stirling_number1.test.cpp
  - test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
  - test/src/polynomial/common_sequences/stirling_number2.test.cpp
  - test/src/polynomial/common_sequences/bernoulli_number.test.cpp
  - test/src/polynomial/common_sequences/partition_function.test.cpp
  - test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
documentation_of: library/polynomial/fps_naive.hpp
layout: document
title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
---
## FFT-free な形式的べき級数

積や乗法逆元 $\mathrm{inv}$，指数関数 $\exp$，対数関数 $\log$，べき乗 $\mathrm{pow}$，平方根 $\mathrm{sqrt}$ を $\Theta(N ^ 2)$ で計算する形式的べき級数ライブラリ．Set Power Series など，最大次数が十分小さいことが分かっている場合にこちらを用いることで高速化が期待できる．

FFT や NTT を必要としない点も特徴的?

## 前置き

形式的べき級数 $f$ の $i$ 次の係数を $f_i$ と書く．

## 積

$h = fg$ を満たす $h$ を求める．これは，以下のように計算される．

$$
h _ n = \sum _ {i = 0} ^ n f _ i g _ {n - i}.
$$

## FPS としての除算

$h = \dfrac{f}{g}$ を満たす $h$ を求める．ただし，$g _ 0 \neq 0$ を仮定する．$f = gh$ であるから，次のように計算される．

$$
\begin{aligned}
f _ n 
&= \sum _ {i = 0} ^ n h _ i g _ {n - i}\\
&= h _ n g _ 0 + \sum _ {i = 0} ^ {n - 1} h _ i g _ {n - i},\\
h _ n 
&= \dfrac{1}{g _ 0}\left(f _ n - \sum _ {i = 0} ^ {n - 1}h _ i g _ {n - i} \right).
\end{aligned}
$$

## $\mathrm{inv}$

$gh=1$ を満たす $h$ を求める．ただし，$g _ 0 \neq 0$ を仮定する．形式的べき級数としての除算において $f\equiv 1$ とすればよいので，次のように計算される．

$$
h _ n = \begin{cases}
\dfrac{1}{g _ 0} & \text{if } n = 0\\
\displaystyle -\dfrac{1}{g _ 0}  \sum _ {i = 0} ^ {n - 1} h _ i g _ {n - i} & \text{otherwise}
\end{cases}.
$$

## $\exp$

$g = \exp f$ を満たす $g$ を求める．ただし，$f _ 0 = 0$ を仮定する．$g' = f' g$ より，次のように計算される．

$$
\begin{aligned}
(n + 1) g _ {n + 1}
&= \sum _ {i = 0} ^ n (n - i + 1) f _ {n - i + 1} g _ i,\\
g _ n &= \begin{cases}
1 & \text{if }n = 0 \\
\dfrac{1}{n}\displaystyle\sum _ {i = 0} ^ {n - 1} (n - i) f _ {n - i} g _ i &\text{otherwise}

\end{cases}
\end{aligned}
$$

## $\log$

$g = \log f$ を満たす $g$ を求める．ただし，$f _ 0 = 1$ を仮定する．$fg'=f'$ より，次のように計算される．

$$
\begin{aligned}
\sum _ {i = 0} ^ n (i + 1) g _ {i + 1} f _ {n - i} &= (n + 1)f _ {n + 1},\\
(n + 1) f _ 0 g _ {n + 1} &= (n + 1) f _ {n + 1} - \sum _ {i = 0} ^ {n - 1}(i + 1) g _ {i + 1} f _ {n - i},\\
g _ {n + 1} &= \dfrac{1}{(n + 1) f _ 0}\left((n + 1) f _ {n + 1} - \sum _ {i = 0} ^ {n - 1}(i + 1) g _ {i + 1} f _ {n - i}\right),\\
g _ n &= \begin{cases}
0 & \text{if }n = 0\\
\displaystyle \dfrac{1}{nf_0}\left(n f _ {n} - \sum _ {i = 1} ^ {n - 1}i g _ i f _ {n - i}\right) & \text{otherwise}
\end{cases}
\end{aligned}
$$

## $\mathrm{pow}$

$g = f ^ k$ を満たす $g$ を求める．ただし，$k \gt 0$ および $f_0\neq 0$ を仮定する．$g'=kf^{k-1} f'$ の両辺に $f$ を掛けることで $fg'=kgf'$ が得られるので，以下のように計算される．

$$
\begin{aligned}
\sum _ {i = 0} ^ n (i + 1) g _ {i + 1} f _ {n - i} 
&= k\sum _ {i = 0} ^ n g _ i\cdot (n - i + 1) f _ {n - i + 1}, \\
(n+1)f_0g _ {n+1}
&= k\sum _ {i = 0} ^ n g _ i\cdot (n - i + 1) f _ {n - i + 1} - \sum _ {i = 1} ^ {n} i g _ i f _ {n - i + 1} \\
&=\sum _ {i = 0} ^ {n} (k(n-i+1)-i)g_i f _{n-i+1},\\
g _ {n + 1} &= \dfrac{1}{(n + 1) f _ 0}\sum _ {i = 0} ^ {n} (k (n - i + 1) - i) g _ i f _ {n - i + 1},\\
g _ n &= \begin{cases}
f _ 0 ^ k & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n - 1} (k (n - i) - i) g _ i f _ {n - i} & \text{otherwise}
\end{cases}
\end{aligned}
$$

$k=0$ の場合は，$g\equiv 1$ として計算される．

$k\gt 0$ かつ $f _ 0 = 0$ の場合は，$f = x ^ p \cdot f'\ (f'_0 \neq 0)$ の形に直してから $g = x ^ {pk} f'^ k$  として計算すればよい．そのような $f'$ が存在しない場合，即ち $f\equiv 0$ の場合は $g \equiv 0$ である．

## $\mathrm{sqrt}$

$g ^ 2 = f$ を満たす $g$ を $1$ つ求める (存在しても一意とは限らない)．ただし，$g _ 0 \neq 0$ および $v ^ 2 = f _ 0$ を満たす $v$ (これを $f _ 0 ^ {1 / 2}$ と書く) が存在することを仮定する．これは，以下のように計算できる．

$$
\begin{aligned}
f _ {n + 1} &= \sum _ {i = 0} ^ {n + 1} g _ i g _ {n + 1 - i},\\
2 g _ 0 g _ {n + 1} &= f _ {n + 1} - \sum _ {i = 1} ^ {n} g _ i g _ {n + 1 - i},\\
g _ n &= \begin{cases}
f _ 0 ^ {1/2} & \text{if }n = 0\\
\displaystyle \dfrac{1}{2 g _ 0}\left(f _ {n } - \sum _ {i = 1} ^ {n - 1} g _ i g _ {n - i}\right) & \text{otherwise}
\end{cases}.
\end{aligned}
$$

$f _ i \neq 0$ となる最小の $i$ が偶数であれば，上式で計算される $g$ に対して $g' = x ^ {i / 2} g$ が ${g'} ^ 2 = f$ を満たす．$i$ が奇数であれば，条件を満たす $g$ は存在しない．

## $k$ th root (__未実装__)

$g ^ k = f$ を満たす $g$ を求める．$\mathrm{pow}$ と同様の計算により，次を得る．

$$
g _ n = \begin{cases}
f _ 0 ^ {1/k} & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n-1} (k ^ {- 1} (n - i) - i) g _ i f _ {n - i} & \text{otherwise}
\end{cases}
$$

$\mathrm{pow}$ と組み合わせることで，より一般に $g = f ^ {p/q}$ を満たす $g$ を計算できる．
