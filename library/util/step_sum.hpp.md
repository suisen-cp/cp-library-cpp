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
    \ <cstdint>\n#include <utility>\n\nnamespace suisen {\n    struct BarrettReduction\
    \ {\n        uint32_t m;\n        uint64_t im;\n        BarrettReduction() = default;\n\
    \        BarrettReduction(uint32_t m) : m(m), im(uint64_t(0x7fff'ffff'ffff'ffff)\
    \ / m + 1) {}\n\n        // 0 <= n < 2**63\n        std::pair<uint64_t, uint32_t>\
    \ quorem(uint64_t n) const {\n            uint64_t q = uint64_t((__uint128_t(n)\
    \ * im) >> 63);\n            int64_t r = n - q * m;\n            if (r < 0) --q,\
    \ r += m;\n            return std::make_pair(q, r);\n        }\n        // 0 <=\
    \ n < 2**63\n        uint32_t quo(uint64_t n) const {\n            return quorem(n).first;\n\
    \        }\n        // 0 <= n < 2**63\n        uint32_t rem(uint64_t n) const\
    \ {\n            return quorem(n).second;\n        }\n\n        template <typename\
    \ Head, typename ...Tails>\n        uint32_t mul(Head &&head, Tails &&...tails)\
    \ const {\n            if constexpr (sizeof...(tails)) {\n                return\
    \ rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));\n            } else\
    \ {\n                return head;\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n#line 7 \"library/util/step_sum.hpp\"\n\nnamespace suisen {\n\
    \    template <typename T>\n    struct StepSum {\n        using value_type = T;\n\
    \n        StepSum() : StepSum(std::vector<value_type>{}, 1) {}\n        template\
    \ <typename Sequence>\n        StepSum(const Sequence &a, int step) : _sum(a.begin(),\
    \ a.end()), _step(step), _n(_sum.size()), _br(_step) {\n            for (int i\
    \ = _step; i < _n; ++i) {\n                _sum[i] += _sum[i - _step];\n     \
    \       }\n        }\n        // sum A_i for i = k (mod step) and i in [l, r)\n\
    \        value_type sum(int k, int l, int r) const {\n            if (r <= k or\
    \ r <= l or l >= _n) return 0;\n            const int t = _br.quo(std::min(_n,\
    \ r) - 1 - k);\n            T ans = _sum[t * _step + k];\n            if (l >\
    \ k) {\n                const int s = _br.quo(l - 1 - k);\n                ans\
    \ -= _sum[s * _step + k];\n            }\n            return ans;\n        }\n\
    \        // sum A_i for i = k (mod step) and i in [l, r)\n        value_type operator()(int\
    \ k, int l, int r) const { return sum(k, l, r); }\n\n        // sum[i] = a[i]\
    \ + a[i - step] + a[i - 2 * step] + ...\n        std::vector<value_type>& data()\
    \ { return _sum; }\n        // sum[i] = a[i] + a[i - step] + a[i - 2 * step] +\
    \ ...\n        const std::vector<value_type>& data() const { return _sum; }\n\
    \    private:\n        std::vector<value_type> _sum;\n        int _step, _n;\n\
    \        BarrettReduction _br;\n    };\n    template <typename Sequence>\n   \
    \ StepSum(Sequence, int) -> StepSum<std::decay_t<decltype(*std::declval<Sequence>().begin())>>;\n\
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
    \        std::vector<value_type> _sum;\n        int _step, _n;\n        BarrettReduction\
    \ _br;\n    };\n    template <typename Sequence>\n    StepSum(Sequence, int) ->\
    \ StepSum<std::decay_t<decltype(*std::declval<Sequence>().begin())>>;\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_STEP_SUM\n"
  dependsOn:
  - library/number/barrett_reduction.hpp
  isVerificationFile: false
  path: library/util/step_sum.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:33:28+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/util/step_sum/dummy.test.cpp
documentation_of: library/util/step_sum.hpp
layout: document
redirect_from:
- /library/library/util/step_sum.hpp
- /library/library/util/step_sum.hpp.html
title: library/util/step_sum.hpp
---
