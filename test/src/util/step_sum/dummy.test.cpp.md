---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/number/barrett_reduction.hpp
    title: Barrett Reduction
  - icon: ':x:'
    path: library/util/step_sum.hpp
    title: library/util/step_sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/util/step_sum/dummy.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/util/step_sum.hpp\"\n\n\n\n#include <vector>\n\
    \n#line 1 \"library/number/barrett_reduction.hpp\"\n\n\n\n#include <array>\n#include\
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
    } // namespace suisen\n\n\n\n#line 6 \"test/src/util/step_sum/dummy.test.cpp\"\
    \n\ntemplate <typename T>\nstruct StepSumNaive {\n    template <typename Sequence>\n\
    \    StepSumNaive(const Sequence& a, int step): _dat(a.begin(), a.end()), _step(step),\
    \ _n(_dat.size()) {}\n    T sum(int k, int l, int r) const {\n        T ans =\
    \ 0;\n        for (int i = k; i < std::min(r, _n); i += _step) {\n           \
    \ if (i >= l) {\n                ans += _dat[i];\n            }\n        }\n \
    \       return ans;\n    }\n    T operator()(int k, int l, int r) const { return\
    \ sum(k, l, r); }\nprivate:\n    std::vector<T> _dat;\n    int _step, _n;\n};\n\
    template <typename Sequence>\nStepSumNaive(Sequence, int) -> StepSumNaive<typename\
    \ Sequence::value_type>;\n\n#include <cassert>\n#include <random>\n\nvoid test()\
    \ {\n    std::mt19937 rng{0};\n\n    int n = 100, v = 10000000;\n    std::vector<int>\
    \ a(n);\n    for (auto& e : a) e = rng() % v - v / 2;\n\n    for (int step = 1;\
    \ step <= n; ++step) {\n        suisen::StepSum sum1(a, step);\n        StepSumNaive\
    \ sum2(a, step);\n        for (int k = 0; k < step; ++k) {\n            for (int\
    \ l = -10; l <= n + 10; ++l) {\n                for (int r = -10; r <= n + 10;\
    \ ++r) {\n                    if (sum1(k, l, r) != sum2(k, l, r)) {\n        \
    \                for (int e : a) std::cerr << e << \",\";\n                  \
    \      std::cerr << std::endl;\n                        std::cerr << \"step =\
    \ \" << step << std::endl;\n                        std::cerr << \"(k, l, r) =\
    \ (\" << k << \", \" << l << \", \" << r << \")\" << std::endl;\n\n          \
    \              std::cerr << \"Actual  :\" << sum1(k, l, r) << std::endl;\n   \
    \                     std::cerr << \"Expected:\" << sum2(k, l, r) << std::endl;\n\
    \                        assert(false);\n                    }\n             \
    \   }\n            }\n        }\n    }\n}\n\nstruct S {\n    using value_type\
    \ = int;\n    std::vector<int> a;\n    auto begin() const { return a.begin();\
    \ }\n    auto end() const { return a.end(); }\n};\n\nint main() {\n    suisen::StepSum\
    \ sum(S{std::vector<int>{1}}, 2);\n    suisen::StepSum sum2(std::vector<long long>{1},\
    \ 2);\n    test();\n    std::cout << \"Hello World\" << std::endl;\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include \"library/util/step_sum.hpp\"\n\ntemplate\
    \ <typename T>\nstruct StepSumNaive {\n    template <typename Sequence>\n    StepSumNaive(const\
    \ Sequence& a, int step): _dat(a.begin(), a.end()), _step(step), _n(_dat.size())\
    \ {}\n    T sum(int k, int l, int r) const {\n        T ans = 0;\n        for\
    \ (int i = k; i < std::min(r, _n); i += _step) {\n            if (i >= l) {\n\
    \                ans += _dat[i];\n            }\n        }\n        return ans;\n\
    \    }\n    T operator()(int k, int l, int r) const { return sum(k, l, r); }\n\
    private:\n    std::vector<T> _dat;\n    int _step, _n;\n};\ntemplate <typename\
    \ Sequence>\nStepSumNaive(Sequence, int) -> StepSumNaive<typename Sequence::value_type>;\n\
    \n#include <cassert>\n#include <random>\n\nvoid test() {\n    std::mt19937 rng{0};\n\
    \n    int n = 100, v = 10000000;\n    std::vector<int> a(n);\n    for (auto& e\
    \ : a) e = rng() % v - v / 2;\n\n    for (int step = 1; step <= n; ++step) {\n\
    \        suisen::StepSum sum1(a, step);\n        StepSumNaive sum2(a, step);\n\
    \        for (int k = 0; k < step; ++k) {\n            for (int l = -10; l <=\
    \ n + 10; ++l) {\n                for (int r = -10; r <= n + 10; ++r) {\n    \
    \                if (sum1(k, l, r) != sum2(k, l, r)) {\n                     \
    \   for (int e : a) std::cerr << e << \",\";\n                        std::cerr\
    \ << std::endl;\n                        std::cerr << \"step = \" << step << std::endl;\n\
    \                        std::cerr << \"(k, l, r) = (\" << k << \", \" << l <<\
    \ \", \" << r << \")\" << std::endl;\n\n                        std::cerr << \"\
    Actual  :\" << sum1(k, l, r) << std::endl;\n                        std::cerr\
    \ << \"Expected:\" << sum2(k, l, r) << std::endl;\n                        assert(false);\n\
    \                    }\n                }\n            }\n        }\n    }\n}\n\
    \nstruct S {\n    using value_type = int;\n    std::vector<int> a;\n    auto begin()\
    \ const { return a.begin(); }\n    auto end() const { return a.end(); }\n};\n\n\
    int main() {\n    suisen::StepSum sum(S{std::vector<int>{1}}, 2);\n    suisen::StepSum\
    \ sum2(std::vector<long long>{1}, 2);\n    test();\n    std::cout << \"Hello World\"\
    \ << std::endl;\n    return 0;\n}\n"
  dependsOn:
  - library/util/step_sum.hpp
  - library/number/barrett_reduction.hpp
  isVerificationFile: true
  path: test/src/util/step_sum/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-05-11 13:33:28+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/util/step_sum/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/util/step_sum/dummy.test.cpp
- /verify/test/src/util/step_sum/dummy.test.cpp.html
title: test/src/util/step_sum/dummy.test.cpp
---
