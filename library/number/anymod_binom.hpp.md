---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/number/linear_sieve.hpp
    title: library/number/linear_sieve.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://qiita.com/suisen_cp/items/d0ab7e728b98bbec818f
  bundledCode: "#line 1 \"library/number/linear_sieve.hpp\"\n#include <numeric>\n\
    #include <vector>\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
    class LinearSieve {\n    public:\n        LinearSieve(const unsigned int n) :\
    \ _n(n), min_prime_factor(std::vector<unsigned int>(n + 1)) {\n            std::iota(min_prime_factor.begin(),\
    \ min_prime_factor.end(), 0);\n            prime_list.reserve(_n / 3);\n     \
    \       for (unsigned int d = 2; d <= _n; ++d) {\n                if (min_prime_factor[d]\
    \ == d) prime_list.push_back(d);\n                const unsigned int prime_max\
    \ = std::min(min_prime_factor[d], _n / d);\n                for (unsigned int\
    \ prime : prime_list) {\n                    if (prime > prime_max) break;\n \
    \                   min_prime_factor[prime * d] = prime;\n                }\n\
    \            }\n        }\n        unsigned int prime_num() const { return prime_list.size();\
    \ }\n        const std::vector<unsigned int>& get_prime_list() const { return\
    \ prime_list; }\n        const std::vector<unsigned int>& get_min_prime_factor()\
    \ const { return min_prime_factor; }\n    private:\n        const unsigned int\
    \ _n;\n        std::vector<unsigned int> min_prime_factor;\n        std::vector<unsigned\
    \ int> prime_list;\n};\n} // namespace suisen\n#line 2 \"library/number/anymod_binom.hpp\"\
    \n\nnamespace suisen {\n/**\n * calc Binom[N, k] mod M for all k = 0, ..., N in\
    \ O(NlogM/loglogM) time.\n * \n * reference: https://qiita.com/suisen_cp/items/d0ab7e728b98bbec818f\n\
    \ */\ntemplate <typename mint>\nclass ArbitraryModBinomialCoefficients {\n   \
    \ public:\n        ArbitraryModBinomialCoefficients(const unsigned int N) :\n\
    \            _N(N), _M(mint::mod()), _sieve(LinearSieve(N)), _binom(std::vector<mint>(N\
    \ + 1)) {\n            solve();\n        }\n        inline mint operator[](const\
    \ unsigned int k) const { return _binom[k]; }\n        const std::vector<mint>&\
    \ get_coeffs() const { return _binom; }\n        const LinearSieve& get_sieve()\
    \ const { return _sieve; }\n    private:\n        const unsigned int _N, _M;\n\
    \        const LinearSieve _sieve;\n        std::vector<mint> _binom;\n\n    \
    \    void mod_invs(std::vector<mint>& invs) {\n            const auto &mpf = _sieve.get_min_prime_factor();\n\
    \            if (_N >= 1) invs[1] = 1;\n            for (unsigned int i = 2; i\
    \ <= _N; ++i) {\n                const unsigned int pf = mpf[i];\n           \
    \     if (pf == i) {\n                    if (_M % pf) invs[i] = mint(i).inv();\n\
    \                } else {\n                    invs[i] = invs[pf] * invs[i / pf];\n\
    \                }\n            }\n        }\n        \n        void precalc_powers(const\
    \ unsigned int L, const std::vector<unsigned int> &base_primes, std::vector<std::vector<mint>>\
    \ &powers) {\n            for (unsigned int i = 1; i <= L; ++i) {\n          \
    \      const unsigned int max_index = _N / (base_primes[i] - 1);\n           \
    \     powers[i].resize(max_index + 1);\n                const mint pi = base_primes[i];\n\
    \                powers[i][0] = 1;\n                for (unsigned int j = 0; j\
    \ < max_index; ++j) {\n                    powers[i][j + 1] = powers[i][j] * pi;\n\
    \                }\n            }\n        }\n\n        void solve() {\n     \
    \       auto &primes = _sieve.get_prime_list();\n            std::vector<unsigned\
    \ int> divisor_index(_N + 1, 0);\n            std::vector<unsigned int> p;\n \
    \           for (unsigned int prime : primes) {\n                if (_M % prime)\
    \ continue;\n                p.push_back(prime);\n                const unsigned\
    \ int sz = p.size();\n                for (unsigned int v = prime; v <= _N; v\
    \ += prime) divisor_index[v] = sz;\n            }\n            const unsigned\
    \ int L = p.size();\n            p.insert(p.begin(), 0);\n            std::vector<mint>\
    \ invs(_N + 1);\n            mod_invs(invs);\n            std::vector<std::vector<mint>>\
    \ powers(L + 1);\n            precalc_powers(L, p, powers);\n            const\
    \ unsigned int half = (_N + 1) / 2;\n            mint S = 1;\n            std::vector<unsigned\
    \ int> T(L, 0);\n            _binom[0] = 1;\n            for (unsigned int k =\
    \ 1; k <= half; ++k) {\n                unsigned int num = _N - k + 1, den = k;\n\
    \                while (divisor_index[num]) ++T[divisor_index[num]], num /= p[divisor_index[num]];\n\
    \                while (divisor_index[den]) --T[divisor_index[den]], den /= p[divisor_index[den]];\n\
    \                S *= num * invs[den];\n                _binom[k] = S;\n     \
    \           for (unsigned int i = 1; i <= L; ++i) _binom[k] *= powers[i][T[i]];\n\
    \            }\n            for (unsigned int k = half + 1; k <= _N; ++k) _binom[k]\
    \ = _binom[_N - k];\n        }\n};\n} // namespace suisen\n"
  code: "#include \"linear_sieve.hpp\"\n\nnamespace suisen {\n/**\n * calc Binom[N,\
    \ k] mod M for all k = 0, ..., N in O(NlogM/loglogM) time.\n * \n * reference:\
    \ https://qiita.com/suisen_cp/items/d0ab7e728b98bbec818f\n */\ntemplate <typename\
    \ mint>\nclass ArbitraryModBinomialCoefficients {\n    public:\n        ArbitraryModBinomialCoefficients(const\
    \ unsigned int N) :\n            _N(N), _M(mint::mod()), _sieve(LinearSieve(N)),\
    \ _binom(std::vector<mint>(N + 1)) {\n            solve();\n        }\n      \
    \  inline mint operator[](const unsigned int k) const { return _binom[k]; }\n\
    \        const std::vector<mint>& get_coeffs() const { return _binom; }\n    \
    \    const LinearSieve& get_sieve() const { return _sieve; }\n    private:\n \
    \       const unsigned int _N, _M;\n        const LinearSieve _sieve;\n      \
    \  std::vector<mint> _binom;\n\n        void mod_invs(std::vector<mint>& invs)\
    \ {\n            const auto &mpf = _sieve.get_min_prime_factor();\n          \
    \  if (_N >= 1) invs[1] = 1;\n            for (unsigned int i = 2; i <= _N; ++i)\
    \ {\n                const unsigned int pf = mpf[i];\n                if (pf ==\
    \ i) {\n                    if (_M % pf) invs[i] = mint(i).inv();\n          \
    \      } else {\n                    invs[i] = invs[pf] * invs[i / pf];\n    \
    \            }\n            }\n        }\n        \n        void precalc_powers(const\
    \ unsigned int L, const std::vector<unsigned int> &base_primes, std::vector<std::vector<mint>>\
    \ &powers) {\n            for (unsigned int i = 1; i <= L; ++i) {\n          \
    \      const unsigned int max_index = _N / (base_primes[i] - 1);\n           \
    \     powers[i].resize(max_index + 1);\n                const mint pi = base_primes[i];\n\
    \                powers[i][0] = 1;\n                for (unsigned int j = 0; j\
    \ < max_index; ++j) {\n                    powers[i][j + 1] = powers[i][j] * pi;\n\
    \                }\n            }\n        }\n\n        void solve() {\n     \
    \       auto &primes = _sieve.get_prime_list();\n            std::vector<unsigned\
    \ int> divisor_index(_N + 1, 0);\n            std::vector<unsigned int> p;\n \
    \           for (unsigned int prime : primes) {\n                if (_M % prime)\
    \ continue;\n                p.push_back(prime);\n                const unsigned\
    \ int sz = p.size();\n                for (unsigned int v = prime; v <= _N; v\
    \ += prime) divisor_index[v] = sz;\n            }\n            const unsigned\
    \ int L = p.size();\n            p.insert(p.begin(), 0);\n            std::vector<mint>\
    \ invs(_N + 1);\n            mod_invs(invs);\n            std::vector<std::vector<mint>>\
    \ powers(L + 1);\n            precalc_powers(L, p, powers);\n            const\
    \ unsigned int half = (_N + 1) / 2;\n            mint S = 1;\n            std::vector<unsigned\
    \ int> T(L, 0);\n            _binom[0] = 1;\n            for (unsigned int k =\
    \ 1; k <= half; ++k) {\n                unsigned int num = _N - k + 1, den = k;\n\
    \                while (divisor_index[num]) ++T[divisor_index[num]], num /= p[divisor_index[num]];\n\
    \                while (divisor_index[den]) --T[divisor_index[den]], den /= p[divisor_index[den]];\n\
    \                S *= num * invs[den];\n                _binom[k] = S;\n     \
    \           for (unsigned int i = 1; i <= L; ++i) _binom[k] *= powers[i][T[i]];\n\
    \            }\n            for (unsigned int k = half + 1; k <= _N; ++k) _binom[k]\
    \ = _binom[_N - k];\n        }\n};\n} // namespace suisen"
  dependsOn:
  - library/number/linear_sieve.hpp
  isVerificationFile: false
  path: library/number/anymod_binom.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/anymod_binom.hpp
layout: document
redirect_from:
- /library/library/number/anymod_binom.hpp
- /library/library/number/anymod_binom.hpp.html
title: library/number/anymod_binom.hpp
---
