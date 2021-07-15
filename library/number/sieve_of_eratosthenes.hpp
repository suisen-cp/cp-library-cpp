#include <vector>

namespace suisen {
template <unsigned int M>
class sieve_of_eratosthenes {
    public:
        sieve_of_eratosthenes() {
            pf.resize(M + 1);
            pf[0] = 0;
            for (unsigned int i = 1; i <= M; ++i) {
                if (i & 1) {
                    if (i % 3) pf[i] = i;
                    else pf[i] = 3;
                } else pf[i] = 2;
            }
            for (unsigned int i = 5; i * i <= M; i += 6) {
                unsigned int p1 = i, p2 = i + 2;
                if (pf[p1] == p1) {
                    for (unsigned int v = p1 * p1; v <= M; v += 2 * p1) {
                        pf[v] = p1;
                    }
                }
                if (pf[p2] == p2) {
                    for (unsigned int v = p2 * p2; v <= M; v += 2 * p2) {
                        pf[v] = p2;
                    }
                }
            }
        }
        bool is_prime(unsigned int v) {
            return pf[v] == v;
        }
        unsigned int prime_factor(unsigned int v) {
            return pf[v];
        }
        std::vector<std::pair<unsigned int, unsigned int>> factorize(unsigned int v) {
            std::vector<std::pair<unsigned int, unsigned int>> pfs;
            while (v != 1) {
                unsigned int p = pf[v], c = 0;
                do {
                    v /= p;
                    ++c;
                } while (v % p == 0);
                pfs.push_back({p, c});
            }
            return pfs;
        }
    private:
        std::vector<int> pf;
};
} // namespace suisen