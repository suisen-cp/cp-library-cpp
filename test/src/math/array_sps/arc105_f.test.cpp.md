---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/array_subset_convolution.hpp
    title: Array Subset Convolution
  - icon: ':question:'
    path: library/math/array_sps.hpp
    title: Array Sps
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':question:'
    path: library/polynomial/array_fps_naive.hpp
    title: Array Fps Naive
  - icon: ':question:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':question:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc105/tasks/arc105_f
    links:
    - https://atcoder.jp/contests/arc105/tasks/arc105_f
  bundledCode: "#line 1 \"test/src/math/array_sps/arc105_f.test.cpp\"\n#define PROBLEM\
    \ \"https://atcoder.jp/contests/arc105/tasks/arc105_f\"\n\n#include <iostream>\n\
    #include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\n#line 1\
    \ \"library/math/array_sps.hpp\"\n\n\n\n#line 1 \"library/convolution/array_subset_convolution.hpp\"\
    \n\n\n\n#line 1 \"library/polynomial/array_fps_naive.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cmath>\n#include <limits>\n#include <type_traits>\n#include <array>\n\
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
    library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen {\n \
    \   template <typename mint>\n    class inv_mods {\n    public:\n        inv_mods()\
    \ {}\n        inv_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return invs[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = invs.size();\n    \
    \        if (sz < 2) invs = { 0, 1 }, sz = 2;\n            if (sz < n + 1) {\n\
    \                invs.resize(n + 1);\n                for (int i = sz; i <= n;\
    \ ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n            }\n       \
    \ }\n    private:\n        static std::vector<mint> invs;\n        static constexpr\
    \ int mod = mint::mod();\n    };\n    template <typename mint>\n    std::vector<mint>\
    \ inv_mods<mint>::invs{};\n\n    template <typename mint>\n    std::vector<mint>\
    \ get_invs(const std::vector<mint>& vs) {\n        const int n = vs.size();\n\n\
    \        mint p = 1;\n        for (auto& e : vs) {\n            p *= e;\n    \
    \        assert(e != 0);\n        }\n        mint ip = p.inv();\n\n        std::vector<mint>\
    \ rp(n + 1);\n        rp[n] = 1;\n        for (int i = n - 1; i >= 0; --i) {\n\
    \            rp[i] = rp[i + 1] * vs[i];\n        }\n        std::vector<mint>\
    \ res(n);\n        for (int i = 0; i < n; ++i) {\n            res[i] = ip * rp[i\
    \ + 1];\n            ip *= vs[i];\n        }\n        return res;\n    }\n}\n\n\
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
    \ suisen::ArrayFPSNaive<mint, N>{}) {\n    return a.inv();\n}\n\n\n#line 1 \"\
    library/transform/subset.hpp\"\n\n\n\n#line 1 \"library/transform/kronecker_power.hpp\"\
    \n\n\n\n#line 5 \"library/transform/kronecker_power.hpp\"\n#include <utility>\n\
    #line 7 \"library/transform/kronecker_power.hpp\"\n\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    \    namespace default_operator_noref {\n        template <typename T>\n     \
    \   auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(T x, T y) -> decltype(x + y) { return x + y;\
    \ }\n        template <typename T>\n        auto sub(T x, T y) -> decltype(x -\
    \ y) { return x - y; }\n        template <typename T>\n        auto mul(T x, T\
    \ y) -> decltype(x * y) { return x * y; }\n        template <typename T>\n   \
    \     auto div(T x, T y) -> decltype(x / y) { return x / y; }\n        template\
    \ <typename T>\n        auto mod(T x, T y) -> decltype(x % y) { return x % y;\
    \ }\n        template <typename T>\n        auto neg(T x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(T x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 9 \"library/transform/kronecker_power.hpp\"\n\nnamespace suisen {\n\
    \    namespace kronecker_power_transform {\n        namespace internal {\n   \
    \         template <typename UnitTransform, typename ReferenceGetter, std::size_t...\
    \ Seq>\n            void unit_transform(UnitTransform transform, ReferenceGetter\
    \ ref_getter, std::index_sequence<Seq...>) {\n                transform(ref_getter(Seq)...);\n\
    \            }\n        }\n\n        template <typename T, std::size_t D, auto\
    \ unit_transform>\n        void kronecker_power_transform(std::vector<T> &x) {\n\
    \            const std::size_t n = x.size();\n            for (std::size_t block\
    \ = 1; block < n; block *= D) {\n                for (std::size_t l = 0; l < n;\
    \ l += D * block) {\n                    for (std::size_t offset = l; offset <\
    \ l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
    \ i) -> T& { return x[offset + i * block]; };\n                        internal::unit_transform(unit_transform,\
    \ ref_getter, std::make_index_sequence<D>());\n                    }\n       \
    \         }\n            }\n        }\n\n        template <typename T, typename\
    \ UnitTransform>\n        void kronecker_power_transform(std::vector<T> &x, const\
    \ std::size_t D, UnitTransform unit_transform) {\n            const std::size_t\
    \ n = x.size();\n            std::vector<T> work(D);\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        for (std::size_t i = 0; i\
    \ < D; ++i) work[i] = x[offset + i * block];\n                        unit_transform(work);\n\
    \                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block]\
    \ = work[i];\n                    }\n                }\n            }\n      \
    \  }\n\n        template <typename T, auto e = default_operator::zero<T>, auto\
    \ add = default_operator::add<T>, auto mul = default_operator::mul<T>>\n     \
    \   auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>>\
    \ &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(),\
    \ std::declval<T>()), void()) {\n            const std::size_t D = A.size();\n\
    \            assert(D == A[0].size());\n            auto unit_transform = [&](std::vector<T>\
    \ &x) {\n                std::vector<T> y(D, e());\n                for (std::size_t\
    \ i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {\n                 \
    \   y[i] = add(y[i], mul(A[i][j], x[j]));\n                }\n               \
    \ x.swap(y);\n            };\n            kronecker_power_transform<T>(x, D, unit_transform);\n\
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 5 \"library/transform/subset.hpp\"\
    \n\nnamespace suisen::subset_transform {\n    namespace internal {\n        template\
    \ <typename T, auto add = default_operator::add<T>>\n        void zeta_unit_transform(T\
    \ &x0, T &x1) {\n                                // 1, 0\n            x1 = add(x1,\
    \ x0);   // 1, 1\n        }\n        template <typename T, auto sub = default_operator::sub<T>>\n\
    \        void mobius_unit_transform(T &x0, T &x1) {\n                        \
    \        //  1, 0\n            x1 = sub(x1, x0);   // -1, 1\n        }\n    }\
    \ // namespace internal\n\n    using kronecker_power_transform::kronecker_power_transform;\n\
    \n    template <typename T, auto add = default_operator::add<T>>\n    void zeta(std::vector<T>\
    \ &a) {\n        kronecker_power_transform<T, 2, internal::zeta_unit_transform<T,\
    \ add>>(a);\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void mobius(std::vector<T> &a) {\n        kronecker_power_transform<T, 2,\
    \ internal::mobius_unit_transform<T, sub>>(a);\n    }\n} // namespace suisen::subset_transform\n\
    \n\n#line 6 \"library/convolution/array_subset_convolution.hpp\"\n\nnamespace\
    \ suisen::array_ranked_subset_transform {\n    template <typename T, std::size_t\
    \ N>\n    using polynomial_t = ArrayFPSNaive<T, N>;\n\n    namespace internal\
    \ {\n        template <typename T, std::size_t N>\n        std::vector<polynomial_t<T,\
    \ N>> ranked(const std::vector<T>& a) {\n            const int n = a.size();\n\
    \            assert((-n & n) == n);\n            std::vector fs(n, polynomial_t<T,\
    \ N>{});\n            for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)]\
    \ = a[i];\n            return fs;\n        }\n        template <typename T, std::size_t\
    \ N>\n        std::vector<T> deranked(const std::vector<polynomial_t<T, N>>& polys)\
    \ {\n            const int n = polys.size();\n            assert((-n & n) == n);\n\
    \            std::vector<T> a(n);\n            for (int i = 0; i < n; ++i) a[i]\
    \ = polys[i][__builtin_popcount(i)];\n            return a;\n        }\n    }\
    \ // namespace suisen::array_ranked_subset_transform::internal\n\n    template\
    \ <typename T, std::size_t N>\n    std::vector<polynomial_t<T, N>> ranked_zeta(const\
    \ std::vector<T>& a) {\n        auto ranked = internal::ranked<T, N>(a);\n   \
    \     subset_transform::zeta(ranked);\n        return ranked;\n    }\n    template\
    \ <typename T, std::size_t N>\n    std::vector<T> deranked_mobius(std::vector<polynomial_t<T,\
    \ N>>& ranked) {\n        subset_transform::mobius(ranked);\n        return internal::deranked<T,\
    \ N>(ranked);\n    }\n} // namespace suisen::array_ranked_subset_transform\n\n\
    \n#line 5 \"library/math/array_sps.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T, std::size_t N>\n    struct ArraySPS : public std::vector<T> {\n        using\
    \ base_type = std::vector<T>;\n        using value_type = typename base_type::value_type;\n\
    \        using size_type = typename base_type::size_type;\n\n        using polynomial_type\
    \ = array_ranked_subset_transform::polynomial_t<value_type, N>;\n\n        using\
    \ base_type::vector;\n\n        ArraySPS() : ArraySPS(0) {}\n        ArraySPS(size_type\
    \ n) : ArraySPS(n, value_type{ 0 }) {}\n        ArraySPS(size_type n, const value_type&\
    \ val) : ArraySPS(std::vector<value_type>(1 << n, val)) {}\n        ArraySPS(const\
    \ base_type& a) : ArraySPS(base_type(a)) {}\n        ArraySPS(base_type&& a) :\
    \ base_type(std::move(a)) {\n            const int n = this->size();\n       \
    \     assert(n == (-n & n));\n        }\n        ArraySPS(std::initializer_list<value_type>\
    \ l) : ArraySPS(base_type(l)) {}\n\n        static ArraySPS one(int n) {\n   \
    \         ArraySPS f(n, value_type{ 0 });\n            f[0] = value_type{ 1 };\n\
    \            return f;\n        }\n\n        void set_cardinality(int n) {\n \
    \           this->resize(1 << n, value_type{ 0 });\n        }\n        int cardinality()\
    \ const {\n            return __builtin_ctz(this->size());\n        }\n\n    \
    \    ArraySPS cut_lower(size_type p) const {\n            return ArraySPS(this->begin(),\
    \ this->begin() + p);\n        }\n        ArraySPS cut_upper(size_type p) const\
    \ {\n            return ArraySPS(this->begin() + p, this->begin() + p + p);\n\
    \        }\n\n        void concat(const ArraySPS& upper) {\n            assert(this->size()\
    \ == upper.size());\n            this->insert(this->end(), upper.begin(), upper.end());\n\
    \        }\n\n        ArraySPS operator+() const {\n            return *this;\n\
    \        }\n        ArraySPS operator-() const {\n            ArraySPS res(*this);\n\
    \            for (auto& e : res) e = -e;\n            return res;\n        }\n\
    \        ArraySPS& operator+=(const ArraySPS& g) {\n            for (size_type\
    \ i = 0; i < g.size(); ++i) (*this)[i] += g[i];\n            return *this;\n \
    \       }\n        ArraySPS& operator-=(const ArraySPS& g) {\n            for\
    \ (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];\n            return\
    \ *this;\n        }\n        ArraySPS& operator*=(const ArraySPS& g) {\n     \
    \       return *this = (zeta() *= g).mobius_inplace();\n        }\n        ArraySPS&\
    \ operator*=(const value_type &c) {\n            for (auto& e : *this) e *= c;\n\
    \            return *this;\n        }\n        ArraySPS& operator/=(const value_type\
    \ &c) {\n            value_type inv_c = ::inv(c);\n            for (auto& e :\
    \ *this) e *= inv_c;\n            return *this;\n        }\n        friend ArraySPS\
    \ operator+(ArraySPS f, const ArraySPS& g) { f += g; return f; }\n        friend\
    \ ArraySPS operator-(ArraySPS f, const ArraySPS& g) { f -= g; return f; }\n  \
    \      friend ArraySPS operator*(ArraySPS f, const ArraySPS& g) { f *= g; return\
    \ f; }\n        friend ArraySPS operator*(ArraySPS f, const value_type &c) { f\
    \ *= c; return f; }\n        friend ArraySPS operator*(const value_type &c, ArraySPS\
    \ f) { f *= c; return f; }\n        friend ArraySPS operator/(ArraySPS f, const\
    \ value_type &c) { f /= c; return f; }\n\n        ArraySPS inv() {\n         \
    \   return zeta().inv_inplace().mobius_inplace();\n        }\n        ArraySPS\
    \ sqrt() {\n            return zeta().sqrt_inplace().mobius_inplace();\n     \
    \   }\n        ArraySPS exp() {\n            return zeta().exp_inplace().mobius_inplace();\n\
    \        }\n        ArraySPS log() {\n            return zeta().log_inplace().mobius_inplace();\n\
    \        }\n        ArraySPS pow(long long k) {\n            return zeta().pow_inplace(k).mobius_inplace();\n\
    \        }\n\n        struct ZetaSPS : public std::vector<polynomial_type> {\n\
    \            using base_type = std::vector<polynomial_type>;\n            ZetaSPS()\
    \ = default;\n            ZetaSPS(const ArraySPS<value_type, N>& f) : base_type::vector(array_ranked_subset_transform::ranked_zeta<T,\
    \ N>(f)), _d(f.cardinality()) {}\n\n            ZetaSPS operator+() const {\n\
    \                return *this;\n            }\n            ZetaSPS operator-()\
    \ const {\n                ZetaSPS res(*this);\n                for (auto& f :\
    \ res) f = -f;\n                return res;\n            }\n            friend\
    \ ZetaSPS operator+(ZetaSPS f, const ZetaSPS& g) { f += g; return f; }\n     \
    \       friend ZetaSPS operator-(ZetaSPS f, const ZetaSPS& g) { f -= g; return\
    \ f; }\n            friend ZetaSPS operator*(ZetaSPS f, const ZetaSPS& g) { f\
    \ *= g; return f; }\n            friend ZetaSPS operator*(ZetaSPS f, const value_type\
    \ &c) { f *= c; return f; }\n            friend ZetaSPS operator*(const value_type\
    \ &c, ZetaSPS f) { f *= c; return f; }\n            friend ZetaSPS operator/(ZetaSPS\
    \ f, const value_type &c) { f /= c; return f; }\n\n            ZetaSPS& operator+=(const\
    \ ZetaSPS& rhs) {\n                assert(_d == rhs._d);\n                for\
    \ (int i = 0; i < 1 << _d; ++i) (*this)[i] += rhs[i];\n                return\
    \ *this;\n            }\n            ZetaSPS& operator-=(const ZetaSPS& rhs) {\n\
    \                assert(_d == rhs._d);\n                for (int i = 0; i < 1\
    \ << _d; ++i) (*this)[i] -= rhs[i];\n                return *this;\n         \
    \   }\n            ZetaSPS& operator*=(value_type c) {\n                for (auto&\
    \ f : *this) f *= c;\n                return *this;\n            }\n         \
    \   ZetaSPS& operator/=(value_type c) {\n                value_type inv_c = ::inv(c);\n\
    \                for (auto& f : *this) f *= inv_c;\n                return *this;\n\
    \            }\n            ZetaSPS& operator*=(const ZetaSPS& rhs) {\n      \
    \          assert(_d == rhs._d);\n                for (size_type i = 0; i < size_type(1)\
    \ << _d; ++i) (*this)[i] = (*this)[i].mul(rhs[i]);\n                return *this;\n\
    \            }\n            ZetaSPS inv()  const { auto f = ZetaSPS(*this).inv_inplace();\
    \  return f; }\n            ZetaSPS sqrt() const { auto f = ZetaSPS(*this).sqrt_inplace();\
    \ return f; }\n            ZetaSPS exp()  const { auto f = ZetaSPS(*this).exp_inplace();\
    \  return f; }\n            ZetaSPS log()  const { auto f = ZetaSPS(*this).log_inplace();\
    \  return f; }\n            ZetaSPS pow(long long k) const { auto f = ZetaSPS(*this).pow_inplace(k);\
    \ return f; }\n            ZetaSPS& inv_inplace() {\n                for (auto&\
    \ f : *this) f = f.inv();\n                return *this;\n            }\n    \
    \        ZetaSPS& sqrt_inplace() {\n                for (auto& f : *this) f =\
    \ f.sqrt();\n                return *this;\n            }\n            ZetaSPS&\
    \ exp_inplace() {\n                for (auto& f : *this) f = f.exp();\n      \
    \          return *this;\n            }\n            ZetaSPS& log_inplace() {\n\
    \                for (auto& f : *this) f = f.log();\n                return *this;\n\
    \            }\n            ZetaSPS& pow_inplace(long long k) {\n            \
    \    for (auto& f : *this) f = f.pow(k);\n                return *this;\n    \
    \        }\n            ArraySPS<value_type, N> mobius_inplace() {\n         \
    \       return array_ranked_subset_transform::deranked_mobius<value_type, N>(*this);\n\
    \            }\n            ArraySPS<value_type, N> mobius() const {\n       \
    \         auto rf = ZetaSPS(*this);\n                return array_ranked_subset_transform::deranked_mobius<value_type,\
    \ N>(rf);\n            }\n        private:\n            int _d;\n        };\n\n\
    \        ZetaSPS zeta() const {\n            return ZetaSPS(*this);\n        }\n\
    \    };\n} // namespace suisen\n\n\n#line 9 \"test/src/math/array_sps/arc105_f.test.cpp\"\
    \n\nusing namespace suisen;\n\nint main() {\n    int n, m;\n    std::cin >> n\
    \ >> m;\n    int k = n;\n    std::vector<int> c(1 << k, 0);\n    for (int i =\
    \ 0; i < m; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        c[(1\
    \ << --u) | (1 << --v)] = 1;\n    }\n    subset_transform::zeta<int>(c);\n   \
    \ mint inv_2 = mint(2).inv();\n    std::vector<mint> pow_2(m + 1, 0), pow_inv_2(m\
    \ + 1, 0);\n    pow_2[0] = pow_inv_2[0] = 1;\n    for (int i = 1; i <= m ;++i)\
    \ {\n        pow_inv_2[i] = pow_inv_2[i - 1] * inv_2;\n        pow_2[i] = pow_2[i\
    \ - 1] * 2;\n    }\n    ArraySPS<mint, 18> p(n);\n    for (int i = 0; i < 1 <<\
    \ n; ++i) {\n        p[i] = pow_inv_2[c[i]];\n    }\n    ArraySPS<mint, 18> q\
    \ = p.pow(2);\n    for (int i = 0; i < 1 << n; ++i) {\n        q[i] *= pow_2[c[i]];\n\
    \    }\n    std::cout << q.zeta().sqrt_inplace().log_inplace().mobius_inplace().back().val()\
    \ << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc105/tasks/arc105_f\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/math/array_sps.hpp\"\n\nusing namespace suisen;\n\nint main()\
    \ {\n    int n, m;\n    std::cin >> n >> m;\n    int k = n;\n    std::vector<int>\
    \ c(1 << k, 0);\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n      \
    \  std::cin >> u >> v;\n        c[(1 << --u) | (1 << --v)] = 1;\n    }\n    subset_transform::zeta<int>(c);\n\
    \    mint inv_2 = mint(2).inv();\n    std::vector<mint> pow_2(m + 1, 0), pow_inv_2(m\
    \ + 1, 0);\n    pow_2[0] = pow_inv_2[0] = 1;\n    for (int i = 1; i <= m ;++i)\
    \ {\n        pow_inv_2[i] = pow_inv_2[i - 1] * inv_2;\n        pow_2[i] = pow_2[i\
    \ - 1] * 2;\n    }\n    ArraySPS<mint, 18> p(n);\n    for (int i = 0; i < 1 <<\
    \ n; ++i) {\n        p[i] = pow_inv_2[c[i]];\n    }\n    ArraySPS<mint, 18> q\
    \ = p.pow(2);\n    for (int i = 0; i < 1 << n; ++i) {\n        q[i] *= pow_2[c[i]];\n\
    \    }\n    std::cout << q.zeta().sqrt_inplace().log_inplace().mobius_inplace().back().val()\
    \ << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/math/array_sps.hpp
  - library/convolution/array_subset_convolution.hpp
  - library/polynomial/array_fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/transform/subset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/math/array_sps/arc105_f.test.cpp
  requiredBy: []
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/math/array_sps/arc105_f.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/array_sps/arc105_f.test.cpp
- /verify/test/src/math/array_sps/arc105_f.test.cpp.html
title: test/src/math/array_sps/arc105_f.test.cpp
---
