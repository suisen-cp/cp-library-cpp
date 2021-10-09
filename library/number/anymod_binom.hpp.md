---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
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
  bundledCode: "#line 1 \"library/number/anymod_binom.hpp\"\n\n\n\n#line 1 \"library/number/linear_sieve.hpp\"\
    \n\n\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ suisen {\n// referece: https://37zigen.com/linear-sieve/\nclass LinearSieve\
    \ {\n    public:\n        LinearSieve(const int n) : _n(n), min_prime_factor(std::vector<int>(n\
    \ + 1)) {\n            std::iota(min_prime_factor.begin(), min_prime_factor.end(),\
    \ 0);\n            prime_list.reserve(_n / 20);\n            for (int d = 2; d\
    \ <= _n; ++d) {\n                if (min_prime_factor[d] == d) prime_list.push_back(d);\n\
    \                const int prime_max = std::min(min_prime_factor[d], _n / d);\n\
    \                for (int prime : prime_list) {\n                    if (prime\
    \ > prime_max) break;\n                    min_prime_factor[prime * d] = prime;\n\
    \                }\n            }\n        }\n        int prime_num() const noexcept\
    \ { return prime_list.size(); }\n        /**\n         * Returns a vector of primes\
    \ in [0, n].\n         * It is guaranteed that the returned vector is sorted in\
    \ ascending order.\n         */\n        const std::vector<int>& get_prime_list()\
    \ const noexcept  {\n            return prime_list;\n        }\n        const\
    \ std::vector<int>& get_min_prime_factor() const noexcept { return min_prime_factor;\
    \ }\n        /**\n         * Returns a vector of `{ prime, index }`.\n       \
    \  * It is guaranteed that the returned vector is sorted in ascending order.\n\
    \         */\n        std::vector<std::pair<int, int>> factorize(int n) const\
    \ noexcept {\n            assert(0 < n and n <= _n);\n            std::vector<std::pair<int,\
    \ int>> prime_powers;\n            while (n > 1) {\n                int p = min_prime_factor[n],\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n    private:\n        const int _n;\n        std::vector<int> min_prime_factor;\n\
    \        std::vector<int> prime_list;\n};\n} // namespace suisen\n\n\n#line 5\
    \ \"library/number/anymod_binom.hpp\"\n\nnamespace suisen {\n/**\n * calc Binom[N,\
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
    \ = _binom[_N - k];\n        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ANY_MOD_BINOM\n#define SUISEN_ANY_MOD_BINOM\n\n#include \"\
    library/number/linear_sieve.hpp\"\n\nnamespace suisen {\n/**\n * calc Binom[N,\
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
    \ = _binom[_N - k];\n        }\n};\n} // namespace suisen\n\n#endif // SUISEN_ANY_MOD_BINOM\n"
  dependsOn:
  - library/number/linear_sieve.hpp
  isVerificationFile: false
  path: library/number/anymod_binom.hpp
  requiredBy: []
  timestamp: '2021-08-04 13:32:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/anymod_binom.hpp
layout: document
redirect_from:
- /library/library/number/anymod_binom.hpp
- /library/library/number/anymod_binom.hpp.html
title: library/number/anymod_binom.hpp
---
