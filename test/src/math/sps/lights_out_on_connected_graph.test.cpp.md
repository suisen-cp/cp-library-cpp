---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':question:'
    path: library/math/sps.hpp
    title: Sps
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc105/tasks/arc105_f
    links:
    - https://atcoder.jp/contests/arc105/tasks/arc105_f
  bundledCode: "#line 1 \"test/src/math/sps/lights_out_on_connected_graph.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/arc105/tasks/arc105_f\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/math/sps.hpp\"\n\n\n\n#include <cmath>\n#include <initializer_list>\n\
    #include <type_traits>\n#line 1 \"library/math/modint_extension.hpp\"\n\n\n\n\
    #include <cassert>\n#include <optional>\n\nnamespace suisen {\n/**\n * refernce:\
    \ https://37zigen.com/tonelli-shanks-algorithm/\n * calculates x s.t. x^2 = a\
    \ mod p in O((log p)^2).\n */\ntemplate <typename mint>\nstd::optional<mint> optional_sqrt(mint\
    \ a) {\n    static int p = mint::mod();\n    if (a == 0) return std::make_optional(0);\n\
    \    if (p == 2) return std::make_optional(a);\n    if (a.pow((p - 1) / 2) !=\
    \ 1) return std::nullopt;\n    mint b = 1;\n    while (b.pow((p - 1) / 2) == 1)\
    \ ++b;\n    static int tlz = __builtin_ctz(p - 1), q = (p - 1) >> tlz;\n    mint\
    \ x = a.pow((q + 1) / 2);\n    b = b.pow(q);\n    for (int shift = 2; x * x !=\
    \ a; ++shift) {\n        mint e = a.inv() * x * x;\n        if (e.pow(1 << (tlz\
    \ - shift)) != 1) x *= b;\n        b *= b;\n    }\n    return std::make_optional(x);\n\
    }\n\n};\n\n/**\n * calculates x s.t. x^2 = a mod p in O((log p)^2).\n * if not\
    \ exists, raises runtime error.\n */\ntemplate <typename mint>\nauto sqrt(mint\
    \ a) -> decltype(mint::mod(), mint()) {\n    return *suisen::optional_sqrt(a);\n\
    }\ntemplate <typename mint>\nauto log(mint a) -> decltype(mint::mod(), mint())\
    \  {\n    assert(a == 1);\n    return 0;\n}\ntemplate <typename mint>\nauto exp(mint\
    \ a) -> decltype(mint::mod(), mint())  {\n    assert(a == 0);\n    return 1;\n\
    }\ntemplate <typename mint, typename T>\nauto pow(mint a, T b) -> decltype(mint::mod(),\
    \ mint())  {\n    return a.pow(b);\n}\ntemplate <typename mint>\nauto inv(mint\
    \ a) -> decltype(mint::mod(), mint()) {\n    return a.inv();\n}\n\n\n#line 1 \"\
    library/convolution/subset_convolution.hpp\"\n\n\n\n#include <vector>\n\nnamespace\
    \ suisen {\n    namespace internal::subset_convolution {\n        template <typename\
    \ T>\n        std::vector<T>& addeq(std::vector<T> &a, const std::vector<T> &b)\
    \ {\n            const int n = a.size();\n            for (int i = 0; i < n; ++i)\
    \ a[i] += b[i];\n            return a;\n        }\n        template <typename\
    \ T>\n        std::vector<T>& subeq(std::vector<T> &a, const std::vector<T> &b)\
    \ {\n            const int n = a.size();\n            for (int i = 0; i < n; ++i)\
    \ a[i] -= b[i];\n            return a;\n        }\n        template <typename\
    \ T>\n        std::vector<T>& muleq(std::vector<T> &a, const std::vector<T> &b)\
    \ {\n            const int n = a.size();\n            for (int i = n - 1; i >=\
    \ 0; --i) {\n                for (int j = n - 1 - i; j > 0; --j) a[i + j] += a[i]\
    \ * b[j];\n                a[i] *= b[0];\n            }\n            return a;\n\
    \        }\n        template <typename T>\n        std::vector<T> add(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            std::vector<T> c = a;\n        \
    \    return addeq(c, b);\n        }\n        template <typename T>\n        std::vector<T>\
    \ sub(const std::vector<T> &a, const std::vector<T> &b) {\n            std::vector<T>\
    \ c = a;\n            return subeq(c, b);\n        }\n        template <typename\
    \ T>\n        std::vector<T> mul(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n            std::vector<T> c = a;\n            return muleq(c, b);\n\
    \        }\n\n        template <typename T>\n        std::vector<std::vector<T>>\
    \ ranked(const std::vector<T> &a) {\n            const int n = a.size();\n   \
    \         assert((-n & n) == n);\n            std::vector fs(n, std::vector(__builtin_ctz(n)\
    \ + 1, T(0)));\n            for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)]\
    \ = a[i];\n            return fs;\n        }\n        template <typename T>\n\
    \        std::vector<T> deranked(const std::vector<std::vector<T>> &polys) {\n\
    \            const int n = polys.size();\n            assert((-n & n) == n);\n\
    \            std::vector<T> a(n);\n            for (int i = 0; i < n; ++i) a[i]\
    \ = polys[i][__builtin_popcount(i)];\n            return a;\n        }\n\n   \
    \     template <typename T>\n        std::vector<std::vector<T>> ranked_zeta(const\
    \ std::vector<T> &a) {\n            std::vector<std::vector<T>> ranked_a = ranked<T>(a);\n\
    \            const int n = ranked_a.size();\n            for (int k = 1; k < n;\
    \ k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {\n\
    \                addeq(ranked_a[i + k], ranked_a[i]);\n            }\n       \
    \     return ranked_a;\n        }\n        template <typename T>\n        std::vector<T>\
    \ deranked_mobius(std::vector<std::vector<T>> &ranked_a) {\n            const\
    \ int n = ranked_a.size();\n            for (int k = 1; k < n; k *= 2) for (int\
    \ l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {\n              \
    \  subeq(ranked_a[i + k], ranked_a[i]);\n            }\n            return deranked<T>(ranked_a);\n\
    \        }\n    } // internal::subset_convolution\n\n    template <typename T>\n\
    \    std::vector<T> subset_convolution(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n        using namespace internal::subset_convolution;\n        const\
    \ int n = a.size();\n        auto ranked_a = ranked_zeta(a), ranked_b = ranked_zeta(b);\n\
    \        for (int i = 0; i < n; ++i) muleq(ranked_a[i], ranked_b[i]);\n      \
    \  return deranked_mobius(ranked_a);\n    }\n} // namespace suisen\n\n\n#line\
    \ 9 \"library/math/sps.hpp\"\n\nnamespace suisen {\n\ntemplate <typename T>\n\
    class SPS : private std::vector<T> {\n    public:\n        using base_type = std::vector<T>;\n\
    \        using value_type             = typename base_type::value_type;\n    \
    \    using reference              = typename base_type::reference;\n        using\
    \ const_reference        = typename base_type::const_reference;\n        using\
    \ pointer                = typename base_type::pointer;\n        using const_pointer\
    \          = typename base_type::const_pointer;\n        using allocator_type\
    \         = typename base_type::allocator_type;\n        using size_type     \
    \         = typename base_type::size_type;\n        using difference_type    \
    \    = typename base_type::difference_type;\n        using iterator          \
    \     = typename base_type::iterator;\n        using const_iterator         =\
    \ typename base_type::const_iterator;\n        using reverse_iterator       =\
    \ typename base_type::reverse_iterator;\n        using const_reverse_iterator\
    \ = typename base_type::const_reverse_iterator;\n\n        using base_type::vector;\n\
    \n        SPS() : SPS(0) {}\n        SPS(size_type n) : SPS(n, 0) {}\n       \
    \ SPS(size_type n, const value_type &val) : SPS(std::vector<value_type>(1 << n,\
    \ val)) {}\n        SPS(const base_type &a) : SPS(base_type(a)) {}\n        SPS(base_type\
    \ &&a) : base_type(std::move(a)) {\n            resize(ceil_pow2(size()), 0);\n\
    \        }\n        SPS(std::initializer_list<value_type> l) : SPS(base_type(l))\
    \ {}\n\n        using base_type::operator=;\n\n        using base_type::size;\n\
    \        using base_type::max_size;\n        using base_type::capacity;\n    \
    \    using base_type::empty;\n        using base_type::reserve;\n        using\
    \ base_type::shrink_to_fit;\n\n        using base_type::begin;\n        using\
    \ base_type::end;\n        using base_type::cbegin;\n        using base_type::cend;\n\
    \        using base_type::rbegin;\n        using base_type::rend;\n        using\
    \ base_type::crbegin;\n        using base_type::crend;\n        \n        using\
    \ base_type::operator[];\n        using base_type::at;\n        using base_type::data;\n\
    \        using base_type::front;\n        using base_type::back;\n\n        using\
    \ base_type::swap;\n\n        static SPS one(int n) {\n            SPS f(n, 0);\n\
    \            f[0] = 1;\n            return f;\n        }\n\n        friend bool\
    \ operator==(const SPS &lhs, const SPS &rhs) {\n            return std::operator==(lhs,\
    \ rhs);\n        }\n\n        void set_cardinality(int n) {\n            resize(1\
    \ << n, 0);\n        }\n        int cardinality() const {\n            return\
    \ __builtin_ctz(size());\n        }\n\n        SPS cut_lower(size_type p) const\
    \ {\n            return SPS(begin(), begin() + p);\n        }\n        SPS cut_upper(size_type\
    \ p) const {\n            return SPS(begin() + p, begin() + p + p);\n        }\n\
    \n        void concat(const SPS &upper) {\n            assert(size() == upper.size());\n\
    \            insert(end(), upper.begin(), upper.end());\n        }\n\n       \
    \ SPS operator+() const {\n            return *this;\n        }\n        SPS operator-()\
    \ const {\n            SPS res(*this);\n            for (auto &e : res) e = -e;\n\
    \            return res;\n        }\n        SPS& operator+=(const SPS &g) {\n\
    \            ensure(g.size());\n            for (size_type i = 0; i < g.size();\
    \ ++i) (*this)[i] += g[i];\n            return *this;\n        }\n        SPS&\
    \ operator-=(const SPS &g) {\n            ensure(g.size());\n            for (size_type\
    \ i = 0; i < g.size(); ++i) (*this)[i] -= g[i];\n            return *this;\n \
    \       }\n        SPS& operator*=(const SPS &g) {\n            SPS g_(g);\n \
    \           ensure(g_.size()), g_.ensure(size());\n            *this = subset_convolution<value_type>(*this,\
    \ g_);\n            return *this;\n        }\n        SPS& operator*=(value_type\
    \ c) {\n            for (auto &e : *this) e *= c;\n            return *this;\n\
    \        }\n        SPS& operator/=(value_type c) {\n            value_type inv_c\
    \ = ::inv(c);\n            for (auto &e : *this) e *= inv_c;\n            return\
    \ *this;\n        }\n        friend SPS operator+(const SPS &f, const SPS &g)\
    \ { return SPS(f) += g; }\n        friend SPS operator-(const SPS &f, const SPS\
    \ &g) { return SPS(f) -= g; }\n        friend SPS operator*(const SPS &f, const\
    \ SPS &g) { return SPS(f) *= g; }\n        friend SPS operator*(const SPS &f,\
    \ value_type c) { return SPS(f) *= c; }\n        friend SPS operator*(value_type\
    \ c, const SPS &f) { return SPS(f) *= c; }\n        friend SPS operator/(const\
    \ SPS &f, value_type c) { return SPS(f) /= c; }\n\n        SPS inv() {\n     \
    \       using namespace internal::subset_convolution;\n\n            SPS res {\
    \ ::inv(front()) };\n            res.reserve(size());\n            for (size_type\
    \ p = 1; p < size(); p <<= 1) {\n                auto res_poly = ranked_zeta<value_type>(res);\n\
    \                auto poly = ranked_zeta<value_type>(cut_upper(p));\n        \
    \        for (size_type i = 0; i < p; ++i) {\n                    muleq(muleq(poly[i],\
    \ res_poly[i]), res_poly[i]);\n                    for (auto &e : poly[i]) e *=\
    \ -1;\n                }\n                res.concat(deranked_mobius<value_type>(poly));\n\
    \            }\n            return res;\n        }\n        // SPS inv() {\n \
    \       //     using namespace internal::subset_convolution;\n        //     const\
    \ int n = size();\n        //     auto rf = ranked(*this);\n        //     rf[0][0]\
    \ = ::inv(front());\n        //     for (int i = 1; i < n; i <<= 1) {\n      \
    \  //         for (int k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l +=\
    \ 2 * k) for (int p = l; p < l + k; ++p) addeq(rf[p + k], rf[p]);\n        //\
    \         for (int j = 0; j < i; ++j) {\n        //             muleq(rf[i + j],\
    \ rf[j]);\n        //             muleq(rf[i + j], rf[j]);\n        //       \
    \      rf[i + j] = sub(rf[j], rf[i + j]);\n        //         }\n        //  \
    \   }\n        //     return deranked_mobius(rf);\n        // }\n        SPS sqrt()\
    \ {\n            using namespace internal::subset_convolution;\n\n           \
    \ SPS res { ::sqrt(front()) };\n            assert(res[0] * res[0] == front());\n\
    \            res.reserve(size());\n            for (size_type p = 1; p < size();\
    \ p <<= 1) {\n                auto res_poly = ranked_zeta<value_type>(res);\n\
    \                auto poly = ranked_zeta<value_type>(cut_upper(p));\n        \
    \        for (size_type i = 0; i < p; ++i) {\n                    for (auto &e\
    \ : res_poly[i]) e *= 2;\n                    muleq(poly[i], naive_poly_inv(res_poly[i]));\n\
    \                }\n                res.concat(deranked_mobius<value_type>(poly));\n\
    \            }\n            return res;\n        }\n        // SPS sqrt() {\n\
    \        //     using namespace internal::subset_convolution;\n        //    \
    \ const int n = size();\n        //     auto rf = ranked(*this);\n        // \
    \    rf[0][0] = ::sqrt(front());\n        //     assert(rf[0][0] * rf[0][0] ==\
    \ front());\n        //     for (int i = 1; i < n; i <<= 1) {\n        //    \
    \     for (int k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l += 2 * k) for\
    \ (int p = l; p < l + k; ++p) addeq(rf[p + k], rf[p]);\n        //         for\
    \ (int j = 0; j < i; ++j) {\n        //             auto inv_2rg = rf[j];\n  \
    \      //             for (auto &e : inv_2rg) e *= 2;\n        //            \
    \ muleq(rf[i + j], naive_poly_inv(inv_2rg));\n        //             addeq(rf[i\
    \ + j], rf[j]);\n        //         }\n        //     }\n        //     return\
    \ deranked_mobius(rf);\n        // }\n        SPS exp() {\n            SPS res\
    \ { ::exp(front()) };\n            res.reserve(size());\n            for (size_type\
    \ p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * res);\n            return\
    \ res;\n        }\n        // SPS exp() {\n        //     using namespace internal::subset_convolution;\n\
    \        //     const int n = size();\n        //     auto rf = ranked(*this);\n\
    \        //     rf[0][0] = ::exp(front());\n        //     for (int i = 1; i <\
    \ n; i <<= 1) {\n        //         for (int k = 1; k < i; k <<= 1) for (int l\
    \ = i; l < 2 * i; l += 2 * k) for (int p = l; p < l + k; ++p) addeq(rf[p + k],\
    \ rf[p]);\n        //         for (int j = 0; j < i; ++j) {\n        //      \
    \       ++rf[i + j][0];\n        //             muleq(rf[i + j], rf[j]);\n   \
    \     //         }\n        //     }\n        //     return deranked_mobius(rf);\n\
    \        // }\n        SPS log() {\n            SPS res { ::log(front()) };\n\
    \            res.reserve(size());\n            SPS inv_ = cut_lower(size() >>\
    \ 1).inv();\n            for (size_type p = 1; p < size(); p <<= 1) res.concat(cut_upper(p)\
    \ * inv_.cut_lower(p));\n            return res;\n        }\n        // SPS log()\
    \ {\n        //     using namespace internal::subset_convolution;\n        //\
    \     const int n = size();\n        //     auto rg = ranked_zeta<value_type>(cut_lower(size()\
    \ >> 1).inv());\n        //     for (auto &v : rg) v.push_back(value_type(0));\n\
    \        //     auto rf = ranked(*this);\n        //     rf[0][0] = ::log(front());\n\
    \        //     for (int i = 1; i < n; i <<= 1) {\n        //         for (int\
    \ k = 1; k < i; k <<= 1) for (int l = i; l < 2 * i; l += 2 * k) for (int p = l;\
    \ p < l + k; ++p) addeq(rf[p + k], rf[p]);\n        //         for (int j = 0;\
    \ j < i; ++j) {\n        //             muleq(rf[i + j], rg[j]);\n        // \
    \            addeq(rf[i + j], rf[j]);\n        //         }\n        //     }\n\
    \        //     return deranked_mobius(rf);\n        // }\n        SPS pow(long\
    \ long k) {\n            const value_type c = (*this)[0];\n\n            if (c\
    \ != 0) {\n                value_type pow_c = ::pow(c, k);\n                SPS\
    \ f = *this / c;\n                f = (value_type(k) * f.log()).exp();\n     \
    \           for (auto &e : f) e *= pow_c;\n                return f;\n       \
    \     }\n\n            using namespace internal::subset_convolution;\n\n     \
    \       int n = cardinality();\n            if (n < k) return SPS(n, 0);\n   \
    \         auto res_poly = ranked_zeta<value_type>(one(n));\n            auto cur_poly\
    \ = ranked_zeta<value_type>(*this);\n            for (size_type i = 0; i < size();\
    \ ++i) {\n                for (long long b = k; b; b >>= 1) {\n              \
    \      if (b & 1) muleq(res_poly[i], cur_poly[i]);\n                    muleq(cur_poly[i],\
    \ std::vector<value_type>(cur_poly[i]));\n                }\n            }\n \
    \           return SPS(deranked_mobius<value_type>(res_poly));\n        }\n\n\
    \    private:\n        using base_type::assign;\n        using base_type::push_back;\n\
    \        using base_type::emplace_back;\n        using base_type::pop_back;\n\
    \        using base_type::insert;\n        using base_type::emplace;\n       \
    \ using base_type::erase;\n        using base_type::clear;\n        using base_type::resize;\n\
    \n        static constexpr int ceil_pow2(size_type n) {\n            size_type\
    \ res = 1;\n            while (res < n) res <<= 1;\n            return res;\n\
    \        }\n\n        void ensure(size_type n) {\n            if (size() < n)\
    \ resize(n, 0);\n        }\n\n        static std::vector<value_type> naive_poly_inv(std::vector<value_type>\
    \ &a) {\n            const size_type n = a.size();\n            std::vector<value_type>\
    \ res(n, value_type(0));\n            value_type v = ::inv(a[0]);\n          \
    \  for (size_type j = 0; j < n; ++j) {\n                res[j] = j == 0;\n   \
    \             for (size_type k = 0; k < j; ++k) res[j] -= a[j - k] * res[k];\n\
    \                res[j] *= v;\n            }\n            return res;\n      \
    \  }\n};\n\n} // namespace suisen\n\n\n#line 1 \"library/transform/subset.hpp\"\
    \n\n\n\n#line 1 \"library/transform/kronecker_power.hpp\"\n\n\n\n#line 6 \"library/transform/kronecker_power.hpp\"\
    \n\n#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace suisen {\n\
    \    namespace default_operator {\n        template <typename T>\n        auto\
    \ zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(const T &x, const T &y) -> decltype(x + y) {\
    \ return x + y; }\n        template <typename T>\n        auto sub(const T &x,\
    \ const T &y) -> decltype(x - y) { return x - y; }\n        template <typename\
    \ T>\n        auto mul(const T &x, const T &y) -> decltype(x * y) { return x *\
    \ y; }\n        template <typename T>\n        auto div(const T &x, const T &y)\
    \ -> decltype(x / y) { return x / y; }\n        template <typename T>\n      \
    \  auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }\n   \
    \     template <typename T>\n        auto neg(const T &x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(const T &x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n    namespace default_operator_noref\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(T\
    \ x, T y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(T x, T y) -> decltype(x - y) { return x - y; }\n        template\
    \ <typename T>\n        auto mul(T x, T y) -> decltype(x * y) { return x * y;\
    \ }\n        template <typename T>\n        auto div(T x, T y) -> decltype(x /\
    \ y) { return x / y; }\n        template <typename T>\n        auto mod(T x, T\
    \ y) -> decltype(x % y) { return x % y; }\n        template <typename T>\n   \
    \     auto neg(T x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(T x) -> decltype(one<T>() / x)  { return one<T>() / x;\
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 8 \"library/transform/kronecker_power.hpp\"\
    \n\nnamespace suisen {\n    namespace kronecker_power_transform {\n        namespace\
    \ internal {\n            template <typename UnitTransform, typename ReferenceGetter,\
    \ std::size_t... Seq>\n            void unit_transform(UnitTransform transform,\
    \ ReferenceGetter ref_getter, std::index_sequence<Seq...>) {\n               \
    \ transform(ref_getter(Seq)...);\n            }\n        }\n\n        template\
    \ <typename T, std::size_t D, auto unit_transform>\n        void kronecker_power_transform(std::vector<T>\
    \ &x) {\n            const std::size_t n = x.size();\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
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
    \n\n#line 10 \"test/src/math/sps/lights_out_on_connected_graph.test.cpp\"\n\n\
    using namespace suisen;\n\nint main() {\n    int n, m;\n    std::cin >> n >> m;\n\
    \    int k = n;\n    std::vector<int> c(1 << k, 0);\n    for (int i = 0; i < m;\
    \ ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        c[(1 << --u)\
    \ | (1 << --v)] = 1;\n    }\n    subset_transform::zeta<int>(c);\n    mint inv_2\
    \ = mint(2).inv();\n    std::vector<mint> pow_2(m + 1, 0), pow_inv_2(m + 1, 0);\n\
    \    pow_2[0] = pow_inv_2[0] = 1;\n    for (int i = 1; i <= m ;++i) {\n      \
    \  pow_inv_2[i] = pow_inv_2[i - 1] * inv_2;\n        pow_2[i] = pow_2[i - 1] *\
    \ 2;\n    }\n    SPS<mint> p(n);\n    for (int i = 0; i < 1 << n; ++i) {\n   \
    \     p[i] = pow_inv_2[c[i]];\n    }\n    SPS<mint> q = p * p;\n    for (int i\
    \ = 0; i < 1 << n; ++i) {\n        q[i] *= pow_2[c[i]];\n    }\n    std::cout\
    \ << q.sqrt().log().back().val() << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc105/tasks/arc105_f\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/math/sps.hpp\"\n#include \"library/transform/subset.hpp\"\
    \n\nusing namespace suisen;\n\nint main() {\n    int n, m;\n    std::cin >> n\
    \ >> m;\n    int k = n;\n    std::vector<int> c(1 << k, 0);\n    for (int i =\
    \ 0; i < m; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        c[(1\
    \ << --u) | (1 << --v)] = 1;\n    }\n    subset_transform::zeta<int>(c);\n   \
    \ mint inv_2 = mint(2).inv();\n    std::vector<mint> pow_2(m + 1, 0), pow_inv_2(m\
    \ + 1, 0);\n    pow_2[0] = pow_inv_2[0] = 1;\n    for (int i = 1; i <= m ;++i)\
    \ {\n        pow_inv_2[i] = pow_inv_2[i - 1] * inv_2;\n        pow_2[i] = pow_2[i\
    \ - 1] * 2;\n    }\n    SPS<mint> p(n);\n    for (int i = 0; i < 1 << n; ++i)\
    \ {\n        p[i] = pow_inv_2[c[i]];\n    }\n    SPS<mint> q = p * p;\n    for\
    \ (int i = 0; i < 1 << n; ++i) {\n        q[i] *= pow_2[c[i]];\n    }\n    std::cout\
    \ << q.sqrt().log().back().val() << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/math/sps.hpp
  - library/math/modint_extension.hpp
  - library/convolution/subset_convolution.hpp
  - library/transform/subset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/math/sps/lights_out_on_connected_graph.test.cpp
  requiredBy: []
  timestamp: '2022-01-31 17:40:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/sps/lights_out_on_connected_graph.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/sps/lights_out_on_connected_graph.test.cpp
- /verify/test/src/math/sps/lights_out_on_connected_graph.test.cpp.html
title: test/src/math/sps/lights_out_on_connected_graph.test.cpp
---
