#ifndef SUISEN_BOSTAN_MORI
#define SUISEN_BOSTAN_MORI

namespace suisen {
    template <typename FPSType>
    typename FPSType::value_type bostan_mori(FPSType P, FPSType Q, unsigned long long n) {
        auto alternate = [](FPSType&& a, bool odd) -> FPSType&& {
            int i = 0;
            for (int j = odd; j < int(a.size()); j += 2) a[i++] = a[j];
            a.erase(a.begin() + i, a.end());
            return std::move(a);
        };
        for (; n; n >>= 1) {
            if (n < (unsigned long long)(P.size())) P.resize(n + 1);
            if (n < (unsigned long long)(Q.size())) Q.resize(n + 1);
            FPSType mQ = Q;
            for (int i = 1; i < int(Q.size()); i += 2) mQ[i] = -mQ[i];
            P = alternate(P * mQ, n & 1);
            Q = alternate(Q * mQ, 0);
        }
        return P.size() ? P[0] / Q[0] : 0;
    }

    template <typename FPSType>
    typename FPSType::value_type nth_term_of_linearly_recurrent_sequence(const FPSType& a, const FPSType& c, const unsigned long long n) {
        const int K = c.size();
        assert(K <= a.size());
        FPSType Q(K + 1);
        Q[0] = 1;
        for (int i = 0; i < K; ++i) {
            Q[i + 1] = -c[i];
        }
        FPSType P = a * Q;
        P.cut(K);
        return bostan_mori(P, Q, n);
    }

} // namespace suisen

#endif // SUISEN_BOSTAN_MORI