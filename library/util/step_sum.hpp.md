---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/number/barrett_reduction.hpp
    title: Barrett Reduction
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/util/step_sum/dummy.test.cpp
    title: test/src/util/step_sum/dummy.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/step_sum.hpp\"\n\n\n\n#include <vector>\n\n\
    #line 1 \"library/number/barrett_reduction.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <utility>\n\nnamespace suisen {\n  \
    \  struct barrett {\n        constexpr barrett() : M(1), L(0) {}\n        constexpr\
    \ explicit barrett(uint32_t M) : M(M), L(uint64_t(-1) / M + 1) { assert(M); }\n\
    \        constexpr int32_t mod() { return M; }\n        constexpr uint32_t umod()\
    \ const { return M; }\n        // floor(x/M) (correctly works for all 0<=x<2^64)\n\
    \        template <bool care_M1 = true> constexpr uint64_t quo(uint64_t x) const\
    \ { return quorem<care_M1>(x).first; }\n        // x%M (correctly works for all\
    \ 0<=x<2^64)\n        template <bool care_M1 = true> constexpr uint32_t rem(uint64_t\
    \ x) const { return quorem<care_M1>(x).second; }\n        // { floor(x/M), x%M\
    \ } (correctly works for all 0<=x<2^64)\n        template <bool care_M1 = true>\
    \ constexpr std::pair<uint64_t, uint32_t> quorem(uint64_t x) const {\n       \
    \     if constexpr (care_M1) if (M == 1) return { x, 0 };\n            uint64_t\
    \ q = (__uint128_t(x) * L) >> 64;\n            int32_t r = x - q * M;\n      \
    \      if (r < 0) --q, r += M;\n            return { q, uint32_t(r) };\n     \
    \   }\n        // a*b mod M\n        template <bool care_M1 = true> constexpr\
    \ uint32_t mul(uint32_t a, uint32_t b) const { return rem<care_M1>(uint64_t(a)\
    \ * b); }\n    private:\n        uint32_t M; // mod\n        uint64_t L; // ceil(2^K\
    \ / M), where K = 64 (if M != 1)\n    };\n} // namespace suisen\n\n\n\n#line 7\
    \ \"library/util/step_sum.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T>\n    struct StepSum {\n        using value_type = T;\n\n        StepSum()\
    \ : StepSum(std::vector<value_type>{}, 1) {}\n        template <typename Sequence>\n\
    \        StepSum(const Sequence &a, int step) : _sum(a.begin(), a.end()), _step(step),\
    \ _n(_sum.size()), _br(_step) {\n            for (int i = _step; i < _n; ++i)\
    \ {\n                _sum[i] += _sum[i - _step];\n            }\n        }\n \
    \       // sum A_i for i = k (mod step) and i in [l, r)\n        value_type sum(int\
    \ k, int l, int r) const {\n            if (r <= k or r <= l or l >= _n) return\
    \ 0;\n            const int t = _br.quo(std::min(_n, r) - 1 - k);\n          \
    \  T ans = _sum[t * _step + k];\n            if (l > k) {\n                const\
    \ int s = _br.quo(l - 1 - k);\n                ans -= _sum[s * _step + k];\n \
    \           }\n            return ans;\n        }\n        // sum A_i for i =\
    \ k (mod step) and i in [l, r)\n        value_type operator()(int k, int l, int\
    \ r) const { return sum(k, l, r); }\n\n        // sum[i] = a[i] + a[i - step]\
    \ + a[i - 2 * step] + ...\n        std::vector<value_type>& data() { return _sum;\
    \ }\n        // sum[i] = a[i] + a[i - step] + a[i - 2 * step] + ...\n        const\
    \ std::vector<value_type>& data() const { return _sum; }\n    private:\n     \
    \   std::vector<value_type> _sum;\n        int _step, _n;\n        barrett _br;\n\
    \    };\n    template <typename Sequence>\n    StepSum(Sequence, int) -> StepSum<std::decay_t<decltype(*std::declval<Sequence>().begin())>>;\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_STEP_SUM\n#define SUISEN_STEP_SUM\n\n#include <vector>\n\n\
    #include \"library/number/barrett_reduction.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T>\n    struct StepSum {\n        using value_type = T;\n\n      \
    \  StepSum() : StepSum(std::vector<value_type>{}, 1) {}\n        template <typename\
    \ Sequence>\n        StepSum(const Sequence &a, int step) : _sum(a.begin(), a.end()),\
    \ _step(step), _n(_sum.size()), _br(_step) {\n            for (int i = _step;\
    \ i < _n; ++i) {\n                _sum[i] += _sum[i - _step];\n            }\n\
    \        }\n        // sum A_i for i = k (mod step) and i in [l, r)\n        value_type\
    \ sum(int k, int l, int r) const {\n            if (r <= k or r <= l or l >= _n)\
    \ return 0;\n            const int t = _br.quo(std::min(_n, r) - 1 - k);\n   \
    \         T ans = _sum[t * _step + k];\n            if (l > k) {\n           \
    \     const int s = _br.quo(l - 1 - k);\n                ans -= _sum[s * _step\
    \ + k];\n            }\n            return ans;\n        }\n        // sum A_i\
    \ for i = k (mod step) and i in [l, r)\n        value_type operator()(int k, int\
    \ l, int r) const { return sum(k, l, r); }\n\n        // sum[i] = a[i] + a[i -\
    \ step] + a[i - 2 * step] + ...\n        std::vector<value_type>& data() { return\
    \ _sum; }\n        // sum[i] = a[i] + a[i - step] + a[i - 2 * step] + ...\n  \
    \      const std::vector<value_type>& data() const { return _sum; }\n    private:\n\
    \        std::vector<value_type> _sum;\n        int _step, _n;\n        barrett\
    \ _br;\n    };\n    template <typename Sequence>\n    StepSum(Sequence, int) ->\
    \ StepSum<std::decay_t<decltype(*std::declval<Sequence>().begin())>>;\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_STEP_SUM\n"
  dependsOn:
  - library/number/barrett_reduction.hpp
  isVerificationFile: false
  path: library/util/step_sum.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/util/step_sum/dummy.test.cpp
documentation_of: library/util/step_sum.hpp
layout: document
title: Step Sum
---
## Step Sum
