#ifndef SUISEN_BERLEKAMP_MASSEY
#define SUISEN_BERLEKAMP_MASSEY

#include <cassert>
#include <vector>

namespace suisen {
    /**
     * @brief Find linear recurrence in O(|s|^2) time
     * @tparam F Arbitrary field (operator +, -, *, /, +=, -=, *=, /= must be defined)
     * @param s Prefix of a linearly reccurent sequence
     * @return The vector of length L+1 c s.t. c_0=1 and s_i=Sum[j=1,L]c_i*s_{i-j}=0 for all i>=L, where L is the minimum integer s.t. there exists such c of length L+1.
     */
    template <typename F>
    std::vector<F> find_linear_recuurence(const std::vector<F>& s) {
        std::vector<F> B{ 1 }, C{ 1 };
        B.reserve(s.size()), C.reserve(s.size());
        F b = 1;
        for (std::size_t N = 0, L = 0, x = 1; N < s.size(); ++N) {
            F d = s[N];
            for (std::size_t i = 1; i <= L; ++i) d += C[i] * s[N - i];
            if (d == 0) {
                ++x;
            } else {
                F c = d / b;
                if (C.size() < B.size() + x) C.resize(B.size() + x);
                if (2 * L > N) {
                    for (std::size_t i = 0; i < B.size(); ++i) C[x + i] -= c * B[i];
                    ++x;
                } else {
                    std::vector<F> T = C;
                    for (std::size_t i = 0; i < B.size(); ++i) C[x + i] -= c * B[i];
                    L = N + 1 - L, B = std::move(T), b = d, x = 1;
                }
            }
        }
        while (C.size() and C.back() == 0) C.pop_back();
        const std::size_t L = C.size() - 1;
        for (std::size_t N = 1; N <= L; ++N) C[N] = -C[N];
        return C;
    }
} // namespace suisen


#endif // SUISEN_BERLEKAMP_MASSEY
