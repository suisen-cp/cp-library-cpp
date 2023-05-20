#ifndef SUISEN_POLYNOMIAL_GCD
#define SUISEN_POLYNOMIAL_GCD

#include <array>
#include <cassert>
#include <tuple>

namespace suisen {
    namespace internal::poly_gcd {
        template <typename Polynomial>
        using PolynomialMatrix = std::array<std::array<Polynomial, 2>, 2>;

        template <typename Polynomial>
        PolynomialMatrix<Polynomial> e1() {
            return { Polynomial{1}, Polynomial{}, Polynomial{}, Polynomial{1} };
        }
        template <typename Polynomial>
        PolynomialMatrix<Polynomial> mul_mat(const PolynomialMatrix<Polynomial>& A, const PolynomialMatrix<Polynomial>& B) {
            PolynomialMatrix<Polynomial> C{};
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k) C[i][k] += A[i][j] * B[j][k];
                for (int j = 0; j < 2; ++j) C[i][j].cut_trailing_zeros();
            }
            return C;
        }
        template <typename Polynomial>
        std::array<Polynomial, 2> mul_vec(const PolynomialMatrix<Polynomial>& A, const std::array<Polynomial, 2>& x) {
            std::array<Polynomial, 2> y{};
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) y[i] += A[i][j] * x[j];
                y[i].cut_trailing_zeros();
            }
            return y;
        }

        template <typename Polynomial>
        std::pair<PolynomialMatrix<Polynomial>, Polynomial> half_gcd(Polynomial f, Polynomial g, int lo = -1) {
            PolynomialMatrix<Polynomial> P = e1<Polynomial>();
            while (g.size()) {
                assert(f.size() >= g.size());
                const int fd = f.deg(), gd = g.deg();
                if (const int k = fd / 2; k > 128 and k <= gd) {
                    PolynomialMatrix<Polynomial> Q = half_gcd(Polynomial(f.begin() + k, f.end()), Polynomial(g.begin() + k, g.end()), (fd - k) / 2).first;
                    if (Q != e1<Polynomial>()) {
                        auto [f2, g2] = mul_vec(Q, { std::move(f), std::move(g) });
                        f = std::move(f2), g = std::move(g2);
                        if (f.deg() <= lo) break;
                        P = mul_mat(Q, P);
                    }
                }
                if (g.deg() <= lo) break;
                auto [p, q] = f.div_mod(g);
                f = std::move(g), g = std::move(q);
                P = mul_mat(PolynomialMatrix<Polynomial>{ Polynomial{}, Polynomial{ 1 }, Polynomial{ 1 }, -p }, P);
            }
            return { P, f };
        }

        // { x, y, g=gcd(a,b) (monic) } s.t. ax+by=g
        template <typename Polynomial>
        std::tuple<Polynomial, Polynomial, Polynomial> ext_gcd(Polynomial a, Polynomial b) {
            bool swapped = false;
            a.cut_trailing_zeros();
            b.cut_trailing_zeros();
            if (a.size() < b.size()) std::swap(a, b), swapped = true;
            auto [P, g] = half_gcd(a, b);
            auto& [x, y] = P[0];
            if (g.size()) {
                auto c = g.back().inv();
                x *= c, y *= c, g *= c;
            }
            if (swapped) std::swap(x, y);
            return { x, y, g };
        }
    }

    // @return { x, y, g=gcd(a,b) (monic) } s.t. ax+by=g
    template <typename Polynomial>
    std::tuple<Polynomial, Polynomial, Polynomial> polynomial_ext_gcd(const Polynomial &a, const Polynomial &b) {
        return internal::poly_gcd::ext_gcd(a, b);
    }
    // @return { x, g=gcd(a,b) (monic) } s.t. ax=g (mod m)
    template <typename Polynomial>
    std::pair<Polynomial, Polynomial> polynomial_gcd_inv(const Polynomial &a, const Polynomial &m) {
        auto [x, _, g] = polynomial_ext_gcd(a, m);
        return { x, g };
    }
    // @return x s.t. ax=1 (mod m)
    template <typename Polynomial>
    std::pair<Polynomial, Polynomial> polynomial_inv(const Polynomial &a, const Polynomial &m) {
        auto [x, _, g] = polynomial_ext_gcd(a, m);
        assert(g == Polynomial{1});
        return x;
    }
    // @return gcd(a,b) (monic)
    template <typename Polynomial>
    std::tuple<Polynomial, Polynomial, Polynomial> polynomial_gcd(const Polynomial &a, const Polynomial &b) {
        return std::get<2>(ext_gcd(a, b));
    }
} // namespace suisen


#endif // SUISEN_POLYNOMIAL_GCD
