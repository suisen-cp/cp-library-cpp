#ifndef SUISEN_PERMUTATION
#define SUISEN_PERMUTATION

#include <algorithm>
#include <numeric>
#include <vector>

namespace suisen {
    struct Permutation : public std::vector<int> {
        using base_type = std::vector<int>;
        using base_type::base_type;

        Permutation() : Permutation(0) {}
        Permutation(std::size_t n) : Permutation(int(n)) {}
        Permutation(int n) : base_type(n) {
            std::iota(begin(), end(), 0);
        }
        Permutation(const std::vector<int>& a) : std::vector<int>(a) {}
        Permutation(std::vector<int>&& a) : std::vector<int>(std::move(a)) {}

        // returns b s.t. b[i] = a[p[i]]
        template <typename T>
        std::vector<T> permute(const std::vector<T>& a) const {
            const int n = a.size();
            std::vector<T> res(n);
            for (int i = 0; i < n; ++i) res[i] = a[(*this)[i]];
            return res;
        }
        // returns b s.t. b[p[i]] = a[i]
        template <typename T>
        std::vector<T> inv_permute(const std::vector<T>& a) const {
            const int n = a.size();
            std::vector<T> res(n);
            for (int i = 0; i < n; ++i) res[(*this)[i]] = a[i];
            return res;
        }

        // returns p * q s.t. (p * q)[i] = p[q[i]]
        friend Permutation operator*(const Permutation& p, const Permutation& q) {
            return q.permute(p);
        }
        Permutation& operator*=(const Permutation& q) {
            return *this = *this * q;
        }
        Permutation inv() const {
            const int n = size();
            Permutation res(n);
            for (int i = 0; i < n; ++i) res[(*this)[i]] = i;
            return res;
        }
        Permutation pow(long long k) const {
            const int n = size();
            Permutation res(n), p = *this;
            for (; k; k >>= 1) {
                if (k & 1) res *= p;
                p *= p;
            }
            return res;
        }

        template <typename T, typename Comp = std::less<T>>
        static Permutation index_sort(const std::vector<T>& a, Comp comp = Comp{}) {
            Permutation p(a.size());
            std::sort(p.begin(), p.end(), [&](int i, int j) { return comp(a[i], a[j]); });
            return p;
        }
    };

    template <typename hash_t>
    struct PermutationHash {
        hash_t operator()(const Permutation &p) const {
            return hash(p);
        }
        /**
         * minimal perfect hash function for permutations.
         * complexity: O(n) time, O(n) extra space
         * reference: https://twitter.com/noshi91/status/1452081886025555972?s=20
         */
        static hash_t hash(const Permutation &per) {
            hash_t h = 0;
            const int n = per.size();
            Permutation p = per;
            Permutation q = per.inv();
            for (int i = n - 1; i >= 0; --i) {
                h = h * (i + 1) + p[i];
                p[q[i]] = p[i];
                q[p[i]] = q[i];
            }
            return h;
        }
        static Permutation unhash(int n, hash_t h) {
            Permutation p = Permutation(n), q = p;
            for (int i = 0; i < n; ++i) {
                p[i] = h % (i + 1), q[i] = q[p[i]];
                q[p[i]] = p[q[i]] = i;
                h /= i + 1;
            }
            return p;
        }
    };
} // namespace suisen

#endif // SUISEN_PERMUTATION
