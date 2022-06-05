---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
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
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/convolution/subset_convolution.hpp: line 5: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef SUISEN_SPS\n#define SUISEN_SPS\n\n#include \"library/convolution/subset_convolution.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct SPS : public std::vector<T>\
    \ {\n        using base_type = std::vector<T>;\n        using value_type = typename\
    \ base_type::value_type;\n        using size_type = typename base_type::size_type;\n\
    \n        using polynomial_type = ranked_subset_transform::polynomial_t<value_type>;\n\
    \n        using base_type::vector;\n\n        SPS() : SPS(0) {}\n        SPS(size_type\
    \ n) : SPS(n, value_type{ 0 }) {}\n        SPS(size_type n, const value_type&\
    \ val) : SPS(std::vector<value_type>(1 << n, val)) {}\n        SPS(const base_type&\
    \ a) : SPS(base_type(a)) {}\n        SPS(base_type&& a) : base_type(std::move(a))\
    \ {\n            const int n = this->size();\n            assert(n == (-n & n));\n\
    \        }\n        SPS(std::initializer_list<value_type> l) : SPS(base_type(l))\
    \ {}\n\n        static SPS one(int n) {\n            SPS f(n, value_type{ 0 });\n\
    \            f[0] = value_type{ 1 };\n            return f;\n        }\n\n   \
    \     void set_cardinality(int n) {\n            this->resize(1 << n, value_type{\
    \ 0 });\n        }\n        int cardinality() const {\n            return __builtin_ctz(this->size());\n\
    \        }\n\n        SPS cut_lower(size_type p) const {\n            return SPS(this->begin(),\
    \ this->begin() + p);\n        }\n        SPS cut_upper(size_type p) const {\n\
    \            return SPS(this->begin() + p, this->begin() + p + p);\n        }\n\
    \n        void concat(const SPS& upper) {\n            assert(this->size() ==\
    \ upper.size());\n            this->insert(this->end(), upper.begin(), upper.end());\n\
    \        }\n\n        SPS operator+() const {\n            return *this;\n   \
    \     }\n        SPS operator-() const {\n            SPS res(*this);\n      \
    \      for (auto& e : res) e = -e;\n            return res;\n        }\n     \
    \   SPS& operator+=(const SPS& g) {\n            for (size_type i = 0; i < g.size();\
    \ ++i) (*this)[i] += g[i];\n            return *this;\n        }\n        SPS&\
    \ operator-=(const SPS& g) {\n            for (size_type i = 0; i < g.size();\
    \ ++i) (*this)[i] -= g[i];\n            return *this;\n        }\n        SPS&\
    \ operator*=(const SPS& g) {\n            return *this = (zeta() *= g).mobius_inplace();\n\
    \        }\n        SPS& operator*=(const value_type &c) {\n            for (auto&\
    \ e : *this) e *= c;\n            return *this;\n        }\n        SPS& operator/=(const\
    \ value_type &c) {\n            value_type inv_c = ::inv(c);\n            for\
    \ (auto& e : *this) e *= inv_c;\n            return *this;\n        }\n      \
    \  friend SPS operator+(SPS f, const SPS& g) { f += g; return f; }\n        friend\
    \ SPS operator-(SPS f, const SPS& g) { f -= g; return f; }\n        friend SPS\
    \ operator*(SPS f, const SPS& g) { f *= g; return f; }\n        friend SPS operator*(SPS\
    \ f, const value_type &c) { f *= c; return f; }\n        friend SPS operator*(const\
    \ value_type &c, SPS f) { f *= c; return f; }\n        friend SPS operator/(SPS\
    \ f, const value_type &c) { f /= c; return f; }\n\n        SPS inv() {\n     \
    \       return zeta().inv_inplace().mobius_inplace();\n        }\n        SPS\
    \ sqrt() {\n            return zeta().sqrt_inplace().mobius_inplace();\n     \
    \   }\n        SPS exp() {\n            return zeta().exp_inplace().mobius_inplace();\n\
    \        }\n        SPS log() {\n            return zeta().log_inplace().mobius_inplace();\n\
    \        }\n        SPS pow(long long k) {\n            return zeta().pow_inplace(k).mobius_inplace();\n\
    \        }\n\n        struct ZetaSPS : public std::vector<polynomial_type> {\n\
    \            using base_type = std::vector<polynomial_type>;\n            ZetaSPS()\
    \ = default;\n            ZetaSPS(const SPS<value_type>& f) : base_type::vector(ranked_subset_transform::ranked_zeta(f)),\
    \ _d(f.cardinality()) {}\n\n            ZetaSPS operator+() const {\n        \
    \        return *this;\n            }\n            ZetaSPS operator-() const {\n\
    \                ZetaSPS res(*this);\n                for (auto& f : res) f =\
    \ -f;\n                return res;\n            }\n            friend ZetaSPS\
    \ operator+(ZetaSPS f, const ZetaSPS& g) { f += g; return f; }\n            friend\
    \ ZetaSPS operator-(ZetaSPS f, const ZetaSPS& g) { f -= g; return f; }\n     \
    \       friend ZetaSPS operator*(ZetaSPS f, const ZetaSPS& g) { f *= g; return\
    \ f; }\n            friend ZetaSPS operator*(ZetaSPS f, const value_type &c) {\
    \ f *= c; return f; }\n            friend ZetaSPS operator*(const value_type &c,\
    \ ZetaSPS f) { f *= c; return f; }\n            friend ZetaSPS operator/(ZetaSPS\
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
    \ << _d; ++i) (*this)[i] = (*this)[i].mul(rhs[i], _d);\n                return\
    \ *this;\n            }\n            ZetaSPS inv()  const { auto f = ZetaSPS(*this).inv_inplace();\
    \  return f; }\n            ZetaSPS sqrt() const { auto f = ZetaSPS(*this).sqrt_inplace();\
    \ return f; }\n            ZetaSPS exp()  const { auto f = ZetaSPS(*this).exp_inplace();\
    \  return f; }\n            ZetaSPS log()  const { auto f = ZetaSPS(*this).log_inplace();\
    \  return f; }\n            ZetaSPS pow(long long k) const { auto f = ZetaSPS(*this).pow_inplace(k);\
    \ return f; }\n            ZetaSPS& inv_inplace() {\n                for (auto&\
    \ f : *this) f = f.inv(_d);\n                return *this;\n            }\n  \
    \          ZetaSPS& sqrt_inplace() {\n                for (auto& f : *this) f\
    \ = f.sqrt(_d);\n                return *this;\n            }\n            ZetaSPS&\
    \ exp_inplace() {\n                for (auto& f : *this) f = f.exp(_d);\n    \
    \            return *this;\n            }\n            ZetaSPS& log_inplace()\
    \ {\n                for (auto& f : *this) f = f.log(_d);\n                return\
    \ *this;\n            }\n            ZetaSPS& pow_inplace(long long k) {\n   \
    \             for (auto& f : *this) f = f.pow(k, _d);\n                return\
    \ *this;\n            }\n            SPS<value_type> mobius_inplace() {\n    \
    \            return ranked_subset_transform::deranked_mobius<value_type>(*this);\n\
    \            }\n            SPS<value_type> mobius() const {\n               \
    \ auto rf = ZetaSPS(*this);\n                return ranked_subset_transform::deranked_mobius<value_type>(rf);\n\
    \            }\n        private:\n            int _d;\n        };\n\n        ZetaSPS\
    \ zeta() const {\n            return ZetaSPS(*this);\n        }\n    };\n} //\
    \ namespace suisen\n\n#endif // SUISEN_SPS\n"
  dependsOn:
  - library/convolution/subset_convolution.hpp
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/transform/subset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/math/sps.hpp
  requiredBy: []
  timestamp: '2022-06-04 18:33:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/sps/abc236_h.test.cpp
  - test/src/math/sps/arc105_f.test.cpp
  - test/src/math/sps/abc253_h_2.test.cpp
  - test/src/math/sps/abc253_h.test.cpp
  - test/src/math/sps/abc213_g.test.cpp
documentation_of: library/math/sps.hpp
layout: document
title: Set Power Series
---
## Set Power Series