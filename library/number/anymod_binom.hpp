#include "linear_sieve.hpp"

namespace suisen {
/**
 * calc Binom[N, k] mod M for all k = 0, ..., N in O(NlogM/loglogM) time.
 * 
 * reference: https://qiita.com/suisen_cp/items/d0ab7e728b98bbec818f
 */
template <typename mint>
class ArbitraryModBinomialCoefficients {
    public:
        ArbitraryModBinomialCoefficients(const unsigned int N) :
            _N(N), _M(mint::mod()), _sieve(LinearSieve(N)), _binom(std::vector<mint>(N + 1)) {
            solve();
        }
        inline mint operator[](const unsigned int k) const { return _binom[k]; }
        const std::vector<mint>& get_coeffs() const { return _binom; }
        const LinearSieve& get_sieve() const { return _sieve; }
    private:
        const unsigned int _N, _M;
        const LinearSieve _sieve;
        std::vector<mint> _binom;

        void mod_invs(std::vector<mint>& invs) {
            const auto &mpf = _sieve.get_min_prime_factor();
            if (_N >= 1) invs[1] = 1;
            for (unsigned int i = 2; i <= _N; ++i) {
                const unsigned int pf = mpf[i];
                if (pf == i) {
                    if (_M % pf) invs[i] = mint(i).inv();
                } else {
                    invs[i] = invs[pf] * invs[i / pf];
                }
            }
        }
        
        void precalc_powers(const unsigned int L, const std::vector<unsigned int> &base_primes, std::vector<std::vector<mint>> &powers) {
            for (unsigned int i = 1; i <= L; ++i) {
                const unsigned int max_index = _N / (base_primes[i] - 1);
                powers[i].resize(max_index + 1);
                const mint pi = base_primes[i];
                powers[i][0] = 1;
                for (unsigned int j = 0; j < max_index; ++j) {
                    powers[i][j + 1] = powers[i][j] * pi;
                }
            }
        }

        void solve() {
            auto &primes = _sieve.get_prime_list();
            std::vector<unsigned int> divisor_index(_N + 1, 0);
            std::vector<unsigned int> p;
            for (unsigned int prime : primes) {
                if (_M % prime) continue;
                p.push_back(prime);
                const unsigned int sz = p.size();
                for (unsigned int v = prime; v <= _N; v += prime) divisor_index[v] = sz;
            }
            const unsigned int L = p.size();
            p.insert(p.begin(), 0);
            std::vector<mint> invs(_N + 1);
            mod_invs(invs);
            std::vector<std::vector<mint>> powers(L + 1);
            precalc_powers(L, p, powers);
            const unsigned int half = (_N + 1) / 2;
            mint S = 1;
            std::vector<unsigned int> T(L, 0);
            _binom[0] = 1;
            for (unsigned int k = 1; k <= half; ++k) {
                unsigned int num = _N - k + 1, den = k;
                while (divisor_index[num]) ++T[divisor_index[num]], num /= p[divisor_index[num]];
                while (divisor_index[den]) --T[divisor_index[den]], den /= p[divisor_index[den]];
                S *= num * invs[den];
                _binom[k] = S;
                for (unsigned int i = 1; i <= L; ++i) _binom[k] *= powers[i][T[i]];
            }
            for (unsigned int k = half + 1; k <= _N; ++k) _binom[k] = _binom[_N - k];
        }
};
} // namespace suisen