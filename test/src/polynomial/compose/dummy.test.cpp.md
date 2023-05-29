---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/polynomial/compose.hpp
    title: "\u5408\u6210"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/polynomial/compose/dummy.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/polynomial/compose.hpp\"\n\n\n\n#include <cmath>\n\
    #include <vector>\n#include <atcoder/convolution>\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    std::vector<mint> compose(const std::vector<mint>& f, std::vector<mint>\
    \ g, const int n) {\n        std::vector<mint> res(n);\n        if (n == 0) return\
    \ res;\n        if (f.empty()) return res;\n\n        if (std::find_if(g.begin(),\
    \ g.end(), [](mint x) { return x != 0; }) == g.end()) return res[0] = f[0], res;\n\
    \n        // taylor shift f(x + [x^0]g)\n        const std::vector<mint> fa =\
    \ [&]{\n            const mint a = std::exchange(g[0], 0);\n            const\
    \ int siz_f = f.size();\n            \n            std::vector<mint> fac(siz_f),\
    \ fac_inv(siz_f);\n            fac[0] = 1;\n            for (int i = 1; i <= siz_f\
    \ - 1; ++i) fac[i] = fac[i - 1] * i;\n            fac_inv[siz_f - 1] = fac[siz_f\
    \ - 1].inv();\n            for (int i = siz_f - 1; i >= 1; --i) fac_inv[i - 1]\
    \ = fac_inv[i] * i;\n\n            std::vector<mint> ec(siz_f), fa(siz_f);\n \
    \           mint p = 1;\n            for (int i = 0; i < siz_f; ++i, p *= a) {\n\
    \                ec[i] = p * fac_inv[i];\n                fa[siz_f - 1 - i] =\
    \ (i < int(f.size()) ? f[i] : 0) * fac[i];\n            }\n            fa = atcoder::convolution(fa,\
    \ ec), fa.resize(siz_f);\n            std::reverse(fa.begin(), fa.end());\n  \
    \          for (int i = 0; i < siz_f; ++i) {\n                fa[i] *= fac_inv[i];\n\
    \            }\n            if (siz_f > n) fa.resize(n);\n            return fa;\n\
    \        }();\n\n        const int sqn = ::sqrt(f.size()) + 1;\n\n        const\
    \ int z = [n]{\n            int z = 1;\n            while (z < 2 * n - 1) z <<=\
    \ 1;\n            return z;\n        }();\n        const mint iz = mint(z).inv();\n\
    \n        g.erase(g.begin());\n        g.resize(z);\n        atcoder::internal::butterfly(g);\n\
    \n        auto mult_g = [&](std::vector<mint> a) {\n            a.resize(z);\n\
    \            atcoder::internal::butterfly(a);\n            for (int j = 0; j <\
    \ z; ++j) a[j] *= g[j] * iz;\n            atcoder::internal::butterfly_inv(a);\n\
    \            a.resize(n);\n            return a;\n        };\n\n        std::vector<std::vector<mint>>\
    \ pow_g(sqn, std::vector<mint>(n));\n        pow_g[0][0] = 1;\n        for (int\
    \ i = 1; i < sqn; ++i) {\n            pow_g[i] = mult_g(pow_g[i - 1]);\n     \
    \   }\n\n        std::vector<mint> gl = mult_g(pow_g[sqn - 1]);\n        gl.resize(z);\n\
    \        atcoder::internal::butterfly(gl);\n\n        std::vector<mint> pow_gl(z);\n\
    \        pow_gl[0] = 1;\n\n        for (int i = 0; i < sqn; ++i) {\n         \
    \   const int off_i = i * sqn;\n            const int siz_i = n - off_i;\n   \
    \         if (siz_i < 0) break;\n            std::vector<mint> fg(siz_i);\n  \
    \          for (int j = 0; j < sqn; ++j) {\n                const int ij = i *\
    \ sqn + j;\n                if (ij >= int(fa.size())) break;\n\n             \
    \   const mint c = fa[ij];\n                const std::vector<mint>& gj = pow_g[j];\n\
    \                for (int k = 0; k < siz_i - j; ++k) {\n                    fg[j\
    \ + k] += c * gj[k];\n                }\n            }\n            fg.resize(z);\n\
    \            atcoder::internal::butterfly(pow_gl);\n            atcoder::internal::butterfly(fg);\n\
    \            for (int k = 0; k < z; ++k) {\n                fg[k] *= pow_gl[k]\
    \ * iz;\n                pow_gl[k] *= gl[k] * iz;\n            }\n           \
    \ atcoder::internal::butterfly_inv(pow_gl);\n            atcoder::internal::butterfly_inv(fg);\n\
    \            for (int k = 0; k < siz_i; ++k) {\n                res[off_i + k]\
    \ += fg[k];\n            }\n            std::fill(pow_gl.begin() + n, pow_gl.end(),\
    \ 0);\n        }\n        return res;\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 6 \"test/src/polynomial/compose/dummy.test.cpp\"\n\n#include <atcoder/modint>\n\
    \nusing mint = atcoder::modint998244353;\n\nnamespace atcoder {\n    std::istream&\
    \ operator>>(std::istream& in, mint& a) {\n        long long e; in >> e; a = e;\n\
    \        return in;\n    }\n\n    std::ostream& operator<<(std::ostream& out,\
    \ const mint& a) {\n        out << a.val();\n        return out;\n    }\n} //\
    \ namespace atcoder\n\nstd::vector<mint> naive(std::vector<mint> f, std::vector<mint>\
    \ g, int n) {\n    if (n == 0) return {};\n\n    std::vector<mint> powg(n);\n\
    \    powg[0] = 1;\n\n    std::vector<mint> fg(n);\n    for (mint fi : f) {\n \
    \       for (int j = 0; j < n; ++j) {\n            fg[j] += fi * powg[j];\n  \
    \      }\n        powg = atcoder::convolution(powg, g);\n        powg.resize(n);\n\
    \    }\n    return fg;\n}\n\nvoid test() {\n    {\n        std::vector<mint> f\
    \ { 1, 2, 3, 4 };\n        std::vector<mint> g { 5, 4, 3, 2 };\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n    {\n        std::vector<mint> f { 1, 2, 3, 4, 5, 6, 7 };\n\
    \        std::vector<mint> g { 5, 4, 3, 2 };\n        assert((suisen::compose(f,\
    \ g, 8) == naive(f, g, 8)));\n        assert((suisen::compose(f, g, 7) == naive(f,\
    \ g, 7)));\n        assert((suisen::compose(f, g, 6) == naive(f, g, 6)));\n  \
    \      assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f,\
    \ g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f,\
    \ g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n  \
    \      assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f,\
    \ g, 0) == naive(f, g, 0)));\n    }\n    {\n        std::vector<mint> f {};\n\
    \        std::vector<mint> g { 5, 4, 3 };\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n    {\n        std::vector<mint> f { 2 };\n        std::vector<mint>\
    \ g { 5, 4, 3 };\n        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n\
    \        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f,\
    \ g, 3) == naive(f, g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f,\
    \ g, 2)));\n        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n  \
    \      assert((suisen::compose(f, g, 0) == naive(f, g, 0)));\n    }\n    {\n \
    \       std::vector<mint> f { 2 };\n        std::vector<mint> g { 3 };\n     \
    \   assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f,\
    \ g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f,\
    \ g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n  \
    \      assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f,\
    \ g, 0) == naive(f, g, 0)));\n    }\n    {\n        std::vector<mint> f { 5, 4,\
    \ 3 };\n        std::vector<mint> g { 2 };\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n    {\n        std::vector<mint> f { 5, 4, 3 };\n        std::vector<mint>\
    \ g {};\n        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n     \
    \   assert((suisen::compose(f, g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f,\
    \ g, 3) == naive(f, g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f,\
    \ g, 2)));\n        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n  \
    \      assert((suisen::compose(f, g, 0) == naive(f, g, 0)));\n    }\n    {\n \
    \       std::vector<mint> f {};\n        std::vector<mint> g {};\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n}\n\nint main() {\n    test();\n    std::cout << \"Hello World\"\
    \ << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include \"library/polynomial/compose.hpp\"\n\n#include\
    \ <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\nnamespace atcoder\
    \ {\n    std::istream& operator>>(std::istream& in, mint& a) {\n        long long\
    \ e; in >> e; a = e;\n        return in;\n    }\n\n    std::ostream& operator<<(std::ostream&\
    \ out, const mint& a) {\n        out << a.val();\n        return out;\n    }\n\
    } // namespace atcoder\n\nstd::vector<mint> naive(std::vector<mint> f, std::vector<mint>\
    \ g, int n) {\n    if (n == 0) return {};\n\n    std::vector<mint> powg(n);\n\
    \    powg[0] = 1;\n\n    std::vector<mint> fg(n);\n    for (mint fi : f) {\n \
    \       for (int j = 0; j < n; ++j) {\n            fg[j] += fi * powg[j];\n  \
    \      }\n        powg = atcoder::convolution(powg, g);\n        powg.resize(n);\n\
    \    }\n    return fg;\n}\n\nvoid test() {\n    {\n        std::vector<mint> f\
    \ { 1, 2, 3, 4 };\n        std::vector<mint> g { 5, 4, 3, 2 };\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n    {\n        std::vector<mint> f { 1, 2, 3, 4, 5, 6, 7 };\n\
    \        std::vector<mint> g { 5, 4, 3, 2 };\n        assert((suisen::compose(f,\
    \ g, 8) == naive(f, g, 8)));\n        assert((suisen::compose(f, g, 7) == naive(f,\
    \ g, 7)));\n        assert((suisen::compose(f, g, 6) == naive(f, g, 6)));\n  \
    \      assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f,\
    \ g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f,\
    \ g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n  \
    \      assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f,\
    \ g, 0) == naive(f, g, 0)));\n    }\n    {\n        std::vector<mint> f {};\n\
    \        std::vector<mint> g { 5, 4, 3 };\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n    {\n        std::vector<mint> f { 2 };\n        std::vector<mint>\
    \ g { 5, 4, 3 };\n        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n\
    \        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f,\
    \ g, 3) == naive(f, g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f,\
    \ g, 2)));\n        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n  \
    \      assert((suisen::compose(f, g, 0) == naive(f, g, 0)));\n    }\n    {\n \
    \       std::vector<mint> f { 2 };\n        std::vector<mint> g { 3 };\n     \
    \   assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f,\
    \ g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f,\
    \ g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n  \
    \      assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f,\
    \ g, 0) == naive(f, g, 0)));\n    }\n    {\n        std::vector<mint> f { 5, 4,\
    \ 3 };\n        std::vector<mint> g { 2 };\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n    {\n        std::vector<mint> f { 5, 4, 3 };\n        std::vector<mint>\
    \ g {};\n        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));\n     \
    \   assert((suisen::compose(f, g, 4) == naive(f, g, 4)));\n        assert((suisen::compose(f,\
    \ g, 3) == naive(f, g, 3)));\n        assert((suisen::compose(f, g, 2) == naive(f,\
    \ g, 2)));\n        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));\n  \
    \      assert((suisen::compose(f, g, 0) == naive(f, g, 0)));\n    }\n    {\n \
    \       std::vector<mint> f {};\n        std::vector<mint> g {};\n        assert((suisen::compose(f,\
    \ g, 5) == naive(f, g, 5)));\n        assert((suisen::compose(f, g, 4) == naive(f,\
    \ g, 4)));\n        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));\n  \
    \      assert((suisen::compose(f, g, 2) == naive(f, g, 2)));\n        assert((suisen::compose(f,\
    \ g, 1) == naive(f, g, 1)));\n        assert((suisen::compose(f, g, 0) == naive(f,\
    \ g, 0)));\n    }\n}\n\nint main() {\n    test();\n    std::cout << \"Hello World\"\
    \ << std::endl;\n    return 0;\n}\n"
  dependsOn:
  - library/polynomial/compose.hpp
  isVerificationFile: true
  path: test/src/polynomial/compose/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-05-27 18:49:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/polynomial/compose/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/compose/dummy.test.cpp
- /verify/test/src/polynomial/compose/dummy.test.cpp.html
title: test/src/polynomial/compose/dummy.test.cpp
---
