#ifndef SUISEN_FACTORIAL_EMBEDED
#define SUISEN_FACTORIAL_EMBEDED

#include <iostream>
#include <limits>

namespace suisen {
    // write (iB)! for i=0,1,...,(MOD-1)/B
    template <int MOD, int B>
    void write_embeded_factorial(std::ostream& out) {
        constexpr int D = (MOD - 1) / B + 1;

        out << "namespace suisen::internal::factorial_embeded {" << '\n';
        out << "    static constexpr int MOD = " << MOD << ";" << '\n';
        out << "    static constexpr int B = " << B << ";" << '\n';
        out << "    static constexpr int D = " << D << ";" << '\n';
        out << "    static constexpr int F[D]{" << '\n';
        out << "        ";
        long long f = 1;
        for (int i = 0; i < D; ++i) {
            out << f << ",";
            if (i == D - 1) break;
            const int l = i * B + 1, r = (i + 1) * B;
            for (int j = l; j <= r; ++j) f = f * j % MOD;
        }
        out << '\n';
        out << "    };" << '\n';
        out << "    constexpr int factorial_embeded(long long n) {" << '\n';
        out << "        if (n >= MOD) return 0;" << '\n';
        out << "        int q = n / B;" << '\n';
        out << "        long long ans = F[q];" << '\n';
        out << "        for (long long i = q * B + 1; i <= n; ++i) {" << '\n';
        out << "            ans = ans * i % MOD;" << '\n';
        out << "        }" << '\n';
        out << "        return ans;" << '\n';
        out << "    }" << '\n';
        out << "}" << '\n';
        out << "using suisen::internal::factorial_embeded::factorial_embeded;" << '\n';
        out.flush();
    }
} // namespace suisen


#endif // SUISEN_FACTORIAL_EMBEDED
