#ifndef SUISEN_SIEVE_OF_ERATOSTHENES
#define SUISEN_SIEVE_OF_ERATOSTHENES

#include <cmath>

#include "library/number/internal_eratosthenes.hpp"

namespace suisen {

template <unsigned int N>
class SimpleSieve {
    private:
        static constexpr unsigned int siz = N / internal::sieve::PROD + 1;
        static std::uint8_t flag[siz];
    public:
        SimpleSieve() {
            using namespace internal::sieve;
            flag[0] |= 1;
            unsigned int k_max = (unsigned int) std::sqrt(N + 2) / PROD;
            for (unsigned int kp = 0; kp <= k_max; ++kp) {
                for (std::uint8_t bits = ~flag[kp]; bits; bits &= bits - 1) {
                    const std::uint8_t mp = mask_to_index(bits & -bits), m = RM[mp];
                    unsigned int kr = kp * (PROD * kp + 2 * m) + m * m / PROD;
                    for (std::uint8_t mq = mp; kr < siz; kr += kp * DR[mq] + DF[mp][mq], ++mq &= 7) {
                        flag[kr] |= MASK[mp][mq];
                    }
                }
            }
        }
        inline bool is_prime(const unsigned int p) const {
            using namespace internal::sieve;
            switch (p) {
                case 2: case 3: case 5: return true;
                default:
                    switch (p % PROD) {
                        case RM[0]: return ((flag[p / PROD] >> 0) & 1) == 0;
                        case RM[1]: return ((flag[p / PROD] >> 1) & 1) == 0;
                        case RM[2]: return ((flag[p / PROD] >> 2) & 1) == 0;
                        case RM[3]: return ((flag[p / PROD] >> 3) & 1) == 0;
                        case RM[4]: return ((flag[p / PROD] >> 4) & 1) == 0;
                        case RM[5]: return ((flag[p / PROD] >> 5) & 1) == 0;
                        case RM[6]: return ((flag[p / PROD] >> 6) & 1) == 0;
                        case RM[7]: return ((flag[p / PROD] >> 7) & 1) == 0;
                        default: return false;
                    }
            }
        }
};
template <unsigned int N>
std::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];

template <unsigned int N>
class Sieve {
    private:
        static unsigned int pf[N + internal::sieve::PROD];
    public:
        Sieve() {
            using namespace internal::sieve;
            pf[1] = 1;
            unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1) / PROD;
            for (unsigned int kp = 0; kp <= k_max; ++kp) {
                const int base_i = kp * 30;
                for (int mp = 0; mp < K; ++mp) {
                    const int m = RM[mp], i = base_i + m;
                    if (pf[i] == 0) {
                        unsigned int base_j = (kp * (PROD * kp + 2 * m) + m * m / PROD) * PROD;
                        for (std::uint8_t mq = mp; base_j < N; base_j += kp * DRP[mq] + DFP[mp][mq], ++mq &= 7) {
                            int j = base_j + OFFSET[mp][mq];
                            pf[j] = i;
                        }
                    }
                }
            }
        }
        inline bool is_prime(const unsigned int p) const {
            using namespace internal::sieve;
            switch (p) {
                case 2: case 3: case 5: return true;
                default:
                    switch (p % PROD) {
                        case RM[0]: case RM[1]: case RM[2]: case RM[3]:
                        case RM[4]: case RM[5]: case RM[6]: case RM[7]: return pf[p] == 0;
                        default: return false;
                    }
            }
        }
        inline int prime_factor(const unsigned int p) const {
            using namespace internal::sieve;
            switch (p % PROD) {
                case RM[0]: case RM[1]: case RM[2]: case RM[3]:
                case RM[4]: case RM[5]: case RM[6]: case RM[7]: return pf[p] ? pf[p] : p;
                case  0: case  2: case  4: case  6: case  8:
                case 10: case 12: case 14: case 16: case 18:
                case 20: case 22: case 24: case 26: case 28: return 2;
                case  3: case  9: case 15: case 21: case 27: return 3;
                case  5: case 25: return 5;
                default: assert(false);
            }
        }
};
template <unsigned int N>
unsigned int Sieve<N>::pf[N + internal::sieve::PROD];
} // namespace suisen

#endif // SUISEN_SIEVE_OF_ERATOSTHENES
