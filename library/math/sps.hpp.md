---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':heavy_check_mark:'
    path: library/math/modint_extension.hpp
    title: library/math/modint_extension.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/connectivity2.test.cpp
    title: test/src/math/sps/connectivity2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/lights_out_on_connected_graph.test.cpp
    title: test/src/math/sps/lights_out_on_connected_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/sps.hpp\"\n\n\n\n#include <cmath>\n#include\
    \ <initializer_list>\n#include <type_traits>\n#line 1 \"library/math/modint_extension.hpp\"\
    \n\n\n\n#include <cassert>\n#include <optional>\n\nnamespace suisen {\n/**\n *\
    \ refernce: https://37zigen.com/tonelli-shanks-algorithm/\n * calculates x s.t.\
    \ x^2 = a mod p in O((log p)^2).\n */\ntemplate <typename mint>\nstd::optional<mint>\
    \ optional_sqrt(mint a) {\n    static int p = mint::mod();\n    if (a == 0) return\
    \ std::make_optional(0);\n    if (p == 2) return std::make_optional(a);\n    if\
    \ (a.pow((p - 1) / 2) != 1) return std::nullopt;\n    mint b = 1;\n    while (b.pow((p\
    \ - 1) / 2) == 1) ++b;\n    static int tlz = __builtin_ctz(p - 1), q = (p - 1)\
    \ >> tlz;\n    mint x = a.pow((q + 1) / 2);\n    b = b.pow(q);\n    for (int shift\
    \ = 2; x * x != a; ++shift) {\n        mint e = a.inv() * x * x;\n        if (e.pow(1\
    \ << (tlz - shift)) != 1) x *= b;\n        b *= b;\n    }\n    return std::make_optional(x);\n\
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
    \n        SPS() : SPS(0) {}\n        SPS(int n) : SPS(n, 0) {}\n        SPS(int\
    \ n, T val) : SPS(std::vector<T>(1 << n, val)) {}\n        SPS(const std::vector<T>\
    \ &a) : SPS(std::vector<T>(a)) {}\n        SPS(std::vector<T> &&a) : std::vector<T>(std::move(a))\
    \ {\n            resize(ceil_pow2(size()), 0);\n        }\n        SPS(std::initializer_list<T>\
    \ l) : SPS(std::vector<T>(l)) {}\n\n        using base_type::operator=;\n\n  \
    \      using base_type::size;\n        using base_type::max_size;\n        using\
    \ base_type::capacity;\n        using base_type::empty;\n        using base_type::reserve;\n\
    \        using base_type::shrink_to_fit;\n\n        using base_type::begin;\n\
    \        using base_type::end;\n        using base_type::cbegin;\n        using\
    \ base_type::cend;\n        using base_type::rbegin;\n        using base_type::rend;\n\
    \        using base_type::crbegin;\n        using base_type::crend;\n        \n\
    \        using base_type::operator[];\n        using base_type::at;\n        using\
    \ base_type::data;\n        using base_type::front;\n        using base_type::back;\n\
    \n        using base_type::swap;\n\n        static SPS one(int n) {\n        \
    \    SPS f(n, 0);\n            f[0] = 1;\n            return f;\n        }\n\n\
    \        friend bool operator==(const SPS &lhs, const SPS &rhs) {\n          \
    \  return std::operator==(lhs, rhs);\n        }\n\n        void set_cardinality(int\
    \ n) {\n            resize(1 << n, 0);\n        }\n        int cardinality() {\n\
    \            return __builtin_ctz(size());\n        }\n\n        SPS cut_lower(unsigned\
    \ int p) const {\n            return SPS(begin(), begin() + p);\n        }\n \
    \       SPS cut_upper(unsigned int p) const {\n            return SPS(begin()\
    \ + p, begin() + p + p);\n        }\n\n        void concat(const SPS &upper) {\n\
    \            assert(size() == upper.size());\n            insert(end(), upper.begin(),\
    \ upper.end());\n        }\n\n        SPS operator+() const {\n            return\
    \ *this;\n        }\n        SPS operator-() const {\n            SPS res(*this);\n\
    \            for (auto &e : res) e = -e;\n            return res;\n        }\n\
    \        SPS& operator+=(const SPS &g) {\n            ensure(g.size());\n    \
    \        for (unsigned int i = 0; i < g.size(); ++i) (*this)[i] += g[i];\n   \
    \         return *this;\n        }\n        SPS& operator-=(const SPS &g) {\n\
    \            ensure(g.size());\n            for (unsigned int i = 0; i < g.size();\
    \ ++i) (*this)[i] -= g[i];\n            return *this;\n        }\n        SPS&\
    \ operator*=(const SPS &g) {\n            SPS g_(g);\n            ensure(g_.size()),\
    \ g_.ensure(size());\n            *this = subset_convolution<T>(*this, g_);\n\
    \            return *this;\n        }\n        SPS& operator*=(T c) {\n      \
    \      for (auto &e : *this) e *= c;\n            return *this;\n        }\n \
    \       SPS& operator/=(T c) {\n            T inv_c = ::inv(c);\n            for\
    \ (auto &e : *this) e *= inv_c;\n            return *this;\n        }\n      \
    \  friend SPS operator+(const SPS &f, const SPS &g) { return SPS(f) += g; }\n\
    \        friend SPS operator-(const SPS &f, const SPS &g) { return SPS(f) -= g;\
    \ }\n        friend SPS operator*(const SPS &f, const SPS &g) { return SPS(f)\
    \ *= g; }\n        friend SPS operator*(const SPS &f, T c) { return SPS(f) *=\
    \ c; }\n        friend SPS operator*(T c, const SPS &f) { return SPS(f) *= c;\
    \ }\n        friend SPS operator/(const SPS &f, T c) { return SPS(f) /= c; }\n\
    \n        SPS inv() {\n            using namespace internal::subset_convolution;\n\
    \n            SPS res { ::inv(front()) };\n            res.reserve(size());\n\
    \            for (unsigned int p = 1; p < size(); p <<= 1) {\n               \
    \ auto res_poly = ranked_zeta<T>(res);\n                auto poly = ranked_zeta<T>(cut_upper(p));\n\
    \                for (unsigned int i = 0; i < p; ++i) {\n                    muleq(muleq(poly[i],\
    \ res_poly[i]), res_poly[i]);\n                    for (auto &e : poly[i]) e *=\
    \ -1;\n                }\n                res.concat(deranked_mobius<T>(poly));\n\
    \            }\n            return res;\n        }\n        SPS sqrt() {\n   \
    \         using namespace internal::subset_convolution;\n\n            SPS res\
    \ { ::sqrt(front()) };\n            assert(res[0] * res[0] == front());\n    \
    \        res.reserve(size());\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) {\n                auto res_poly = ranked_zeta<T>(res);\n         \
    \       auto poly = ranked_zeta<T>(cut_upper(p));\n                for (unsigned\
    \ int i = 0; i < p; ++i) {\n                    for (auto &e : res_poly[i]) e\
    \ *= 2;\n                    muleq(poly[i], naive_poly_inv(res_poly[i]));\n  \
    \              }\n                res.concat(deranked_mobius<T>(poly));\n    \
    \        }\n            return res;\n        }\n        SPS exp() {\n        \
    \    SPS res { ::exp(front()) };\n            res.reserve(size());\n         \
    \   for (unsigned int p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * res);\n\
    \            return res;\n        }\n        SPS log() {\n            SPS res\
    \ { ::log(front()) };\n            res.reserve(size());\n            SPS inv_\
    \ = cut_lower(size() >> 1).inv();\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) res.concat(cut_upper(p) * inv_.cut_lower(p));\n            return res;\n\
    \        }\n        SPS pow(long long k) {\n            const T c = (*this)[0];\n\
    \n            if (c != 0) {\n                T pow_c = ::pow(c, k);\n        \
    \        SPS f = *this / c;\n                f = (T(k) * f.log()).exp();\n   \
    \             for (auto &e : f) e *= pow_c;\n                return f;\n     \
    \       }\n\n            using namespace internal::subset_convolution;\n\n   \
    \         int n = cardinality();\n            if (n < k) return SPS(n, 0);\n \
    \           auto res_poly = ranked<T>(one(n));\n            auto cur_poly = ranked<T>(*this);\n\
    \            for (; k; k >>= 1) {\n                for (unsigned int i = 0; i\
    \ < size(); ++i) {\n                    if (k & 1) muleq(res_poly[i], cur_poly[i]);\n\
    \                    muleq(cur_poly[i], std::vector<T>(cur_poly[i]));\n      \
    \          }\n            }\n            return SPS(deranked<T>(res_poly));\n\
    \        }\n\n    private:\n        using base_type::assign;\n        using base_type::push_back;\n\
    \        using base_type::emplace_back;\n        using base_type::pop_back;\n\
    \        using base_type::insert;\n        using base_type::emplace;\n       \
    \ using base_type::erase;\n        using base_type::clear;\n        using base_type::resize;\n\
    \n        static constexpr int ceil_pow2(unsigned int n) {\n            unsigned\
    \ int res = 1;\n            while (res < n) res <<= 1;\n            return res;\n\
    \        }\n\n        void ensure(unsigned int n) {\n            if (size() <\
    \ n) resize(n, 0);\n        }\n\n        static std::vector<T> naive_poly_inv(std::vector<T>\
    \ &a) {\n            const unsigned int n = a.size();\n            std::vector<T>\
    \ res(n, T(0));\n            T v = ::inv(a[0]);\n            for (unsigned int\
    \ j = 0; j < n; ++j) {\n                res[j] = j == 0;\n                for\
    \ (unsigned int k = 0; k < j; ++k) res[j] -= a[j - k] * res[k];\n            \
    \    res[j] *= v;\n            }\n            return res;\n        }\n};\n\n}\
    \ // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SPS\n#define SUISEN_SPS\n\n#include <cmath>\n#include <initializer_list>\n\
    #include <type_traits>\n#include \"library/math/modint_extension.hpp\"\n#include\
    \ \"library/convolution/subset_convolution.hpp\"\n\nnamespace suisen {\n\ntemplate\
    \ <typename T>\nclass SPS : private std::vector<T> {\n    public:\n        using\
    \ base_type = std::vector<T>;\n        using value_type             = typename\
    \ base_type::value_type;\n        using reference              = typename base_type::reference;\n\
    \        using const_reference        = typename base_type::const_reference;\n\
    \        using pointer                = typename base_type::pointer;\n       \
    \ using const_pointer          = typename base_type::const_pointer;\n        using\
    \ allocator_type         = typename base_type::allocator_type;\n        using\
    \ size_type              = typename base_type::size_type;\n        using difference_type\
    \        = typename base_type::difference_type;\n        using iterator      \
    \         = typename base_type::iterator;\n        using const_iterator      \
    \   = typename base_type::const_iterator;\n        using reverse_iterator    \
    \   = typename base_type::reverse_iterator;\n        using const_reverse_iterator\
    \ = typename base_type::const_reverse_iterator;\n\n        using base_type::vector;\n\
    \n        SPS() : SPS(0) {}\n        SPS(int n) : SPS(n, 0) {}\n        SPS(int\
    \ n, T val) : SPS(std::vector<T>(1 << n, val)) {}\n        SPS(const std::vector<T>\
    \ &a) : SPS(std::vector<T>(a)) {}\n        SPS(std::vector<T> &&a) : std::vector<T>(std::move(a))\
    \ {\n            resize(ceil_pow2(size()), 0);\n        }\n        SPS(std::initializer_list<T>\
    \ l) : SPS(std::vector<T>(l)) {}\n\n        using base_type::operator=;\n\n  \
    \      using base_type::size;\n        using base_type::max_size;\n        using\
    \ base_type::capacity;\n        using base_type::empty;\n        using base_type::reserve;\n\
    \        using base_type::shrink_to_fit;\n\n        using base_type::begin;\n\
    \        using base_type::end;\n        using base_type::cbegin;\n        using\
    \ base_type::cend;\n        using base_type::rbegin;\n        using base_type::rend;\n\
    \        using base_type::crbegin;\n        using base_type::crend;\n        \n\
    \        using base_type::operator[];\n        using base_type::at;\n        using\
    \ base_type::data;\n        using base_type::front;\n        using base_type::back;\n\
    \n        using base_type::swap;\n\n        static SPS one(int n) {\n        \
    \    SPS f(n, 0);\n            f[0] = 1;\n            return f;\n        }\n\n\
    \        friend bool operator==(const SPS &lhs, const SPS &rhs) {\n          \
    \  return std::operator==(lhs, rhs);\n        }\n\n        void set_cardinality(int\
    \ n) {\n            resize(1 << n, 0);\n        }\n        int cardinality() {\n\
    \            return __builtin_ctz(size());\n        }\n\n        SPS cut_lower(unsigned\
    \ int p) const {\n            return SPS(begin(), begin() + p);\n        }\n \
    \       SPS cut_upper(unsigned int p) const {\n            return SPS(begin()\
    \ + p, begin() + p + p);\n        }\n\n        void concat(const SPS &upper) {\n\
    \            assert(size() == upper.size());\n            insert(end(), upper.begin(),\
    \ upper.end());\n        }\n\n        SPS operator+() const {\n            return\
    \ *this;\n        }\n        SPS operator-() const {\n            SPS res(*this);\n\
    \            for (auto &e : res) e = -e;\n            return res;\n        }\n\
    \        SPS& operator+=(const SPS &g) {\n            ensure(g.size());\n    \
    \        for (unsigned int i = 0; i < g.size(); ++i) (*this)[i] += g[i];\n   \
    \         return *this;\n        }\n        SPS& operator-=(const SPS &g) {\n\
    \            ensure(g.size());\n            for (unsigned int i = 0; i < g.size();\
    \ ++i) (*this)[i] -= g[i];\n            return *this;\n        }\n        SPS&\
    \ operator*=(const SPS &g) {\n            SPS g_(g);\n            ensure(g_.size()),\
    \ g_.ensure(size());\n            *this = subset_convolution<T>(*this, g_);\n\
    \            return *this;\n        }\n        SPS& operator*=(T c) {\n      \
    \      for (auto &e : *this) e *= c;\n            return *this;\n        }\n \
    \       SPS& operator/=(T c) {\n            T inv_c = ::inv(c);\n            for\
    \ (auto &e : *this) e *= inv_c;\n            return *this;\n        }\n      \
    \  friend SPS operator+(const SPS &f, const SPS &g) { return SPS(f) += g; }\n\
    \        friend SPS operator-(const SPS &f, const SPS &g) { return SPS(f) -= g;\
    \ }\n        friend SPS operator*(const SPS &f, const SPS &g) { return SPS(f)\
    \ *= g; }\n        friend SPS operator*(const SPS &f, T c) { return SPS(f) *=\
    \ c; }\n        friend SPS operator*(T c, const SPS &f) { return SPS(f) *= c;\
    \ }\n        friend SPS operator/(const SPS &f, T c) { return SPS(f) /= c; }\n\
    \n        SPS inv() {\n            using namespace internal::subset_convolution;\n\
    \n            SPS res { ::inv(front()) };\n            res.reserve(size());\n\
    \            for (unsigned int p = 1; p < size(); p <<= 1) {\n               \
    \ auto res_poly = ranked_zeta<T>(res);\n                auto poly = ranked_zeta<T>(cut_upper(p));\n\
    \                for (unsigned int i = 0; i < p; ++i) {\n                    muleq(muleq(poly[i],\
    \ res_poly[i]), res_poly[i]);\n                    for (auto &e : poly[i]) e *=\
    \ -1;\n                }\n                res.concat(deranked_mobius<T>(poly));\n\
    \            }\n            return res;\n        }\n        SPS sqrt() {\n   \
    \         using namespace internal::subset_convolution;\n\n            SPS res\
    \ { ::sqrt(front()) };\n            assert(res[0] * res[0] == front());\n    \
    \        res.reserve(size());\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) {\n                auto res_poly = ranked_zeta<T>(res);\n         \
    \       auto poly = ranked_zeta<T>(cut_upper(p));\n                for (unsigned\
    \ int i = 0; i < p; ++i) {\n                    for (auto &e : res_poly[i]) e\
    \ *= 2;\n                    muleq(poly[i], naive_poly_inv(res_poly[i]));\n  \
    \              }\n                res.concat(deranked_mobius<T>(poly));\n    \
    \        }\n            return res;\n        }\n        SPS exp() {\n        \
    \    SPS res { ::exp(front()) };\n            res.reserve(size());\n         \
    \   for (unsigned int p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * res);\n\
    \            return res;\n        }\n        SPS log() {\n            SPS res\
    \ { ::log(front()) };\n            res.reserve(size());\n            SPS inv_\
    \ = cut_lower(size() >> 1).inv();\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) res.concat(cut_upper(p) * inv_.cut_lower(p));\n            return res;\n\
    \        }\n        SPS pow(long long k) {\n            const T c = (*this)[0];\n\
    \n            if (c != 0) {\n                T pow_c = ::pow(c, k);\n        \
    \        SPS f = *this / c;\n                f = (T(k) * f.log()).exp();\n   \
    \             for (auto &e : f) e *= pow_c;\n                return f;\n     \
    \       }\n\n            using namespace internal::subset_convolution;\n\n   \
    \         int n = cardinality();\n            if (n < k) return SPS(n, 0);\n \
    \           auto res_poly = ranked<T>(one(n));\n            auto cur_poly = ranked<T>(*this);\n\
    \            for (; k; k >>= 1) {\n                for (unsigned int i = 0; i\
    \ < size(); ++i) {\n                    if (k & 1) muleq(res_poly[i], cur_poly[i]);\n\
    \                    muleq(cur_poly[i], std::vector<T>(cur_poly[i]));\n      \
    \          }\n            }\n            return SPS(deranked<T>(res_poly));\n\
    \        }\n\n    private:\n        using base_type::assign;\n        using base_type::push_back;\n\
    \        using base_type::emplace_back;\n        using base_type::pop_back;\n\
    \        using base_type::insert;\n        using base_type::emplace;\n       \
    \ using base_type::erase;\n        using base_type::clear;\n        using base_type::resize;\n\
    \n        static constexpr int ceil_pow2(unsigned int n) {\n            unsigned\
    \ int res = 1;\n            while (res < n) res <<= 1;\n            return res;\n\
    \        }\n\n        void ensure(unsigned int n) {\n            if (size() <\
    \ n) resize(n, 0);\n        }\n\n        static std::vector<T> naive_poly_inv(std::vector<T>\
    \ &a) {\n            const unsigned int n = a.size();\n            std::vector<T>\
    \ res(n, T(0));\n            T v = ::inv(a[0]);\n            for (unsigned int\
    \ j = 0; j < n; ++j) {\n                res[j] = j == 0;\n                for\
    \ (unsigned int k = 0; k < j; ++k) res[j] -= a[j - k] * res[k];\n            \
    \    res[j] *= v;\n            }\n            return res;\n        }\n};\n\n}\
    \ // namespace suisen\n\n#endif // SUISEN_SPS\n"
  dependsOn:
  - library/math/modint_extension.hpp
  - library/convolution/subset_convolution.hpp
  isVerificationFile: false
  path: library/math/sps.hpp
  requiredBy: []
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
documentation_of: library/math/sps.hpp
layout: document
redirect_from:
- /library/library/math/sps.hpp
- /library/library/math/sps.hpp.html
title: library/math/sps.hpp
---
