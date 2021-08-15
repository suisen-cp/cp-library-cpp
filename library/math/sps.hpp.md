---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: library/math/modint_extension.hpp
  - icon: ':question:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/math/sps/connectivity2.test.cpp
    title: test/src/math/sps/connectivity2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/lights_out_on_connected_graph.test.cpp
    title: test/src/math/sps/lights_out_on_connected_graph.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/sps.hpp\"\n\n\n\n#include <cmath>\n#include\
    \ <initializer_list>\n#include <type_traits>\n#line 1 \"library/convolution/subset_convolution.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen::internal::arithmetic_operator {\n\
    template <typename T>\nvoid operator+=(std::vector<T> &a, const std::vector<T>\
    \ &b) {\n    int n = b.size();\n    for (int i = 0; i < n; ++i) a[i] += b[i];\n\
    }\ntemplate <typename T>\nvoid operator-=(std::vector<T> &a, const std::vector<T>\
    \ &b) {\n    int n = b.size();\n    for (int i = 0; i < n; ++i) a[i] -= b[i];\n\
    }\ntemplate <typename T>\nvoid operator*=(std::vector<T> &a, const std::vector<T>\
    \ &b) {\n    int n = b.size();\n    for (int i = n - 1; i >= 0; --i) {\n     \
    \   for (int j = n - i - 1; j > 0; --j) a[i + j] += a[i] * b[j];\n        a[i]\
    \ *= b[0];\n    }\n}\n}\n\n#line 1 \"library/transform/subset.hpp\"\n\n\n\n#include\
    \ <cassert>\n#line 6 \"library/transform/subset.hpp\"\n\nnamespace suisen::internal::arithmetic_operator\
    \ {}\n\nnamespace suisen {\nnamespace subset_transform {\nnamespace internal {\n\
    template <typename T, typename AssignOp>\nvoid transform(std::vector<T> &f, AssignOp\
    \ assign_op) {\n    const int n = f.size();\n    assert((-n & n) == n);\n    for\
    \ (int k = 1; k < n; k <<= 1) {\n        for (int l = 0; l < n; l += 2 * k) {\n\
    \            int m = l + k;\n            for (int p = 0; p < k; ++p) assign_op(f[m\
    \ + p], f[l + p]);\n        }\n    }\n}\n} // namespace internal\n\nusing namespace\
    \ suisen::internal::arithmetic_operator;\n\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    internal::transform(f,\
    \ add_assign);\n}\ntemplate <typename T, typename SubAssign>\nvoid mobius(std::vector<T>\
    \ &f, SubAssign sub_assign) {\n    internal::transform(f, sub_assign);\n}\ntemplate\
    \ <typename T>\nvoid zeta(std::vector<T> &f) {\n    zeta(f, [](T &a, const T &b)\
    \ { a += b; });\n}\ntemplate <typename T>\nvoid mobius(std::vector<T> &f) {\n\
    \    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace subset_transform\n\
    \ntemplate <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign,\
    \ SubAssign sub_assign>\nstruct SubsetTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        subset_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        subset_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct SubsetTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        subset_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        subset_transform::mobius(a);\n\
    \    }\n};\n\n} // namespace suisen\n\n\n\n#line 1 \"library/convolution/convolution.hpp\"\
    \n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n\
    namespace internal::arithmetic_operator {}\ntemplate <typename T, template <typename>\
    \ class Transform>\nstruct Convolution {\n    static std::vector<T> convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        using namespace internal::arithmetic_operator;\n\
    \        const int n = a.size();\n        assert(n == int(b.size()));\n      \
    \  Transform<T>::transform(a);\n        Transform<T>::transform(b);\n        for\
    \ (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        using namespace internal::arithmetic_operator;\n        const\
    \ int num = a.size();\n        if (num == 0) return {};\n        const int n =\
    \ a[0].size();\n        for (auto &v : a) {\n            assert(n == int(v.size()));\n\
    \            Transform<T>::transform(v);\n        }\n        auto &res = a[0];\n\
    \        for (int i = 1; i < num; ++i) {\n            for (int j = 0; j < n; ++j)\
    \ res[j] *= a[i][j];\n        }\n        Transform<T>::inverse_transform(res);\n\
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n\n#line 29 \"library/convolution/subset_convolution.hpp\"\
    \n\nnamespace suisen {\n\nnamespace internal::subset_convolution {\ntemplate <typename\
    \ T, typename Container>\nauto add_rank(const Container &a) {\n    int n = a.size();\n\
    \    assert((-n & n) == n);\n    std::vector<std::vector<T>> fs(n, std::vector<T>(__builtin_ctz(n)\
    \ + 1, T(0)));\n    for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] =\
    \ a[i];\n    return fs;\n}\ntemplate <typename T>\nauto remove_rank(const std::vector<std::vector<T>>\
    \ &polys) {\n    int n = polys.size();\n    assert((-n & n) == n);\n    std::vector<T>\
    \ a(n);\n    for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n\
    \    return a;\n}\n} // namespace internal\n\ntemplate <typename T>\nusing SubsetConvolution\
    \ = Convolution<std::vector<T>, SubsetTransform>;\n\ntemplate <typename T, typename\
    \ ...Args>\nstd::vector<T> subset_convolution(Args &&...args) {\n    using namespace\
    \ internal::subset_convolution;\n    return remove_rank<T>(SubsetConvolution<T>::convolution(add_rank<T>(args)...));\n\
    }\n\n} // namespace suisen\n\n\n#line 1 \"library/math/modint_extension.hpp\"\n\
    \n\n\n#line 5 \"library/math/modint_extension.hpp\"\n#include <optional>\n\nnamespace\
    \ suisen {\n/**\n * refernce: https://37zigen.com/tonelli-shanks-algorithm/\n\
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
    \ a.inv();\n}\n\n\n#line 9 \"library/math/sps.hpp\"\n\nnamespace suisen {\n\n\
    template <typename T>\nclass SPS : private std::vector<T> {\n    public:\n   \
    \     using base_type = std::vector<T>;\n        using value_type            \
    \ = typename base_type::value_type;\n        using reference              = typename\
    \ base_type::reference;\n        using const_reference        = typename base_type::const_reference;\n\
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
    \        void set_cardinality(int n) {\n            resize(1 << n, 0);\n     \
    \   }\n        int cardinality() {\n            return __builtin_ctz(size());\n\
    \        }\n\n        SPS cut_lower(unsigned int p) const {\n            return\
    \ SPS(begin(), begin() + p);\n        }\n        SPS cut_upper(unsigned int p)\
    \ const {\n            return SPS(begin() + p, begin() + p + p);\n        }\n\n\
    \        void concat(const SPS &upper) {\n            assert(size() == upper.size());\n\
    \            insert(end(), upper.begin(), upper.end());\n        }\n\n       \
    \ SPS operator+() const {\n            return *this;\n        }\n        SPS operator-()\
    \ const {\n            SPS res(*this);\n            for (auto &e : res) e = -e;\n\
    \            return res;\n        }\n        SPS& operator+=(const SPS &g) {\n\
    \            ensure(g.size());\n            for (unsigned int i = 0; i < g.size();\
    \ ++i) (*this)[i] += g[i];\n            return *this;\n        }\n        SPS&\
    \ operator-=(const SPS &g) {\n            ensure(g.size());\n            for (unsigned\
    \ int i = 0; i < g.size(); ++i) (*this)[i] -= g[i];\n            return *this;\n\
    \        }\n        SPS& operator*=(const SPS &g) {\n            SPS g_(g);\n\
    \            ensure(g_.size()), g_.ensure(size());\n            *this = subset_convolution<T>(*this,\
    \ g_);\n            return *this;\n        }\n        SPS& operator*=(T c) {\n\
    \            for (auto &e : *this) e *= c;\n            return *this;\n      \
    \  }\n        SPS& operator/=(T c) {\n            T inv_c = ::inv(c);\n      \
    \      for (auto &e : *this) e *= inv_c;\n            return *this;\n        }\n\
    \        friend SPS operator+(const SPS &f, const SPS &g) { return SPS(f) += g;\
    \ }\n        friend SPS operator-(const SPS &f, const SPS &g) { return SPS(f)\
    \ -= g; }\n        friend SPS operator*(const SPS &f, const SPS &g) { return SPS(f)\
    \ *= g; }\n        friend SPS operator*(const SPS &f, T c) { return SPS(f) *=\
    \ c; }\n        friend SPS operator*(T c, const SPS &f) { return SPS(f) *= c;\
    \ }\n        friend SPS operator/(const SPS &f, T c) { return SPS(f) /= c; }\n\
    \n        SPS inv() {\n            using namespace suisen::internal::arithmetic_operator;\n\
    \            using namespace suisen::internal::subset_convolution;\n\n       \
    \     SPS res { ::inv(front()) };\n            res.reserve(size());\n        \
    \    for (unsigned int p = 1; p < size(); p <<= 1) {\n                auto res_poly\
    \ = add_rank<T>(res);\n                auto poly = add_rank<T>(cut_upper(p));\n\
    \                subset_transform::zeta(res_poly);\n                subset_transform::zeta(poly);\n\
    \                for (unsigned int i = 0; i < p; ++i) {\n                    poly[i]\
    \ *= res_poly[i], poly[i] *= res_poly[i];\n                    for (auto &e :\
    \ poly[i]) e *= -1;\n                }\n                subset_transform::mobius(poly);\n\
    \                res.concat(remove_rank<T>(poly));\n            }\n          \
    \  return res;\n        }\n        SPS sqrt() {\n            using namespace suisen::internal::arithmetic_operator;\n\
    \            using namespace suisen::internal::subset_convolution;\n\n       \
    \     SPS res { ::sqrt(front()) };\n            assert(res[0] * res[0] == front());\n\
    \            res.reserve(size());\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) {\n                auto res_poly = add_rank<T>(res);\n            \
    \    auto poly = add_rank<T>(cut_upper(p));\n                subset_transform::zeta(res_poly);\n\
    \                subset_transform::zeta(poly);\n                for (unsigned\
    \ int i = 0; i < p; ++i) {\n                    unsigned int n = res_poly[i].size();\n\
    \                    for (auto &e : res_poly[i]) e *= 2;\n                   \
    \ std::vector<T> res_inv(n, 0);\n                    T v = ::inv(res_poly[i][0]);\n\
    \                    for (unsigned int j = 0; j < n; ++j) {\n                \
    \        res_inv[j] = j == 0;\n                        for (unsigned int k = 0;\
    \ k < j; ++k) {\n                            res_inv[j] -= res_poly[i][j - k]\
    \ * res_inv[k];\n                        }\n                        res_inv[j]\
    \ *= v;\n                    }\n                    poly[i] *= res_inv;\n    \
    \            }\n                subset_transform::mobius(poly);\n            \
    \    res.concat(remove_rank<T>(poly));\n            }\n            return res;\n\
    \        }\n        SPS exp() {\n            SPS res { ::exp(front()) };\n   \
    \         res.reserve(size());\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) res.concat(cut_upper(p) * res);\n            return res;\n        }\n\
    \        SPS log() {\n            SPS res { ::log(front()) };\n            res.reserve(size());\n\
    \            SPS inv_ = cut_lower(size() >> 1).inv();\n            for (unsigned\
    \ int p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * inv_.cut_lower(p));\n\
    \            return res;\n        }\n        SPS pow(long long k) {\n        \
    \    using namespace suisen::internal::arithmetic_operator;\n            using\
    \ namespace suisen::internal::subset_convolution;\n\n            T c = (*this)[0];\n\
    \            if (c == 0) {\n                int n = cardinality();\n         \
    \       if (n < k) return SPS(n, 0);\n                auto res_poly = add_rank<T>(one(n));\n\
    \                auto cur_poly = add_rank<T>(SPS(*this));\n                for\
    \ (; k; k >>= 1) {\n                    for (unsigned int i = 0; i < size(); ++i)\
    \ {\n                        if (k & 1) res_poly[i] *= cur_poly[i];\n        \
    \                cur_poly[i] *= std::vector<T>(cur_poly[i]);\n               \
    \     }\n                }\n                return SPS(remove_rank<T>(res_poly));\n\
    \            }\n            T pow_c = ::pow(c, k);\n            SPS f = *this\
    \ / c;\n            f = (T(k) * f.log()).exp();\n            for (auto &e : f)\
    \ e *= pow_c;\n            return f;\n        }\n\n    private:\n        using\
    \ base_type::assign;\n        using base_type::push_back;\n        using base_type::emplace_back;\n\
    \        using base_type::pop_back;\n        using base_type::insert;\n      \
    \  using base_type::emplace;\n        using base_type::erase;\n        using base_type::clear;\n\
    \        using base_type::resize;\n\n        static constexpr int ceil_pow2(unsigned\
    \ int n) {\n            unsigned int res = 1;\n            while (res < n) res\
    \ <<= 1;\n            return res;\n        }\n\n        void ensure(unsigned int\
    \ n) {\n            if (size() < n) resize(n, 0);\n        }\n};\n\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_SPS\n#define SUISEN_SPS\n\n#include <cmath>\n#include <initializer_list>\n\
    #include <type_traits>\n#include \"library/convolution/subset_convolution.hpp\"\
    \n#include \"library/math/modint_extension.hpp\"\n\nnamespace suisen {\n\ntemplate\
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
    \        void set_cardinality(int n) {\n            resize(1 << n, 0);\n     \
    \   }\n        int cardinality() {\n            return __builtin_ctz(size());\n\
    \        }\n\n        SPS cut_lower(unsigned int p) const {\n            return\
    \ SPS(begin(), begin() + p);\n        }\n        SPS cut_upper(unsigned int p)\
    \ const {\n            return SPS(begin() + p, begin() + p + p);\n        }\n\n\
    \        void concat(const SPS &upper) {\n            assert(size() == upper.size());\n\
    \            insert(end(), upper.begin(), upper.end());\n        }\n\n       \
    \ SPS operator+() const {\n            return *this;\n        }\n        SPS operator-()\
    \ const {\n            SPS res(*this);\n            for (auto &e : res) e = -e;\n\
    \            return res;\n        }\n        SPS& operator+=(const SPS &g) {\n\
    \            ensure(g.size());\n            for (unsigned int i = 0; i < g.size();\
    \ ++i) (*this)[i] += g[i];\n            return *this;\n        }\n        SPS&\
    \ operator-=(const SPS &g) {\n            ensure(g.size());\n            for (unsigned\
    \ int i = 0; i < g.size(); ++i) (*this)[i] -= g[i];\n            return *this;\n\
    \        }\n        SPS& operator*=(const SPS &g) {\n            SPS g_(g);\n\
    \            ensure(g_.size()), g_.ensure(size());\n            *this = subset_convolution<T>(*this,\
    \ g_);\n            return *this;\n        }\n        SPS& operator*=(T c) {\n\
    \            for (auto &e : *this) e *= c;\n            return *this;\n      \
    \  }\n        SPS& operator/=(T c) {\n            T inv_c = ::inv(c);\n      \
    \      for (auto &e : *this) e *= inv_c;\n            return *this;\n        }\n\
    \        friend SPS operator+(const SPS &f, const SPS &g) { return SPS(f) += g;\
    \ }\n        friend SPS operator-(const SPS &f, const SPS &g) { return SPS(f)\
    \ -= g; }\n        friend SPS operator*(const SPS &f, const SPS &g) { return SPS(f)\
    \ *= g; }\n        friend SPS operator*(const SPS &f, T c) { return SPS(f) *=\
    \ c; }\n        friend SPS operator*(T c, const SPS &f) { return SPS(f) *= c;\
    \ }\n        friend SPS operator/(const SPS &f, T c) { return SPS(f) /= c; }\n\
    \n        SPS inv() {\n            using namespace suisen::internal::arithmetic_operator;\n\
    \            using namespace suisen::internal::subset_convolution;\n\n       \
    \     SPS res { ::inv(front()) };\n            res.reserve(size());\n        \
    \    for (unsigned int p = 1; p < size(); p <<= 1) {\n                auto res_poly\
    \ = add_rank<T>(res);\n                auto poly = add_rank<T>(cut_upper(p));\n\
    \                subset_transform::zeta(res_poly);\n                subset_transform::zeta(poly);\n\
    \                for (unsigned int i = 0; i < p; ++i) {\n                    poly[i]\
    \ *= res_poly[i], poly[i] *= res_poly[i];\n                    for (auto &e :\
    \ poly[i]) e *= -1;\n                }\n                subset_transform::mobius(poly);\n\
    \                res.concat(remove_rank<T>(poly));\n            }\n          \
    \  return res;\n        }\n        SPS sqrt() {\n            using namespace suisen::internal::arithmetic_operator;\n\
    \            using namespace suisen::internal::subset_convolution;\n\n       \
    \     SPS res { ::sqrt(front()) };\n            assert(res[0] * res[0] == front());\n\
    \            res.reserve(size());\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) {\n                auto res_poly = add_rank<T>(res);\n            \
    \    auto poly = add_rank<T>(cut_upper(p));\n                subset_transform::zeta(res_poly);\n\
    \                subset_transform::zeta(poly);\n                for (unsigned\
    \ int i = 0; i < p; ++i) {\n                    unsigned int n = res_poly[i].size();\n\
    \                    for (auto &e : res_poly[i]) e *= 2;\n                   \
    \ std::vector<T> res_inv(n, 0);\n                    T v = ::inv(res_poly[i][0]);\n\
    \                    for (unsigned int j = 0; j < n; ++j) {\n                \
    \        res_inv[j] = j == 0;\n                        for (unsigned int k = 0;\
    \ k < j; ++k) {\n                            res_inv[j] -= res_poly[i][j - k]\
    \ * res_inv[k];\n                        }\n                        res_inv[j]\
    \ *= v;\n                    }\n                    poly[i] *= res_inv;\n    \
    \            }\n                subset_transform::mobius(poly);\n            \
    \    res.concat(remove_rank<T>(poly));\n            }\n            return res;\n\
    \        }\n        SPS exp() {\n            SPS res { ::exp(front()) };\n   \
    \         res.reserve(size());\n            for (unsigned int p = 1; p < size();\
    \ p <<= 1) res.concat(cut_upper(p) * res);\n            return res;\n        }\n\
    \        SPS log() {\n            SPS res { ::log(front()) };\n            res.reserve(size());\n\
    \            SPS inv_ = cut_lower(size() >> 1).inv();\n            for (unsigned\
    \ int p = 1; p < size(); p <<= 1) res.concat(cut_upper(p) * inv_.cut_lower(p));\n\
    \            return res;\n        }\n        SPS pow(long long k) {\n        \
    \    using namespace suisen::internal::arithmetic_operator;\n            using\
    \ namespace suisen::internal::subset_convolution;\n\n            T c = (*this)[0];\n\
    \            if (c == 0) {\n                int n = cardinality();\n         \
    \       if (n < k) return SPS(n, 0);\n                auto res_poly = add_rank<T>(one(n));\n\
    \                auto cur_poly = add_rank<T>(SPS(*this));\n                for\
    \ (; k; k >>= 1) {\n                    for (unsigned int i = 0; i < size(); ++i)\
    \ {\n                        if (k & 1) res_poly[i] *= cur_poly[i];\n        \
    \                cur_poly[i] *= std::vector<T>(cur_poly[i]);\n               \
    \     }\n                }\n                return SPS(remove_rank<T>(res_poly));\n\
    \            }\n            T pow_c = ::pow(c, k);\n            SPS f = *this\
    \ / c;\n            f = (T(k) * f.log()).exp();\n            for (auto &e : f)\
    \ e *= pow_c;\n            return f;\n        }\n\n    private:\n        using\
    \ base_type::assign;\n        using base_type::push_back;\n        using base_type::emplace_back;\n\
    \        using base_type::pop_back;\n        using base_type::insert;\n      \
    \  using base_type::emplace;\n        using base_type::erase;\n        using base_type::clear;\n\
    \        using base_type::resize;\n\n        static constexpr int ceil_pow2(unsigned\
    \ int n) {\n            unsigned int res = 1;\n            while (res < n) res\
    \ <<= 1;\n            return res;\n        }\n\n        void ensure(unsigned int\
    \ n) {\n            if (size() < n) resize(n, 0);\n        }\n};\n\n} // namespace\
    \ suisen\n\n#endif // SUISEN_SPS\n"
  dependsOn:
  - library/convolution/subset_convolution.hpp
  - library/transform/subset.hpp
  - library/convolution/convolution.hpp
  - library/math/modint_extension.hpp
  isVerificationFile: false
  path: library/math/sps.hpp
  requiredBy: []
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: LIBRARY_SOME_WA
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
