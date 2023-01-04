---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/relaxed_convolution.hpp
    title: Relaxed Convolution
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc230/tasks/abc230_h
    links:
    - https://atcoder.jp/contests/abc230/tasks/abc230_h
  bundledCode: "#line 1 \"test/src/convolution/relaxed_convolution/abc230_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc230/tasks/abc230_h\"\n\n#include\
    \ <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\n\
    using mint = atcoder::modint998244353;\n\n#line 1 \"library/math/inv_mods.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <typename mint>\n\
    \    class inv_mods {\n    public:\n        inv_mods() {}\n        inv_mods(int\
    \ n) { ensure(n); }\n        const mint& operator[](int i) const {\n         \
    \   ensure(i);\n            return invs[i];\n        }\n        static void ensure(int\
    \ n) {\n            int sz = invs.size();\n            if (sz < 2) invs = { 0,\
    \ 1 }, sz = 2;\n            if (sz < n + 1) {\n                invs.resize(n +\
    \ 1);\n                for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod\
    \ / i) * invs[mod % i];\n            }\n        }\n    private:\n        static\
    \ std::vector<mint> invs;\n        static constexpr int mod = mint::mod();\n \
    \   };\n    template <typename mint>\n    std::vector<mint> inv_mods<mint>::invs{};\n\
    \n    template <typename mint>\n    std::vector<mint> get_invs(const std::vector<mint>&\
    \ vs) {\n        const int n = vs.size();\n\n        mint p = 1;\n        for\
    \ (auto& e : vs) {\n            p *= e;\n            assert(e != 0);\n       \
    \ }\n        mint ip = p.inv();\n\n        std::vector<mint> rp(n + 1);\n    \
    \    rp[n] = 1;\n        for (int i = n - 1; i >= 0; --i) {\n            rp[i]\
    \ = rp[i + 1] * vs[i];\n        }\n        std::vector<mint> res(n);\n       \
    \ for (int i = 0; i < n; ++i) {\n            res[i] = ip * rp[i + 1];\n      \
    \      ip *= vs[i];\n        }\n        return res;\n    }\n}\n\n\n#line 1 \"\
    library/convolution/relaxed_convolution.hpp\"\n\n\n\n#line 5 \"library/convolution/relaxed_convolution.hpp\"\
    \n\nnamespace suisen {\n    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
    \    template <typename T>\n    struct RelaxedConvolution {\n        using value_type\
    \ = T;\n        using polynomial_type = std::vector<value_type>;\n        using\
    \ convolution_type = polynomial_type(*)(const polynomial_type&, const polynomial_type&);\n\
    \n        RelaxedConvolution() = default;\n        RelaxedConvolution(const convolution_type\
    \ &convolve) : _convolve(convolve), _n(0), _f{}, _g{}, _h{} {}\n\n        void\
    \ set_convolve_function(const convolution_type &convolve) {\n            _convolve\
    \ = convolve;\n        }\n\n        value_type append(const value_type &fi, const\
    \ value_type &gi) {\n            ++_n;\n            _f.push_back(fi), _g.push_back(gi);\n\
    \            for (int p = 1;; p <<= 1) {\n                int l1 = _n - p, r1\
    \ = _n, l2 = p - 1, r2 = l2 + p;\n                add(l1 + l2, range_convolve(l1,\
    \ r1, l2, r2));\n                if (l1 == l2) break;\n                add(l1\
    \ + l2, range_convolve(l2, r2, l1, r1));\n                if (not (_n & p)) break;\n\
    \            }\n            return _h[_n - 1];\n        }\n\n        const value_type&\
    \ operator[](int i) const {\n            return _h[i];\n        }\n        polynomial_type\
    \ get() const {\n            return _h;\n        }\n\n    private:\n        convolution_type\
    \ _convolve = [](const polynomial_type&, const polynomial_type&) -> polynomial_type\
    \ { assert(false); };\n        int _n;\n        polynomial_type _f, _g, _h;\n\n\
    \        polynomial_type range_convolve(int l1, int r1, int l2, int r2) {\n  \
    \          return _convolve(polynomial_type(_f.begin() + l1, _f.begin() + r1),\
    \ polynomial_type(_g.begin() + l2, _g.begin() + r2));\n        }\n\n        void\
    \ add(std::size_t bias, const polynomial_type &h) {\n            if (_h.size()\
    \ < bias + h.size()) _h.resize(bias + h.size());\n            for (std::size_t\
    \ i = 0; i < h.size(); ++i) _h[bias + i] += h[i];\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n#line 12 \"test/src/convolution/relaxed_convolution/abc230_h.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<mint> c(n + 1);\n\
    \    for (int i = 0; i < m; ++i) {\n        int w;\n        std::cin >> w;\n \
    \       c[w] = 1;\n    }\n    suisen::inv_mods<mint> invs(n);\n\n    suisen::RelaxedConvolution<mint>\
    \ h{ [](const auto& f, const auto &g) { return atcoder::convolution(f, g); } };\n\
    \n    std::vector<mint> f(n), g(n);\n    for (int w = 1; w < n; ++w) {\n     \
    \   for (int i = 1; i * w - 1 < n; ++i) {\n            g[i * w - 1] += w * (f[w\
    \ - 1] + c[w]);\n        }\n        f[w] = h.append((w == 1) + f[w - 1], g[w -\
    \ 1]) * invs[w];\n    }\n    f.erase(f.begin());\n\n    for (const auto &e : f)\
    \ {\n        std::cout << e.val() << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc230/tasks/abc230_h\"\n\n\
    #include <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\
    \nusing mint = atcoder::modint998244353;\n\n#include \"library/math/inv_mods.hpp\"\
    \n#include \"library/convolution/relaxed_convolution.hpp\"\n\nint main() {\n \
    \   std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ m;\n    std::cin >> n >> m;\n\n    std::vector<mint> c(n + 1);\n    for (int\
    \ i = 0; i < m; ++i) {\n        int w;\n        std::cin >> w;\n        c[w] =\
    \ 1;\n    }\n    suisen::inv_mods<mint> invs(n);\n\n    suisen::RelaxedConvolution<mint>\
    \ h{ [](const auto& f, const auto &g) { return atcoder::convolution(f, g); } };\n\
    \n    std::vector<mint> f(n), g(n);\n    for (int w = 1; w < n; ++w) {\n     \
    \   for (int i = 1; i * w - 1 < n; ++i) {\n            g[i * w - 1] += w * (f[w\
    \ - 1] + c[w]);\n        }\n        f[w] = h.append((w == 1) + f[w - 1], g[w -\
    \ 1]) * invs[w];\n    }\n    f.erase(f.begin());\n\n    for (const auto &e : f)\
    \ {\n        std::cout << e.val() << '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/math/inv_mods.hpp
  - library/convolution/relaxed_convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/relaxed_convolution/abc230_h.test.cpp
  requiredBy: []
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/relaxed_convolution/abc230_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/relaxed_convolution/abc230_h.test.cpp
- /verify/test/src/convolution/relaxed_convolution/abc230_h.test.cpp.html
title: test/src/convolution/relaxed_convolution/abc230_h.test.cpp
---
