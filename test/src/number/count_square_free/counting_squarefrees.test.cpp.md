---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/count_square_free.hpp
    title: library/number/count_square_free.hpp
  - icon: ':heavy_check_mark:'
    path: library/number/kth_root_round.hpp
    title: $\lfloor a ^ {\frac{1}{k}}\rfloor, \lceil a ^ {\frac{1}{k}}\rceil$
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/counting_squarefrees
    links:
    - https://judge.yosupo.jp/problem/counting_squarefrees
  bundledCode: "#line 1 \"test/src/number/count_square_free/counting_squarefrees.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/counting_squarefrees\"\n\n\
    #line 1 \"library/number/count_square_free.hpp\"\n\n\n\n#include <cmath>\n#include\
    \ <cstdint>\n#include <vector>\n\n#line 1 \"library/number/kth_root_round.hpp\"\
    \n\n\n\n#line 5 \"library/number/kth_root_round.hpp\"\n#include <type_traits>\n\
    \nnamespace suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T floor_kth_root(T x, int k) {\n        if (k\
    \ == 1 or x == 0 or x == 1) return x;\n        if (k == 2) return ::sqrtl(x);\n\
    \        if (k >= 64) return 1;\n        T res = ::powl(x, ::nextafterl(1 / (long\
    \ double) k, 0));\n        while (::powl(res + 1, k) <= x) ++res;\n        return\
    \ res;\n    }\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T ceil_kth_root(T x, int k) {\n        T res\
    \ = floor_kth_root(x, k);\n        res += ::powl(res, k) < x;\n        return\
    \ res;\n    }\n} // namespace suisen\n\n\n\n#line 9 \"library/number/count_square_free.hpp\"\
    \n\nnamespace suisen {\n    // O(n^(2/5) log log n)\n    long long count_square_free(long\
    \ long n) {\n        if (n <= 0) return 0;\n        if (n <= 3) return n;\n\n\
    \        const int I = std::min<int>(floor_kth_root(n, 5) * 2, floor_kth_root(n\
    \ / 4, 3));\n        // NOTE. floor(sqrt(n/i)) = floor(sqrt(floor(n/i)))\n   \
    \     const int D = ::sqrtl(n / I);\n\n        uint64_t ans = 0;\n\n        std::vector<int>\
    \ mobius(D + 1);\n        mobius[1] = 1;\n        std::vector<int8_t> sieve(D\
    \ + 1, 1);\n        for (int p = 2; p <= D; ++p) if (sieve[p]) {\n           \
    \ if (const int vmax = D / p; vmax < p) { // <==> p * p > D, so the sieve is complete.\n\
    \                for (int v = vmax; v; --v) if (mobius[v]) mobius[v * p] = -mobius[v];\n\
    \            } else {\n                for (int v = vmax; v >= p; --v) {\n   \
    \                 if (mobius[v]) mobius[v * p] = -mobius[v];\n               \
    \     sieve[v * p] = false;\n                }\n                for (int v = p\
    \ - 1; v; --v) if (mobius[v]) mobius[v * p] = -mobius[v];\n            }\n   \
    \     }\n\n        for (int i = 1; i <= D; ++i) if (mobius[i]) ans += mobius[i]\
    \ * (n / (1LL * i * i));\n\n        auto& mertens = mobius;\n        for (int\
    \ i = 1; i <= D; ++i) mertens[i] += mertens[i - 1];\n\n        std::vector<int>\
    \ mertens_large(I + 1);\n        for (int i = I - 1; i >= 1; --i) {\n        \
    \    const int xi = ::sqrtl(n / i);\n            const int h = ::sqrt(xi), quo_num\
    \ = 2 * h - (h == xi / h);\n            auto quo = [xi, h, quo_num](int i) ->\
    \ int {\n                return i < h ? i + 1 : double(xi) / (2 * h - (quo_num\
    \ & 1) - i);\n            };\n            long long sum = 1;\n            for\
    \ (int t = 1, l = 1; t < quo_num; ++t) {\n                int r = quo(t), q =\
    \ quo(quo_num - t - 1);\n                sum -= 1LL * (r - l) * (q <= D ? mertens[q]\
    \ : mertens_large[i * r * r]);\n                l = r;\n            }\n      \
    \      ans += (mertens_large[i] = sum);\n        }\n        return ans - 1LL *\
    \ (I - 1) * mertens[D];\n    }\n} // namespace suisen\n\n\n\n#line 4 \"test/src/number/count_square_free/counting_squarefrees.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n    long long n;\n    std::cin >> n;\n\
    \    std::cout << suisen::count_square_free(n) << std::endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_squarefrees\"\n\
    \n#include \"library/number/count_square_free.hpp\"\n\n#include <iostream>\n\n\
    int main() {\n    long long n;\n    std::cin >> n;\n    std::cout << suisen::count_square_free(n)\
    \ << std::endl;\n}"
  dependsOn:
  - library/number/count_square_free.hpp
  - library/number/kth_root_round.hpp
  isVerificationFile: true
  path: test/src/number/count_square_free/counting_squarefrees.test.cpp
  requiredBy: []
  timestamp: '2024-01-31 04:55:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/count_square_free/counting_squarefrees.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/count_square_free/counting_squarefrees.test.cpp
- /verify/test/src/number/count_square_free/counting_squarefrees.test.cpp.html
title: test/src/number/count_square_free/counting_squarefrees.test.cpp
---
